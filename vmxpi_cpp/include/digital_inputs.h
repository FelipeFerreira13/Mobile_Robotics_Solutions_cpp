#pragma once

#include "VMXPi.h"
#include <stdio.h>  
#include <string.h> 
#include <inttypes.h>

#include "hardware_interface_vmxpi.h"

class digitalInput_hardware{
	public:
		VMXIO *io;
        VMXErrorCode vmxerr;
		VMXPi *vmx;
		VMXResourceHandle digitalio_res_handle;
};

class digitalInput : digitalInput_hardware{
	private:
		int dio_channel_index;

	public:
		digitalInput();
		void Init( int channel);
		~digitalInput();
		
		bool Get();	
};

