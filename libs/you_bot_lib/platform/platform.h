#ifndef __PLATFORM_H__
#define __PLATFORM_H__
#include "actuator/actuator.h"
#include "../you_bot_sim_config.h"
#include "../../types_lib/axis.h"
#include "../../types_lib/velocity.h"

class PLATFORM
{
private:
    int _clinet_id;
    enum bumper
    {
        FORWARD,
        BACKWARD,
        BUMPER_COUNT
    };
    enum side
    {
        LEFT,
        RIGHT,
        SIDE_COUNT
    };
    ACTUATOR actuator[BUMPER_COUNT][SIDE_COUNT];
    void actuators_init();

    void calc_IK();
    void calc_FK();
    void calc_Odom();

public:
    PLATFORM(int clinet_id);
    void trigger();

    velocity_msg targer_velocity;
    velocity_msg current_velocity;


    ~PLATFORM();
};




#endif // __PLATFORM_H__