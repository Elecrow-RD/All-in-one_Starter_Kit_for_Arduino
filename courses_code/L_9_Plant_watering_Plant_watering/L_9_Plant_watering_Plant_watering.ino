/*******************Moisture*******************/
int sensorPin1 = A3;    // select the input pin for the potentiometer
int Pin1Value = 0;  // variable to store the value coming from the sensor
int mappedValue;
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
/*******************Buzzer*******************/
int buzzerPin = 3;

/*******************LED*******************/
int LedPin = 10;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);   // 初始化串口
  while (!lcd.begin(16, 2)) {
    Serial.println("Could not init backpack. Check wiring.");
    delay(50);
  }
  Serial.println("Backpack init'd.");
  pinMode(sensorPin1, INPUT);

  pinMode(buzzerPin, OUTPUT);
  LCD_print("Soil moisture", "");
}

void loop() {
  // put your main code here, to run repeatedly:
  Pin1Value = analogRead(sensorPin1);
  Serial.print("sensor1 = " );
  Serial.println(Pin1Value);
  mappedValue = map(Pin1Value, 0, 1023, 0, 100);


  String Value = String(mappedValue) + "%";
  lcd.setCursor(0, 1);
  lcd.print("    ");
  lcd.setCursor(0, 1);
  lcd.print(Value);
  delay(500);

  if (mappedValue < 10)
  {
    tone(buzzerPin, 1300);
    delay(250);
    noTone(buzzerPin);
  } else if (mappedValue >= 10 && mappedValue < 20)
  {
    digitalWrite(LedPin, HIGH);
    delay(100);
    digitalWrite(LedPin, LOW);
  } else if (mappedValue >= 20)
  {
    digitalWrite(LedPin, HIGH);
  }

}
