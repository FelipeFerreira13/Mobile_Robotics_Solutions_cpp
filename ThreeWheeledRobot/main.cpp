#include "Arduino.h"

int main(int argc, char *argv[])
{
	system("/usr/local/frc/bin/frcKillRobot.sh");
	
	bool realtime = true;
	uint8_t update_rate_hz = 50;
	VMXPi vmx(realtime, update_rate_hz);
	vmx_ptr = &vmx;

	Serial Serial;

	PWM M0_in1( &vmx, 18 );
	PWM M0_in2( &vmx, 19 );


	M0_in1.SetAngle( 0 );
	M0_in2.SetAngle( 300 );

	delay( 2000 );

	M0_in1.SetAngle( 0 );
	M0_in2.SetAngle( 0 );

	delay( 2000 );

	M0_in1.SetAngle( 300 );
	M0_in2.SetAngle( 0 );

	delay( 2000 );


	Serial.~Serial();
	return 0;

}
