#ifdef M5_CORE2
#include "M5_init.h"

AirQ_GFX lcd;
M5Canvas mainCanvas(&lcd);
StatusView statusView(&lcd, &mainCanvas);

void M5_init()
{
    lcd.begin();
    lcd.setEpdMode(epd_mode_t::epd_fastest);
    // lcd.sleep();

    statusView.begin();
    statusView.load();
}
#endif