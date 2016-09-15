// rpm control values
int rpm_counter = 999;




void rpm_ramp_loop(){
  // increment the pulse length and call func to write to pin
  rpm_counter = rpm_counter + 1;
  if (rpm_counter == 2001){ 
    rpm_counter = 1000;
  }
  set_rpm(rpm_counter); // we speculate 1000-2000 is the acceptable range of pulse lengths to vary rpm

  Serial.print("RPM: ");
  Serial.println(rpm_counter);
}