#include <Adafruit_NeoPixel.h>

// 0 = GHOST
// 1 = FUTURE
// 2 = GIANT
#define BOX_ID      2
#define BOX_LEN     3

// Hardware Setup
#define LED_PIN     2
#define SENSOR_PIN  4


// NeoPixel brightness, 0 (min) to 255 (max)
#define BRIGHTNESS 55

int ledCount[BOX_LEN] =
  {
    14, // GHOST
    20, // FUTURE
    28  // GIANT
  };

uint8_t mainColorR[BOX_LEN] = 
  {
    66, // GHOST
    20, // FUTURE
    139 // GIANT
  };
uint8_t mainColorG[BOX_LEN] = 
  {
    153, // GHOST
    235, // FUTURE
    235  // GIANT
  };
uint8_t mainColorB[BOX_LEN] = 
  {
    235, // GHOST
    20, // FUTURE
    115  // GIANT
  };

Adafruit_NeoPixel strip(ledCount[BOX_ID], LED_PIN, NEO_GRB + NEO_KHZ800);


// variables will change:
int sensorState = 0, lastState=0;         // variable for reading the pushbutton status

void setup() {
  // initialize the LED pin as an output:
  pinMode(LED_BUILTIN, OUTPUT);      
  // initialize the sensor pin as an input:
  pinMode(SENSOR_PIN, INPUT);     
  digitalWrite(SENSOR_PIN, HIGH); // turn on the pullup

  Serial.begin(9600);


  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(BRIGHTNESS);

}

void loop(){
  // read the state of the sensor:
  sensorState = digitalRead(SENSOR_PIN);

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
  
  // BEAM IS NOW UNBROKEN
  if (sensorState && !lastState) {
    Serial.println("UNBROKEN");
    for(int p = 0; p < strip.numPixels(); p++)
    {
      strip.setPixelColor(p, strip.Color(0,0,0));  
    }
    strip.show();
  } 
  // BEAM IS NOW BROKEN
  if (!sensorState && lastState) {
    Serial.println("BROKEN");
    switch (BOX_ID) {
      case 0: // GHOST
        ColorFadeUpDown(mainColorR[BOX_ID],mainColorG[BOX_ID],mainColorB[BOX_ID],3,150);
        ColorFadeUpDown(mainColorR[BOX_ID],mainColorG[BOX_ID],mainColorB[BOX_ID],3,150);
        ColorFadeUpDown(mainColorR[BOX_ID],mainColorG[BOX_ID],mainColorB[BOX_ID],6,450);
        break;
      case 1: // FUTURE
        ColorFadeUpDown(mainColorR[BOX_ID],mainColorG[BOX_ID],mainColorB[BOX_ID],1,50);
        ColorFadeUpDown(mainColorR[BOX_ID],mainColorG[BOX_ID],mainColorB[BOX_ID],1,50);
        ColorFadeUpDown(mainColorR[BOX_ID],mainColorG[BOX_ID],mainColorB[BOX_ID],6,450);
        break;
      case 2: // GIANT
        strip.fill(strip.Color(240, 20, 20), 0, 7);
        strip.show();
        delay(600);
        strip.fill(strip.Color(220,155,  0),7, 7);
        strip.show();
        delay(600);
        strip.fill(strip.Color( 20,255, 80),14, 7);
        strip.show();
        delay(600);
        strip.fill(strip.Color(  0,255,  0),21, 7);
        strip.show();
        delay(600);
        ColorFadeUpDown(mainColorR[BOX_ID],mainColorG[BOX_ID],mainColorB[BOX_ID],6,450);
        break;
    }
    delay(5000);
  }
  lastState = sensorState;
}

void ColorFadeUpDown (uint8_t colorR, uint8_t colorG, uint8_t colorB, int stepDelay, int middleHold)
{
  uint32_t c;
  for (int i = 0; i < 255; i++)
  {
    float f = (float)i/255;
    c = strip.Color(f*colorR,f*colorG,f*colorB);
    for(int p = 0; p < strip.numPixels(); p++)
    {
      strip.setPixelColor(p, c);  
    }
    strip.show();
    delay(stepDelay);
  }
  delay(middleHold);
  for (int i = 255; i >= 0; i--)
  {
    float f = (float)i/255;
    c = strip.Color(f*colorR,f*colorG,f*colorB);
    for(int p = 0; p < strip.numPixels(); p++)
    {
      strip.setPixelColor(p, c);  
    }
    strip.show();
    delay(stepDelay);
  }
}

void colorWipe(uint32_t color, int wait) {
  for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
    strip.setPixelColor(i, color);         //  Set pixel's color (in RAM)
    strip.show();                          //  Update strip to match
    delay(wait);                           //  Pause for a moment
  }
}