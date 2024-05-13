#include "object_management_system.h"

OMS::OMS(){}

void OMS::OMSDriver( float desired_height ) {
   
    int current_time = millis();
    int previous_time = millis();

    int current_enc = enc_elevator.GetEncoderCount();
    int previous_enc = enc_elevator.GetEncoderCount();

    simpleControl elevatorControl;
    elevatorControl.max_motor_speed = 15;

    float desired_speed = 0;

    if ( desired_height < high_height && desired_height > low_height ){
        do{

            if( !limitswitch_low.Get()  ){ height = low_height; }
            if( !limitswitch_high.Get() ){ height = high_height; }


            current_time = millis();
            float delta_time = float(current_time - previous_time) / 1000.0; // [s]
            previous_time = current_time;

            current_enc = enc_elevator.GetEncoderCount();
            float delta_enc = current_enc - previous_enc;
            previous_enc = current_enc;

            //Pinion Velocity
            float elevatorVelocity  = (((2 * PI * pinionRadius * delta_enc) / (ticksPerRev * delta_time)));   // [cm/s]

            if ( isnan(elevatorVelocity) || isinf(elevatorVelocity) ){ elevatorVelocity  = 0; }
            
            //Elevation Displacement
            float delta_elev  = elevatorVelocity  * delta_time; // Displacement per iteration

            height = height + delta_elev;   // [cm]

            float elev_diff  = desired_height - height;

            float max_speed = 10.0; // cm/s

            desired_speed = map_func( elev_diff, -5.0, 5.0, -1 * max_speed, max_speed );  // [cm], [cm], [cm], [cm/s], [cm/s]
            desired_speed = max( min( desired_speed, max_speed ), -1 * max_speed );
            if( abs(elev_diff) < tolerance ){ desired_speed = 0; }

            int elevatorPWM  = elevatorControl.motorControl(desired_speed, elevatorVelocity, delta_time);

            printf("vel: %f  ", elevatorVelocity);
            printf("time: %f\n", delta_time);


            printf("des_vel: %f  ", desired_speed);

            printf("leftPWM: %d   ", elevatorPWM);

            printf("enc: %d\n", current_enc);

            printf("height: %f   ", height);

            if ( !stop_button.Get() ){ elevatorMotor(0); }
            else{ elevatorMotor(elevatorPWM); }

            delay(100);

        }while( desired_speed != 0 );
    }else{
        printf( "Desired Position out of range %f to %f", low_height, high_height );
    }
    elevatorMotor(0);
    
    delay(250);
}

void OMS::setHeight( float set_height ){
    height = set_height;
}

// -1 to send it down and 1 to send it up
void OMS::reset( int direction ){
    
    if( direction == 1 ){
        elevatorMotor( 100 );
        while( limitswitch_high.Get( ) && stop_button.Get()){
            delay(50);
        }
        height = high_height;
        printf("new height is %f", height);
    }else if (direction == -1){
        elevatorMotor( -100 );
        while( limitswitch_low.Get( ) && stop_button.Get() ){
            delay(50);
        }
        height = low_height;
        printf("new height is %f", height);
    }else{}
    elevatorMotor( 0 );
}

void OMS::setGripper( int set ){
    gripper.SetAngle( set );
}
