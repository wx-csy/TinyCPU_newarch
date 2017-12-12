`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2017/12/08 20:41:10
// Design Name: 
// Module Name: Memory_test
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


module Memory_test();
    reg mclk, clk;
    reg [13:0] instr_addr;
    wire [31:0] instr_data;
    reg we;
    reg [13:0] data_addr;
    reg [31:0] wdata;
    wire [31:0] data;
    Memory mem(mclk, instr_addr, instr_data, we, data_addr, wdata, data);
    
    always #5 mclk = ~mclk;
    always #10 clk = ~clk;
    initial begin
        mclk = 0; clk = 0; we = 0;
        instr_addr = 0; data_addr = 0;
        #9; we = 1; wdata = 32'h01234567;
        #20; we = 0;
        #20; instr_addr = 1;
    end
endmodule
