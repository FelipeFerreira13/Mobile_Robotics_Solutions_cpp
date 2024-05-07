#include "pwm.h"
#include "encoder.h"
#include "digital_outputs.h"
#include "digital_inputs.h"
#include "analog_inputs.h"

int main(int argc, char *argv[])
{

    system("/usr/local/frc/bin/frcKillRobot.sh");

	bool realtime = true;
	uint8_t update_rate_hz = 50;
	VMXPi vmx(realtime, update_rate_hz);

    EncoderMotor enc(&vmx, 1);

    for (int i = 0; i < 50; i++){
        printf("DI: %d\n", enc.GetEncoderCount( ));
        vmx.time.DelayMilliseconds(150);
    }



    }
