#include "hardware_interface.h"
#include "functions.h"
#include "constants.h"
#include "movement.h"
#include "object_management_system.h"

int main(int argc, char *argv[])
{
	system("/usr/local/frc/bin/frcKillRobot.sh");
	
	bool realtime = true;
	uint8_t update_rate_hz = 50;
	//Initialize the VMX
	VMXPi vmx(realtime, update_rate_hz);
	vmx_ptr = &vmx;

	Initialize_hardware( &vmx );	// Initialize the peripherals

	OMS oms;	// Creates the OMS Object


	// while( start_button.Get() ){}

	oms.reset( -1 );	//Initiate touching the LimitSwitch
	// oms.setGripper( GRIPPER_OPEN );	//Set the Gripper to open

	// SetPosition( 30, 30, 0 );
	// PositionDriver( 50, 30, 0 );

	while( start_button.Get() ){
		printf( "front_left: %f   ", sensor_front_left.GetIRDistance() );
		printf( "front_right: %f   ", sensor_front_right.GetIRDistance() );
		printf( "left: %f   ", sensor_left.GetIRDistance() );
		printf( "right: %f\n", sensor_right.GetIRDistance() );
		delay(500);
	}

	return 0;

}
