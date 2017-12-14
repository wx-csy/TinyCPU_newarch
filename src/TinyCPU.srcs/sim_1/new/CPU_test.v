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
    reg clk;
    reg uart_rxd;
    wire uart_txd;
    CPU cpu(clk, uart_rxd, uart_txd, , , ,);
    
    task send_thru_serial;
        input [7:0] data;
        reg [10:0] frame;
        integer i;
        begin
            frame = {1'b1, (^data[7:0]), data, 1'b0};
            for (i = 0; i<=10; i=i+1) begin
                uart_rxd = frame[i]; #32;
            end
        end
    endtask
    
    initial begin 
        clk = 0; uart_rxd = 1; 
        #545;
        send_thru_serial(8'h1);
        send_thru_serial(8'h0);
        send_thru_serial(8'h0);
        send_thru_serial(8'h0);
        send_thru_serial(8'h27);
        send_thru_serial(8'he3);
        send_thru_serial(8'h52);
        send_thru_serial(8'hf0);
    end
    
    always #1 clk = ~clk;
endmodule
