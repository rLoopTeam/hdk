package main

import (
	"bufio"
	"fmt"
	"github.com/tarm/goserial"
	"io"
	"os"
)

//opens a serial (USB) port. if a "port_number" is send, that port will be ignored
func openPort(port string) io.ReadWriteCloser {

	//try opening serial port i
	config := &serial.Config{Name: port, Baud: 9600}
	usb, err := serial.OpenPort(config)

	if err != nil {
		panic(err)
	} else {
		fmt.Println("Opened ", port)
		return usb
	}
}

//figure out which port is the laser and which is accelerometer
func findLaser(reader_1 *bufio.Reader) *bufio.Reader {

	data, err := reader_1.ReadBytes('\n')
	if err != nil {
		fmt.Println(err)
	}

	//grab a sample from one sensor and see how many values it has,
	//we know the accelerometer should have alot more than 2 values
	fmt.Println(string(data))
	// split := strings.Split(string(data), ",")
	return reader_1
}

//this thread syncs up the data between the sensors if they are sending at diffrent rates.
func fileWriter(acc_channel_send chan bool, acc_channel_data chan string, file *os.File) {
	var acc_data string

	for {
		//send some data on the channels to let both sensors send one value
		acc_channel_send <- true

		//read the values. fileWriter will block here untill it gets one value from both sensors.
		//this means fileWriter will automatically adjust to the sensor with the slowest data rate.
		//excess data from the faster sensor is discarded
		acc_data = <-acc_channel_data

		//print and write to file
		fmt.Println(acc_data)
		file.WriteString(acc_data + "\n")
	}

}

//reads sensor data and discards excess values
func readSensor(reader *bufio.Reader, channel_in chan bool, channel_out chan string) {

	for {
		//read one value from sensor
		data, err := reader.ReadBytes('\n')
		if err != nil {
			panic(err)
		}

		//check if we should send this value to the file writer
		select {

		//this is basically an if("channel has some data"). also removes the data from channel, so we can only write send sensor value per channel_in data received.
		//this is what creates the synchronization, think of the data as a "permission to send one value"-token.
		//what we send on the _in channel doesnt matter, only that we send "something".
		//in this case we send booleans but could be anything.
		case <-channel_in:
			data = data[:len(data)-2]   //remove "\n\r from sensor value"
			channel_out <- string(data) //send sensor value to file writer thread
		default:
			//if there was no data on the channel the "select" will go into the default case, and we discard the sensor value. aka DO NOTHING :D
		}
	}
}

func main() {

	//these channels are used by fileWriter to synchronize the sensor data-rates
	//the "0" means there can only be 1 value on the channel at any one time, aka "unbuffered" channel
	acc_channel_in := make(chan bool, 0)

	//these are used to send sensor values to the file writer
	acc_channel_data := make(chan string, 0)

	//open two usb ports. we use i to make sure we dont open the same port twice!
	usb_1 := openPort("/dev/cu.usbmodem1967811")

	//make 2 buffered readers from serial port readers. buffered readers are easier to work with
	reader_1 := bufio.NewReader(usb_1)

	//figure out which port is laser and which is accelerometer
	accelerometer := findLaser(reader_1)

	//reader from the keyboard
	key_reader := bufio.NewReader(os.Stdin)

	fmt.Println("Ready to record, enter file name?")

	file_name, _ := key_reader.ReadString('\n')
	file_name = file_name[:len(file_name)-1] // remove "\n"
	//we need a default file name if nothing was entered
	if len(file_name) == 0 {
		file_name = fmt.Sprint("data")
	}
	file_name += ".csv"
	fmt.Println("Recording..")
	fmt.Println("Filename: ", file_name)

	//file_name = "/home/nebu/python/rchart/" + file_name //change this to where to save files on your computer

	//remove old file and create a new one
	_ = os.Remove(file_name)
	file, err := os.Create(file_name)
	if err != nil {
		panic(err)
	}

	//write the header with column names
	file.WriteString("Target_Height, Laser_Pin1, Laser_Pin4, Laser_Pin5, H1_Height, H1_PWM, H2_Height, H2_PWM, H3_Height, H3_PWM, H4_Height, H4_PWM, H1_Adjusted_PWM, H2_Adjusted_PWM, H3_Adjusted_PWM, H4_Adjusted_PWM,\n")

	//start file writer and sensor reader threads. "go" command runs a function in a separate thread! (technically a separate "go routine", which is "almost" a thread)
	go fileWriter(acc_channel_in, acc_channel_data, file)
	go readSensor(accelerometer, acc_channel_in, acc_channel_data)

	_, _ = key_reader.ReadString('\n')
	fmt.Println("Stopped recording")
	fmt.Println("-----------------\n")
}
