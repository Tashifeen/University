`timescale 1ns / 1ps

module test_register_file;
  logic Clock, nReset;
  logic WB;
  logic [3:0] Rd, Ra, Rb;
  logic [7:0] Data;
  
  logic [7:0] A, B, LED0, LED1;
  
  register_file rf (.*);
  
  // Using a 100MHz clock 
  // where (10ns period = 5ns high, 5ns low)
  always #5ns Clock = ~Clock;
  
  // Print outputs when they change
  // Help: https://www.chipverify.com/verilog/verilog-display-tasks 
  always @(A or B or LED0 or LED1)
    $display("Time=%0t | Ra=%2d Rb=%2d | A=%3d B=%3d | LED0=%3d LED1=%3d | WB=%b Rd=%2d Data=%3d",
              $time, Ra, Rb, A, B, LED0, LED1, WB, Rd, Data);
  
  // Stop sim. after 300ns
  initial #300ns $finish;
  
  initial begin
    // 1. Initialize all signals
    Clock = 0;
    nReset = 1;
    WB = 0;
    Rd = 0;
    Ra = 0; 
    Rb = 0;
    Data = 0;
    #10ns;
    
    // 2. Apply and release reset
    nReset = 0;
    #20ns nReset = 1; 
    #10ns; 
    
    // 3. Test special registers R0 and R1
    $display("\n1. Test special registers R0 and R1");
    Ra = 0; 
    Rb = 1; // Read R0 and R1
    #20ns;
    
    // 4. Write to R2 and read back
    $display("\n 2. Write and read R2");
    WB = 1;
    Rd = 2; 
    Data = 42;
    #20ns;
    WB = 0; 
    Ra = 2; 
    Rb = 2;
    #20ns;
    
    // 5. Test writing to all WRITABLE registers (R2-R15)
    	// Help: https://stackoverflow.com/questions/37909010/signed-multiplication-multiplying-numbers-of-different-sizes
    $display("\n 3. Write to multiple registers (R3-R7)");
    for (int i = 2; i < 16; i++) begin
      WB = 1;
      Rd = i; 
      Data = i * 10; // unique value to be stored in each register
      #20ns;
      WB = 0;
      Ra = i;
      Rb = i;
      #20ns;
    end
    
    // 6. Test LED registers (R14 and R15)
    	// read and write
    $display("\n 4. Test LED registers (R14, R15)");
    WB = 1;
    Rd = 14; 
    Data = 100;
    #20ns;
    WB = 1;
    Rd = 15;
    Data = 200;
    #20ns;
    WB = 0;
    Ra = 14;
    Rb = 15;
    #20ns;
    
    // 7. Try to write to protected registers R0 and R1
    $display("\n 5. Try writing to protected registers (should fail)");
    WB = 1;
    Rd = 0;
    Data = 99;
    #20ns;
    Ra = 0; // Read R0 - should still be 0
    #10ns;
    
    WB = 1;
    Rd = 1;
    Data = 99;
    #20ns;
    Rb = 1; // Read R1 - should still be 1
    #10ns;
    
    // 8. Test simultaneous reads from different registers
    $display("\n 6. Simultaneous reads from different registers");
    WB = 0;
    Ra = 3;
    Rb = 5;
    #10ns;
    Ra = 4;
    Rb = 6;
    #10ns;
    Ra = 7;
    Rb = 2;
    #10ns;
    
    // 9. Test reading while writing same register
    	// Before posedge: reads will show old data
    	// after posedge: reads show 80
    $display("\n 7. Read while writing same register");
    WB = 1; 
    Rd = 8;
    Data = 80;
    Ra = 8; 
    Rb = 8;
    #20ns;
    WB = 0;
    #10ns;
    
    
    // 10. Final read spot-checks
	// Increment i by 3 to read registers Ra, Rb simultaneously
    $display("\n 9. Final read of key registers");
    WB = 0;
    for (int i = 0; i < 16; i = i + 3) begin
      Ra = i; 
      Rb = (i+1) % 16;
      #10ns;
    end
    
  end
  
endmodule
