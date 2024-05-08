#pragma once

#include "VMXPi.h"
#include <stdio.h>  
#include <string.h> 
#include <inttypes.h>

class EncoderMotor{
	private:
		VMXIO *io;
        VMXErrorCode vmxerr;
		VMXPi *vmx;
        
		VMXResourceIndex encoder_index;
		VMXResourceHandle encoder_res_handle;

	public:
		EncoderMotor();
		void Init(VMXPi *vmx, uint8_t encoder);
		~EncoderMotor();
		
		int GetEncoderCount( );
        void DisplayVMXError(VMXErrorCode vmxerr);
	
};