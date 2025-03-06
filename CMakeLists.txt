cmake_minimum_required(VERSION 3.12)
include(pico_sdk_import.cmake)
project(main) 
pico_sdk_init()

# Add compilation subdirectory
add_subdirectory(lib/config)
add_subdirectory(lib/lcd)
add_subdirectory(lib/font)
add_subdirectory(lib/fatfs)
add_subdirectory(lib/sdcard)
add_subdirectory(lib/display)

# Add header file directory
include_directories(./lib/config)
include_directories(./lib/lcd)
include_directories(./lib/font)
include_directories(./lib/fatfs)
include_directories(./lib/sdcard)
include_directories(./lib/display)

# Generate executable file
add_executable(main 
main.cpp
)

# enable usb output, disable uart output
pico_enable_stdio_usb(main 1)
pico_enable_stdio_uart(main 0)

# create map/bin/hex/uf2 file etc.
pico_add_extra_outputs(main)

#target_compile_definitions(main PRIVATE PICO_DEFAULT_SPI_SCK_PIN=10 PICO_DEFAULT_SPI_TX_PIN=11 PICO_DEFAULT_SPI_RX_PIN=12)
target_link_libraries(main lcd font config fatfs display pico_stdlib pico_cyw43_arch_lwip_threadsafe_background hardware_spi)
