/*
 * HDK code
 * Uses PID controller to stabilise the HDK
 *
 * PID implemented for yaw using BNO055
 * need pitch and roll via laser distance sensor
 * 
 * 
 */

#include <Servo.h>
#include <Wire.h>
//#include <Adafruit_MMA8451.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>


// variables for PID controller
unsigned long lastTime = 0;  // time stamp in milliseconds of the previous loop



/*
 * Main setup function. 
 * Reset the HDK, initialise sensors and PID and start motors
 */
void setup() {  
  pinMode(pwmPin1, OUTPUT);
  pinMode(pwmPin2, OUTPUT);
  pinMode(pwmPin3, OUTPUT);
  pinMode(pwmPin4, OUTPUT);
  analogWriteFrequency(pwmPin1, 490);
  analogWriteFrequency(pwmPin2, 490);
  analogWriteFrequency(pwmPin3, 490);
  analogWriteFrequency(pwmPin4, 490);
  stop_motors();
  delay(6000);
  start_motors();
  
  myservo1.attach(step1);
  myservo2.attach(step2);
  myservo3.attach(step3);
  myservo4.attach(step4);
  set_servo(90, 70, 90, 100); // TODO ask about this
  //set_servo(90, 90, 90, 90);
  delay(1000);

  Serial.begin(9600);
  Serial.println("Orientation Sensor Test"); Serial.println("");

  /* Initialise the sensor */
  if(!bno.begin())
  {
    /* There was a problem detecting the BNO055 ... check your connections */
    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    while(1);
  }

  delay(1000);

  /* Display some basic information on this sensor */
  displaySensorDetails();

  /* Optional: Display current status */
  displaySensorStatus();

  bno.setExtCrystalUse(true);
  delay(10);
  //setup_constants(0.2, 0, 0);
  setup_constants(0.2, 0, 0, 0, 0, 0, 0, 0, 0);

}



/*
 * Main loop function.
 * Run PID to adjust servos, to stabilise HDK
 */
void loop() {

  unsigned long now = millis();
  double timeChange = (double)(now - lastTime);
  int firstTime = 0; 

 
  /*********** Display the floating point data **********/

  /* Optional: Display calibration status */
  displayCalStatus();

  /* Optional: Display sensor status (debug only) */
  //displaySensorStatus();

  /* New line for the next sample */
  Serial.println("");

  /* Wait the specified delay before requesting next data */
  delay(BNO055_SAMPLERATE_DELAY_MS);
}





