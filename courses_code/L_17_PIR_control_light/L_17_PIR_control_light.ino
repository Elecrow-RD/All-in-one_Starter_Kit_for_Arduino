#define PIR_PIN A2

static int oldState = 0;
int LedPin = 10;
void setup() {
  Serial.begin(115200);
  while(!Serial);
  pinMode(PIR_PIN, INPUT);
  pinMode(LedPin, OUTPUT);
}

void loop() {
  byte state = digitalRead(PIR_PIN);
  if( state && oldState != state ) {
    Serial.println("[-] Motion detected!");
    oldState = state;
    digitalWrite(LedPin, HIGH);
    delay(5000);
  } else if( !state && oldState != state ) {
    Serial.println("[-] No Motion!");
    digitalWrite(LedPin, LOW);
    oldState = state;
  }
  delay(20);
}
