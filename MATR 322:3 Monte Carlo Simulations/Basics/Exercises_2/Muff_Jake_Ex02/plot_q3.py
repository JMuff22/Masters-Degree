import numpy as np
from  matplotlib import pyplot as plt
# Load in data file
data = np.loadtxt("lcg.dat")
data1 = np.loadtxt("pm.dat")
data2= np.loadtxt("rand.dat")
data3 = np.loadtxt("automersenne.dat")
data4 = np.loadtxt("lcgshuffle.dat")
# Make arrays containing x-axis and binding energies as function of A
x = data[:,0]
corr = data[:,1]
corr2 = data1[:,1]
corr3= data2[:,1]
corr4= data3[:,1]
corr5 = data4[:,1]

fig = plt.figure(figsize=(20,5))
ax1 = fig.add_subplot(151)
ax2 = fig.add_subplot(152)
ax3 = fig.add_subplot(153)
ax4 = fig.add_subplot(154)
ax5 = fig.add_subplot(155)

ax1.plot(x, corr)
ax1.set_title('LCG Autocorrelation')

ax2.plot(x,corr5)
ax2.set_title('LCG Shuffle Autocorrelation')

ax3.plot(x, corr2)
ax3.set_title('PM Autocorrelation')

ax4.plot(x, corr3)
ax4.set_title('rand Autocorrelation')

ax5.plot(x, corr4)
ax5.set_title('Mersenne Autocorrelation')


# plt.plot(x, corr3 ,'ro', x, corr4, 'b')
# plt.axis([0,100000,-0.03, 0.03])
# plt.xlabel(r'$d$')
# plt.ylabel(r'$C_d$')
# plt.title(r'autocorrelation function for RNG')
# plt.savefig('autocorr.pdf')
plt.show()