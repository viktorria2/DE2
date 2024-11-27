#ifndef SSD1306_H
#define SSD1306_H

#include <Wire.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
#define OLED_ADDR     0x3C

void initDisplay();
void clearDisplay();
void printNote(const char* note);
void setCursor(uint8_t x, uint8_t y);

#endif
