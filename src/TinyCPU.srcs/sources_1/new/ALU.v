module ALU(input clk, input [31:0] op1, input [31:0] op2, input [4:0] funct, output reg [31:0] ans);
    reg [32:0] tmp;
    reg [31:0] HI = 0; reg [31:0] LO = 0;
    always @(*) begin
        case (funct)
            5'b00000: ans = 0;              // 0
            5'b00001: ans = op1 + op2;      // ADD
            5'b00011: ans = op1 - op2;      // SUB
            5'b00100: ans = op1 & op2;      // AND
            5'b00101: ans = op1 | op2;      // OR
            5'b00110: ans = op1 ^ op2;      // XOR
            5'b00111: ans = ~(op1 | op2);   // NOR
            5'b01000: ans = (op1 == 0) || (op1[31]);    // <=0
            5'b01001: ans = (op1 == op2);    // ==
            5'b01010:                        // LT
                begin
                    tmp = op1 - op2;
                    ans = (tmp[32] == tmp[31]);
                end
            5'b01011: ans = (op1 < op2);    // LTU
            5'b01100: ans = op1 << (op2[4:0]);      // SLL
            5'b01101: ans = op1 >> (op2[4:0]);      // SRL
            5'b10000: ans = HI;                 // MFHI
            5'b10010: ans = LO;                 // MFLO
            default: ans = 0;              // undefined funct
        endcase
    end
    
    always @(posedge clk) begin
        case (funct)
            5'b11001: begin {HI, LO} <= op1 * op2; end              // MULTU
            5'b11011: begin HI <= op1 % op2; LO <= op1 / op2; end   // DIVU
        endcase
    end
endmodule
