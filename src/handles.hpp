/* 
  Copyright (C) 2016 -2017 Jerry Jin
*/

#ifndef handles_h
#define handles_h
#include <nan.h>
#include <string>
#include <queue>
#include <utility>

#include "../quantlibxl.hpp"

#include <oh/objecthandler.hpp>

using namespace node;
using namespace v8;
using namespace std;


class HandleCurrentLinkWorker {
  public:
    string mObjectID;

    string mReturnValue;

    string mError;

    HandleCurrentLinkWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class HandleEmptyWorker {
  public:
    string mObjectID;

    bool mReturnValue;

    string mError;

    HandleEmptyWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class RelinkableHandleLinkToWorker {
  public:
    string mObjectID;
    string mCurrentLink;

    string mError;

    RelinkableHandleLinkToWorker(
      string ObjectID
,       string CurrentLink
     )
      {
        mObjectID = ObjectID;
        mCurrentLink = CurrentLink;
      };

    void Execute();
};
 
#endif
