import numpy as np
import matplotlib.pyplot as plt
from scipy . stats import chi2

def chisq_flat(binned_data: np.ndarray):
    mean = np.sum(binned_data) / binned_data.size
    return np.sum((binned_data - mean) ** 2 / mean)

MT = np.loadtxt('MT_arr.txt')
LCG = np.loadtxt('lcg_arr.txt')
PM = np.loadtxt('pm_arr.txt')
QCG = np.loadtxt('qcg_arr.txt')

binsl = 100
binsw = 1.0/100

k = binsl -1
runs = 10
points = 1e6

bins = np.empty(100)
for i in range(100):
    bins[i] = i*binsw

# Chi-squared distribution values from table for k = 99
# alpha1 = 0.1
# alpha2 = 0.05
p1_up = 117.407
p2_up = 123.225
p1_low = 81.449
p2_low = 77.046






hist_mt , bins_mt = np.histogram(MT ,bins)
hist_lcg , bins_lcg = np.histogram(LCG ,bins)
hist_pm , bins_pm = np.histogram(PM ,bins)
hist_qcg , bins_qcg = np.histogram(QCG ,bins)
chisqs = np.empty((runs,))
for i_run in range(runs):
    hist, bin_edges = np.histogram(MT, bins=binsl, range=(0, 1))
    chisq = chisq_flat(hist)
    chisqs[i_run] = chisq

print("Expected median:", k*(1 - 2/(9*k))**3)
print("mean chisq:", np.mean(chisqs))
print("median chisq:", np.median(chisqs))



fig = plt.figure(figsize=(20,5))

ax1 = fig.add_subplot(141)
ax2 = fig.add_subplot(142)
ax3 = fig.add_subplot(143)
ax4 = fig.add_subplot(144)


ax1.hist(MT, bins)
ax1.set_title('MT')
ax2.hist(LCG, bins)
ax2.set_title('LCG')
ax3.hist(PM, bins)
ax3.set_title('PM')
ax4.hist(QCG, bins)
ax4.set_title('QCG')

value_real = np.empty(99) #expected freqs in each bin for 1e6 points, 100 bins, uniform dist

for i in range(99):
    value_real[i] = len(MT)/binsl

chi2_mt = sum (( value_real - hist_mt )**2/ hist_mt )
chi2_lcg = sum (( value_real - hist_lcg )**2/ hist_lcg )
chi2_pm = sum (( value_real - hist_pm )**2/ hist_pm )
chi2_qcg = sum (( value_real - hist_qcg )**2/ hist_qcg )

print ('chi ^2 for MT :', chi2_mt )
print ('chi ^2 for LCG :', chi2_lcg )
print ('chi ^2 for PM :', chi2_pm )
print ('chi ^2 for QCG :', chi2_qcg )

fig = plt.figure(figsize=(20,5))
ax = fig.add_subplot(121)
counts, bins, patches = ax.hist(chisqs)
ax.set_title('MT')
ax.set_xlabel(r"$\chi^2$")
ax.set_ylabel("Occurrences")

plt.show()