#cmake_minimum_required(VERSION 3.13)

#set(PICO_BOARD "pico_w")  # Required setting, since the Pico W is slightly
                          # different from the default Pico. Has to be set
                          # before including the SDK's cmake.
#include(/home/Tashifeen/pico-sdk/pico_sdk_init.cmake)  # Include the Pico SDK cmake
                                                # logic

# Usual cmake things
#project(lab5_amber C CXX ASM) # CHANGE HERE
#add_executable(lab5_amber lab5_amber.c) # CHANGE HERE

# Pico setup
#pico_sdk_init()  # Initialise the Pico SDK

# Enable USB output, disable UART output (see the Comms lecture later)
#pico_enable_stdio_usb(lab5_amber 1)
#pico_enable_stdio_uart(lab5_amber 0)

# Create extra output files when building, useful later!
#pico_add_extra_outputs(lab5_amber) # CHANGE HERE

# Note the weird standard and warning configuration, to support the SDK and its
# accompanying tools. Also include -O3 for extra "gogogo".
#set(CMAKE_C_STANDARD gnu17)
#target_compile_options(lab5_amber PRIVATE -Wall -Wextra -Werror
#                       -Wno-unused-parameter -O3) # CHANGE HERE
#target_link_libraries(lab5_amber pico_stdlib pico_cyw43_arch_none hardware_adc) # CHANGE HERE

cmake_minimum_required(VERSION 3.13)

set(PICO_BOARD "pico_w")  # Required setting, since the Pico W is slightly
                          # different from the default Pico. Has to be set
                          # before including the SDK's cmake.
include(/home/Tashifeen/pico-sdk/pico_sdk_init.cmake)  # Include the Pico SDK cmake
                                                # logic

# Usual cmake things
project(first_example C CXX ASM)
add_executable(first_example first_example.c)

# Pico setup
pico_sdk_init()  # Initialise the Pico SDK

# Enable USB output, disable UART output (see the Comms lecture later)
pico_enable_stdio_usb(first_example 1)
pico_enable_stdio_uart(first_example 0)

# Create extra output files when building, useful later!
pico_add_extra_outputs(first_example)

# Note the weird standard and warning configuration, to support the SDK and its
# accompanying tools. Also include -O3 for extra "gogogo".
set(CMAKE_C_STANDARD gnu17)
target_compile_options(first_example PRIVATE -Wall -Wextra -Werror
                       -Wno-unused-parameter -O3)
target_link_libraries(first_example pico_stdlib pico_cyw43_arch_none)
