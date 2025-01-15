
#include <Wire.h>

#include "MPU6050.h"
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
  // join I2C bus (I2Cdev library doesn't do this automatically)
  Wire.begin();

  // initialize serial communication
  // (38400 chosen because it works as well at 8MHz as it does at 16MHz, but
  // it's really up to you depending on your project)
  Serial.begin(115200);
   Wire.begin();//以主机模式开启总线
   MPU_START();//启动MPU6050   
   GYRO_CONFIG_SET(0);//配置器件角速度倍率
   ACCEL_CONFIG_SET(0);//配置器件加速度倍率
   
  while (!lcd.begin(16, 2)) {
    Serial.println("Could not init backpack. Check wiring.");
    delay(50);
  }
  lcd.setCursor(0, 0);
  lcd.print("ax:");
  lcd.setCursor(8, 0);
  lcd.print("ay:");
  lcd.setCursor(0, 1);
  lcd.print("az:");
}

void loop() {

  Get_Value();
  lcd.setCursor(3, 0);
  lcd.print(val_seven[0]);
  lcd.setCursor(11, 0);
  lcd.print(val_seven[1]);
  lcd.setCursor(3, 1);
  lcd.print(val_seven[2]);
  delay(500);
}
