#pragma once

#ifndef __DIGITAL_OUT_H__
#include "interface.h"
#include <stdlib.h>
#include "pigpio.h"

// port of https://github.com/ARMmbed/mbed-os/blob/a3be10c976c36da222517abc0cb4f81e88ff8552/drivers/include/drivers/DigitalOut.h
// TODO: initialize the GPIO after gpio.h is done
// TODO: convert in types to pinname and pinmode types acc to pigpio

//TODO: make sure that return codes are checked
// TODO: make sure that pigpio lib is initialized
namespace nana {
    class DigitalOut {
        // TODO: constructors: init GPIO object?
        public:
        /**
         * @brief Construct a new Digital Out object at a GPIO pin
         * 
         * @param pinname GPIO pin to use
         */
        DigitalOut(int pinname);

        /**
         * @brief Construct a new Digital Out object at a GPIO pin that writes a value when defined
         * 
         * @param pinname GPIO pin to use
         * @param value Value to write on definition
         */
        DigitalOut(int pinname, int value);
        // ~DigitalOut() {
        //     // delete gpio object
        // }

        /**
         * @brief Read input from the GPIO pin
         * 
         * @return Input read from pin
         */
        int read();

        /**
         * @brief Write a value to the GPIO pin
         * 
         * @param value Value to write to pin
         */
        void write(int value);

        /**
         * @brief Verify if the GPIO pin is connected
         * 
         * @return Non-zero number if true, else 0
         */
        int is_connected();

        DigitalOut& operator= (int value);
        DigitalOut& operator= (DigitalOut &rhs);
        operator int();

        private:
        int pinname;
    };
};

#define __DIGITAL_OUT_H__
#endif