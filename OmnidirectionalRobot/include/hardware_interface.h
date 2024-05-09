#ifndef HARDWARE
#define HARDWARE

#include "VMXPi.h"
#include "constants.h"

#include "encoder.h"
#include "pwm.h"
#include "pwm_motor.h"
#include "digital_outputs.h"

inline VMXPi *vmx_ptr;

inline EncoderMotor enc_left;
inline EncoderMotor enc_right;
inline EncoderMotor enc_back;
inline EncoderMotor enc_elevator;

inline PWM_Motor motor_left;
inline PWM_Motor motor_right;
inline PWM_Motor motor_back;
inline PWM_Motor motor_elevator;

#endif
