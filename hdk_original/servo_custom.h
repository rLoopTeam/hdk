#ifndef SERVO_CUSTOM_H
#define SERVO_CUSTOM_H

/** Servo pins */
#define step4 3
#define step3 5
#define step2 4
#define step1 6

/** Servo initialization */
Servo myservo1;
Servo myservo2;
Servo myservo3;
Servo myservo4;

/**
 * Function for setting the servos including a calibration value
 * Parameters match the hover engine/servo number on the HDK
 * e.g. 1 - servo 1, 2 - servo 2 etc
 */
void set_servo(double myservo1_val, double myservo2_val, double myservo3_val, double myservo4_val);

/**
 *  attach servos and set default positions.
 */
void servo_setup();
#endif
