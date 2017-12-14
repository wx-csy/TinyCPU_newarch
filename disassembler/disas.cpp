#include <iostream>
#include <cstdio>
using namespace std;
#include "instr.h"

void printbits(uint32_t num, uint8_t bitcnt){
    for (int i=bitcnt-1; i>=0; i--)
        putchar((num&((uint32_t)(1)<<i))?'1':'0');
}

void print_instr_R(uint32_t instr){
    INSTR_R instr_R;
    instr_R.instr_u32 = instr;
    printf("[R] ");
    printbits(instr_R.opcode, 6); putchar(' ');
    printbits(instr_R.rs, 5); putchar(' ');
    printbits(instr_R.rt, 5); putchar(' ');
    printbits(instr_R.rd, 5); putchar(' ');
    printbits(instr_R.shamt, 5); putchar(' ');
    printbits(instr_R.funct, 6); putchar(' ');
    printf("\n");
    printf("   |opcode| rs  | rt  | rd  |shamt|funct |\n");
}

void print_instr_I(uint32_t instr){
    INSTR_I instr_I;
    instr_I.instr_u32 = instr;
    printf("[I] ");
    printbits(instr_I.opcode, 6); putchar(' ');
    printbits(instr_I.rs, 5); putchar(' ');
    printbits(instr_I.rt, 5); putchar(' ');
    printbits(instr_I.immd, 16); putchar(' ');
    printf("\n");
    printf("   |opcode| rs  | rt  |      immd      |\n");
}

void print_instr_J(uint32_t instr){
    INSTR_J instr_J;
    instr_J.instr_u32 = instr;
    printf("[J] ");
    printbits(instr_J.opcode, 6); putchar(' ');
    printbits(instr_J.addr, 26); putchar(' ');
    printf("\n");
    printf("   |opcode|           addr           |\n");
}


int main(){
    uint32_t instr;
    while (scanf("%x", &instr)){
        print_instr_R(instr);
        print_instr_I(instr);
        print_instr_J(instr);
    }
    return 0;
}
