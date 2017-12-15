#include <string>

void _data(string label, string str){
    _ADD_LABEL(label);
    for (unsigned i = 0; i <= str.length(); i++){
        *(char*)(mem+mem_ptr) = (char)(str[i]);
        mem_ptr += 1;
    }
    while (mem_ptr & 3) mem_ptr++;
}

