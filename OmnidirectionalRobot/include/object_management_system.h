#ifndef ELEV
#define ELEV

#include "math.h"

#include "functions.h"
#include "constants.h"
#include "hardware_interface.h"

static const float pinionRadius = 1.25; //Pinion's radius [cm]

//Robot Position
static float height = 0;    //OMS height [cm]

static int current_enc = 0;
static int previous_enc = 0;

static float tolerance  = 1.5;  //  [cm]

//Time
static int current_time;
static int previous_time;

//Functions protofunctions
void OMSDriver( float desired_x, float desired_y, float desired_th );

#endif

