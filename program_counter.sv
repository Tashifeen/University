`timescale 1ns / 1ps

// Purpose: PC Used to hold the address of the next instruction in a simple CPU
// Behaviour:
	// On every clock cycle, PC updates
	// If reset active, PC jumps back to 0
	// If branch is taken, PC jumps by signed branch amount
	// Otherwise, PC increments by 1 in order to fetch the next instruction
// Who cares?: allows the CPU to follow different paths through the program in response to data path results

module program_counter(
  // Clock - rising edge triggers synchronous clock signal
  // nReset - active low reset that returns the program counter to zero
  input logic Clock, nReset,
  
  // Active high branch taken signal 
  input logic Taken,
  
  // Signed branch amount where
  //   + is forward
  //   - is backward
  input logic signed [7:0] Bamt,
  
  // Stores current program address
  output logic [7:0] PC
);
  

  // Use sequential logic - update PC on every rising edge of "Clock" or negative edge of "nReset"
  always_ff @(posedge Clock or negedge nReset) begin
    // If reset is active (i.e. nReset = 0), then set the PC back to 0
    if (~nReset) begin
      PC <= 8'd0; // <= means after all calculations PC is reset to 0
    end // "begin" and "end" are complimentary to each other
    
    else begin
      // Branch case: If Taken = 1, PC jumps by Bamt (branch amount)
      if (Taken)
        PC <= PC + Bamt;
      // Normal case: If no branch is taken, PC just adds 1 (so moving to the next instruction)
      else
        PC <= PC + 8'd1;
    end // ends entire else statment (which holds the 2 cases inside)
  end // ends sequential logic block (always_ff)

endmodule
