ADC Independent Modes

1) Single channel single conversion mode
	simplest ADC mode, we do single conversion of a single channel and stop after we complete it
		exmaple determine if a system should be stopped or not, lets say whether a system has passed a certain temperature
		it will end the operation and exit. 
		Start -> CHx -> Stop

2) multichannel single conversion mode
	used to convert multiple channels(up to 16 channels with different sampling times(microcontrollers allow to do these in
	different cycles)). 
		Start -> CHx ...  CHn -> Stop

3) single channel continous conversion mode
	used to convert a single channel continously, similar to a loop
	       Start -> Chx  ->
		      ^        |
		      |        |
		      |________|
		an example is continously measuing the temperature of a room to know whether to adjust it or not.

4) multichannel continous conversion mode
	Same thing as above but can be done with multiple channels(up to 16). You start from the beginning
		Start -> Chx ... Chn -> 
                      ^                |
                      |                |
                      |________________|
	
		Use example, you have a robotic arm and you want to check the status of each joint in that arm, so you check the chain
		of the joints one by one, return back and keep on doing it over and over again.

5) Injected conversion Mode
	use when conversion is triggered by an external event or a software. The injected group has a priority over other 
	regular groups

	ADC1 CH0 .. CH1 .   . CH2 .. CH3 ...
			  ^
			  | 
		         CH10

