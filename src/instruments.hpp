/* 
  Copyright (C) 2016 -2017 Jerry Jin
*/

#ifndef instruments_h
#define instruments_h
#include <nan.h>
#include <string>
#include <queue>
#include <utility>

#include "../quantlibxl.hpp"

#include <oh/objecthandler.hpp>

using namespace node;
using namespace v8;
using namespace std;


class InstrumentNPVWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    InstrumentNPVWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class InstrumentErrorEstimateWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    InstrumentErrorEstimateWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class InstrumentValuationDateWorker {
  public:
    string mObjectID;

    long mReturnValue;

    string mError;

    InstrumentValuationDateWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class InstrumentResultsWorker {
  public:
    string mObjectID;
    string mResultType;

    double mReturnValue;

    string mError;

    InstrumentResultsWorker(
      string ObjectID
,       string ResultType
     )
      {
        mObjectID = ObjectID;
        mResultType = ResultType;
      };

    void Execute();
};

class InstrumentIsExpiredWorker {
  public:
    string mObjectID;

    bool mReturnValue;

    string mError;

    InstrumentIsExpiredWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class InstrumentSetPricingEngineWorker {
  public:
    string mObjectID;
    string mPricingEngine;

    string mError;

    InstrumentSetPricingEngineWorker(
      string ObjectID
,       string PricingEngine
     )
      {
        mObjectID = ObjectID;
        mPricingEngine = PricingEngine;
      };

    void Execute();
};
 
#endif
