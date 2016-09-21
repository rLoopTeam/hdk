/* Control of HDK Engines */


// hover engine pins
#define pwmPin1 20
#define pwmPin2 21
#define pwmPin3 22
#define pwmPin4 23

void hover_engine_setup(){
  pinMode(pwmPin1, OUTPUT);
  pinMode(pwmPin2, OUTPUT);
  pinMode(pwmPin3, OUTPUT);
  pinMode(pwmPin4, OUTPUT);
  analogWriteFrequency(pwmPin1, 490); //why?
  analogWriteFrequency(pwmPin2, 490); // Second parameter is in hz
  analogWriteFrequency(pwmPin3, 490);
  analogWriteFrequency(pwmPin4, 490);
  stop_motors();
  delay(3000);
  start_motors();

}
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


/*
 * Function for setting the motor rpm (hover engines); range is 126-248 (mostly true; not sure about lower end of range)
 */
void set_rpm(int rpm1, int rpm2, int rpm3, int rpm4)
{
  analogWrite(pwmPin1, rpm1);
  analogWrite(pwmPin2, rpm2);
  analogWrite(pwmPin3, rpm3);
  analogWrite(pwmPin4, rpm4);
}

