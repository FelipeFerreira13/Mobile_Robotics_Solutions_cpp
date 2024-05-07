#pragma once

#include "VMXPi.h"
#include <thread>
#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include <unistd.h>
#include <sys/syscall.h>

class PWM {
	private:
		VMXIO *io; // IO class of VMXPi
		VMXErrorCode vmxerr;
		VMXPi *vmx;

		VMXResourceHandle pwmgen_res_handle;
		VMXResourcePortIndex res_port_index;
		    
    	double maxangle = 300, minangle = 0;
		// convert user's input of degrees into a value readable by the HAL
		uint16_t mapAngle(double angle); 
		uint8_t channel_index;
		
		double angle_ = 0;
       
	public:
		PWM( VMXPi *vmx, uint8_t channel);
    	~PWM();
		
		// set an angle between 0 and 300
		bool SetAngle(double angle); 
   		// get current angle
		double GetAngle(); 
		// get the servo's min angle
    	double GetMinAngle(); 
		// get the servo's max angle
    	double GetMaxAngle(); 

		void DisplayVMXError(VMXErrorCode vmxerr);
};