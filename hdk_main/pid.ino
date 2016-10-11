/* All PID control loops can be found here */

static double set_point = 0; // desired direction in degrees
static double correction_angle_x, correction_angle_y, correction_angle_z; // correction that needs to be made to the direction of the servos to move toward the set_point
static double correction_rpm_y, correction_rpm_z; //correction in pulse for pwm converted from angle

double Err_x, Err_y, Err_z;  // Current measured error
double iErr = 0; // integrated error (PID)
double dErr = 0; // differential error (PID)
double last_error_x = 0, last_error_y = 0, last_error_z = 0; // error stored from previous loop through code

double kp_x, ki_x, kd_x; // constants to tune PID loop
double kp_y, ki_y, kd_y; // constants to tune PID loop
double kp_z, ki_z, kd_z; // constants to tune PID loop

int firstTime = 0;

void set_servo(double myservo1_val, double myservo2_val, double myservo3_val, double myservo4_val); // use func from servo.ino to set gimballing angle

/*
 * Function for setting up the three PID constants
 */
  // why is this necessary?
void pid_setup(double p_x, double i_x, double d_x, double p_y, double i_y, double d_y, double p_z, double i_z, double d_z)
{
   kp_x = p_x;
   ki_x = i_x;
   kd_x = d_x;
   kp_y = p_y;
   ki_y = i_y;
   kd_y = d_y;
   kp_z = p_z;
   ki_z = i_z;
   kd_z = d_z;
}

int compute_correction(double Err, double last_error, double kp, double ki, double kd, double timeChange){
  double correction_angle = 0;
  if (Err > 180)
  {
    Err = Err - 360;
  }

  // to avoid having integral error calc blow up the first time through 
  //    (when loop runtime is calculated using: lastTime = 0; now = millis())
  if (!firstTime) 
  {
    // differential error calculation
    dErr = (Err - last_error)/timeChange;

    // integral error calculation
    iErr = iErr + Err*timeChange; 
  }  

  // final PID value
  correction_angle = kp * Err + ki * iErr + kd * dErr;
  
  firstTime = 1;
  return correction_angle;
}


int pulse_correction(double correction_angle){
  // correct pitch/roll using pwm signal to hover engines
  // write this...
}

void print_data(){
  Serial.print("\tcorrection_angle_x: ");
  Serial.print(correction_angle_x, 4);
  Serial.print("\tcorrection_angle_y: ");
  Serial.print(correction_angle_y, 4);
  Serial.print("\tcorrection_angle_z: ");
  Serial.print(correction_angle_z, 4);
  Serial.print("\tErr_x: ");
  Serial.print(Err_x, 4);
  Serial.print("\tErr_y: ");
  Serial.print(Err_y, 4);
  Serial.print("\tErr_z: ");
  Serial.print(Err_z, 4);
}

void pid_loop(int timeChange){

  // calculate error from intended orientation (currently set to an absolute value of 0 (like a compass pointing north), but could be adjusted, or even made relative)
  Err_x = measured_BNO_value_x - set_point;
  Err_y = measured_BNO_value_y - set_point;
  Err_z = measured_BNO_value_z - set_point;

  correction_angle_x = compute_correction(Err_x, last_error_x, kp_x, ki_x, kd_x, timeChange);
  correction_angle_y = compute_correction(Err_y, last_error_y, kp_y, ki_y, kd_y, timeChange);
  correction_angle_z = compute_correction(Err_z, last_error_z, kp_z, ki_z, kd_z, timeChange);

  correction_rpm_y = pulse_correction(correction_angle_y);
  correction_rpm_z = pulse_correction(correction_angle_z);

  /********** YAW CORRECTION (complete w/ pid) *************/
  if (correction_angle_x < 0)
  {
    correction_angle_x = -1 * correction_angle_x;
  }

  // cap the correction_angle value at 20 for yaw, beyond that risks the gimbal hiting the ground or the top plate
  if (correction_angle_x > 20)
  {
      correction_angle_x = 20;
  }

  // set servo values according to the offset direction and apply the PID value
  if (Err_x < 0)
  {
    set_servo(90, 90 - correction_angle_x, 90, 90 + correction_angle_x); // set two diagonal motors to always point downwards, and the other two to point according to the PID
  }
  else
  {
    set_servo(90 + correction_angle_x, 90, 90 - correction_angle_x, 90); // set two diagonal motors to always point downwards, and the other two to point according to the PID
  }

  // lagging variable for P error
  last_error_x = Err_x;
  last_error_y = Err_y;
  last_error_z = Err_z;

  //print_data();
}// end of pid_loop()
