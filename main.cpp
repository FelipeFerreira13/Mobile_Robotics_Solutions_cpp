// #include "vmxpi_cpp/include/hardware_interface_vmxpi.h" // Includes the dependecies of the specific hardware to be used

#include "general/include/functions.h"
#include "general/include/constants.h"
#include "OmnidirectionalRobot/include/movement.h"
#include "Object_Management_System/include/oms_control.h"
#include "general/include/hardware_interface.h"


int main(int argc, char *argv[])
{
	system("/usr/local/frc/bin/frcKillRobot.sh");
	
	bool realtime = true;
	int update_rate_hz = 50;
	//Initialize the VMX
	VMXPi vmx(realtime, update_rate_hz);
	vmx_ptr = &vmx;
	
    // initialize the HARDWARE
	start_button.Init( BUTTON_START );
	stop_button.Init( BUTTON_STOP );

	limitswitch_low.Init( LIMITSWITCH_LOW);
	limitswitch_high.Init( LIMITSWITCH_HIGH);

	enc_left.Init( ENCODER_LEFT );
	enc_right.Init( ENCODER_RIGHT );
	enc_back.Init( ENCODER_BACK );
	enc_elevator.Init( ENCODER_ELEVATOR );

	gripper.Init( SERVO_GRIPPER );

	sensor_front_left.Init( SHARP_FRONT_LEFT );
	sensor_front_right.Init( SHARP_FRONT_RIGHT );
	sensor_left.Init( SHARP_LEFT );
	sensor_right.Init( SHARP_RIGHT );

	motor_left.Init( MOTOR_LEFT_0, MOTOR_LEFT_1 );
	motor_right.Init( MOTOR_RIGHT_0, MOTOR_RIGHT_1 );
	motor_back.Init( MOTOR_BACK_0, MOTOR_BACK_1 );
	motor_elevator.Init( MOTOR_ELEVATOR_0, MOTOR_ELEVATOR_1 );

	motor_left.SetMotorPWM(0);
	motor_right.SetMotorPWM(0);
	motor_back.SetMotorPWM(0);
	motor_elevator.SetMotorPWM(0);

	OMS oms;	// Creates the OMS Object

	oms.setGripper( GRIPPER_CLOSE );	//Set the Gripper to open


	while( start_button.Get() ){
		delay(500);
		printf("sharp: %f\n", sensor_front_left.GetIRDistance());
	}	// Wait until the Start button is pressed

	SetPosition( 0.0, 0.0, 0.0 );
	PositionDriver( 30.0, 0.0, 0.0 );

	oms.reset( -1 );	// Hit the LimitSwitch to reset the OMS position
	oms.setGripper( GRIPPER_OPEN );	//Set the Gripper to open

	// SetPosition( 30.0, 30.0, 0.0 );

	return 0;

}
