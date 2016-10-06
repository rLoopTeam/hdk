# data analysis
# 	Fitting data of average laser distance measured vs pulse width sent to control hdk engine rpm's.

import csv, numpy as np, matplotlib.pyplot as plt

filename = "../data_read_and_plot/2108.csv"
with open(filename, 'r') as csv_file:
	csv_data = csv.reader(csv_file)
	csv_data = [i[:-1] for i in csv_data] # last item in each data point is empty due to main.go syntax

def Change_Data_Types(csv_data):
	"""change data types from strings to int/float"""
	csv_data_reformat = []
	csv_data_reformat.append(csv_data[0]) # zero index contains column titles (e.g. 'BNO', 'Laser1'), which should be left as strings
	for item in csv_data[1:]:
		new_item = []
		for j in range(len(item)):
			if j != 1: # BNO data are float, rest should be int
				new_item.append(int(item[j]))
			else:
				new_item.append(float(item[j]))
		csv_data_reformat.append(new_item)
	return csv_data_reformat 

csv_data = Change_Data_Types(csv_data)

# Add the average of the 3 laser measurements to each data point
csv_data[0].append('Laser_avg')
for item in csv_data[1:]:
	laser_data = tuple(item[-3:])
	item.append(np.mean(laser_data))

###############################
# raw data
time = [item[0] for item in csv_data[1:]]
rpm_pulse_width = [item[2] for item in csv_data][1:]
avg_laser = [item[6] for item in csv_data][1:]

# Plot raw data 
plt.subplot(311)
plt.scatter(time, avg_laser, color='r', s=25)
plt.xlabel('time (s)')
plt.ylabel('Avg Laser Distance Measurement')
plt.title("Avg Laser Distance Measurement vs Time")

###############################
# significant data
#	data in region where rpm affects hover height

# 1. Data for inc/dec rpm is not symmetric, 
#   height on deceleration doesn't match up with initial acceleration values, 
#	probably because we held hdk to keep it from scuffing engines 
#	in the event rpm given is insufficient for it to hover.
first_ramp_up = []
i = 1
while csv_data[i][2] != 248: 
	first_ramp_up.append(csv_data[i])
	i += 1
first_ramp_pulse_width = [item[2] for item in first_ramp_up]
first_ramp_avg_laser = [item[6] for item in first_ramp_up]

# 2. Hover height appears to have no dependence on rpm beyond a pulse width of ~199, 
#   only apply fit to values below 200.
significant_data = []
i = 0
while first_ramp_up[i][2] < 200: 
	significant_data.append(first_ramp_up[i])
	i += 1

# Polynomial fit for the relevant pulse width values
fit = np.polyfit([item[2] for item in significant_data], [item[6] for item in significant_data], 2) # 2nd order polynonmial fit for avg laser measurement vs pulse width to hover engines
p = np.poly1d(fit)

# Print significant data and polyfit constants, for reference
print("sig data: %s" % (significant_data))
print("polyfit coeffs: %s" % fit)

# significant data
sig_rpm_pulse_width = [item[2] for item in significant_data]
sig_avg_laser = [item[6] for item in significant_data]

# Plot significant data and fit line
plt.subplot(313)
plt.scatter(first_ramp_pulse_width, first_ramp_avg_laser, color='r', s=25)
plt.plot(sig_rpm_pulse_width, p(sig_rpm_pulse_width))
plt.xlabel('RPM Pulse Width')
plt.ylabel('Avg Laser Distance Measurement')
plt.title("RPM Pulse Width vs Avg Laser Distance Measurement")
plt.show()




"""
$ data_analysis_2108.py

sig data: [[18, 0.4375, 173, 338, 384, 346, 356.0], [19, 0.3125, 174, 343, 385, 341, 356.33333333333331], [20, 0.25, 175, 339, 388, 348, 358.33333333333331], [21, 0.375, 176, 347, 400, 348, 365.0], [22, 0.25, 177, 352, 400, 353, 368.33333333333331], [23, 0.25, 178, 358, 411, 360, 376.33333333333331], [24, 0.375, 179, 370, 418, 367, 385.0], [25, 0.375, 180, 365, 409, 369, 381.0], [26, 0.375, 181, 362, 416, 369, 382.33333333333331], [28, 0.4375, 182, 370, 413, 367, 383.33333333333331], [29, 0.4375, 183, 369, 420, 372, 387.0], [30, 0.4375, 184, 376, 424, 377, 392.33333333333331], [31, 0.5, 185, 377, 421, 378, 392.0], [32, 0.5625, 186, 382, 422, 377, 393.66666666666669], [33, 0.5625, 187, 377, 428, 387, 397.33333333333331], [34, 0.5625, 188, 382, 429, 383, 398.0], [35, 0.5625, 189, 387, 436, 386, 403.0], [36, 0.5625, 190, 387, 436, 390, 404.33333333333331], [37, 0.6875, 191, 388, 439, 390, 405.66666666666669], [38, 0.6875, 192, 391, 439, 392, 407.33333333333331], [39, 0.75, 193, 397, 446, 393, 412.0], [40, 0.75, 194, 396, 447, 395, 412.66666666666669], [41, 0.6875, 195, 396, 448, 397, 413.66666666666669], [42, 0.625, 196, 396, 444, 401, 413.66666666666669], [43, 1.125, 197, 399, 447, 400, 415.33333333333331], [44, 1.0, 198, 397, 448, 401, 415.33333333333331], [45, 0.6875, 199, 399, 448, 402, 416.33333333333331]]
polyfit coeffs: [ -6.06556917e-02   2.49552482e+01  -2.14726813e+03]
[Finished in 1.8s]

"""