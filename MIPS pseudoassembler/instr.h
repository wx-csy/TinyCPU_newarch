#ifndef _INSTR_H
#define _INSTR_H

union INSTR_R{
    struct {
        uint32_t funct:6;
        uint32_t shamt:5;
        uint32_t rd:5;
        uint32_t rt:5;
        uint32_t rs:5;
        uint32_t opcode:6;
    };
    uint32_t instr_u32;
};

union INSTR_I {
    struct {
        uint32_t immd:16;
        uint32_t rt:5;
        uint32_t rs:5;
        uint32_t opcode:6;
    };
    uint32_t instr_u32;
};

union INSTR_J {
    struct {
        uint32_t addr:26;
        uint32_t opcode:6;
    };
    uint32_t instr_u32;
};

#endif
