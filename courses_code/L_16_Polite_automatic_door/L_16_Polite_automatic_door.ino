#include <Servo.h>
int pos = 0;
Servo myservo;

int buttonPin = 7;

/*******************LCD函数*******************/
#include "Adafruit_LiquidCrystal.h"
Adafruit_LiquidCrystal lcd(1);


void setup() {
  // put your setup code here, to run once:
  pinMode(buttonPin, INPUT);
  myservo.attach(9, 600, 2520);
  Serial.begin(115200);   // 初始化串口
  while (!lcd.begin(16, 2)) {
    Serial.println("Could not init backpack. Check wiring.");
    delay(50);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  if (!digitalRead(buttonPin))
  {
    myservo.write(180);
    lcd.setCursor(0, 0);
    lcd.print("             ");
    lcd.setCursor(0, 0);
    lcd.print("Welcome");
  }
  else
  {
    myservo.write(0);
    lcd.setCursor(0, 0);
    lcd.print("             ");

  }


  delay(100);
}
