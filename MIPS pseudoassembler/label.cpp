#include <string>
#include <map>
#include <vector>
#include <utility>
#include <cstdio>
using namespace std;

#include "common.h"
#include "instr.h"

map<string, uint32_t> labels;

void _ADD_LABEL(string label){
    Assert(labels.find(label) == labels.end(), "redefinition of label `%s'.", label.c_str());
    labels[label] = mem_ptr;
}

enum LINK_TYPE{LINKING_J, LINKING_J_PC, LINKING_I, LINKING_I_PC};

struct LINK_RECORD{
    LINK_TYPE type;
    uint32_t position;
    string label;
};

vector<LINK_RECORD> links;

void _ADD_LINK_RCD(LINK_TYPE type, uint32_t position, string label){
    LINK_RECORD rcd = {type, position, label};
    links.push_back(rcd);
}

void process_links(){
    union {
        INSTR_I instr_I;
        INSTR_J instr_J;
    };
    LINK_TYPE type;
    uint32_t position;
    string label;
    for (unsigned i = 0; i < links.size(); i++){
        type = links[i].type;
        position = links[i].position;
        label = links[i].label;
        fprintf(stderr, "[LINKER] Resolving symbol `%s' at 0x%x ...\n", label.c_str(), position);
        Assert((position & 3) == 0, "the address is not aligned! (addr = 0x%x)\n", position);
        Assert(labels.find(label) != labels.end(), "label `%s' is not defined.", label.c_str());
        switch (type){
        case LINKING_I:
            instr_I.instr_u32 = *(uint32_t*)(mem+position);
            instr_I.immd += labels[label];
            *(uint32_t*)(mem+position) = instr_I.instr_u32;
            break;
        case LINKING_I_PC:
            instr_I.instr_u32 = *(uint32_t*)(mem+position);
            instr_I.immd += (labels[label] - position) / 4;
            *(uint32_t*)(mem+position) = instr_I.instr_u32;
            break;
        /*
        case LINKING_J:
            union {
                struct {
                    uint32_t addr:26;
                    uint32_t opcode:6;
                };
                uint32_t instr_u32;
            } _instr_J;
            _instr_J.instr_u32 = *(uint32_t*)(mem+position);
            _instr_J.addr += labels[label];
            *(uint32_t*)(mem+position) = _instr_J.instr_u32;
            break;
        */
        case LINKING_J_PC:

            instr_J.instr_u32 = *(uint32_t*)(mem+position);
            instr_J.addr += labels[label] / 4;
            *(uint32_t*)(mem+position) = instr_J.instr_u32;
            break;
        default:
            Assert(0, "unknown linking type for label `%s' at 0x%x.", label.c_str(), position);
        }
    }
}
