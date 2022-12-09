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
        /** Creates a Serial object with its location and baud rate
         * @param location File location of the serial connection
         * @param baudrate Baud rate of the serial connection: default is 9600
         */
        Serial(const char* location, int baudrate = DEFAULT_SERIAL_BAUD_RATE);

        /**
         * @brief Close serial connection and destroy Serial object
         */
        ~Serial();

        /**
         * @brief Adjust the baud rate of the serial connection
         * 
         * @param baudrate New baud rate for the serial connection
         * @return Success on change, otherwise failure (See 4DGL documentation)
         */
        int baud(int baudrate);

        /**
         * @brief Read a byte from the serial connection
         * 
         * @return Read byte from serial input
         */
        char getc();

        /**
         * @brief Sends a byte to the serial connection
         * 
         * @param c Byte to send
         * @return Success on write, otherwise failure (See 4DGL documentation)
         */
        int putc(const unsigned char c);

        /**
         * @brief Verify if the data line is free
         * 
         * @return true if available
         * @return false if not available
         */
        bool readable();

        private:
        const char* location;
        int baudrate;
        int _ser;
    };
};

#define __SERIAL_H__
#endif