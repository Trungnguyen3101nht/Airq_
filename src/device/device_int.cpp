#include "device_intit.h"

void device_intit()
{
    Wire.begin(MY_SCL, MY_SDA);
    SENSOR_init();
    More_init();
}