/*
 * HDK code
 *
 * Main file, implements:
 *  pid.ino
 *  BNO055.ino
 *  servo.ino
 *  hover_engine_initial.ino
 *  rpm_ramp.ino
 *  optoNCDT_analog_HDK_2.ino
 *
 */

#include <Servo.h>
#include <Wire.h>
//#include <Adafruit_MMA8451.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

unsigned long lastTime = 0;  // time stamp in milliseconds of the previous loop

/********* Declare functions from other files ********/
// pid.ino
void pid_setup();
void pid_loop();

// servo.ino
void set_servo();
void servo_initial_setup();

// hover_engine_initial.ino
void hover_engine_initial_setup();
void start_motors();
void stop_motors();

// optoNCDT_analog_HDK2.ino
void read_optoNCDT_values();

// BNO055.ino
void BNO055_setup();
void BNO055_loop();

// rpm_ramp.ino
void rpm_ramp_loop();


/*
 * Main setup function. 
 * Reset the HDK, initialise sensors and PID and start motors
 */
void setup(){  
  Serial.begin(9600);

  servo_setup();
  hover_engine_initial_setup();
  BNO055_setup();

  //setup_constants(0.2, 0, 0); 
  pid_setup(0.2, 0, 0, 0, 0, 0, 0, 0, 0); // put this in pid.ino

}


/*
 * Main loop function.
 */

void loop() {
  unsigned long now = millis();
  double timeChange = (double)(now - lastTime);
  int firstTime = 0; 

  pid_loop();
  rpm_ramp_loop();
  BNO055_loop();
  read_optoNCDT_values();

  Serial.println(""); // New line for next sample

}

