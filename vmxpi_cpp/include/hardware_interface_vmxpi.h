#ifndef VMXPI
#define VMXPI

#include "VMXPi.h"

#include "encoder.h"
#include "pwm.h"
#include "pwm_motor.h"
#include "digital_inputs.h"
#include "digital_outputs.h"
#include "analog_inputs.h"

inline VMXPi *vmx_ptr;

void DisplayVMXError(VMXErrorCode vmxerr);

#endif
