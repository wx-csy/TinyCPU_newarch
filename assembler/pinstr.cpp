#define NOP()           SLL($0, $0, 0)
#define MOV(rd, rt)     SLL(rd, rt, 0)
#define NOT(rd, rs)     NOR(rd, rs, $0)
#define NEG(rd, rt)     SUBU(rd, $0, rt)
#define LI(rd, immd)    ADDIU(rd, $0, immd)

void _org(uint32_t pos){
    mem_ptr = pos;
}

void LOFFSET(_REGISTER rd, string label){
    _ADD_LINK_RCD(LINKING_I, mem_ptr, label);
    ADDIU(rd, $0, 0);
}

#define $(label) _ADD_LABEL(label);
