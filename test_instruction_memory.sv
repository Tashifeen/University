`timescale 1ns / 1ps

module test_instruction_memory;
  logic [7:0]  PC;
  logic [15:0] Instr;

  instruction_memory im0 (.*);   

  // Print whenever Instr changes
  // Help: https://www.chipverify.com/verilog/verilog-display-tasks
  always @(Instr)
    $display("Time=%0t | PC=%d | Instr=%h", $time, PC, Instr);

  initial begin
    // 1. Preload some instructions into memory
    	// Represent as hex values (Source: https://circuitcove.com/system-tasks-format-spec/)
    im0.memory[0]  = 16'hABCD; // inst at address 0
    im0.memory[1]  = 16'h1234; // inst at address 1
    im0.memory[2]  = 16'hDEAD; // inst at address 2
    im0.memory[3]  = 16'hBEEF; // inst at address 3
    im0.memory[10] = 16'hFACE; // inst at address 10

    // 2. Read from address 0
    PC = 8'd0;
    #5ns;

    // 3. Read from address 1
    PC = 8'd1;
    #5ns;

    // 4. Read from address 2
    PC = 8'd2;
    #5ns;

    // 5. Read from address 3
    PC = 8'd3;
    #5ns;

    // 6. Read from address 10
    PC = 8'd10;
    #5ns;

    // 7. Read from an address we didn’t preload
    // This will show X or 0 depending on simulator defaults
    PC = 8'd20;
    #5ns;
    
    $finish;
    
  end

endmodule

