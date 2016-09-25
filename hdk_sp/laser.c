void convert(){
  distance_measured = (sensorValue - min_distance_10bit) * max_distance / 1023 + min_distance;
}

void read_optoNCDT_values() {
  sensorValue = analogRead(sensorPin1);
  // Serial.print("Sensor1: ");
  Serial.print(sensorValue);
  Serial.print(",");
  // Serial.print("  ");
  // convert();
  // Serial.println(distance_measured);

  sensorValue = analogRead(sensorPin4);
  // Serial.print("Sensor4: ");
  Serial.print(sensorValue);
  Serial.print(",");
  // Serial.print("  ");
  // convert();
  // Serial.println(distance_measured);

  sensorValue = analogRead(sensorPin5);
  // Serial.print("Sensor5: ");
  Serial.print(sensorValue);
  Serial.print(",");
  Serial.println("");
  // Serial.print("  ");
  // convert();
  // Serial.println(distance_measured);

}
