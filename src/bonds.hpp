/* 
  Copyright (C) 2016 -2017 Jerry Jin
*/

#ifndef bonds_h
#define bonds_h
#include <nan.h>
#include <string>
#include <queue>
#include <utility>

#include "../quantlibxl.hpp"

#include <oh/objecthandler.hpp>

using namespace node;
using namespace v8;
using namespace std;


class FixedRateBondWorker {
  public:
    string mObjectID;
    string mDescription;
    string mCurrency;
    long mSettlementDays;
    double mFaceAmount;
    string mScheduleID;
    std::vector<double> mCoupons;
    string mDayCounter;
    string mPaymentBDC;
    double mRedemption;
    ObjectHandler::property_t mIssueDate;
    string mPaymentCalendar;

    string mReturnValue;

    string mError;

    FixedRateBondWorker(
      string ObjectID
,       string Description
,       string Currency
,       long SettlementDays
,       double FaceAmount
,       string ScheduleID
,       std::vector<double> Coupons
,       string DayCounter
,       string PaymentBDC
,       double Redemption
,       ObjectHandler::property_t IssueDate
,       string PaymentCalendar
     )
      {
        mObjectID = ObjectID;
        mDescription = Description;
        mCurrency = Currency;
        mSettlementDays = SettlementDays;
        mFaceAmount = FaceAmount;
        mScheduleID = ScheduleID;
        mCoupons = Coupons;
        mDayCounter = DayCounter;
        mPaymentBDC = PaymentBDC;
        mRedemption = Redemption;
        mIssueDate = IssueDate;
        mPaymentCalendar = PaymentCalendar;
      };

    void Execute();
};

class FixedRateBond2Worker {
  public:
    string mObjectID;
    string mDescription;
    string mCurrency;
    long mSettlementDays;
    double mFaceAmount;
    string mScheduleID;
    std::vector<string> mCoupons;
    string mPaymentBDC;
    double mRedemption;
    ObjectHandler::property_t mIssueDate;
    string mPaymentCalendar;

    string mReturnValue;

    string mError;

    FixedRateBond2Worker(
      string ObjectID
,       string Description
,       string Currency
,       long SettlementDays
,       double FaceAmount
,       string ScheduleID
,       std::vector<string> Coupons
,       string PaymentBDC
,       double Redemption
,       ObjectHandler::property_t IssueDate
,       string PaymentCalendar
     )
      {
        mObjectID = ObjectID;
        mDescription = Description;
        mCurrency = Currency;
        mSettlementDays = SettlementDays;
        mFaceAmount = FaceAmount;
        mScheduleID = ScheduleID;
        mCoupons = Coupons;
        mPaymentBDC = PaymentBDC;
        mRedemption = Redemption;
        mIssueDate = IssueDate;
        mPaymentCalendar = PaymentCalendar;
      };

    void Execute();
};

class FloatingRateBondWorker {
  public:
    string mObjectID;
    string mDescription;
    string mCurrency;
    long mSettlementDays;
    string mPaymentBDC;
    double mFaceAmount;
    string mScheduleID;
    ObjectHandler::property_t mFixingDays;
    bool mIsInArrears;
    string mDayCounter;
    std::vector<double> mFloors;
    std::vector<double> mGearings;
    string mIborIndex;
    std::vector<double> mSpreads;
    std::vector<double> mCaps;
    double mRedemption;
    ObjectHandler::property_t mIssueDate;

    string mReturnValue;

    string mError;

