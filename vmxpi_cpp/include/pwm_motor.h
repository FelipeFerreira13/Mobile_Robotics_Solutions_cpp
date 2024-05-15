#pragma once

#include "VMXPi.h"
#include <thread>
#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include <unistd.h>
#include <sys/syscall.h>

#include "hardware_interface_vmxpi.h"

class PWM_Motor_hardware{
	public:
		VMXIO *io; // IO class of VMXPi
		VMXErrorCode vmxerr;
		VMXPi *vmx;

		VMXResourceHandle pwmgen_res_handle_a;
		VMXResourcePortIndex res_port_index_a;

		VMXResourceHandle pwmgen_res_handle_b;
		VMXResourcePortIndex res_port_index_b;
};

class PWM_Motor : PWM_Motor_hardware{
	private:	    
		uint8_t INA;
		uint8_t INB;
		
		double duty_cycle_ = 0;
       
	public:
		PWM_Motor();
        void Init( int INA, int INB);
    	~PWM_Motor();
		
		// set a pwm from -1 to 1
		bool SetMotorPWM(double pwm); 
};