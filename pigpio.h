#define __GPIO_WIN_INSIGHTS_DEBUGGING 1

#if __GPIO_WIN_INSIGHTS_DEBUGGING == 1
const int PI_OUTPUT = 0;
void gpioSetMode(int, int);
int gpioRead(int);
void gpioWrite(int, int);

int serReadByte(int);
int serWriteByte(int, int);
int serDataAvailable(int);
int serOpen(char*, int, int);
int serClose(int);
#endif