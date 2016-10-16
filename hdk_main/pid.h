#ifndef PID_H
#define PID_H

/**
 *  All pid Control loops here
 */


 static double last_error_x; 		// error stored from previous loop through code
 static double last_error_y; 		// error stored from previous loop through code
 static double last_error_z; 		// error stored from previous loop through code
 static double set_point = 0; 		// desired direction in degrees
 static double correction_angle_x; 	// correction that needs to be made to the direction of the servos to move toward the set_point
 static double correction_angle_y; 	// correction that needs to be made to the direction of the servos to move toward the set_point
 static double correction_angle_z; 	// correction that needs to be made to the direction of the servos to move toward the set_point
 static double correction_rpm_y; 	// correction in pulse for pwm converted from angle
 static double correction_rpm_z; 	// correction in pulse for pwm converted from angle
 double Err_x = 0;  				// Current measured error
 double Err_y = 0;  				// Current measured error
 double Err_z = 0;  				// Current measured error
 double iErr = 0; 					// integrated error (PID)
 double dErr = 0; 					// differential error (PID)
 double kp_x; 						// constants to tune PID loop
 double ki_x; 						// "" ""
 double kd_x; 						// "" ""
 double kp_y; 						// constants to tune PID loop
 double ki_y; 						// "" ""
 double kd_y; 						// "" ""
 double kp_z; 						// constants to tune PID loop
 double ki_z; 						// "" ""
 double kd_z; 						// "" ""
 int firstTime = 0;

/**
 *  Set servo to a position
 *  @param myservo1_val Servo 1 pulse width
 *  @param myservo2_val Servo 2 pulse width
 *  @param myservo3_val Servo 3 pulse width
 *  @param myservo4_val Servo 4 pulse width
 */
void set_servo(double myservo1_val, double myservo2_val, double myservo3_val, double myservo4_val);

/**
 *  Setting up three PID constants, 3 dimensions
 *  @param p_x Propotional X
 *  @param i_x Integral X
 *  @param d_x Derivative X
 *  @param p_y Propotional Y
 *  @param i_y Integral Y
 *  @param d_y Derivative Y
 *  @param p_z Propotional Z
 *  @param i_z Integral Z
 *  @param i_y Derivative Z
 */
void pid_setup(double p_x, double i_x, double d_x, double p_y, double i_y, double d_y, double p_z, double i_z, double i_y);

/**
 *  Finding the corrections from errors
 *  @param  Err        Error
 *  @param  last_error Previous Error
 *  @param  kp         Propotional constant
 *  @param  ki         Integral Constant
 *  @param  kd         Derivative Constant
 *  @param  timeChange Time between last computation
 *  @return            correction(?)
 */
int compute_correction(double Err, double last_error, double kp, double ki, double kd, double timeChange);

/**
 *  @param  correction_angle N/A
 *  @return                  N/A
 */
int pulse_correction(double correction_angle);

/**
 *  The bulk of the pid functions.
 *  @param timeChange the time between now and last
 */
void pid_loop(int timeChange);

#endif
