/*******************LCD函数*******************/
#include "Adafruit_LiquidCrystal.h"
Adafruit_LiquidCrystal lcd(1);

String NULL_TXT = "                ";
void LCD_print(String txt1, String txt2)
{
  lcd.setCursor(0, 0);
  lcd.print("                ");
  lcd.setCursor(0, 1);
  lcd.print("                ");

  lcd.setCursor(0, 0);
  lcd.print(txt1);
  lcd.setCursor(0, 1);
  lcd.print(txt2);

}
/*******************Ultrasonic*******************/
#include <HCSR04.h>

// Initialize sensor that uses digital pins 13 and 12.
const byte triggerPin = 6;
const byte echoPin = 5;
UltraSonicDistanceSensor distanceSensor(triggerPin, echoPin);

int Cursor_position = 0;
int flag = 0;

int relayPin = 4;
int LedPin = 10;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);   // 初始化串口
  while (!lcd.begin(16, 2)) {
    Serial.println("Could not init backpack. Check wiring.");
    delay(50);
  }
  Serial.println("Backpack init'd.");

  pinMode(relayPin, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned long previousMillis = 0; // 上次更新的时间
  const long interval = 500;
  LCD_print("Distance    30", "");
  while (1)
  {
    float distance = distanceSensor.measureDistanceCm();
    String Value = String(distance);
    //如果读取失败则退出本次循环
    if(distance== -1)
        continue;
    // 检查是否应该更新 LCD
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis; // 更新上次更新时间
      //      lcd.setCursor(0, 1);
      //      lcd.print(Value);
      if ((int)distance >= 30)
      {
        lcd.setCursor(9, 0);
        lcd.print(">=");
        digitalWrite(relayPin, LOW);
        digitalWrite(LedPin, LOW);
      }
      else
      {
        lcd.setCursor(9, 0);
        lcd.print("< ");
        digitalWrite(relayPin, HIGH);
        digitalWrite(LedPin, HIGH);
      }
    Serial.println((int)distance);
    }

    delay(100);
  }

}
