#ifndef LASER_H
#define LASER_H

/**
 *  handle taking readings from the laser distance sensors.
 *  Apparently, they're in analog and will need to be converted to digital.
 *        - Legacy comment
 */

int sensorPin5 = A0;
int sensorPin1 = A1;
int sensorPin4 = A2;
int sensorPin2 = A15;
int sensorPin3 = A16;
int sensorPin6 = A17;

int sensorValue = 0;

int distance_10bit = 0;
int min_distance_10bit = 223;
int min_distance = 35;
int max_distance = 86;
float distance_measured = 0;

/**
 *  Convert from analog to digital (?)
 */
void convert();

/**
 *  Takes a reading from each laser distance sensor
 *  outputs to serial.
 */
void read_optoNCDT_values();


#endif
