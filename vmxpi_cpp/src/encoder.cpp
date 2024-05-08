#include "encoder.h"


void EncoderMotor::DisplayVMXError(VMXErrorCode vmxerr) {
	const char *p_err_description = GetVMXErrorString(vmxerr);
	printf("VMXError %d:  %s\n", vmxerr, p_err_description);
}
EncoderMotor::EncoderMotor(){}

void EncoderMotor::Init(VMXPi *vmx, uint8_t encoder){
    this->vmx = vmx;
	this->encoder_index = encoder;
	try {
		if(vmx->IsOpen()) {
			if( encoder < 4 && encoder > -1 ){

				VMXChannelInfo enc_channels[2] = { 
					{VMXChannelInfo( (encoder_index * 2) + 0, VMXChannelCapability::EncoderAInput)},
					{VMXChannelInfo( (encoder_index * 2) + 1, VMXChannelCapability::EncoderBInput)}};
				EncoderConfig encoder_cfg(EncoderConfig::EncoderEdge::x4);

				if (!vmx->io.ActivateDualchannelResource(enc_channels[0], enc_channels[1], &encoder_cfg, encoder_res_handle, &vmxerr)) {
					printf("Failed to Activate Encoder Resource %d.\n", encoder_index);
					DisplayVMXError(vmxerr);
					vmx->io.DeallocateResource(encoder_res_handle, &vmxerr);
				} else {
					printf("Successfully Activated Encoder Resource %d with VMXChannels %d and %d\n", encoder_index, enc_channels[0].index, enc_channels[1].index);
				}
			
				VMXResourceHandle encoder_res_handle;
				if (!vmx->io.GetResourceHandle(VMXResourceType::Encoder, encoder_index, encoder_res_handle, &vmxerr)) {
					DisplayVMXError(vmxerr);
				}
			}else{
				printf("Invalid Analog input channel (0-3)\n");
			}

		} else {
			printf("Error:  Unable to open VMX Client.\n");
		}
	}
	catch(const std::exception& ex){
		printf("Caught exception:  %s", ex.what());
	}
}

EncoderMotor::~EncoderMotor(){}

int EncoderMotor::GetEncoderCount( ){
	int counter;
	if (vmx->io.Encoder_GetCount(encoder_res_handle, counter, &vmxerr)) {
		VMXIO::EncoderDirection encoder_direction;
		if(vmx->io.Encoder_GetDirection(encoder_res_handle, encoder_direction, &vmxerr)) {
			// printf("%s\t", (encoder_direction == VMXIO::EncoderForward) ? "F" : "R");
		} else {
			printf("Error retrieving Encoder %d direction.\n", encoder_index);
			DisplayVMXError(vmxerr);
		}
	} else {
		printf("Error retrieving Encoder %d count.\n", encoder_index);
		DisplayVMXError(vmxerr);
	}
	return counter;
}


