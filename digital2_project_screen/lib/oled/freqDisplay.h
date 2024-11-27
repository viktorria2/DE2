#ifndef FREQUENCY_DISPLAY_H
#define FREQUENCY_DISPLAY_H

#include <Arduino.h>
#include <oled.h>

// Структура для состояния дисплея и кнопок
typedef struct {
    U8G2_SSD1306_128X64_NONAME_F_HW_I2C* u8g2;  // Указатель на U8g2-дисплей
    int startBtnPin;
    int stopBtnPin;
    bool isRunning;
    int micPin;  // Пин микрофона
    const char* detectedNote;
} NoteDisplay;

// Функции управления дисплеем
void NoteDisplay_init(NoteDisplay* display, U8G2_SSD1306_128X64_NONAME_F_HW_I2C* u8g2, int startButton, int stopButton, int micPin);
void NoteDisplay_begin(NoteDisplay* display);
void NoteDisplay_update(NoteDisplay* display);
void NoteDisplay_displayNote(NoteDisplay* display);
const char* NoteDisplay_detectNoteFrequency(int micPin);

#endif
