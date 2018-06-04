#include "deca_device_api.h"
#include "wiringPi.h"

/* Wrapper function to be used by decadriver. Declared in deca_device_api.h */
void deca_sleep(unsigned int time_ms)
{
    delay(time_ms);
}
