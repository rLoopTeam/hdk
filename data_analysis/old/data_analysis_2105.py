# data analysis
# 	Fitting data of average laser distance measured vs pulse width sent to control hdk engine rpm's.

import csv, numpy as np, matplotlib.pyplot as plt

filename = "../data_read_and_plot/2105.csv"
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
$ data_analysis_2105.py

sig data: [[18, 0.5625, 173, 339, 386, 339, 354.66666666666669], [19, 0.5625, 174, 340, 393, 347, 360.0], [20, 0.625, 175, 346, 397, 347, 363.33333333333331], [21, 0.6875, 176, 355, 406, 352, 371.0], [22, 0.6875, 177, 353, 409, 356, 372.66666666666669], [23, 0.6875, 178, 361, 416, 359, 378.66666666666669], [24, 0.75, 179, 362, 405, 359, 375.33333333333331], [25, 0.75, 180, 364, 410, 365, 379.66666666666669], [26, 0.75, 181, 367, 413, 374, 384.66666666666669], [28, 0.8125, 182, 374, 416, 372, 387.33333333333331], [29, 0.875, 183, 370, 422, 379, 390.33333333333331], [30, 0.875, 184, 372, 426, 384, 394.0], [31, 0.9375, 185, 376, 427, 381, 394.66666666666669], [32, 0.9375, 186, 378, 430, 387, 398.33333333333331], [33, 1.0625, 187, 381, 431, 385, 399.0], [34, 1.0625, 188, 384, 429, 386, 399.66666666666669], [35, 1.125, 189, 385, 437, 390, 404.0], [36, 1.0, 190, 387, 438, 390, 405.0], [37, 1.125, 191, 394, 439, 394, 409.0], [38, 1.1875, 192, 395, 447, 401, 414.33333333333331], [39, 1.1875, 193, 393, 450, 395, 412.66666666666669], [40, 1.1875, 194, 395, 449, 397, 413.66666666666669], [41, 1.1875, 195, 397, 450, 399, 415.33333333333331], [42, 1.1875, 196, 400, 452, 401, 417.66666666666669], [43, 1.375, 197, 401, 456, 401, 419.33333333333331], [44, 1.3125, 198, 401, 455, 403, 419.66666666666669], [45, 1.375, 199, 401, 457, 403, 420.33333333333331]]
polyfit coeffs: [ -5.27584803e-02   2.20893212e+01  -1.88557573e+03]
[Finished in 46.6s]

"""