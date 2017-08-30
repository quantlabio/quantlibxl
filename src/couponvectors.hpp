/* 
  Copyright (C) 2016 -2017 Jerry Jin
*/

#ifndef couponvectors_h
#define couponvectors_h
#include <nan.h>
#include <string>
#include <queue>
#include <utility>

#include "../quantlibxl.hpp"

#include <oh/objecthandler.hpp>

using namespace node;
using namespace v8;
using namespace std;


class FixedRateLegWorker {
  public:
    string mObjectID;
    string mPaymentBDC;
    std::vector<double> mNominals;
    string mScheduleID;
    std::vector<double> mCoupons;
    string mDayCounter;

    string mReturnValue;

    string mError;

    FixedRateLegWorker(
      string ObjectID
,       string PaymentBDC
,       std::vector<double> Nominals
,       string ScheduleID
,       std::vector<double> Coupons
,       string DayCounter
     )
      {
        mObjectID = ObjectID;
        mPaymentBDC = PaymentBDC;
        mNominals = Nominals;
        mScheduleID = ScheduleID;
        mCoupons = Coupons;
        mDayCounter = DayCounter;
      };

    void Execute();
};

class FixedRateLeg2Worker {
  public:
    string mObjectID;
    string mPaymentBDC;
    std::vector<double> mNominals;
    string mScheduleID;
    std::vector<string> mCoupons;

    string mReturnValue;

    string mError;

    FixedRateLeg2Worker(
      string ObjectID
,       string PaymentBDC
,       std::vector<double> Nominals
,       string ScheduleID
,       std::vector<string> Coupons
     )
      {
        mObjectID = ObjectID;
        mPaymentBDC = PaymentBDC;
        mNominals = Nominals;
        mScheduleID = ScheduleID;
        mCoupons = Coupons;
      };

    void Execute();
};

class IborLegWorker {
  public:
    string mObjectID;
    string mPaymentBDC;
    std::vector<double> mNominals;
    string mScheduleID;
    std::vector<ObjectHandler::property_t> mFixingDays;
    bool mIsInArrears;
    string mDayCounter;
    std::vector<double> mFloors;
    std::vector<double> mGearings;
    string mIborIndex;
    std::vector<double> mSpreads;
    std::vector<double> mCaps;

    string mReturnValue;

    string mError;

    IborLegWorker(
      string ObjectID
,       string PaymentBDC
,       std::vector<double> Nominals
,       string ScheduleID
,       std::vector<ObjectHandler::property_t> FixingDays
,       bool IsInArrears
,       string DayCounter
,       std::vector<double> Floors
,       std::vector<double> Gearings
,       string IborIndex
,       std::vector<double> Spreads
,       std::vector<double> Caps
     )
      {
        mObjectID = ObjectID;
        mPaymentBDC = PaymentBDC;
        mNominals = Nominals;
        mScheduleID = ScheduleID;
        mFixingDays = FixingDays;
        mIsInArrears = IsInArrears;
        mDayCounter = DayCounter;
        mFloors = Floors;
        mGearings = Gearings;
        mIborIndex = IborIndex;
        mSpreads = Spreads;
        mCaps = Caps;
      };

    void Execute();
};

class DigitalIborLegWorker {
  public:
    string mObjectID;
    string mPaymentBDC;
    std::vector<double> mNominals;
    string mScheduleID;
    std::vector<ObjectHandler::property_t> mFixingDays;
    bool mIsInArrears;
    string mDayCounter;
    std::vector<double> mGearings;
    string mIborIndex;
    std::vector<double> mSpreads;
    std::vector<double> mCallStrikes;
    string mCallSpecs;
    std::vector<double> mCallPayoff;
    std::vector<double> mPutStrikes;
    string mPutSpecs;
    std::vector<double> mPutPayoff;
    string mReplication;

    string mReturnValue;

    string mError;

    DigitalIborLegWorker(
      string ObjectID
,       string PaymentBDC
,       std::vector<double> Nominals
,       string ScheduleID
,       std::vector<ObjectHandler::property_t> FixingDays
,       bool IsInArrears
,       string DayCounter
,       std::vector<double> Gearings
,       string IborIndex
,       std::vector<double> Spreads
,       std::vector<double> CallStrikes
,       string CallSpecs
,       std::vector<double> CallPayoff
,       std::vector<double> PutStrikes
,       string PutSpecs
,       std::vector<double> PutPayoff
,       string Replication
     )
      {
        mObjectID = ObjectID;
        mPaymentBDC = PaymentBDC;
        mNominals = Nominals;
        mScheduleID = ScheduleID;
        mFixingDays = FixingDays;
        mIsInArrears = IsInArrears;
        mDayCounter = DayCounter;
        mGearings = Gearings;
        mIborIndex = IborIndex;
        mSpreads = Spreads;
        mCallStrikes = CallStrikes;
        mCallSpecs = CallSpecs;
        mCallPayoff = CallPayoff;
        mPutStrikes = PutStrikes;
        mPutSpecs = PutSpecs;
        mPutPayoff = PutPayoff;
        mReplication = Replication;
      };

