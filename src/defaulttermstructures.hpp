/* 
  Copyright (C) 2016 -2017 Jerry Jin
*/

#ifndef defaulttermstructures_h
#define defaulttermstructures_h
#include <nan.h>
#include <string>
#include <queue>
#include <utility>

#include "../quantlibxl.hpp"

#include <oh/objecthandler.hpp>

using namespace node;
using namespace v8;
using namespace std;


class RelinkableHandleDefaultProbabilityTermStructureWorker {
  public:
    string mObjectID;
    string mCurrentLink;

    string mReturnValue;

    string mError;

    RelinkableHandleDefaultProbabilityTermStructureWorker(
      string ObjectID
,       string CurrentLink
     )
      {
        mObjectID = ObjectID;
        mCurrentLink = CurrentLink;
      };

    void Execute();
};

class FlatHazardRateWorker {
  public:
    string mObjectID;
    long mNDays;
    string mCalendar;
    ObjectHandler::property_t mRate;
    string mDayCounter;

    string mReturnValue;

    string mError;

    FlatHazardRateWorker(
      string ObjectID
,       long NDays
,       string Calendar
,       ObjectHandler::property_t Rate
,       string DayCounter
     )
      {
        mObjectID = ObjectID;
        mNDays = NDays;
        mCalendar = Calendar;
        mRate = Rate;
        mDayCounter = DayCounter;
      };

    void Execute();
};

class DefaultTSDefaultProbabilityWorker {
  public:
    string mObjectID;
    std::vector<ObjectHandler::property_t> mDates;
    bool mAllowExtrapolation;

    std::vector<double> mReturnValue;

    string mError;

    DefaultTSDefaultProbabilityWorker(
      string ObjectID
,       std::vector<ObjectHandler::property_t> Dates
,       bool AllowExtrapolation
     )
      {
        mObjectID = ObjectID;
        mDates = Dates;
        mAllowExtrapolation = AllowExtrapolation;
      };

    void Execute();
};

class ProbabilityToHRWorker {
  public:
    double mProbability;
    ObjectHandler::property_t mDate;
    string mDayCounter;

    double mReturnValue;

    string mError;

    ProbabilityToHRWorker(
      double Probability
,       ObjectHandler::property_t Date
,       string DayCounter
     )
      {
        mProbability = Probability;
        mDate = Date;
        mDayCounter = DayCounter;
      };

    void Execute();
};
 
#endif
