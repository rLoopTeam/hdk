# data analysis
# 	Fitting data of average laser distance measured vs pulse width sent to control hdk engine rpm's.

# TODO: import all csv's into this file

import os, csv, numpy as np, matplotlib.pyplot as plt

filename = "../data_read_and_plot/2004.csv"

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
for item in csv_data[2:]:
	laser_data = tuple(item[-3:])
	item.append(np.mean(laser_data))

###############################
# raw data
rpm_pulse_width = [item[0] for item in csv_data][2:]
avg_laser = [item[-1] for item in csv_data][2:]

x = np.arange(len(avg_laser))

# Plot raw data 
plt.subplot(311)
plt.scatter(x, avg_laser, color='r', s=25)
plt.ylabel('Avg Laser Distance Measurement')
plt.title("Avg Laser Distance Measurement")

###############################
# significant data set
#	data in region where a change in rpm affects hover height, 
#	pulse width <200; plateaus beyond there

significant_data = [item for item in csv_data[2:] if item[0] < 200]

fit = np.polyfit([item[0] for item in significant_data], [item[-1] for item in significant_data], 2)
p = np.poly1d(fit)

print("sig data: %s" % (significant_data))
print("polyfit coeffs: %s" % fit)

# Plot significant data and fit line
plt.subplot(313) # (row col num), skip 312 for spacing
plt.scatter([item[0] for item in significant_data], [item[-1] for item in significant_data], color='r', s=25)
plt.plot([item[0] for item in significant_data], p([item[0] for item in significant_data]))
plt.xlabel('RPM Pulse Width')
plt.ylabel('Avg Laser Distance Measurement')
plt.title("RPM Pulse Width vs Avg Laser Distance Measurement")
plt.show()







"""
$ data_analysis_2004.py

sig data: [[173, 344, 384, 345, 357.66666666666669], [174, 348, 393, 342, 361.0], [175, 345, 393, 350, 362.66666666666669], [176, 354, 408, 360, 374.0], [177, 357, 406, 356, 373.0], [178, 360, 408, 361, 376.33333333333331], [179, 367, 418, 361, 382.0], [180, 369, 419, 363, 383.66666666666669], [181, 367, 418, 367, 384.0], [182, 375, 419, 372, 388.66666666666669], [183, 374, 424, 372, 390.0], [184, 376, 426, 381, 394.33333333333331], [185, 380, 432, 383, 398.33333333333331], [186, 381, 433, 382, 398.66666666666669], [187, 384, 431, 386, 400.33333333333331], [188, 384, 438, 388, 403.33333333333331], [189, 385, 439, 389, 404.33333333333331], [190, 388, 439, 392, 406.33333333333331], [191, 388, 440, 396, 408.0], [192, 389, 447, 390, 408.66666666666669], [193, 392, 445, 395, 410.66666666666669], [194, 394, 445, 399, 412.66666666666669], [195, 395, 451, 401, 415.66666666666669], [196, 396, 456, 401, 417.66666666666669], [197, 400, 454, 405, 419.66666666666669], [198, 401, 456, 407, 421.33333333333331], [199, 400, 457, 403, 420.0]]
polyfit coeffs: [ -5.28440908e-02   2.20249126e+01  -1.86993741e+03]
[Finished in 2.4s]
"""