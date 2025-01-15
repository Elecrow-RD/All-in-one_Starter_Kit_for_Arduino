int LinearPin = A0;
int LedPin = 10;
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
  pinMode(LedPin, OUTPUT);
  pinMode(LinearPin, INPUT);
  lcd.setCursor(0, 0);
  lcd.print("Brightness check");
}

void loop() {
  // put your main code here, to run repeatedly:
  int adcValue;
  int mappedValue;
  adcValue = analogRead(LinearPin); // 读取ADC值
  mappedValue = map(adcValue, 0, 1023, 0, 255);
  analogWrite(LedPin, mappedValue); // 设置 PWM 占空比
  mappedValue = map(adcValue, 0, 1023, 0, 10);

  String Value = String(mappedValue) ;

  delay(100); // 延时以观察变化
  lcd.setCursor(0, 1);
  lcd.print("    ");
  lcd.setCursor(0, 1);
  lcd.print(Value);
}
