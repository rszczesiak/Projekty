from matplotlib import pyplot as plt
from matplotlib import style
from matplotlib.ticker import FuncFormatter
import numpy as np
import pandas as pd
import pylab
import sys
import os
import math
import scipy.stats as sp
from scipy.ndimage.filters import gaussian_filter

file = sys.argv[1]
# file = r'..\0_1.CSV'
specname = os.path.basename(file).split('.')[0]  # specimen name
style.use('seaborn-bright')

# specimen dimensions
H = 4
B = 10

# read data from CSV file
my_data = pd.read_csv(file, delimiter=';', decimal=',', header=None, skiprows=22, usecols=[0, 5], names=[0, 1])
my_eps = pd.read_csv(r'..\GOM\%s.CSV' % specname, delimiter=';', decimal='.', header=None, skiprows=1,
                     names=[0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10])
for i in range(1, 10):
    for j in range(0, len(my_eps[i])):
        if math.isnan(my_eps[i][j]):
            my_eps = my_eps[0:j]
            break
xd = my_eps[1]
yd = my_data[1]

# take average of five extensometers
for i in range(0, len(xd)):
    for j in range(2, 5):
        xd[i] += my_eps[j][i]
    xd[i] /= 5

# filter strain and load data
xd = gaussian_filter(xd, 5)
xd = pd.Series(xd)
yd = gaussian_filter(yd, 5)
yd = pd.Series(yd)

# if strain is less than 0.05%, then remove the data point to prevent noise impact the results
for i in range(0, len(xd)):
    if xd[i] <= .05:
        xd.pop(i)
        if 'index_list' in dir():
            index_list.append(i)
        else:
            index_list = [i]
my_eps.drop(my_eps.index[index_list], inplace=True)

# rearrange vector indices
xd = xd.reset_index(drop=True)
my_eps = my_eps.reset_index(drop=True)

# if strain between previous and next data point drops more than 0.005% of max. strain, then truncate the remaining data
for i in range(1, len(xd)):
    if (abs(xd[i - 1] - xd[i])) > .005 * max(abs(xd)):
        xd = xd[0:i]
        my_eps = my_eps[0:i]
        break

# if load is less than 0.004 kN, then remove the data point to prevent noise impact the results
for i in range(0, len(yd)):
    if yd[i] <= 0.004:
        yd.pop(i)

# rearrange vector indices
yd = yd.reset_index(drop=True)

# if load between previous and next data point drops more than 0.05% of max. load, then truncate the remaining data
for i in range(1, len(yd)):
    if yd[i - 1] - yd[i] > .0005 * max(yd):
        yd = yd[0:i]
        break

# rearrange vector indices
yd = yd.reset_index(drop=True)

# interpolate yd list
yd = np.interp(np.linspace(0, 1, len(xd)), np.linspace(0, 1, len(yd)), yd)
yd = pd.Series(yd)

nu = my_eps[6]

# take average of five extensometers and calculate nu
for i in range(0, len(nu)):
    for j in range(7, 10):
        nu[i] += my_eps[j][i]
    nu[i] /= -xd[i]
    nu[i] /= 5

# filter strain and load data
nu = gaussian_filter(nu, 5)
nu = pd.Series(nu)

for i in range(0, len(xd)):
    yd[i] /= (H * B / 1000)  # calculate nominal tensile stress
    xd[i] /= 100  # percents to units

# plot preview
# print(np.mean(nu))
# plt.plot(my_eps[0], nu)
# plt.show()

# set R^2 to 0 and initial set of experimental points to 10 and iterate trough the experimental data until R^2 is not
# less than 0.9925 or until no data is left to fit he regression line
Rsqr = 0
limit = 100
while Rsqr < .995 and limit <= len(xd):
    slope, intercept, r_value, p_value, std_err = sp.linregress(xd[0:limit], yd[0:limit])
    Rsqr = r_value ** 2
    limit += 1  # loop counter
limit -= 2

# iterate trough experimental data to find yield strength Rp0.2 using previously derived tangent line
for i in range(0, len(xd)):
    if (yd[i] - slope * (xd[i] - xd[0] - .002) - yd[0]) < .001 * max(yd):  # if residuum equals 0.1% of max. stress
        Rp = yd[i]
        break
    else:
        Rp = 0  # if no Rp0.2 found, then set to 0 to prevent printing error

# strictly tangent line section
xt = [xd[0], xd[limit]]
yt = [slope * xx + intercept for xx in xt]

# extend regression line to make it more visible -- 10% of max. stress as a difference to distinguish plots
for i in range(0, len(xd)):
    xl = [xd[0], xd[i]]
    yl = [slope * xx + intercept for xx in xl]
    if yl[-1] - yd[i] > .1 * max(yd):
        break


def percent(x, pos):
    return '%0.2f' % (x * 100)


# plot formatting
formatter = FuncFormatter(percent)
fig, ax = plt.subplots()
ax.xaxis.set_major_formatter(formatter)
plt.xlabel("Strain [%]")
plt.ylabel("Stress [MPa]")
plt.axis((0, 1.1 * max(xd), 0, 1.1 * max(yd)))  # set plot axes limits
plt.title('Specimen: %s' % specname)

# plot results
plt.scatter(xd, yd, s=1, alpha=0.15, marker='x', c='k')  # make the scatter plot
plt.plot(xl, yl, '-b')  # plot extended tangent line
plt.plot(xt, yt, '--r')  # plot strictly tangent line section

# print statistics and mechanical derived properties
plt.text(.05 * max(xd) + .95 * min(xd), 1 * max(yd) + .0 * min(yd), '$R^2 = %0.3f$' % Rsqr, fontsize=12)
plt.text(.65 * max(xd) + .35 * min(xd), .35 * max(yd) + .65 * min(yd), '$E_x = %0.2f$ GPa' % (slope / 1000),
         fontsize=12)
plt.text(.65 * max(xd) + .35 * min(xd), .25 * max(yd) + .75 * min(yd), '$R_m = %0.2f$ MPa' % max(yd), fontsize=12)
plt.text(.65 * max(xd) + .35 * min(xd), .15 * max(yd) + .85 * min(yd), '$R_{p0.2} = %0.2f$ MPa' % Rp, fontsize=12)
plt.text(.65 * max(xd) + .35 * min(xd), .05 * max(yd) + .95 * min(yd), '$e_t = %0.2f$ %%' % (max(xd) * 100),
         fontsize=12)

pylab.savefig(r'..\fig\%s.png' % specname)
# plt.show()
plt.close(fig)
