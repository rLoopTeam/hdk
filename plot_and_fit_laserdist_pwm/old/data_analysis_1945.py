# data analysis
# 	Fitting data of average laser distance measured vs pulse width sent to control hdk engine rpm's.

import csv, numpy as np, matplotlib.pyplot as plt

filename = "../data_read_and_plot/1945.csv"
with open(filename, 'r') as csv_file:
	csv_data = csv.reader(csv_file)
	csv_data = [i[:-1] for i in csv_data] # last item in each data point is empty due to main.go syntax

def Change_Data_Types(csv_data):
	"""change data types from strings to int/float"""
	csv_data_reformat = []
	csv_data_reformat.append(csv_data[0]) # zero index contains column titles (e.g. 'BNO', 'Laser1'), which should be left as strings
	for item in csv_data[2:]: # first data point wonky
		new_item = []
		for j in range(len(item)):
			new_item.append(int(item[j]))
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
rpm_pulse_width = [item[0] for item in csv_data][1:]
avg_laser = [item[-1] for item in csv_data][2:]

x = np.arange(len(avg_laser))

# Plot raw data 
plt.subplot(311)
plt.scatter(x, avg_laser, color='r', s=25)
plt.ylabel('Avg Laser Distance Measurement')
plt.title("Avg Laser Distance Measurement")

###############################
# significant data
#	data in region where rpm affects hover height

# 1. Data for inc/dec rpm is not symmetric, 
#   height on deceleration doesn't match up with initial acceleration values, 
#	probably because we held hdk to keep it from scuffing engines 
#	in the event rpm given is insufficient for it to hover.
first_ramp_up = []
i = 2
while csv_data[i][0] != 248: 
	first_ramp_up.append(csv_data[i])
	i += 1
first_ramp_pulse_width = [item[0] for item in first_ramp_up]
first_ramp_avg_laser = [item[-1] for item in first_ramp_up]

# 2. Hover height appears to have no dependence on rpm beyond a pulse width of ~199, 
#   only apply fit to values below 200.
significant_data = []
i = 0
while first_ramp_up[i][0] < 200: 
	significant_data.append(first_ramp_up[i])
	i += 1

# Polynomial fit for the relevant pulse width values
fit = np.polyfit([item[0] for item in significant_data], [item[-1] for item in significant_data], 2) # 2nd order polynonmial fit for avg laser measurement vs pulse width to hover engines
p = np.poly1d(fit)

# Print significant data and polyfit constants, for reference
print("sig data: %s" % (significant_data))
print("polyfit coeffs: %s" % fit)

# significant data
sig_rpm_pulse_width = [item[0] for item in significant_data]
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
$ data_analysis_1945.py

sig data: [[162, 291, 319, 219, 276.33333333333331], [163, 287, 323, 292, 300.66666666666669], [164, 301, 337, 289, 309.0], [165, 303, 343, 306, 317.33333333333331], [166, 310, 350, 300, 320.0], [167, 312, 352, 305, 323.0], [168, 321, 362, 311, 331.33333333333331], [169, 322, 369, 322, 337.66666666666669], [180, 366, 420, 368, 384.66666666666669], [181, 368, 419, 370, 385.66666666666669], [182, 374, 428, 373, 391.66666666666669], [183, 378, 423, 372, 391.0], [184, 376, 429, 372, 392.33333333333331], [185, 380, 426, 377, 394.33333333333331], [186, 379, 435, 385, 399.66666666666669], [187, 387, 436, 385, 402.66666666666669], [188, 390, 436, 387, 404.33333333333331], [189, 390, 440, 389, 406.33333333333331], [190, 390, 442, 391, 407.66666666666669], [191, 392, 442, 394, 409.33333333333331], [192, 396, 448, 395, 413.0], [193, 398, 450, 394, 414.0], [194, 397, 457, 398, 417.33333333333331], [195, 397, 449, 406, 417.33333333333331], [196, 402, 453, 404, 419.66666666666669], [197, 403, 458, 405, 422.0], [198, 401, 456, 406, 421.0], [199, 404, 458, 407, 423.0]]
polyfit coeffs: [ -7.92695214e-02   3.20787842e+01  -2.82360939e+03]
[Finished in 28.5s]
"""