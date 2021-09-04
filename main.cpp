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
void setup()
{
    
}

void loop()
{   
    kbot.platform.trigger();
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