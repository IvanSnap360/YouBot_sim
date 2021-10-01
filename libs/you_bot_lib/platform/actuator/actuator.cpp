#include "actuator.h"
ACTUATOR::ACTUATOR(/* args */)
{
}

ACTUATOR::~ACTUATOR()
{
}

void ACTUATOR::init(const char * sim_name, int clientID)
{
    
    simxGetObjectHandle(clientID,sim_name,&_handle,simx_opmode_blocking);
    _clientID = clientID;
    INFO_PRINT("Initialization "  << Bold << Cyan << sim_name << Green << " Done "  << Reset);
    setAngularVelocity(0.0);
}

void ACTUATOR::setAngularVelocity(double angular_velocity)
{
    simxSetJointTargetVelocity(_clientID,_handle,(angular_velocity * 180.0 / pi),simx_opmode_oneshot);
}

double ACTUATOR::getAngularVelocity()
{
    simxGetObjectFloatParameter(_clientID,_handle,2012,&_curr_vel,simx_opmode_streaming);
    return (_curr_vel * (pi / 180.0));
}
