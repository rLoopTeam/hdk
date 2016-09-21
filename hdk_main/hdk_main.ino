/*
 * HDK code
 *
 * Main file, implements:
 *  pid.ino
 *  BNO055.ino
 *  servo.ino
 *  hover_engine_initial.ino
 *  optoNCDT_analog_HDK_2.ino
 *  rpm_ramp.ino
 *  pitch_and_roll.ino
 */

#include <Servo.h>
#include <Wire.h>
//#include <Adafruit_MMA8451.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

unsigned long lastTime = 0;  // time stamp in milliseconds of the previous loop
unsigned long runTime = 0; // total time code has been running
unsigned long startTime = millis();

/********* Declare functions from other files ********/
// pid.ino
void pid_setup(double p_x, double i_x, double d_x, double p_y, double i_y, double d_y, double p_z, double i_z, double d_z);
void pid_loop(int timeChange);

// servo.ino
void set_servo(double myservo1_val, double myservo2_val, double myservo3_val, double myservo4_val);
void servo_setup();

// hover_engine.ino
void hover_engine_setup();
void start_motors();
void stop_motors();

// optoNCDT_analog_HDK2.ino
void read_optoNCDT_values();

// BNO055.ino
void BNO055_setup();
void BNO055_loop();

// rpm_ramp.ino
void rpm_ramp_loop();

// pitch_and_roll.ino
//void pitch_and_roll_setup();
//void pitch_and_roll_loop(unsigned long runTime);



/*
 * Main setup function. 
 * Reset the HDK, initialise sensors and PID and start motors
 */
void setup(){  
  hover_engine_setup();
  delay(1000);
  servo_setup();
  BNO055_setup();
  // pid_setup(0.2, 0, 0, 0, 0, 0, 0, 0, 0); // pid constants (3-dimensions)
  Serial.begin(9600);

  delay(10000); // hover for X seconds.

}


/*
 * Main loop function. Calls loop functions from each file.
 */

void loop() {
  unsigned long now = millis();
  double timeChange = (double)(now - lastTime);
  runTime = now - startTime;
  Serial.print(runTime/1000); // elapsed time
  Serial.print(",");

  pid_loop(timeChange);
  BNO055_loop();
  rpm_ramp_loop();
  read_optoNCDT_values();
  //pitch_and_roll_loop(runTime);
  // if (runTime > 60000){
  //   stop_motors();
  //   delay(999999999999);
  // }

  delay(1000);
}

