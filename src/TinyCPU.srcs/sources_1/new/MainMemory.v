`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2017/12/08 20:34:54
// Design Name: 
// Module Name: Memory
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

module MainMemory(input clk, input [31:0] instr_addr, output [31:0] instr_data,
                  input en, input rw, input [31:0] address, inout [31:0] io_data);

    reg [31:0] mem [4095:0];
    wire [11:0] mem_index;
    assign instr_data = mem[instr_addr[13:2]];
    assign mem_index = address[13:2];
    assign data = mem[address[13:2]];
    initial begin
        $readmemh("E:/Vivado/TinyCPU_newarch/result.txt", mem);
    end
    assign io_data = (en && ~rw) ? mem[mem_index] : 32'bz;
    always @(posedge clk) begin
        if (en && rw) mem[mem_index] <= io_data;
    end 
    
endmodule
