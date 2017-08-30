/* 
  Copyright (C) 2016 -2017 Jerry Jin
*/

#ifndef forwardrateagreement_h
#define forwardrateagreement_h
#include <nan.h>
#include <string>
#include <queue>
#include <utility>

#include "../quantlibxl.hpp"

#include <oh/objecthandler.hpp>

using namespace node;
using namespace v8;
using namespace std;


class FRAWorker {
  public:
    string mObjectID;
    ObjectHandler::property_t mValueDate;
    ObjectHandler::property_t mMaturityDate;
    string mPosition;
    double mStrike;
    double mNotional;
    string mIborIndex;
    ObjectHandler::property_t mYieldCurve;

    string mReturnValue;

    string mError;

    FRAWorker(
      string ObjectID
,       ObjectHandler::property_t ValueDate
,       ObjectHandler::property_t MaturityDate
,       string Position
,       double Strike
,       double Notional
,       string IborIndex
,       ObjectHandler::property_t YieldCurve
     )
      {
        mObjectID = ObjectID;
        mValueDate = ValueDate;
        mMaturityDate = MaturityDate;
        mPosition = Position;
        mStrike = Strike;
        mNotional = Notional;
        mIborIndex = IborIndex;
        mYieldCurve = YieldCurve;
      };

    void Execute();
};

class FRAforwardRateWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    FRAforwardRateWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class FRAforwardValueWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    FRAforwardValueWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class FRAspotValueWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    FRAspotValueWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};
 
#endif
