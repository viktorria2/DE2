#ifndef SSD1306_H
#define SSD1306_H

#include <Wire.h>
#include <U8g2lib.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
//#define OLED_RESET    -1
//#define OLED_ADDR     0x3C
// button pins
#define BUTTON_START_PIN 2
#define BUTTON_STOP_PIN  3

//functions
void initDisplay();
void clearDisplay();
void printNote(const char* note);
void setCursor(uint8_t x, uint8_t y);
void initButtons();
unsigned long getmeasuredTime();
void displaymeasuredTime(unsigned long measuredTime);

#endif
