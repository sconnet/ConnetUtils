//
// Security Classification: UNCLASSIFIED
//
//*****************************************************************************
//
// Copyright (C) 2001 Spectrum Astro, Inc.  All rights reserved.
//
// Contractor       : Spectrum Astro, Inc.
//                    1440 N. Fiesta Blvd
//                    Gilbert, Arizona 85233
//                    USA
//
// Source File Name : Stopwatch.h
//
// File Overview    : Performs timing in microsecond resolution
//                    Ignores timezone considerations
//
//*****************************************************************************
//

#ifndef __STOPWATCH_H_
#define __STOPWATCH_H_

#include <sys/time.h>

class Stopwatch
{
    static const long million = 1000000L;
    struct timeval st;

public:
    Stopwatch() {
        start();
    }
    void start() {
        gettimeofday(&st, NULL);
    }
    double seconds() {
        return (double)elapsed() / (double)million;
    }
    long elapsed() {  /* microseconds */
        long sec, usec;
        struct timeval now;
        gettimeofday(&now, NULL);
        sec = now.tv_sec - st.tv_sec;
        usec = now.tv_usec - st.tv_usec;
        if(now.tv_usec < st.tv_usec) {
            --sec;
            usec = now.tv_usec + (million - st.tv_usec);
        }
        return sec * million + usec;
    }
};

#endif // __STOPWATCH_H_

//*****************************************************************************
//
// Security Classification: UNCLASSIFIED
//
