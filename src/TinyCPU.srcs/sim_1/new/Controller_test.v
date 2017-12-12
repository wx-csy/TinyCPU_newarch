`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2017/12/10 00:59:02
// Design Name: 
// Module Name: Controller_test
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


module Controller_test();
    wire _jump, _rel, _addr_ext_mode;
    wire [1:0] _s_next_PC;
    wire _ext_signed, _mem_rw;
    wire [1:0] _r1_sel; wire [1:0] _r2_sel; wire [1:0] _rw_sel;
    wire [4:0] _w_reg; wire [1:0] _s_regw_data;
    wire [1:0] _s_alu_op2; wire [3:0] _alu_funct;
    wire _serial_txrx, _serial_send, _s_iow;
    
    reg [5:0] d_opcode;
    reg [5:0] d_funct;
    Controller controller(d_opcode, d_funct, _jump, _rel, _addr_ext_mode, _s_next_PC,
                              _ext_signed, _mem_rw,
                              _r1_sel, _r2_sel, _rw_sel, _w_reg, _s_regw_data,
                              _s_alu_op2, _alu_funct,
                              _serial_txrx, _serial_send, _s_iow);
    
    initial begin
        d_opcode = 0; d_funct = 0; #10;
        d_opcode = 6'b111111; d_funct = 6'b100000; #10;
        $stop;
    end
endmodule
