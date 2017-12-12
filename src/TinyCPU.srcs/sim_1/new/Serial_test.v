`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2017/12/12 19:17:06
// Design Name: 
// Module Name: Serial_test
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


module Serial_test();
    reg clk, clk_100M, en, rw;
    reg [31:0] address;
    reg [31:0] iodata_reg;
    wire [31:0] iodata = en && rw ? iodata_reg : 32'bz;
    wire uart_txd;
    Serial serial(clk, clk_100M, en, rw, address, iodata, uart_txd, 1);
    
    always #5 begin clk = ~clk; clk_100M = ~clk_100M; end
    initial begin
        clk = 0;
        clk_100M = 0;
        address = 16;
        en = 1; rw = 1;
        iodata_reg = 32'ha3;
        #6; en = 0;
    end
endmodule
