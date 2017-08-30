/* 
  Copyright (C) 2016 -2017 Jerry Jin
*/

#ifndef ratehelpers_h
#define ratehelpers_h
#include <nan.h>
#include <string>
#include <queue>
#include <utility>

#include "../quantlibxl.hpp"

#include <oh/objecthandler.hpp>

using namespace node;
using namespace v8;
using namespace std;


class DepositRateHelperWorker {
  public:
    string mObjectID;
    ObjectHandler::property_t mRate;
    string mIborIndex;

    string mReturnValue;

    string mError;

    DepositRateHelperWorker(
      string ObjectID
,       ObjectHandler::property_t Rate
,       string IborIndex
     )
      {
        mObjectID = ObjectID;
        mRate = Rate;
        mIborIndex = IborIndex;
      };

    void Execute();
};

class DepositRateHelper2Worker {
  public:
    string mObjectID;
    ObjectHandler::property_t mRate;
    string mTenor;
    ObjectHandler::property_t mFixingDays;
    string mCalendar;
    string mConvention;
    bool mEndOfMonth;
    string mDayCounter;

    string mReturnValue;

    string mError;

    DepositRateHelper2Worker(
      string ObjectID
,       ObjectHandler::property_t Rate
,       string Tenor
,       ObjectHandler::property_t FixingDays
,       string Calendar
,       string Convention
,       bool EndOfMonth
,       string DayCounter
     )
      {
        mObjectID = ObjectID;
        mRate = Rate;
        mTenor = Tenor;
        mFixingDays = FixingDays;
        mCalendar = Calendar;
        mConvention = Convention;
        mEndOfMonth = EndOfMonth;
        mDayCounter = DayCounter;
      };

    void Execute();
};

class SwapRateHelperWorker {
  public:
    string mObjectID;
    ObjectHandler::property_t mRate;
    string mSwapIndex;
    ObjectHandler::property_t mSpread;
    string mForwardStart;
    ObjectHandler::property_t mDiscountingCurve;
    string mPillarDate;
    ObjectHandler::property_t mCustomPillarDate;

    string mReturnValue;

    string mError;

    SwapRateHelperWorker(
      string ObjectID
,       ObjectHandler::property_t Rate
,       string SwapIndex
,       ObjectHandler::property_t Spread
,       string ForwardStart
,       ObjectHandler::property_t DiscountingCurve
,       string PillarDate
,       ObjectHandler::property_t CustomPillarDate
     )
      {
        mObjectID = ObjectID;
        mRate = Rate;
        mSwapIndex = SwapIndex;
        mSpread = Spread;
        mForwardStart = ForwardStart;
        mDiscountingCurve = DiscountingCurve;
        mPillarDate = PillarDate;
        mCustomPillarDate = CustomPillarDate;
      };

    void Execute();
};

class SwapRateHelper2Worker {
  public:
    string mObjectID;
    ObjectHandler::property_t mRate;
    ObjectHandler::property_t mSettlDays;
    string mTenor;
    string mCalendar;
    string mFixedLegFrequency;
    string mFixedLegConvention;
    string mFixedLegDayCounter;
    string mIborIndex;
    ObjectHandler::property_t mSpread;
    string mForwardStart;
    ObjectHandler::property_t mDiscountingCurve;
    string mPillarDate;
    ObjectHandler::property_t mCustomPillarDate;

    string mReturnValue;

    string mError;

    SwapRateHelper2Worker(
      string ObjectID
,       ObjectHandler::property_t Rate
,       ObjectHandler::property_t SettlDays
,       string Tenor
,       string Calendar
,       string FixedLegFrequency
,       string FixedLegConvention
,       string FixedLegDayCounter
,       string IborIndex
,       ObjectHandler::property_t Spread
,       string ForwardStart
,       ObjectHandler::property_t DiscountingCurve
,       string PillarDate
,       ObjectHandler::property_t CustomPillarDate
     )
      {
        mObjectID = ObjectID;
        mRate = Rate;
        mSettlDays = SettlDays;
        mTenor = Tenor;
        mCalendar = Calendar;
        mFixedLegFrequency = FixedLegFrequency;
        mFixedLegConvention = FixedLegConvention;
        mFixedLegDayCounter = FixedLegDayCounter;
        mIborIndex = IborIndex;
        mSpread = Spread;
        mForwardStart = ForwardStart;
        mDiscountingCurve = DiscountingCurve;
        mPillarDate = PillarDate;
        mCustomPillarDate = CustomPillarDate;
      };

    void Execute();
};

class OISRateHelperWorker {
  public:
    string mObjectID;
    ObjectHandler::property_t mSettlDays;
    string mTenor;
    ObjectHandler::property_t mFixedRate;
    string mONIndex;
    ObjectHandler::property_t mDiscountingCurve;

    string mReturnValue;

    string mError;

