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

	initHardware();

	AHRSCallback imu( vmx.ahrs );	// Initialize IMU
	imu.Init();

	OMS oms;	// Creates the OMS Object

	

	oms.setGripper( GRIPPER_CLOSE );	//Set the Gripper to open


	while( start_button.Get() ){
		delay(500);
		printf("sharp: %f\n", sensor_front_left.GetIRDistance());

	}	// Wait until the Start button is pressed

	cmd_drive( 30, 0, 0 );

	delay( 3000 );

	cmd_drive( 0, 0, 0 );

	delay( 1000 );

	SetPosition( 0.0, 0.0, 0.0 );
	PositionDriver( 30.0, 0.0, 0.0 );

	oms.reset( -1 );	// Hit the LimitSwitch to reset the OMS position
	oms.setGripper( GRIPPER_OPEN );	//Set the Gripper to open



	return 0;

}
