#include <iostream>
#include <chrono>

extern "C"
{
#include "libs/sim_lib/extApi.h"
#include "libs/sim_lib/extApiPlatform.h"
#include "libs/sim_lib/simConst.h"
#include "libs/sim_lib/simConfig.h"
}

#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <X11/keysymdef.h>

#include "libs/help_lib/print_lib.h"
#include "libs/you_bot_lib/you_bot.h"

unsigned long long real_time_ms;

Display *dpy = XOpenDisplay(":0");
using namespace std::chrono;

int clientID;
YOU_BOT kbot;

pose goal[6];
int goal_index = 0;
void setup()
{
    // kbot.platform.targer_velocity.linear.x = -0.005;
    // kbot.platform.targer_velocity.linear.y = 0.005;
    // kbot.platform.targer_velocity.angular.z = 0.01;
    goal[0].position.x = 0.5;
    goal[0].position.y = 0.5;

    goal[1].position.x = 0.5;
    goal[1].position.y = -0.5;

    goal[2].position.x = -0.5;
    goal[2].position.y = -0.5;

    goal[3].position.x = -0.5;
    goal[3].position.y = 0.5;

    goal[4].position.x = 0.5;
    goal[4].position.y = 0.5;

    goal[5].position.x = 0.0;
    goal[5].position.y = 0.0;
}

void loop()
{
    // println(kbot.platform.odom.position.x << "  " << kbot.platform.odom.position.y << "   " << kbot.platform.odom.orientation.z);
    // println(kbot.platform.imu_gyro.z);
    kbot.platform.goal.position.x = 0.05;
    
    kbot.platform.go_trigger();
    kbot.platform.trigger(real_time_ms);
}

//#################################################################################################################

bool key_is_pressed(KeySym ks)
{
    char keys_return[32];
    XQueryKeymap(dpy, keys_return);
    KeyCode kc2 = XKeysymToKeycode(dpy, ks);
    bool isPressed = !!(keys_return[kc2 >> 3] & (1 << (kc2 & 7)));
    return isPressed;
}

int main()
{
    println("########## CONNECTING TO SIMULATOR ##########");

    int clientID = simxStart(
        (simxChar *)SIM_IP_ADDRESS,
        SIM_PORT,
        SIM_waitUntilConnected,
        SIM_doNotReconnectOnceDisconnected,
        SIM_timeOutInMs,
        SIM_commThreadCycleInMs);

    println("########## CONNECTING TO SIMULATOR DONE ##########");
    print("Client ID: ");
    println(clientID);

    kbot.init(clientID);

    simxStartSimulation(clientID, simx_opmode_oneshot);
    println("########## START SIM ##########");
    println("For stop press Ctrl + Q ");

    setup();
    while (1)
    {
        milliseconds ms = duration_cast<milliseconds>(
            system_clock::now().time_since_epoch());
        real_time_ms = ms.count();

        loop();
        if (key_is_pressed(XK_Control_L) && key_is_pressed(XK_q))
        {
            println("########## STOP SIM ##########");
            int res = simxStopSimulation(clientID, simx_opmode_blocking);
            break;
        }
    }
    XCloseDisplay(dpy);
    simxFinish(clientID);
    return 0;
}