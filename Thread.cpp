//*****************************************************************************
//
// Copyright (C) 2001 Steve Connet.  All rights reserved.
//
// Source File Name : Thread.cpp
// Author           : Steve Connet
//
// Version          : $Id: $
//
// Revision History : 
//
// $Log: $
//
//*****************************************************************************

#pragma implementation

#include <sys/time.h>
#include "thread.h"

//
//-------------------------------------------------------------------------
// Function       : Thread::Thread()
//
// Implementation : Constructor
//
//-------------------------------------------------------------------------
//
Thread::Thread() :
   m_tid(0),
   m_bKillEventSet(false)
{
  pthread_mutex_init(&m_killLock, NULL);
  pthread_cond_init(&m_killCondition, NULL);
}


//
//-------------------------------------------------------------------------
// Function       : Thread::~Thread()
//
// Implementation : Destructor
//
//-------------------------------------------------------------------------
//
Thread::~Thread()
{
    pthread_mutex_destroy(&m_killLock);
    pthread_cond_destroy(&m_killCondition);
}

//
//-------------------------------------------------------------------------
// Function       : void Thread::Start()
//
// Implementation : Spawns the thread in the subclassed object
//
//-------------------------------------------------------------------------
//
void Thread::Start()
{
    if(!m_tid)
        pthread_create(&m_tid, NULL, &_Thread, this);

} // Start


//
//-------------------------------------------------------------------------
// Function       : void Thread::Stop()
//
// Implementation : Sets the kill event to true and signals the kill 
//                  signal. It waits for spawned threads to die. 
//
//-------------------------------------------------------------------------
//
void Thread::Stop()
{
    pthread_mutex_lock(&m_killLock);
    m_bKillEventSet = true;
    pthread_mutex_unlock(&m_killLock);
    pthread_cond_signal(&m_killCondition);

    pthread_join(m_tid, NULL);
    m_tid = 0;
    m_bKillEventSet = false;

} // Stop


//
//-------------------------------------------------------------------------
// Function       : struct timespec Thread::MakeTimespec(int nTimeout)
//
// Implementation : Returns a timespec struct to be used in a
//                  pthread_cond_timedwait. nTimeout must be in 
//                  milliseconds.
//
//-------------------------------------------------------------------------
//
struct timespec Thread::MakeTimespec(int nTimeout)
{
    const long billion = 1000000000L;

    struct timespec deadline;
    struct timespec interval;

    interval.tv_sec = nTimeout / 1000;
    interval.tv_nsec = (nTimeout % 1000) * 1000000L;

    struct timeval now;
    gettimeofday(&now, NULL);
    deadline.tv_sec = now.tv_sec;
    deadline.tv_nsec = now.tv_usec * 1000;

    if((deadline.tv_nsec += interval.tv_nsec) >= billion)
    {
        deadline.tv_nsec -= billion;
        deadline.tv_sec += 1;
    }
    deadline.tv_sec += interval.tv_sec;

    return deadline;

} // MakeTimespec


//
//-------------------------------------------------------------------------
// Function       : bool Thread::WaitForKillEvent(int nTimeout)
//
// Implementation : Waits specified timeout period on the kill event.
//                  nTimeout is in milliseconds. Subclassed objects
//                  should use this function in their thread function
//                  to give "breathing room" for other threads. Using
//                  this function will prevent the CPU from being railed,
//                  which is a VERY BAD thing.
//
//                  This function returns TRUE if the kill event has
//                  been signalled (ie. the Stop function was called).
//                  When this function returns true, the subclassed
//                  object's thread should exit!
//
//-------------------------------------------------------------------------
//
bool Thread::WaitForKillEvent(int nTimeout)
{
    pthread_mutex_lock(&m_killLock);

    bool bKillEventSet = m_bKillEventSet;
    if(!bKillEventSet)
    {
        struct timespec tm = MakeTimespec(nTimeout);
        pthread_cond_timedwait(&m_killCondition, &m_killLock, &tm);
    }

    pthread_mutex_unlock(&m_killLock);
    return bKillEventSet;

} // WaitForKillEvent
