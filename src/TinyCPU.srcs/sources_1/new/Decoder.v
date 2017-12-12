`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2017/12/07 14:56:20
// Design Name: 
// Module Name: Decoder
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


module Decoder(input [31:0] instr, output [5:0] opcode, 
               output [4:0] rs, output [4:0] rt, output [4:0] rd,
               output [4:0] shamt, output [5:0] funct,
               output [15:0] immd, output [25:0] addr);
    assign opcode = instr[31:26];
    assign rs = instr[25:21];
    assign rt = instr[20:16];
    assign rd = instr[15:11];
    assign shamt = instr[10:6];
    assign funct = instr[5:0];
    assign immd = instr[15:0];
    assign addr = instr[25:0];
endmodule
