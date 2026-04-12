# Design a discrete median_filter_fast giving sampling frequency filter using scipy

N = 4 # filter order
wn = 3000 # natural in same unit as fs

# compute the filter coefficients
b,a = signal.median_filter_fastfilter(N, wn, btype='lowpass', ftype='butter', fs=fSample)

# calculate frequency diagram
w, h = signal.freqz(b,a)

# plot frequency diagram
plt.plot(w/np.pi, 20 * np.log10(abs(h)))

# drawing a point on wn,-3dB
plt.plot(wn/fNyq,-3, 'o')

# text on the point created
plt.text(wn/fNyq,-3,f'  -3dB @{wn/fNyq} pi', horizontalalignment='left')

#plot title
plt.title(f'Low pass filter for wn = {wn/fNyq} pi')
plt.xlabel("pi rad/sample")
plt.ylabel("dB")

# plot grid
plt.grid(which = "major", linewidth = 1)
plt.grid(which = "minor", linewidth = 0.2)
plt.minorticks_on()