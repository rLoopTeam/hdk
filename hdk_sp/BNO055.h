/**
 *  Read values and print status of accelerometers to serial.
 */

static double measured_BNO_value_x; // value output from the BNO orientation sensor
static double measured_BNO_value_y; // value output from the BNO orientation sensor
static double measured_BNO_value_z; // value output from the BNO orientation sensor

#define BNO055_SAMPLERATE_DELAY_MS(20)

/** bno055 orientation sensor */
Adafruit_BN055 bno = Adafruit_BN055(55);

/**
 *  Display the sensors details at initialization
 */
void displaySensorDetails(void);

/**
 *  Display status of the sensors
 */
void displaySensorStatus(void);

/**
 *  Display calibrated status
 */
void displayCalStatus(void);

/**
 *  inital setup code for BNO
 */
void BNO055_setup();

/**
 *  accelerometer loop
 */
void BNO055_loop();
