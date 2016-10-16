// hover engine pins
#define pwmPin1 20
#define pwmPin2 21
#define pwmPin3 22
#define pwmPin4 23



void setup() {
  // put your setup code here, to run once:
pinMode(pwmPin1, OUTPUT);
pinMode(pwmPin2, OUTPUT);
pinMode(pwmPin3, OUTPUT);
pinMode(pwmPin4, OUTPUT);
analogWriteFrequency(pwmPin1, 490);
analogWriteFrequency(pwmPin2, 490); 
analogWriteFrequency(pwmPin3, 490);
analogWriteFrequency(pwmPin4, 490);  
 stop_motors();
}

void loop() {
  // put your main code here, to run repeatedly:
}

void stop_motors()
{
  analogWrite(pwmPin1, 125);
  delay(1000);
  analogWrite(pwmPin2, 125);
  delay(1000);
  analogWrite(pwmPin3, 125);
  delay(1000);
  analogWrite(pwmPin4, 125);
  
}
