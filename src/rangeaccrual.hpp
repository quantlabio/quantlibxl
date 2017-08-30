/* 
  Copyright (C) 2016 -2017 Jerry Jin
*/

#ifndef rangeaccrual_h
#define rangeaccrual_h
#include <nan.h>
#include <string>
#include <queue>
#include <utility>

#include "../quantlibxl.hpp"

#include <oh/objecthandler.hpp>

using namespace node;
using namespace v8;
using namespace std;


class RangeAccrualFloatersCouponWorker {
  public:
    string mObjectID;
    double mNominal;
    ObjectHandler::property_t mPaymentDate;
    string mIborIndex;
    ObjectHandler::property_t mStartDate;
    ObjectHandler::property_t mEndDate;
    long mFixingDays;
    string mDayCountID;
    double mGearings;
    double mSpreads;
    ObjectHandler::property_t mRefPeriodStart;
    ObjectHandler::property_t mRefPeriodEnd;
    string mObserSchedID;
    double mLowerTrigger;
    double mUpperTrigger;

    string mReturnValue;

    string mError;

    RangeAccrualFloatersCouponWorker(
      string ObjectID
,       double Nominal
,       ObjectHandler::property_t PaymentDate
,       string IborIndex
,       ObjectHandler::property_t StartDate
,       ObjectHandler::property_t EndDate
,       long FixingDays
,       string DayCountID
,       double Gearings
,       double Spreads
,       ObjectHandler::property_t RefPeriodStart
,       ObjectHandler::property_t RefPeriodEnd
,       string ObserSchedID
,       double LowerTrigger
,       double UpperTrigger
     )
      {
        mObjectID = ObjectID;
        mNominal = Nominal;
        mPaymentDate = PaymentDate;
        mIborIndex = IborIndex;
        mStartDate = StartDate;
        mEndDate = EndDate;
        mFixingDays = FixingDays;
        mDayCountID = DayCountID;
        mGearings = Gearings;
        mSpreads = Spreads;
        mRefPeriodStart = RefPeriodStart;
        mRefPeriodEnd = RefPeriodEnd;
        mObserSchedID = ObserSchedID;
        mLowerTrigger = LowerTrigger;
        mUpperTrigger = UpperTrigger;
      };

    void Execute();
};

class RangeAccrualFloatersCouponFromLegWorker {
  public:
    string mObjectID;
    string mRangeAccrualLeg;
    long mPosition;

    string mReturnValue;

    string mError;

    RangeAccrualFloatersCouponFromLegWorker(
      string ObjectID
,       string RangeAccrualLeg
,       long Position
     )
      {
        mObjectID = ObjectID;
        mRangeAccrualLeg = RangeAccrualLeg;
        mPosition = Position;
      };

    void Execute();
};

class RangeAccrualPricerByBgmWorker {
  public:
    string mObjectID;
    double mCorrelation;
    string mSmileOnStartDateID;
    string mSmileOnEndDateID;
    bool mWithSmile;
    bool mByCallSpread;

    string mReturnValue;

    string mError;

    RangeAccrualPricerByBgmWorker(
      string ObjectID
,       double Correlation
,       string SmileOnStartDateID
,       string SmileOnEndDateID
,       bool WithSmile
,       bool ByCallSpread
     )
      {
        mObjectID = ObjectID;
        mCorrelation = Correlation;
        mSmileOnStartDateID = SmileOnStartDateID;
        mSmileOnEndDateID = SmileOnEndDateID;
        mWithSmile = WithSmile;
        mByCallSpread = ByCallSpread;
      };

    void Execute();
};

class RangeAccrualFloatersCouponSetPricerWorker {
  public:
    string mObjectID;
    string mRangeAccrualPricer;

    string mError;

    RangeAccrualFloatersCouponSetPricerWorker(
      string ObjectID
,       string RangeAccrualPricer
     )
      {
        mObjectID = ObjectID;
        mRangeAccrualPricer = RangeAccrualPricer;
      };

    void Execute();
};

class RangeAccrualFloatersCouponObservationDatesWorker {
  public:
    string mObjectID;

    std::vector<long> mReturnValue;

    string mError;

    RangeAccrualFloatersCouponObservationDatesWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class RangeAccrualFloatersCouponStarDateWorker {
  public:
    string mObjectID;

    long mReturnValue;

    string mError;

    RangeAccrualFloatersCouponStarDateWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class RangeAccrualFloatersCouponEndDateWorker {
  public:
    string mObjectID;

    long mReturnValue;

    string mError;

    RangeAccrualFloatersCouponEndDateWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class RangeAccrualFloatersCouponObservationsNoWorker {
  public:
    string mObjectID;

    long mReturnValue;

    string mError;

    RangeAccrualFloatersCouponObservationsNoWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class RangeAccrualFloatersPriceWorker {
  public:
    string mObjectID;
    ObjectHandler::property_t mYieldCurve;

    double mReturnValue;

    string mError;

    RangeAccrualFloatersPriceWorker(
      string ObjectID
,       ObjectHandler::property_t YieldCurve
     )
      {
        mObjectID = ObjectID;
        mYieldCurve = YieldCurve;
      };

    void Execute();
};

class SimpleFloaterPriceWorker {
  public:
    string mObjectID;
    ObjectHandler::property_t mYieldCurve;

    double mReturnValue;

    string mError;

    SimpleFloaterPriceWorker(
      string ObjectID
,       ObjectHandler::property_t YieldCurve
     )
      {
        mObjectID = ObjectID;
        mYieldCurve = YieldCurve;
      };

    void Execute();
};
 
#endif
