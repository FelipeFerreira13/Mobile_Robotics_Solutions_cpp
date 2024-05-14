#include "OmnidirectionalRobot/include/hardware_interface.h"
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


	while( start_button.Get() ){}	// Wait until the Start button is pressed

	oms.reset( -1 );	// Hit the LimitSwitch to reset the OMS position
	oms.setGripper( GRIPPER_OPEN );	//Set the Gripper to open

	SetPosition( 30, 30, 0 );

	return 0;

}
