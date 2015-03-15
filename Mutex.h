//*****************************************************************************
//
// Copyright (C) 2001 Steve Connet.  All rights reserved.
//
// Source File Name : Mutex.h
// Author           : Steve Connet
//
// Version          : $Id: Mutex.h,v 1.3 2015/03/14 23:44:56 clu Exp $
//
// File Overview    : class for single locking mechanism and condition
//
// Revision History :
//
// $Log: Mutex.h,v $
// Revision 1.3  2015/03/14 23:44:56  clu
// astyle code formatter applied
//
// Revision 1.2  2002/01/11 03:41:49  sconnet
// *** empty log message ***
//
// Revision 1.1  2001/11/08 06:17:14  sconnet
// Initial revision
//
//
//*****************************************************************************

//#pragma interface

#ifndef __MUTEX_H_
#define __MUTEX_H_

#include <sys/time.h>
#include <pthread.h>

//namespace ConnetUtils
//{

class Mutex
{
public:
    Mutex();
    ~Mutex();

    void lock()    {
        pthread_mutex_lock(&mutex);
    }
    void unlock()  {
        pthread_mutex_unlock(&mutex);
    }
    bool trylock() {
        return (0 == pthread_mutex_trylock(&mutex));
    }
    void reset()   {
        event = false;
    }

    void signal();
    void broadcast();
    void waitEvent();
    bool waitEvent(int timeout /* ms */);

private:
    bool event;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
};

//}

#endif // __MUTEX_H_
