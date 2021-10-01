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

void PLATFORM::trigger(unsigned long long time)
{
    if (trigger_first_call_flag == true)
    {
        last_time = time;
        trigger_first_call_flag = false;
    }

    calc_IK();
    calc_FK();
    read_imu();

    if (time - last_time >= 150.0)
    {
        calc_Odom(time);
        last_time = time;
    }

    actuator[LEFT][FORWARD].setAngularVelocity(tw1);
    actuator[LEFT][BACKWARD].setAngularVelocity(tw2);
    actuator[RIGHT][FORWARD].setAngularVelocity(tw3);
    actuator[RIGHT][BACKWARD].setAngularVelocity(tw4);
}

void PLATFORM::go_trigger()
{
    double dx = goal.position.x - odom.position.x;
    double dy = goal.position.y - odom.position.y;

    double dd = sqrt(pow(dx, 2) + pow(dy, 2));
    double alpha = atan2(dy, dx) *  M_PI / 180.0;



    const double offset = 0.4;
    if (abs(dx) < offset)
        targer_velocity.linear.x = 0.0;

    if (abs(dy) < offset)
        targer_velocity.linear.y = 0.0;

    println("goal.position.x: " << goal.position.x);
    println("goal.position.y: " << goal.position.y);
    println("odom.position.x: " << odom.position.x);
    println("odom.position.y: " << odom.position.y);
    println("dx: " << dx);
    println("dy: " << dy);
    println("dd: " << dd);
    println("alpha: " << alpha);
    println("targer_velocity.linear.x: " << targer_velocity.linear.x);
    println("targer_velocity.linear.y: " << targer_velocity.linear.y);
    println("###################################") 
    if (abs(dy) < offset && abs(dx) < offset) is_done = true;
}

void PLATFORM::read_imu()
{
    simxGetFloatSignal(_clinet_id, "accel_x", &accel_buff[0], simx_opmode_streaming);
    simxGetFloatSignal(_clinet_id, "accel_y", &accel_buff[1], simx_opmode_streaming);
    simxGetFloatSignal(_clinet_id, "accel_z", &accel_buff[2], simx_opmode_streaming);

    simxGetFloatSignal(_clinet_id, "gyro_x", &gyro_buff[0], simx_opmode_streaming);
    simxGetFloatSignal(_clinet_id, "gyro_y", &gyro_buff[1], simx_opmode_streaming);
    simxGetFloatSignal(_clinet_id, "gyro_z", &gyro_buff[2], simx_opmode_streaming);

    imu_accel.x = accel_buff[0];
    imu_accel.y = accel_buff[1];
    imu_accel.z = accel_buff[2];

    imu_gyro.x = gyro_buff[0];
    imu_gyro.y = gyro_buff[1];
    imu_gyro.z = gyro_buff[2];
}

void PLATFORM::calc_IK()
{
    tvx = -targer_velocity.linear.x;
    tvy = targer_velocity.linear.y;
    tvz = targer_velocity.angular.z;

    tvx = constrain(tvx, YOU_BOT_PLATFORM_X_MAX_VELOCITY, YOU_BOT_PLATFORM_X_MIN_VELOCITY);
    tvy = constrain(tvy, YOU_BOT_PLATFORM_Y_MAX_VELOCITY, YOU_BOT_PLATFORM_Y_MIN_VELOCITY);
    tvz = constrain(tvz, YOU_BOT_PLATFORM_Z_MAX_VELOCITY, YOU_BOT_PLATFORM_Z_MIN_VELOCITY);

    tw1 = (1.0 / r) * (tvx - tvy - (lx + ly) * tvz);
    tw2 = (1.0 / r) * (tvx + tvy + (lx + ly) * tvz);
    tw3 = (1.0 / r) * (tvx + tvy - (lx + ly) * tvz);
    tw4 = (1.0 / r) * (tvx - tvy + (lx + ly) * tvz);
}

void PLATFORM::calc_FK()
{

    cw1 = actuator[LEFT][FORWARD].getAngularVelocity();
    cw2 = actuator[LEFT][BACKWARD].getAngularVelocity();
    cw3 = actuator[RIGHT][FORWARD].getAngularVelocity();
    cw4 = actuator[RIGHT][BACKWARD].getAngularVelocity();

    cvx = (cw1 + cw2 + cw3 + cw4) * (r / 4.0);
    cvy = (-cw1 + cw2 + cw3 - cw4) * (r / 4.0);
    cvz = (-cw1 + cw2 - cw3 + cw4) * (r / (4.0 * (lx + ly)));

    current_velocity.linear.x = -cvx;

    current_velocity.linear.y = cvy;
    current_velocity.angular.z = cvz;
}

void PLATFORM::calc_Odom(unsigned long long cur_time)
{

    if (targer_velocity.linear.x == 0)
        current_velocity.linear.x = 0.0;

    if (targer_velocity.linear.y == 0)
        current_velocity.linear.y = 0.0;

    if (targer_velocity.angular.z == 0)
        current_velocity.angular.z = 0.0;

    dt = cur_time - last_time;
    // std::cout << dt << std::endl;
    double v = sqrt(pow(cvx, 2) + pow(cvy, 2));
    double alpha_v = atan2(cvy, cvx) - 1.57;

    if (targer_velocity.linear.x == 0 && targer_velocity.linear.y == 0)
    {
        v = 0.0;
        alpha_v = 0.0;
    }
    if (targer_velocity.angular.z == 0)
        cvz = 0.0;

    double dx = v * (dt / 100.0) * cos(alpha_v);
    double dy = v * (dt / 100.0) * sin(alpha_v);
    double dth = cvz * (dt / 100.0);
    // std::cout << "current_velocity.linear.x: " <<  current_velocity.linear.x << std::endl;
    // std::cout << "current_velocity.linear.y: " <<  current_velocity.linear.y << std::endl;
    // std::cout << "current_velocity.angular.z: " <<  current_velocity.angular.z << std::endl;
    // std::cout << v << "   " << alpha_v << std::endl;
    // std::cout << dx << "   " << dy << "  "<< dth << std::endl;
    odom.position.x += dx;
    odom.position.y += dy;
    odom.orientation.z += dth;

    last_time = cur_time;
}

void PLATFORM::setMaxVelocities(double mvx, double mvy, double mwz)
{
    _max_vx = mvx;
    _max_vy = mvy;
    _max_wz = mwz;
}

void PLATFORM::setMinVelocities(double mvx, double mvy, double mwz)
{
    _min_vx = mvx;
    _min_vy = mvy;
    _min_wz = mwz;
}