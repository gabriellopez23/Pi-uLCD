#include "mbed-hal-interface/Serial.h"

int nana::Serial::baud(int baudrate) {
    this-> baudrate = baudrate;
    if (__PI_UART_INTERFACE == __PI_PIGPIO) {
        if (serClose(_ser) < 0) {
            exit(EXIT_FAILURE);
        }
        if ((_ser = serOpen((char*) this -> location, baudrate, 0)) < 0) {
            exit(__INTERFACE_FATAL_ERROR);
        }
        return __INTERFACE_SUCCESS;
    }
    return __INTERFACE_UNSUPPORTED_INTERFACE;
}

char nana::Serial::getc() {
    if (__PI_UART_INTERFACE == __PI_PIGPIO) {
        return serReadByte(_ser);
    }
}

int nana::Serial::putc(const unsigned char c) {
    if (__PI_UART_INTERFACE == __PI_PIGPIO) {
        return serWriteByte(_ser, c);
    }
    return __INTERFACE_UNSUPPORTED_INTERFACE;
}

bool nana::Serial::readable() {
    if (__PI_UART_INTERFACE == __PI_PIGPIO) {
        return serDataAvailable(_ser);
    }
    return __INTERFACE_UNSUPPORTED_INTERFACE;
}

nana::Serial::Serial(const char* location, int baudrate) {
    this -> location = location;
    if (__PI_UART_INTERFACE == __PI_PIGPIO) { 
        //TODO: confirm this is the sertty
        if ((_ser = serOpen((char*) location, baudrate, 0)) < 0) {
            exit(__INTERFACE_FATAL_ERROR);
        }
    } else {
        exit(__INTERFACE_UNSUPPORTED_INTERFACE);
    }
}

nana::Serial::~Serial() {
    if (__PI_UART_INTERFACE == __PI_PIGPIO) {      
        if (serClose(_ser) < 0) {
            exit(EXIT_FAILURE);
        }
    } else {
        exit(__INTERFACE_UNSUPPORTED_INTERFACE);
    }
}