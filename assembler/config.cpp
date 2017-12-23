#include <cstdlib>
#include <string>
using namespace std;

uint32_t MEM_SIZE_WORD = 4096;
uint32_t LOAD_OFFSET = 128*4;
bool generate_hex = 1;

void load_config(int argc, char* argv[]){
    int argptr = 1;
    string cmd;
    while (argptr < argc){
        cmd = argv[argptr];
        if (cmd == "-m") {
            argptr++;
        } else if(cmd == "-h"){
            argptr++;
        } else if (cmd == "-?"){
            printf("Usage: [TBD]\n");
        } else {
            printf("Unknown command \"%s\". For usage, use -?.\n", argv[argptr]);
        }
    }
}

void init_config(){
    mem = (char*)calloc(MEM_SIZE_WORD, 4);
}
