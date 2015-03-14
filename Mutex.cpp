//*****************************************************************************
//
// Copyright (C) 2001 Steve Connet.  All rights reserved.
//
// Source File Name : Mutex.cpp
// Author           : Steve Connet
//
// Version          : $Id: Mutex.cpp,v 1.2 2002/01/11 03:41:49 sconnet Exp clu $
//
// Revision History :
//
// $Log: Mutex.cpp,v $
// Revision 1.2  2002/01/11 03:41:49  sconnet
// *** empty log message ***
//
// Revision 1.1  2001/11/08 06:17:14  sconnet
// Initial revision
//
//
//*****************************************************************************

#pragma implementation

#include <cerrno>

#include "misc.h"
#include "Mutex.h"

//using namespace ConnetUtils;

//
//-------------------------------------------------------------------------
// Method         : constructor
//
// Implementation : initialize
//
//-------------------------------------------------------------------------
//
Mutex::Mutex() : event(false)
{
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond, NULL);
}

//
//-------------------------------------------------------------------------
// Method         : destructor
//
// Implementation : clean up
//
//-------------------------------------------------------------------------
//
Mutex::~Mutex()
{
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);
}

//
//-------------------------------------------------------------------------
// Method         : signal
//
// Implementation : signals a thread sitting in a waitEvent
//
//-------------------------------------------------------------------------
//
void Mutex::signal()
{
    lock();
    event = true;
    unlock();
    pthread_cond_signal(&cond);

} // signal

//
//-------------------------------------------------------------------------
// Method         : broadcast
//
// Implementation : signals all threads sitting in a waitEvent
//
//-------------------------------------------------------------------------
//
void Mutex::broadcast()
{
    lock();
    event = true;
    unlock();
    pthread_cond_broadcast(&cond);

} // broadcast

//
//-------------------------------------------------------------------------
// Method         : waitEvent
//
// Implementation : waits forever until a thread calls signal or broadcast
//
//-------------------------------------------------------------------------
//
void Mutex::waitEvent()
{
    lock();
    while(!event) {
        pthread_cond_wait(&cond, &mutex);
    }
    unlock();
    event = false; // reset event

} // waitEvent

//
//-------------------------------------------------------------------------
// Method         : waitEvent(int timeout /* ms */)
//
// Implementation : waits for specified time period, in milliseconds,
//                  until a thread calls signal or broadcast
//                  returns the state of the event
//
//-------------------------------------------------------------------------
//
bool Mutex::waitEvent(int timeout /* ms */)
{
    lock();
    bool event_status(event);

    while(!event)
    {
        struct timespec deadline;
        makeTimespec(timeout, deadline);

        if(pthread_cond_timedwait(&cond, &mutex, &deadline) == ETIMEDOUT) {
            break;
        }
        else
        {
            event = false; // reset event
            event_status = event;
        }
    }
    unlock();
    return event_status;

} // waitEvent

