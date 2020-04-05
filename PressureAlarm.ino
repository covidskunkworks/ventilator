int buzzLow = 900;      // Define the Lower Limit alarm Frequency.
int buzzHigh = 2800;    // Define the Upper Limit alarm Frequency.

int pressureLow = 300;  // Define the Lower Limit threshold.
int pressureHigh = 800; // Define the Upper Limit threshold.

//define where your pins are
int latchPin = 11;
int dataPin = 9;
int clockPin = 10;

//hold the data for shift register.
byte switchVar = 0;

int sensorPin[] = {A0, A1, A2, A3, A4, A5};     // Select the input pin for the pressure Sensors.
int indicatorPin[] = {2, 3, 4, 5, 6, 7};        // Select the output pin for the LED Indicators.
int buzzer = 8;         // Select the pin for the Buzzer.

int sensorValue[] = {0, 0, 0, 0, 0, 0};    // Variable to store the value coming from the sensor.

int valvesToMonitor[] = {0, 0, 0, 0, 0, 0};   //valves selected to monitor

void setup() {  // put your setup code here, to run once:
  Serial.begin(9600);         // Enable the serial port at 9600 baud.
  for(int n=0; n<6; n=n+1){  // Set LED pinMode as OUTPUT.
    pinMode(indicatorPin[n], OUTPUT);
  }
  for(int n=0; n<6; n=n+1){  // Set Analog pinMode as INPUT.
    pinMode(sensorPin[n], INPUT);
  }

  pinMode(buzzer, OUTPUT);    // Set the Buzzer Pin to output.

  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, INPUT);
}

int masterToggleBit = 6;
boolean bouncing = false;
int debounceStart = 0;

void loop() { // This function runs in a continuous loop until reset or power is lost.
  
  //choose which valves to monitor
  if (!bouncing) {
    valveChoice();
  } else if ( (millis() - debounceStart) > 500 ) {
    bouncing = false;
  }

  if(bitRead(switchVar, masterToggleBit)){  
    // Run Function to check the pressure.
    checkPressure();
  
    for(int i=0; i<6; i=i+1){
      // This continuosly evaluates the pressure value
      // and decides what action to take.
      if(valvesToMonitor[i] == 1){
        if (sensorValue[i] <= pressureLow) {                                          // If pressure is lower than the definded lower limit,
          Serial.print("Valve ");                                                     // print to serial output,
          Serial.print(i);                                                            // ...
          Serial.println(", Low pressure...");                                        // ...
          tone(buzzer, buzzLow); // sound alarm,
                 
          digitalWrite(indicatorPin[i], LOW); // light the LED.
          delay(150);
          digitalWrite(indicatorPin[i], HIGH); // light LED.
          delay(150);
          
        } else if (sensorValue[i] > pressureLow && sensorValue[i] < pressureHigh) {   // Else If the pressure is in the safe zone,
          Serial.print("Valve ");                                                     // print to serial output,
          Serial.print(i);                                                            // ...
          Serial.println(", pressure is Perfect...");                                 // ...
          noTone(buzzer); // without alarm,
          
          digitalWrite(indicatorPin[i], HIGH);                                         // turn off LED.
          
        } else if (sensorValue[i] >= pressureHigh) {                                  // Else If the pressure is higher than the defined upper limit,
          Serial.print("Valve ");                                                     // print to serial output,
          Serial.print(i);                                                            // ...
          Serial.println(", High pressure...");                                       // ...
          tone(buzzer, buzzHigh);                                                     // sound alarm,
          
          digitalWrite(indicatorPin[i], LOW); // light LED.
          delay(150);
          digitalWrite(indicatorPin[i], HIGH); // light LED.
          delay(150);
          
        }
      }
    }
    Serial.println("");
  }
  
  //delay(1000);
}

void checkPressure() {  // Function to read the pressure.
  for(int x=0; x<6; x=x+1){
  sensorValue[x] = analogRead(sensorPin[x]);  // read the value from the sensor.
  }
}

//function to turn on selected valve
void valveChoice(){
 
  digitalWrite(latchPin,1);   //to collect parallel data
  delayMicroseconds(20);  
  digitalWrite(latchPin,0);   //to transmit data serially

  //read in switch options
  switchVar = readSwitches();

  //turn on led for switch
  //this is where we turn on the valve to monitor
  for(int i = 0; i <= 5; i++){
    if(bitRead(switchVar, i)){
      bouncing = true;
      if(!valvesToMonitor[i]) {
        digitalWrite(indicatorPin[i], HIGH);
        valvesToMonitor[i] = 1;
      } else {
        digitalWrite(indicatorPin[i], LOW);
        valvesToMonitor[i] = 0;
      }
    } // else do nothing.
  }
}
//reads which switches are selected
//returns a byte value to turn on selected
//valves/leds
byte readSwitches() {

  int temp = 0;
  byte switchVal = 0;

  for (int i = 6; i >= 0; i--)
  {
    digitalWrite(clockPin, LOW); 
    delayMicroseconds(0.5);
    temp = digitalRead(dataPin);
    if
    
    
    if (temp) {
      switchVal = switchVal | (1 << i);
    }
       
    digitalWrite(clockPin, HIGH);
    delayMicroseconds(0.5);
  }
  
  return switchVal;
}
