#pragma once

#include "VMXPi.h"
#include <thread>
#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include <unistd.h>
#include <sys/syscall.h>

#include "hardware_interface_vmxpi.h"

class PWM_hardware{
	public:
		VMXIO *io; // IO class of VMXPi
		VMXErrorCode vmxerr;
		VMXPi *vmx;

		VMXResourceHandle pwmgen_res_handle;
		VMXResourcePortIndex res_port_index;
};

class PWM : PWM_hardware{
	private:    
    	double maxangle = 300, minangle = 0;
		// convert user's input of degrees into a value readable by the HAL
		double mapAngle(double angle); 
		int channel_index;
		
		double angle_ = 0;
       
	public:
		PWM();
		void Init( int channel);
    	~PWM();
		
		// set an angle between 0 and 300
		bool SetAngle(double angle); 
   		// get current angle
		double GetAngle(); 
		// get the servo's min angle
    	double GetMinAngle(); 
		// get the servo's max angle
    	double GetMaxAngle(); 
};