/* run through the possible values for rpm to see how hover engine hover height is affected */
  // need to note in particular the value at which hdk can safely hover

int rpm_counter = 125;

void set_rpm(int rpm1, int rpm2, int rpm3, int rpm4); // use func from hover_engine.ino to set engine rpm's

void rpm_ramp_loop(){
  // increment the pulse length and call func to write to pin; 
	// print rpm values, to be compared against hover height values printed from optoNCDT_analog_hdk2.ino
  rpm_counter = rpm_counter + 1;
  if (rpm_counter == 249){ 
    rpm_counter = 126;
  }
  set_rpm(rpm_counter, rpm_counter, rpm_counter, rpm_counter); // we speculate 1000-2000 is the acceptable range of pulse lengths to vary rpm

  // Serial.print("RPM: ");
  Serial.print(rpm_counter);
  Serial.print(",");
}
