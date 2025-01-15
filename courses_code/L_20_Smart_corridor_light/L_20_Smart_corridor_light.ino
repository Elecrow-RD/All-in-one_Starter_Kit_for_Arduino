#include <BH1750.h>
#include <Wire.h>
BH1750 lightMeter(0x5c);
#define PIR_PIN A2

int LedPin = 10;
#define SOUND_PIN A1


void setup() {

  Serial.begin(115200);

  // Initialize the I2C bus (BH1750 library doesn't do this automatically)
  Wire.begin();
 
  if (lightMeter.begin(BH1750::CONTINUOUS_HIGH_RES_MODE, 0x5c, &Wire)) {
    Serial.println(F("BH1750 Advanced begin"));
  } else {
    Serial.println(F("Error initialising BH1750"));
  }
  pinMode(PIR_PIN, INPUT);

  pinMode(LedPin, OUTPUT);
  pinMode(SOUND_PIN, INPUT);
}

void loop() {
  if (lightMeter.measurementReady(true)) {
    int lux = lightMeter.readLightLevel();
    Serial.print("[-] Light: [");
    Serial.print(lux);
    Serial.println("] lx");
    if (lux < 100)
    {

      while (1)
      {
        int state = digitalRead(PIR_PIN);
        if ( state == HIGH || digitalRead(SOUND_PIN)) {
          Serial.println("[-] Motion detected!");
          
          digitalWrite(LedPin, HIGH);
          
          delay(10000);
        } else if(state == LOW && digitalRead(SOUND_PIN)==LOW){
          Serial.println("[-] No Motion!");
          
          digitalWrite(LedPin, LOW);         
        }
        lux = lightMeter.readLightLevel();
        if (lux >= 100)
          break;
      }

    } else if (lux >= 100)
    {
      digitalWrite(LedPin, LOW);
    }

  }
  delay(100);
}
