`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2017/12/07 14:52:58
// Design Name: 
// Module Name: Controller
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

module ProgramCounter(input clk, input [31:0] next_PC, input jump, input cond, input rel, output reg [31:0] PC);
    initial PC = 0;
    always @(posedge clk) begin
        if (jump && cond) begin
            if (rel) PC <= PC + 4 + next_PC;
            else PC <= next_PC;
        end else 
            PC <= PC + 4;
    end
endmodule 

module Controller(input [5:0] opcode, input [5:0] funct,
                  output _jump, output _rel, output _addr_ext_mode, output [1:0] _s_next_PC,
                  output _ext_signed, output _mem_en, output _mem_rw, output _mem_byte,
                  output [1:0] _r1_sel, output [1:0] _r2_sel, output [1:0] _rw_sel, output [4:0] _w_reg, output [1:0] _s_regw_data,
                  output [1:0] _s_alu_op2, output [4:0] _alu_funct);
    reg [28:0] CW;
    assign {_jump, _rel, _addr_ext_mode, _s_next_PC, _ext_signed, _mem_en, _mem_rw, _mem_byte,
            _r1_sel,  _r2_sel, _rw_sel, _w_reg, _s_regw_data, _s_alu_op2, _alu_funct
           } = CW;
            
    (* rom_style = "block" *)reg [28:0] CW_op [63:0];
    (* rom_style = "block" *)reg [28:0] CW_sp [63:0];

    integer i;
    initial begin
        for (i = 0; i <= 63; i = i + 1) begin
            case (i)
                6'b100011: CW_op[i] = 29'b_0_0_0_00__1__1_0_0__01_00_10_00000_01__11_00001; // LW
                6'b101011: CW_op[i] = 29'b_0_0_0_00__1__1_1_0__01_10_00_00000_00__11_00001; // SW
                6'b100000: CW_op[i] = 29'b_0_0_0_00__1__1_0_1__01_00_10_00000_01__11_00001; // LB
                6'b101000: CW_op[i] = 29'b_0_0_0_00__1__1_1_1__01_10_00_00000_00__11_00001; // SB
        
                6'b001001: CW_op[i] = 29'b_0_0_0_00__1__0_0_0__01_00_10_00000_10__11_00001; // ADDIU
                6'b001100: CW_op[i] = 29'b_0_0_0_00__0__0_0_0__01_00_10_00000_10__11_00100; // ANDI
                6'b001101: CW_op[i] = 29'b_0_0_0_00__0__0_0_0__01_00_10_00000_10__11_00101; // ORI
                6'b001110: CW_op[i] = 29'b_0_0_0_00__0__0_0_0__01_00_10_00000_10__11_00110; // XORI
                6'b001010: CW_op[i] = 29'b_0_0_0_00__1__0_0_0__01_00_10_00000_10__11_01010; // SLTI
                6'b001011: CW_op[i] = 29'b_0_0_0_00__1__0_0_0__01_00_10_00000_10__11_01011; // SLTIU
        
                6'b000010: CW_op[i] = 29'b_1_0_1_10__0__0_0_0__00_00_00_00000_00__00_01000; // J
                6'b000100: CW_op[i] = 29'b_1_1_0_01__1__0_0_0__01_10_00_00000_00__01_01001; // BEQ
                6'b000110: CW_op[i] = 29'b_1_1_0_01__1__0_0_0__01_00_00_00000_00__00_01000; // BLEZ
                6'b000011: CW_op[i] = 29'b_1_0_1_10__0__0_0_0__00_00_00_11111_00__00_01000; // JAL
                default:   CW_op[i] = 29'b_0_0_0_00__0__0_0_0__00_00_00_00000_00__00_00000; 
            endcase
            case (i)
                6'b100001: CW_sp[i] = 29'b_0_0_0_00__0__0_0_0__01_10_11_00000_10__01_00001; // ADDU
                6'b100011: CW_sp[i] = 29'b_0_0_0_00__0__0_0_0__01_10_11_00000_10__01_00011; // SUBU
                6'b100100: CW_sp[i] = 29'b_0_0_0_00__0__0_0_0__01_10_11_00000_10__01_00100; // AND
                6'b100101: CW_sp[i] = 29'b_0_0_0_00__0__0_0_0__01_10_11_00000_10__01_00101; // OR
                6'b100110: CW_sp[i] = 29'b_0_0_0_00__0__0_0_0__01_10_11_00000_10__01_00110; // XOR
                6'b100111: CW_sp[i] = 29'b_0_0_0_00__0__0_0_0__01_10_11_00000_10__01_00111; // NOR
                6'b101010: CW_sp[i] = 29'b_0_0_0_00__0__0_0_0__01_10_11_00000_10__01_01010; // SLT
                6'b101011: CW_sp[i] = 29'b_0_0_0_00__0__0_0_0__01_10_11_00000_10__01_01011; // SLTU
                6'b000000: CW_sp[i] = 29'b_0_0_0_00__0__0_0_0__10_00_11_00000_10__10_01100; // SLL
                6'b000100: CW_sp[i] = 29'b_0_0_0_00__0__0_0_0__10_01_11_00000_10__01_01100; // SLLV
                6'b000010: CW_sp[i] = 29'b_0_0_0_00__0__0_0_0__10_00_11_00000_10__10_01101; // SRL
                6'b000110: CW_sp[i] = 29'b_0_0_0_00__0__0_0_0__10_01_11_00000_10__01_01101; // SRLV
                6'b011001: CW_sp[i] = 29'b_0_0_0_00__0__0_0_0__01_10_00_00000_00__01_11001; // MULTU
                6'b011011: CW_sp[i] = 29'b_0_0_0_00__0__0_0_0__01_10_00_00000_00__01_11011; // DIVU
                6'b010000: CW_sp[i] = 29'b_0_0_0_00__0__0_0_0__00_00_11_00000_10__00_10000; // MFHI
                6'b010010: CW_sp[i] = 29'b_0_0_0_00__0__0_0_0__00_00_11_00000_10__01_10010; // MFLO
                
                6'b001000: CW_sp[i] = 29'b_1_0_0_00__0__0_0_0__00_01_00_00000_00__00_01000; // JR
                default:   CW_sp[i] = 29'b_0_0_0_00__0__0_0_0__00_00_00_00000_00__00_00000; 
            endcase;
        end
    end

    always @(*) begin
        case (opcode)
            6'b000000: CW = CW_sp[funct];
            default:   CW = CW_op[opcode];
        endcase
    end

endmodule
