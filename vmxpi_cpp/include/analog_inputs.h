#pragma once

#include "VMXPi.h"
#include "math.h"
#include <thread>
#include <unistd.h>
#include <sys/syscall.h>

class Analog {
	private:
		VMXIO *io; // IO class of VMXPi
		VMXResourceHandle accumulator_res_handle;
		uint8_t analog_in_chan_index;
        VMXErrorCode vmxerr;
		VMXPi *vmx;

    
	public:
		// specify channel input
		Analog();
		void Init(VMXPi *vmx, uint8_t channel);
    	~Analog();
		double GetIRDistance(); // get distance in cm
		double GetRawVoltage(); // get raw voltage

        void DisplayVMXError(VMXErrorCode vmxerr);	
};