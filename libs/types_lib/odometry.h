#ifndef __ODOMETRY_H__
#define __ODOMETRY_H__
#include "axis.h"
struct odometry_msg
{
    vectors position;
    vectors orientation;
};


#endif // __ODOMETRY_H__