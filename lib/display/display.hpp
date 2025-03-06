#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include "framebuf.hpp"
extern "C" {
#include "pico/time.h"
#include "hardware/spi.h"
#include "pico/stdlib.h"
}

#define LCD_DC 8
#define LCD_CS 9
#define LCD_SCK 10
#define LCD_CLK 10
#define LCD_MOSI 11
#define LCD_MISO 12
#define LCD_BL 13
#define LCD_RST 15
#define TP_CS 16
#define TP_IRQ 17

struct ScreenPos {
  int x;
  int y;
};

class Display : public FrameBuffer {
    public:
        Display();

        void write_cmd(uint8_t cmd);
        void write_data(uint16_t buf);
        void init_display();
        void show_up();
        void show_down();

        // ScreenPos touch_get();
        
    private:
        int rotate = 90;
};


#endif
