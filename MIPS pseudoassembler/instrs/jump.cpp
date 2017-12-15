inline void J(_ADDRESS addr){
    _MAKE_INSTR(J, (002, addr));
}

inline void J(string label){
    _ADD_LINK_RCD(LINKING_J, mem_ptr, label);
    _MAKE_INSTR(J, (002, 0));
}

inline void BLEZ(_REGISTER rs, _IMMEDIATE offset){
    _MAKE_INSTR(I, (006, rs, $0, offset));
}

inline void BLEZ(_REGISTER rs, string label){
    _ADD_LINK_RCD(LINKING_I_PC, mem_ptr, label);
    _MAKE_INSTR(I, (006, rs, $0, -1));
}

inline void JAL(_ADDRESS addr){
    _MAKE_INSTR(J, (003, addr));
}

inline void JAL(string label){
    _ADD_LINK_RCD(LINKING_J, mem_ptr, label);
    _MAKE_INSTR(J, (003, 0));
}

inline void JR(_REGISTER rs){
    _MAKE_INSTR(R, (0, rs, $0, $0, 0, 010));
}

