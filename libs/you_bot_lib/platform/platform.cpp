#include "platform.h"

PLATFORM::PLATFORM(int clinet_id)
{
    _clinet_id = clinet_id;
}

PLATFORM::~PLATFORM()
{
}

void PLATFORM::actuators_init()
{
    actuator[FORWARD][LEFT].init(YOU_BOT_LEFT_FORWARD_WHEEL_MOTOR_SIM_NAME,_clinet_id);
    actuator[FORWARD][RIGHT].init(YOU_BOT_RIGHT_FORWARD_WHEEL_MOTOR_SIM_NAME,_clinet_id);
    actuator[BACKWARD][LEFT].init(YOU_BOT_LEFT_BACKWARD_WHEEL_MOTOR_SIM_NAME,_clinet_id);
    actuator[BACKWARD][RIGHT].init(YOU_BOT_RIGHT_BACKWARD_WHEEL_MOTOR_SIM_NAME,_clinet_id);
}

void PLATFORM::trigger()
{
    calc_IK();
    calc_FK();
    calc_Odom();
}

void PLATFORM::calc_IK()
{
    
}