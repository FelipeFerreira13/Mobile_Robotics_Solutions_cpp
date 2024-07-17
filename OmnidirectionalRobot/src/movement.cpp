#include "movement.h"

void SetPosition( float x, float y, float th ){
  x_global = x;
  y_global = y;
  th_global = th;
}

float get_x() { return x_global;  }
float get_y() { return y_global;  }
float get_th(){ return th_global; }

void PositionDriver( float desired_x, float desired_y, float desired_th ) {

    bool reach_linear_tol  = false;
    bool reach_angular_tol = false;
   
    int current_time = millis();
    int previous_time = millis();

    simpleControl leftControl;
    simpleControl rightControl;
    simpleControl backControl;

    float desired_vx;
    float desired_vy;
    float desired_vth;

    do{
        current_time = millis();
        float delta_time = float(current_time - previous_time) / 1000.0; // [s]
        previous_time = current_time;

        current_enc_l = enc_left.GetEncoderCount();
        float delta_enc_l = current_enc_l - previous_enc_l;
        previous_enc_l = current_enc_l;

        current_enc_r = enc_right.GetEncoderCount();
        float delta_enc_r = current_enc_r - previous_enc_r;
        previous_enc_r = current_enc_r;

        current_enc_b = enc_back.GetEncoderCount();
        float delta_enc_b = current_enc_b - previous_enc_b;
        previous_enc_b = current_enc_b;

        //Wheels Velocity
        float leftVelocity  = -1 * (((2 * PI * wheelRadius * delta_enc_l) / (ticksPerRev * delta_time)));   // [cm/s]
        float rightVelocity = -1 * (((2 * PI * wheelRadius * delta_enc_r) / (ticksPerRev * delta_time)));   // [cm/s]
        float backVelocity  = -1 * (((2 * PI * wheelRadius * delta_enc_b) / (ticksPerRev * delta_time)));   // [cm/s]

        if ( isnan(leftVelocity)  || isinf(leftVelocity) ) { leftVelocity  = 0; }
        if ( isnan(rightVelocity) || isinf(rightVelocity) ){ rightVelocity = 0; }
        if ( isnan(backVelocity)  || isinf(backVelocity) ) { backVelocity  = 0; }

        float th_radius = (( th_global / 180.0 ) * PI);  //Robot Global Position on the Th axis  [rad]
        
        //Forward Kinematics
        float vx   = ( (      0     * backVelocity ) + ( (1.0/sqrt(3.0)) * rightVelocity) + ( (-1.0/sqrt(3.0)) * leftVelocity) );                // [cm/s]
        float vy   = ( ( (-2.0/3.0) * backVelocity ) + (    (1.0/3.0)    * rightVelocity) + (     (1.0/3.0)    * leftVelocity) );                // [cm/s]
        float vth  = ( ( ( 1.0/3.0) * backVelocity ) + (    (1.0/3.0)    * rightVelocity) + (     (1.0/3.0)    * leftVelocity) ) / frameRadius ; // [rad/s]
        
        rotateFrame( vx, vy, (th_global/180) * PI ); // Rotate from Local Frame to Global Frame

        //Robot Displacement
        float delta_x  = vx  * delta_time;
        float delta_y  = vy  * delta_time;
        float delta_th = vth * delta_time;

        //Robot Position update
        x_global  = x_global  + delta_x;
        y_global  = y_global  + delta_y;
        th_global = th_global + ((delta_th / PI) * 180);  //  [degrees/s]

        th_global = Remainder(th_global, 360);

        float desired_position[3] = { desired_x, desired_y, desired_th };  // [cm], [cm], [degrees]
        float current_position[3] = { x_global , y_global, th_global };  // [cm], [cm], [degrees]

        float x_diff  = desired_position[0] - current_position[0];
        float y_diff  = desired_position[1] - current_position[1];
        float th_diff = desired_position[2] - current_position[2];

        if      ( th_diff < -180 ) { th_diff = th_diff + 360; }
        else if ( th_diff >  180 ) { th_diff = th_diff - 360; }

        float max_linear_speed = 10.0; // cm/s
        float max_ang_speed = 0.5; // rad/s

        desired_vx = map_func( x_diff, -15.0, 15.0, -1 * max_linear_speed, max_linear_speed );  // [cm], [cm], [cm], [cm/s], [cm/s]
        desired_vx = max( min( desired_vx, max_linear_speed ), -1 * max_linear_speed );
        if( abs(x_diff) < linear_tolerance ){ desired_vx = 0; }

        desired_vy = map_func( y_diff, -15.0, 15.0, -1 * max_linear_speed, max_linear_speed );  // [cm], [cm], [cm], [cm/s], [cm/s]
        desired_vy = max( min( desired_vy, max_linear_speed ), -1 * max_linear_speed );
        if( abs(y_diff) < linear_tolerance ){ desired_vy = 0; }

        desired_vth = map_func( th_diff, -15.0, 15.0, -1 * max_ang_speed, max_ang_speed );      // [degrees], [degrees], [degrees], [rad/s], [rad/s]
        desired_vth = max( min( desired_vth, max_ang_speed ), -1 * max_ang_speed );
        if( abs(th_diff) < angular_tolerance ){ desired_vth = 0; }

        rotateFrame( desired_vx, desired_vy, -(th_global/180) * PI ); // Rotate from Global Frame to Local Frame

        //Inverse Kinematics
        float desired_back_speed  = ( (-cos(PI/2)    * desired_vx) + (-sin(PI/2)    * desired_vy) + ( frameRadius * desired_vth) );  // [cm/s]
        float desired_right_speed = ( (-cos(7*PI/6)  * desired_vx) + (-sin(7*PI/6)  * desired_vy) + ( frameRadius * desired_vth) );  // [cm/s]
        float desired_left_speed  = ( (-cos(11*PI/6) * desired_vx) + (-sin(11*PI/6) * desired_vy) + ( frameRadius * desired_vth) );  // [cm/s]

        int backPWM  = backControl.motorControl(desired_back_speed, backVelocity, delta_time);
        int leftPWM  = leftControl.motorControl(desired_left_speed, leftVelocity, delta_time);
        int rightPWM = rightControl.motorControl(desired_right_speed, rightVelocity, delta_time);
      

        printf("des_vel_l: %f  ", desired_left_speed);
        printf("des_vel_r: %f  ", desired_right_speed);
        printf("des_vel_b: %f\n", desired_back_speed);

        printf("leftPWM: %d   ", leftPWM);
        printf("rightPWM: %d   ", rightPWM);
        printf("backPWM: %d\n", backPWM);

        printf("enc: %d\n", current_enc_r);

        printf("x: %f   ", x_global);
        printf("y: %f   ", y_global);
        printf("th: %f\n", th_global);

        if ( !stop_button.Get() ){ 
          leftMotor(0);
          rightMotor(0);
          backMotor(0);
        }else{
          leftMotor(leftPWM);
          rightMotor(rightPWM);
          backMotor(backPWM);
        }

        delay(100);

    }while( desired_vx != 0 || desired_vy != 0 || desired_vth != 0 );


    leftMotor(0);
    rightMotor(0);
    backMotor(0);

    delay(250);
}
