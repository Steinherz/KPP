// Program used to test the driving simulator functions on 
// the USB Joystick object on the Arduino Leonardo or 
// Arduino Micro.
//
// Matthew Heironimus
// 2016-05-29   Original version.
//------------------------------------------------------------

#include "Joystick.h"
//Joystick_ Joystick;


Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID,JOYSTICK_TYPE_GAMEPAD,
  7, 0,                  // Button Count, Hat Switch Count
  false, false, false,   // X and Y, but no Z Axis
  false, false, false,   // No Rx, Ry, or Rz
  false, true,           // No rudder or throttle
  false, false, false);  // No accelerator, brake, or steering

const int analogInPin = A0;  // Analog input pin that the potentiometer is attached to
const int analogOutPin = 9; // Analog output pin that the LED is attached to


const int numReadings = 10;
int readings[numReadings];      // the readings from the analog input
int readIndex = 0;              // the index of the current reading
int total = 0;                  // the running total
int average = 0;                // the average



int sensorValue = 0;        // value read from the pot
int senValMin = 10;
int senValMax = 900;
int outputValue = 0;        // value output to the PWM (analog out)

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings[thisReading] = 0;
  }
  Joystick.begin();
  Joystick.setThrottleRange(0, 255);
  
  //pinMode(A0, INPUT_PULLUP);

}

void loop() {
  // put your main code here, to run repeatedly:

  // read the analog in value:
  //sensorValue = analogRead(analogInPin);

  sensorValue =  smooth();


  
  // map it to the range of the analog out:
  if (sensorValue < senValMin) sensorValue = senValMin;
  if (sensorValue > senValMax) sensorValue = senValMax;
  outputValue = map(sensorValue, senValMin, senValMax, 0, 255);

  Joystick.setThrottle(outputValue);
  
  // change the analog out value:
  analogWrite(analogOutPin, outputValue);

  // print the results to the Serial Monitor:

  Serial.print("sensor = ");
  Serial.print(analogRead(analogInPin));
  Serial.print("\t average = ");
  Serial.print(average);
  Serial.print("\t value = ");
  Serial.print(sensorValue);
  Serial.print("\t output = ");
  Serial.println(outputValue);

  // wait 2 milliseconds before the next loop for the analog-to-digital
  // converter to settle after the last reading:
  delay(20);

}

int smooth (){
    // subtract the last reading:
  total = total - readings[readIndex];
  // read from the sensor:
  readings[readIndex] = analogRead(analogInPin);
  // add the reading to the total:
  total = total + readings[readIndex];
  // advance to the next position in the array:
  readIndex = readIndex + 1;

  // if we're at the end of the array...
  if (readIndex >= numReadings) {
    // ...wrap around to the beginning:
    readIndex = 0;
  }

  // calculate the average:
  average = total / numReadings;
  return average;
}



