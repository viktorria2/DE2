#include "SSD1306.h"

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

unsigned long startTime = 0;  // Время старта
unsigned long elapsedTime = 0;  // Прошедшее время
bool isRunning = false;  // Флаг для отслеживания состояния

// Инициализация дисплея
void initDisplay() {
  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)) {
    Serial.println(F("Не удалось найти дисплей SSD1306!"));
    for(;;);  // Блокировка программы
  }
  display.display();
  delay(2000);  // Задержка для инициализации
}

// Очистка экрана
void clearDisplay() {
  display.clearDisplay();  // Очистка экрана
  display.display();       // Обновление экрана
}

// Вывод ноты на экран
void printNote(const char* note) {
  clearDisplay();  // Очистка экрана перед выводом новой ноты
  display.setTextSize(2);  // Установка размера текста
  display.setTextColor(SSD1306_WHITE);  // Цвет текста
  display.setCursor(0, 0);  // Установка начальной позиции курсора
  display.print("Note: ");  // Печать текста "Note: "
  display.println(note);    // Печать ноты
  display.display();        // Обновление экрана
}

// Установка позиции курсора
void setCursor(uint8_t x, uint8_t y) {
  display.setCursor(x, y);  // Установка курсора
}

// Инициализация кнопок
void initButtons() {
  pinMode(BUTTON_START_PIN, INPUT_PULLUP);  // Кнопка Start
  pinMode(BUTTON_STOP_PIN, INPUT_PULLUP);   // Кнопка Stop
}

// Получение прошедшего времени в миллисекундах
unsigned long getElapsedTime() {
  if (isRunning) {
    return millis() - startTime;
  }
  return elapsedTime;
}

// Отображение прошедшего времени на экране
void displayElapsedTime(unsigned long elapsedTime) {
  clearDisplay();
  display.setTextSize(2);  
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.print("Time: ");
  display.print(elapsedTime / 1000);  // Переводим миллисекунды в секунды
  display.println(" sec");
  display.display();
}

// Основной цикл программы
void loop() {
  static unsigned long lastButtonPressTime = 0;

  // Проверка нажатия кнопки Start
  if (digitalRead(BUTTON_START_PIN) == LOW && millis() - lastButtonPressTime > 200) {
    lastButtonPressTime = millis();
    if (!isRunning) {
      startTime = millis();  // Сохраняем время старта
      isRunning = true;  // Таймер начал работать
    }
  }

  // Проверка нажатия кнопки Stop
  if (digitalRead(BUTTON_STOP_PIN) == LOW && millis() - lastButtonPressTime > 200) {
    lastButtonPressTime = millis();
    if (isRunning) {
      elapsedTime = millis() - startTime;  // Сохраняем прошедшее время
      isRunning = false;  // Таймер остановлен
    }
  }

  // Отображаем прошедшее время
  unsigned long currentElapsedTime = getElapsedTime();
  displayElapsedTime(currentElapsedTime);  // Показываем прошедшее время
}

