//*****************************************************************************
//
// Copyright (C) 2001 Steve Connet.  All rights reserved.
//
// Source File Name : TriggerQueue.h
// Author           : Steve Connet
//
// Version          : $Id: $
//
// File Overview    : queue template with auto trigger on push
//
// Revision History : 
//
// $Log: $
//
//*****************************************************************************

#ifndef __TRIGGERQUEUE_H_
#define __TRIGGERQUEUE_H_

#include <cerrno>
#include <queue>

namespace ConnetUtils
{
  
template<class T>
class TriggerQueue
{
  std::queue<T> data_queue;
  bool trigger;
  pthread_cond_t cond;
  pthread_mutex_t mutex;
  
 public:
  TriggerQueue::TriggerQueue()
    {
      pthread_mutex_init(&mutex, NULL);
      pthread_cond_init(&cond, NULL);
    }

  TriggerQueue::~TriggerQueue()
    {
      // signal all threads to wake up
      trigger(true);
      pthread_mutex_destroy(&mutex);
      pthread_cond_destroy(&cond);
    }

  void TriggerQueue::waitOnTrigger()
    {
      pthread_mutex_lock(&mutex);
  
      // turn off the trigger if the queue is empty
      if(data_queue.size() == 0)
        trigger = false;
  
      while(!trigger)
        pthread_cond_wait(&cond, &mutex);
  
      pthread_mutex_unlock(&mutex);

    } // waitOnTrigger
    
  void TriggerQueue::trigger(bool all = false)
    {      
      // turn the trigger on
      pthread_mutex_lock(&mutex);
      trigger = true;
      pthread_mutex_unlock(&mutex);
  
      if(all)
        pthread_cond_broadcast(&cond); // signal all waiting threads
      else
        pthread_cond_signal(&cond); // signal a single waiting thread

    } // trigger
  
  int size() const { return data_queue.size(); }
  
  void push(T obj, bool all = false)
    {
      data_queue.push( obj );
      trigger( all );  // true to trigger all waiting threads
    }
  
  bool pop_front(T& obj)
    {
      bool is_empty( (bool)data_queue.empty() );
      if( !is_empty )
      {
        obj = data_queue.front();
        data_queue.pop();
      }
      
      return !bEmpty;
    }
};

#endif // __TRIGGER_QUEUE_H_
