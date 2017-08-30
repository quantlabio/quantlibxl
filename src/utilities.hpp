/* 
  Copyright (C) 2016 -2017 Jerry Jin
*/

#ifndef utilities_h
#define utilities_h
#include <nan.h>
#include <string>
#include <queue>
#include <utility>

#include "../quantlibxl.hpp"

#include <oh/objecthandler.hpp>

using namespace node;
using namespace v8;
using namespace std;


class xlVersionWorker {
  public:
    bool mVerbose;

    string mReturnValue;

    string mError;

    xlVersionWorker(
      bool Verbose
     )
      {
        mVerbose = Verbose;
      };

    void Execute();
};

class AddinVersionWorker {
  public:

    string mReturnValue;

    string mError;

    AddinVersionWorker(
    )
      {
      };

    void Execute();
};

class VersionWorker {
  public:

    string mReturnValue;

    string mError;

    VersionWorker(
    )
      {
      };

    void Execute();
};

class FunctionCountWorker {
  public:

    long mReturnValue;

    string mError;

    FunctionCountWorker(
    )
      {
      };

    void Execute();
};
 
#endif
