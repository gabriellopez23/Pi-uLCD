#pragma once

#ifndef __SERIAL_H__

#include <cstdio>
#include <sys/types.h>
#include <cstddef>
#include <stdlib.h>
#include "includes/interface.h"
#include "pigpio.h"

// port of https://github.com/ARMmbed/mbed-os/blob/master/platform/include/platform/Stream.h
// TODO: initialize the GPIO after gpio.h is done
// TODO: convert in types to pinname and pinmode types acc to pigpio

namespace nana {
    const int DEFAULT_SERIAL_BAUD_RATE = 9600;
    class Serial { //: Stream {
        public:
        Serial(char* location, int baudrate = DEFAULT_SERIAL_BAUD_RATE);
        ~Serial();
        int baud(int baudrate);
        char getc();
        int putc(const unsigned char c);
        bool readable();

        private:
        char* location;
        int baudrate;
        int _ser;
    };
};

#define __SERIAL_H__
#endif