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
