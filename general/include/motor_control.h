#ifndef CONTROL
#define CONTROL

#include "functions.h"
#include "hardware_interface.h"

class simpleControl{
    private:
        float correction = 0; // [PWM]

    public:   
        float max_motor_speed = 60.0; // [cm/s]

        simpleControl();
        float motorControl(float desiredSpeed, float currentSpeed, float delta_time);
};

void leftMotor(float PWM);
void rightMotor(float PWM);
void backMotor( float PWM );
void elevatorMotor(float PWM);


#endif