    FloatingRateBondWorker(
      string ObjectID
,       string Description
,       string Currency
,       long SettlementDays
,       string PaymentBDC
,       double FaceAmount
,       string ScheduleID
,       ObjectHandler::property_t FixingDays
,       bool IsInArrears
,       string DayCounter
,       std::vector<double> Floors
,       std::vector<double> Gearings
,       string IborIndex
,       std::vector<double> Spreads
,       std::vector<double> Caps
,       double Redemption
,       ObjectHandler::property_t IssueDate
     )
      {
        mObjectID = ObjectID;
        mDescription = Description;
        mCurrency = Currency;
        mSettlementDays = SettlementDays;
        mPaymentBDC = PaymentBDC;
        mFaceAmount = FaceAmount;
        mScheduleID = ScheduleID;
        mFixingDays = FixingDays;
        mIsInArrears = IsInArrears;
        mDayCounter = DayCounter;
        mFloors = Floors;
        mGearings = Gearings;
        mIborIndex = IborIndex;
        mSpreads = Spreads;
        mCaps = Caps;
        mRedemption = Redemption;
        mIssueDate = IssueDate;
      };

    void Execute();
};

class CmsRateBondWorker {
  public:
    string mObjectID;
    string mDescription;
    string mCurrency;
    long mSettlementDays;
    string mPaymentBDC;
    double mFaceAmount;
    string mScheduleID;
    ObjectHandler::property_t mFixingDays;
    bool mIsInArrears;
    string mDayCounter;
    std::vector<double> mFloors;
    std::vector<double> mGearings;
    string mSwapIndex;
    std::vector<double> mSpreads;
    std::vector<double> mCaps;
    double mRedemption;
    ObjectHandler::property_t mIssueDate;

    string mReturnValue;

    string mError;

    CmsRateBondWorker(
      string ObjectID
,       string Description
,       string Currency
,       long SettlementDays
,       string PaymentBDC
,       double FaceAmount
,       string ScheduleID
,       ObjectHandler::property_t FixingDays
,       bool IsInArrears
,       string DayCounter
,       std::vector<double> Floors
,       std::vector<double> Gearings
,       string SwapIndex
,       std::vector<double> Spreads
,       std::vector<double> Caps
,       double Redemption
,       ObjectHandler::property_t IssueDate
     )
      {
        mObjectID = ObjectID;
        mDescription = Description;
        mCurrency = Currency;
        mSettlementDays = SettlementDays;
        mPaymentBDC = PaymentBDC;
        mFaceAmount = FaceAmount;
        mScheduleID = ScheduleID;
        mFixingDays = FixingDays;
        mIsInArrears = IsInArrears;
        mDayCounter = DayCounter;
        mFloors = Floors;
        mGearings = Gearings;
        mSwapIndex = SwapIndex;
        mSpreads = Spreads;
        mCaps = Caps;
        mRedemption = Redemption;
        mIssueDate = IssueDate;
      };

    void Execute();
};

class ZeroCouponBondWorker {
  public:
    string mObjectID;
    string mDescription;
    string mCurrency;
    long mSettlementDays;
    string mCalendar;
    double mFaceAmount;
    ObjectHandler::property_t mMaturity;
    string mPaymentBDC;
    double mRedemption;
    ObjectHandler::property_t mIssueDate;

    string mReturnValue;

    string mError;

    ZeroCouponBondWorker(
      string ObjectID
,       string Description
,       string Currency
,       long SettlementDays
,       string Calendar
,       double FaceAmount
,       ObjectHandler::property_t Maturity
,       string PaymentBDC
,       double Redemption
,       ObjectHandler::property_t IssueDate
     )
      {
        mObjectID = ObjectID;
        mDescription = Description;
        mCurrency = Currency;
        mSettlementDays = SettlementDays;
        mCalendar = Calendar;
        mFaceAmount = FaceAmount;
        mMaturity = Maturity;
        mPaymentBDC = PaymentBDC;
        mRedemption = Redemption;
        mIssueDate = IssueDate;
      };

    void Execute();
};

class BondWorker {
  public:
    string mObjectID;
    string mDescription;
    string mCurrency;
    long mSettlementDays;
    string mCalendar;
    double mFaceAmount;
    ObjectHandler::property_t mMaturityDate;
    ObjectHandler::property_t mIssueDate;
    string mLegID;

    string mReturnValue;

    string mError;

