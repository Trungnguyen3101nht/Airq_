#ifndef M5_INIT_H
#define M5_INIT_H

#include "globals.h"

class AirQ_GFX : public lgfx::LGFX_Device
{
    lgfx::Panel_GDEW0154D67 _panel_instance;
    lgfx::Bus_SPI _spi_bus_instance;

public:
    AirQ_GFX(void)
    {
        {
            auto cfg = _spi_bus_instance.config();

            cfg.pin_mosi = EPD_MOSI;
            cfg.pin_miso = EPD_MISO;
            cfg.pin_sclk = EPD_SCLK;
            cfg.pin_dc = EPD_DC;
            cfg.freq_write = EPD_FREQ;

            _spi_bus_instance.config(cfg);
            _panel_instance.setBus(&_spi_bus_instance);
        }
        {
            auto cfg = _panel_instance.config();

            cfg.invert = false;
            cfg.pin_cs = EPD_CS;
            cfg.pin_rst = EPD_RST;
            cfg.pin_busy = EPD_BUSY;
            cfg.panel_width = 200;
            cfg.panel_height = 200;
            cfg.offset_x = 0;
            cfg.offset_y = 0;

            _panel_instance.config(cfg);
        }
        setPanel(&_panel_instance);
    }
    bool begin(void) { return init_impl(true, false); };
};

void M5_init();
extern StatusView statusView;
extern AirQ_GFX lcd;
#endif
