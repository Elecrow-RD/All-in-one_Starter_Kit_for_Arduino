int buttonPin = 7;
int LedPin = 10;
void setup() {
  // put your setup code here, to run once:
  pinMode(LedPin, OUTPUT);
  pinMode(buttonPin, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (digitalRead(buttonPin))
    digitalWrite(LedPin, LOW);
  else
    digitalWrite(LedPin, HIGH);

  delay(100);
}
