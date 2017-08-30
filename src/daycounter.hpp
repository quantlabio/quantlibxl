/* 
  Copyright (C) 2016 -2017 Jerry Jin
*/

#ifndef daycounter_h
#define daycounter_h
#include <nan.h>
#include <string>
#include <queue>
#include <utility>

#include "../quantlibxl.hpp"

#include <oh/objecthandler.hpp>

using namespace node;
using namespace v8;
using namespace std;


class DayCounterNameWorker {
  public:
    string mDayCounter;

    string mReturnValue;

    string mError;

    DayCounterNameWorker(
      string DayCounter
     )
      {
        mDayCounter = DayCounter;
      };

    void Execute();
};

class DayCounterDayCountWorker {
  public:
    string mDayCounter;
    ObjectHandler::property_t mStartDate;
    std::vector<ObjectHandler::property_t> mEndDate;

    std::vector<long> mReturnValue;

    string mError;

    DayCounterDayCountWorker(
      string DayCounter
,       ObjectHandler::property_t StartDate
,       std::vector<ObjectHandler::property_t> EndDate
     )
      {
        mDayCounter = DayCounter;
        mStartDate = StartDate;
        mEndDate = EndDate;
      };

    void Execute();
};

class DayCounterYearFractionWorker {
  public:
    string mDayCounter;
    ObjectHandler::property_t mStartDate;
    std::vector<ObjectHandler::property_t> mEndDate;
    ObjectHandler::property_t mRefPeriodStart;
    ObjectHandler::property_t mRefPeriodEnd;

    std::vector<double> mReturnValue;

    string mError;

    DayCounterYearFractionWorker(
      string DayCounter
,       ObjectHandler::property_t StartDate
,       std::vector<ObjectHandler::property_t> EndDate
,       ObjectHandler::property_t RefPeriodStart
,       ObjectHandler::property_t RefPeriodEnd
     )
      {
        mDayCounter = DayCounter;
        mStartDate = StartDate;
        mEndDate = EndDate;
        mRefPeriodStart = RefPeriodStart;
        mRefPeriodEnd = RefPeriodEnd;
      };

    void Execute();
};
 
#endif
