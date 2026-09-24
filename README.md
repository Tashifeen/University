# CPU Design Coursework
 
## Files
 
### Source Modules
- `program_counter.sv` - Program Counter implementation
- `instruction_memory.sv` - Instruction Memory implementation
- `alu.sv` - Arithmetic Logic Unit (ALU) implementation
- `decoder.sv` - Instruction Decoder implementation
- `register_file.sv` - Register File implementation
 
### Testbenches
- `test_program_counter.sv` - Tests for Program Counter
- `test_alu.sv` - Tests for ALU
- `test_decoder.sv` - Tests for Decoder
- `test_register_file.sv` - Tests for Register File
 
## Running Tests
 
Compile the required module with its corresponding testbench using your SystemVerilog simulator.
 
Example:
 
```bash
iverilog -g2012 program_counter.sv test_program_counter.sv -o test_pc
vvp test_pc
