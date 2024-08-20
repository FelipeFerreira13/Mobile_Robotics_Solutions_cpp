#pragma once

#include <stdio.h>  
#include <string.h> 
#include <inttypes.h>

#include "hardware_interface_vmxpi.h"

class AHRSCallback : public IVMXTimestampedAHRSDataSubscriber
{
	vmx::AHRS& ahrs;
    public:
        AHRSCallback( vmx::AHRS& ahrs_ref ) : ahrs(ahrs_ref) {}
        virtual ~AHRSCallback() {}
        virtual void timestampedDataReceived( long system_timestamp, long sensor_timestamp, const AHRSProtocol::AHRSUpdateBase& sensor_data, void * context )
        {
            // printf("AHRS Callback Data Received.  SysTimestamp:  %ld, SensorTimestamp:  %ld\n",
            //         system_timestamp,
            //         sensor_timestamp);
            // printf("Yaw: %f\n", yaw);
            // printf("Yaw, Pitch, Roll:  %f, %f, %f\n", ahrs.GetYaw(), ahrs.GetPitch(), ahrs.GetRoll());
        }
        double getYaw(){ return ahrs.GetYaw();; }
        void Init( );
};