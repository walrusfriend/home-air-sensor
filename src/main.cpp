#include <Arduino.h>
// библиотеки для работы с OLED экраном Arduino IDE
#include "Wire.h"
#include "Adafruit_GFX.h"
#include "Adafruit_SSD1306.h"
#include <WEMOS_SHT3X.h>

const unsigned char degreeSymbol[] PROGMEM = {
    0b00000000, 0b00000000,
    0b00000111, 0b11100000,
    0b00011110, 0b01111000,
    0b00111000, 0b00011100,
    0b01110000, 0b00001110,
    0b01110000, 0b00001110,
    0b11100000, 0b00000111,
    0b11100000, 0b00000111,
    0b11100000, 0b00000111,
    0b11100000, 0b00000111,
    0b01110000, 0b00001110,
    0b01110000, 0b00001110,
    0b00111000, 0b00011100,
    0b00011110, 0b01111000,
    0b00000111, 0b11100000,
    0b00000000, 0b00000000
};

Adafruit_SSD1306 display(128, 64, &Wire1, 4); // указываем размер экрана в пикселях

SHT3X sht30(0x45);

void draw(const int& temp, const int& hum);

void setup() {
   Wire1.begin(32, 33);

   display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // указываем адрес устройства на шине
   display.clearDisplay();
   display.setTextSize(3, 6); // указываем размер шрифта
   display.setTextColor(SSD1306_WHITE); // указываем цвет надписи
}

void loop() {
   if (sht30.get() == 0)
   {
      draw(sht30.cTemp, sht30.humidity);
   }
   else
   {
      display.setCursor(25, 18);
      display.setTextSize(2, 4);
      display.print("NO DATA");
      display.display();
      display.setTextSize(3, 6);
   }

   delay(500);
}

void draw(const int& temp, const int& hum) {
   /* Prepare the screen */
   display.clearDisplay();

   /* Input data check */
   if (temp > 100 or temp < -100 or hum < 0 or hum > 100) {
      display.setCursor(5, 20);
      display.setTextSize(2, 4);
      display.print("WRONG DATA");
      display.display();
      display.setTextSize(3, 6);
      return;
   }

   /* Draw percent symbol */
   display.setCursor(110, 10);
   display.print("%");

   /* Define position of the temperature and the humidity values
      depended on digits number in the value */
   if (temp < 0) {
      if (temp > -10) {
         display.setCursor(10, 10);
         /* Draw degree symbol */
         display.drawBitmap(50, 5, degreeSymbol, 16, 16, WHITE);
      }
      else {
         display.setCursor(0, 10);
         /* Draw degree symbol */
         display.drawBitmap(55, 5, degreeSymbol, 16, 16, WHITE);
      }
   }
   else {
      /* Draw degree symbol */
      display.drawBitmap(50, 5, degreeSymbol, 16, 16, WHITE);

      if (temp < 10) 
         display.setCursor(28, 10);
      else
         display.setCursor(10, 10);
   }

   display.print(temp);

   if (hum < 10)
      display.setCursor(88, 10);
   else
      display.setCursor(70, 10);

   display.print(hum);
   display.display();
}