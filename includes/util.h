#pragma once

#ifndef __UTIL_H__

// #include <unistd.h>

void wait_us(int us) {
    return; //usleep(us);
}

void wait_ms(int ms) {
    return; //usleep(1000*ms);
}

void wait(int s) {
    return; //usleep(1000*1000*s);
}

#define __UTIL_H__
#endif