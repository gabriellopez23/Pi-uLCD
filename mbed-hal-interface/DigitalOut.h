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
        DigitalOut(int pinname);
        DigitalOut(int pinname, int value);
        // ~DigitalOut() {
        //     // delete gpio object
        // }
        int read();
        void write(int value);
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