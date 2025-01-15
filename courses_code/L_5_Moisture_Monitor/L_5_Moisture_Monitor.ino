
/*******************Moisture*******************/
int sensorPin1 = A3;    // select the input pin for the potentiometer
int Pin1Value = 0;  // variable to store the value coming from the sensor
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
  
  pinMode(sensorPin1, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  Pin1Value = analogRead(sensorPin1);
  Serial.print("sensor1 = " );
  Serial.println(Pin1Value);
  String Pin1String = "A3:" + String(Pin1Value) ;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(Pin1String);

  delay(1000);
}
