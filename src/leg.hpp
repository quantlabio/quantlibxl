/* 
  Copyright (C) 2016 -2017 Jerry Jin
*/

#ifndef leg_h
#define leg_h
#include <nan.h>
#include <string>
#include <queue>
#include <utility>

#include "../quantlibxl.hpp"

#include <oh/objecthandler.hpp>

using namespace node;
using namespace v8;
using namespace std;


class LegWorker {
  public:
    string mObjectID;
    std::vector<double> mAmounts;
    std::vector<ObjectHandler::property_t> mDates;
    bool mToBeSorted;

    string mReturnValue;

    string mError;

    LegWorker(
      string ObjectID
,       std::vector<double> Amounts
,       std::vector<ObjectHandler::property_t> Dates
,       bool ToBeSorted
     )
      {
        mObjectID = ObjectID;
        mAmounts = Amounts;
        mDates = Dates;
        mToBeSorted = ToBeSorted;
      };

    void Execute();
};

class LegFromCapFloorWorker {
  public:
    string mObjectID;
    string mCapFloor;

    string mReturnValue;

    string mError;

    LegFromCapFloorWorker(
      string ObjectID
,       string CapFloor
     )
      {
        mObjectID = ObjectID;
        mCapFloor = CapFloor;
      };

    void Execute();
};

class LegFromSwapWorker {
  public:
    string mObjectID;
    string mSwap;
    long mLegNumber;

    string mReturnValue;

    string mError;

    LegFromSwapWorker(
      string ObjectID
,       string Swap
,       long LegNumber
     )
      {
        mObjectID = ObjectID;
        mSwap = Swap;
        mLegNumber = LegNumber;
      };

    void Execute();
};

class MultiPhaseLegWorker {
  public:
    string mObjectID;
    std::vector<string> mLegIDs;
    bool mToBeSorted;

    string mReturnValue;

    string mError;

    MultiPhaseLegWorker(
      string ObjectID
,       std::vector<string> LegIDs
,       bool ToBeSorted
     )
      {
        mObjectID = ObjectID;
        mLegIDs = LegIDs;
        mToBeSorted = ToBeSorted;
      };

    void Execute();
};

class InterestRateWorker {
  public:
    string mObjectID;
    double mRate;
    string mDayCounter;
    string mCompounding;
    string mFrequency;

    string mReturnValue;

    string mError;

    InterestRateWorker(
      string ObjectID
,       double Rate
,       string DayCounter
,       string Compounding
,       string Frequency
     )
      {
        mObjectID = ObjectID;
        mRate = Rate;
        mDayCounter = DayCounter;
        mCompounding = Compounding;
        mFrequency = Frequency;
      };

    void Execute();
};

class LegFlowAnalysisWorker {
  public:
    string mObjectID;
    ObjectHandler::property_t mAfterDate;

    std::vector< std::vector<string> > mReturnValue;

    string mError;

    LegFlowAnalysisWorker(
      string ObjectID
,       ObjectHandler::property_t AfterDate
     )
      {
        mObjectID = ObjectID;
        mAfterDate = AfterDate;
      };

    void Execute();
};

class LegSetCouponPricersWorker {
  public:
    string mObjectID;
    std::vector<string> mFloatingRateCouponPricer;

    string mError;

    LegSetCouponPricersWorker(
      string ObjectID
,       std::vector<string> FloatingRateCouponPricer
     )
      {
        mObjectID = ObjectID;
        mFloatingRateCouponPricer = FloatingRateCouponPricer;
      };

    void Execute();
};

class InterestRateRateWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    InterestRateRateWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class InterestRateDayCounterWorker {
  public:
    string mObjectID;

    string mReturnValue;

    string mError;

    InterestRateDayCounterWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class InterestRateCompoundingWorker {
  public:
    string mObjectID;

    string mReturnValue;

    string mError;

    InterestRateCompoundingWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class InterestRateFrequencyWorker {
  public:
    string mObjectID;

    string mReturnValue;

    string mError;

    InterestRateFrequencyWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class InterestRateDiscountFactorWorker {
  public:
    string mObjectID;
    ObjectHandler::property_t mStartDate;
    ObjectHandler::property_t mEndDate;
    ObjectHandler::property_t mRefPeriodStart;
    ObjectHandler::property_t mRefPeriodEnd;

    double mReturnValue;

    string mError;

    InterestRateDiscountFactorWorker(
      string ObjectID
,       ObjectHandler::property_t StartDate
,       ObjectHandler::property_t EndDate
,       ObjectHandler::property_t RefPeriodStart
,       ObjectHandler::property_t RefPeriodEnd
     )
      {
        mObjectID = ObjectID;
        mStartDate = StartDate;
        mEndDate = EndDate;
        mRefPeriodStart = RefPeriodStart;
        mRefPeriodEnd = RefPeriodEnd;
      };

    void Execute();
};

class InterestRateCompoundFactorWorker {
  public:
    string mObjectID;
    ObjectHandler::property_t mStartDate;
    ObjectHandler::property_t mEndDate;
    ObjectHandler::property_t mRefPeriodStart;
    ObjectHandler::property_t mRefPeriodEnd;

    double mReturnValue;

    string mError;

    InterestRateCompoundFactorWorker(
      string ObjectID
,       ObjectHandler::property_t StartDate
,       ObjectHandler::property_t EndDate
,       ObjectHandler::property_t RefPeriodStart
,       ObjectHandler::property_t RefPeriodEnd
     )
      {
        mObjectID = ObjectID;
        mStartDate = StartDate;
        mEndDate = EndDate;
        mRefPeriodStart = RefPeriodStart;
        mRefPeriodEnd = RefPeriodEnd;
      };

    void Execute();
};

class InterestRateEquivalentRateWorker {
  public:
    string mObjectID;
    string mDayCounter;
    string mCompounding;
    string mFrequency;
    ObjectHandler::property_t mStartDate;
    ObjectHandler::property_t mEndDate;
    ObjectHandler::property_t mRefPeriodStart;
    ObjectHandler::property_t mRefPeriodEnd;

    double mReturnValue;

    string mError;

    InterestRateEquivalentRateWorker(
      string ObjectID
,       string DayCounter
,       string Compounding
,       string Frequency
,       ObjectHandler::property_t StartDate
,       ObjectHandler::property_t EndDate
,       ObjectHandler::property_t RefPeriodStart
,       ObjectHandler::property_t RefPeriodEnd
     )
      {
        mObjectID = ObjectID;
        mDayCounter = DayCounter;
        mCompounding = Compounding;
        mFrequency = Frequency;
        mStartDate = StartDate;
        mEndDate = EndDate;
        mRefPeriodStart = RefPeriodStart;
        mRefPeriodEnd = RefPeriodEnd;
      };

    void Execute();
};

class LegStartDateWorker {
  public:
    string mObjectId;

    long mReturnValue;

    string mError;

    LegStartDateWorker(
      string ObjectId
     )
      {
        mObjectId = ObjectId;
      };

    void Execute();
};

class LegMaturityDateWorker {
  public:
    string mObjectId;

    long mReturnValue;

    string mError;

    LegMaturityDateWorker(
      string ObjectId
     )
      {
        mObjectId = ObjectId;
      };

    void Execute();
};

class LegIsExpiredWorker {
  public:
    string mObjectId;
    bool mIncludeSettlDate;
    ObjectHandler::property_t mSettlementDate;

    bool mReturnValue;

    string mError;

    LegIsExpiredWorker(
      string ObjectId
,       bool IncludeSettlDate
,       ObjectHandler::property_t SettlementDate
     )
      {
        mObjectId = ObjectId;
        mIncludeSettlDate = IncludeSettlDate;
        mSettlementDate = SettlementDate;
      };

    void Execute();
};

class LegPreviousCashFlowDateWorker {
  public:
    string mObjectId;
    bool mIncludeSettlDate;
    ObjectHandler::property_t mSettlementDate;

    long mReturnValue;

    string mError;

    LegPreviousCashFlowDateWorker(
      string ObjectId
,       bool IncludeSettlDate
,       ObjectHandler::property_t SettlementDate
     )
      {
        mObjectId = ObjectId;
        mIncludeSettlDate = IncludeSettlDate;
        mSettlementDate = SettlementDate;
      };

    void Execute();
};

class LegNextCashFlowDateWorker {
  public:
    string mObjectId;
    bool mIncludeSettlDate;
    ObjectHandler::property_t mSettlementDate;

    long mReturnValue;

    string mError;

    LegNextCashFlowDateWorker(
      string ObjectId
,       bool IncludeSettlDate
,       ObjectHandler::property_t SettlementDate
     )
      {
        mObjectId = ObjectId;
        mIncludeSettlDate = IncludeSettlDate;
        mSettlementDate = SettlementDate;
      };

    void Execute();
};

class LegPreviousCashFlowAmountWorker {
  public:
    string mObjectId;
    bool mIncludeSettlDate;
    ObjectHandler::property_t mSettlementDate;

    double mReturnValue;

    string mError;

    LegPreviousCashFlowAmountWorker(
      string ObjectId
,       bool IncludeSettlDate
,       ObjectHandler::property_t SettlementDate
     )
      {
        mObjectId = ObjectId;
        mIncludeSettlDate = IncludeSettlDate;
        mSettlementDate = SettlementDate;
      };

    void Execute();
};

class LegNextCashFlowAmountWorker {
  public:
    string mObjectId;
    bool mIncludeSettlDate;
    ObjectHandler::property_t mSettlementDate;

    double mReturnValue;

    string mError;

    LegNextCashFlowAmountWorker(
      string ObjectId
,       bool IncludeSettlDate
,       ObjectHandler::property_t SettlementDate
     )
      {
        mObjectId = ObjectId;
        mIncludeSettlDate = IncludeSettlDate;
        mSettlementDate = SettlementDate;
      };

    void Execute();
};

class LegPreviousCouponRateWorker {
  public:
    string mObjectId;
    bool mIncludeSettlDate;
    ObjectHandler::property_t mSettlementDate;

    double mReturnValue;

    string mError;

    LegPreviousCouponRateWorker(
      string ObjectId
,       bool IncludeSettlDate
,       ObjectHandler::property_t SettlementDate
     )
      {
        mObjectId = ObjectId;
        mIncludeSettlDate = IncludeSettlDate;
        mSettlementDate = SettlementDate;
      };

    void Execute();
};

class LegNextCouponRateWorker {
  public:
    string mObjectId;
    bool mIncludeSettlDate;
    ObjectHandler::property_t mSettlementDate;

    double mReturnValue;

    string mError;

    LegNextCouponRateWorker(
      string ObjectId
,       bool IncludeSettlDate
,       ObjectHandler::property_t SettlementDate
     )
      {
        mObjectId = ObjectId;
        mIncludeSettlDate = IncludeSettlDate;
        mSettlementDate = SettlementDate;
      };

    void Execute();
};

class LegNominalWorker {
  public:
    string mObjectId;
    bool mIncludeSettlDate;
    ObjectHandler::property_t mSettlementDate;

    double mReturnValue;

    string mError;

    LegNominalWorker(
      string ObjectId
,       bool IncludeSettlDate
,       ObjectHandler::property_t SettlementDate
     )
      {
        mObjectId = ObjectId;
        mIncludeSettlDate = IncludeSettlDate;
        mSettlementDate = SettlementDate;
      };

    void Execute();
};

class LegAccrualStartDateWorker {
  public:
    string mObjectId;
    bool mIncludeSettlDate;
    ObjectHandler::property_t mSettlementDate;

    long mReturnValue;

    string mError;

    LegAccrualStartDateWorker(
      string ObjectId
,       bool IncludeSettlDate
,       ObjectHandler::property_t SettlementDate
     )
      {
        mObjectId = ObjectId;
        mIncludeSettlDate = IncludeSettlDate;
        mSettlementDate = SettlementDate;
      };

    void Execute();
};

class LegAccrualEndDateWorker {
  public:
    string mObjectId;
    bool mIncludeSettlDate;
    ObjectHandler::property_t mSettlementDate;

    long mReturnValue;

    string mError;

    LegAccrualEndDateWorker(
      string ObjectId
,       bool IncludeSettlDate
,       ObjectHandler::property_t SettlementDate
     )
      {
        mObjectId = ObjectId;
        mIncludeSettlDate = IncludeSettlDate;
        mSettlementDate = SettlementDate;
      };

    void Execute();
};

class LegReferencePeriodStartWorker {
  public:
    string mObjectId;
    bool mIncludeSettlDate;
    ObjectHandler::property_t mSettlementDate;

    long mReturnValue;

    string mError;

    LegReferencePeriodStartWorker(
      string ObjectId
,       bool IncludeSettlDate
,       ObjectHandler::property_t SettlementDate
     )
      {
        mObjectId = ObjectId;
        mIncludeSettlDate = IncludeSettlDate;
        mSettlementDate = SettlementDate;
      };

    void Execute();
};

class LegReferencePeriodEndWorker {
  public:
    string mObjectId;
    bool mIncludeSettlDate;
    ObjectHandler::property_t mSettlementDate;

    long mReturnValue;

    string mError;

    LegReferencePeriodEndWorker(
      string ObjectId
,       bool IncludeSettlDate
,       ObjectHandler::property_t SettlementDate
     )
      {
        mObjectId = ObjectId;
        mIncludeSettlDate = IncludeSettlDate;
        mSettlementDate = SettlementDate;
      };

    void Execute();
};

class LegAccrualPeriodWorker {
  public:
    string mObjectId;
    bool mIncludeSettlDate;
    ObjectHandler::property_t mSettlementDate;

    double mReturnValue;

    string mError;

    LegAccrualPeriodWorker(
      string ObjectId
,       bool IncludeSettlDate
,       ObjectHandler::property_t SettlementDate
     )
      {
        mObjectId = ObjectId;
        mIncludeSettlDate = IncludeSettlDate;
        mSettlementDate = SettlementDate;
      };

    void Execute();
};

class LegAccrualDaysWorker {
  public:
    string mObjectId;
    bool mIncludeSettlDate;
    ObjectHandler::property_t mSettlementDate;

    long mReturnValue;

    string mError;

    LegAccrualDaysWorker(
      string ObjectId
,       bool IncludeSettlDate
,       ObjectHandler::property_t SettlementDate
     )
      {
        mObjectId = ObjectId;
        mIncludeSettlDate = IncludeSettlDate;
        mSettlementDate = SettlementDate;
      };

    void Execute();
};

class LegAccruedPeriodWorker {
  public:
    string mObjectId;
    bool mIncludeSettlDate;
    ObjectHandler::property_t mSettlementDate;

    double mReturnValue;

    string mError;

    LegAccruedPeriodWorker(
      string ObjectId
,       bool IncludeSettlDate
,       ObjectHandler::property_t SettlementDate
     )
      {
        mObjectId = ObjectId;
        mIncludeSettlDate = IncludeSettlDate;
        mSettlementDate = SettlementDate;
      };

    void Execute();
};

class LegAccruedDaysWorker {
  public:
    string mObjectId;
    bool mIncludeSettlDate;
    ObjectHandler::property_t mSettlementDate;

    long mReturnValue;

    string mError;

    LegAccruedDaysWorker(
      string ObjectId
,       bool IncludeSettlDate
,       ObjectHandler::property_t SettlementDate
     )
      {
        mObjectId = ObjectId;
        mIncludeSettlDate = IncludeSettlDate;
        mSettlementDate = SettlementDate;
      };

    void Execute();
};

class LegAccruedAmountWorker {
  public:
    string mObjectId;
    bool mIncludeSettlDate;
    ObjectHandler::property_t mSettlementDate;

    double mReturnValue;

    string mError;

    LegAccruedAmountWorker(
      string ObjectId
,       bool IncludeSettlDate
,       ObjectHandler::property_t SettlementDate
     )
      {
        mObjectId = ObjectId;
        mIncludeSettlDate = IncludeSettlDate;
        mSettlementDate = SettlementDate;
      };

    void Execute();
};

class LegNPVWorker {
  public:
    string mObjectId;
    string mDiscountCurve;
    bool mIncludeSettlDate;
    ObjectHandler::property_t mSettlementDate;
    ObjectHandler::property_t mNpvDate;

    double mReturnValue;

    string mError;

    LegNPVWorker(
      string ObjectId
,       string DiscountCurve
,       bool IncludeSettlDate
,       ObjectHandler::property_t SettlementDate
,       ObjectHandler::property_t NpvDate
     )
      {
        mObjectId = ObjectId;
        mDiscountCurve = DiscountCurve;
        mIncludeSettlDate = IncludeSettlDate;
        mSettlementDate = SettlementDate;
        mNpvDate = NpvDate;
      };

    void Execute();
};

class LegBPSWorker {
  public:
    string mObjectId;
    string mDiscountCurve;
    bool mIncludeSettlDate;
    ObjectHandler::property_t mSettlementDate;
    ObjectHandler::property_t mNpvDate;

    double mReturnValue;

    string mError;

    LegBPSWorker(
      string ObjectId
,       string DiscountCurve
,       bool IncludeSettlDate
,       ObjectHandler::property_t SettlementDate
,       ObjectHandler::property_t NpvDate
     )
      {
        mObjectId = ObjectId;
        mDiscountCurve = DiscountCurve;
        mIncludeSettlDate = IncludeSettlDate;
        mSettlementDate = SettlementDate;
        mNpvDate = NpvDate;
      };

    void Execute();
};

class LegAtmRateWorker {
  public:
    string mObjectId;
    string mDiscountCurve;
    bool mIncludeSettlDate;
    ObjectHandler::property_t mSettlementDate;
    ObjectHandler::property_t mNpvDate;
    double mNPV;

    double mReturnValue;

    string mError;

    LegAtmRateWorker(
      string ObjectId
,       string DiscountCurve
,       bool IncludeSettlDate
,       ObjectHandler::property_t SettlementDate
,       ObjectHandler::property_t NpvDate
,       double NPV
     )
      {
        mObjectId = ObjectId;
        mDiscountCurve = DiscountCurve;
        mIncludeSettlDate = IncludeSettlDate;
        mSettlementDate = SettlementDate;
        mNpvDate = NpvDate;
        mNPV = NPV;
      };

    void Execute();
};

class LegNPVFromYieldWorker {
  public:
    string mObjectId;
    double mYield;
    string mDayCounter;
    string mCompounding;
    string mFrequency;
    bool mIncludeSettlDate;
    ObjectHandler::property_t mSettlementDate;
    ObjectHandler::property_t mNpvDate;

    double mReturnValue;

    string mError;

    LegNPVFromYieldWorker(
      string ObjectId
,       double Yield
,       string DayCounter
,       string Compounding
,       string Frequency
,       bool IncludeSettlDate
,       ObjectHandler::property_t SettlementDate
,       ObjectHandler::property_t NpvDate
     )
      {
        mObjectId = ObjectId;
        mYield = Yield;
        mDayCounter = DayCounter;
        mCompounding = Compounding;
        mFrequency = Frequency;
        mIncludeSettlDate = IncludeSettlDate;
        mSettlementDate = SettlementDate;
        mNpvDate = NpvDate;
      };

    void Execute();
};

class LegBPSFromYieldWorker {
  public:
    string mObjectId;
    double mYield;
    string mDayCounter;
    string mCompounding;
    string mFrequency;
    bool mIncludeSettlDate;
    ObjectHandler::property_t mSettlementDate;
    ObjectHandler::property_t mNpvDate;

    double mReturnValue;

    string mError;

    LegBPSFromYieldWorker(
      string ObjectId
,       double Yield
,       string DayCounter
,       string Compounding
,       string Frequency
,       bool IncludeSettlDate
,       ObjectHandler::property_t SettlementDate
,       ObjectHandler::property_t NpvDate
     )
      {
        mObjectId = ObjectId;
        mYield = Yield;
        mDayCounter = DayCounter;
        mCompounding = Compounding;
        mFrequency = Frequency;
        mIncludeSettlDate = IncludeSettlDate;
        mSettlementDate = SettlementDate;
        mNpvDate = NpvDate;
      };

    void Execute();
};

class LegYieldWorker {
  public:
    string mObjectId;
    double mNPV;
    string mDayCounter;
    string mCompounding;
    string mFrequency;
    bool mIncludeSettlDate;
    ObjectHandler::property_t mSettlementDate;
    ObjectHandler::property_t mNpvDate;
    double mAccuracy;
    long mMaxIterations;
    double mGuess;

    double mReturnValue;

    string mError;

    LegYieldWorker(
      string ObjectId
,       double NPV
,       string DayCounter
,       string Compounding
,       string Frequency
,       bool IncludeSettlDate
,       ObjectHandler::property_t SettlementDate
,       ObjectHandler::property_t NpvDate
,       double Accuracy
,       long MaxIterations
,       double Guess
     )
      {
        mObjectId = ObjectId;
        mNPV = NPV;
        mDayCounter = DayCounter;
        mCompounding = Compounding;
        mFrequency = Frequency;
        mIncludeSettlDate = IncludeSettlDate;
        mSettlementDate = SettlementDate;
        mNpvDate = NpvDate;
        mAccuracy = Accuracy;
        mMaxIterations = MaxIterations;
        mGuess = Guess;
      };

    void Execute();
};

class LegDurationWorker {
  public:
    string mObjectId;
    double mYield;
    string mDayCounter;
    string mCompounding;
    string mFrequency;
    string mDurationType;
    bool mIncludeSettlDate;
    ObjectHandler::property_t mSettlementDate;
    ObjectHandler::property_t mNpvDate;

    double mReturnValue;

    string mError;

    LegDurationWorker(
      string ObjectId
,       double Yield
,       string DayCounter
,       string Compounding
,       string Frequency
,       string DurationType
,       bool IncludeSettlDate
,       ObjectHandler::property_t SettlementDate
,       ObjectHandler::property_t NpvDate
     )
      {
        mObjectId = ObjectId;
        mYield = Yield;
        mDayCounter = DayCounter;
        mCompounding = Compounding;
        mFrequency = Frequency;
        mDurationType = DurationType;
        mIncludeSettlDate = IncludeSettlDate;
        mSettlementDate = SettlementDate;
        mNpvDate = NpvDate;
      };

    void Execute();
};

class LegConvexityWorker {
  public:
    string mObjectId;
    double mYield;
    string mDayCounter;
    string mCompounding;
    string mFrequency;
    bool mIncludeSettlDate;
    ObjectHandler::property_t mSettlementDate;
    ObjectHandler::property_t mNpvDate;

    double mReturnValue;

    string mError;

    LegConvexityWorker(
      string ObjectId
,       double Yield
,       string DayCounter
,       string Compounding
,       string Frequency
,       bool IncludeSettlDate
,       ObjectHandler::property_t SettlementDate
,       ObjectHandler::property_t NpvDate
     )
      {
        mObjectId = ObjectId;
        mYield = Yield;
        mDayCounter = DayCounter;
        mCompounding = Compounding;
        mFrequency = Frequency;
        mIncludeSettlDate = IncludeSettlDate;
        mSettlementDate = SettlementDate;
        mNpvDate = NpvDate;
      };

    void Execute();
};

class LegBasisPointValueWorker {
  public:
    string mObjectId;
    double mYield;
    string mDayCounter;
    string mCompounding;
    string mFrequency;
    bool mIncludeSettlDate;
    ObjectHandler::property_t mSettlementDate;
    ObjectHandler::property_t mNpvDate;

    double mReturnValue;

    string mError;

    LegBasisPointValueWorker(
      string ObjectId
,       double Yield
,       string DayCounter
,       string Compounding
,       string Frequency
,       bool IncludeSettlDate
,       ObjectHandler::property_t SettlementDate
,       ObjectHandler::property_t NpvDate
     )
      {
        mObjectId = ObjectId;
        mYield = Yield;
        mDayCounter = DayCounter;
        mCompounding = Compounding;
        mFrequency = Frequency;
        mIncludeSettlDate = IncludeSettlDate;
        mSettlementDate = SettlementDate;
        mNpvDate = NpvDate;
      };

    void Execute();
};

class LegYieldValueBasisPointWorker {
  public:
    string mObjectId;
    double mYield;
    string mDayCounter;
    string mCompounding;
    string mFrequency;
    bool mIncludeSettlDate;
    ObjectHandler::property_t mSettlementDate;
    ObjectHandler::property_t mNpvDate;

    double mReturnValue;

    string mError;

    LegYieldValueBasisPointWorker(
      string ObjectId
,       double Yield
,       string DayCounter
,       string Compounding
,       string Frequency
,       bool IncludeSettlDate
,       ObjectHandler::property_t SettlementDate
,       ObjectHandler::property_t NpvDate
     )
      {
        mObjectId = ObjectId;
        mYield = Yield;
        mDayCounter = DayCounter;
        mCompounding = Compounding;
        mFrequency = Frequency;
        mIncludeSettlDate = IncludeSettlDate;
        mSettlementDate = SettlementDate;
        mNpvDate = NpvDate;
      };

    void Execute();
};

class LegNPVFromZSpreadWorker {
  public:
    string mObjectId;
    string mDiscountCurve;
    double mZSpread;
    string mDayCounter;
    string mCompounding;
    string mFrequency;
    bool mIncludeSettlDate;
    ObjectHandler::property_t mSettlementDate;
    ObjectHandler::property_t mNpvDate;

    double mReturnValue;

    string mError;

    LegNPVFromZSpreadWorker(
      string ObjectId
,       string DiscountCurve
,       double ZSpread
,       string DayCounter
,       string Compounding
,       string Frequency
,       bool IncludeSettlDate
,       ObjectHandler::property_t SettlementDate
,       ObjectHandler::property_t NpvDate
     )
      {
        mObjectId = ObjectId;
        mDiscountCurve = DiscountCurve;
        mZSpread = ZSpread;
        mDayCounter = DayCounter;
        mCompounding = Compounding;
        mFrequency = Frequency;
        mIncludeSettlDate = IncludeSettlDate;
        mSettlementDate = SettlementDate;
        mNpvDate = NpvDate;
      };

    void Execute();
};

class LegZSpreadWorker {
  public:
    string mObjectId;
    double mNPV;
    string mDiscountCurve;
    string mDayCounter;
    string mCompounding;
    string mFrequency;
    bool mIncludeSettlDate;
    ObjectHandler::property_t mSettlementDate;
    ObjectHandler::property_t mNpvDate;
    double mAccuracy;
    long mMaxIterations;
    double mGuess;

    double mReturnValue;

    string mError;

    LegZSpreadWorker(
      string ObjectId
,       double NPV
,       string DiscountCurve
,       string DayCounter
,       string Compounding
,       string Frequency
,       bool IncludeSettlDate
,       ObjectHandler::property_t SettlementDate
,       ObjectHandler::property_t NpvDate
,       double Accuracy
,       long MaxIterations
,       double Guess
     )
      {
        mObjectId = ObjectId;
        mNPV = NPV;
        mDiscountCurve = DiscountCurve;
        mDayCounter = DayCounter;
        mCompounding = Compounding;
        mFrequency = Frequency;
        mIncludeSettlDate = IncludeSettlDate;
        mSettlementDate = SettlementDate;
        mNpvDate = NpvDate;
        mAccuracy = Accuracy;
        mMaxIterations = MaxIterations;
        mGuess = Guess;
      };

    void Execute();
};

class InterestRateImpliedRateWorker {
  public:
    double mCompound;
    string mDayCounter;
    string mCompounding;
    string mFrequency;
    ObjectHandler::property_t mStartDate;
    ObjectHandler::property_t mEndDate;
    ObjectHandler::property_t mRefPeriodStart;
    ObjectHandler::property_t mRefPeriodEnd;

    double mReturnValue;

    string mError;

    InterestRateImpliedRateWorker(
      double Compound
,       string DayCounter
,       string Compounding
,       string Frequency
,       ObjectHandler::property_t StartDate
,       ObjectHandler::property_t EndDate
,       ObjectHandler::property_t RefPeriodStart
,       ObjectHandler::property_t RefPeriodEnd
     )
      {
        mCompound = Compound;
        mDayCounter = DayCounter;
        mCompounding = Compounding;
        mFrequency = Frequency;
        mStartDate = StartDate;
        mEndDate = EndDate;
        mRefPeriodStart = RefPeriodStart;
        mRefPeriodEnd = RefPeriodEnd;
      };

    void Execute();
};
 
#endif
