int sensorPin5 = A0;
int sensorPin1 = A1;
int sensorPin4 = A2;
int sensorPin2 = A15;
int sensorPin3 = A16;
int sensorPin6 = A17;

int sensorValue = 0;

int distance_10bit = 0;
int min_distance_10bit = 223;
int min_distance = 35;
int max_distance = 86;
float distance_measured = 0;


void convert(){
  distance_measured = (sensorValue - min_distance_10bit) * max_distance / 1023 + min_distance;  
}


/* Takes a reading from each laser distance sensor */
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


