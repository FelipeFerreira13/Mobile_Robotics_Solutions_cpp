#include "hardware_interface.h"
#include "functions.h"
#include "constants.h"
#include "movement.h"

int main(int argc, char *argv[])
{
	system("/usr/local/frc/bin/frcKillRobot.sh");
	
	bool realtime = true;
	uint8_t update_rate_hz = 50;
	VMXPi vmx(realtime, update_rate_hz);
	vmx_ptr = &vmx;

	start_button.Init( &vmx, BUTTON_START );
	stop_button.Init( &vmx, BUTTON_STOP );

	enc_left.Init( &vmx, ENCODER_LEFT );
	enc_right.Init( &vmx, ENCODER_RIGHT );
	enc_back.Init( &vmx, ENCODER_BACK );
	enc_elevator.Init( &vmx, ENCODER_ELEVATOR );

	motor_left.Init( &vmx, MOTOR_LEFT_0, MOTOR_LEFT_1 );
	motor_right.Init( &vmx, MOTOR_RIGHT_0, MOTOR_RIGHT_1 );
	motor_back.Init( &vmx, MOTOR_BACK_0, MOTOR_BACK_1 );
	motor_elevator.Init( &vmx, MOTOR_ELEVATOR_0, MOTOR_ELEVATOR_1 );

	motor_left.SetMotorPWM(0);
	motor_right.SetMotorPWM(0);
	motor_back.SetMotorPWM(0);
	motor_elevator.SetMotorPWM(0);

	while(true){
		while( start_button.Get() ){}

		PositionDriver( 100, 0, 0 );
		PositionDriver( 100, 100, 90 );
		PositionDriver( 0, 100, 180 );
		PositionDriver( 0, 0, 270 );
	}

	return 0;

}
