#pragma once

#ifndef __PLATFORM_H__
#define EMBEDDED_IN_VM 1
#include <stdlib.h>
#include <stdatomic.h>

// #include "mbed-hal-interface/gpio.h"
// #include "mbed-hal-interface/DigitalIn.h"
#include "mbed-hal-interface/DigitalOut.h"
// #include "mbed-hal-interface/Stream.h"
// #include "mbed-hal-interface/BufferedSerial.h"
#include "mbed-hal-interface/Serial.h"

#include "util.h"

static const std::atomic<bool> __start_up_gpio;

// TODO: proper location
class __StartUp
{
   public:
   __StartUp() { 
      printf("[C++ -> uLCD] Starting up Pi GPIO: %d\n", __start_up_gpio);
      if (!__start_up_gpio) {
         gpioInitialise();
         std::atexit(gpioTerminate);
      }
   };
};



// void initialize_platform() {
//     if (gpioInitialise() < 0) exit(EXIT_FAILURE);
// }

// void destroy_platform() {
//     gpioTerminate();
// }

#define __PLATFORM_H__
#endif