    OISRateHelperWorker(
      string ObjectID
,       ObjectHandler::property_t SettlDays
,       string Tenor
,       ObjectHandler::property_t FixedRate
,       string ONIndex
,       ObjectHandler::property_t DiscountingCurve
     )
      {
        mObjectID = ObjectID;
        mSettlDays = SettlDays;
        mTenor = Tenor;
        mFixedRate = FixedRate;
        mONIndex = ONIndex;
        mDiscountingCurve = DiscountingCurve;
      };

    void Execute();
};

class DatedOISRateHelperWorker {
  public:
    string mObjectID;
    ObjectHandler::property_t mStartDate;
    ObjectHandler::property_t mEndDate;
    ObjectHandler::property_t mFixedRate;
    string mONIndex;
    ObjectHandler::property_t mDiscountingCurve;

    string mReturnValue;

    string mError;

    DatedOISRateHelperWorker(
      string ObjectID
,       ObjectHandler::property_t StartDate
,       ObjectHandler::property_t EndDate
,       ObjectHandler::property_t FixedRate
,       string ONIndex
,       ObjectHandler::property_t DiscountingCurve
     )
      {
        mObjectID = ObjectID;
        mStartDate = StartDate;
        mEndDate = EndDate;
        mFixedRate = FixedRate;
        mONIndex = ONIndex;
        mDiscountingCurve = DiscountingCurve;
      };

    void Execute();
};

class FraRateHelperWorker {
  public:
    string mObjectID;
    ObjectHandler::property_t mRate;
    string mPeriodToStart;
    string mIborIndex;
    string mPillarDate;
    ObjectHandler::property_t mCustomPillarDate;

    string mReturnValue;

    string mError;

    FraRateHelperWorker(
      string ObjectID
,       ObjectHandler::property_t Rate
,       string PeriodToStart
,       string IborIndex
,       string PillarDate
,       ObjectHandler::property_t CustomPillarDate
     )
      {
        mObjectID = ObjectID;
        mRate = Rate;
        mPeriodToStart = PeriodToStart;
        mIborIndex = IborIndex;
        mPillarDate = PillarDate;
        mCustomPillarDate = CustomPillarDate;
      };

    void Execute();
};

class FraRateHelper2Worker {
  public:
    string mObjectID;
    ObjectHandler::property_t mRate;
    string mPeriodToStart;
    ObjectHandler::property_t mLengthInMonths;
    ObjectHandler::property_t mFixingDays;
    string mCalendar;
    string mConvention;
    bool mEndOfMonth;
    string mDayCounter;
    string mPillarDate;
    ObjectHandler::property_t mCustomPillarDate;

    string mReturnValue;

    string mError;

    FraRateHelper2Worker(
      string ObjectID
,       ObjectHandler::property_t Rate
,       string PeriodToStart
,       ObjectHandler::property_t LengthInMonths
,       ObjectHandler::property_t FixingDays
,       string Calendar
,       string Convention
,       bool EndOfMonth
,       string DayCounter
,       string PillarDate
,       ObjectHandler::property_t CustomPillarDate
     )
      {
        mObjectID = ObjectID;
        mRate = Rate;
        mPeriodToStart = PeriodToStart;
        mLengthInMonths = LengthInMonths;
        mFixingDays = FixingDays;
        mCalendar = Calendar;
        mConvention = Convention;
        mEndOfMonth = EndOfMonth;
        mDayCounter = DayCounter;
        mPillarDate = PillarDate;
        mCustomPillarDate = CustomPillarDate;
      };

    void Execute();
};

class BondHelperWorker {
  public:
    string mObjectID;
    ObjectHandler::property_t mPrice;
    string mBond;
    bool mUseCleanPrice;

    string mReturnValue;

    string mError;

    BondHelperWorker(
      string ObjectID
,       ObjectHandler::property_t Price
,       string Bond
,       bool UseCleanPrice
     )
      {
        mObjectID = ObjectID;
        mPrice = Price;
        mBond = Bond;
        mUseCleanPrice = UseCleanPrice;
      };

    void Execute();
};

class FixedRateBondHelperWorker {
  public:
    string mObjectID;
    ObjectHandler::property_t mPrice;
    long mSettlementDays;
    double mFaceAmount;
    string mScheduleID;
    std::vector<double> mCoupons;
    string mDayCounter;
    string mPaymentBDC;
    double mRedemption;
    ObjectHandler::property_t mIssueDate;
    string mPaymentCalendar;
    string mExCouponPeriod;
    string mExCouponCalendar;
    string mExCouponBDC;
    bool mExCouponEndOfMonth;
    bool mUseCleanPrice;

    string mReturnValue;

    string mError;

