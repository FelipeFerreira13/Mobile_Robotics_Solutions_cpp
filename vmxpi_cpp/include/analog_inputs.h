#pragma once

#include "VMXPi.h"
#include "math.h"
#include <thread>
#include <unistd.h>
#include <sys/syscall.h>

#include "hardware_interface_vmxpi.h"

class Analog_hardware{
	public:
		VMXIO *io; // IO class of VMXPi
		VMXResourceHandle accumulator_res_handle;
        VMXErrorCode vmxerr;
		VMXPi *vmx;
};

class Analog : Analog_hardware {
	private:
		int16_t analog_in_chan_index;
    
	public:
		// specify channel input
		Analog();
		void Init( int channel);
    	~Analog();
		double GetIRDistance(); // get distance in cm
		double GetRawVoltage(); // get raw voltage
};

