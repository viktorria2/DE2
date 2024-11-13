/*
 * Display library for Digital Electronics 2 project named Electronically controlled xylophone.
 * (c) 2024 Viktoriia Shishkova
 *
 * Developed using PlatformIO and AVR 8-bit Toolchain 3.6.2.
 * Tested on Arduino Uno board and ATmega328P, 16 MHz.
 */

#include <Wire.h>
#ifndef display
#define display

// display dimensions
#define OLED_Width 128
#define OLED_Height 64
// I2C address of the OLED display (change if necessary)
#define OLED_I2C_ADDRESS 0x3C

// Define some basic commands for the OLED (common for SSD1306-based displays)
#define OLED_DISPLAY_OFF 0xAE
#define OLED_DISPLAY_ON  0xAF
#define OLED_SET_ADDRESS_MODE 0x20
#define OLED_SET_COLUMN_ADDR  0x21
#define OLED_SET_PAGE_ADDR    0x22

// Function prototypes
void oled_init();
void oled_clear();
void oled_display_on();
void oled_display_off();
void oled_set_cursor(uint8_t x, uint8_t y);
void oled_print_char(char c);
void oled_print(const char* str);

#endif  // 
