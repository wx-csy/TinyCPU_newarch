`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2017/12/03 20:05:12
// Design Name: 
// Module Name: display
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

module display_decoder(input [3:0] num, output reg [6:0] dis);
    always @(*) begin
        case (num)
            0: dis = 7'b0111111;
            1: dis = 7'b0000110;
            2: dis = 7'b1011011;
            3: dis = 7'b1001111;
            4: dis = 7'b1100110;
            5: dis = 7'b1101101;
            6: dis = 7'b1111101;
            7: dis = 7'b0000111;
            8: dis = 7'b1111111;
            9: dis = 7'b1101111;
            10:dis = 7'b1110111;
            11:dis = 7'b1111100;
            12:dis = 7'b1011000;
            13:dis = 7'b1011110;
            14:dis = 7'b1111001;
            15:dis = 7'b1110001;
        endcase
    end
endmodule

module display_driver(input clk, input [31:0] data, output [6:0] dis1, output [6:0] dis2, output [3:0] sel);
    wire [1:0] sw;
    reg [31:0] cnt;
    initial cnt = 0;
    assign sw = cnt[31:30];
    assign sel = 1 << sw;
    display_decoder dec1(data[16+sw*4 +: 4], dis1);
    display_decoder dec2(data[sw*4 +: 4], dis2);
    always @(posedge clk) cnt = cnt + 4295;
endmodule