    FixedRateBondHelperWorker(
      string ObjectID
,       ObjectHandler::property_t Price
,       long SettlementDays
,       double FaceAmount
,       string ScheduleID
,       std::vector<double> Coupons
,       string DayCounter
,       string PaymentBDC
,       double Redemption
,       ObjectHandler::property_t IssueDate
,       string PaymentCalendar
,       string ExCouponPeriod
,       string ExCouponCalendar
,       string ExCouponBDC
,       bool ExCouponEndOfMonth
,       bool UseCleanPrice
     )
      {
        mObjectID = ObjectID;
        mPrice = Price;
        mSettlementDays = SettlementDays;
        mFaceAmount = FaceAmount;
        mScheduleID = ScheduleID;
        mCoupons = Coupons;
        mDayCounter = DayCounter;
        mPaymentBDC = PaymentBDC;
        mRedemption = Redemption;
        mIssueDate = IssueDate;
        mPaymentCalendar = PaymentCalendar;
        mExCouponPeriod = ExCouponPeriod;
        mExCouponCalendar = ExCouponCalendar;
        mExCouponBDC = ExCouponBDC;
        mExCouponEndOfMonth = ExCouponEndOfMonth;
        mUseCleanPrice = UseCleanPrice;
      };

    void Execute();
};

class FuturesRateHelperWorker {
  public:
    string mObjectID;
    ObjectHandler::property_t mPrice;
    string mFuturesType;
    ObjectHandler::property_t mFuturesDate;
    string mIborIndex;
    ObjectHandler::property_t mConvexityAdjQuote;

    string mReturnValue;

    string mError;

    FuturesRateHelperWorker(
      string ObjectID
,       ObjectHandler::property_t Price
,       string FuturesType
,       ObjectHandler::property_t FuturesDate
,       string IborIndex
,       ObjectHandler::property_t ConvexityAdjQuote
     )
      {
        mObjectID = ObjectID;
        mPrice = Price;
        mFuturesType = FuturesType;
        mFuturesDate = FuturesDate;
        mIborIndex = IborIndex;
        mConvexityAdjQuote = ConvexityAdjQuote;
      };

    void Execute();
};

class FuturesRateHelper2Worker {
  public:
    string mObjectID;
    ObjectHandler::property_t mPrice;
    string mFuturesType;
    ObjectHandler::property_t mFuturesDate;
    long mLengthInMonths;
    string mCalendar;
    string mConvention;
    bool mEndOfMonth;
    string mDayCounter;
    ObjectHandler::property_t mConvexityAdjQuote;

    string mReturnValue;

    string mError;

    FuturesRateHelper2Worker(
      string ObjectID
,       ObjectHandler::property_t Price
,       string FuturesType
,       ObjectHandler::property_t FuturesDate
,       long LengthInMonths
,       string Calendar
,       string Convention
,       bool EndOfMonth
,       string DayCounter
,       ObjectHandler::property_t ConvexityAdjQuote
     )
      {
        mObjectID = ObjectID;
        mPrice = Price;
        mFuturesType = FuturesType;
        mFuturesDate = FuturesDate;
        mLengthInMonths = LengthInMonths;
        mCalendar = Calendar;
        mConvention = Convention;
        mEndOfMonth = EndOfMonth;
        mDayCounter = DayCounter;
        mConvexityAdjQuote = ConvexityAdjQuote;
      };

    void Execute();
};

class FuturesRateHelper3Worker {
  public:
    string mObjectID;
    ObjectHandler::property_t mPrice;
    string mFuturesType;
    ObjectHandler::property_t mFuturesDate;
    ObjectHandler::property_t mEndDate;
    string mDayCounter;
    ObjectHandler::property_t mConvexityAdjQuote;

    string mReturnValue;

    string mError;

    FuturesRateHelper3Worker(
      string ObjectID
,       ObjectHandler::property_t Price
,       string FuturesType
,       ObjectHandler::property_t FuturesDate
,       ObjectHandler::property_t EndDate
,       string DayCounter
,       ObjectHandler::property_t ConvexityAdjQuote
     )
      {
        mObjectID = ObjectID;
        mPrice = Price;
        mFuturesType = FuturesType;
        mFuturesDate = FuturesDate;
        mEndDate = EndDate;
        mDayCounter = DayCounter;
        mConvexityAdjQuote = ConvexityAdjQuote;
      };

    void Execute();
};

class FxSwapRateHelperWorker {
  public:
    string mObjectID;
    ObjectHandler::property_t mFwdPoint;
    ObjectHandler::property_t mSpotFx;
    string mTenor;
    ObjectHandler::property_t mFixingDays;
    string mCalendar;
    string mConvention;
    bool mEndOfMonth;
    bool mIsFxBaseCurrencyCollateralCurrency;
    ObjectHandler::property_t mCollateralCurve;

    string mReturnValue;

    string mError;

