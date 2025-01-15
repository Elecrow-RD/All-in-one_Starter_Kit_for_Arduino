//**************
//IR receive demo v1.0
//Connect the IR sent pins to D2 for this demo
//******************************
#include <IRSendRev.h>
//#include <IRSendRevInt.h>

#define IR_PIN 2

#include <Servo.h>
int pos = 0;
Servo myservo;

/*******************LCD函数*******************/
#include "Adafruit_LiquidCrystal.h"
Adafruit_LiquidCrystal lcd(1);


int value = 0;

int i = 0;
unsigned long previousMillis = 0;  // 上次更新的时间
const long interval = 10;  // LED闪烁间隔（毫秒）
String num;
String num1;
void setup() {
  Serial.begin(115200);   // 初始化串口
  while (!lcd.begin(16, 2)) {
    Serial.println("Could not init backpack. Check wiring.");
    delay(50);
  }
  Serial.println("Backpack init'd.");
  IR.Init(IR_PIN);
  Serial.println("init over");
  //  myservo.attach(9, 600, 2520);
  //  myservo.write(180);

  num1 = "Angle:";
  lcd.setCursor(0, 0);
  lcd.print(num1);
}

void loop() {



  byte dta[10];
  if (IR.IsDta()) {
    byte length = IR.Recv(dta);
    //    //    for (byte i =0;i<length;i++) {
    //    //      Serial.print(dta[i]);
    //    //      Serial.print("\t");
    //    //    }
    Serial.print("- press -\t");
    switch (dta[8]) {
      case 2:   Serial.println("[NEXT]");
        myservo.attach(9, 600, 2520);
        myservo.write(180);
        lcd.setCursor(0, 0);
        lcd.print("             ");
        lcd.setCursor(0, 0);
        lcd.print("Servo Open");
        break;
      case 194: Serial.println("[PLAY/PAUSE]");
        myservo.detach();
        lcd.setCursor(0, 0);
        lcd.print("             ");
        lcd.setCursor(0, 0);
        lcd.print("Servo Close");
        break;
      case 144: Serial.println("[EQ]");
        if (num.toInt() >= 0 && num.toInt() <= 180)
        {
          Serial.println(num);
          num1 = "Angle:";
          myservo.write(num.toInt());
          num = "";
          value = myservo.read();
          num1 += String(value);
          lcd.setCursor(0, 0);
          lcd.print("             ");
          lcd.setCursor(0, 0);
          lcd.print(num1);
          break;
        }
        else
        {
          num1 = "Angle:";
          num1 += "Error";
          num = "";
          lcd.setCursor(0, 0);
          lcd.print("             ");
          lcd.setCursor(0, 0);
          lcd.print(num1);
          break;
        }

      case 104: Serial.println("[0]");
        num = num + '0';
        break;
      case 48:  Serial.println("[1]");
        num = num + '1';
        break;
      case 24:  Serial.println("[2]");
        num = num + '2';
        break;
      case 122: Serial.println("[3]");
        num = num + '3';
        break;
      case 16:  Serial.println("[4]");
        num = num + '4';
        break;
      case 56:  Serial.println("[5]");
        num = num + '5';
        break;
      case 90:  Serial.println("[6]");
        num = num + '6';
        break;
      case 66:  Serial.println("[7]");
        num = num + '7';
        break;
      case 74:  Serial.println("[8]");
        num = num + '8';
        break;
      case 82:  Serial.println("[9]");
        num = num + '9';
        break;
    }
    lcd.setCursor(0, 1);
    lcd.print("                ");
    lcd.setCursor(0, 1);
    lcd.print(num);
  }
  delay(100);
}
