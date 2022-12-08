#pragma once

#ifndef __PLATFORM__

#include <stdlib.h>

// #include "mbed-hal-interface/gpio.h"
// #include "mbed-hal-interface/DigitalIn.h"
#include "mbed-hal-interface/DigitalOut.h"
// #include "mbed-hal-interface/Stream.h"
// #include "mbed-hal-interface/BufferedSerial.h"
#include "mbed-hal-interface/Serial.h"

#include "util.h"

// void initialize_platform() {
//     if (gpioInitialise() < 0) exit(EXIT_FAILURE);
// }

// void destroy_platform() {
//     gpioTerminate();
// }

#define __PLATFORM__
#endif