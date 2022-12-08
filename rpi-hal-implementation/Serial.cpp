#include "mbed-hal-interface/Serial.h"

int nana::Serial::baud(int baudrate) {
    this-> baudrate = baudrate;
    if (__PI_UART_INTERFACE == __PI_PIGPIO) {
        return __INTERFACE_ACCEPTABLE_UNSUPPORTED_OPERATION;
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

nana::Serial::Serial(char* location, int baudrate = nana::DEFAULT_SERIAL_BAUD_RATE) {
    if (__PI_UART_INTERFACE == __PI_PIGPIO) { 
        //TODO: confirm this is the sertty
        if ((_ser = serOpen(location, baudrate, 0)) < 0) {
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