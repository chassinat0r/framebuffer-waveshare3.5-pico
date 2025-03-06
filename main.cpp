#include <iostream>
#include <stdio.h>

extern "C" {
#include "pico/cyw43_arch.h"
#include "pico/stdlib.h"
#include "pico/time.h"
#include "LCD_GUI.h"
}

#include "display.hpp"

char ssid[] = "SSID_HERE";
char pass[] = "PASSWORD_HERE";

COLOR to_rgb565(int R, int G, int B){
    return (((G&0b00011100)<<3) +((B&0b11111000)>>3)<<8) + (R&0b11111000)+((G&0b11100000)>>5);
}

COLOR colours[14] = { WHITE, BLACK, BLUE, BRED, GRED, GBLUE, RED, MAGENTA, GREEN, CYAN, YELLOW, BROWN, BRRED, GRAY };

const int FPS = 30;
const float frame_delay = 1000 / FPS;

int frame_start = 0;
int frame_time = 0;

uint32_t get_ms_since_boot() {
    absolute_time_t t = get_absolute_time();

    return to_ms_since_boot(t);

}
int main() {

    stdio_init_all();

    // bool connected = false;

    // int rc = cyw43_arch_init_with_country(CYW43_COUNTRY_UK);
    // if (!rc) {
    //     cyw43_arch_enable_sta_mode();

    //     if (!cyw43_arch_wifi_connect_timeout_ms(ssid, pass, CYW43_AUTH_WPA2_AES_PSK, 10000)) {
    //         connected = true;
    //     }
    // }

    int c = 0;

    Display display;
    display.fill(0x0000);
    // display.fill_rect(10, 10, 80, 80, 0x07E0);
    display.show_up();
    display.show_down();

    float timer = 0;

    while (true) {
        frame_start = get_ms_since_boot();

        display.fill(0x0000);
        // if (connected) {
        //     display.text("Connected", 0, 0, WHITE);
        // } else {
        //     display.text("No connection", 0, 0, WHITE);

        // }
        display.fill_rect(10, 10, 100, 100, colours[c]);

        display.show_up();
        
        frame_time = get_ms_since_boot() - frame_start;

        if (frame_delay > frame_time) {
            sleep_ms(frame_delay - frame_time);
        }

        timer += frame_delay;

        if (timer > 1000) {
            c++;
            if (c > 13) {
                c = 0;
            }
            timer = 0;
        }
    }
    return 0;
}
