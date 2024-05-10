#ifndef MOVE
#define MOVE

#include "math.h"

#include "functions.h"
#include "constants.h"
#include "hardware_interface.h"

//Robot Position
static float x = 0;    //Robot Global Position on the X  axis  [cm]
static float y = 0;    //Robot Global Position on the Y  axis  [cm]
static float th = 0;   //Robot Global Position on the Th axis  [degrees]

static int current_enc_l = 0;
static int previous_enc_l = 0;

static int current_enc_r = 0;
static int previous_enc_r = 0;

static int current_enc_b = 0;
static int previous_enc_b = 0;

static float linear_tolerance  = 5;  //  [cm]
static float angular_tolerance = 3;  //  [degrees]

//Time
static int current_time;
static int previous_time;

//Functions protofunctions
void PositionDriver( float desired_x, float desired_y, float desired_th );

#endif

