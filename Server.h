//*****************************************************************************
//
// Copyright (C) 2001 Steve Connet.  All rights reserved.
//
// Source File Name : Server.h
// Author           : Steve Connet
//
// Version          : $Id: Server.h,v 1.4 2015/03/14 23:44:56 clu Exp $
//
// File Overview    : Listens for incoming connections and calls a user's
//                    callback so the user can read the data.
//
// Revision History :
//
// $Log: Server.h,v $
// Revision 1.4  2015/03/14 23:44:56  clu
// astyle code formatter applied
//
// Revision 1.3  2002/02/03 03:49:58  steve
// added static connect method
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

#ifndef __SERVER_H_
#define __SERVER_H_

#include <vector>
#include <string>
#include "Exception.h"
#include "Mutex.h"

// file descriptor is passed to you, read from it and return false if
// client disconnects or cannot read from file descriptor, or return
// true if the read was successful
//typedef bool (*Callback)(int fd, void *data = 0);
typedef bool (*Callback)(int fd, void *data);

//namespace ConnetUtils
//{

class Server
{
    int fd;
    int port;
    bool listening;

    Callback callbackFn;
    void *callbackData;

    std::vector<int> client;
    Mutex mutex;

public:
    Server();
    ~Server();

    // use default args to use values passed to constructor
    int listen(int port = 0, Callback fn = 0, void *data = 0) throw(Exception);
    int select() throw(Exception);
    void quit();

    // returns the connected file descriptor
    static int connect(const std::string &host, int port) throw(Exception);
};

//}

#endif // __SERVER_H_
