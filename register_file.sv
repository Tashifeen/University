`timescale 1ns / 1ps

// Purpose: Register file contains 16 registers of 8 bit length that are used to store intermediate computation values
// Behaviour: Has two read ports (Ra, Rb) and one write port (WB) with synchronous writes and asynchronous reset

module register_file(
    input logic Clock,nReset,
    input logic WB,
    input logic [3:0] Rd, Ra, Rb,
    input logic [7:0] Data,
    
    output logic [7:0] A, B,
    output logic [7:0] LED0, LED1
 );
  
  // 16 registers - 8 bits each
  logic [7:0] regs [15:0];
  
  // Using enum for register indices
  	// Note: the value of R14, R15 <=> LED0, LED1
  enum logic [3:0] {
    R0, R1, R2, R3,
    R4, R5, R6, R7,
    R8, R9, R10, R11,
    R12, R13, R14, R15
  } regs_index; // We don't use this (not needed)
  
  // Combinatorial reads (same for Ra and Rb)
  // A lot more efficnient than using always_comb 
  	 // ? -> ternary conditional operator (if : else)
  assign A = (Ra == R0) ? 8'b0 : // if Ra == R0 -> output 0
    		 (Ra == R1) ? 8'b1 : // if Ra == R1 -> output 1
    		 regs[Ra];
  
  assign B = (Rb == R0) ? 8'b0 :
    		 (Rb == R1) ? 8'b1 :
    		 regs[Rb];
  
  
  // Synchronous writes
  always_ff @(posedge Clock or negedge nReset)
    begin
  	    if (~nReset) 
  	        begin
  	            // clear values of all registers using for loop (Source: https://www.chipverify.com/systemverilog/systemverilog-for-loop)
  	            for (int i = 0; i < 16; i++) // 0 - 15, ++ means increment by 1
  	                begin
  	                    regs[i] <= 8'b0;
                    end
                // force R1 to 1 after reset (as R1 is hardcoded to output 1!)
                regs[R1] <= 8'b1;
            end 
      
        // Contents of register will only be updated if WB AND rd == 1
      	// && -> behavioural "AND" statement
      	// use R1 to compare here to be safe as R1 is hardcoded to be 0 in denary and binary
        else if (WB && Rd > R1)
            begin
              regs[Rd] <= Data; // Wite only to R2-R15
            end
    end
  
  // LED outputs
  assign LED0 = regs[R14];
  assign LED1 = regs[R15];

endmodule



