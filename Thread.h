//*****************************************************************************
//
// Copyright (C) 2001 Steve Connet.  All rights reserved.
//
// Source File Name : Thread.h
// Author           : Steve Connet
//
// Version          : $Id: Thread.h,v 1.2 2002/01/11 03:45:47 steve Exp steve $
//
// File Overview    : Base class for threadable object
//
// Revision History : 
//
// $Log: Thread.h,v $
// Revision 1.2  2002/01/11 03:45:47  steve
// *** empty log message ***
//
// Revision 1.1  2002/01/11 03:41:49  sconnet
// Initial revision
//
//
//*****************************************************************************

#pragma interface

#ifndef __THREAD_H_
#define __THREAD_H_

#include <pthread.h>

class Thread
{
  // thread id
  pthread_t m_tid;
    
  // kill event variables
  pthread_cond_t m_killCondition;
  pthread_mutex_t m_killLock;
  bool m_bKillEventSet;

  struct timespec makeTimespec(int nTimeout);

  // pure virtual function must be overridden by subclassed objects
  virtual void run() = 0;
  static void* _run(void* pData) { reinterpret_cast<Thread*>(pData)->run(); return 0; }
  
 public:
  Thread();
  virtual ~Thread();

  virtual void start();
  virtual void stop();
  bool waitForKillEvent(int nTimeout);
  pthread_t getThreadId() { return m_tid; }
};

#endif // __THREAD_H_