    void Execute();
};

class CmsLegWorker {
  public:
    string mObjectID;
    string mPaymentBDC;
    std::vector<double> mNominals;
    string mScheduleID;
    std::vector<ObjectHandler::property_t> mFixingDays;
    bool mIsInArrears;
    string mDayCounter;
    std::vector<double> mFloors;
    std::vector<double> mGearings;
    string mSwapIndex;
    std::vector<double> mSpreads;
    std::vector<double> mCaps;

    string mReturnValue;

    string mError;

    CmsLegWorker(
      string ObjectID
,       string PaymentBDC
,       std::vector<double> Nominals
,       string ScheduleID
,       std::vector<ObjectHandler::property_t> FixingDays
,       bool IsInArrears
,       string DayCounter
,       std::vector<double> Floors
,       std::vector<double> Gearings
,       string SwapIndex
,       std::vector<double> Spreads
,       std::vector<double> Caps
     )
      {
        mObjectID = ObjectID;
        mPaymentBDC = PaymentBDC;
        mNominals = Nominals;
        mScheduleID = ScheduleID;
        mFixingDays = FixingDays;
        mIsInArrears = IsInArrears;
        mDayCounter = DayCounter;
        mFloors = Floors;
        mGearings = Gearings;
        mSwapIndex = SwapIndex;
        mSpreads = Spreads;
        mCaps = Caps;
      };

    void Execute();
};

class DigitalCmsLegWorker {
  public:
    string mObjectID;
    string mPaymentBDC;
    std::vector<double> mNominals;
    string mScheduleID;
    std::vector<ObjectHandler::property_t> mFixingDays;
    bool mIsInArrears;
    string mDayCounter;
    std::vector<double> mGearings;
    string mSwapIndex;
    std::vector<double> mSpreads;
    std::vector<double> mCallStrikes;
    string mCallSpecs;
    std::vector<double> mCallPayoff;
    std::vector<double> mPutStrikes;
    string mPutSpecs;
    std::vector<double> mPutPayoff;
    string mReplication;

    string mReturnValue;

    string mError;

    DigitalCmsLegWorker(
      string ObjectID
,       string PaymentBDC
,       std::vector<double> Nominals
,       string ScheduleID
,       std::vector<ObjectHandler::property_t> FixingDays
,       bool IsInArrears
,       string DayCounter
,       std::vector<double> Gearings
,       string SwapIndex
,       std::vector<double> Spreads
,       std::vector<double> CallStrikes
,       string CallSpecs
,       std::vector<double> CallPayoff
,       std::vector<double> PutStrikes
,       string PutSpecs
,       std::vector<double> PutPayoff
,       string Replication
     )
      {
        mObjectID = ObjectID;
        mPaymentBDC = PaymentBDC;
        mNominals = Nominals;
        mScheduleID = ScheduleID;
        mFixingDays = FixingDays;
        mIsInArrears = IsInArrears;
        mDayCounter = DayCounter;
        mGearings = Gearings;
        mSwapIndex = SwapIndex;
        mSpreads = Spreads;
        mCallStrikes = CallStrikes;
        mCallSpecs = CallSpecs;
        mCallPayoff = CallPayoff;
        mPutStrikes = PutStrikes;
        mPutSpecs = PutSpecs;
        mPutPayoff = PutPayoff;
        mReplication = Replication;
      };

    void Execute();
};

class RangeAccrualLegWorker {
  public:
    string mObjectID;
    string mPaymentBDC;
    std::vector<double> mNominals;
    string mScheduleID;
    std::vector<ObjectHandler::property_t> mFixingDays;
    string mDayCounter;
    std::vector<double> mLowerStrikes;
    std::vector<double> mGearings;
    string mIborIndex;
    std::vector<double> mSpreads;
    std::vector<double> mUpperStrikes;
    string mObservationsTenor;
    string mObservationsBDC;

    string mReturnValue;

    string mError;

