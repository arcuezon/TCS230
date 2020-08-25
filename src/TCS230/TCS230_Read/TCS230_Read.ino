#include <MD_TCS230.h>
#include <FreqCount.h>
#include "ColorMatch.h"

// Pin definitions
//S0, S1, LED to pins 2, 3, 4 (No particular order)
//Output pin to Arduino pin 5
#define S2_OUT 11 //S2 pin
#define S3_OUT 12 //S3 pin
#define OE_OUT 8  // LOW = ENABLED (Not used)

//Color Sensor Object
MD_TCS230 CS(S2_OUT, S3_OUT, OE_OUT);

// Global variables
colorData rgb;
bool writeToPort = false; //True to interface with processing

void setup()
{
  Serial.begin(57600);

  for (int i = 2; i <= 4; i++) //Pins for s0, s1, LED
  {
    pinMode(i, OUTPUT);
    digitalWrite(i, HIGH);
  }

  // initialise color sensor
  CS.begin();
  CS.setDarkCal(&sdBlack); //Retrive calibrations from header
  CS.setWhiteCal(&sdWhite);
}

void loop()
{
  CS.read();
  CS.getRGB(&rgb);
  while (!CS.available())
  {
    delay(200);
  }

  if (writeToPort)
  {
    Serial.write('H');
    Serial.write(rgb.value[TCS230_RGB_R]);
    Serial.write(rgb.value[TCS230_RGB_G]);
    Serial.write(rgb.value[TCS230_RGB_B]);
  }
  else
  {
    Serial.print("Red: ");
    Serial.print(rgb.value[TCS230_RGB_R]);
    Serial.print(" Green: ");
    Serial.print(rgb.value[TCS230_RGB_G]);
    Serial.print(" Blue: ");
    Serial.println(rgb.value[TCS230_RGB_B]); 
  }

  delay(200);
}
