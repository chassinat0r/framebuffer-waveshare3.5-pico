# Search for all source files in the current directory
# and save the names to the DIR_DISPLAY_SRCS variable
aux_source_directory(. DIR_DISPLAY_SRCS)

include_directories(../lcd)
include_directories(../config)
include_directories(../font)


# Generate link library
add_library(display ${DIR_DISPLAY_SRCS})
target_link_libraries(display PUBLIC pico_stdlib lcd config font hardware_spi)
