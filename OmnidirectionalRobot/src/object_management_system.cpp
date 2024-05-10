#include "object_management_system.h"


void OMSDriver( float desired_height ) {
   
    current_time = millis();
    previous_time - millis();

    simpleControl elevatorControl;

    float desired_speed = 0;

    do{
        current_time = millis();
        float delta_time = float(current_time - previous_time) / 1000.0; // [s]
        previous_time = current_time;

        current_enc = enc_elevator.GetEncoderCount();
        float delta_enc = current_enc - previous_enc;
        previous_enc = current_enc;

        //Pinion Velocity
        float elevatorVelocity  = (((2 * PI * pinionRadius * delta_enc) / (ticksPerRev * delta_time)));   // [cm/s]

        if ( isnan(elevatorVelocity)  ){ elevatorVelocity  = 0; }
        
        //Elevation Displacement
        float delta_elev  = elevatorVelocity  * delta_time; // Displacement per iteration

        height = height + delta_elev;   // [cm]

        float elev_diff  = desired_height - height;

        float max_speed = 10.0; // cm/s

        desired_speed = map_func( elev_diff, -30.0, 30.0, -1 * max_speed, max_speed );  // [cm], [cm], [cm], [cm/s], [cm/s]
        desired_speed = max( min( desired_speed, max_speed ), -1 * max_speed );
        if( abs(elev_diff) < tolerance ){ desired_speed = 0; }

        int elevatorPWM  = elevatorControl.motorControl(desired_speed, elevatorVelocity, delta_time);

        printf("des_vel: %f  ", desired_speed);

        printf("leftPWM: %d   ", elevatorPWM);

        printf("enc: %d\n", current_enc);

        printf("height: %f   ", height);

        if ( !stop_button.Get() ){ elevatorMotor(0); }
        else{ elevatorMotor(elevatorPWM); }

        delay(100);

    }while( desired_speed != 0 );
    
    elevatorMotor(0);
    
    delay(250);
}
