//*****************************************************************************
//
// Copyright (C) 2001 Steve Connet.  All rights reserved.
//
// Source File Name : Exception.h
// Author           : Steve Connet
//
// Version          : $Id: Exception.h,v 1.1 2001/11/08 06:17:14 sconnet Exp sconnet $
//
// Revision History : Throw this when throwing exceptions
//
// $Log: Exception.h,v $
// Revision 1.1  2001/11/08 06:17:14  sconnet
// Initial revision
//
//
//*****************************************************************************

//#pragma interface

#ifndef __EXCEPTION_H_
#define __EXCEPTION_H_

#include <iostream>
#include <string>
#include <exception>

//namespace ConnetUtils
//{

class Exception : public std::exception
{
  const std::string why;
  const std::string file;
  const int line;

 public:
  Exception(const std::string& why, const std::string& file, int line) :
    why(why), file(file), line(line) {}
  ~Exception() throw() {}
    
  friend std::ostream& operator<<(std::ostream& out, const Exception& ex);
};

inline std::ostream& operator<<(std::ostream& out, const Exception& ex)
{
  std::string sep(79, '*');
  out << sep
      << "\nEXCEPTION: " << ex.why
      << "\n LOCATION: " << ex.file << ':' << ex.line
      << '\n' << sep;
  return out;
}

//}

#endif // __EXCEPTION_H_
