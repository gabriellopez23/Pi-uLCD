project( pi-ulcd )

# set your include directories (if you have any)
include_directories( includes )
include_directories( mbed-hal-interface )
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# tell cmake what what are your source files
set( CPP_SOURCE_FILES 
    rpi-hal-implementation/DigitalOut.cpp
    rpi-hal-implementation/Serial.cpp
    ulcd/graphics.cpp
    ulcd/media.cpp
    ulcd/text.cpp
    ulcd/main.cpp
    )

# if you are creating an executable then do so like this
# note that ${MY_CPP_FILES} will replace it with its content
add_executable( myExec ${CPP_SOURCE_FILES} )

# if you instead want a library, do it like so
# add_library( myStaticLib STATIC ${MY_CPP_FILES} ) # create a static library
# add_library( mySharedLib SHARED ${MY_CPP_FILES} ) # create a shared library