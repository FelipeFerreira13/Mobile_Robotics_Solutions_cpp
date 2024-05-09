#include "functions.h"


// void analogWrite( int pin, int value)
// {
//     if ( pin < 22 && pin > 11 ){
//         PWM servo_gripper( vmx_ptr, pin );
//         servo_gripper.SetAngle( value );
//         vmx_ptr->time.DelayMilliseconds(100);
//     }
//     else{ printf("Selected pin not a PWM\n"); }
// }

// void digitalWrite( int pin, int value){
//     if ( pin < 22 && pin > 11 ){
//         digitalOutput DO( vmx_ptr, pin );
//         DO.SetPinState( value );
//     }
//     else{ printf("Selected pin not a DO\n"); }
// }

void delay( uint32_t ms ){
    vmx_ptr->time.DelayMilliseconds( ms );
}
void delayMicroseconds( uint32_t us ){
    vmx_ptr->time.DelayMicroseconds(us);
}
uint32_t millis( ){
    uint32_t time = vmx_ptr->time.GetCurrentMicroseconds();
    time = time / 1000;
    return time;
}

long map_func(long x, long in_min, long in_max, long out_min, long out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
float map_func(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

double max( double x, double y ){ return x > y ? x : y; }
int max( int x, int y ){ return x > y ? x : y; }
double min( double x, double y ){ return x > y ? y : x; }
int min( int x, int y ){ return x > y ? y : x; }

void rotateFrame( float &x, float &y, float angle ){
  float x_aux = (cos( angle ) * (x)) + (-sin(angle) * (y));
  float y_aux = (sin( angle ) * (x)) + ( cos(angle) * (y));

  x = x_aux;
  y = y_aux;
}

double Remainder( double x, double y ){
    double Quotient = floor( x / y );
    double Remainder = x - (y * Quotient);

    return Remainder;
}

