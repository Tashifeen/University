`timescale 1ns / 1ps

module test_alu;
  logic [2:0] ALUOp;       
  logic [7:0] A, B;        
  logic [7:0] result;      
  logic Zero, Carry;
  
  // Instantiate the ALU
  alu alu0 (.*);

  // Print whenever result changes
  // Help: https://www.chipverify.com/verilog/verilog-display-tasks 
  always @(result or Zero or Carry)
    $display("Time=%0t | ALUOp=%d | A=%d | B=%d | result=%d | Zero=%b | Carry=%b",
              $time, ALUOp, A, B, result, Zero, Carry);

  initial begin
    // 1. Exectuting all operations with A=10, B=3
    $display("\n 1. Simple test with all operations A = 10, B = 3");
    A = 8'd10;
    B = 8'd3;
    for (int i = 0; i < 8; i++) 
      begin
      	ALUOp = i; 
        #10ns;
      end
    
    // 2. Exteme shifts
    $display("\n 2. Extreme shifts");
    
    // Left shift by 8 (should give 0, carry = LSB)
    A = 8'b10101010; // 170
    B = 8'd8;
    ALUOp = 3'd6; // SHIFT_LEFT
    #10ns;
    
    // Left shift by 9 (should give 0, no carry)
    B = 8'd9;
    #10ns;
    
    // Right shift by 8 (should give 0, carry = MSB)
    B = 8'd8;
    ALUOp = 3'd7; // SHIFT_RIGHT
    #10ns;
    
    // Right shift by 9 (should give 0, no carry)
    B = 8'd9;
    #10ns;
    
    // 3. ADD/SUB carry flags
    $display("\n 3. ADD/SUBB with carry");
    
    // Test ADD overflow (255 + 1 = 0 with carry)
    A = 8'd255;
    B = 8'd1;
    ALUOp = 3'd2; // ADD
    #10ns;
    
    // Test SUB underflow (0 - 1 = 255 with carry)
    A = 8'd0;
    B = 8'd1;
    ALUOp = 3'd3; // SUB
    #10ns;
    
    // 4. Testing other operations don't set carry
    $display("\n 4. Testing other operations won't set carry");
    A = 8'd255;
    B = 8'd255;
    
    // Test OR (should get result, no carry)
    ALUOp = 3'd1; // OR
    #10ns;
    
    // Test AND (should get result, no carry)
    ALUOp = 3'd4; // AND
    #10ns;
    
    // Test XOR (should get result, no carry)
    ALUOp = 3'd5; // XOR
    #10ns;

    // 5. Random testing
    $display("\n 5. Randomised tests");
    repeat (10) begin // Source: https://learn.verificationstudio.com/tutorials/1/systemverilog-tutorial/subcontents/10/randomization
      A = $urandom_range(0,255);
      B = $urandom_range(0,255);
      ALUOp = $urandom_range(0,7); // Random operation code 0-7
      #10ns;
    end
  $finish;
  end

endmodule

