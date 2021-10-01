#ifndef __CONSTRAIN_H__
#define __CONSTRAIN_H__

inline double constrain(double val, double max, double min)
{
    if (val > max)
    {
        val = max;
    }
    else if (val < min)
    {
        val = min;
    }

    return val;
}



#endif // __CONSTRAIN_H__