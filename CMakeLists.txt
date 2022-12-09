project( pi-ulcd )

# dependencies for cmake
find_package(Threads REQUIRED)
add_subdirectory(pigpio)

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
set(CMAKE_INCLUDE_CURRENT_DIR ON)


# if you are creating an executable then do so like this
# note that ${MY_CPP_FILES} will replace it with its content
# add_executable( pi-ulcd ${LIB_CPP_SOURCE_FILES} )

#add pthread library
target_link_libraries(pi-ulcd Threads::Threads)

#adding pigpio to project
target_link_libraries(pi-ulcd pigpio)

#compiling demo with this lib
add_executable( pi-ulcd-demo main.cpp )
target_include_directories( pi-ulcd-demo PRIVATE includes )
target_include_directories( pi-ulcd-demo PRIVATE mbed-hal-interface )
target_link_libraries( pi-ulcd-demo Threads::Threads )
target_link_libraries( pi-ulcd-demo pigpio )
target_link_libraries( pi-ulcd-demo pi-ulcd )

