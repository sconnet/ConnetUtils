//*****************************************************************************
//
// Copyright (C) 2001 Steve Connet.  All rights reserved.
//
// Source File Name : Config.cpp
// Author           : Steve Connet
//
// Version          : $Id: Config.cpp,v 1.2 2002/01/11 03:41:49 sconnet Exp clu $
//
// Revision History :
//
// $Log: Config.cpp,v $
// Revision 1.2  2002/01/11 03:41:49  sconnet
// *** empty log message ***
//
// Revision 1.1  2001/11/08 06:17:14  sconnet
// Initial revision
//
//
//*****************************************************************************

#pragma implementation

#include <cctype>
#include <sstream>
#include <fstream>
#include <algorithm>

#include "misc.h"
#include "Config.h"

using namespace std;
//using namespace ConnetUtils;

//
//-------------------------------------------------------------------------
// Method         : operator<<
//
// Implementation : dump the values in the map
//
//-------------------------------------------------------------------------
//
//ostream& ConnetUtils::operator<<(ostream& out, const Config& config)
ostream &operator<<(ostream &out, const Config &config)
{
    for(map<string, string>::const_iterator cur(config.data.begin()), last(config.data.end()); cur != last; ++cur) {
        out << cur->first << '=' << cur->second << '\n';
    }

    return out;

} // operator<<

//
//-------------------------------------------------------------------------
// Method         : load
//
// Implementation : reads the config file and parses each line
//
//-------------------------------------------------------------------------
//
bool Config::load(const string &file)
{
    data.clear();

    ifstream infile(file.c_str(), ios::in);
    bool ok(infile);
    string buf;
    while(getline(infile, buf))
    {
        if(buf.length() && isalpha(buf[0]))
        {
            transform(buf.begin(), buf.end(), buf.begin(), ::tolower);

            string::size_type pos(buf.find_first_of('='));
            string name(buf.substr(0, pos));
            string value(buf.substr(pos + 1));

            data[trimLeft(trimRight(name))] = trimLeft(trimRight(value));
        }
    }

    infile.close();
    return ok;

} // load

//
//-------------------------------------------------------------------------
// Method         : getValueAsStr
//
// Implementation : Returns a value given a name. If name is not found
//                  then default is returned.
//
//-------------------------------------------------------------------------
//
string Config::getValueAsStr(const string &name, const string &default_value)
{
    string value(default_value);
    string key(name);
    transform(key.begin(), key.end(), key.begin(), ::tolower);

    map<string, string>::iterator p(data.find(key));
    if(p != data.end()) {
        value = p->second;
    }

    return value;

} // getValueAsString

//
//-------------------------------------------------------------------------
// Method         : getValueAsStr
//
// Implementation : Returns a value given a name. The value is
//                  converted to an int. If the name is not found,
//                  the default value is returned.
//
//-------------------------------------------------------------------------
//
int Config::getValueAsInt(const string &name, int default_value)
{
    int value(default_value);
    string value_str(getValueAsStr(name, ""));
    if(value_str.length())
    {
        stringstream oss;
        oss << value_str;
        oss >> value;
        //   value = atoi( s.c_str() );
    }

    return value;

} // getValueAsInt
