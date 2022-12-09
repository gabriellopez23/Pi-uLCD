#pragma once

#ifndef __UTIL_H__

#include <unistd.h>

void wait_us(int us);

void wait_ms(int ms);

void wait(int s);

#define __UTIL_H__
#endif