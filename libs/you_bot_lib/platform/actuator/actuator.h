#ifndef __ACTUATOR_H__
#define __ACTUATOR_H__
extern "C"
{
#include "libs/sim_lib/extApi.h"
#include "libs/sim_lib/extApiPlatform.h"
#include "libs/sim_lib/simConst.h"
#include "libs/sim_lib/simConfig.h"
}

#include "../../../help_lib/print_lib.h"
class ACTUATOR
{    
public:
    ACTUATOR();
    void init(const char * sim_name, int clientID);
    void setAngularVelocity(double angular_velocity);
    double getAngularVelocity();

    ~ACTUATOR();
private:
    const double pi = 3.14159265359;

    int _handle;
    int _clientID;
    simxFloat _curr_vel;
};



#endif // __ACTUATOR_H__