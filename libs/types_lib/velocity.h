#ifndef __VELOCITY_H__
#define __VELOCITY_H__
#include "axis.h"

struct velocity_msg
{
    vectors linear;
    vectors angular;
};


#endif // __VELOCITY_H__