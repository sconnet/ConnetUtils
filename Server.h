//*****************************************************************************
//
// Copyright (C) 2001 Steve Connet.  All rights reserved.
//
// Source File Name : Server.h
// Author           : Steve Connet
//
// Version          : $Id: $
//
// File Overview    : Listens for incoming connections and calls a user's
//                    callback so the user can read the data.
//
// Revision History : 
//
// $Log: $
//
//*****************************************************************************

#pragma interface

#ifndef __SERVER_H_
#define __SERVER_H_

#include <vector>
#include "Exception.h"
#include "Mutex.h"

// file descriptor is passed to you, read from it and return false if
// client disconnects or cannot read from file descriptor, or return
// true if the read was successful
typedef bool (*Callback)(int, void*);

namespace ConnetUtils
{

class Server
{
  int fd;
  int port;
  bool listening;

  Callback callbackFn;
  void* callbackData;

  std::vector<int> client;
  Mutex mutex;

 public:
  explicit Server(int port = 0, Callback fn = 0, void* data = 0);
  ~Server();

  // use default args to use values passed to constructor
  int listen(int port = 0, Callback fn = 0, void* data = 0) throw (Exception);
  int select() throw (Exception);
  void quit();
  void setCallback(Callback fn, void* data);
};

}

#endif // __SERVER_H_
