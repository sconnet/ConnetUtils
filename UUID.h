//*****************************************************************************
//
// Copyright (C) 2001 Steve Connet.  All rights reserved.
//
// Source File Name : UUID.h
// Author           : Steve Connet
//
// Version          : $Id: UUID.h,v 1.1 2001/11/08 06:17:14 sconnet Exp sconnet $
//
// Revision History : Creates a unique identifier
//                    Not gauranteed unique if created faster than
//                    once every microsecond
//
// $Log: UUID.h,v $
// Revision 1.1  2001/11/08 06:17:14  sconnet
// Initial revision
//
//
//*****************************************************************************

#pragma interface

#ifndef __UUID_H_
#define __UUID_H_

#include <sys/time.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <iostream>
#include <string>

//namespace ConnetUtils
//{

class UUID
{
 public:
  static struct in_addr ia;
  struct timeval tv;
    
 public:
  UUID();
  operator std::string();
    
  friend std::ostream& operator<<(std::ostream& out, const UUID& uuid);
  friend bool operator<(const UUID& lhs, const UUID& rhs);
  friend bool operator==(const UUID& lhs, const UUID& rhs);
  friend bool operator!=(const UUID& lhs, const UUID& rhs);  
};

//}

#endif // __UUID_H_
