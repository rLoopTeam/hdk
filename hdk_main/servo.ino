// servo pins
#define step4 3
#define step3 5
#define step2 4
#define step1 6

// servo initialisation
Servo myservo1;
Servo myservo2; 
Servo myservo3;
Servo myservo4;

/*
 * Function for setting the servos including a calibration value
 * Parameters match the hover engine/servo number on the HDK 
 * e.g. 1 - servo 1, 2 - servo 2 etc
 */
void set_servo(double myservo1_val, double myservo2_val, double myservo3_val, double myservo4_val)
{
  // when setting the value of a servo, we include a correction value to account for hardware issues.
  // the correction vlaue is simply the correction angle required to make the gimbal point straight down.
  // if we set the servo to point to 90 degrees(straight down) but the gimbal points 5 degrees off, we have to add to remove
  // 5 degrees in the write() function parameter as shown below.
  myservo1.write(myservo1_val - 0); // 90 - 45 == motor pointing downwards (when downwards is 90 degrees)
  myservo2.write(myservo2_val + 5);
  myservo3.write(myservo3_val - 5);
  myservo4.write(myservo4_val + 5);
}


void servo_setup(){
  myservo1.attach(step1);
  myservo2.attach(step2);
  myservo3.attach(step3);
  myservo4.attach(step4);
  set_servo(90, 70, 90, 100); // TODO ask about this
  delay(1000);
}



