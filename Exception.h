//*****************************************************************************
//
// Copyright (C) 2001 Steve Connet.  All rights reserved.
//
// Source File Name : Exception.h
// Author           : Steve Connet
//
// Version          : $Id: $
//
// Revision History : Throw this when throwing exceptions
//
// $Log: $
//
//*****************************************************************************

#pragma interface

#ifndef __EXCEPTION_H_
#define __EXCEPTION_H_

#include <iostream>
#include <string>

namespace ConnetUtils
{

class Exception
{
 public:
  Exception(const std::string& why, const std::string& file, int line) :
    why(why), file(file), line(line) {}
    
  const std::string why;
  const std::string file;
  const int line;
    
  friend std::ostream& operator<<(std::ostream& out, const Exception& exception)
    {
      std::string sep(79, '*');
      out << sep
          << "\nEXCEPTION: " << exception.why
          << "\n LOCATION: " << exception.file << ":" << exception.line
          << '\n' << sep;
      return out;
    }
};

}

#endif // __EXCEPTION_H_
