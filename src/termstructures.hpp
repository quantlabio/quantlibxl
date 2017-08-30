/* 
  Copyright (C) 2016 -2017 Jerry Jin
*/

#ifndef termstructures_h
#define termstructures_h
#include <nan.h>
#include <string>
#include <queue>
#include <utility>

#include "../quantlibxl.hpp"

#include <oh/objecthandler.hpp>

using namespace node;
using namespace v8;
using namespace std;


class RelinkableHandleYieldTermStructureWorker {
  public:
    string mObjectID;
    string mCurrentLink;

    string mReturnValue;

    string mError;

    RelinkableHandleYieldTermStructureWorker(
      string ObjectID
,       string CurrentLink
     )
      {
        mObjectID = ObjectID;
        mCurrentLink = CurrentLink;
      };

    void Execute();
};

class DiscountCurveWorker {
  public:
    string mObjectID;
    std::vector<ObjectHandler::property_t> mCurveDates;
    std::vector<double> mCurveDiscounts;
    string mDayCounter;

    string mReturnValue;

    string mError;

    DiscountCurveWorker(
      string ObjectID
,       std::vector<ObjectHandler::property_t> CurveDates
,       std::vector<double> CurveDiscounts
,       string DayCounter
     )
      {
        mObjectID = ObjectID;
        mCurveDates = CurveDates;
        mCurveDiscounts = CurveDiscounts;
        mDayCounter = DayCounter;
      };

    void Execute();
};

class ZeroCurveWorker {
  public:
    string mObjectID;
    std::vector<ObjectHandler::property_t> mCurveDates;
    std::vector<double> mCurveYields;
    string mDayCounter;

    string mReturnValue;

    string mError;

    ZeroCurveWorker(
      string ObjectID
,       std::vector<ObjectHandler::property_t> CurveDates
,       std::vector<double> CurveYields
,       string DayCounter
     )
      {
        mObjectID = ObjectID;
        mCurveDates = CurveDates;
        mCurveYields = CurveYields;
        mDayCounter = DayCounter;
      };

    void Execute();
};

class ForwardCurveWorker {
  public:
    string mObjectID;
    std::vector<ObjectHandler::property_t> mCurveDates;
    std::vector<double> mForwardYields;
    string mDayCounter;

    string mReturnValue;

    string mError;

    ForwardCurveWorker(
      string ObjectID
,       std::vector<ObjectHandler::property_t> CurveDates
,       std::vector<double> ForwardYields
,       string DayCounter
     )
      {
        mObjectID = ObjectID;
        mCurveDates = CurveDates;
        mForwardYields = ForwardYields;
        mDayCounter = DayCounter;
      };

    void Execute();
};

class FlatForwardWorker {
  public:
    string mObjectID;
    long mNDays;
    string mCalendar;
    ObjectHandler::property_t mRate;
    string mDayCounter;
    string mCompounding;
    string mFrequency;

    string mReturnValue;

    string mError;

    FlatForwardWorker(
      string ObjectID
,       long NDays
,       string Calendar
,       ObjectHandler::property_t Rate
,       string DayCounter
,       string Compounding
,       string Frequency
     )
      {
        mObjectID = ObjectID;
        mNDays = NDays;
        mCalendar = Calendar;
        mRate = Rate;
        mDayCounter = DayCounter;
        mCompounding = Compounding;
        mFrequency = Frequency;
      };

    void Execute();
};

class ForwardSpreadedTermStructureWorker {
  public:
    string mObjectID;
    ObjectHandler::property_t mBaseYieldCurve;
    ObjectHandler::property_t mSpread;

    string mReturnValue;

    string mError;

    ForwardSpreadedTermStructureWorker(
      string ObjectID
,       ObjectHandler::property_t BaseYieldCurve
,       ObjectHandler::property_t Spread
     )
      {
        mObjectID = ObjectID;
        mBaseYieldCurve = BaseYieldCurve;
        mSpread = Spread;
      };

    void Execute();
};

class ImpliedTermStructureWorker {
  public:
    string mObjectID;
    ObjectHandler::property_t mBaseYieldCurve;
    ObjectHandler::property_t mReferenceDate;

    string mReturnValue;

    string mError;

    ImpliedTermStructureWorker(
      string ObjectID
,       ObjectHandler::property_t BaseYieldCurve
,       ObjectHandler::property_t ReferenceDate
     )
      {
        mObjectID = ObjectID;
        mBaseYieldCurve = BaseYieldCurve;
        mReferenceDate = ReferenceDate;
      };

    void Execute();
};

class InterpolatedYieldCurveWorker {
  public:
    string mObjectID;
    std::vector<ObjectHandler::property_t> mDates;
    std::vector<double> mData;
    string mCalendar;
    string mDayCounter;
    std::vector<ObjectHandler::property_t> mJumps;
    std::vector<ObjectHandler::property_t> mJumpDates;
    string mTraitsID;
    string mInterpolatorID;
    string mMixedInterpolationBehavior;
    long mNRateHelper;

    string mReturnValue;

    string mError;

    InterpolatedYieldCurveWorker(
      string ObjectID
,       std::vector<ObjectHandler::property_t> Dates
,       std::vector<double> Data
,       string Calendar
,       string DayCounter
,       std::vector<ObjectHandler::property_t> Jumps
,       std::vector<ObjectHandler::property_t> JumpDates
,       string TraitsID
,       string InterpolatorID
,       string MixedInterpolationBehavior
,       long NRateHelper
     )
      {
        mObjectID = ObjectID;
        mDates = Dates;
        mData = Data;
        mCalendar = Calendar;
        mDayCounter = DayCounter;
        mJumps = Jumps;
        mJumpDates = JumpDates;
        mTraitsID = TraitsID;
        mInterpolatorID = InterpolatorID;
        mMixedInterpolationBehavior = MixedInterpolationBehavior;
        mNRateHelper = NRateHelper;
      };

