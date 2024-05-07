#pragma once

#include "VMXPi.h"
#include <stdio.h>  
#include <string.h> 
#include <inttypes.h>

class digitalInput{
	private:
		VMXIO *io;
        VMXErrorCode vmxerr;
		VMXPi *vmx;
		uint8_t dio_channel_index;
		VMXResourceHandle digitalio_res_handle;

	public:
		digitalInput(VMXPi *vmx, uint8_t channel);
		~digitalInput();
		
		bool Get();
        void DisplayVMXError(VMXErrorCode vmxerr);
	
};