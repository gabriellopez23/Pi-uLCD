#pragma once

#ifndef __PLATFORM_H__

#include <stdlib.h>

// #include "mbed-hal-interface/gpio.h"
// #include "mbed-hal-interface/DigitalIn.h"
#include "mbed-hal-interface/DigitalOut.h"
// #include "mbed-hal-interface/Stream.h"
// #include "mbed-hal-interface/BufferedSerial.h"
#include "mbed-hal-interface/Serial.h"

#include "util.h"

bool __start_up_gpio() { 
   gpioInitialise();
   std::atexit(gpioTerminate);
   return 0;
}
// TODO: proper location
class __StartUp
{
public:
   static bool __gpio_startup_config;
};

__StartUp::__gpio_startup_config = __start_up_gpio();


// void initialize_platform() {
//     if (gpioInitialise() < 0) exit(EXIT_FAILURE);
// }

// void destroy_platform() {
//     gpioTerminate();
// }

#define __PLATFORM_H__
#endif