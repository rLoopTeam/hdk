// run through the possible values for rpm to see how hover engine hover height is affected

int rpm_counter = 999;

void set_rpm(); // use func from hover_engine.ino to set engine rpm's

void rpm_ramp_loop(){
  // increment the pulse length and call func to write to pin; 
	// print rpm values, to be compared against hover height values printed from optoNCDT_analog_hdk2.ino
  rpm_counter = rpm_counter + 1;
  if (rpm_counter == 2001){ 
    rpm_counter = 1000;
  }
  set_rpm(rpm_counter, rpm_counter, rpm_counter, rpm_counter); // we speculate 1000-2000 is the acceptable range of pulse lengths to vary rpm

  Serial.print("RPM: ");
  Serial.println(rpm_counter);
}