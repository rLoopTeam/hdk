void pitch_and_roll_setup(){
	// start with all rpm's at the middle of their range
	set_rpm(mid_range_rpm, mid_range_rpm, mid_range_rpm, mid_range_rpm);
}

void pitch_and_roll_loop(unsigned long runTime){
	// move left and back, forward and back; 1 sec movements; print out rpm's each loop
	if (runTime < 1000 + multiplier * 4000){ // roll left
  	set_rpm(mid_range_rpm - delta, mid_range_rpm + delta, mid_range_rpm - delta, mid_range_rpm + delta);
	}
	else if(runTime < 2000 + multiplier * 4000){ // roll right
		set_rpm(mid_range_rpm + delta, mid_range_rpm - delta, mid_range_rpm + delta, mid_range_rpm - delta);
	}
	else if(runTime < 3000 + multiplier * 4000){ // pitch up
  	set_rpm(mid_range_rpm + delta, mid_range_rpm + delta, mid_range_rpm - delta, mid_range_rpm - delta);
	}
	else if(runTime < 4000 + multiplier * 4000){ // pitch down
	  set_rpm(mid_range_rpm - delta, mid_range_rpm - delta, mid_range_rpm + delta, mid_range_rpm + delta);
	}
	else{ // roll left and increment multiplier
  	set_rpm(mid_range_rpm - delta, mid_range_rpm + delta, mid_range_rpm - delta, mid_range_rpm + delta);
		multiplier = multiplier + 1;
	}

 //  Serial.print("RPM's: ");
 //  Serial.print(analogRead(pwmPin1));
 //  Serial.print(", ");
 //  Serial.print(analogRead(pwmPin2));
 //  Serial.print(", ");
 //  Serial.print(analogRead(pwmPin3));
 //  Serial.print(", ");
	// Serial.println(analogRead(pwmPin4));

}
