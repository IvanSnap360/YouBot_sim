#ifndef __PLATFORM_H__
#define __PLATFORM_H__
#include "actuator/actuator.h"
#include "../you_bot_sim_config.h"
#include "../../types_lib/axis.h"
#include "../../types_lib/velocity.h"
#include "../../types_lib/odometry.h"
#include "../../types_lib/pose.h"
#include "../../math_lib/constrain.h"
#include <math.h>
class PLATFORM
{
public:
    PLATFORM();
    void init(int clinet_id);
    void setMaxVelocities(double mvx, double mvy, double mwz);
    void setMinVelocities(double mvx, double mvy, double mwz);
    void go_trigger();
    void trigger(unsigned long long time);
    bool is_reached()
    {
        return is_done;
    }
    pose goal;
    void setGoalPosition(pose pos)
    {
        goal = pos;
        is_done = false;
    }

    

    ~PLATFORM();

private:
    double mapping(double x, double in_min, double in_max, double out_min, double out_max)
    {

        return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
        // std::cout << "ERRORR" << std::endl;
    }


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
    void calc_Odom(unsigned long long cur_time);
    void read_imu();

    velocity_msg targer_velocity;
    velocity_msg current_velocity;
    odometry_msg odom;
    
    vectors imu_accel;
    vectors imu_gyro;

    const double r = YOU_BOT_WHEEL_DEAMETER / 2;
    const double lx = YOU_BOT_WHEEL_BASE_WIDTH / 2;
    const double ly = YOU_BOT_WHEEL_BASE_LENTH / 2;

    double tvx = 0.0;
    double tvy = 0.0;
    double tvz = 0.0;

    

    double tw1 = 0.0;
    double tw2 = 0.0;
    double tw3 = 0.0;
    double tw4 = 0.0;

    double cvx = 0.0;
    double cvy = 0.0;
    double cvz = 0.0;

    double cw1 = 0.0;
    double cw2 = 0.0;
    double cw3 = 0.0;
    double cw4 = 0.0;

    double _max_vx = 0.0;
    double _max_vy = 0.0;
    double _max_wz = 0.0;

    double _min_vx = 0.0;
    double _min_vy = 0.0;
    double _min_wz = 0.0;

    bool trigger_first_call_flag = true;
    unsigned long long last_time;

    
    bool is_done = false;
    
    unsigned long long dt;

    simxFloat accel_buff[3];
    simxFloat gyro_buff[3];
};

#endif // __PLATFORM_H__