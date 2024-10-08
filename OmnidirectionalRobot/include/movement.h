#ifndef MOVE
#define MOVE

#include "math.h"

#include "functions.h"
#include "constants.h"
#include "motor_control.h"
#include "hardware_interface.h"

//Robot Position
static float x_global = 0;    //Robot Global Position on the X  axis  [cm]
static float y_global = 0;    //Robot Global Position on the Y  axis  [cm]
static float th_global = 0;   //Robot Global Position on the Th axis  [degrees]

static float offset_th = 0;

static int current_enc_l = 0;
static int previous_enc_l = 0;

static int current_enc_r = 0;
static int previous_enc_r = 0;

static int current_enc_b = 0;
static int previous_enc_b = 0;

static float linear_tolerance  = 2.5;  //  [cm]
static float angular_tolerance = 1;  //  [degrees]

static simpleControl leftControl;
static simpleControl rightControl;
static simpleControl backControl;

//Functions protofunctions

void PositionDriver( float desired_x, float desired_y, float desired_th );  // Defines the position to go to
void SetPosition( float x, float y, float th ); // Set the current robot position
float get_x();
float get_y();
float get_th();
void cmd_drive( float vx, float vy, float vth );

#endif

