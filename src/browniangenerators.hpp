/* 
  Copyright (C) 2016 -2017 Jerry Jin
*/

#ifndef browniangenerators_h
#define browniangenerators_h
#include <nan.h>
#include <string>
#include <queue>
#include <utility>

#include "../quantlibxl.hpp"

#include <oh/objecthandler.hpp>

using namespace node;
using namespace v8;
using namespace std;


class MTBrownianGeneratorFactoryWorker {
  public:
    string mObjectID;
    long mSeed;

    string mReturnValue;

    string mError;

    MTBrownianGeneratorFactoryWorker(
      string ObjectID
,       long Seed
     )
      {
        mObjectID = ObjectID;
        mSeed = Seed;
      };

    void Execute();
};
 
#endif
