void displaySensorDetails(void)
{
  sensor_t sensor;
  bno.getSensor(&sensor);
  // Serial.println("------------------------------------");
  // Serial.print  ("Sensor:       "); Serial.println(sensor.name);
  // Serial.print  ("Driver Ver:   "); Serial.println(sensor.version);
  // Serial.print  ("Unique ID:    "); Serial.println(sensor.sensor_id);
  // Serial.print  ("Max Value:    "); Serial.print(sensor.max_value); Serial.println(" xxx");
  // Serial.print  ("Min Value:    "); Serial.print(sensor.min_value); Serial.println(" xxx");
  // Serial.print  ("Resolution:   "); Serial.print(sensor.resolution); Serial.println(" xxx");
  // Serial.println("------------------------------------");
  // Serial.println("");
  delay(500);
}

void displaySensorStatus(void)
{
  /* Get the system status values (mostly for debugging purposes) */
  uint8_t system_status, self_test_results, system_error;
  system_status = self_test_results = system_error = 0;
  bno.getSystemStatus(&system_status, &self_test_results, &system_error);

  /* Display the results in the Serial Monitor */
  // Serial.println("");
  // Serial.print("System Status: 0x");
  // Serial.println(system_status, HEX);
  // Serial.print("Self Test:     0x");
  // Serial.println(self_test_results, HEX);
  // Serial.print("System Error:  0x");
  // Serial.println(system_error, HEX);
  // Serial.println("");
  delay(500);
}

void displayCalStatus(void)
{
  /* Get the four calibration values (0..3) */
  /* Any sensor data reporting 0 should be ignored, */
  /* 3 means 'fully calibrated" */
  uint8_t system, gyro, accel, mag;
  system = gyro = accel = mag = 0;
  bno.getCalibration(&system, &gyro, &accel, &mag);

  /* The data should be ignored until the system calibration is > 0 */
  //Serial.print("\t");
  if (!system)
  {
    //Serial.print("! ");
  }

  /* Display the individual values */
  // Serial.println("BNO Values");
  // Serial.print("Sys:");
  // Serial.print(system, DEC);
  // Serial.print(" G:");
  // Serial.print(gyro, DEC);
  // Serial.print(" A:");
  // Serial.print(accel, DEC);
  // Serial.print(" M:");
  // Serial.print(mag, DEC);
}

void BNO055_setup(){
	  //Serial.println("Orientation Sensor Test"); Serial.println("");

  /* Initialise the sensor */
  if(!bno.begin())
  {
    /* There was a problem detecting the BNO055 ... check your connections */
    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    while(1);
  }

  delay(1000);

  /* Display some basic information on this sensor */
  displaySensorDetails();

  /* Optional: Display current status */
  displaySensorStatus();

  bno.setExtCrystalUse(true);
  delay(10);

}

void BNO055_loop(){
  sensors_event_t event;
  // update sensor
  bno.getEvent(&event);


  // get orientation from sensor
  measured_BNO_value_x = event.orientation.x;
  measured_BNO_value_y = event.orientation.y;
  measured_BNO_value_z = event.orientation.z;


  // Serial.print("X: ");
  Serial.print(event.orientation.x, 4);
  Serial.print(",");
  // Serial.print("\tY: ");
  // Serial.print(event.orientation.y, 4);
  // Serial.print("\tZ: ");
  // Serial.print(event.orientation.z, 4);

  /* Wait the specified delay before requesting next data */
  delay(BNO055_SAMPLERATE_DELAY_MS);

}
