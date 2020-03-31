int buzzLow = 900;      // Define the Lower Limit alarm Frequency.
int buzzHigh = 2800;    // Define the Upper Limit alarm Frequency.

int pressureLow = 300;  // Define the Lower Limit threshold.
int pressureHigh = 800; // Define the Upper Limit threshold.

int sensorPin[] = {A0, A1, A2, A3, A4, A5};     // Select the input pin for the pressure Sensors.
int indicatorPin[] = {2, 3, 4, 5, 6, 7};        // Select the output pin for the LED Indicators.
int buzzer = 8;         // Select the pin for the Buzzer.
int ledPin = 13;        // Select the pin for the LED.

int sensorValue[] = {0, 0, 0, 0, 0, 0};    // Variable to store the value coming from the sensor.

void setup() {  // put your setup code here, to run once:
  Serial.begin(9600);         // Enable the serial port at 9600 baud.
  for(int n=0; n<6; n=n+1){
    pinMode(indicatorPin[n], OUTPUT);
  }
  pinMode(ledPin, OUTPUT);    // Set the LED Pin to output.
  pinMode(buzzer, OUTPUT);    // Set the Buzzer Pin to output.
  delay(500);
}

void loop() { // This function runs in a continuous loop until reset or power is lost.
  // Run Function to check the pressure.
  checkPressure();

  for(int i=0; i<6; i=i+1){
    // This continuosly evaluates the pressure value
    // and decides what action to take.
      if (sensorValue[i] <= pressureLow) {                                          // If pressure is lower than the definded lower limit,
        Serial.print("Valve ");                                                     // print to serial output,
        Serial.print(i);                                                            // ...
        Serial.println(", Low pressure...");                                        // ...
        tone(buzzer, buzzLow);                                                      // sound alarm,
        digitalWrite(indicatorPin[i], HIGH);                                        // light the LED.
      } else if (sensorValue[i] > pressureLow && sensorValue[i] < pressureHigh) {   // Else If the pressure is in the safe zone,
        Serial.print("Valve ");                                                     // print to serial output,
        Serial.print(i);                                                            // ...
        Serial.println(", pressure is Perfect...");                                 // ...
        noTone(buzzer);                                                             // without alarm,
        digitalWrite(indicatorPin[i], LOW);                                         // turn off LED.
      } else if (sensorValue[i] >= pressureHigh) {                                  // Else If the pressure is higher than the defined upper limit,
        Serial.print("Valve ");                                                     // print to serial output,
        Serial.print(i);                                                            // ...
        Serial.println(", High pressure...");                                       // ...
        tone(buzzer, buzzHigh);                                                     // sound alarm,
        digitalWrite(indicatorPin[i], HIGH);                                        // light LED.
      }
  }
  Serial.println("");
  delay(1000);
}

void checkPressure() {  // Function to read the pressure.
  for(int x=0; x<6; x=x+1){
  sensorValue[x] = analogRead(sensorPin[x]);  // read the value from the sensor.
  }
  