    BondWorker(
      string ObjectID
,       string Description
,       string Currency
,       long SettlementDays
,       string Calendar
,       double FaceAmount
,       ObjectHandler::property_t MaturityDate
,       ObjectHandler::property_t IssueDate
,       string LegID
     )
      {
        mObjectID = ObjectID;
        mDescription = Description;
        mCurrency = Currency;
        mSettlementDays = SettlementDays;
        mCalendar = Calendar;
        mFaceAmount = FaceAmount;
        mMaturityDate = MaturityDate;
        mIssueDate = IssueDate;
        mLegID = LegID;
      };

    void Execute();
};

class BondSettlementDaysWorker {
  public:
    string mObjectID;

    long mReturnValue;

    string mError;

    BondSettlementDaysWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class BondCalendarWorker {
  public:
    string mObjectID;

    string mReturnValue;

    string mError;

    BondCalendarWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class BondNotionalsWorker {
  public:
    string mObjectID;

    std::vector<double> mReturnValue;

    string mError;

    BondNotionalsWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class BondNotionalWorker {
  public:
    string mObjectID;
    ObjectHandler::property_t mSettlementDate;

    double mReturnValue;

    string mError;

    BondNotionalWorker(
      string ObjectID
,       ObjectHandler::property_t SettlementDate
     )
      {
        mObjectID = ObjectID;
        mSettlementDate = SettlementDate;
      };

    void Execute();
};

class BondMaturityDateWorker {
  public:
    string mObjectID;

    long mReturnValue;

    string mError;

    BondMaturityDateWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class BondIssueDateWorker {
  public:
    string mObjectID;

    long mReturnValue;

    string mError;

    BondIssueDateWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class BondIsTradableWorker {
  public:
    string mObjectID;
    ObjectHandler::property_t mSettlementDate;

    bool mReturnValue;

    string mError;

    BondIsTradableWorker(
      string ObjectID
,       ObjectHandler::property_t SettlementDate
     )
      {
        mObjectID = ObjectID;
        mSettlementDate = SettlementDate;
      };

    void Execute();
};

class BondSettlementDateWorker {
  public:
    string mObjectID;
    ObjectHandler::property_t mEvaluationDate;

    long mReturnValue;

    string mError;

    BondSettlementDateWorker(
      string ObjectID
,       ObjectHandler::property_t EvaluationDate
     )
      {
        mObjectID = ObjectID;
        mEvaluationDate = EvaluationDate;
      };

    void Execute();
};

class BondCleanPriceWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    BondCleanPriceWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class BondDescriptionWorker {
  public:
    string mObjectID;

    string mReturnValue;

    string mError;

    BondDescriptionWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class BondCurrencyWorker {
  public:
    string mObjectID;

    string mReturnValue;

    string mError;

    BondCurrencyWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class BondRedemptionAmountWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    BondRedemptionAmountWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class BondRedemptionDateWorker {
  public:
    string mObjectID;

    long mReturnValue;

    string mError;

    BondRedemptionDateWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class BondFlowAnalysisWorker {
  public:
    string mObjectID;
    ObjectHandler::property_t mAfterDate;

    std::vector< std::vector<string> > mReturnValue;

    string mError;

    BondFlowAnalysisWorker(
      string ObjectID
,       ObjectHandler::property_t AfterDate
     )
      {
        mObjectID = ObjectID;
        mAfterDate = AfterDate;
      };

    void Execute();
};

class BondSetCouponPricerWorker {
  public:
    string mObjectID;
    string mFloatingRateCouponPricer;

    string mError;

    BondSetCouponPricerWorker(
      string ObjectID
,       string FloatingRateCouponPricer
     )
      {
        mObjectID = ObjectID;
        mFloatingRateCouponPricer = FloatingRateCouponPricer;
      };

    void Execute();
};

class BondSetCouponPricersWorker {
  public:
    string mObjectID;
    std::vector<string> mFloatingRateCouponPricer;

    string mError;

    BondSetCouponPricersWorker(
      string ObjectID
,       std::vector<string> FloatingRateCouponPricer
     )
      {
        mObjectID = ObjectID;
        mFloatingRateCouponPricer = FloatingRateCouponPricer;
      };

    void Execute();
};

class BondStartDateWorker {
  public:
    string mObjectId;

    long mReturnValue;

    string mError;

    BondStartDateWorker(
      string ObjectId
     )
      {
        mObjectId = ObjectId;
      };

    void Execute();
};

class BondPreviousCashFlowDateWorker {
  public:
    string mObjectId;
    ObjectHandler::property_t mSettlementDate;

    long mReturnValue;

    string mError;

    BondPreviousCashFlowDateWorker(
      string ObjectId
,       ObjectHandler::property_t SettlementDate
     )
      {
        mObjectId = ObjectId;
        mSettlementDate = SettlementDate;
      };

    void Execute();
};

class BondNextCashFlowDateWorker {
  public:
    string mObjectId;
    ObjectHandler::property_t mSettlementDate;

    long mReturnValue;

    string mError;

    BondNextCashFlowDateWorker(
      string ObjectId
,       ObjectHandler::property_t SettlementDate
     )
      {
        mObjectId = ObjectId;
        mSettlementDate = SettlementDate;
      };

    void Execute();
};

class BondPreviousCashFlowAmountWorker {
  public:
    string mObjectId;
    ObjectHandler::property_t mSettlementDate;

    double mReturnValue;

    string mError;

    BondPreviousCashFlowAmountWorker(
      string ObjectId
,       ObjectHandler::property_t SettlementDate
     )
      {
        mObjectId = ObjectId;
        mSettlementDate = SettlementDate;
      };

    void Execute();
};

class BondNextCashFlowAmountWorker {
  public:
    string mObjectId;
    ObjectHandler::property_t mSettlementDate;

    double mReturnValue;

    string mError;

    BondNextCashFlowAmountWorker(
      string ObjectId
,       ObjectHandler::property_t SettlementDate
     )
      {
        mObjectId = ObjectId;
        mSettlementDate = SettlementDate;
      };

    void Execute();
};

class BondPreviousCouponRateWorker {
  public:
    string mObjectId;
    ObjectHandler::property_t mSettlementDate;

    double mReturnValue;

    string mError;

    BondPreviousCouponRateWorker(
      string ObjectId
,       ObjectHandler::property_t SettlementDate
     )
      {
        mObjectId = ObjectId;
        mSettlementDate = SettlementDate;
      };

    void Execute();
};

class BondNextCouponRateWorker {
  public:
    string mObjectId;
    ObjectHandler::property_t mSettlementDate;

    double mReturnValue;

    string mError;

    BondNextCouponRateWorker(
      string ObjectId
,       ObjectHandler::property_t SettlementDate
     )
      {
        mObjectId = ObjectId;
        mSettlementDate = SettlementDate;
      };

    void Execute();
};

class BondAccrualStartDateWorker {
  public:
    string mObjectId;
    ObjectHandler::property_t mSettlementDate;

    long mReturnValue;

    string mError;

    BondAccrualStartDateWorker(
      string ObjectId
,       ObjectHandler::property_t SettlementDate
     )
      {
        mObjectId = ObjectId;
        mSettlementDate = SettlementDate;
      };

    void Execute();
};

class BondAccrualEndDateWorker {
  public:
    string mObjectId;
    ObjectHandler::property_t mSettlementDate;

    long mReturnValue;

    string mError;

    BondAccrualEndDateWorker(
      string ObjectId
,       ObjectHandler::property_t SettlementDate
     )
      {
        mObjectId = ObjectId;
        mSettlementDate = SettlementDate;
      };

    void Execute();
};

class BondReferencePeriodStartWorker {
  public:
    string mObjectId;
    ObjectHandler::property_t mSettlementDate;

    long mReturnValue;

    string mError;

    BondReferencePeriodStartWorker(
      string ObjectId
,       ObjectHandler::property_t SettlementDate
     )
      {
        mObjectId = ObjectId;
        mSettlementDate = SettlementDate;
      };

    void Execute();
};

class BondReferencePeriodEndWorker {
  public:
    string mObjectId;
    ObjectHandler::property_t mSettlementDate;

    long mReturnValue;

    string mError;

    BondReferencePeriodEndWorker(
      string ObjectId
,       ObjectHandler::property_t SettlementDate
     )
      {
        mObjectId = ObjectId;
        mSettlementDate = SettlementDate;
      };

    void Execute();
};

class BondAccrualPeriodWorker {
  public:
    string mObjectId;
    ObjectHandler::property_t mSettlementDate;

    double mReturnValue;

    string mError;

    BondAccrualPeriodWorker(
      string ObjectId
,       ObjectHandler::property_t SettlementDate
     )
      {
        mObjectId = ObjectId;
        mSettlementDate = SettlementDate;
      };

    void Execute();
};

class BondAccrualDaysWorker {
  public:
    string mObjectId;
    ObjectHandler::property_t mSettlementDate;

    long mReturnValue;

    string mError;

    BondAccrualDaysWorker(
      string ObjectId
,       ObjectHandler::property_t SettlementDate
     )
      {
        mObjectId = ObjectId;
        mSettlementDate = SettlementDate;
      };

    void Execute();
};

class BondAccruedPeriodWorker {
  public:
    string mObjectId;
    ObjectHandler::property_t mSettlementDate;

    double mReturnValue;

    string mError;

    BondAccruedPeriodWorker(
      string ObjectId
,       ObjectHandler::property_t SettlementDate
     )
      {
        mObjectId = ObjectId;
        mSettlementDate = SettlementDate;
      };

    void Execute();
};

class BondAccruedDaysWorker {
  public:
    string mObjectId;
    ObjectHandler::property_t mSettlementDate;

    long mReturnValue;

    string mError;

    BondAccruedDaysWorker(
      string ObjectId
,       ObjectHandler::property_t SettlementDate
     )
      {
        mObjectId = ObjectId;
        mSettlementDate = SettlementDate;
      };

    void Execute();
};

class BondAccruedAmountWorker {
  public:
    string mObjectId;
    ObjectHandler::property_t mSettlementDate;

    double mReturnValue;

    string mError;

    BondAccruedAmountWorker(
      string ObjectId
,       ObjectHandler::property_t SettlementDate
     )
      {
        mObjectId = ObjectId;
        mSettlementDate = SettlementDate;
      };

    void Execute();
};

class BondCleanPriceFromYieldTermStructureWorker {
  public:
    string mObjectId;
    string mYieldCurve;
    ObjectHandler::property_t mSettlementDate;

    double mReturnValue;

    string mError;

    BondCleanPriceFromYieldTermStructureWorker(
      string ObjectId
,       string YieldCurve
,       ObjectHandler::property_t SettlementDate
     )
      {
        mObjectId = ObjectId;
        mYieldCurve = YieldCurve;
        mSettlementDate = SettlementDate;
      };

    void Execute();
};

class BondBpsFromYieldTermStructureWorker {
  public:
    string mObjectId;
    string mYieldCurve;
    ObjectHandler::property_t mSettlementDate;

    double mReturnValue;

    string mError;

    BondBpsFromYieldTermStructureWorker(
      string ObjectId
,       string YieldCurve
,       ObjectHandler::property_t SettlementDate
     )
      {
        mObjectId = ObjectId;
        mYieldCurve = YieldCurve;
        mSettlementDate = SettlementDate;
      };

    void Execute();
};

class BondAtmRateFromYieldTermStructureWorker {
  public:
    string mObjectId;
    string mYieldCurve;
    ObjectHandler::property_t mSettlementDate;
    double mCleanPrice;

    double mReturnValue;

    string mError;

    BondAtmRateFromYieldTermStructureWorker(
      string ObjectId
,       string YieldCurve
,       ObjectHandler::property_t SettlementDate
,       double CleanPrice
     )
      {
        mObjectId = ObjectId;
        mYieldCurve = YieldCurve;
        mSettlementDate = SettlementDate;
        mCleanPrice = CleanPrice;
      };

    void Execute();
};

class BondCleanPriceFromYieldWorker {
  public:
    string mObjectId;
    double mYield;
    string mDayCounter;
    string mCompounding;
    string mFrequency;
    ObjectHandler::property_t mSettlementDate;

    double mReturnValue;

    string mError;

    BondCleanPriceFromYieldWorker(
      string ObjectId
,       double Yield
,       string DayCounter
,       string Compounding
,       string Frequency
,       ObjectHandler::property_t SettlementDate
     )
      {
        mObjectId = ObjectId;
        mYield = Yield;
        mDayCounter = DayCounter;
        mCompounding = Compounding;
        mFrequency = Frequency;
        mSettlementDate = SettlementDate;
      };

    void Execute();
};

class BondDirtyPriceFromYieldWorker {
  public:
    string mObjectId;
    double mYield;
    string mDayCounter;
    string mCompounding;
    string mFrequency;
    ObjectHandler::property_t mSettlementDate;

    double mReturnValue;

    string mError;

    BondDirtyPriceFromYieldWorker(
      string ObjectId
,       double Yield
,       string DayCounter
,       string Compounding
,       string Frequency
,       ObjectHandler::property_t SettlementDate
     )
      {
        mObjectId = ObjectId;
        mYield = Yield;
        mDayCounter = DayCounter;
        mCompounding = Compounding;
        mFrequency = Frequency;
        mSettlementDate = SettlementDate;
      };

    void Execute();
};

class BondBpsFromYieldWorker {
  public:
    string mObjectId;
    double mYield;
    string mDayCounter;
    string mCompounding;
    string mFrequency;
    ObjectHandler::property_t mSettlementDate;

    double mReturnValue;

    string mError;

    BondBpsFromYieldWorker(
      string ObjectId
,       double Yield
,       string DayCounter
,       string Compounding
,       string Frequency
,       ObjectHandler::property_t SettlementDate
     )
      {
        mObjectId = ObjectId;
        mYield = Yield;
        mDayCounter = DayCounter;
        mCompounding = Compounding;
        mFrequency = Frequency;
        mSettlementDate = SettlementDate;
      };

    void Execute();
};

class BondYieldFromCleanPriceWorker {
  public:
    string mObjectId;
    double mCleanPrice;
    string mDayCounter;
    string mCompounding;
    string mFrequency;
    ObjectHandler::property_t mSettlementDate;
    double mAccuracy;
    long mMaxIterations;
    double mGuess;

    double mReturnValue;

    string mError;

    BondYieldFromCleanPriceWorker(
      string ObjectId
,       double CleanPrice
,       string DayCounter
,       string Compounding
,       string Frequency
,       ObjectHandler::property_t SettlementDate
,       double Accuracy
,       long MaxIterations
,       double Guess
     )
      {
        mObjectId = ObjectId;
        mCleanPrice = CleanPrice;
        mDayCounter = DayCounter;
        mCompounding = Compounding;
        mFrequency = Frequency;
        mSettlementDate = SettlementDate;
        mAccuracy = Accuracy;
        mMaxIterations = MaxIterations;
        mGuess = Guess;
      };

    void Execute();
};

class BondDurationFromYieldWorker {
  public:
    string mObjectId;
    double mYield;
    string mDayCounter;
    string mCompounding;
    string mFrequency;
    string mDurationType;
    ObjectHandler::property_t mSettlementDate;

    double mReturnValue;

    string mError;

    BondDurationFromYieldWorker(
      string ObjectId
,       double Yield
,       string DayCounter
,       string Compounding
,       string Frequency
,       string DurationType
,       ObjectHandler::property_t SettlementDate
     )
      {
        mObjectId = ObjectId;
        mYield = Yield;
        mDayCounter = DayCounter;
        mCompounding = Compounding;
        mFrequency = Frequency;
        mDurationType = DurationType;
        mSettlementDate = SettlementDate;
      };

    void Execute();
};

class BondConvexityFromYieldWorker {
  public:
    string mObjectId;
    double mYield;
    string mDayCounter;
    string mCompounding;
    string mFrequency;
    ObjectHandler::property_t mSettlementDate;

    double mReturnValue;

    string mError;

    BondConvexityFromYieldWorker(
      string ObjectId
,       double Yield
,       string DayCounter
,       string Compounding
,       string Frequency
,       ObjectHandler::property_t SettlementDate
     )
      {
        mObjectId = ObjectId;
        mYield = Yield;
        mDayCounter = DayCounter;
        mCompounding = Compounding;
        mFrequency = Frequency;
        mSettlementDate = SettlementDate;
      };

    void Execute();
};

class BondCleanPriceFromZSpreadWorker {
  public:
    string mObjectId;
    string mYieldCurve;
    double mZSpread;
    string mDayCounter;
    string mCompounding;
    string mFrequency;
    ObjectHandler::property_t mSettlementDate;

    double mReturnValue;

    string mError;

    BondCleanPriceFromZSpreadWorker(
      string ObjectId
,       string YieldCurve
,       double ZSpread
,       string DayCounter
,       string Compounding
,       string Frequency
,       ObjectHandler::property_t SettlementDate
     )
      {
        mObjectId = ObjectId;
        mYieldCurve = YieldCurve;
        mZSpread = ZSpread;
        mDayCounter = DayCounter;
        mCompounding = Compounding;
        mFrequency = Frequency;
        mSettlementDate = SettlementDate;
      };

    void Execute();
};

class BondZSpreadFromCleanPriceWorker {
  public:
    string mObjectId;
    double mCleanPrice;
    string mYieldCurve;
    string mDayCounter;
    string mCompounding;
    string mFrequency;
    ObjectHandler::property_t mSettlementDate;
    double mAccuracy;
    long mMaxIterations;
    double mGuess;

    double mReturnValue;

    string mError;

    BondZSpreadFromCleanPriceWorker(
      string ObjectId
,       double CleanPrice
,       string YieldCurve
,       string DayCounter
,       string Compounding
,       string Frequency
,       ObjectHandler::property_t SettlementDate
,       double Accuracy
,       long MaxIterations
,       double Guess
     )
      {
        mObjectId = ObjectId;
        mCleanPrice = CleanPrice;
        mYieldCurve = YieldCurve;
        mDayCounter = DayCounter;
        mCompounding = Compounding;
        mFrequency = Frequency;
        mSettlementDate = SettlementDate;
        mAccuracy = Accuracy;
        mMaxIterations = MaxIterations;
        mGuess = Guess;
      };

    void Execute();
};

class BondAliveWorker {
  public:
    std::vector<string> mBonds;
    ObjectHandler::property_t mRefDate;

    std::vector<string> mReturnValue;

    string mError;

    BondAliveWorker(
      std::vector<string> Bonds
,       ObjectHandler::property_t RefDate
     )
      {
        mBonds = Bonds;
        mRefDate = RefDate;
      };

    void Execute();
};

class BondMaturityLookupWorker {
  public:
    std::vector<string> mBonds;
    ObjectHandler::property_t mMaturity;

    string mReturnValue;

    string mError;

    BondMaturityLookupWorker(
      std::vector<string> Bonds
,       ObjectHandler::property_t Maturity
     )
      {
        mBonds = Bonds;
        mMaturity = Maturity;
      };

    void Execute();
};

class BondMaturitySortWorker {
  public:
    std::vector<string> mBonds;

    std::vector<string> mReturnValue;

    string mError;

    BondMaturitySortWorker(
      std::vector<string> Bonds
     )
      {
        mBonds = Bonds;
      };

    void Execute();
};
 
#endif
