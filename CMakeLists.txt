cmake_minimum_required (VERSION 3.18)

project( pi-ulcd )

# dependencies for cmake
find_package(Threads REQUIRED)
find_package(Java REQUIRED)

#dont need jni extensions
find_package(JNI REQUIRED)

add_subdirectory(pigpio)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

# tell cmake what what are your source files
set( LIB_CPP_SOURCE_FILES 
    rpi-hal-implementation/__gpio_init.cpp
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

execute_process (
    COMMAND bash -c "cd .. && chmod 777 ./build-java.sh && cp ./run-java.sh ./build/run-java.sh && chmod 777 ./build/run-java.sh && ./build-java.sh"
)

execute_process (
    COMMAND bash -c "cd .. && cp -r ./res ./build/res"
)


include(UseJava)
add_library( pi-ulcd-jni MODULE pi-ulcd-jni/uLCDInterface.cpp com_nana_uLCDInterface.h)
set_property(TARGET pi-ulcd-jni PROPERTY POSITION_INDEPENDENT_CODE ON)
target_include_directories( pi-ulcd-jni PRIVATE ${JNI_INCLUDE_DIRS})
target_include_directories( pi-ulcd-jni PRIVATE com/nana/ )
target_include_directories( pi-ulcd-jni PRIVATE pi-ulcd-jni )
target_include_directories( pi-ulcd-jni PRIVATE includes )
target_include_directories( pi-ulcd-jni PRIVATE mbed-hal-interface )
target_include_directories( pi-ulcd-jni PRIVATE pi-ulcd-jni)
target_link_libraries( pi-ulcd-jni PRIVATE pigpio )
target_link_libraries( pi-ulcd-jni PRIVATE Threads::Threads )
target_link_libraries( pi-ulcd-jni PRIVATE pi-ulcd )
target_link_libraries( pi-ulcd-jni PRIVATE ${JNI_LIBRARIES} )
set_target_properties( pi-ulcd-jni PROPERTIES SUFFIX ".so" )