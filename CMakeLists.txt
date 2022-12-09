cmake_minimum_required (VERSION 3.18)

project( pi-ulcd )

# dependencies for cmake
find_package(Threads REQUIRED)
add_subdirectory(pigpio)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

# tell cmake what what are your source files
set( LIB_CPP_SOURCE_FILES 
    rpi-hal-implementation/DigitalOut.cpp
    rpi-hal-implementation/Serial.cpp
    rpi-hal-implementation/util.cpp
    ulcd/graphics.cpp
    ulcd/media.cpp
    ulcd/text.cpp
    ulcd/core.cpp
    )
# make a pi-ulcd static library
add_library( pi-ulcd STATIC ${LIB_CPP_SOURCE_FILES} ) # create a static library

# set your include directories (if you have any)
target_include_directories( pi-ulcd PRIVATE includes )
target_include_directories( pi-ulcd PRIVATE mbed-hal-interface )
target_link_libraries(pi-ulcd PRIVATE pigpio)
target_link_libraries(pi-ulcd PRIVATE Threads::Threads)

#compiling demo with this lib
add_executable( pi-ulcd-demo main.cpp )
target_include_directories( pi-ulcd-demo PRIVATE includes )
target_include_directories( pi-ulcd-demo PRIVATE mbed-hal-interface )
target_link_libraries( pi-ulcd-demo PRIVATE pigpio )
target_link_libraries( pi-ulcd-demo PRIVATE Threads::Threads )
target_link_libraries( pi-ulcd-demo PRIVATE pi-ulcd )

file(COPY ./java.mk DESTINATION ./)