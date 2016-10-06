# data analysis
# 	Fitting data of average laser distance measured vs pulse width sent to control hdk engine rpm's.

import csv, numpy as np, matplotlib.pyplot as plt

filename = "../data_read_and_plot/2046.csv"
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
avg_laser = [item[-1] for item in csv_data][1:]

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
first_ramp_avg_laser = [item[-1] for item in first_ramp_up]

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
sig_avg_laser = [item[-1] for item in significant_data]

# Plot significant data and fit line
plt.subplot(313)
plt.scatter(first_ramp_pulse_width, first_ramp_avg_laser, color='r', s=25)
plt.plot(sig_rpm_pulse_width, p(sig_rpm_pulse_width))
plt.xlabel('RPM Pulse Width')
plt.ylabel('Avg Laser Distance Measurement')
plt.title("RPM Pulse Width vs Avg Laser Distance Measurement")
plt.show()




"""
$ data_analysis_2046.py

sig data: [[18, 0.3125, 173, 339, 389, 352, 360.0], [19, 0.1875, 174, 347, 391, 348, 362.0], [20, 0.3125, 175, 352, 395, 353, 366.66666666666669], [21, 0.375, 176, 355, 404, 356, 371.66666666666669], [22, 0.25, 177, 354, 401, 361, 372.0], [23, 0.1875, 178, 359, 393, 363, 371.66666666666669], [24, 0.3125, 179, 361, 405, 386, 384.0], [25, 0.5, 180, 364, 410, 368, 380.66666666666669], [26, 0.375, 181, 372, 415, 373, 386.66666666666669], [28, 0.375, 182, 377, 414, 379, 390.0], [29, 0.4375, 183, 377, 412, 384, 391.0], [30, 0.5, 184, 381, 423, 378, 394.0], [31, 0.3125, 185, 382, 419, 387, 396.0], [32, 0.5, 186, 380, 427, 385, 397.33333333333331], [33, 0.5625, 187, 383, 426, 391, 400.0], [34, 0.625, 188, 387, 434, 395, 405.33333333333331], [35, 0.625, 189, 388, 426, 388, 400.66666666666669], [36, 0.625, 190, 389, 442, 396, 409.0], [37, 0.625, 191, 391, 432, 398, 407.0], [38, 0.8125, 192, 393, 442, 399, 411.33333333333331], [39, 0.9375, 193, 396, 447, 399, 414.0], [40, 0.75, 194, 398, 442, 407, 415.66666666666669], [41, 0.9375, 195, 397, 444, 406, 415.66666666666669], [42, 1.0625, 196, 399, 443, 407, 416.33333333333331], [43, 1.125, 197, 400, 457, 406, 421.0], [44, 1.0625, 198, 404, 455, 409, 422.66666666666669], [45, 1.125, 199, 401, 450, 410, 420.33333333333331]]
polyfit coeffs: [ -4.49342484e-02   1.91141973e+01  -1.60231511e+03]
[Finished in 63.9s]
"""