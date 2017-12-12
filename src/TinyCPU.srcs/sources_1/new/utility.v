`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2017/12/09 21:29:54
// Design Name: 
// Module Name: utility
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


module MUX4_5(input [1:0] sel, input [4:0] x0, input [4:0] x1, input [4:0] x2, input [4:0] x3,
              output reg [4:0] y);
    always @(*) begin
        case (sel)
            0: y = x0;
            1: y = x1;
            2: y = x2;
            3: y = x3;
        endcase
    end
endmodule

module MUX4_32(input [1:0] sel, input [31:0] x0, input [31:0] x1, input [31:0] x2, input [31:0] x3,
               output reg [31:0] y);
    always @(*) begin
        case (sel)
            0: y = x0;
            1: y = x1;
            2: y = x2;
            3: y = x3;
        endcase
    end
endmodule

module MUX2_32(input sel, input [31:0] x0, input [31:0] x1, output [31:0] y);
    assign y = sel ? x1 : x0;
endmodule

module FIFO8(input write_clk, input write_en, input [7:0] wdata, 
             input read_clk, input read_en, output [7:0] rdata, 
             output full, output empty);
    reg [7:0] FIFO [256:0];
    reg [7:0] rptr; reg [7:0] wptr;
    initial begin
        rptr = 0; wptr = 0;
    end
    assign full = (wptr == rptr - 1);
    assign empty = (wptr == rptr);
    assign rdata = FIFO[rptr];
    always @(posedge write_clk) begin
        if (write_en && !full) begin
            FIFO[wptr] <= wdata;
            wptr <= wptr + 1;
        end
    end
    always @(posedge read_clk) begin
        if (read_en && !empty) rptr <= rptr + 1;
    end
endmodule
