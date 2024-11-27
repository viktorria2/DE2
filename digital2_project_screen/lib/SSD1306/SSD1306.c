#include "SSD1306.h"

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

unsigned long startTime = 0;  
unsigned long mesuaredTime = 0;  //how much is from the button 'start' was pressed
bool isRunning = false;  // flag for status control

// Array for adding new notes 
#define MAX_NOTES 4
char notes[MAX_NOTES][20];  
int noteIndex = 0;  

// Display initialization
void initDisplay() {
  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)) {
    Serial.println(F("SSD1306 can't be found!"));
    for(;;);  // blocking
  }
  display.display();
  delay(2000);  //
}

// Display clear
void clearLine(uint8_t line) {
  display.fillRect(0, line * 10, SCREEN_WIDTH, 10, SSD1306_BLACK);
}

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
  display.clearDisplay();  
  for (int i = 0; i < MAX_NOTES; i++) {
    if (strlen(notes[i]) > 0) {
      display.setTextSize(2); 
      display.setTextColor(SSD1306_BLUE);  
      display.setCursor(0, i * 10);  
      display.print(notes[i]); 
    }
  }
  display.display();  // display reload
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
  display.setTextSize(1);
  display.setTextColor(SSD1306_SILVER);
  display.setCursor(SCREEN_WIDTH - 60, SCREEN_HEIGHT - 10);  
  display.print(measuredTime / 1000); 
  display.print(" sec");
  display.display();
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
