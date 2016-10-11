/* This file handles taking readings from the laser distance sensors*/
  // will need to be changed from analog to digital

int sensorPin5 = A0;
int sensorPin1 = A1;
int sensorPin4 = A2;
int sensorPin2 = A15;
int sensorPin3 = A16;
int sensorPin6 = A17;

int sensorValues[3] = {0, 0, 0};

int distance_10bit = 0;
int min_distance_10bit = 223;
int min_distance = 35;
int max_distance = 86;
float distances_mm = {0, 0, 0};

/* Convert 10bit values to mm */
void convert(){
  for (i=0; i<3; i++){
    distances_mm[i] = (sensorValues[i] - min_distance_10bit) * max_distance / 1023 + min_distance;  
  }
}

/* Takes a reading from each laser distance sensor */
void read_optoNCDT_values() {
  sensorValues[0] = analogRead(sensorPin1);
  sensorValues[1] = analogRead(sensorPin4);
  sensorValues[2] = analogRead(sensorPin5);
  convert();

  // Print measurements
  for (i=0; i<3; i++){
    Serial.print(sensorValues[i]);
    Serial.print(",");
  }
  Serial.println("");
 
}


