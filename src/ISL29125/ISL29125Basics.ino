#include <Wire.h>
#include "SparkFunISL29125.h"

// Declare sensor object
SFE_ISL29125 RGB_sensor;

//Calibration Values
int redHi = 1476;
int redLo = 141;
int greenHi = 2551;
int greenLo = 294;
int blueHi = 2578;
int blueLo = 288;

bool writeToPort = false; //Write to port for processing 3 interfacing
int count = 0;

void setup()
{
  // Initialize serial communication
  Serial.begin(57600);

  // Initialize the ISL29125 with simple configuration so it starts sampling
  if (RGB_sensor.init())
  {
    Serial.println("Sensor Initialization Successful\n\r");
  }

  if (sensorReset()) Serial.println("Config Success");
}

bool sensorReset()
{
  bool resetStatus = RGB_sensor.reset();
  return resetStatus && (RGB_sensor.config(CFG1_MODE_RGB | CFG1_10KLUX, CFG2_IR_ADJUST_LOW | CFG2_IR_OFFSET_OFF, CFG_DEFAULT));
}

void loop()
{
  // Read sensor values (16 bit integers)
  unsigned int red = RGB_sensor.readRed();
  unsigned int green = RGB_sensor.readGreen();
  unsigned int blue = RGB_sensor.readBlue();

  int redV = constrain(map(red, redLo, redHi, 0, 255), 0, 255);
  int greenV = constrain(map(green, greenLo, greenHi, 0, 255), 0, 255);
  int blueV = constrain(map(blue, blueLo, blueHi, 0, 255), 0, 255);

  int boutFlag = (RGB_sensor.readStatus() & FLAG_BROWNOUT); //Check flag register
  if (boutFlag == 4) //Catch flag
  {
    Serial.print("Brownout flag. ");
    if(sensorReset()) Serial.println("Sensor Reset");
    Serial.println();
    delay(500);
  }

  //Else, display RGB
  else if (writeToPort)
  {
    Serial.write('H');
    Serial.write(redV);
    Serial.write(greenV);
    Serial.write(blueV);
  }
  else
  {
    Serial.print("Red: "); Serial.println(redV, DEC);
    Serial.print("Green: "); Serial.println(greenV, DEC);
    Serial.print("Blue: "); Serial.println(blueV, DEC);
    Serial.println();
  }


  delay(1000);
}
