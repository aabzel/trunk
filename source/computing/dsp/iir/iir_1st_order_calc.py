import matplotlib.pyplot as plt
import math
import numpy as np

freq_a_hz = 48000
freq_calc = freq_a_hz/2

'''
#Feed Forward
A = np.array([  
        0.00000000001785336951,
        0.00000000008926684755,
        0.00000000017853369510,
        0.00000000017853369510,
        0.00000000008926684755,
        0.00000000001785336951

        ])
#Feed Back
B = np.array([      
        1.00000000000000000000,
        -4.94580510978888640000,
        9.78458861225242060000,
        -9.67891547624729400000,
        4.78728571419223670000,
        -0.94715373983704532000
        ])
'''
        
A = np.array([  
        0.150,
        0.000
        ])

#Feed Back
B = np.array([      
        0.00,
        0,85
        ])
 

freq_hz = np.arange(2, freq_calc, 1)

def Z_n(N,f,Fs):
   T_a = 1.0/Fs
   omega = (2.0 * np.pi)*f
   #exp_val=np.exp(-1j*N*omega) 
   exp_val=np.cos(-N*omega*T_a) - (0+1j)*np.sin(-N*omega*T_a) 
   return exp_val

def CalcFreqResp(A,B,freq_s_hz):
    print ('A Type  {}  Nums{}'.format(type(A),len(A)))
    Amp = np.array([])
    for f in range(len(freq_hz)):
        numenator = 0
        denominator = 1
        
        for n in range(len(A)):
            forward = Z_n(n,f,freq_s_hz)*A[n]
            numenator = numenator+forward
        for n in range(len(B)):
            if n!=0:
                back = Z_n(n,f,freq_s_hz)*B[n]
                denominator =  denominator - back

        element =  np.absolute(numenator/denominator)
        Amp = np.append(Amp, element)
    return Amp


Amp1 = CalcFreqResp(A,B,freq_a_hz )
Amp2 = CalcFreqResp(B,A,freq_a_hz )
 
#Amp2 = CalcFreqResp(a2_0,b2_1,freq_a_hz )


print ('Amp1 {} Nums'.format(len(Amp1)))
print ('freq_hz {} Nums'.format(len(freq_hz)))
 

print ('Type Amp1 {} '.format(type(Amp1)))
print ('Type freq_hz {} '.format(type(freq_hz)))


plt.title("amplitude")
plt.grid(True)
plt.ylabel('Amplitude')
plt.xlabel('freq, [Hz]')
plt.plot(freq_hz, Amp1,'r')
plt.plot(freq_hz, Amp2,'b')
#plt.plot(freq_hz, Amp2,'b', label='a0={:4.4f}, b1={:4.4f}'.format(a2_0,b2_1))
plt.legend()
#plt.xscale('log')
plt.show()
        
        