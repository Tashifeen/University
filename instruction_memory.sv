// Purpose: Instruction memory holds all of the programs instructions and outputs the instruction at the address pointed to by the program counter 
// Behaviour: 
    // PC is treated and used as an index to the memory array 
    // Instr would output the instruction stored at memory[PC].


module instruction_memory(
    input  logic [7:0]  PC, // current program address
    output logic [15:0] Instr // the value stored stored in program memory at teh PC address
);

    // Packed vs Unpacked arrays (Source: https://verificationguide.com/systemverilog/systemverilog-packed-and-unpacked-array/) 
        // Packed arrays: declared before the variable name 
        // Bits are stored contiguously (side by side) 
        // e.g. 000, 001, 010 ...
        // Unpacked arrays declared after the variable name 
        // Elements are stored separately, like a list of items 
        // 111, 010, 100, 011 ... (kind of random)


    // For this one below... 
        // Each item (memory[i]) is packed (16 bits) 
        // But the array itself is unpacked (256 seperate items) logic [15:0] memory [255:0] 
        // 256 instructions (2^8 since we are dealing with 8 bits)
    logic [15:0] memory [255:0];

    // Combinational read
    // Output instruction at PC address
    assign Instr = memory[PC];

endmodule
