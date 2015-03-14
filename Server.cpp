//*****************************************************************************
//
// Copyright (C) 2001 Steve Connet.  All rights reserved.
//
// Source File Name : Server.cpp
// Author           : Steve Connet
//
// Version          : $Id: Server.cpp,v 1.3 2002/02/03 03:49:47 steve Exp clu $
//
// Revision History :
//
// $Log: Server.cpp,v $
// Revision 1.3  2002/02/03 03:49:47  steve
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

#pragma implementation

#include <netinet/in.h> // sockaddr_in
#include <sys/socket.h> // AF_INET, shutdown
#include <fcntl.h>      // fcntl
#include <netdb.h>      // gethostbyname
#include <arpa/inet.h>  // inet_ntoa
#include <unistd.h>     // close,read/write

#include <cerrno>
#include <algorithm>
#include <iostream>

#include "Server.h"

using namespace std;
//using namespace ConnetUtils;

//
//-------------------------------------------------------------------------
// Method         : constructor
//
// Implementation : default constructor
//
//-------------------------------------------------------------------------
//
Server::Server() :
    fd(-1),
    port(-1),
    listening(false),
    callbackFn(NULL),
    callbackData(NULL)
{
} // constructor


//
//-------------------------------------------------------------------------
// Method         : destructor
//
// Implementation : clean up
//
//-------------------------------------------------------------------------
//
Server::~Server()
{
    quit();

} // destructor

//
//-------------------------------------------------------------------------
// Method         : listen
//
// Implementation : Starts listening for connections.
//
//-------------------------------------------------------------------------
//
int Server::listen(int port, Callback fn, void *data = 0) throw(Exception)
{
    if(listening) {
        return 0;
    }

    // override port or callback
    this->port = port;
    callbackFn = fn;
    callbackData = data;

    // create our listening socket
    if((fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        throw(Exception("socket creation failed", __FILE__, __LINE__));
    }

    // allow rebinding of this socket
    long l = 1;
    setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &l, sizeof(long));

    // bind to port and listen for connections
    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons((short) port);
    if((::bind(fd, (struct sockaddr *) &server, sizeof(struct sockaddr_in)) == -1) || (::listen(fd, SOMAXCONN) == -1))
    {
        close(fd);
        throw(Exception("bind or listen failed", __FILE__, __LINE__));
    }

    listening = true;
    return 0;

} // listen

//
//-------------------------------------------------------------------------
// Method         : select
//
// Implementation : reads incoming data
//
//-------------------------------------------------------------------------
//
int Server::select() throw(Exception)
{
    fd_set read_set;
    FD_ZERO(&read_set);

    // keep reading data until we are told to stop
    while(!mutex.waitEvent(0))
    {
        // make sure users callback is still valid
        if(!callbackFn)
        {
            quit();
            throw(Exception("User callback function is not set", __FILE__, __LINE__));
        }

        mutex.lock();

        // setup for select
        int max_fd = fd;
        if(!client.empty()) {
            max_fd = *max_element(client.begin(), client.end());
        }

        FD_SET(fd, &read_set);
        for(unsigned int n = 0; n < client.size(); n++) {
            FD_SET(client[n], &read_set);
        }

        // wait for incoming connection
        if(::select(max_fd + 1, &read_set, NULL, NULL, NULL) <= 0)
        {
            if(errno == EINTR) { // exit on signal
                break;
            }
            else {
                throw(Exception("select failed", __FILE__, __LINE__));
            }
        }

        // check each fd for readability
        for(vector<int>::iterator cur(client.begin()); cur != client.end(); ++cur)
        {
            int client_fd = *cur;

            // call user's callback if fd is readable
            if(FD_ISSET(client_fd, &read_set))
            {
                FD_CLR(client_fd, &read_set);

                // call user's callback fn
                if(!callbackFn(client_fd, callbackData))
                {
                    shutdown(client_fd, SHUT_RDWR);
                    close(client_fd);
                    //          client.erase( remove(client.begin(), client.end(), client_fd), client.end() );
                    cur = client.erase(cur);
                    cerr << "-- client disconnected fd " << client_fd << endl;
                }
            }
        }

        // new connection?
        if(FD_ISSET(fd, &read_set))
        {
            FD_CLR(fd, &read_set);
            struct sockaddr_in acceptSock;
            socklen_t len = sizeof(struct sockaddr_in);
            int new_fd = ::accept(fd, (struct sockaddr *)&acceptSock, &len);
            if(new_fd == -1) {
                throw(Exception("Accept failed, returned -1", __FILE__, __LINE__));
            }
            else {
                client.push_back(new_fd);
            }
        }

        mutex.unlock();

    } // end while

    mutex.unlock();
    return 0;

} // select

//
//-------------------------------------------------------------------------
// Method         : quit
//
// Implementation : quits reading and listening for connections
//
//-------------------------------------------------------------------------
//
void Server::quit()
{
    mutex.signal();
    mutex.lock();

    // close listening socket
    close(fd);

    // close connected sockets
    for(unsigned int n = 0; n < client.size(); n++)
    {
        shutdown(client[n], SHUT_RDWR);
        close(client[n]);
    }

    client.clear();
    listening = false;

    mutex.reset();
    mutex.unlock();

} // quit

//
//-------------------------------------------------------------------------
// Method         : int connect
//
// Implementation : Connects to a remote host
//                  returns the connected file descriptor
//
//-------------------------------------------------------------------------
//
int Server::connect(const string &host, int port) throw(Exception)
{
    // get dotted ip from dns given hostname
    // int gethostbyname_r (const char *, hostent *, char *, unsigned int, hostent**, int *)
    struct hostent *h = gethostbyname(host.c_str());
    if(!h) {
        throw(Exception("gethostbyname failed, bad host name?", __FILE__, __LINE__));
    }

    // create the socket
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if(fd == -1) {
        throw(Exception("socket failed, returned -1", __FILE__, __LINE__));
    }

    // setup for socket creation
    struct sockaddr_in sock;
    sock.sin_family = AF_INET;
    sock.sin_port = htons(port);
    memcpy(&sock.sin_addr, h->h_addr, h->h_length);

    // attempt to connect (blocking)
    if((::connect(fd, (struct sockaddr *)&sock, sizeof(sock))) == -1)
    {
        close(fd);
        throw(Exception("connect failed, returned -1", __FILE__, __LINE__));
    }

    return fd;

} // connect
