/*******************DHT20*******************/
#include "DHT20.h"
DHT20 DHT(&Wire);

uint8_t count_DHT20 = 0;
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
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);   // 初始化串口
  while (!lcd.begin(16, 2)) {
    Serial.println("Could not init backpack. Check wiring.");
    delay(50);
  }
  Serial.println("Backpack init'd.");
  Wire.begin();
  DHT.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  LCD_print("Tem:", "Hum:");
  while (1)
  {
    if (millis() - DHT.lastRead() >= 1000) {
      //  READ DATA
      uint32_t start = micros();
      int status = DHT.read();
      uint32_t stop = micros();

      if ((count_DHT20 % 10) == 0) {
        count_DHT20 = 0;
        Serial.println();
        Serial.println("Type\tHumidity (%)\tTemp (°C)");
        //\tTime (µs)\tStatus
      }
      count_DHT20++;

      Serial.print("DHT20 \t");
      //  DISPLAY DATA, sensor has only one decimal.
      Serial.print(DHT.getHumidity(), 1);
      Serial.print("\t");
      Serial.print(DHT.getTemperature(), 1);

      Serial.print("\n");

      String TemValue = "Tem:" + String(DHT.getTemperature()) + " C";
      String HumValue = "Hum:" + String(DHT.getHumidity()) + " %";

      lcd.setCursor(4, 0);
      lcd.print(String(DHT.getHumidity())+ " C");
      lcd.setCursor(4, 1);
      lcd.print(String(DHT.getTemperature())+ " %");
    }

    delay(10);

  }
}
