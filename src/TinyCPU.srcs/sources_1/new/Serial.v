`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2017/12/09 21:19:48
// Design Name: 
// Module Name: Serial
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

//               100MHz       50MHz         25MHz
// buad rate    increment
// 9600         412317       824634       1649267
// 19200        824634       1649267      3298535
// 38400        1649267      3298535      6597070
// 57600        2473901      4947802      9895605
// 115200       4947802      9895605      19791209

// `define __DEBUG__

module freq_div(input clk, input en, output out_freq);
    reg [31:0] cnt;
    initial cnt = 0;
`ifdef __DEBUG__
    always @(posedge clk) if (en) cnt = cnt + 1073741824/4; else cnt = 0;
`else
    always @(posedge clk) if (en) cnt = cnt + 1649267; else cnt = 0;
`endif
    assign out_freq = cnt[31];
endmodule

module serial_rx(input clk_serial, input uart_rxd, 
                 output reg FIFO_we, output reg [7:0] FIFO_wdata,
                 output reg check, output reg [31:0] debug = 0);
    reg [7:0] cnt;
    reg [11:0] frame;
    reg last_s_clk;
    reg arrival;
    integer i;
    wire s_clk;
    
    freq_div div(clk_serial, arrival, s_clk);
    initial begin
        FIFO_wdata = 0;
        FIFO_we = 0;
        cnt = 0;
        check = 0;
        frame = 0;
        last_s_clk = 0;
        arrival = 0;
    end
    always @(posedge clk_serial) begin
        if (~arrival & ~uart_rxd) begin
            arrival <= 1;
            cnt <= 0;
        end else if (arrival) begin
            if (cnt == 11) begin
                arrival <= 0;
                cnt <= 0;
                FIFO_wdata <= 0;
                FIFO_we <= 0;
            end else
            if (s_clk & ~last_s_clk) begin
                frame[cnt] <= uart_rxd;
                if (cnt == 10) begin
                    cnt <= cnt + 1;
                    debug[31:0] <= {debug[31:16] + 1, debug[8:1], frame[8:1]};
                    FIFO_wdata <= frame[8:1];
                    FIFO_we <= 1;
                    check <= ^(frame[9:1]);
                end else cnt <= cnt + 1;
            end
        end
        last_s_clk <= s_clk;
    end
endmodule

module serial_tx(input clk_serial, input FIFO_empty, input [7:0] FIFO_rdata, output reg FIFO_re, output reg uart_txd,
                 output reg [31:0] debug = 0);
    reg [9:0] frame;
    reg sending;
    reg [7:0] cnt;
    integer i;
    reg last_s_clk;
    
    wire s_clk;
    freq_div div(clk_serial, sending, s_clk);
    
    initial begin
        sending = 0;
        uart_txd = 1;
        frame = 0;
        cnt = 0;
        last_s_clk = 0;
        FIFO_re = 0;
    end
    
    always @(posedge clk_serial) begin
        if (FIFO_re == 1) FIFO_re <= 0;
        if (~sending && ~FIFO_empty) begin
            uart_txd <= 0;
            cnt <= 0;
            sending <= 1;
            frame[7:0] <= FIFO_rdata;
            debug <= (debug << 8) | FIFO_rdata;
            frame[8] <= (^FIFO_rdata[7:0]);
            frame[9] <= 1;
            FIFO_re <= 1;
        end else if (last_s_clk & ~s_clk) begin
            if (cnt <= 9) begin
                uart_txd <= frame[cnt];
                cnt <= cnt + 1;
            end else begin
                uart_txd <= 1;
                cnt <= 0;
                sending <= 0;
            end
        end
        last_s_clk <= s_clk;
    end
endmodule

module Serial(input clk, input clk_serial, input en, input rw, input [31:0] address, inout [31:0] iodata,
              output uart_txd, input uart_rxd, output [31:0] debug);
    wire [9:0] port = address[9:0];
    
    wire rx_FIFO_full, rx_FIFO_empty;
    wire rx_FIFO_write_en;
    wire rx_FIFO_read_en = en && ~rw && (port == 16);
    wire [7:0] rx_FIFO_wdata;
    wire [7:0] rx_FIFO_rdata;
    FIFO8 rx_FIFO(clk_serial, rx_FIFO_write_en, rx_FIFO_wdata, 
                  clk, rx_FIFO_read_en, rx_FIFO_rdata, 
                  rx_FIFO_full, rx_FIFO_empty);
    
    wire tx_FIFO_full, tx_FIFO_empty;
    wire tx_FIFO_write_en = (en && rw && (port == 16));
    wire tx_FIFO_read_en;
    wire [7:0] tx_FIFO_wdata = iodata[7:0];
    wire [7:0] tx_FIFO_rdata;
    FIFO8 tx_FIFO(clk, tx_FIFO_write_en, tx_FIFO_wdata, 
                  clk_serial, tx_FIFO_read_en, tx_FIFO_rdata, 
                  tx_FIFO_full, tx_FIFO_empty);
    
    serial_rx rx(clk_serial, uart_rxd, rx_FIFO_write_en, rx_FIFO_wdata, , );
    serial_tx tx(clk_serial, tx_FIFO_empty, tx_FIFO_rdata, tx_FIFO_read_en, uart_txd, debug);
    
    reg [31:0] output_data;
    assign iodata = (en & ~rw) ? output_data : 32'bz;
    
    always @(*) begin
        case (port)
            0: output_data = {31'b0, ~rx_FIFO_empty};   // rx_receive
            1: output_data = {31'b0, tx_FIFO_full};     // tx_busy
            16: output_data = {24'b0, rx_FIFO_rdata};   // rx/tx
            default: output_data = 0;
        endcase
    end
    
endmodule
