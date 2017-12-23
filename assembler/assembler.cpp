#include <cstdio>
#include <cstring>
using namespace std;
#include "common.h"
#include "device.h"

char* mem;

#include "config.cpp"

uint32_t mem_ptr = 0;

void write_instr(uint32_t instr){
    Assert((mem_ptr & 3) == 0, "the address is not aligned! (addr = 0x%x)\n", mem_ptr);
    *(uint32_t*)(mem+mem_ptr) = instr;
    mem_ptr += 4;
}

void generate_code(){
    /*
    puts("MEMORY_INITIALIZATION_RADIX=16;");
    printf("MEMORY_INITIALIZATION_VECTOR=");
    for (uint32_t i=0; i<MEM_SIZE_WORD; i++){
        printf("%08x,", ((uint32_t*)mem)[i]);
    }*/

    if (generate_hex){
        uint32_t limit = 0;
        for (uint32_t i = LOAD_OFFSET / 4; i < MEM_SIZE_WORD; i++) if (((uint32_t*)mem)[i]) limit = i;
        limit += 1;
        uint32_t sz = limit - LOAD_OFFSET / 4;
        unsigned char sz_chr[4];
        memcpy(sz_chr, &sz, 4);
        printf("size = %x (%02x %02x %02x %02x)\n", sz, sz_chr[0], sz_chr[1], sz_chr[2], sz_chr[3]);
        for (uint32_t i = LOAD_OFFSET; i < limit * 4; i++){
            printf("%02x ", (unsigned char)mem[i]);
        }

    } else {
        for (uint32_t i=0; i<MEM_SIZE_WORD; i++){
            printf("@%04x %08x\n", i, ((uint32_t*)mem)[i]);
        }
    }

}

#include "label.cpp"
#include "data.cpp"
#include "instr.cpp"
#include "pinstr.cpp"

int main(int argc, char* argv[]){
    load_config(argc, argv);
    init_config();

    void asm_code();
    asm_code();
    process_links();
    freopen("result.txt", "w", stdout);
    generate_code();
    fclose(stdout);
    fprintf(stderr, "The assembler has successfully exited.\n");
}

void asm_code(){
    #include "asm.cpp"
}
