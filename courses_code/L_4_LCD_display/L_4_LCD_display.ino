/*******************LCD函数*******************/
#include "Adafruit_LiquidCrystal.h"
Adafruit_LiquidCrystal lcd(1);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);   // 初始化串口
  while (!lcd.begin(16, 2)) {
    Serial.println("Could not init backpack. Check wiring.");
    delay(50);
  }
  Serial.println("Backpack init'd.");
  lcd.setCursor(0, 0);
  lcd.print("HELLO WORLD");
  delay(1000);
  lcd.setCursor(0, 1);
  lcd.print("Bye Bye");
  delay(1000);
  lcd.clear();
  lcd.setBacklight(0);
}

void loop() {
  // put your main code here, to run repeatedly:

}
