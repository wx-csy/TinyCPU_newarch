inline void LW(_REGISTER rt, _REGISTER base, _IMMEDIATE offset){
    _MAKE_INSTR(I, (043, base, rt, offset));
}

inline void LW(_REGISTER rt, _REGISTER base, string label){
    _ADD_LINK_RCD(LINKING_I, mem_ptr, label);
    _MAKE_INSTR(I, (043, base, rt, 0));
}

inline void SW(_REGISTER rt, _REGISTER base, _IMMEDIATE offset){
    _MAKE_INSTR(I, (053, base, rt, offset));
}

inline void SW(_REGISTER rt, _REGISTER base, string label){
    _ADD_LINK_RCD(LINKING_I, mem_ptr, label);
    _MAKE_INSTR(I, (053, base, rt, 0));
}

inline void LB(_REGISTER rt, _REGISTER base, _IMMEDIATE offset){
    _MAKE_INSTR(I, (040, base, rt, offset));
}

inline void LB(_REGISTER rt, _REGISTER base, string label){
    _ADD_LINK_RCD(LINKING_I, mem_ptr, label);
    _MAKE_INSTR(I, (040, base, rt, 0));
}

inline void SB(_REGISTER rt, _REGISTER base, _IMMEDIATE offset){
    _MAKE_INSTR(I, (050, base, rt, offset));
}

inline void SB(_REGISTER rt, _REGISTER base, string label){
    _ADD_LINK_RCD(LINKING_I, mem_ptr, label);
    _MAKE_INSTR(I, (050, base, rt, 0));
}
