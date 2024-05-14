#include "hardware_interface.h"

void Initialize_hardware( VMXPi *vmx ){

    // initialize the HARDWARE
	start_button.Init( vmx, BUTTON_START );
	stop_button.Init( vmx, BUTTON_STOP );

	limitswitch_low.Init( vmx, LIMITSWITCH_LOW);
	limitswitch_high.Init( vmx, LIMITSWITCH_HIGH);

	enc_left.Init( vmx, ENCODER_LEFT );
	enc_right.Init( vmx, ENCODER_RIGHT );
	enc_back.Init( vmx, ENCODER_BACK );
	enc_elevator.Init( vmx, ENCODER_ELEVATOR );

	gripper.Init( vmx, SERVO_GRIPPER );

	sensor_front_left.Init( vmx, SHARP_FRONT_LEFT );
	sensor_front_right.Init( vmx, SHARP_FRONT_RIGHT );
	sensor_left.Init( vmx, SHARP_LEFT );
	sensor_right.Init( vmx, SHARP_RIGHT );

	motor_left.Init( vmx, MOTOR_LEFT_0, MOTOR_LEFT_1 );
	motor_right.Init( vmx, MOTOR_RIGHT_0, MOTOR_RIGHT_1 );
	motor_back.Init( vmx, MOTOR_BACK_0, MOTOR_BACK_1 );
	motor_elevator.Init( vmx, MOTOR_ELEVATOR_0, MOTOR_ELEVATOR_1 );

	motor_left.SetMotorPWM(0);
	motor_right.SetMotorPWM(0);
	motor_back.SetMotorPWM(0);
	motor_elevator.SetMotorPWM(0);
}

simpleControl::simpleControl(){}

float simpleControl::motorControl(float desiredSpeed, float currentSpeed, float delta_time) {

    float Desired_PWM = (desiredSpeed / max_motor_speed) * 255.0; // Proportional PWM regarding MAX speed of the motor [PWM]

    float error = desiredSpeed - currentSpeed;  // [cm/s]

    //Defines a proportional increment to the PWM
    float incrementPWM = map_func(error, -1 * max_motor_speed, max_motor_speed, -100.0, 100.0);  // ( [cm], [cm], [cm], [PWM], [PWM] )
    incrementPWM = incrementPWM * delta_time;

    if( error == 0 ){ correction = 0;}
    else{ correction  = max( min( correction + incrementPWM, 50.0 ), -50.0 ); }

    printf("correction: %f\n", correction);

    Desired_PWM = max( min( Desired_PWM + correction, 255.0 ),  -255.0 );

    if (desiredSpeed == 0){ Desired_PWM = 0; }

    return Desired_PWM;
}


void backMotor( float PWM ){
    PWM = PWM / 255.0;
    motor_back.SetMotorPWM( PWM );
}

void leftMotor( float PWM ){
    PWM = PWM / 255.0;
    motor_left.SetMotorPWM( PWM );
}

void rightMotor( float PWM ){
    PWM = PWM / 255.0;
    motor_right.SetMotorPWM( PWM );
}

void elevatorMotor( float PWM ){
    PWM = PWM / 255.0;
    motor_elevator.SetMotorPWM( PWM );
}

void delay( uint32_t ms ){
    vmx_ptr->time.DelayMilliseconds( ms );
}
void delayMicroseconds( uint32_t us ){
    vmx_ptr->time.DelayMicroseconds(us);
}
uint32_t millis( ){
    uint32_t time = vmx_ptr->time.GetCurrentMicroseconds();
    time = time / 1000;
    return time;
}