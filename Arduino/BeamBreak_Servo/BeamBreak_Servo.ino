/* 
  IR Breakbeam sensor demo!
*/
#include <Servo.h>


#define SERVO_PIN     2
#define SENSOR_PIN_1  4
#define SENSOR_PIN_2  6

// How many NeoPixels are attached to the Arduino?
#define LED_COUNT  20

// NeoPixel brightness, 0 (min) to 255 (max)
#define BRIGHTNESS 50 // Set BRIGHTNESS to about 1/5 (max = 255)


Servo myservo;

// variables will change:
int sensorState = 0, lastState=0;         // variable for reading the pushbutton status

void setup() {
  // initialize the LED pin as an output:
  pinMode(LED_BUILTIN, OUTPUT);      
  // initialize the sensor pin as an input:
  pinMode(SENSOR_PIN_1, INPUT);     
  pinMode(SENSOR_PIN_2, INPUT);     
  digitalWrite(SENSOR_PIN_1, HIGH); // turn on the pullup
  digitalWrite(SENSOR_PIN_2, HIGH); // turn on the pullup
  
  myservo.attach(SERVO_PIN);
  myservo.write(0);

  Serial.begin(9600);


}

void loop(){

  sensorState = digitalRead(SENSOR_PIN_1) && digitalRead(SENSOR_PIN_2);

  // check if the sensor beam is broken
  // if it is, the sensorState is LOW:
  if (sensorState == LOW) {     
    // turn LED on:
    digitalWrite(LED_BUILTIN, HIGH);  
  } 
  else {
    // turn LED off:
    digitalWrite(LED_BUILTIN, LOW); 
  }
  
  if (sensorState && !lastState) {
    // colorWipe(strip.Color(255,   0,   0)     , 50); // Red
    Serial.println("UNBROKEN");
  } 
  if (!sensorState && lastState) {
    Serial.println("BROKEN");
    myservo.write(45);              // tell servo to go to position in variable 'pos'
    delay(200);    
    myservo.write(0);              // tell servo to go to position in variable 'pos'
  }
  lastState = sensorState;
}
