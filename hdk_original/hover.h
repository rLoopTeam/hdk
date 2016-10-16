#ifndef HOVER_H
#define HOVER_H
/**
 *  Control of HDK Engines.
 */

#define pwmPin1 20
#define pwmPin2 21
#define pwmPin3 22
#define pwmPin4 23


/**
 *  Attach the pulse width pins,
 *  set pins to output and set frequency.
 *
 *  NOTE: changing the write frequency is not understood
 *        as of right now. They have been proven to work
 *        though.
 */
void hover_engine_setup();

/**
 *  Write the start up pulse to the ESC.
 */
void start_motors();

/**
 *  Write the Stop pulse to the ESC.
 */
void stop_motors();

/**
 *  Set the RPM for each specific hover engine.
 *  The range appears to be 126 - 248 according to previous code.
 *  "mostly true; not sure about lower end of range"
 *  @param rpm1 pulse width to motor 1
 *  @param rpm2 pulse width to motor 2
 *  @param rpm3 pulse width to motor 3
 *  @param rpm4 pulse width to motor 4
 */
void set_rmp(int rpm1, int rpm2, int rpm3, int rpm4);

#endif
