#ifndef HARDWARE
#define HARDWARE

#include "hardware_interface_vmxpi.h" // Includes the dependecies of the specific hardware to be used

#include "constants.h"

enum GRIPPER { GRIPPER_OPEN = 50, GRIPPER_CLOSE = 150 };

static int ENCODER_BACK     = 0;
static int ENCODER_RIGHT    = 1;
static int ENCODER_LEFT     = 2;
static int ENCODER_ELEVATOR = 3;

static int MOTOR_LEFT_0     = 21;
static int MOTOR_LEFT_1     = 20;
static int MOTOR_BACK_0     = 19;
static int MOTOR_BACK_1     = 18;
static int MOTOR_RIGHT_0    = 17;
static int MOTOR_RIGHT_1    = 16;
static int MOTOR_ELEVATOR_0 = 15;
static int MOTOR_ELEVATOR_1 = 14;

static int SHARP_FRONT_LEFT  = 0;
static int SHARP_FRONT_RIGHT = 1;
static int SHARP_LEFT        = 2;
static int SHARP_RIGHT       = 3;

static int LIMITSWITCH_HIGH  = 8;
static int LIMITSWITCH_LOW   = 9;

static int BUTTON_START = 11;
static int BUTTON_STOP  = 10;

static int SERVO_GRIPPER = 12;

void delay( int ms );
void delayMicroseconds( int us );
int millis( );

inline digitalInput start_button;
inline digitalInput stop_button;

inline digitalInput limitswitch_low;
inline digitalInput limitswitch_high;

inline EncoderMotor enc_left;
inline EncoderMotor enc_right;
inline EncoderMotor enc_back;
inline EncoderMotor enc_elevator;

inline PWM_Motor motor_left;
inline PWM_Motor motor_right;
inline PWM_Motor motor_back;
inline PWM_Motor motor_elevator;

inline PWM gripper;

inline Analog sensor_front_left;
inline Analog sensor_front_right;
inline Analog sensor_left;
inline Analog sensor_right;


#endif
