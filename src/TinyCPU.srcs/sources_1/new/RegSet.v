module RegSet(input clk,
              input [4:0] r1, output [31:0] r1v,
              input [4:0] r2, output [31:0] r2v,
              input [4:0] rw, input  [31:0] rwv);
    reg [31:0] regs [31:0];
    integer i;
    initial begin
        for (i = 0; i < 32; i = i + 1) regs[i] = 0;
    end
    assign r1v = regs[r1];
    assign r2v = regs[r2];
    always @(posedge clk) begin
        if (rw != 0) begin
            regs[rw] <= rwv;
        end
    end
endmodule
