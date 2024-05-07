#include "cobra.h"

#define ARRAY_SIZE(a) (sizeof(a)/sizeof(a[0]))

void Cobra::DisplayVMXError(VMXErrorCode vmxerr) {
	const char *p_err_description = GetVMXErrorString(vmxerr);
	printf("VMXError %d:  %s\n", vmxerr, p_err_description);
}

Cobra::Cobra(VMXPi *vmx) :
	io{&vmx->getIO()}, deviceAddress(0x48), vRef(5.0F), mode(CONFIG_MODE_CONT), gain(CONFIG_PGA_2), rate(CONFIG_RATE_1600HZ) {

	this->vmx = vmx;
	try {
		if(vmx->IsOpen()) {
			vmx->ahrs.Stop();

			VMXChannelInfo i2c_channels[2] = {
				{ VMXChannelInfo(io->GetSoleChannelIndex(VMXChannelCapability::I2C_SDA), VMXChannelCapability::I2C_SDA) },
				{ VMXChannelInfo(io->GetSoleChannelIndex(VMXChannelCapability::I2C_SCL), VMXChannelCapability::I2C_SCL) }};

			I2CConfig i2c_cfg;

			if (!vmx->io.ActivateDualchannelResource(i2c_channels[0], i2c_channels[1], &i2c_cfg, i2c_res_handle, &vmxerr)) {
				printf("Failed to Activate I2C Resource.\n");
				DisplayVMXError(vmxerr);
			} else {
				printf("Successfully Activated I2C Resource with VMXChannels %d and %d\n",
						i2c_channels[0].index, i2c_channels[1].index);
			}

			if (IsConnected())
				printf("Connected\n");
			else
				printf("Not connected\n");
			

			// uint8_t device_7bit_i2c_address = 0x48; /* navX-MXP/navX-Micro I2C address */
			// uint8_t tx_data[2];
			// uint8_t rx_data[32];

			// tx_data[0] = 0;  /* First Address to Read */
			// tx_data[1] = 32; /* Number of bytes to read */
			// for (int i = 0; i < 50; i++) {

			// 	if (!vmx->io.I2C_Transaction(i2c_res_handle, device_7bit_i2c_address,
			// 								tx_data, ARRAY_SIZE(tx_data),
			// 								rx_data, ARRAY_SIZE(rx_data),
			// 								&vmxerr)) {
			// 		printf("I2C Transaction Error.\n");
			// 		DisplayVMXError(vmxerr);
			// 	} else {
			// 		printf("I2C rx data:  ");
			// 		for (int i = 0; i < 32; i++) {
			// 			printf("%02x", rx_data[i]);
			// 		}
			// 		printf("\n");
			// 	}

			// 	vmx->time.DelayMilliseconds(20);
			// }
		} else {
			printf("Error:  Unable to open VMX Client.\n");
		}
	}
	catch(const std::exception& ex){
		printf("Caught exception:  %s", ex.what());
	}
}

Cobra::~Cobra(){}

bool Cobra::IsConnected() {
    uint8_t buffer = 0;
	
    if (io->I2C_Read(i2c_res_handle, deviceAddress, 0, &buffer, 1, &vmxerr)) // to fix, I2C_Read function currently does not work
	    return true;
    else {
      DisplayVMXError(vmxerr);
	    return false;
    }
}

int Cobra::GetSingle(uint8_t channel) {
	 if (channel > 3)
	    return 0;
    
    int config = CONFIG_OS_SINGLE | mode | rate | gain; // OR the config options together
    switch(channel) { // this allows the config data to be specific to each channel
	    case(0):
        config |= CONFIG_MUX_SINGLE_0;
        break;
	    case(1):
        config |= CONFIG_MUX_SINGLE_1;
        break;
	    case(2):
	      config |= CONFIG_MUX_SINGLE_2;
	      break;
	    case(3):
	      config |= CONFIG_MUX_SINGLE_3;
	      break;
    }
    uint8_t raw[2] = {(uint8_t) (config >> 8), (uint8_t) (config & 0xFF)};
    uint8_t buffer[2];
    VMXErrorCode vmxerr;

    if (!io->I2C_Write(i2c_res_handle, deviceAddress, // send the config data to the cobra
			    POINTER_CONFIG, raw, (int32_t)sizeof(raw), 
			    &vmxerr)) {
	    printf("I2C send failed\n");
      DisplayVMXError(vmxerr);
    }
	
    uint8_t data[2] = {POINTER_CONVERT, POINTER_CONVERT};
    
    if (!io->I2C_Transaction(i2c_res_handle, deviceAddress, // write to the register in order to receive the raw value back
				data, (uint16_t)sizeof(data),
				buffer, (uint16_t)sizeof(buffer),
				&vmxerr)) {
	    printf("I2C Transaction failed\n");
      DisplayVMXError(vmxerr);
    }
	
    int val = (int)((buffer[0]<<8) & 0xFF00) | (buffer[1] & 0xFF); // since the data is little-endian, shift data to get correct value
    //ROS_INFO_STREAM("channel " << channel << ": " << (val >> 4));
    return val>>4;
}
