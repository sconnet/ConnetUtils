//*****************************************************************************
//
// Copyright (C) 2001 Steve Connet.  All rights reserved.
//
// Source File Name : Config.h
// Author           : Steve Connet
//
// Version          : $Id: Config.h,v 1.3 2015/03/14 23:30:04 clu Exp $
//
// File Overview    : Reads in the configuration file once and puts
//                    each name value pair into a map for quick
//                    retrieval.
//
// Revision History :
//
// $Log: Config.h,v $
// Revision 1.3  2015/03/14 23:30:04  clu
// astyle code formatter applied
//
// Revision 1.2  2002/01/11 03:41:49  sconnet
// *** empty log message ***
//
// Revision 1.1  2001/11/08 06:17:14  sconnet
// Initial revision
//
//
//*****************************************************************************

#pragma interface

#ifndef __CONFIG_H_
#define __CONFIG_H_

#include <map>
#include <string>
#include <iostream>

//namespace ConnetUtils
//{

class Config
{
public:
    friend std::ostream &operator<<(std::ostream &out, const Config &config);

private:
    std::map<std::string, std::string> data;

    int getValueAsInt(const std::string &name, int default_value);
    std::string getValueAsStr(const std::string &name, const std::string &default_value);


public:
    bool load(const std::string &file);

    /*    std::string operator()(const std::string& name, const std::string& default) */
    /*      { return getValueAsStr(name, default); } */

    /*    int operator()(const std::string& name, int default = 0) */
    /*      { return getValueAsInt(name, default); } */

};

//}

#endif // __CONFIG_H_

