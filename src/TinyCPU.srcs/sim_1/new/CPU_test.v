`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2017/12/10 15:42:23
// Design Name: 
// Module Name: CPU_test
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


module CPU_test();
    reg clk, uart_rxd;
    wire uart_txd;
    CPU cpu(clk, uart_rxd, uart_txd, , , ,);
    
    task send_thru_serial;
        input [7:0] data;
        reg [10:0] frame;
        integer i;
        begin
            frame = {1'b1, (^data[7:0]), data, 1'b0};
            for (i = 0; i<=10; i=i+1) begin
                uart_rxd = frame[i]; #16;
            end
        end
    endtask
    
    initial begin 
        clk = 0; uart_rxd = 1; 
        // #544;
        // send_thru_serial(8'h61);
        // send_thru_serial(8'h32);
    end
    
    always #1 clk = ~clk;
endmodule
