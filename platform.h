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

// TODO: proper location
class __StartUp
{
   public:
      static bool isInit;
   public:
   __StartUp() { 
      printf("[C++ -> uLCD] Starting up Pi GPIO: %d\n", __StartUp::isInit);
      if (!__StartUp::isInit) {
         gpioInitialise();
         std::atexit(gpioTerminate);
      }
   };
};

static const std::atomic<__StartUp> __start_up_gpio;


// void initialize_platform() {
//     if (gpioInitialise() < 0) exit(EXIT_FAILURE);
// }

// void destroy_platform() {
//     gpioTerminate();
// }

#define __PLATFORM_H__
#endif