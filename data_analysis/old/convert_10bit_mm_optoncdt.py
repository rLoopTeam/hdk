import numpy as np, matplotlib.pyplot as plt

a = sorted([602,890,495, 300, 425, 416, 543, 655, 785, 761, 898, 996, 1023])
b = sorted([49, 61,  40.5,35,  40,  40,  45,  50,  55,  55,  60,  65, 70])

fit = np.polyfit(a,b,1)
p = np.poly1d(fit)

plt.scatter(a,b)
plt.plot(a, p(a))
plt.show()

print("polyfit coeffs: %s" % fit)

"""
$ convert_10bit_mm_optoncdt.py
polyfit coeffs: [  0.05407716  14.6819392 ]

# without clipped data points
polyfit coeffs: [  0.04584026  20.20076731]

"""



# analog circuit on teensy board does not accurately convert 4-20mA signal to 0-5V

"""
35	300
40 	416, 425
45 	543
50	655
55	785, 761
60 	898
65 	996
70 	1023
75 	1023
89 	1023
85	1023
"""
