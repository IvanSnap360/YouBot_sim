#include "platform.h"

PLATFORM::PLATFORM()
{
}

void PLATFORM::init(int clinet_id)
{
    _clinet_id = clinet_id;
    actuators_init();
}

PLATFORM::~PLATFORM()
{
}

void PLATFORM::actuators_init()
{
    actuator[FORWARD][LEFT].init(YOU_BOT_LEFT_FORWARD_WHEEL_MOTOR_SIM_NAME, _clinet_id);
    actuator[FORWARD][RIGHT].init(YOU_BOT_RIGHT_FORWARD_WHEEL_MOTOR_SIM_NAME, _clinet_id);
    actuator[BACKWARD][LEFT].init(YOU_BOT_LEFT_BACKWARD_WHEEL_MOTOR_SIM_NAME, _clinet_id);
    actuator[BACKWARD][RIGHT].init(YOU_BOT_RIGHT_BACKWARD_WHEEL_MOTOR_SIM_NAME, _clinet_id);
}

void PLATFORM::trigger()
{
    calc_IK();
    calc_FK();
    calc_Odom();

    actuator[LEFT][FORWARD].setAngularVelocity(w1);
    actuator[LEFT][BACKWARD].setAngularVelocity(w2);
    actuator[RIGHT][FORWARD].setAngularVelocity(w3);
    actuator[RIGHT][BACKWARD].setAngularVelocity(w4);
}

void PLATFORM::calc_IK()
{
    vx = -targer_velocity.linear.x;
    vy = targer_velocity.linear.y;
    vz = targer_velocity.angular.z;

    r = YOU_BOT_WHEEL_DEAMETER / 2;
    lx = YOU_BOT_WHEEL_BASE_WIDTH / 2;
    ly = YOU_BOT_WHEEL_BASE_LENTH / 2;
    

    w1 = (1 / r) * (vx - vy - (lx + ly) * vz);
    w2 = (1 / r) * (vx + vy + (lx + ly) * vz);
    w3 = (1 / r) * (vx + vy - (lx + ly) * vz);
    w4 = (1 / r) * (vx - vy + (lx + ly) * vz);


}

void PLATFORM::calc_FK()
{
}

void PLATFORM::calc_Odom()
{
}