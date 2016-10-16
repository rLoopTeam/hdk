extern "C" {
  #include "LaserOrientation.h"
}

// hover engine pins
#define pwmPin1 20
#define pwmPin2 21
#define pwmPin3 22
#define pwmPin4 23

#define HESIZE 4 

//define struct
    //hover_engine.h
struct hover_engine{
    float height;
    int pwm;
    int minPWM;
    int maxPWM;
}he[HESIZE] = { {0,249,170,249},{0,249,170,249},{0,249,170,249},{0,249,170,249} };

//struct laser{
//    
//};

struct pid_data{
    float prev_errorSum; //previous integral
    float prev_error_diff; //previous proportional error
    float target_height;
}data[HESIZE] = {{0,0,8},{0,0,8},{0,0,8},{0,0,8}};

struct pid_constants{
    float Kp;
    float Ki;
    float Kd;
    float i_decay;
    float out_min;
    float out_max;
}pid_consts = {10,0,0,1,-100,100};

//Global Vars
float target_height;
int SampleTime = 1000;
unsigned long lastTime;

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


//HE heights
float HE1_height, HE2_height, HE3_height, HE4_height;

void setup() {
  struct hover_engine *he_ptr = he;
  Serial.begin(9600);
  // read_optoNCDT_values(); 
  stop_motors();
  delay(3000);
  start_motors();
  delay(30000);
  read_optoNCDT_values(); 
  get_lowest_height();
  print_he_info(he_ptr);
  Serial.print("Reach end of setup...\n");
}

void loop() {
  Serial.print("Testing...\n");
  struct hover_engine *he_ptr = he;
  struct pid_data *data_ptr = data;
  struct pid_constants *pid_consts_ptr = &pid_consts;


  read_optoNCDT_values(); //HE heights are also calculated in here
  Serial.print("Before...\n");
  print_he_info(he_ptr);
  computePID(data_ptr, pid_consts_ptr, he_ptr);
  Serial.print("After...\n");
  print_he_info(he_ptr);
  change_motors(he_ptr);

 
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

void change_motors(struct hover_engine *he_ptr)
{
  for(int i = 0; i < HESIZE; i++){
    if(i==0) {
      analogWrite(pwmPin1, he_ptr->pwm);
    }
    else if (i==1){
      analogWrite(pwmPin2, he_ptr->pwm);
    }
    else if (i==2){
      analogWrite(pwmPin3, he_ptr->pwm);
    }
    else if (i==3){
      analogWrite(pwmPin4, he_ptr->pwm);
    }
    he_ptr++;
  }
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
  
//  Serial.print(sensorValue);
//  Serial.print(",");
  // Serial.print("  ");
  
  Serial.print("LaserPin1: ");
  convert();
  Laser1Reading = distance_measured;
  Serial.print(distance_measured);
  Serial.print(",");


  sensorValue = analogRead(sensorPin4);
//  Serial.print(sensorValue);
//  Serial.print(",");
  // Serial.print("  ");
  
     Serial.print("LaserPin4: ");

  convert();
  Laser2Reading = distance_measured;
  Serial.print(distance_measured);
  Serial.print(",");


  sensorValue = analogRead(sensorPin5);
//  Serial.print(sensorValue);
//  Serial.print(",");
//  Serial.println("");
  // Serial.print("  ");

   Serial.print("LaserPin5: ");

  convert();
  Laser3Reading = distance_measured;
  Serial.print(distance_measured);
  Serial.print(",");
//   Serial.println("");

   calculateOrientation();

}

void calculateOrientation() {
  RecalcOrientation();
  he[0].height = HE1HeightAboveTrack;
  he[1].height = HE2HeightAboveTrack;
  he[2].height = HE3HeightAboveTrack;
  he[3].height = HE4HeightAboveTrack;
  //Serial.printf("HE1 Height: %f\n", HE1HeightAboveTrack);
  //Serial.printf("HE2 Height: %f\n", HE2HeightAboveTrack);
  //Serial.printf("HE3 Height: %f\n", HE3HeightAboveTrack);
  //Serial.printf("HE4 Height: %f\n", HE4HeightAboveTrack);
}

void get_lowest_height() {
  float a = he[0].height, b=he[1].height, c=he[2].height, d=he[3].height;
  float min_ab, min_bc, min;
  min_ab = a < b ? a : b;
  min_bc = c < d ? c : d;
  min = min_ab < min_bc ? min_ab : min_bc;

  target_height = min;

  Serial.print("Target Height: ");
  Serial.println(target_height);
}

void print_he_info(struct hover_engine *he_ptr) {
    for(int i = 1; i < HESIZE+1; i++){
        Serial.printf("HE%d <Height: %f, PWM: %d>\n",i,he_ptr->height,he_ptr->pwm);
        he_ptr++;
    }
}

void set_he_pwn(struct hover_engine *he_ptr, float new_pwm[4]) {
    for(int i = 0; i < HESIZE; i++){
        he_ptr->pwm = new_pwm[i];
        he_ptr++;
    }
}

void set_he_height(struct hover_engine *he_ptr, float new_height[4]) {
    for(int i = 0; i < HESIZE; i++){
        he_ptr->height = new_height[i];
        he_ptr++;
    }
}

void computePID(struct pid_data *data_ptr, struct pid_constants *consts_ptr, struct hover_engine *he_ptr) {
    float error_diff, errorSum, errorSlope;
    float p, i, d;
    float pid;
    float adjusted_PWM;
    unsigned long now = millis();
    int timeChange = (int)(now - lastTime);
    Serial.print("Time Change: ");
    Serial.println(timeChange);
    
    if(timeChange >= SampleTime){
        for(int j = 0; j < HESIZE; j++){
            error_diff=0, errorSum=0, errorSlope=0, p=0, i=0, d=0, pid=0, adjusted_PWM=0;
        
            error_diff = target_height - he_ptr->height;
            errorSum = data_ptr->prev_errorSum + error_diff;
            errorSlope = error_diff - data_ptr->prev_error_diff;
        
            p = error_diff * consts_ptr->Kp;
            i = errorSum * consts_ptr->Ki;
            d = errorSlope * consts_ptr->Kd;
        
            pid = p + i + d;
            
            errorSum = errorSum * consts_ptr->i_decay;
            data_ptr->prev_errorSum = errorSum;
            data_ptr->prev_error_diff = error_diff;
            
            adjusted_PWM = pid < consts_ptr->out_max? (pid > consts_ptr->out_min? pid : consts_ptr->out_min) : consts_ptr->out_max;
            
            Serial.printf("Adjusted PWM: %f\n",adjusted_PWM);
            
            he_ptr->pwm = he_ptr->pwm + adjusted_PWM;
            
            he_ptr->pwm =  (he_ptr->pwm < he_ptr->maxPWM)? (he_ptr->pwm > he_ptr->minPWM?
                he_ptr->pwm: he_ptr->minPWM): he_ptr->maxPWM;
            
            //TODO balance and offset?
            
            he_ptr++;
            data_ptr++;
        }
        
        lastTime = now;
    }
}

