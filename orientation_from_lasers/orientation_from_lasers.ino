extern "C" {
  #include "LaserOrientation.h"
}


// hover engine pins
#define pwmPin1 20
#define pwmPin2 21
#define pwmPin3 22
#define pwmPin4 23

/* This file handles taking readings from the laser distance sensors*/

int sensorPin1 = A2;
int sensorPin4 = A0;
int sensorPin5 = A1;

int sensorValue = 0;
float distance_measured = 0;
int rpm_counter = 201;

//Global Variables
float Laser1Reading;
float Laser2Reading;
float Laser3Reading;


void setup() {
  pinMode(pwmPin1, OUTPUT);
  pinMode(pwmPin2, OUTPUT);
  pinMode(pwmPin3, OUTPUT);
  pinMode(pwmPin4, OUTPUT);
  analogWriteFrequency(pwmPin1, 490);
  analogWriteFrequency(pwmPin2, 490);
  analogWriteFrequency(pwmPin3, 490);
  analogWriteFrequency(pwmPin4, 490);
  Serial.begin(9600);
  
  // delay(2000);
  // stop_motors();
  // delay(6000);  
  // start_motors();
  // delay(30000);
}

void loop() {
  read_optoNCDT_values();
  // Serial.print(rpm_counter);
  // Serial.print(",");
  // set_rpm(rpm_counter,rpm_counter,rpm_counter,rpm_counter);
  // rpm_counter -=1;
  
  // if (rpm_counter == 135){ 
  //     stop_motors();
  // }
  delay(500);
}


/* Control of HDK Engines */

/*
 * Function for starting the motors (hover engines)
 */
void start_motors()
{
  analogWrite(pwmPin1, 249);
  analogWrite(pwmPin2, 249);
  analogWrite(pwmPin3, 249);
  analogWrite(pwmPin4, 249);
}

/*
 * Function for stopping the motors (hover engines)
 */
void stop_motors()
{
  analogWrite(pwmPin1, 125);
  analogWrite(pwmPin2, 125);
  analogWrite(pwmPin3, 125);
  analogWrite(pwmPin4, 125);
}


void set_rpm(int rpm1, int rpm2, int rpm3, int rpm4)
{
  analogWrite(pwmPin1, rpm1);
  analogWrite(pwmPin2, rpm2);
  analogWrite(pwmPin3, rpm3);
  analogWrite(pwmPin4, rpm4);
}

void convert(){
  distance_measured = ( 50*((double)(sensorValue-200)/800)) + 35;  
}

/* Takes a reading from each laser distance sensor */
void read_optoNCDT_values() {
  sensorValue = analogRead(sensorPin1);
  // Serial.print("LaserPin1: ");
  convert();
  Laser1Reading = distance_measured;
  Serial.print(distance_measured);
  Serial.print(",");

  sensorValue = analogRead(sensorPin4);
  //Serial.print("LaserPin4: ");
  convert();
  Laser2Reading = distance_measured;
  Serial.print(distance_measured);
  Serial.print(",");

  sensorValue = analogRead(sensorPin5);
  //Serial.print("LaserPin5: ");
  convert();
  Laser3Reading = distance_measured;
  Serial.print(distance_measured);
  Serial.print(",");

  calculateOrientation();
}

void calculateOrientation() {
  RecalcOrientation();
//    Serial.printf("HE1 Height: %f\n", HE1HeightAboveTrack);
//    Serial.printf("HE2 Height: %f\n", HE2HeightAboveTrack);
//    Serial.printf("HE3 Height: %f\n", HE3HeightAboveTrack);
//    Serial.printf("HE4 Height: %f\n", HE4HeightAboveTrack);
//    Serial.printf("Roll: %f\n", Roll);
//    Serial.printf("Pitch: %f\n", Pitch);
  Serial.print(Pitch);
  Serial.print(",");

  Serial.print(Roll);
  Serial.print(",");
   
  Serial.println("");

  // PrintPlane();
}

