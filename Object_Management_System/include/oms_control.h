#ifndef ELEVATION
#define ELEVATION

#include "math.h"

#include "functions.h"
#include "constants.h"
#include "motor_control.h"
#include "hardware_interface.h"


class OMS{
    private:
        float pinionRadius = 1.25; //Pinion's radius [cm]

        //Robot Position
        float height = 1000;    //OMS height [cm]

        float low_height = 9;
        float high_height = 36;

        float tolerance  = 1.5;  //  [cm]

    public:
        OMS();
        void OMSDriver( float desired_height );
        void setHeight( float set_height ); //Set the Elevation height
        void reset( int direction ); //Send the elevator to one o f the Limit Switches

        void setGripper( int set );
};

#endif

