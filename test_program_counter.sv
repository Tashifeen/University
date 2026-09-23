`timescale 1ns / 1ps

module test_program_counter;

  // Signals used for driving the program counter
  logic Clock, nReset, Taken;
  logic signed [7:0] Bamt;
  logic [7:0] PC;

  // Instantiate PC
  program_counter pc0 (.*);   // shorthand connects signals by name (Source: https://stackoverflow.com/questions/58436253/in-systemverilog-what-does-mean)
  
  // Print PC whenever it changes
  // Help: https://www.chipverify.com/verilog/verilog-display-tasks 
  always @(PC)
    $display("Time=%0t | PC=%d | Reset=%b | Taken=%b | Bamt=%d",
              $time, PC, nReset, Taken, Bamt);

  // Start clock at 0, then toggle every 5ns -> 10ns period
  initial Clock = 0;
  always #5ns Clock <= ~Clock;

  initial begin
    // 1. Initial conditions
    $display("\n 1. Setting inital values");
    nReset = 0; // Reset active so PC moved to 0
    Taken = 0; // No branch, PC will just increment normally
    Bamt = 0; // Since Taken is 0, the branch amount will be irrelevant!
    #10ns;
    nReset = 1; // reset is released, now the PC starts counting...

    // 2. Normal increments
    // PC increments by 1 each cycle (while Taken = 0)
    // Executed 5 times
    $display("\n 2. Incrementing PC (x5)");
    repeat (5) #10ns; // repeat function in sv source: https://www.chipverify.com/systemverilog/systemverilog-repeat-loop

    // 3. Branch forward by +4
    $display("\n 3. Branching forward by +4");
    Taken = 1; 
    Bamt = 8'd4;
    #10ns; 
    Taken = 0; // Stop branching

    // 4. Normal increments again
    $display("\n 4. Back to incrementing PC (x3)");
    repeat (3) #10ns; 

    // 5. Branch backward by -2
    $display("\n 5. Branching backward by -2");
    Taken = 1; 
    Bamt = -(8'd2);
    #10ns;
    Taken = 0;

    // 6. Normal increments again
    $display("\n 6. Back to incrementing PC (x3)");
    repeat (3) #10ns;

    // 7. Reset mid-run
    	// PC goes back to 0
    $display("\n 7. Applying reset mid-run");
    nReset = 0;
    #10ns; 
    nReset = 1;

    // 8. Typical increments after reset
    $display("\n 8. Back to incrementing PC (x3) after reset");
    repeat (3) 
    #10ns;
    
    // 9. Edge case 1 - Overflow
    	// Move PC close to max (255) and let it increment pass the value so it wraps aroud to 0
    $display("\n 9. Overflow (with increments after)");
    PC = 8'd250; // manually set PC near the limit
    #1ns
    Taken = 0;
    repeat (10) 
    #10ns;
    
    // 10. Edge case 2 - Underflow
      // PC wraps around to 255
    $display("\n 10. Underflow (with increments after)");
    PC = 8'd0;
    #1ns
    Taken = 1; 
    Bamt = -8'd1; 
    #10ns; 
    Taken = 0;
    repeat (5) 
    #10ns;
  
  $finish;  
  end

endmodule



