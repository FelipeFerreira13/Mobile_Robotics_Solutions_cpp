#include "hardware_interface.h"

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