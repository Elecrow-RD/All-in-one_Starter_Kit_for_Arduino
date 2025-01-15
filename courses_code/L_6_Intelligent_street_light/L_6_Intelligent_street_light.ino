/*******************Light*******************/
#include <BH1750.h>
BH1750 lightMeter(0x5c);
float lux;
/*******************LED*******************/
int LedPin = 10;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);   // 初始化串口
  Wire.begin();

  // put your main code here, to run repeatedly:
  if (lightMeter.begin(BH1750::CONTINUOUS_HIGH_RES_MODE, 0x5c, &Wire)) {
    Serial.println(F("BH1750 Advanced begin"));
  } else {
    Serial.println(F("Error initialising BH1750"));
  }
  pinMode(LedPin, OUTPUT);
}

void loop() {


    if (lightMeter.measurementReady(true)) {
      lux = lightMeter.readLightLevel();
      Serial.print("[-] Light: [");
      Serial.print(lux);
      Serial.println("] lx");
    }

    delay(10);
    if (lux <= 100)
      digitalWrite(LedPin, HIGH);
    else
      digitalWrite(LedPin, LOW);
  


}
