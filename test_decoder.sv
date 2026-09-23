module test_decoder;
  logic [3:0] Opcode;
  logic [2:0] ALUOp;
  logic WB, ImmEnable, ImmType, Branch;
  
  // Instantiate decoder
  decoder d0 (.*);
  
  // Print outputs when they change
  // Help: https://www.chipverify.com/verilog/verilog-display-tasks 
  always @(ALUOp or WB or ImmEnable or ImmType or Branch)
    $display("Time=%0t | Opcode=%4b | ALUOp=%3b | WB=%b | ImmEnable=%b | ImmType=%b | Branch=%b",
              $time, Opcode, ALUOp, WB, ImmEnable, ImmType, Branch);
  
  initial begin
    // Test all 16 opcodes
    for (int i = 0; i < 16; i++) begin
      Opcode = i;
      #10ns;
    end
    
    $finish;
    
  end
  
endmodule

