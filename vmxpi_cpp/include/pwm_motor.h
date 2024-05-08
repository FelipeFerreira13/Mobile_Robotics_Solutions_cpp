#pragma once

#include "VMXPi.h"
#include <thread>
#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include <unistd.h>
#include <sys/syscall.h>

class PWM_Motor {
	private:
		VMXIO *io; // IO class of VMXPi
		VMXErrorCode vmxerr;
		VMXPi *vmx;

		VMXResourceHandle pwmgen_res_handle_a;
		VMXResourcePortIndex res_port_index_a;

		VMXResourceHandle pwmgen_res_handle_b;
		VMXResourcePortIndex res_port_index_b;
		    
		uint8_t INA;
		uint8_t INB;
		
		double duty_cycle_ = 0;
       
	public:
        void Init( VMXPi *vmx, int INA, int INB);
		PWM_Motor();
    	~PWM_Motor();
		
		// set a pwm from -1 to 1
		bool SetMotorPWM(double pwm); 
 
		void DisplayVMXError(VMXErrorCode vmxerr);
};