    FxSwapRateHelperWorker(
      string ObjectID
,       ObjectHandler::property_t FwdPoint
,       ObjectHandler::property_t SpotFx
,       string Tenor
,       ObjectHandler::property_t FixingDays
,       string Calendar
,       string Convention
,       bool EndOfMonth
,       bool IsFxBaseCurrencyCollateralCurrency
,       ObjectHandler::property_t CollateralCurve
     )
      {
        mObjectID = ObjectID;
        mFwdPoint = FwdPoint;
        mSpotFx = SpotFx;
        mTenor = Tenor;
        mFixingDays = FixingDays;
        mCalendar = Calendar;
        mConvention = Convention;
        mEndOfMonth = EndOfMonth;
        mIsFxBaseCurrencyCollateralCurrency = IsFxBaseCurrencyCollateralCurrency;
        mCollateralCurve = CollateralCurve;
      };

    void Execute();
};

class RateHelperEarliestDateWorker {
  public:
    string mObjectID;

    long mReturnValue;

    string mError;

    RateHelperEarliestDateWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class RateHelperLatestRelevantDateWorker {
  public:
    string mObjectID;

    long mReturnValue;

    string mError;

    RateHelperLatestRelevantDateWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class RateHelperPillarDateWorker {
  public:
    string mObjectID;

    long mReturnValue;

    string mError;

    RateHelperPillarDateWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class RateHelperMaturityDateWorker {
  public:
    string mObjectID;

    long mReturnValue;

    string mError;

    RateHelperMaturityDateWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class RateHelperQuoteNameWorker {
  public:
    string mObjectID;

    string mReturnValue;

    string mError;

    RateHelperQuoteNameWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class RateHelperQuoteValueWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    RateHelperQuoteValueWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class RateHelperQuoteIsValidWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    RateHelperQuoteIsValidWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class RateHelperImpliedQuoteWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    RateHelperImpliedQuoteWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class RateHelperQuoteErrorWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    RateHelperQuoteErrorWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class SwapRateHelperSpreadWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    SwapRateHelperSpreadWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class SwapRateHelperForwardStartWorker {
  public:
    string mObjectID;

    string mReturnValue;

    string mError;

    SwapRateHelperForwardStartWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class FuturesRateHelperConvexityAdjustmentWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    FuturesRateHelperConvexityAdjustmentWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class FxSwapRateHelperSpotValueWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    FxSwapRateHelperSpotValueWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class FxSwapRateHelperTenorWorker {
  public:
    string mObjectID;

    string mReturnValue;

    string mError;

    FxSwapRateHelperTenorWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class FxSwapRateHelperFixingDaysWorker {
  public:
    string mObjectID;

    long mReturnValue;

    string mError;

    FxSwapRateHelperFixingDaysWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class FxSwapRateHelperCalendarWorker {
  public:
    string mObjectID;

    string mReturnValue;

    string mError;

    FxSwapRateHelperCalendarWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class FxSwapRateHelperBDCWorker {
  public:
    string mObjectID;

    string mReturnValue;

    string mError;

    FxSwapRateHelperBDCWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class FxSwapRateHelperEOMWorker {
  public:
    string mObjectID;

    bool mReturnValue;

    string mError;

    FxSwapRateHelperEOMWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class FxSwapRateHelperIsBaseCurrencyCollateralCurrencyWorker {
  public:
    string mObjectID;

    bool mReturnValue;

    string mError;

    FxSwapRateHelperIsBaseCurrencyCollateralCurrencyWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class RateHelperSelectionWorker {
  public:
    std::vector<string> mRateHelpers;
    std::vector<ObjectHandler::property_t> mPriority;
    ObjectHandler::property_t mNImmFutures;
    ObjectHandler::property_t mNSerialFutures;
    ObjectHandler::property_t mFutureRollDays;
    string mDepoInclusion;
    std::vector<ObjectHandler::property_t> mMinDistance;

    std::vector<string> mReturnValue;

    string mError;

    RateHelperSelectionWorker(
      std::vector<string> RateHelpers
,       std::vector<ObjectHandler::property_t> Priority
,       ObjectHandler::property_t NImmFutures
,       ObjectHandler::property_t NSerialFutures
,       ObjectHandler::property_t FutureRollDays
,       string DepoInclusion
,       std::vector<ObjectHandler::property_t> MinDistance
     )
      {
        mRateHelpers = RateHelpers;
        mPriority = Priority;
        mNImmFutures = NImmFutures;
        mNSerialFutures = NSerialFutures;
        mFutureRollDays = FutureRollDays;
        mDepoInclusion = DepoInclusion;
        mMinDistance = MinDistance;
      };

    void Execute();
};

class RateHelperRateWorker {
  public:
    string mRateHelper;

    double mReturnValue;

    string mError;

    RateHelperRateWorker(
      string RateHelper
     )
      {
        mRateHelper = RateHelper;
      };

    void Execute();
};
 
#endif
