#include "hardware_interface_vmxpi.h"

void DisplayVMXError(VMXErrorCode vmxerr) {
	const char *p_err_description = GetVMXErrorString(vmxerr);
	printf("VMXError %d:  %s\n", vmxerr, p_err_description);
}

void delay( int ms ){
    vmx_ptr->time.DelayMilliseconds( ms );
}
void delayMicroseconds( int us ){
    vmx_ptr->time.DelayMicroseconds(us);
}
int millis( ){
    int time = vmx_ptr->time.GetCurrentMicroseconds();
    time = time / 1000;
    return time;
}