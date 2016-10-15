#ifndef PITCH_AND_ROLL_H
#define PITCH_AND_ROLL_H

/**
 *  TEST FILE
 *  Test ability to control HDK pitch and roll orientations at rest
 *  Roll left, right; pitch forward, back; for 1 second each
 *  before running, need data on hover height vs rpm to avoid hitting the floor.
 */

/** Change based on RPM ramp data */
int mid_range_rpm = 214;
/** Amout to vary rpm by; rough choice based on seeing that HDK won't
    get of the ground at ~150 or lower pulse width for rpm*/
int delta = 34;
/** Allows for looping the pitch/roll sequence */
int multiplier = 0;

/**
 *  Setup pitch and roll rmps
 */
void pitch_and_roll_setup();

/**
 *  Move left anf back, forward and back; for 1 second each.
 *  @param runTime total time running since reset.
 */
void pitch_and_roll_loop(unsigned long runTime);


#endif