    RangeAccrualLegWorker(
      string ObjectID
,       string PaymentBDC
,       std::vector<double> Nominals
,       string ScheduleID
,       std::vector<ObjectHandler::property_t> FixingDays
,       string DayCounter
,       std::vector<double> LowerStrikes
,       std::vector<double> Gearings
,       string IborIndex
,       std::vector<double> Spreads
,       std::vector<double> UpperStrikes
,       string ObservationsTenor
,       string ObservationsBDC
     )
      {
        mObjectID = ObjectID;
        mPaymentBDC = PaymentBDC;
        mNominals = Nominals;
        mScheduleID = ScheduleID;
        mFixingDays = FixingDays;
        mDayCounter = DayCounter;
        mLowerStrikes = LowerStrikes;
        mGearings = Gearings;
        mIborIndex = IborIndex;
        mSpreads = Spreads;
        mUpperStrikes = UpperStrikes;
        mObservationsTenor = ObservationsTenor;
        mObservationsBDC = ObservationsBDC;
      };

    void Execute();
};

class CmsZeroLegWorker {
  public:
    string mObjectID;
    string mPaymentBDC;
    std::vector<double> mNominals;
    string mScheduleID;
    std::vector<ObjectHandler::property_t> mFixingDays;
    bool mIsInArrears;
    string mDayCounter;
    std::vector<double> mFloors;
    std::vector<double> mGearings;
    string mSwapIndex;
    std::vector<double> mSpreads;
    std::vector<double> mCaps;

    string mReturnValue;

    string mError;

    CmsZeroLegWorker(
      string ObjectID
,       string PaymentBDC
,       std::vector<double> Nominals
,       string ScheduleID
,       std::vector<ObjectHandler::property_t> FixingDays
,       bool IsInArrears
,       string DayCounter
,       std::vector<double> Floors
,       std::vector<double> Gearings
,       string SwapIndex
,       std::vector<double> Spreads
,       std::vector<double> Caps
     )
      {
        mObjectID = ObjectID;
        mPaymentBDC = PaymentBDC;
        mNominals = Nominals;
        mScheduleID = ScheduleID;
        mFixingDays = FixingDays;
        mIsInArrears = IsInArrears;
        mDayCounter = DayCounter;
        mFloors = Floors;
        mGearings = Gearings;
        mSwapIndex = SwapIndex;
        mSpreads = Spreads;
        mCaps = Caps;
      };

    void Execute();
};

class IborCouponPricerWorker {
  public:
    string mObjectID;
    ObjectHandler::property_t mVolatility;
    string mIborCouponPricerType;

    string mReturnValue;

    string mError;

    IborCouponPricerWorker(
      string ObjectID
,       ObjectHandler::property_t Volatility
,       string IborCouponPricerType
     )
      {
        mObjectID = ObjectID;
        mVolatility = Volatility;
        mIborCouponPricerType = IborCouponPricerType;
      };

    void Execute();
};

class CmsCouponPricerWorker {
  public:
    string mObjectID;
    ObjectHandler::property_t mVolatility;
    string mCmsCouponPricerType;
    string mYieldCurveModel;
    ObjectHandler::property_t mMeanReversion;

    string mReturnValue;

    string mError;

    CmsCouponPricerWorker(
      string ObjectID
,       ObjectHandler::property_t Volatility
,       string CmsCouponPricerType
,       string YieldCurveModel
,       ObjectHandler::property_t MeanReversion
     )
      {
        mObjectID = ObjectID;
        mVolatility = Volatility;
        mCmsCouponPricerType = CmsCouponPricerType;
        mYieldCurveModel = YieldCurveModel;
        mMeanReversion = MeanReversion;
      };

    void Execute();
};

class ConundrumPricerByNumericalIntegrationWorker {
  public:
    string mObjectID;
    ObjectHandler::property_t mSwaptionVol;
    string mYieldCurveModel;
    ObjectHandler::property_t mMeanReversion;
    double mLowerLimit;
    double mUpperLimit;
    double mPrecision;

    string mReturnValue;

    string mError;

    ConundrumPricerByNumericalIntegrationWorker(
      string ObjectID
,       ObjectHandler::property_t SwaptionVol
,       string YieldCurveModel
,       ObjectHandler::property_t MeanReversion
,       double LowerLimit
,       double UpperLimit
,       double Precision
     )
      {
        mObjectID = ObjectID;
        mSwaptionVol = SwaptionVol;
        mYieldCurveModel = YieldCurveModel;
        mMeanReversion = MeanReversion;
        mLowerLimit = LowerLimit;
        mUpperLimit = UpperLimit;
        mPrecision = Precision;
      };

    void Execute();
};

class DigitalReplicationWorker {
  public:
    string mObjectID;
    string mReplication;
    double mGap;

    string mReturnValue;

    string mError;

    DigitalReplicationWorker(
      string ObjectID
,       string Replication
,       double Gap
     )
      {
        mObjectID = ObjectID;
        mReplication = Replication;
        mGap = Gap;
      };

    void Execute();
};

class ConundrumPricerByNumericalIntegrationUpperLimitWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    ConundrumPricerByNumericalIntegrationUpperLimitWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};
 
#endif
