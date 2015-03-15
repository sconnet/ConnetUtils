//*****************************************************************************
//
// Copyright (C) 2001 Steve Connet.  All rights reserved.
//
// Source File Name : Singleton.h
// Author           : Steve Connet
//
// Version          : $Id: Singleton.h,v 1.3 2015/03/14 23:44:56 clu Exp $
//
// Revision History : Turn a class into a singleton
//
// $Log: Singleton.h,v $
// Revision 1.3  2015/03/14 23:44:56  clu
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

#ifndef __SINGLETON_H_
#define __SINGLETON_H_

//namespace ConnetUtils
//{
template <class T>
class Singleton
{
    Singleton() {}
    ~Singleton() {}

public:
    static T &Instance()
    {
        static T instance;
        return instance;
    }
};

#define SINGLETON(T) protected:friend class Singleton<T>; T() {}
#define SINGLETON_INSTANCE(T) Singleton<T>::Instance()

/*
  example of how to use:

  class test
  {
  SINGLETON(test);
  public:
  int a;
  };

  int main()
  {
  test& t = SINGLETON_INSTANCE(test);
  t.a = 10;

  test& f = SINGLETON_INSTANCE(test);
  cout << f.a << endl;
  }
*/
//}

#endif // __SINGLETON_H_

