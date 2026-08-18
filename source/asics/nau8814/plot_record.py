import matplotlib.pyplot as plt
import csv
import sys

F_adc_hz = 48000.0

t_sample = 1.0/F_adc_hz
X = []
Y = []
corr = []

file_name=sys.argv[1] 
 

with open(file_name, 'r') as datafile:
    plotting = csv.reader(datafile, delimiter='|')
    for ROWS in plotting:
        X.append(float(ROWS[1])*t_sample)
        #X.append('{} {}'.format(ROWS[3], ROWS[4]))
        Y.append(float(ROWS[4]))

print ('X {} Nums'.format(len(X)))
print ('Y {} Nums'.format(len(Y)))
 

print ('Type X {} '.format(type(X)))
print ('Type Y {} '.format(type(Y)))


plt.plot(X, Y,label="ADC")
plt.legend(loc='best')

file_name = file_name.replace('csv', '_')
file_name = file_name.replace('.', '_')
file_name = file_name.replace('/', '_')
file_name = file_name.replace('__', '_')

plt.title('{}'.format(file_name))
plt.xticks(rotation=-90)
plt.xlabel('Time,[s]')
plt.ylabel('ADC, [sample]')
#plt.grid()

plt.savefig('{}.png'.format(file_name))
plt.show()
