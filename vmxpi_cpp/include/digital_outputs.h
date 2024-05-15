#pragma once

#include "VMXPi.h"
#include <stdio.h> 
#include <string.h> 
#include <inttypes.h>

#include "hardware_interface_vmxpi.h"

class digitalOutput_hardware {
	public:
		VMXIO *io; 
		VMXErrorCode vmxerr;
		VMXPi *vmx;
		VMXResourceHandle digitalout_res_handle;
};

class digitalOutput : digitalOutput_hardware {
	private:

		int channel_index;
		
	public:
		digitalOutput();
		void Init( int channel );
        ~digitalOutput();
		
		// set the state of the pin duration
		void SetPinState( bool state );
	
};