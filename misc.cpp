//*****************************************************************************
//
// Copyright (C) 2001 Steve Connet.  All rights reserved.
//
// Source File Name : misc.cpp
// Author           : Steve Connet
//
// Version          : $Id: $
//
// Revision History : 
//
// $Log: $
//
//*****************************************************************************

#include "misc.h"

using namespace std;
using namespace ConnetUtils;

//
//-------------------------------------------------------------------------
// Method         : trimLeft
//
// Implementation : Remove whitespace from the left of the string
// 
//-------------------------------------------------------------------------
//
string trimLeft(const string &value)
{
  string::size_type where = value.find_first_not_of(' ');
  
  // string has nothing but space
  if(where == string::npos)
    return string();
   
  // string has no leading space,
  // don't copy its contents (assuming COW strings)
  if(where == 0)
    return value;
   
  return value.substr(where);

} // trimLeft

//
//-------------------------------------------------------------------------
// Method         : trimRight
//
// Implementation : Remove whitespace from the right of the string
// 
//-------------------------------------------------------------------------
//
string trimRight(const string &value)
{
  string::size_type where = value.find_last_not_of(' ');
  
  // string has nothing but space
  if(where == string::npos)
    return string();
  
  // string has no trailing space, don't copy its contents
  if(where == (value.length() - 1))
    return value;
  
  return value.substr(0, where + 1);

} // trimRight

//
//-------------------------------------------------------------------------
// Method         : makeTimespec
//
// Implementation : Returns a timespec struct to be used in a
//                  pthread_cond_timedwait. nTimeout must be in
//                  milliseconds.
// 
//-------------------------------------------------------------------------
//
void makeTimespec(int timeout /* ms */, struct timespec& ts)
{
  const long billion = 1000000000L;
  
  struct timespec interval;
  interval.tv_sec = timeout / 1000;
  interval.tv_nsec = (timeout % 1000) * 1000000L;
  
  struct timeval now;
  gettimeofday(&now, NULL);
  ts.tv_sec = now.tv_sec;
  ts.tv_nsec = now.tv_usec * 1000;
  
  if((ts.tv_nsec += interval.tv_nsec) >= billion)
  {
    ts.tv_nsec -= billion;
    ts.tv_sec += 1;
  }
  
  ts.tv_sec += interval.tv_sec;
  
} // makeTimespec
