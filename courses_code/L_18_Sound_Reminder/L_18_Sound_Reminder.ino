#define SOUND_PIN A1
int buzzerPin = 3;
void setup() {
  Serial.begin(115200);
  while (!Serial);
  pinMode(SOUND_PIN, INPUT);
  pinMode(buzzerPin, OUTPUT);
}

void loop() {
  if (analogRead(SOUND_PIN)>=400 ) {
    Serial.println("[-] Detect Sound!");
    tone(buzzerPin, 1300);
    delay(1000);
    
    while (1)
    {
      if ( analogRead(SOUND_PIN)>=400 )
      {
        //      tone(buzzerPin, 1300);
        Serial.println(analogRead(SOUND_PIN));  
      }
      else
      {
        noTone(buzzerPin);
        break;
      }
    }

  }

}
