// Target_Height, Laser_Pin1, Laser_Pin4, Laser_Pin5, H1_Height, H1_PWM, H2_Height, H2_PWM, H3_Height, H3_PWM, H4_Height, H4_PWM, H1_Adjusted_PWM, H2_Adjusted_PWM, H3_Adjusted_PWM, H4_Adjusted_PWM, 

extern "C" {
  #include "LaserOrientation.h"
}

// hover engine pins
#define pwmPin1 20
#define pwmPin2 21
#define pwmPin3 22
#define pwmPin4 23

#define HESIZE 4 

float adjusted_PWM[4];


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
    float prev_i_error; //previous integral
    float prev_error; //previous proportional error
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



//Global Variables
float Laser1Reading;
float Laser2Reading;
float Laser3Reading;


//HE heights
float HE1_height, HE2_height, HE3_height, HE4_height;

void setup() {
  //struct hover_engine *he_ptr = he;
  Serial.begin(9600);
  // read_optoNCDT_values(); 
  stop_motors();
  delay(3000);
  start_motors();
  delay(30000);
  read_optoNCDT_values(); 
  // print_laser_info();
  get_lowest_height();
  // print_he_info(he_ptr);
  // Serial.print("Reach end of setup...\n");
}

void loop() {
  print_target_height();
  // Serial.print("Testing...\n");
  struct hover_engine *he_ptr = he;
  struct pid_data *data_ptr = data;
  struct pid_constants *pid_consts_ptr = &pid_consts;

  
  read_optoNCDT_values(); //HE heights are also calculated in here
  print_laser_info();
  print_he_info(he_ptr);
  computePID(data_ptr, pid_consts_ptr, he_ptr);
  print_PWM_after_computePID(adjusted_PWM);
  Serial.print("\n");
  // Serial.print("After...\n");
  // print_he_info(he_ptr);
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


float convert(){
  return ( 50*((double)(sensorValue-200)/800)) + 35;  
}


/* Takes a reading from each laser distance sensor */
void read_optoNCDT_values() {
  sensorValue = analogRead(sensorPin1);  
  Laser1Reading = convert();

  sensorValue = analogRead(sensorPin4);
  Laser2Reading = convert();

  sensorValue = analogRead(sensorPin5);
  Laser3Reading = convert();
  calculateOrientation();

}

void print_laser_info() {
  Serial.printf("%f,",Laser1Reading);
  Serial.printf("%f,",Laser2Reading);
  Serial.printf("%f,",Laser3Reading);
}

void calculateOrientation() {
  RecalcOrientation();
  he[0].height = HE1HeightAboveTrack;
  he[1].height = HE2HeightAboveTrack;
  he[2].height = HE3HeightAboveTrack;
  he[3].height = HE4HeightAboveTrack;
}

void get_lowest_height() {
  float a = he[0].height, b=he[1].height, c=he[2].height, d=he[3].height;
  float min_ab, min_bc, min;
  min_ab = a < b ? a : b;
  min_bc = c < d ? c : d;
  min = min_ab < min_bc ? min_ab : min_bc;

  target_height = min;
}

void print_target_height() {
  Serial.printf("%f,",target_height);
}

void print_he_info(struct hover_engine *he_ptr) {
    for(int i = 1; i < HESIZE+1; i++){
        Serial.printf("%f,%d,",he_ptr->height,he_ptr->pwm);
        he_ptr++;
    }
}

void print_PWM_after_computePID(float adjusted_PWM[4]) {
  for(int i=0; i<4; i++) {
      Serial.printf("%f,",adjusted_PWM[i]);
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
    float error, i_error, d_error;
    float p, i, d;
    float pid;
    unsigned long now = millis();
    int timeChange = (int)(now - lastTime);
    // Serial.print("Time Change: ");
    // Serial.println(timeChange);
    
    if(timeChange >= SampleTime){
        for(int j = 0; j < HESIZE; j++){
            error=0, i_error=0, d_error=0, p=0, i=0, d=0, pid=0;
        
            error = target_height - he_ptr->height;
            i_error = data_ptr->prev_i_error + error*timeChange;
            d_error = (error - data_ptr->prev_error)/timeChange;
        
            p = error * consts_ptr->Kp;
            i = i_error * consts_ptr->Ki;
            d = d_error * consts_ptr->Kd;
        
            pid = p + i + d;
            
            i_error = i_error * consts_ptr->i_decay;
            data_ptr->prev_i_error = i_error;
            data_ptr->prev_error = error;
            
            adjusted_PWM[j] = pid < consts_ptr->out_max? (pid > consts_ptr->out_min? pid : consts_ptr->out_min) : consts_ptr->out_max;
            
//            print_PWM_after_computePID(adjusted_PWM);
            
            he_ptr->pwm = he_ptr->pwm + adjusted_PWM[j];
            
            he_ptr->pwm =  (he_ptr->pwm < he_ptr->maxPWM)? (he_ptr->pwm > he_ptr->minPWM?
                he_ptr->pwm: he_ptr->minPWM): he_ptr->maxPWM;
            
            //TODO balance and offset?
            
            he_ptr++;
            data_ptr++;
        }
        
        lastTime = now;
    }
}