    void Execute();
};

class TermStructureDayCounterWorker {
  public:
    string mObjectID;

    string mReturnValue;

    string mError;

    TermStructureDayCounterWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class TermStructureMaxDateWorker {
  public:
    string mObjectID;

    long mReturnValue;

    string mError;

    TermStructureMaxDateWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class TermStructureReferenceDateWorker {
  public:
    string mObjectID;

    long mReturnValue;

    string mError;

    TermStructureReferenceDateWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class TermStructureTimeFromReferenceWorker {
  public:
    string mObjectID;
    std::vector<ObjectHandler::property_t> mDate;

    std::vector<double> mReturnValue;

    string mError;

    TermStructureTimeFromReferenceWorker(
      string ObjectID
,       std::vector<ObjectHandler::property_t> Date
     )
      {
        mObjectID = ObjectID;
        mDate = Date;
      };

    void Execute();
};

class TermStructureCalendarWorker {
  public:
    string mObjectID;

    string mReturnValue;

    string mError;

    TermStructureCalendarWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class TermStructureSettlementDaysWorker {
  public:
    string mObjectID;

    long mReturnValue;

    string mError;

    TermStructureSettlementDaysWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class YieldTSDiscountWorker {
  public:
    string mObjectID;
    std::vector<ObjectHandler::property_t> mDfDates;
    bool mAllowExtrapolation;

    std::vector<double> mReturnValue;

    string mError;

    YieldTSDiscountWorker(
      string ObjectID
,       std::vector<ObjectHandler::property_t> DfDates
,       bool AllowExtrapolation
     )
      {
        mObjectID = ObjectID;
        mDfDates = DfDates;
        mAllowExtrapolation = AllowExtrapolation;
      };

    void Execute();
};

class YieldTSForwardRateWorker {
  public:
    string mObjectID;
    ObjectHandler::property_t mD1;
    std::vector<ObjectHandler::property_t> mD2;
    string mResultDayCounter;
    string mCompounding;
    string mFrequency;
    bool mAllowExtrapolation;

    std::vector<string> mReturnValue;

    string mError;

    YieldTSForwardRateWorker(
      string ObjectID
,       ObjectHandler::property_t D1
,       std::vector<ObjectHandler::property_t> D2
,       string ResultDayCounter
,       string Compounding
,       string Frequency
,       bool AllowExtrapolation
     )
      {
        mObjectID = ObjectID;
        mD1 = D1;
        mD2 = D2;
        mResultDayCounter = ResultDayCounter;
        mCompounding = Compounding;
        mFrequency = Frequency;
        mAllowExtrapolation = AllowExtrapolation;
      };

    void Execute();
};

class YieldTSForwardRate2Worker {
  public:
    string mObjectID;
    std::vector<ObjectHandler::property_t> mDate;
    string mPeriod;
    string mResultDayCounter;
    string mCompounding;
    string mFrequency;
    bool mAllowExtrapolation;

    std::vector<string> mReturnValue;

    string mError;

    YieldTSForwardRate2Worker(
      string ObjectID
,       std::vector<ObjectHandler::property_t> Date
,       string Period
,       string ResultDayCounter
,       string Compounding
,       string Frequency
,       bool AllowExtrapolation
     )
      {
        mObjectID = ObjectID;
        mDate = Date;
        mPeriod = Period;
        mResultDayCounter = ResultDayCounter;
        mCompounding = Compounding;
        mFrequency = Frequency;
        mAllowExtrapolation = AllowExtrapolation;
      };

    void Execute();
};

class YieldTSZeroRateWorker {
  public:
    string mObjectID;
    std::vector<ObjectHandler::property_t> mDates;
    string mResultDayCounter;
    string mCompounding;
    string mFrequency;
    bool mAllowExtrapolation;

    std::vector<string> mReturnValue;

    string mError;

    YieldTSZeroRateWorker(
      string ObjectID
,       std::vector<ObjectHandler::property_t> Dates
,       string ResultDayCounter
,       string Compounding
,       string Frequency
,       bool AllowExtrapolation
     )
      {
        mObjectID = ObjectID;
        mDates = Dates;
        mResultDayCounter = ResultDayCounter;
        mCompounding = Compounding;
        mFrequency = Frequency;
        mAllowExtrapolation = AllowExtrapolation;
      };

    void Execute();
};

class InterpolatedYieldCurveTimesWorker {
  public:
    string mObjectID;

    std::vector<double> mReturnValue;

    string mError;

    InterpolatedYieldCurveTimesWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class InterpolatedYieldCurveDatesWorker {
  public:
    string mObjectID;

    std::vector<long> mReturnValue;

    string mError;

    InterpolatedYieldCurveDatesWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class InterpolatedYieldCurveDataWorker {
  public:
    string mObjectID;

    std::vector<double> mReturnValue;

    string mError;

    InterpolatedYieldCurveDataWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class InterpolatedYieldCurveJumpTimesWorker {
  public:
    string mObjectID;

    std::vector<double> mReturnValue;

    string mError;

    InterpolatedYieldCurveJumpTimesWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class InterpolatedYieldCurveJumpDatesWorker {
  public:
    string mObjectID;

    std::vector<long> mReturnValue;

    string mError;

    InterpolatedYieldCurveJumpDatesWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};
 
#endif
