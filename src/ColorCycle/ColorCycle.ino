/*
  Arduino Starter Kit example
  Project 4 - Color Mixing Lamp

  This sketch is written to accompany Project 3 in the Arduino Starter Kit

  Parts required:
  - one RGB LED
  - three 10 kilohm resistors
  - three 220 ohm resistors
  - three photoresistors
  - red green and blue colored gels

  created 13 Sep 2012
  modified 14 Nov 2012
  by Scott Fitzgerald
  Thanks to Federico Vanzati for improvements

  http://www.arduino.cc/starterKit

  This example code is part of the public domain.
*/

const int greenLEDPin = 9;    // LED connected to digital pin 9
const int redLEDPin = 11;     // LED connected to digital pin 10
const int blueLEDPin = 10;    // LED connected to digital pin 11

const int redSensorPin = A0;  // pin with the photoresistor with the red gel
const int greenSensorPin = A1;   // pin with the photoresistor with the green gel
const int blueSensorPin = A2;   // pin with the photoresistor with the blue gel

// The LED is non-linear and works well in this range
const int minValue = 512;
const int maxValue = 768;

int redValue = minValue; // value to write to the red LED
int greenValue = minValue; // value to write to the green LED
int blueValue = minValue; // value to write to the blue LED

int redInc = 1;
int greenInc = 2;
int blueInc = 4;

void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);

  // set the digital pins as outputs
  pinMode(greenLEDPin, OUTPUT);
  pinMode(redLEDPin, OUTPUT);
  pinMode(blueLEDPin, OUTPUT);
}

int nextValue(int value, int * inc)
{
  int nextValue = value + *inc;
  if (nextValue >= maxValue || nextValue < minValue)
  {
    *inc = -(*inc);
    nextValue = value + *inc;
    nextValue = value + *inc;
  }

  return nextValue;
}

void loop() {
  redValue = nextValue(redValue, &redInc);
  greenValue = nextValue(greenValue, &greenInc);
  blueValue = nextValue(blueValue, &blueInc);

  // print out the mapped values
  Serial.print("Mapped sensor Values \t red: ");
  Serial.print(redValue);
  Serial.print("\t green: ");
  Serial.print(greenValue);
  Serial.print("\t Blue: ");
  Serial.println(blueValue);

  /*
    Now that you have a usable value, it's time to PWM the LED.
  */
  analogWrite(redLEDPin, redValue);
  analogWrite(greenLEDPin, greenValue);
  analogWrite(blueLEDPin, blueValue);

  delay(10);
}
