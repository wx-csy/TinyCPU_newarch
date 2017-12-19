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

module MainMemory(input clk, input [31:0] instr_addr, output [31:0] instr_data, input byte,
                  input en, input rw, input [31:0] address, inout [31:0] io_data);

    reg [31:0] mem [4095:0];
    wire [31:0] word_data = mem[address[13:2]];
    wire [7:0] byte_data = mem[address[13:2]] >> (8*address[1:0]);
    wire [31:0] data = byte ? {{24{byte_data[7]}}, byte_data} : word_data;
    assign instr_data = mem[instr_addr[13:2]];
    
    initial begin
        $readmemh("E:/Vivado/TinyCPU_newarch/result.txt", mem);
    end
    assign io_data = (en && ~rw) ? data : 32'bz;
    always @(posedge clk) begin
        if (en && rw)
            if (byte)
                case (address[1:0])
                    0: mem[address[13:2]] <= mem[address[13:2]] & 32'hFFFFFF00 | io_data[7:0];
                    1: mem[address[13:2]] <= mem[address[13:2]] & 32'hFFFF00FF | (io_data[7:0] << 8);
                    2: mem[address[13:2]] <= mem[address[13:2]] & 32'hFF00FFFF | (io_data[7:0] << 16);
                    3: mem[address[13:2]] <= mem[address[13:2]] & 32'h00FFFFFF | (io_data[7:0] << 24);
                endcase
            else 
                mem[address[13:2]] <= io_data;
    end 
    
endmodule
