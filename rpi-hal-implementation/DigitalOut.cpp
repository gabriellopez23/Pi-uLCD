#include "mbed-hal-interface/DigitalOut.h"

nana::DigitalOut::DigitalOut(int pinname) : pinname(pinname) {
    // gpio init pinname
    if (__PI_UART_INTERFACE == __PI_PIGPIO) {
        gpioSetMode(this -> pinname, PI_OUTPUT);
    } else {
        exit(__INTERFACE_UNSUPPORTED_INTERFACE);
    }
};

nana::DigitalOut::DigitalOut(int pinname, int value) :pinname(pinname) {
    // gpio init pinname, value
    if (__PI_UART_INTERFACE == __PI_PIGPIO) {
        gpioSetMode(this -> pinname, PI_OUTPUT);
        write(value);
    } else {
        exit(__INTERFACE_UNSUPPORTED_INTERFACE);
    }
}

int nana::DigitalOut::read() {
    // return gpio read
    if (__PI_UART_INTERFACE == __PI_PIGPIO) {
        return gpioRead(this -> pinname);
    } 
}


void nana::DigitalOut::write(int value) {
    // gpio write value
    if (__PI_UART_INTERFACE == __PI_PIGPIO) {
        gpioWrite(this -> pinname, value);
    } 
}

int nana::DigitalOut::is_connected()  {
    // return if the gpio is connected
    // not really necessary
    if (__PI_UART_INTERFACE == __PI_PIGPIO) {
        return true;
    } 
}

nana::DigitalOut& nana::DigitalOut::operator=(int value) {
    write(value);
    return *this;
}

nana::DigitalOut& nana::DigitalOut::operator= (nana::DigitalOut &rhs) {
    write(rhs.read());
    return *this;
}

nana::DigitalOut::operator int(){
    return read();
}