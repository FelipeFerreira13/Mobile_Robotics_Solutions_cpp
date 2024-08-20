#include "imu.h"

void AHRSCallback::Init( ){

	try {
		if(vmx_ptr->IsOpen()) {
			printf("AHRS Connected:  %s\n", (vmx_ptr->ahrs.IsConnected() ? "Yes" : "No"));

			/* Usage Model 1:  Foreground polling (of latest data in receive cache) */
			for ( int i = 0; i < 10; i++) {
				printf("Yaw, Pitch, Roll:  %f, %f, %f\n", vmx_ptr->ahrs.GetYaw(), vmx_ptr->ahrs.GetPitch(), vmx_ptr->ahrs.GetRoll());
				vmx_ptr->time.DelayMilliseconds(20);
			}

			/* Usage Model 2:  Interrupt-driven callbacks whenever new data arrives. */
			vmx_ptr->ahrs.RegisterCallback(this, NULL);

			vmx_ptr->time.DelaySeconds(10);
		} else {
			printf("Error:  Unable to open VMX Client.\n");
			printf("\n");
			printf("        - Is pigpio (or the system resources it requires) in use by another process?\n");
			printf("        - Does this application have root privileges?\n");
		}
	}
	catch(const std::exception& ex){
		printf("Caught exception:  %s", ex.what());
	}
	vmx_ptr->ahrs.DeregisterCallback(this);

}
