#include "movement.h"



const float max_motor_speed = 60.0; // [cm/s]
float correction = 0; //  [PWM]

float motorControl(float desiredSpeed, float currentSpeed) {

  float Desired_PWM = (desiredSpeed / max_motor_speed) * 255.0; // Proportional PWM regarding MAX speed of the motor [PWM]

  float error = desiredSpeed - currentSpeed;  // [cm/s]

  //Defines a proportional increment to the PWM
  float incrementPWM = map_func(error, -1 * max_motor_speed, max_motor_speed, -100, 100);  // ( [m], [m], [m], [PWM], [PWM] )
  incrementPWM = incrementPWM * delta_time;

  correction = correction + incrementPWM;

  Desired_PWM = max( min( Desired_PWM + correction, 255.0 ), -255.0 );

  if (desiredSpeed == 0){ Desired_PWM = 0; }

  return Desired_PWM;
}


void leftMotor( int PWM ){
    PWM = PWM / 255;
    motor_left.SetMotorPWM( PWM );
}

void rightMotor( int PWM ){
    PWM = PWM / 255;
    motor_right.SetMotorPWM( PWM );
}

void PositionDriver( float desired_x, float desired_y, float desired_th ) {

    bool reach_linear_tol  = false;
    bool reach_angular_tol = false;
   
    float move_magnitude = 0;

    current_time = millis();
    previous_time - millis();

    do{
        current_time = millis();
        delta_time = float(current_time - previous_time) / 1000.0; // [s]
        previous_time = current_time;

        current_enc_l = enc_left.GetEncoderCount();
        float delta_enc_l = current_enc_l - previous_enc_l;
        previous_enc_l = current_enc_l;

        current_enc_r = enc_right.GetEncoderCount();
        float delta_enc_r = current_enc_r - previous_enc_r;
        previous_enc_r = current_enc_r;

        //Wheels Velocity
        float leftVelocity  = (((2 * PI * wheelRadius * delta_enc_l) / ((732 * 2) * delta_time)));   // [cm/s]
        float rightVelocity = (((2 * PI * wheelRadius * delta_enc_r) / ((732 * 2) * delta_time)));   // [cm/s]

        if ( isnan(leftVelocity) ) { leftVelocity  = 0; }
        if ( isnan(rightVelocity) ){ rightVelocity = 0; }

        float th_radius = (( th / 180.0 ) * PI);  //Robot Global Position on the Th axis  [rad]
        
        //Forward Kinematics
        float vx  = (( rightVelocity + leftVelocity ) / 2) * cos( th_radius );  // [cm/s]
        float vy  = (( rightVelocity + leftVelocity ) / 2) * sin( th_radius );  // [cm/s]
        float vth = (( rightVelocity - leftVelocity ) / frameRadius) * 0.525;             // [rad/s]

        //Robot Displacement
        float delta_x  = vx  * delta_time;
        float delta_y  = vy  * delta_time;
        float delta_th = vth * delta_time;

        //Robot Position update
        x  = x  + delta_x;
        y  = y  + delta_y;
        th = th + ((delta_th / PI) * 180);  //  [degrees/s]

        float desired_position[3] = { desired_x, desired_y, desired_th };  // [cm], [cm], [degrees]
        float current_position[3] = { x , y, th };  // [cm], [cm], [degrees]

        float x_diff  = desired_position[0] - current_position[0];
        float y_diff  = desired_position[1] - current_position[1];
        float th_diff = desired_position[2] - current_position[2];

        float move_ang = atan2( y_diff, x_diff ); // [rad]
        move_ang = (move_ang / PI) * 180;         // [degrees]

        move_magnitude = sqrt( pow( x_diff, 2 ) + pow( y_diff, 2 ) ); // [cm]

        //When the robot reaches the linear goal tries to reach the desired angle
        if ( move_magnitude < linear_tolerance || reach_linear_tol ){
          reach_linear_tol = true;
          move_magnitude = 0;
          move_ang = th_diff;
        }
        else{
          move_ang = move_ang - current_position[2];
        }

        if      ( move_ang < -180 ) { move_ang = move_ang + 360; }
        else if ( move_ang >  180 ) { move_ang = move_ang - 360; }

        float max_ang_speed = 1; // rad/s
        setPoint_angular = map_func( move_ang, -20.0, 20.0, -1 * max_ang_speed, max_ang_speed );               // [degrees], [degrees], [degrees], [rad/s], [rad/s]
        setPoint_angular = max( min( setPoint_angular, max_ang_speed ), -1 * max_ang_speed );
        float max_linear_speed = 10; // cm/s
        setPoint_linear  = map_func( move_magnitude, -10.0, 10.0, -1 * max_linear_speed, max_linear_speed );  // [cm], [cm], [cm], [cm/s], [cm/s]
        setPoint_linear  = max( min( setPoint_linear, max_linear_speed ), -1 * max_linear_speed );


        if ( abs(move_ang) > 10 ){ setPoint_linear = 0; }
        if ( move_magnitude < linear_tolerance && abs(th_diff) < angular_tolerance ) { setPoint_linear  = 0; setPoint_angular = 0; }

        //Inverse Kinematics
        float desired_right_speed = ((2 * setPoint_linear) + (setPoint_angular * frameRadius)) / 2;   // [cm/s]
        float desired_left_speed  = ((2 * setPoint_linear) - (setPoint_angular * frameRadius)) / 2;   // [cm/s]

        int leftPWM  = motorControl(desired_left_speed, leftVelocity);

        int rightPWM = motorControl(desired_right_speed, rightVelocity);

        printf("enc_left: %d  ", current_enc_l);
        printf("enc_right: %d\n", current_enc_r);
        printf("leftPWM: %d   ", leftPWM);
        printf("rightPWM: %d\n", rightPWM);
        printf("x: %f   ", x);
        printf("y: %f   ", y);
        printf("th: %f\n", th);
        printf("time: %f\n", delta_time);

        leftMotor(leftPWM);
        rightMotor(rightPWM);

        delay(100);

    }while( setPoint_linear != 0 || setPoint_angular != 0 );

    leftMotor(0);
    rightMotor(0);
    delay(250);
}

