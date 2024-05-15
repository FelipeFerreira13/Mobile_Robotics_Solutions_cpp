#include "pwm_motor.h"

PWM_Motor::PWM_Motor( ){}

void PWM_Motor::Init(int INA, int INB){
    this->vmx = vmx_ptr;
    try {
		if(vmx->IsOpen()) {
			if( INA < 22 && INA > 11 && INB < 22 && INB > 11 ){
    
                PWMGeneratorConfig pwmgen_cfg(1000 /* Frequency in Hz */);

                int dio_channel_index = INA;

                if (!vmx->io.ActivateSinglechannelResource(VMXChannelInfo(dio_channel_index, VMXChannelCapability::PWMGeneratorOutput), &pwmgen_cfg, 
                        pwmgen_res_handle_a, &vmxerr)) {
                    printf("Error Activating Singlechannel Resource PWM Generator for Channel index %d.\n", dio_channel_index);
                    DisplayVMXError(vmxerr);

                } else {
                    printf("Successfully Activated PWMGenerator Resource %d with VMXChannel %d\n", EXTRACT_VMX_RESOURCE_INDEX(pwmgen_res_handle_a), dio_channel_index);
                    if (!vmx->io.PWMGenerator_SetDutyCycle(pwmgen_res_handle_a, res_port_index_a, 50, &vmxerr)) {
                        printf("Failed to set DutyCycle for PWMGenerator Resource %d, Port %d.\n", EXTRACT_VMX_RESOURCE_INDEX(pwmgen_res_handle_a), res_port_index_a);
                        DisplayVMXError(vmxerr);
                    }
                }

                dio_channel_index = INB;
                
                if (!vmx->io.ActivateSinglechannelResource(VMXChannelInfo(dio_channel_index, VMXChannelCapability::PWMGeneratorOutput), &pwmgen_cfg, 
                        pwmgen_res_handle_b, &vmxerr)) {
                    printf("Error Activating Singlechannel Resource PWM Generator for Channel index %d.\n", dio_channel_index);
                    DisplayVMXError(vmxerr);

                } else {
                    printf("Successfully Activated PWMGenerator Resource %d with VMXChannel %d\n", EXTRACT_VMX_RESOURCE_INDEX(pwmgen_res_handle_b), dio_channel_index);
                    if (!vmx->io.PWMGenerator_SetDutyCycle(pwmgen_res_handle_b, res_port_index_b, 50, &vmxerr)) {
                        printf("Failed to set DutyCycle for PWMGenerator Resource %d, Port %d.\n", EXTRACT_VMX_RESOURCE_INDEX(pwmgen_res_handle_b), res_port_index_b);
                        DisplayVMXError(vmxerr);
                    }
                }
            }else{
				printf("Invalid Analog input channel (12-21)\n");
            }
		} else { printf("Error:  Unable to open VMX Client.\n"); }
	}
	catch(const std::exception& ex){
		printf("Caught exception:  %s", ex.what());
	}
}

PWM_Motor::~PWM_Motor(){
    if (!INVALID_VMX_RESOURCE_HANDLE(pwmgen_res_handle_a)) {
        if (!vmx->io.DeallocateResource(pwmgen_res_handle_a, &vmxerr)) {
            printf("Error Deallocating PWM Resource.\n");
        } else {
            printf("Successfully Deallocated PWM Resource Index %d\n", EXTRACT_VMX_RESOURCE_INDEX(pwmgen_res_handle_a));
        }
    }
    if (!INVALID_VMX_RESOURCE_HANDLE(pwmgen_res_handle_b)) {
        if (!vmx->io.DeallocateResource(pwmgen_res_handle_b, &vmxerr)) {
            printf("Error Deallocating PWM Resource.\n");
        } else {
            printf("Successfully Deallocated PWM Resource Index %d\n", EXTRACT_VMX_RESOURCE_INDEX(pwmgen_res_handle_b));
        }
    }
}


bool PWM_Motor::SetMotorPWM( double pwm ){
    // printf("duty_cycle set to %f \n", pwm);

    double duty_cycle = ( abs(pwm) * 255.0 );

    int ina = 0, inb = 0;

    if ( pwm > 0 )      { ina = duty_cycle; inb = 0;          }
    else if ( pwm < 0 ) { ina = 0;          inb = duty_cycle; }
    else if ( pwm == 0 ){ ina = 255;        inb = 255;        }

    if (!vmx->io.PWMGenerator_SetDutyCycle(pwmgen_res_handle_a, res_port_index_a, ina, &vmxerr)) {
        printf("Failed to set DutyCycle for PWMGenerator Resource %d, Port %d.\n", EXTRACT_VMX_RESOURCE_INDEX(pwmgen_res_handle_a), res_port_index_a);
        DisplayVMXError(vmxerr);
        return false;
    }
        if (!vmx->io.PWMGenerator_SetDutyCycle(pwmgen_res_handle_b, res_port_index_b, inb, &vmxerr)) {
        printf("Failed to set DutyCycle for PWMGenerator Resource %d, Port %d.\n", EXTRACT_VMX_RESOURCE_INDEX(pwmgen_res_handle_b), res_port_index_b);
        DisplayVMXError(vmxerr);
        return false;
    }

    duty_cycle_ = duty_cycle;
    return true;
}



