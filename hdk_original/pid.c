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
  // if the sensor is returning a value between 0 and 180, set reverse the error value and set direction to 0
  double correction_angle = 0;
  if (Err > 180)
  {
    Err = Err - 360;
  }

  if (!firstTime)
  {
    // differential error calculation
    dErr = (Err - last_error)/timeChange;

    // integral error calculation
    iErr = iErr + Err*timeChange; // this term blows up since lastTime defined to be 0 and now defined to be millis();
  }

  // final PID value
  correction_angle = kp * Err + ki * iErr + kd * dErr;

  firstTime = 1;
  return correction_angle;
}

int pulse_correction(double correction_angle){
  double pulse = 0;
  if (correction_angle < 0)
    {
      correction_angle = -1 * correction_angle;
    }
  pulse = correction_angle; // <–––––––––––Need to write something to convert correction angle to pulse

  return pulse;
}

void pid_loop(int timeChange){
  // lagging variable for P error
  last_error_x = Err_x;
  last_error_y = Err_y;
  last_error_z = Err_z;

  // below block is in BNO file, might need to be here instead
  // // get orientation from sensor
  // measured_value_x = event.orientation.x;
  // measured_value_y = event.orientation.y;
  // measured_value_z = event.orientation.z;

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

  /********** PITCH CORRECTION *************/
  // adjust engine rpms
  //   which motors need to change speed?
  //   need function to convert correction angle to pulse length (requires data for hdk at rest and at high speed
  // set_rpm()

  //1, 2 are back; 3, 4 are front
  // if (Err_y < 0)
  // {

  // }
  // else
  // {

  // }

  /********** ROLL CORRECTION *************/
  // adjust engine rpms
  //   which motors need to change speed?
  //   need function to convert correction angle to pulse length (requires data for hdk at rest and at high speed)
  // set_rpm()
  // if (Err_z < 0)
  //{
  //set_servo();
  //}
  //else
  //{
  //set_servo();
  //}


  // Serial.print("\tcorrection_angle_x: ");
  // Serial.print(correction_angle_x, 4);
  // Serial.print("\tcorrection_angle_y: ");
  // Serial.print(correction_angle_y, 4);
  // Serial.print("\tcorrection_angle_z: ");
  // Serial.print(correction_angle_z, 4);
  // Serial.print("\tErr_x: ");
  // Serial.print(Err_x, 4);
  // Serial.print("\tErr_y: ");
  // Serial.print(Err_y, 4);
  // Serial.print("\tErr_z: ");
  // Serial.print(Err_z, 4);
}// end of main, code that was looped in hdk.ino
