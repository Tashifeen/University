# Raspberry Pi Pico W – Lab 5 Project Overview

This project contains C code that runs on the Raspberry Pi Pico W using the
official Raspberry Pi Pico SDK. The project is built using CMake, and the
compiled `.uf2` file is flashed onto the Pico via USB.

---

## 📁 Project Structure

### `first_example.c`
This is where your program logic lives. You can create additional `.c` files in
the same directory (e.g., `morse.c`, `wifi_test.c`, etc.). If you add new source
files, you must list them in `CMakeLists.txt`.

### `CMakeLists.txt`
This file tells CMake:

- which `.c` files to compile
- which libraries to link
- which board you are targeting (`pico_w`)
- where the Pico SDK is located

You normally only edit this file when adding new source files or libraries.

### `build/`
This folder is **automatically generated** by CMake. It contains:

- Makefiles
- object files (`.o`)
- dependency files
- the final `.uf2` firmware file

You never edit anything inside `build/`.  
If something breaks, you can safely delete the entire folder and re-run CMake.

---

### 🛠️ Building the Project

From inside the project directory:

```bash
cd build
make -j8




## 🔌 Flashing the Pico W
- Hold the BOOTSEL button on the Pico.
- Plug it into your computer.
- Release BOOTSEL.
- A drive named RPI-RP2 appears in Windows.
- Mount it in WSL:
	sudo mkdir -p /mnt/pico
	sudo mount -t drvfs D: /mnt/pico   # Replace D: with your drive letter
- Copy the firmware
	cp first_example.uf2 /mnt/pico


## ➕ Adding New C Files
- If you create a new file, e.g. morse.c
- You must add it to CMakeLists.txt:
	add_executable(first_example
	    first_example.c
	    morse.c
	)
- Then rebuild:
	cd build
	make -j8

