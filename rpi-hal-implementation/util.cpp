#include "includes/util.h"

void wait_us(int us) {
    usleep(us);
}

void wait_ms(int ms) {
    usleep(1000*ms);
}

void wait(int s) {
    usleep(1000*1000*s);
}