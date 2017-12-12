`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2017/12/12 12:54:04
// Design Name: 
// Module Name: AddressTranslator
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


module AddressTranslator(input en, input [31:0] address, output reg [31:0] en_dev);
    wire dev_id;
    assign dev_id = address[14:10];
    always @(*) begin
        if (!en) en_dev = 0;
        else begin
            if (address[31] == 0) en_dev = 1;
            else en_dev = dev_id > 0 ? 1 << (address[14:10]) : 0;
        end
    end
endmodule
