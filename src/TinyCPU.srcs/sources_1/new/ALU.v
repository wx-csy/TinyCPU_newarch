module ALU(input [31:0] op1, input [31:0] op2, input [3:0] funct, output reg [31:0] ans);
     reg [32:0] tmp;
    always @(*) begin
        case (funct)
            4'b0000: ans <= 0;              // 0
            4'b0001: ans <= op1 + op2;      // ADD
            4'b0011: ans <= op1 - op2;      // SUB
            4'b0100: ans <= op1 & op2;      // AND
            4'b0101: ans <= op1 | op2;      // OR
            4'b0110: ans <= op1 ^ op2;      // XOR
            4'b0111: ans <= ~(op1 | op2);   // NOR
            4'b1000: ans <= (op1 == 0) || (op1[31]);    // <=0
            4'b1010:                        // LT
                begin
                    tmp = op1 - op2;
                    ans <= (tmp[32] == tmp[31]);
                end
            4'b1011: ans <= (op1 < op2);    // LTU
            4'b1100: ans <= op1 << (op2[4:0]);      // SLL
            4'b1101: ans <= op1 >> (op2[4:0]);      // SRL
            default: ans <= 0;              // undefined funct
        endcase
    end
endmodule
