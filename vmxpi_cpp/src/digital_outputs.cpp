#include "digital_outputs.h"


void digitalOutput::DisplayVMXError(VMXErrorCode vmxerr) {
	const char *p_err_description = GetVMXErrorString(vmxerr);
	printf("VMXError %d:  %s\n", vmxerr, p_err_description);
}

digitalOutput::digitalOutput(VMXPi *vmx, uint8_t channel){
    this->vmx = vmx;
	this->channel_index = channel;
	try {
		if(vmx->IsOpen()) {

			/* Configure all HighCurrDIOs as OUTPUTS. */
				DIOConfig dio_config(DIOConfig::OutputMode::PUSHPULL);
				if (!vmx->io.ActivateSinglechannelResource(VMXChannelInfo(channel_index, VMXChannelCapability::DigitalOutput), &dio_config, 
						digitalout_res_handle, &vmxerr)) {
					printf("Error Activating Singlechannel Resource DIO for Channel index %d.\n", channel_index);
					DisplayVMXError(vmxerr);
				} else {
					printf("Digital Output Channel %d activated on Resource type %d, index %d\n", channel_index, EXTRACT_VMX_RESOURCE_TYPE(digitalout_res_handle), EXTRACT_VMX_RESOURCE_INDEX(digitalout_res_handle));
				}
			
		} else {
			printf("Error:  Unable to open VMX Client.\n");
		}
	}
	catch(const std::exception& ex){
		printf("Caught exception:  %s", ex.what());
	}
}

digitalOutput::~digitalOutput(){
	    if (!INVALID_VMX_RESOURCE_HANDLE(digitalout_res_handle)) {
        if (!vmx->io.DeallocateResource(digitalout_res_handle, &vmxerr)) {
            printf("Error Deallocating DO Resource.\n");
        } else {
            printf("Successfully Deallocated PWM Resource Index %d\n", EXTRACT_VMX_RESOURCE_INDEX(digitalout_res_handle));
        }
    }
}

void digitalOutput::SetPinState( bool state ){
    printf("DO %d set to %d \n", channel_index, state);
	if (!vmx->io.DIO_Set(digitalout_res_handle, state, &vmxerr)) {
		printf("Error Setting DO for Digital Out Resource Index %d.\n", channel_index);
		DisplayVMXError(vmxerr);
	}
}
