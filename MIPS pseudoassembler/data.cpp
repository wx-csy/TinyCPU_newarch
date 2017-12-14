#include <string>

void $data(string label, string str){
    _ADD_LABEL(label);
    for (unsigned i = 0; i <= str.length(); i++){
        *(uint32_t*)(mem+mem_ptr) = (unsigned)(str[i]);
        mem_ptr += 4;
    }
}

