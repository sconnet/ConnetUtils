//*****************************************************************************
//
// Copyright (C) 2001 Steve Connet.  All rights reserved.
//
// Source File Name : misc.h
// Author           : Steve Connet
//
// Version          : $Id: misc.h,v 1.2 2002/01/11 03:41:49 sconnet Exp clu $
//
// File Overview    : miscellaneous utility functions
//
// Revision History :
//
// $Log: misc.h,v $
// Revision 1.2  2002/01/11 03:41:49  sconnet
// *** empty log message ***
//
// Revision 1.1  2001/11/08 06:17:14  sconnet
// Initial revision
//
//
//*****************************************************************************

#pragma interface

#ifndef __MISC_H_
#define __MISC_H_

#include <sys/time.h>
#include <string>

//namespace ConnetUtils
//{

std::string trimLeft(const std::string &value);
std::string trimRight(const std::string &value);
void makeTimespec(int timeout /* ms */, struct timespec &ts);

//}

#endif // __MISC_H_
