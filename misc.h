//*****************************************************************************
//
// Copyright (C) 2001 Steve Connet.  All rights reserved.
//
// Source File Name : misc.h
// Author           : Steve Connet
//
// Version          : $Id: $
//
// File Overview    : miscellaneous utility functions
//
// Revision History : 
//
// $Log: $
//
//*****************************************************************************

#ifndef __MISC_H_
#define __MISC_H_

#include <sys/time.h>
#include <string>

namespace ConnetUtils
{

std::string trimLeft(const std::string& value);
std::string trimRight(const std::string& value);
void makeTimespec(int timeout /* ms */, struct timespec& ts);

}

#endif // __MISC_H_
