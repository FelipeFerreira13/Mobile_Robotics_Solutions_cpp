#pragma once

#include "VMXPi.h"
#include <stdio.h>  
#include <string.h> 
#include <inttypes.h>

#include "hardware_interface_vmxpi.h"

class EncoderMotor_hardware{
	public:
		VMXIO *io;
        VMXErrorCode vmxerr;
		VMXPi *vmx;
        
		VMXResourceIndex encoder_index;
		VMXResourceHandle encoder_res_handle;
};

class EncoderMotor : EncoderMotor_hardware{
	private:
		int encoder_channel_index;

	public:
		EncoderMotor();
		void Init( int encoder );
		~EncoderMotor();
		
		int GetEncoderCount( );	
};