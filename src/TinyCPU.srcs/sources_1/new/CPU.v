`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2017/12/09 21:36:49
// Design Name: 
// Module Name: CPU
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module CPU(input clk, input uart_rxd, output uart_txd, output [6:0] dis1, output [6:0] dis2, output [3:0] sel1, output [3:0] sel2);
    wire [31:0] data_bus; wire [31:0] addr_bus;

    wire exec_clk, serial_clk;
    Clock clock(clk, exec_clk, serial_clk);

    wire _jump, _rel, _addr_ext_mode;
    wire [1:0] _s_next_PC;
    wire _ext_signed, _mem_en, _mem_rw, _mem_byte;
    wire [1:0] _r1_sel; wire [1:0] _r2_sel; wire [1:0] _rw_sel;
    wire [4:0] _w_reg; wire [1:0] _s_regw_data;
    wire [1:0] _s_alu_op2; wire [4:0] _alu_funct;
    
    wire [4:0] r_r1; wire [4:0] r_r2; wire [4:0] r_rw;
    wire [31:0] r_r1v; wire [31:0] r_r2v; wire [31:0] r_rwv;
    RegSet regs(exec_clk, r_r1, r_r1v, r_r2, r_r2v, r_rw, r_rwv);
    assign data_bus = (_mem_en && _mem_rw) ? r_r2v : 32'bz;
    
    wire [31:0] alu_op1; wire [31:0] alu_op2; wire [31:0] alu_ans;
    ALU alu(exec_clk, alu_op1, alu_op2, _alu_funct, alu_ans);
    assign alu_op1 = r_r1v;
    assign addr_bus = alu_ans;
    
    wire [31:0] PC; wire [31:0] next_PC;
    ProgramCounter pc(exec_clk, next_PC, _jump, alu_ans[0], _rel, PC);
    
    wire [31:0] dev_en;
    AddressTranslator addresstranslator(_mem_en, addr_bus, dev_en);
    
    wire [31:0] instr;
    MainMemory mainmemory(exec_clk, PC, instr, _mem_byte,
                          dev_en[0], _mem_rw, addr_bus, data_bus);
    
    wire [31:0] debug;
    Serial serial(exec_clk, serial_clk, dev_en[1], _mem_rw, addr_bus, data_bus,
                  uart_txd, uart_rxd, debug);
    
    wire [5:0] d_opcode;
    wire [4:0] d_rs; wire [4:0] d_rt; wire [4:0] d_rd;
    wire [4:0] d_shamt; wire [5:0] d_funct;
    wire [15:0] d_immd; wire [25:0] d_addr;
    Decoder decoder(instr, d_opcode, d_rs, d_rt, d_rd,
                    d_shamt, d_funct, d_immd, d_addr);
    
    wire [31:0] immd_ext;
    assign immd_ext = _ext_signed ? {{16{d_immd[15]}}, d_immd} : {{16{1'b0}}, d_immd};
    
    wire [31:0] addr_ext;
    assign addr_ext = _addr_ext_mode ? {PC[31:26], d_addr} : {{6{d_addr[25]}}, d_addr};
    
    Controller controller(d_opcode, d_funct, _jump, _rel, _addr_ext_mode, _s_next_PC,
                          _ext_signed, _mem_en, _mem_rw, _mem_byte,
                          _r1_sel, _r2_sel, _rw_sel, _w_reg, _s_regw_data,
                          _s_alu_op2, _alu_funct);
    
    MUX4_32 next_PC_mux(_s_next_PC, r_r2v, immd_ext << 2, addr_ext << 2, 0, next_PC);
    
    MUX4_32 rwv_mux(_s_regw_data, PC+4, data_bus, alu_ans, 0, r_rwv);
    
    MUX4_5 r1_mux(_r1_sel, 5'b0, d_rs, d_rt, d_rd, r_r1);
    MUX4_5 r2_mux(_r2_sel, 5'b0, d_rs, d_rt, d_rd, r_r2);
    MUX4_5 rw_mux(_rw_sel, _w_reg, d_rs, d_rt, d_rd, r_rw);
    
    MUX4_32 alu_op2_mux(_s_alu_op2, 0, r_r2v, {27'b0, d_shamt}, immd_ext, alu_op2);

// for debug use only
    display_driver display(clk, debug, dis1, dis2, sel1);
    assign sel2 = sel1;
endmodule
