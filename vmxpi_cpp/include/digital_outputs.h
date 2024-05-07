#pragma once

#include "VMXPi.h"
#include <stdio.h>  /* printf() */
#include <string.h> /* memcpy() */
#include <inttypes.h>

class digitalOutput {
	private:
		VMXIO *io; // IO class of the VMXPi
        VMXErrorCode vmxerr;
		VMXPi *vmx;
		uint8_t channel_index;
		
		VMXResourceHandle digitalout_res_handle;

	public:
		digitalOutput(VMXPi *vmx, uint8_t channel);
        ~digitalOutput();
		
		// set the state of the pin duration
		void SetPinState( bool state );

        void DisplayVMXError(VMXErrorCode vmxerr);
		
};