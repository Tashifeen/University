cmake_minimum_required(VERSION 3.13)

set(PICO_BOARD "pico_w")  # Required setting, since the Pico W is slightly
                          # different from the default Pico. Has to be set
                          # before including the SDK's cmake.
include(/home/Tashifeen/pico-sdk/pico_sdk_init.cmake)  # Include the Pico SDK cmake
                                                # logic

# Usual cmake things
project(lab6_amber C CXX ASM)
add_executable(lab6_amber lab6_amber.c)

# Pico setup
pico_sdk_init()  # Initialise the Pico SDK

# Enable USB output, ENABLE UART OUTPUT
pico_enable_stdio_usb(lab6_amber 1)
pico_enable_stdio_uart(lab6_amber 1)

# Create extra output files when building, useful later!
pico_add_extra_outputs(lab6_amber)

# Note the weird standard and warning configuration, to support the SDK and its
# accompanying tools. Also include -O3 for extra "gogogo".
set(CMAKE_C_STANDARD gnu17)
target_compile_options(lab6_amber PRIVATE -Wall -Wextra -Werror
                       -Wno-unused-parameter -O3)
target_link_libraries(lab6_amber pico_stdlib pico_cyw43_arch_none)
