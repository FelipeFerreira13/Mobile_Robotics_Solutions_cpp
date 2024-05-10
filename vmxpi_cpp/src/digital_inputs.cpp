#include "digital_inputs.h"

void digitalInput::DisplayVMXError(VMXErrorCode vmxerr) {
	const char *p_err_description = GetVMXErrorString(vmxerr);
	printf("VMXError %d:  %s\n", vmxerr, p_err_description);
}
digitalInput::digitalInput(){}
void digitalInput::Init(VMXPi *vmx, uint8_t channel){
    this->vmx = vmx;
	this->dio_channel_index = channel;
	try {
		if(vmx->IsOpen()) {
			if( channel < 12 && channel > 7 ){
				DIOConfig dio_config;
				if (!vmx->io.ActivateSinglechannelResource(VMXChannelInfo(dio_channel_index, VMXChannelCapability::DigitalInput), &dio_config, 
						digitalio_res_handle, &vmxerr)) {
					printf("Error Activating Singlechannel Resource DIO for Channel index %d.\n", dio_channel_index);
					DisplayVMXError(vmxerr);
				} else {
					printf("Digital Input Channel %d activated on Resource type %d, index %d\n", dio_channel_index,
							EXTRACT_VMX_RESOURCE_TYPE(digitalio_res_handle),
							EXTRACT_VMX_RESOURCE_INDEX(digitalio_res_handle));
				}
			}else{
				printf("Invalid Analog input channel (8-11)\n");
			}
		} else {
			printf("Error:  Unable to open VMX Client.\n");
		}
	}
	catch(const std::exception& ex){
		printf("Caught exception:  %s", ex.what());
	}
}

digitalInput::~digitalInput(){}

bool digitalInput::Get() {
	bool state;
	if (!vmx->io.DIO_Get(digitalio_res_handle, state, &vmxerr)) {
		printf("Error Reading Digital Input value for Resource Index %d.\n", dio_channel_index);
		DisplayVMXError(vmxerr);
	} else {
		// printf("DI %d state %d \n", dio_channel_index,(state ? 1 : 0));
	}
    
    return state;
}