`timescale 1ns / 1ps

// Purpose: ALU performs arithmetic and logic operations on two data inputs with ALUOp selecting which operation to perform
// Behaviour:
    // ALU looks at inputs A and B
    // performs selected arithmetic or logical operation, and produces the result
    // raises the Zero flag if the output is all 0s and sets Carry when there's a carry/borrow from an add/subtract operation

module alu(
  input logic [2:0] ALUOp,
  input logic [7:0] A, B,
  output logic [7:0] result,
  output logic Zero, Carry
);

  enum logic [2:0] {
    PASSTHROUGH = 3'b000,
    OR = 3'b001,
    ADD = 3'b010,
    SUB = 3'b011,
    AND = 3'b100,
    XOR = 3'b101,
    SHIFT_LEFT = 3'b110,
    SHIFT_RIGHT = 3'b111
  } op;
  
  logic [8:0] temp;
  
  always_comb begin
    // Defaults
    result = 8'h00;
    Carry = 1'b0;
    temp = 9'h000;
    
    unique case (ALUOp)
        PASSTHROUGH: 
            result = B;
      
        OR: 
            result = A | B;
      
        ADD: begin
            temp = A + B;
            result = temp[7:0];
            Carry = temp[8];
        end
          
        SUB: begin
            temp = A - B;
            result = temp[7:0];
            Carry = temp[8];
        end
          
        AND:
            result = A & B;
      
        XOR:
            result = A ^ B;
      
        SHIFT_LEFT: 
            begin
                // Shifts of 8 or more clear the value
                if (B >= 8) 
                begin
                    result = 8'h00;
            
                    // If shifting by exactly 8, the bit shifted out is original LSB (A[0])
                    Carry = (B == 8) ? A[0] : 1'b0;
                end 
                else 
                    begin
                    // Normal left shift 
                        // extending A with a zero on the RIGHT
                    temp = {A, 1'b0} << B;
            
                    // Extracting 8-bit shifted result
                    result = temp[8:1];
            
                    // Bit shifted out is the carry bit
                    Carry = temp[0];
                end
            end

        SHIFT_RIGHT: 
            begin
                // Shifts of 8 or more clear the value
                if (B >= 8) 
                begin
                    result = 8'h00;
            
                    // If shifting by exactly 8 -> the bit shifted out is original mSB (A[7])
                    Carry = (B == 8) ? A[7] : 1'b0;
                end 
                else 
                begin
                    // Normal left shift 
                        // extending A with a zero on the LEFT
                    temp = {1'b0, A} >> B;
            
                    // Extracting 8-bit shifted result
                    result = temp[7:0];
            
                     // Bit shifted out is the carry bi
                    Carry = temp[8];
                end
            end

      
    endcase
  end
  
  // Seperate assign and always_comb block for readability
  assign Zero = (result == 8'h00);
  
endmodule


