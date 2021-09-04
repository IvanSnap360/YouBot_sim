#include "simConst.h"
#include "../help_lib/print_lib.h"
//################################# SIMULATOR ################################
#define SIM_IP_ADDRESS "192.168.0.2"
#define SIM_PORT       19997
#define SIM_waitUntilConnected true
#define SIM_doNotReconnectOnceDisconnected true
#define SIM_timeOutInMs 5000
#define SIM_commThreadCycleInMs 5

/*
inline void getSimError(int res, const char * msg)
{
    INFO_PRINT(msg);
    switch (res)
    {
    case simx_return_ok:
        INFO_PRINT(">>> OK")
        break;
    case simx_return_novalue_flag:
        WARN_PRINT(">>> There is no command reply in the input buffer. This should not always be considered as an error, depending on the selected operation mode")
        break;
    case simx_return_timeout_flag:
        WARN_PRINT(">>> The specified operation mode is not supported for the given function")
        break;
    case simx_return_illegal_opmode_flag:
        WARN_PRINT(">>> The function caused an error on the server side (e.g. an invalid handle was specified)")
        break;
    case simx_return_remote_error_flag:
        ERROR_PRINT(">>> The function caused an error on the server side (e.g. an invalid handle was specified)");
        break;
    case simx_return_split_progress_flag:
        WARN_PRINT(">>> The communication thread is still processing previous split command of the same type");
        break;
    case simx_return_local_error_flag:
        ERROR_PRINT(">>> The function caused an error on the client side");
        break;
    case simx_return_initialize_error_flag:
        ERROR_PRINT(">>> simxStart was not yet called");
        break;   
    }
}*/