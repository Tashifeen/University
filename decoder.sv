// Purpose+Behaviour: The decoder takes the instruction opcode as an input that uniquely identifies the instruction and outputs the required control signals to perform the operation

module decoder(
    input logic [3:0] Opcode,
    output logic [2:0] ALUOp,
    output logic WB, ImmEnable, ImmType, Branch
);
    // Assume [3:0] Opcode  =  ABCD
        // Help: https://agirlamonggeeks.com/systemverilog-array-reduction-operator-on-2-d-array/
        // "assign" is much simpler to code than "always_comb" here imo
    assign ALUOp = Opcode[2:0];   
    assign WB = |Opcode; // A+B+C+D
    assign ImmEnable = Opcode[3]; // A only   
  assign ImmType = ~(|Opcode[2:0]); // (¬B+¬C+¬D) 
  assign Branch = ~(|Opcode); // ¬(A+B+C+D)
    
endmodule
