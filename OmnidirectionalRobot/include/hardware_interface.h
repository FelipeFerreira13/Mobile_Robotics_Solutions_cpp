#ifndef HARDWARE
#define HARDWARE

#include "VMXPi.h"

#include "functions.h"
#include "constants.h"

#include "encoder.h"
#include "pwm.h"
#include "pwm_motor.h"
#include "digital_inputs.h"
#include "digital_outputs.h"

inline VMXPi *vmx_ptr;

inline digitalInput start_button;
inline digitalInput stop_button;

inline EncoderMotor enc_left;
inline EncoderMotor enc_right;
inline EncoderMotor enc_back;
inline EncoderMotor enc_elevator;

inline PWM_Motor motor_left;
inline PWM_Motor motor_right;
inline PWM_Motor motor_back;
inline PWM_Motor motor_elevator;

static int ENCODER_BACK     = 0;
static int ENCODER_RIGHT    = 1;
static int ENCODER_LEFT     = 2;
static int ENCODER_ELEVATOR = 3;

static int MOTOR_BACK_0     = 19;
static int MOTOR_BACK_1     = 18;
static int MOTOR_RIGHT_0    = 17;
static int MOTOR_RIGHT_1    = 16;
static int MOTOR_ELEVATOR_0 = 15;
static int MOTOR_ELEVATOR_1 = 14;
static int MOTOR_LEFT_0     = 13;
static int MOTOR_LEFT_1     = 12;

static int SHARP_FRONT_LEFT  = 0;
static int SHARP_FRONT_RIGHT = 1;
static int SHARP_LEFT        = 2;
static int SHARP_RIGHT       = 3;

static int LIMITSWITCH_UP   = 8;
static int LIMITSWITCH_DOWN = 9;

static int BUTTON_START = 11;
static int BUTTON_STOP  = 10;

class simpleControl{
    private:
        const float max_motor_speed = 60.0; // [cm/s]
        float correction = 0;               // [PWM]

    public:   
        simpleControl();

        float motorControl(float desiredSpeed, float currentSpeed, float delta_time);
};

void leftMotor(float PWM);
void rightMotor(float PWM);
void backMotor( float PWM );
void elevatorMotor(float PWM);

#endif
