/* run through the possible values for rpm-pwm to see how hover engine hover height is affected */
  //allowed range: 125-248 (>170 to actually hover)

int rpm_counter = 171;
int loop_counter = 0;
int parity = 1;

void stop_motors(); // stop_motors() func from hover_engine.ino

void set_rpm(int rpm1, int rpm2, int rpm3, int rpm4); // use func from hover_engine.ino to set engine rpm's

void rpm_ramp_loop(){
  // increment the pulse length and call func to write to pin; 
	// print rpm values, to be compared against hover height values printed from optoNCDT_analog_hdk2.ino
  rpm_counter += parity;
  if (rpm_counter == 248){ 
    parity *= -1;
  }
  if (rpm_counter == 170){ 
    loop_counter += 1;
    parity *= -1;
  }

  set_rpm(rpm_counter, rpm_counter, rpm_counter, rpm_counter); 

  if (loop_counter == 1){ // slow down motors then stop
    set_rpm(160, 160, 160, 160);
    delay(1000);
    stop_motors();
    delay(9999999);
  }

  // Serial.print("RPM: ");
  Serial.print(rpm_counter);
  Serial.print(",");
}
