/* test ability to control HDK pitch and roll orientation at rest */
	// roll left, right; pitch forward, back; for 1 sec each
	// before running, need data on hover height vs rpm to avoid hitting the floor


void set_rpm(int rpm1, int rpm2, int rpm3, int rpm4); // use func from hover_engine.ino to set engine rpm's 

int mid_range_rpm = 200; // change based on rpm_ramp data
int delta = 25; // amount to vary rpm by; rough choice based on seeing that hdk wont get off the ground at ~150 or lower pulse width for rpm
int multiplier = 0; // allows looping the pitch/roll sequence

void pitch_and_roll_setup(){
	// start with all rpm's at the middle of their range
	set_rpm(mid_range_rpm, mid_range_rpm, mid_range_rpm, mid_range_rpm); 
}

void pitch_and_roll_loop(unsigned long runTime){
	// move left and back, forward and back; 1 sec movements; print out rpm's each loop
	int rpm1, rpm2, rpm3, rpm4
	if (runTime < 1000 + multiplier * 4000){ // roll left
        rpm1 = mid_range_rpm - delta;
        rpm3 = rpm1;
        rpm2 = mid_range_rpm + delta;
        rpm4 = rpm2;
  		set_rpm(rpm1, rpm2, rpm3, rpm4);
	}
	else if(runTime < 2000 + multiplier * 4000){ // roll right
		rpm1 = mid_range_rpm + delta;
        rpm3 = rpm1;
        rpm2 = mid_range_rpm - delta;
        rpm4 = rpm2;
		set_rpm(rpm1, rpm2, rpm3, rpm4); 
	}  
	else if(runTime < 3000 + multiplier * 4000){ // pitch up
		rpm1 = mid_range_rpm + delta;
        rpm2 = rpm1;
        rpm3 = mid_range_rpm - delta;
        rpm4 = rpm3;
  		set_rpm(rpm1, rpm2, rpm3, rpm4); 
	}
	else if(runTime < 4000 + multiplier * 4000){ // pitch down
		rpm1 = mid_range_rpm - delta;
        rpm2 = rpm1;
        rpm3 = mid_range_rpm + delta;
        rpm4 = rpm3;
	  	set_rpm(rpm1, rpm2, rpm3, rpm4); 
	}
	else{ // roll left and increment multiplier
        rpm1 = mid_range_rpm - delta;
        rpm3 = rpm1;
        rpm2 = mid_range_rpm + delta;
        rpm4 = rpm2;
  		set_rpm(rpm1, rpm2, rpm3, rpm4); 
		multiplier = multiplier + 1;
	}	

   Serial.print("RPM's: ");
   Serial.print(rpm1);
   Serial.print(", ");
   Serial.print(rpm2);
   Serial.print(", ");
   Serial.print(rpm3);
   Serial.print(", ");
   Serial.println(rpm4);

}
