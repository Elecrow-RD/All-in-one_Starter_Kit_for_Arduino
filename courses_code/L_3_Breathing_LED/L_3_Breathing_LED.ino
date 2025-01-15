int LinearPin = A0;
int LedPin = 10;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);   // 初始化串口
  Serial.println("Backpack init'd.");
  pinMode(LedPin, OUTPUT);
  pinMode(LinearPin, INPUT);

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

}
