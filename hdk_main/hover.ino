/* hover.ino
* 		If button is pressed, hover the hdk at full rpm for about 30 seconds
*/

#define buttonPin // add a pin number

int buttonPressed = 0;
unsigned long motorStartTime = 0;
int motors_on = 0;

// setup func called from hdk_main_setup()
void hover_setup(){
  PinMode(buttonPin, INPUT);
}

// See if button has been pressed
void check_button(){
	int buttonValue = analogRead(buttonPin);
	if (buttonValue){
		buttonPressed = 1;
	}	
}

// loop function called from hdk_main_loop()
void hover_loop(unsigned long runTime){
	check_button();
	if(buttonPressed){
		motorStartTime = now;
		start_motors(); // once this is started, other rpm controls (rpm_ramp; pitch_and_roll) need to know not to overwrite it
		motors_on = 1;
	}

	if (motors_on){
		time_elapsed = now - motorStartTime;
		if (time_elapsed > 30*1000){
			stop_motors();
			motors_on = 0;
		}
	}
}

