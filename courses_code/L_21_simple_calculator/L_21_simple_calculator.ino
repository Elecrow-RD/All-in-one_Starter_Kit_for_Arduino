//**************
//IR receive demo v1.0
//Connect the IR sent pins to D2 for this demo
//******************************
#include <IRSendRev.h>
//#include <IRSendRevInt.h>

#define IR_PIN 2
/*******************LCD函数*******************/
#include "Adafruit_LiquidCrystal.h"
Adafruit_LiquidCrystal lcd(1);
String num;
String num1;
String num2;
String num3;
int flag1 = 0;
int flag2 = 0;
long value = 0;
void setup() {
  Serial.begin(115200);
  while (!Serial);
  IR.Init(IR_PIN);
  Serial.println("init over");
  while (!lcd.begin(16, 2)) {
    Serial.println("Could not init backpack. Check wiring.");
    delay(50);
  }
  lcd.setCursor(0, 0);
  lcd.print("Equal to:");
  lcd.setCursor(0, 1);
}

void loop() {
  byte dta[10];
  if (IR.IsDta()) {
    byte length = IR.Recv(dta);
    Serial.print("- press -\t");
    switch (dta[8]) {
      case 224: Serial.println("[VOL-]");
        num += '-';
        break;
      case 168: Serial.println("[VOL+]");
        num += '+';
        break;
      case 144: Serial.println("[EQ]");
        num += '=';
        num3 = "Equal to:";
        if (sliceString(num, num1, num2))
        {
          Serial.println("合法数据");
          if (num1.toInt() > 100000000 || num2.toInt() > 100000000 || num1.toInt() < 0 || num2.toInt() < 0)
          {
            Serial.println("不合法数据");
            num = "";
            num3 = "Out of range";
            lcd.setCursor(0, 1);
            lcd.print("               ");
            lcd.setCursor(0, 1);
            lcd.print(num3);
            break;
          }
          if (flag1 )
          {
            value = performOperation(num1.toInt(), num2.toInt(), '+');
            Serial.println("value");
          } else
          {
            value = performOperation(num1.toInt(), num2.toInt(), '-');
            Serial.println("-数据");
          }
          num = "";
          num3 = String(value);
          lcd.setCursor(0, 1);
          lcd.print("               ");
          lcd.setCursor(0, 1);
          lcd.print(num3);
        } else
        {
          num = "";
          num3 = "Error";
          lcd.setCursor(0, 1);
          lcd.print("               ");
          lcd.setCursor(0, 1);
          lcd.print(num3);

        }
        Serial.println("value:");
        Serial.println(value);
        Serial.println();
        Serial.println(num);

        break;
      case 104: Serial.println("[0]");
        num += '0';
        break;
      case 48:  Serial.println("[1]");
        num += '1';
        break;
      case 24:  Serial.println("[2]");
        num += '2';
        break;
      case 122: Serial.println("[3]");
        num += '3';
        break;
      case 16:  Serial.println("[4]");
        num += '4';
        break;
      case 56:  Serial.println("[5]");
        num += '5';
        break;
      case 90:  Serial.println("[6]");
        num += '6';
        break;
      case 66:  Serial.println("[7]");
        num += '7';
        break;
      case 74:  Serial.println("[8]");
        num += '8';
        break;
      case 82:  Serial.println("[9]");
        num += '9';
        break;
    }
    if (num.length() > 14)
    {
      //      num = num.substring(2);
      Serial.println(num.length());
      Serial.println(num.length());
      lcd.setCursor(0, 0);
      lcd.print("                ");
      lcd.setCursor(0, 0);
      lcd.print(num.substring(num.length()-14));
    } else
    {
      Serial.println(num.length());
      lcd.setCursor(0, 0);
      lcd.print("                ");
      lcd.setCursor(0, 0);
      lcd.print(num);
    }

  }
}
// 判断字符串是否包含指定字符的函数
bool containsCharacter(String str, char character) {
  return str.indexOf(character) != -1; // 如果返回值不是 -1，说明包含该字符
}
// 切片函数
int sliceString(String input, String &part1, String &part2) {

  int plusIndex;
  int equalIndex;
  flag1 = containsCharacter(input, '+');
  flag2 = containsCharacter(input, '-');
  if ((flag1 || flag2) && containsCharacter(input, '='))
  {
    if (flag1 == 1)
    {
      plusIndex = input.indexOf('+'); // 查找‘+’的位置
      equalIndex = input.indexOf('='); // 查找‘=’的位置
    } else
    {
      plusIndex = input.indexOf('-'); // 查找‘+’的位置
      equalIndex = input.indexOf('='); // 查找‘=’的位置
    }
  } else
  {
    return 0;
  }
  if (plusIndex != -1) {
    part1 = input.substring(0, plusIndex); // 获取‘+’前的部分
  } else {
    part1 = ""; // 如果没有‘+’，返回空字符串
  }

  if (plusIndex != -1 && equalIndex != -1 && equalIndex > plusIndex) {
    part2 = input.substring(plusIndex + 1, equalIndex); // 获取‘+’和‘=’之间的部分
  } else {
    part2 = ""; // 如果没有有效的部分，返回空字符串
  }
  return 1;
}

// 执行计算
long performOperation(long a, long b, char operation) {
  switch (operation) {
    case '+':
      return a + b;
    case '-':
      return a - b;

    default:
      return a; // 如果操作符不合法，返回原值
  }
}
