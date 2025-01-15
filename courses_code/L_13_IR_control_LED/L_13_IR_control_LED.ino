//**************
//IR receive demo v1.0
//Connect the IR sent pins to D2 for this demo
//******************************
#include <IRSendRev.h>
//#include <IRSendRevInt.h>
#include <TimerOne.h>
#define IR_PIN 2

int LedPin = 10;

bool ledState = true; // LED状态
bool timerRunning = false; // 定义一个变量跟踪定时器状态
void setup() {
  Serial.begin(115200);
  while (!Serial);
  IR.Init(IR_PIN);
  Serial.println("init over");


  pinMode(LedPin, OUTPUT);
  Timer1.initialize(1000000); // 1秒
  Timer1.attachInterrupt(toggleLED); // 绑定中断函数
  Timer1.stop();
  timerRunning = false;
//  digitalWrite(LedPin, LOW);
}

void loop() {
  byte dta[10];
  if (IR.IsDta()) {
    byte length = IR.Recv(dta);
    //    for (byte i =0;i<length;i++) {
    //      Serial.print(dta[i]);
    //      Serial.print("\t");
    //    }
    Serial.print("- press -\t");
    switch (dta[8]) {

      case 48:  Serial.println("[1]");
        digitalWrite(LedPin, HIGH);
        if (timerRunning) {
          stopTimer(); // 如果定时器正在运行，则停止它
        }
        break;
      case 24:  Serial.println("[2]");
        if (!timerRunning) {
          startTimer(); 
        } 
        break;
      case 122: Serial.println("[3]");
        digitalWrite(LedPin, LOW);
        if (timerRunning) {
          stopTimer(); // 如果定时器正在运行，则停止它
        }
        break;
   
    }
  }
}

void toggleLED() {
  // 切换LED状态
  ledState = !ledState; // 更新LED状态
  digitalWrite(LedPin, ledState); // 设置LED
}
void stopTimer() {
  Timer1.stop(); // 停止定时器
  timerRunning = false; // 更新状态
}
void startTimer() {
  Timer1.start(); // 启动定时器
  timerRunning = true; // 更新状态
}
