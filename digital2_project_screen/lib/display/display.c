/*
 * Display library for Digital Electronics 2 project named Electronically controlled xylophone.
 * (c) 2024 Viktoriia Shishkova
 *
 * Developed using PlatformIO and AVR 8-bit Toolchain 3.6.2.
 * Tested on Arduino Uno board and ATmega328P, 16 MHz.
 */

#include "display.h"

// Send a command to the OLED
void oled_send_command(uint8_t command) {
    Wire.beginTransmission(OLED_I2C_ADDRESS);
    Wire.write(0x00); // Co = 0, D/C# = 0
    Wire.write(command);
    Wire.endTransmission();
}

// Initialize the OLED display
void oled_init() {
    Wire.begin();
    
    delay(100);  // Wait for the OLED to power up
    
    // Send initialization commands (example commands for SSD1306)
    oled_send_command(OLED_DISPLAY_OFF);
    oled_send_command(0xA8);  // Set Multiplex Ratio
    oled_send_command(0x3F);  // Multiplex ratio for 128x64 (adjust if different)
    oled_send_command(OLED_SET_ADDRESS_MODE);
    oled_send_command(0x00);  // Horizontal Addressing Mode
    oled_send_command(OLED_DISPLAY_ON);
    
    oled_clear();  // Clear the screen
}

// Clear the OLED display
void oled_clear() {
    for (uint8_t page = 0; page < 8; page++) {
        oled_set_cursor(0, page);
        for (uint8_t col = 0; col < OLED_WIDTH; col++) {
            Wire.beginTransmission(OLED_I2C_ADDRESS);
            Wire.write(0x40); // Co = 0, D/C# = 1
            Wire.write(0x00); // Write 0 (clear pixel data)
            Wire.endTransmission();
        }
    }
}

// Turn the display on
void oled_display_on() {
    oled_send_command(OLED_DISPLAY_ON);
}

// Turn the display off
void oled_display_off() {
    oled_send_command(OLED_DISPLAY_OFF);
}

// Set the cursor position (in terms of columns and pages)
void oled_set_cursor(uint8_t x, uint8_t y) {
    oled_send_command(OLED_SET_COLUMN_ADDR);
    oled_send_command(x);
    oled_send_command(OLED_WIDTH - 1);
    
    oled_send_command(OLED_SET_PAGE_ADDR);
    oled_send_command(y);
    oled_send_command(7);
}

// Print a character to the OLED display (implement with font data)
void oled_print_char(char c) {
    // You would typically have a font array here, with each character represented
    // as a set of bytes. For simplicity, we assume a simple font is available.
    // This example is left abstract as font data is complex.
}

// Print a string to the OLED display
void oled_print(const char* str) {
    while (*str) {
        oled_print_char(*str++);
    }
}