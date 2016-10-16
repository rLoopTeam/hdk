
// hover engine pins
#define pwmPin1 20
#define pwmPin2 21
#define pwmPin3 22
#define pwmPin4 23

/* This file handles taking readings from the laser distance sensors*/

int rpm_counter = 201;




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
  
  delay(2000);
  stop_motors();
  delay(6000);  
  start_motors();
  delay(30000);
}

void loop() {
  Serial.print(rpm_counter);
  Serial.print(",");
  set_rpm(rpm_counter,rpm_counter,rpm_counter,rpm_counter);
  rpm_counter -=1;
  
  if (rpm_counter == 135){ 
      stop_motors();
  }
  
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









