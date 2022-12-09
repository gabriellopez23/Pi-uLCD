#include "platform.h"

bool __start_up_gpio() { 
   gpioInitialise();
   std::atexit(gpioTerminate);
   return 0;
}
bool __StartUp::__gpio_startup_config = __start_up_gpio();