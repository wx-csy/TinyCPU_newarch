`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2017/12/10 10:58:41
// Design Name: 
// Module Name: ALU_test
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


module ALU_test();
    reg [31:0] op1;
    reg [31:0] op2;
    reg [3:0] funct;
    wire [31:0] ans;
    ALU alu(op1, op2, funct, ans);
    
    initial begin
        op1 = 32'h82141953; op2 = 32'h83521abd; funct = 4'b0000; #10;
        funct = 4'b0001; #10;
        funct = 4'b0011; #10;
        op1 = 32'h13894; op2 = 32'habcd; #10;
        op1 = 32'h76543210; op2 = 32'h89abcdef; funct = 4'b0100; #10;
        funct = 4'b0101; #10; funct = 4'b0110; #10; funct = 4'b0111; #10;
        op1 = -325; funct = 4'b1000; #10; op1 = 2147483647; #10;
        op1 = -2147483648; #10; op1 = 0; #10; op1 = 1; #10;
        op1 = -2147483648; op2 = 2147483647; funct = 4'b1010; #10;
        op1 = 0; op2 = -1; #10;
        op1 = 2147483647; op2 = -1; #10
        op1 = 1; op2 = -2147483648; #10
        op1 = 2053; op2 = 28360; funct = 4'b1011; #10;
        op1 = 246; op2 = 0; #10;
        op1 = 28; op2 = 3; funct = 4'b1100; #10;
        op1 = 426; op2 = 6'b100010; #10;
        op1 = 128; op2 = 3; funct = 4'b1101; #10;
        op1 = 298; op2 = 6'b100001; #10;
    end
endmodule
