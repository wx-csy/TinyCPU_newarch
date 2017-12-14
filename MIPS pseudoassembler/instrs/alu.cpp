inline void ADDU(_REGISTER rd, _REGISTER rs, _REGISTER rt){
    _MAKE_INSTR(R, (0, rs, rt, rd, 0, 041));
}

inline void ADDIU(_REGISTER rt, _REGISTER rs, _IMMEDIATE immd){
    _MAKE_INSTR(I, (011, rs, rt, immd));
}

inline void SUBU(_REGISTER rd, _REGISTER rs, _REGISTER rt){
    _MAKE_INSTR(R, (0, rs, rt, rd, 0, 043));
}

inline void AND(_REGISTER rd, _REGISTER rs, _REGISTER rt){
    _MAKE_INSTR(R, (0, rs, rt, rd, 0, 044));
}

inline void ANDI(_REGISTER rt, _REGISTER rs, _IMMEDIATE immd){
    _MAKE_INSTR(I, (014, rs, rt, immd));
}

inline void OR(_REGISTER rd, _REGISTER rs, _REGISTER rt){
    _MAKE_INSTR(R, (0, rs, rt, rd, 0, 045));
}

inline void ORI(_REGISTER rt, _REGISTER rs, _IMMEDIATE immd){
    _MAKE_INSTR(I, (015, rs, rt, immd));
}

inline void XOR(_REGISTER rd, _REGISTER rs, _REGISTER rt){
    _MAKE_INSTR(R, (0, rs, rt, rd, 0, 046));
}

inline void XORI(_REGISTER rt, _REGISTER rs, _IMMEDIATE immd){
    _MAKE_INSTR(I, (016, rs, rt, immd));
}

inline void NOR(_REGISTER rd, _REGISTER rs, _REGISTER rt){
    _MAKE_INSTR(R, (0, rs, rt, rd, 0, 047));
}

inline void SLT(_REGISTER rd, _REGISTER rs, _REGISTER rt){
    _MAKE_INSTR(R, (0, rs, rt, rd, 0, 052));
}

inline void SLTI(_REGISTER rt, _REGISTER rs, _IMMEDIATE immd){
    _MAKE_INSTR(I, (012, rs, rt, immd));
}

inline void SLTU(_REGISTER rd, _REGISTER rs, _REGISTER rt){
    _MAKE_INSTR(R, (0, rs, rt, rd, 0, 053));
}

inline void SLTIU(_REGISTER rt, _REGISTER rs, _IMMEDIATE immd){
    _MAKE_INSTR(I, (013, rs, rt, immd));
}

inline void SLL(_REGISTER rd, _REGISTER rt, uint8_t shamt){
    _MAKE_INSTR(R, (0, $0, rt, rd, shamt, 000));
}

inline void SLLV(_REGISTER rd, _REGISTER rt, _REGISTER rs){
    _MAKE_INSTR(R, (0, rs, rt, rd, 0, 010));
}

inline void SRL(_REGISTER rd, _REGISTER rt, uint8_t shamt){
    _MAKE_INSTR(R, (0, $0, rt, rd, shamt, 002));
}

inline void SRLV(_REGISTER rd, _REGISTER rt, _REGISTER rs){
    _MAKE_INSTR(R, (0, rs, rt, rd, 0, 012));
}

