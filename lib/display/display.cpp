#include "display.hpp"

extern "C" {
#include "hardware/spi.h"
#include "pico/time.h"
#include "LCD_Driver.h"
#include "LCD_Touch.h"
#include "DEV_Config.h"
}

Display::Display() {
    System_Init();
    init_display();
}

void Display::write_cmd(uint8_t cmd) {
    // gpio_put(LCD_CS, 1);
    // gpio_put(LCD_DC, 0);
    // gpio_put(LCD_CS, 0);

    // uint8_t bytes[] = { cmd };
    // uint8_t rxDat;
    // SPI4W_Write_Byte(cmd);

    // gpio_put(LCD_CS, 1);
}

void Display::write_data(uint16_t buf) {
    // gpio_put(LCD_DC, 1);
    // gpio_put(LCD_DC, 1);
    // gpio_put(LCD_CS, 0);

    // uint8_t rxDat;
    // uint8_t a = buf >> 8;
    // uint8_t b = buf & 0XFF;
    // spi_write_read_blocking(spi1, &a, &rxDat, 1);
    // spi_write_read_blocking(spi1, &b, &rxDat, 1);
    
    // gpio_put(LCD_CS, 1);    
}

void Display::init_display() {
    DEV_Digital_Write(LCD_RST_PIN, 1);
    Driver_Delay_ms(5);
    DEV_Digital_Write(LCD_RST_PIN, 0);
    Driver_Delay_ms(10);
    DEV_Digital_Write(LCD_RST_PIN, 1);
    Driver_Delay_ms(5);
    
    LCD_WriteReg(0x21);

    LCD_WriteReg(0xC2);
    LCD_WriteData(0x33);
    
    LCD_WriteReg(0XC5);
    LCD_WriteData(0x00);
    LCD_WriteData(0x1e);
    LCD_WriteData(0x80);
    
    LCD_WriteReg(0xB1);
    LCD_WriteData(0xB0);
    
    LCD_WriteReg(0XE0);
    LCD_WriteData(0x00);
    LCD_WriteData(0x13);
    LCD_WriteData(0x18);
    LCD_WriteData(0x04);
    LCD_WriteData(0x0F);
    LCD_WriteData(0x06);
    LCD_WriteData(0x3a);
    LCD_WriteData(0x56);
    LCD_WriteData(0x4d);
    LCD_WriteData(0x03);
    LCD_WriteData(0x0a);
    LCD_WriteData(0x06);
    LCD_WriteData(0x30);
    LCD_WriteData(0x3e);
    LCD_WriteData(0x0f);
    
    LCD_WriteReg(0XE1);
    LCD_WriteData(0x00);
    LCD_WriteData(0x13);
    LCD_WriteData(0x18);
    LCD_WriteData(0x01);
    LCD_WriteData(0x11);
    LCD_WriteData(0x06);
    LCD_WriteData(0x38);
    LCD_WriteData(0x34);
    LCD_WriteData(0x4d);
    LCD_WriteData(0x06);
    LCD_WriteData(0x0d);
    LCD_WriteData(0x0b);
    LCD_WriteData(0x31);
    LCD_WriteData(0x37);
    LCD_WriteData(0x0f);
    
    LCD_WriteReg(0X3A);
    LCD_WriteData(0x55);

    LCD_WriteReg(0x11);
    Driver_Delay_ms(120);
    LCD_WriteReg(0x29);
    
    LCD_WriteReg(0xB6);
    LCD_WriteData(0x00);
    LCD_WriteData(0x62);
    
    LCD_WriteReg(0x36);

    LCD_WriteData(0x28);
}

void Display::show_up() {
    LCD_WriteReg(0x2A);
    LCD_WriteData(0x00);
    LCD_WriteData(0x00);
    LCD_WriteData(0x01);
    LCD_WriteData(0xdf);
    
    LCD_WriteReg(0x2B);
    LCD_WriteData(0x00);
    LCD_WriteData(0x00);
    LCD_WriteData(0x00);
    LCD_WriteData(0x9f);

    LCD_WriteReg(0x2C);

    DEV_Digital_Write(LCD_CS_PIN, 1);
    DEV_Digital_Write(LCD_DC_PIN, 1);
    DEV_Digital_Write(LCD_CS_PIN, 0);
    
    // for (int i = 0; i < width*height*2; i+= 2) {
    //     SPI4W_Write_Byte(buffer[i]);
    //     SPI4W_Write_Byte(buffer[i+1]);
    // }
	spi_write_blocking(spi1,buffer,width*height*2);
    
    DEV_Digital_Write(LCD_CS_PIN, 1);
}

void Display::show_down() {
    LCD_WriteReg(0x2A);
    LCD_WriteData(0x00);
    LCD_WriteData(0x00);
    LCD_WriteData(0x01);
    LCD_WriteData(0xdf);
    
    LCD_WriteReg(0x2B);
    LCD_WriteData(0x00);
    LCD_WriteData(0xA0);
    LCD_WriteData(0x01);
    LCD_WriteData(0x3f);

    LCD_WriteReg(0x2C);

    DEV_Digital_Write(LCD_CS_PIN, 1);
    DEV_Digital_Write(LCD_DC_PIN, 1);
    DEV_Digital_Write(LCD_CS_PIN, 0);
    
    // for (int i = 0; i < width*height*2; i+= 2) {
    //     SPI4W_Write_Byte(buffer[i]);
    //     SPI4W_Write_Byte(buffer[i+1]);
    // }

	spi_write_blocking(spi1,buffer,width*height*2);
    
    DEV_Digital_Write(LCD_CS_PIN, 1);
}

// ScreenPos Display::touch_get() {
//     if (DEV_Digital_Read(TP_IRQ_PIN) == 0) {
//         ScreenPos pos;
//         if (TP_Read_TwiceADC(&pos.x, &pos.y)) {
            
//         }

//         DEV_Digital_Write(TP_CS_PIN, 0);

//         int X_Point = 0;
//         int Y_Point = 0;

//         for (int i = 0; i < 3; i++) {
//             SPI4W_Write_Byte(0xD0);

//             uint8_t read_date[2];
//             spi_read_blocking(spi1, LCD_MISO_PIN, read_date, 2);

//             sleep_us(10);

//             X_Point += (((read_date[0]<<8)+read_date[1])>>3);
        
//             SPI4W_Write_Byte(0x90);
//             spi_read_blocking(spi1, LCD_MISO_PIN, read_date, 2);
//             Y_Point += (((read_date[0]<<8)+read_date[1])>>3);
//         }

//         X_Point /= 3;
//         Y_Point /= 3;

//         DEV_Digital_Write(TP_CS_PIN, 1);

//         ScreenPos pos = { X_Point, Y_Point };

//         return pos; 
//     }
// }
