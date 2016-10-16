extern "C" {
#include "LaserOrientation.h"
}
/*
 * HDK code
 * Uses PID controller to stabilise the HDK
 */
#include <Servo.h>
#include <Wire.h>
//#include <Adafruit_MMA8451.h>
#include <Adafruit_Sensor.h>

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>




//Adafruit_MMA8451 mma = Adafruit_MMA8451();
#define BNO055_SAMPLERATE_DELAY_MS (20)

// bno055 orientation sensor
Adafruit_BNO055 bno = Adafruit_BNO055(55);

int sensorPin1 = A2;
int sensorPin4 = A0;
int sensorPin5 = A1;

int sensorValue = 0;
// float distance_measured = 0;

//Global Variables
float Laser1Reading;
float Laser2Reading;
float Laser3Reading;

//void RecalcOrientation();


/*
 * Function for setting the servos including a calibration value
 * Parameters match the hover engine/servo number on the HDK 
 * e.g. 1 - servo 1, 2 - servo 2 etc
 */

/*
 * Main setup function. 
 * Reset the HDK, initialise sensors and PID and start motors
 */
void setup() {  
  Serial.begin(9600);
  delay(1000);

  read_optoNCDT_values();

  /* Initialise the sensor */
  if(!bno.begin())
  {
    /* There was a problem detecting the BNO055 ... check your connections */
    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    while(1);
  }

  delay(1000);


  bno.setExtCrystalUse(true);
  delay(10);

//  Serial.println("BNO_Pitch,BNO_Roll,Laser_Pitch,Laser_Roll,");

}


/*
 * Main loop function.
 * Run PID to adjust servos, to stabilise HDK
 */
void loop() {
   read_optoNCDT_values();
  
  /* Get a new sensor event */
  sensors_event_t event;
  bno.getEvent(&event);

  /* Board layout:
         +----------+
         |         *| RST   ROLL  PITCH  HEADING-90 ***
     ADR |*        *| SCL
     INT |*        *| SDA     ^            /->
     PS1 |*        *| GND     |            |
     PS0 |*        *| 3VO     Y    Z-->    \-X
         |         *| VIN
         +----------+
  *** Values switched due to mounted orientation of BNO055 
  
  */

  /* The processing sketch expects data as roll, pitch, heading */
  // Serial.print(F("Orientation: "));
  Serial.print((float)-event.orientation.z);
  Serial.print(",");
  Serial.print((float)event.orientation.y);
  Serial.print(",");
  Serial.println("");



  delay(BNO055_SAMPLERATE_DELAY_MS);
}

float convert(){
  return  ( 50*((double)(sensorValue-200)/800)) + 35;  
}

/* Takes a reading from each laser distance sensor */
void read_optoNCDT_values() {
  sensorValue = analogRead(sensorPin1);
//   Serial.print("LaserPin1: ");

  Laser1Reading = convert();
   Serial.print(Laser1Reading);
   Serial.print(",");

  sensorValue = analogRead(sensorPin4);
//   Serial.print("LaserPin4: ");
  
  Laser2Reading = convert();
   Serial.print(Laser2Reading);
   Serial.print(",");

  sensorValue = analogRead(sensorPin5);
//   Serial.print("LaserPin5: ");
  
  Laser3Reading = convert();;
   Serial.print(Laser3Reading);
   Serial.print(",");

  calculateOrientation();
}

void calculateOrientation() {
  RecalcOrientation();
//    Serial.printf("HE1 Height: %f\n", HE1HeightAboveTrack);
//    Serial.printf("HE2 Height: %f\n", HE2HeightAboveTrack);
//    Serial.printf("HE3 Height: %f\n", HE3HeightAboveTrack);
//    Serial.printf("HE4 Height: %f\n", HE4HeightAboveTrack);
//    
//    
  // Serial.printf("Pitch: %f", Pitch);
 Serial.print(Pitch-90);
  Serial.print(",");
  
  // Serial.printf("Roll: %f", Roll);
 Serial.print(Roll-90);
  Serial.print(",");
   
//   PrintPlane();
}


