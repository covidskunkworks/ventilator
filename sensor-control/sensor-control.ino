#ifndef DEBUG
#define DEBUG false
#endif

void setup() {
  // put your setup code here, to run once:
#if DEBUG
Serial.begin(9600);
#endif
}

int analogPins[6] = { A0, A1, A2, A3, A4, A5 };
int currentPin = 0;
int analogValue;
void loop() {
  // put your main code here, to run repeatedly:
  analogValue = analogRead(analogPins[currentPin]);
  #if DEBUG
  Serial.print("analog pin ");
  Serial.print(currentPin);
  Serial.print(": ");
  Serial.println(analogValue);
  if (currentPin == 5) { delay(1000); }
  #endif

  // increment current pin and reset to 0 when it reaches 6.
  currentPin = (currentPin + 1) % 6;
}
