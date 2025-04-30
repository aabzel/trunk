

Fsignal = 10.0
Fsample_rate = 16000
atten = 0.1


import matplotlib.pyplot as plt
import math
import numpy as np


M = np.arange(1, 10000, 1)
Zeros=np.sin(math.pi*M*2*Fsignal/Fsample_rate)-atten*M*np.sin(math.pi*2*Fsignal/Fsample_rate)


print ('Fsignal {} V'.format(Fsignal))



plt.plot(M, Zeros, label="Uout")
#plt.plot(f_hz, Frequency_response, label="Uout")
plt.title('RCR filter Frequency response')
plt.xlabel('Order,[M]')
plt.ylabel('Zeros')
plt.grid()
#plt.xticks(rotation=-90)
#plt.legend(['code','Signal', 'I','I_filtered'])
plt.show()

