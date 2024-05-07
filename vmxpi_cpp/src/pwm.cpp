#include "pwm.h"

void PWM::DisplayVMXError(VMXErrorCode vmxerr) {
	const char *p_err_description = GetVMXErrorString(vmxerr);
	printf("VMXError %d:  %s\n", vmxerr, p_err_description);
}

PWM::PWM( VMXPi *vmx, uint8_t channel){
    this->vmx = vmx;
    try {
		if(vmx->IsOpen()) {
			if( channel < 22 && channel > 11 ){
    
                PWMGeneratorConfig pwmgen_cfg(200 /* Frequency in Hz */);

                int dio_channel_index = channel;

                if (!vmx->io.ActivateSinglechannelResource(VMXChannelInfo(dio_channel_index, VMXChannelCapability::PWMGeneratorOutput), &pwmgen_cfg, 
                        pwmgen_res_handle, &vmxerr)) {
                    printf("Error Activating Singlechannel Resource PWM Generator for Channel index %d.\n", dio_channel_index);
                    DisplayVMXError(vmxerr);

                } else {
                    printf("Successfully Activated PWMGenerator Resource %d with VMXChannel %d\n", EXTRACT_VMX_RESOURCE_INDEX(pwmgen_res_handle), dio_channel_index);
                    if (!vmx->io.PWMGenerator_SetDutyCycle(pwmgen_res_handle, res_port_index, 0, &vmxerr)) {
                        printf("Failed to set DutyCycle for PWMGenerator Resource %d, Port %d.\n", EXTRACT_VMX_RESOURCE_INDEX(pwmgen_res_handle), res_port_index);
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

PWM::~PWM(){
    if (!INVALID_VMX_RESOURCE_HANDLE(pwmgen_res_handle)) {
        if (!vmx->io.DeallocateResource(pwmgen_res_handle, &vmxerr)) {
            printf("Error Deallocating PWM Resource.\n");
        } else {
            printf("Successfully Deallocated PWM Resource Index %d\n", EXTRACT_VMX_RESOURCE_INDEX(pwmgen_res_handle));
        }
    }
}

double PWM::GetAngle(){ return angle_; }

bool PWM::SetAngle( double angle ){
    printf("PWM set to %f \n", angle);
    if (!vmx->io.PWMGenerator_SetDutyCycle(pwmgen_res_handle, res_port_index, mapAngle(angle), &vmxerr)) {
        printf("Failed to set DutyCycle for PWMGenerator Resource %d, Port %d.\n", EXTRACT_VMX_RESOURCE_INDEX(pwmgen_res_handle), res_port_index);
        DisplayVMXError(vmxerr);

        return false;
    }
    angle_ = angle;
    return true;
}

double PWM::GetMinAngle(){ return minangle; }

double PWM::GetMaxAngle(){ return maxangle; } 


uint16_t PWM::mapAngle (double angle)
{

	/**
	 * 2.5% (5000) = 0.5ms 0 degrees (CW Full speed) Value to put 25
     * 7.5% (5000) = 1.5ms 0 degrees (Stopped) Value to put 375
     * 12.5% (5000) = 2.5ms 300 degrees (CCW Full speed) Value to put 125
    **/
   	//With the updated duty cycle range the accuracy is now 0.6 degrees per step

    if (angle == -1){ angle = angle_; }
    
    if (angle < minangle)
        angle = minangle;
    else if (angle > maxangle)
        angle = maxangle;
        
    double val = ( (((angle - minangle) / (maxangle - minangle)) * (125.0 - 25.0))  + 25.0 );


    return (uint16_t) val;
}
