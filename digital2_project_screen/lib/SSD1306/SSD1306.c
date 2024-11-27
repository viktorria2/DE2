#include "SSD1306.h"

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

unsigned long startTime = 0;  
unsigned long mesuaredTime = 0;  //how much is from the button 'start' was pressed
bool isRunning = false;  // flag for status control

// Array for adding new notes 
#define MAX_NOTES 4
char notes[MAX_NOTES][20];  
int noteIndex = 0;  

// Display initialization
  u8g2.begin();  
  u8g2.clearBuffer();  
  u8g2.setFont(u8g2_font_ncenB08_tr); 
}

// Display clear
//void clearLine(uint8_t line) {
 // display.fillRect(0, line * 10, SCREEN_WIDTH, 10, SSD1306_BLACK);
//}

// Add note on the display
void addNoteToDisplay(const char* note) {
  // If its on the limit move up
  if (noteIndex >= MAX_NOTES) {
    for (int i = 1; i < MAX_NOTES; i++) {
      strcpy(notes[i - 1], notes[i]);
    }
    noteIndex = MAX_NOTES - 1;  
  }
  strcpy(notes[noteIndex], note);
  
  // Display notes
u8g2.clearBuffer();  
  for (int i = 0; i < MAX_NOTES; i++) {
    if (strlen(notes[i]) > 0) {
      u8g2.drawStr(0, (i + 1) * 10, notes[i]);  
    }
  }
  u8g2.sendBuffer();  // send to display
}

// Buttons
void initButtons() {
  pinMode(BUTTON_START_PIN, INPUT_PULLUP);  
  pinMode(BUTTON_STOP_PIN, INPUT_PULLUP);  
}

// Time since start button pressed calculation
unsigned long getmeasuredTime() {
  if (isRunning) {
    return millis() - startTime;
  }
  return elapsedTime;
}

//  Time since start button pressed on display is shown
void displaymeasuredTime(unsigned long measuredTime) {
  // Position of the time parameter
  u8g2.setCursor(SCREEN_WIDTH - 60, SCREEN_HEIGHT - 10);  
  u8g2.print(measuredTime / 1000);  
  u8g2.print(" sec");
  u8g2.sendBuffer();  
}

// The main loop
void loop() {
  static unsigned long lastButtonPressTime = 0;

  // if the Start is pressed
  if (digitalRead(BUTTON_START_PIN) == LOW && millis() - lastButtonPressTime > 200) {
    lastButtonPressTime = millis();
    if (!isRunning) {
      startTime = millis();  
      isRunning = true;  
    }
    addNoteToDisplay("Note Started");
  }

  // when prss Stop button
  if (digitalRead(BUTTON_STOP_PIN) == LOW && millis() - lastButtonPressTime > 200) {
    lastButtonPressTime = millis();
    if (isRunning) {
      measuredTime = millis() - startTime;  
      isRunning = false;  
    }
    addNoteToDisplay("Note Stopped");
  }

  // Time after Stop is pressed
  unsigned long currentmeasuredTime = getmeasuredTime();
  displaymeasuredTime(currentmeasuredTime);  
}
