
# https://youtu.be/3lNtav3CjM8?si=GnWTsXfnhxfEzaYF

sys_clk_hz = 100000000.0
apb1_clk_hz=50000000
apb2_clk_hz=50000000


timer1_tick_s = 1*10**(-6)
timer1_period_s = 100*10**(-3)

timer2_tick_s = 100*10**(-6)
timer2_period_s = 1000*10**(-3)

timer_apb1_clk_hz=apb1_clk_hz*2
timer_apb2_clk_hz=apb2_clk_hz*2

timer_apb1_clk_tick_s=1.0/timer_apb1_clk_hz
timer_apb2_clk_tick_s=1.0/timer_apb2_clk_hz

timer2_prescaler = timer2_tick_s/timer_apb1_clk_tick_s
timer2_period = timer2_period_s/ timer2_tick_s

timer1_prescaler = timer1_tick_s/timer_apb1_clk_tick_s
timer1_period = timer1_period_s/ timer1_tick_s
print ('timer1_prescaler :{} num, Period{} Num'.format(timer1_prescaler,timer1_period))
print ('timer2_prescaler :{} num, Period{} Num'.format(timer2_prescaler,timer2_period))
print ('sys_clk_hz Freq:{} Hz '.format(sys_clk_hz))


