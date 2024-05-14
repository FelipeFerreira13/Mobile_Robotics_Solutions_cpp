#ifndef FUNC
#define FUNC

#include <stdio.h>
#include <stdio.h>  

#include "math.h"

enum pin_state { HIGH = 1, LOW = 0 };

long map_func(long x, long in_min, long in_max, long out_min, long out_max);
float map_func(float x, float in_min, float in_max, float out_min, float out_max);
double max( double x, double y );
int max( int x, int y );
double min( double x, double y );
int min( int x, int y );

void rotateFrame( float &x, float &y, float angle );
double Remainder( double x, double y );

#endif