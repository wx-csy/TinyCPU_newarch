`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2017/12/08 22:05:04
// Design Name: 
// Module Name: Clock
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

module Clock(input raw_clk,  output exec_clk, output serial_clk);
    reg [8:0] cnt;
    wire run;
    reg [8:0] div;
    initial begin
        cnt = 0;
        div = 0;
    end
    assign run = cnt[8];
    assign exec_clk = run & div[3];
    assign serial_clk = run & div[1];
    always @(negedge raw_clk) begin
        if (!run) cnt = cnt + 1; else div = div + 1;
    end
endmodule
