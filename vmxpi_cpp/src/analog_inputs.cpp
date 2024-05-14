#include "analog_inputs.h"

void Analog::DisplayVMXError(VMXErrorCode vmxerr) {
	const char *p_err_description = GetVMXErrorString(vmxerr);
	printf("VMXError %d:  %s\n", vmxerr, p_err_description);
}

Analog::Analog(){}

void Analog::Init(VMXPi *vmx, uint8_t channel){
    this->vmx = vmx;
	this->analog_in_chan_index = channel + 22;
	try {
		if(vmx->IsOpen()) {
			if( channel < 4 && channel > -1 ){
				VMXErrorCode vmxerr;
				float full_scale_voltage;
				if(vmx->io.Accumulator_GetFullScaleVoltage(full_scale_voltage, &vmxerr)) {
					printf("Analog Input Voltage:  %0.1f\n", full_scale_voltage);
				} else {
					printf("ERROR acquiring Analog Input Voltage.\n");
					DisplayVMXError(vmxerr);
				}

				AccumulatorConfig accum_config;
				accum_config.SetNumAverageBits(9);
				if (!vmx->io.ActivateSinglechannelResource(VMXChannelInfo(analog_in_chan_index, VMXChannelCapability::AccumulatorInput),
						&accum_config, accumulator_res_handle, &vmxerr)) {
					printf("Error Activating Singlechannel Resource Accumulator for Channel index %d.\n", analog_in_chan_index);
					DisplayVMXError(vmxerr);
				} else {
					printf("Analog Input Channel %d activated on Resource type %d, index %d\n", analog_in_chan_index,
							EXTRACT_VMX_RESOURCE_TYPE(accumulator_res_handle),
							EXTRACT_VMX_RESOURCE_INDEX(accumulator_res_handle));
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

Analog::~Analog(){}

double Analog::GetIRDistance(){
	return(pow(GetRawVoltage(), -1.2045)) * 27.726; // convert the voltage read
}
double Analog::GetRawVoltage(){
	float an_in_voltage;
	if(vmx->io.Accumulator_GetAverageVoltage(accumulator_res_handle, an_in_voltage, &vmxerr)){
		// printf("%0.3fV\t", an_in_voltage);
	} else {
		printf("Error getting Average Voltage of analog accumulator %d\n");
		DisplayVMXError(vmxerr);
	}
	return an_in_voltage;
}
