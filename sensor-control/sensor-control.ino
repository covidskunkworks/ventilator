#ifndef DEBUG
#define DEBUG false
#endif

void setup() {
  // put your setup code here, to run once:
#if DEBUG
Serial.begin(9600);
#endif
}

int buzzLow = 900;      // Define the Lower Limit alarm Frequency.
int buzzHigh = 2800;    // Define the Upper Limit alarm Frequency.

int pressureLow = 300;  // Define the Lower Limit threshold.
int pressureHigh = 800; // Define the Upper Limit threshold.

int sensorPin[6] = { A0, A1, A2, A3, A4, A5 };
int buzzer = 8;         // Select the pin for the Buzzer.
int ledPin = 13;        // Select the pin for the LED.
int sensorValue[6];
void loop() {
  // put your main code here, to run repeatedly:
  checkPressure();
  for(int i=0; i<6; i=i+1) {
    #if DEBUG
    Serial.print("analog pin ");
    Serial.print(i);
    Serial.print(": ");
    Serial.println(analogValue);
    #endif
    if (sensorValue <= pressureLow) {
      #if DEBUG
      Serial.print("Pressure Low on pin ");
      Serial.println(i);
      #endif
      tone(buzzer, buzzLow);
      digitalWrite(ledPin, HIGH);
    } else if (sensorValue >= pressureHigh) {
      #if DEBUG
      Serial.print("Pressure Low on pin ");
      Serial.println(i);
      #endif
      tone(buzzer, buzzHigh);
      digitalWrite(ledPin, HIGH);
    } else {
      #if DEBUG
      Serial.print("Pressure OK on pin ");
      Serial.println(i);
      #endif
      notone(buzzer);
      digitalWrite(ledPin, LOW);
    }
    
    delay(1000);
  }

}

void checkPressure() {  // Function to read the pressure.
  for(int x=0; x<6; x=x+1){
  sensorValue[x] = analogRead(sensorPin[x]);  // read the value from the sensor.
  }
}
