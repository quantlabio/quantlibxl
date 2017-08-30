/* 
  Copyright (C) 2016 -2017 Jerry Jin
*/

#ifndef processes_h
#define processes_h
#include <nan.h>
#include <string>
#include <queue>
#include <utility>

#include "../quantlibxl.hpp"

#include <oh/objecthandler.hpp>

using namespace node;
using namespace v8;
using namespace std;


class GeneralizedBlackScholesProcessWorker {
  public:
    string mObjectID;
    string mBlackVolID;
    double mUnderlying;
    string mDayCounter;
    ObjectHandler::property_t mSettlementDate;
    double mRiskFreeRate;
    double mDividendYield;

    string mReturnValue;

    string mError;

    GeneralizedBlackScholesProcessWorker(
      string ObjectID
,       string BlackVolID
,       double Underlying
,       string DayCounter
,       ObjectHandler::property_t SettlementDate
,       double RiskFreeRate
,       double DividendYield
     )
      {
        mObjectID = ObjectID;
        mBlackVolID = BlackVolID;
        mUnderlying = Underlying;
        mDayCounter = DayCounter;
        mSettlementDate = SettlementDate;
        mRiskFreeRate = RiskFreeRate;
        mDividendYield = DividendYield;
      };

    void Execute();
};
 
#endif
