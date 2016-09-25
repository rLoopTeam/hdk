#include <Servo.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BN055.h>
#include <utility/imumaths.h>

// Time stamp in milliseconds of the previous loop
unsigned long lastTime = 0;
// Total time code has been running
unsigned long runTime = 0;

unsigned long startTime = millis();

/**
 *  Main setup function.
 *  Reset HDK
 *  Initialize sensors
 *  PID
 *  start motors
 */
void setup() {
  hover_engine_setup();
  delay(1000);
  servo_setup();
  BNO055_setup();
  // PID constants, 3 dimensions
  // pid_setup(0.2, 0, 0, 0, 0, 0, 0, 0, 0);
  Serial.begin(9600);

  delay(10000); // hover for X seconds.
}

/**
 *  Main loop function.
 *
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
  // pitch_and_roll_loop(runTime);
  // if (runTime > 60000) {
  //  stop_motors();
  //  delay(9999999999);
  // }
  delay(1000);
}
