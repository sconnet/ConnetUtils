//*****************************************************************************
//
// Copyright (C) 2001 Steve Connet.  All rights reserved.
//
// Source File Name : UUID.cpp
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

#include <sstream>
#include <netdb.h>
#include "UUID.h"

using namespace std;
using namespace ConnetUtils;

// initialize class variable
struct in_addr UUID::ia = { 0 };

//
//-------------------------------------------------------------------------
// Method         : operator<<(std::ostream& out, const UUID& uuid)
//
// Implementation : put a uuid into an output stream
// 
//-------------------------------------------------------------------------
//
ostream& ConnetUtils::operator<<(ostream& out, const UUID& uuid)
{
  out << uuid.ia.s_addr << uuid.tv.tv_sec << uuid.tv.tv_usec;
  return out;
}

//
//-------------------------------------------------------------------------
// Method         : bool operator<(const UUID& lhs, const UUID& rhs)
//
// Implementation : less then comparison
// 
//-------------------------------------------------------------------------
//
bool ConnetUtils::operator<(const UUID& lhs, const UUID& rhs)
{
  return
    lhs.tv.tv_usec < rhs.tv.tv_usec &&
    lhs.tv.tv_sec < rhs.tv.tv_sec &&
    lhs.ia.s_addr < rhs.ia.s_addr;
}

//
//-------------------------------------------------------------------------
// Method         : bool operator==(const UUID& lhs, const UUID& rhs)
//
// Implementation : equality comparison
// 
//-------------------------------------------------------------------------
//
bool ConnetUtils::operator==(const UUID& lhs, const UUID& rhs)
{
  return
    lhs.tv.tv_usec == rhs.tv.tv_usec &&
    lhs.tv.tv_sec == rhs.tv.tv_sec &&
    lhs.ia.s_addr == rhs.ia.s_addr;
}

//
//-------------------------------------------------------------------------
// Method         : bool operator!=(const UUID& lhs, const UUID& rhs)
//
// Implementation : inequality comparison
// 
//-------------------------------------------------------------------------
//
bool ConnetUtils::operator!=(const UUID& lhs, const UUID& rhs)
{
  return !(lhs == rhs);
}

//
//-------------------------------------------------------------------------
// Method         : constructor
//
// Implementation : 
// 
//-------------------------------------------------------------------------
//
UUID::UUID()
{
  if( ia.s_addr == 0 )
  {
    char host_name[255];
    gethostname(host_name, 255);
    struct hostent* host = gethostbyname(host_name);
    memcpy(&ia, host->h_addr, host->h_length);
  }
  
  gettimeofday(&tv, NULL);
}

//
//-------------------------------------------------------------------------
// Method         : UUID::operator std::string()
//
// Implementation : cast this uuid into a string
// 
//-------------------------------------------------------------------------
//
UUID::operator std::string()
{
  ostringstream oss;
  oss << *this;
  return oss.str();
}

