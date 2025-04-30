import matplotlib.pyplot as plt
import csv
import math
import numpy as np

# f1*cos(2*pi*f1*t)+f2*cos(2*pi*f2*t)=f1+f2
f2=770.0
f1=1477.0

Fs=48000
n=(f1+f2)/(2*(3*f2-f1))

print ('n {} '.format(n))
n=10
T1=2*n/(f1+f2)
T2=(n-0.5)/(f1-f2)
#T= 65.0*(10**(-3))  
T= 9968000.0* 10.0**(-9.0)
T_fs= 1.0/Fs 

print ('math.pi {} '.format(math.pi))

t = np.arange(0, T, T_fs)
Y1 = np.sin(t*2*math.pi*f1)
Y2 = np.sin(t*2*math.pi*f2)

Ydt = f1+f2
Yd=f1*np.cos(2*math.pi*f1*t)+f2*np.cos(2*math.pi*f2*t)-Ydt
Y =Y1+Y2

 
print ('Y {} Nums'.format(len(Y)))

#xx= np.arange(X[0], 20, X[-1])
#xxx= np.array(xx).tolist()
#yySin= np.array(ySin).tolist()

 

#print ('Type xx {} '.format(type(xx)))
#print ('Type xxx {} '.format(type(xxx)))
#print ('Type yySin {} '.format(type(yySin)))
print ('Type X {} '.format(type(t)))
 

#plt.plot(t, Y1)
#plt.plot(t, Y2)
plt.plot(t, Y)
#plt.plot(t, Yd)
plt.title('signal')
plt.xlabel('Time,[s]')
plt.ylabel('PCM, ')
plt.grid()
plt.xticks(rotation=-90)
plt.show()