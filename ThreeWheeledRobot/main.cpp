#include "functions.h"
#include "constants.h"

#include "encoder.h"
#include "pwm.h"
#include "pwm_motor.h"
#include "digital_outputs.h"


int main(int argc, char *argv[])
{
	system("/usr/local/frc/bin/frcKillRobot.sh");
	
	
	bool realtime = true;
	uint8_t update_rate_hz = 50;
	VMXPi vmx(realtime, update_rate_hz);
	vmx_ptr = &vmx;

	Serial Serial;

	EncoderMotor enc( &vmx, ENCODER_LEFT );

	PWM_Motor M0_in1( &vmx, MOTOR_LEFT_0, MOTOR_LEFT_1 );
	// PWM_Motor M0_in2( &vmx, MOTOR_LEFT_1, MOTOR_LEFT_1 );

	

    int prev = enc.GetEncoderCount();
	// M0_in1.SetMotorPWM( 0.1 );

	// for (int i = 0; i < 128; i++){
	//   int current = enc.GetEncoderCount();
	//   printf("diff: %d\n", current - prev);
	//   prev = current;
	//   M0_in1.SetMotorPWM( 0 );
	//   M0_in2.SetMotorPWM( i/255.0 );
	//   delay(100);
	// }

	delay(1000);
	M0_in1.SetMotorPWM( 0.2 );
	// M0_in2.SetMotorPWM( 0.3 );
	delay(2000);
	M0_in1.SetMotorPWM( -0.2 );
	// M0_in2.SetMotorPWM( 0.0 );
	delay(4000);
	M0_in1.SetMotorPWM( 0 );
	// M0_in2.SetMotorPWM( 1 );
	delay(1000);



	// M0_in1.SetAngle( 0 );
	// M0_in2.SetAngle( 100 );

	// delay( 2000 );

	// M0_in1.SetAngle( 0 );
	// M0_in2.SetAngle( 0 );

	// delay( 2000 );

	// M0_in1.SetAngle( 100 );
	// M0_in2.SetAngle( 0 );

	// delay( 2000 );


	Serial.~Serial();
	return 0;

}
