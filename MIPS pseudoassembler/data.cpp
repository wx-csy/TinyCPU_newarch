#include <string>

void _data(string label, string str){
    _ADD_LABEL(label);
    for (unsigned i = 0; i <= str.length(); i++){
        *(char*)(mem+mem_ptr) = (char)(str[i]);
        mem_ptr += 1;
    }
    while (mem_ptr & 3) mem_ptr++;
}

void _udata(string label, uint32_t size){
    _ADD_LABEL(label);
    for (unsigned i = 0; i < size; i++){
        Warn(*(char*)(mem+mem_ptr) == 0, "the data of `%s' at 0x%x is not zero.\n", label.c_str(), mem_ptr);
        *(char*)(mem+mem_ptr) = 0;
        mem_ptr += 1;
    }
    while (mem_ptr & 3) mem_ptr++;
}
