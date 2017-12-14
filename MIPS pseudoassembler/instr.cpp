#include "common.h"
#include "instr.h"
#define _MAKE_INSTR(type, param) uint32_t instr = _encode_instr_##type param; write_instr(instr)

inline uint32_t _encode_instr_R(uint8_t opcode, _REGISTER rs, _REGISTER rt, _REGISTER rd, uint8_t shamt, uint8_t funct){
    _BITS_LIMIT(opcode, 6);
    _BITS_LIMIT(rs.index, 5);
    _BITS_LIMIT(rt.index, 5);
    _BITS_LIMIT(rd.index, 5);
    _BITS_LIMIT(shamt, 5);
    _BITS_LIMIT(funct, 6);

    INSTR_R instr;
    instr.opcode = opcode; instr.rs = rs.index; instr.rt = rt.index;
    instr.rd = rd.index; instr.shamt = shamt; instr.funct = funct;
    return instr.instr_u32;
}

inline uint32_t _encode_instr_I(uint8_t opcode, _REGISTER rs, _REGISTER rt, _IMMEDIATE immd){
    _BITS_LIMIT(opcode, 6);
    _BITS_LIMIT(rs.index, 5);
    _BITS_LIMIT(rt.index, 5);

    INSTR_I instr;
    instr.opcode = opcode; instr.rs = rs.index; instr.rt = rt.index;
    instr.immd = immd;
    return instr.instr_u32;
}

inline uint32_t _encode_instr_J(uint8_t opcode, _ADDRESS address){
    _BITS_LIMIT(opcode, 6);
    _BITS_LIMIT(address, 26);

    INSTR_J instr;
    instr.opcode = opcode; instr.addr = address;
    return instr.instr_u32;
}

// namespace instr{
    #include "instrs/memory.cpp"
    #include "instrs/alu.cpp"
    #include "instrs/jump.cpp"
// }

// #include "instrs/all-instr.h"
