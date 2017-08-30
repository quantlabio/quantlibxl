/* 
  Copyright (C) 2016 -2017 Jerry Jin
*/

#ifndef piecewiseyieldcurve_h
#define piecewiseyieldcurve_h
#include <nan.h>
#include <string>
#include <queue>
#include <utility>

#include "../quantlibxl.hpp"

#include <oh/objecthandler.hpp>

using namespace node;
using namespace v8;
using namespace std;


class PiecewiseYieldCurveWorker {
  public:
    string mObjectID;
    ObjectHandler::property_t mNDays;
    string mCalendar;
    std::vector<string> mRateHelpers;
    string mDayCounter;
    std::vector<ObjectHandler::property_t> mJumps;
    std::vector<ObjectHandler::property_t> mJumpDates;
    double mAccuracy;
    string mTraitsID;
    string mInterpolatorID;

    string mReturnValue;

    string mError;

    PiecewiseYieldCurveWorker(
      string ObjectID
,       ObjectHandler::property_t NDays
,       string Calendar
,       std::vector<string> RateHelpers
,       string DayCounter
,       std::vector<ObjectHandler::property_t> Jumps
,       std::vector<ObjectHandler::property_t> JumpDates
,       double Accuracy
,       string TraitsID
,       string InterpolatorID
     )
      {
        mObjectID = ObjectID;
        mNDays = NDays;
        mCalendar = Calendar;
        mRateHelpers = RateHelpers;
        mDayCounter = DayCounter;
        mJumps = Jumps;
        mJumpDates = JumpDates;
        mAccuracy = Accuracy;
        mTraitsID = TraitsID;
        mInterpolatorID = InterpolatorID;
      };

    void Execute();
};

class PiecewiseYieldCurveMixedInterpolationWorker {
  public:
    string mObjectID;
    ObjectHandler::property_t mNDays;
    string mCalendar;
    std::vector<string> mRateHelpers;
    string mDayCounter;
    std::vector<ObjectHandler::property_t> mJumps;
    std::vector<ObjectHandler::property_t> mJumpDates;
    double mAccuracy;
    string mTraitsID;
    string mInterpolatorID;
    string mMixedInterpolationBehavior;
    long mPillarsBeforeChange;

    string mReturnValue;

    string mError;

    PiecewiseYieldCurveMixedInterpolationWorker(
      string ObjectID
,       ObjectHandler::property_t NDays
,       string Calendar
,       std::vector<string> RateHelpers
,       string DayCounter
,       std::vector<ObjectHandler::property_t> Jumps
,       std::vector<ObjectHandler::property_t> JumpDates
,       double Accuracy
,       string TraitsID
,       string InterpolatorID
,       string MixedInterpolationBehavior
,       long PillarsBeforeChange
     )
      {
        mObjectID = ObjectID;
        mNDays = NDays;
        mCalendar = Calendar;
        mRateHelpers = RateHelpers;
        mDayCounter = DayCounter;
        mJumps = Jumps;
        mJumpDates = JumpDates;
        mAccuracy = Accuracy;
        mTraitsID = TraitsID;
        mInterpolatorID = InterpolatorID;
        mMixedInterpolationBehavior = MixedInterpolationBehavior;
        mPillarsBeforeChange = PillarsBeforeChange;
      };

    void Execute();
};

class PiecewiseYieldCurveTimesWorker {
  public:
    string mObjectID;

    std::vector<double> mReturnValue;

    string mError;

    PiecewiseYieldCurveTimesWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class PiecewiseYieldCurveDatesWorker {
  public:
    string mObjectID;

    std::vector<long> mReturnValue;

    string mError;

    PiecewiseYieldCurveDatesWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class PiecewiseYieldCurveDataWorker {
  public:
    string mObjectID;

    std::vector<double> mReturnValue;

    string mError;

    PiecewiseYieldCurveDataWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class PiecewiseYieldCurveJumpTimesWorker {
  public:
    string mObjectID;

    std::vector<double> mReturnValue;

    string mError;

    PiecewiseYieldCurveJumpTimesWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class PiecewiseYieldCurveJumpDatesWorker {
  public:
    string mObjectID;

    std::vector<long> mReturnValue;

    string mError;

    PiecewiseYieldCurveJumpDatesWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};
 
#endif
