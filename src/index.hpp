/* 
  Copyright (C) 2016 -2017 Jerry Jin
*/

#ifndef index_h
#define index_h
#include <nan.h>
#include <string>
#include <queue>
#include <utility>

#include "../quantlibxl.hpp"

#include <oh/objecthandler.hpp>

using namespace node;
using namespace v8;
using namespace std;


class IborIndexWorker {
  public:
    string mObjectID;
    string mFamilyName;
    string mTenor;
    ObjectHandler::property_t mFixingDays;
    string mCurrency;
    string mCalendar;
    string mBDayConvention;
    bool mEndOfMonth;
    string mDayCounter;
    ObjectHandler::property_t mFwdCurve;

    string mReturnValue;

    string mError;

    IborIndexWorker(
      string ObjectID
,       string FamilyName
,       string Tenor
,       ObjectHandler::property_t FixingDays
,       string Currency
,       string Calendar
,       string BDayConvention
,       bool EndOfMonth
,       string DayCounter
,       ObjectHandler::property_t FwdCurve
     )
      {
        mObjectID = ObjectID;
        mFamilyName = FamilyName;
        mTenor = Tenor;
        mFixingDays = FixingDays;
        mCurrency = Currency;
        mCalendar = Calendar;
        mBDayConvention = BDayConvention;
        mEndOfMonth = EndOfMonth;
        mDayCounter = DayCounter;
        mFwdCurve = FwdCurve;
      };

    void Execute();
};

class OvernightIndexWorker {
  public:
    string mObjectID;
    string mFamilyName;
    ObjectHandler::property_t mFixingDays;
    string mCurrency;
    string mCalendar;
    string mDayCounter;
    ObjectHandler::property_t mYieldCurve;

    string mReturnValue;

    string mError;

    OvernightIndexWorker(
      string ObjectID
,       string FamilyName
,       ObjectHandler::property_t FixingDays
,       string Currency
,       string Calendar
,       string DayCounter
,       ObjectHandler::property_t YieldCurve
     )
      {
        mObjectID = ObjectID;
        mFamilyName = FamilyName;
        mFixingDays = FixingDays;
        mCurrency = Currency;
        mCalendar = Calendar;
        mDayCounter = DayCounter;
        mYieldCurve = YieldCurve;
      };

    void Execute();
};

class EuriborWorker {
  public:
    string mObjectID;
    string mTenor;
    ObjectHandler::property_t mYieldCurve;

    string mReturnValue;

    string mError;

    EuriborWorker(
      string ObjectID
,       string Tenor
,       ObjectHandler::property_t YieldCurve
     )
      {
        mObjectID = ObjectID;
        mTenor = Tenor;
        mYieldCurve = YieldCurve;
      };

    void Execute();
};

class Euribor365Worker {
  public:
    string mObjectID;
    string mTenor;
    ObjectHandler::property_t mYieldCurve;

    string mReturnValue;

    string mError;

    Euribor365Worker(
      string ObjectID
,       string Tenor
,       ObjectHandler::property_t YieldCurve
     )
      {
        mObjectID = ObjectID;
        mTenor = Tenor;
        mYieldCurve = YieldCurve;
      };

    void Execute();
};

class EoniaWorker {
  public:
    string mObjectID;
    ObjectHandler::property_t mYieldCurve;

    string mReturnValue;

    string mError;

    EoniaWorker(
      string ObjectID
,       ObjectHandler::property_t YieldCurve
     )
      {
        mObjectID = ObjectID;
        mYieldCurve = YieldCurve;
      };

    void Execute();
};

class LiborWorker {
  public:
    string mObjectID;
    string mCurrency;
    string mTenor;
    ObjectHandler::property_t mYieldCurve;

    string mReturnValue;

    string mError;

    LiborWorker(
      string ObjectID
,       string Currency
,       string Tenor
,       ObjectHandler::property_t YieldCurve
     )
      {
        mObjectID = ObjectID;
        mCurrency = Currency;
        mTenor = Tenor;
        mYieldCurve = YieldCurve;
      };

    void Execute();
};

class SoniaWorker {
  public:
    string mObjectID;
    ObjectHandler::property_t mYieldCurve;

    string mReturnValue;

    string mError;

    SoniaWorker(
      string ObjectID
,       ObjectHandler::property_t YieldCurve
     )
      {
        mObjectID = ObjectID;
        mYieldCurve = YieldCurve;
      };

    void Execute();
};

class SwapIndexWorker {
  public:
    string mObjectID;
    string mFamilyName;
    string mTenor;
    ObjectHandler::property_t mFixingDays;
    string mCurrency;
    string mCalendar;
    string mFixedLegTenor;
    string mFixedLegBDC;
    string mFixedLegDayCounter;
    string mIborIndex;
    ObjectHandler::property_t mDiscCurve;

    string mReturnValue;

    string mError;

    SwapIndexWorker(
      string ObjectID
,       string FamilyName
,       string Tenor
,       ObjectHandler::property_t FixingDays
,       string Currency
,       string Calendar
,       string FixedLegTenor
,       string FixedLegBDC
,       string FixedLegDayCounter
,       string IborIndex
,       ObjectHandler::property_t DiscCurve
     )
      {
        mObjectID = ObjectID;
        mFamilyName = FamilyName;
        mTenor = Tenor;
        mFixingDays = FixingDays;
        mCurrency = Currency;
        mCalendar = Calendar;
        mFixedLegTenor = FixedLegTenor;
        mFixedLegBDC = FixedLegBDC;
        mFixedLegDayCounter = FixedLegDayCounter;
        mIborIndex = IborIndex;
        mDiscCurve = DiscCurve;
      };

    void Execute();
};

class EuriborSwapWorker {
  public:
    string mObjectID;
    string mFixingType;
    string mTenor;
    ObjectHandler::property_t mFwdCurve;
    ObjectHandler::property_t mDiscCurve;

    string mReturnValue;

    string mError;

    EuriborSwapWorker(
      string ObjectID
,       string FixingType
,       string Tenor
,       ObjectHandler::property_t FwdCurve
,       ObjectHandler::property_t DiscCurve
     )
      {
        mObjectID = ObjectID;
        mFixingType = FixingType;
        mTenor = Tenor;
        mFwdCurve = FwdCurve;
        mDiscCurve = DiscCurve;
      };

    void Execute();
};

class LiborSwapWorker {
  public:
    string mObjectID;
    string mCurrency;
    string mFixingType;
    string mTenor;
    ObjectHandler::property_t mFwdCurve;
    ObjectHandler::property_t mDiscCurve;

    string mReturnValue;

    string mError;

    LiborSwapWorker(
      string ObjectID
,       string Currency
,       string FixingType
,       string Tenor
,       ObjectHandler::property_t FwdCurve
,       ObjectHandler::property_t DiscCurve
     )
      {
        mObjectID = ObjectID;
        mCurrency = Currency;
        mFixingType = FixingType;
        mTenor = Tenor;
        mFwdCurve = FwdCurve;
        mDiscCurve = DiscCurve;
      };

    void Execute();
};

class EuriborSwapIsdaFixAWorker {
  public:
    string mObjectID;
    string mTenor;
    ObjectHandler::property_t mFwdCurve;
    ObjectHandler::property_t mDiscCurve;

    string mReturnValue;

    string mError;

    EuriborSwapIsdaFixAWorker(
      string ObjectID
,       string Tenor
,       ObjectHandler::property_t FwdCurve
,       ObjectHandler::property_t DiscCurve
     )
      {
        mObjectID = ObjectID;
        mTenor = Tenor;
        mFwdCurve = FwdCurve;
        mDiscCurve = DiscCurve;
      };

    void Execute();
};

class BMAIndexWorker {
  public:
    string mObjectID;
    ObjectHandler::property_t mYieldCurve;

    string mReturnValue;

    string mError;

    BMAIndexWorker(
      string ObjectID
,       ObjectHandler::property_t YieldCurve
     )
      {
        mObjectID = ObjectID;
        mYieldCurve = YieldCurve;
      };

    void Execute();
};

class ProxyIborWorker {
  public:
    string mObjectID;
    string mFamilyName;
    string mTenor;
    ObjectHandler::property_t mFixingDays;
    string mCurrency;
    string mCalendar;
    string mBDayConvention;
    bool mEndOfMonth;
    string mDayCounter;
    ObjectHandler::property_t mGearing;
    string mIborIndex;
    ObjectHandler::property_t mSpread;

    string mReturnValue;

    string mError;

    ProxyIborWorker(
      string ObjectID
,       string FamilyName
,       string Tenor
,       ObjectHandler::property_t FixingDays
,       string Currency
,       string Calendar
,       string BDayConvention
,       bool EndOfMonth
,       string DayCounter
,       ObjectHandler::property_t Gearing
,       string IborIndex
,       ObjectHandler::property_t Spread
     )
      {
        mObjectID = ObjectID;
        mFamilyName = FamilyName;
        mTenor = Tenor;
        mFixingDays = FixingDays;
        mCurrency = Currency;
        mCalendar = Calendar;
        mBDayConvention = BDayConvention;
        mEndOfMonth = EndOfMonth;
        mDayCounter = DayCounter;
        mGearing = Gearing;
        mIborIndex = IborIndex;
        mSpread = Spread;
      };

    void Execute();
};

class IndexNameWorker {
  public:
    string mObjectID;

    string mReturnValue;

    string mError;

    IndexNameWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class IndexFixingCalendarWorker {
  public:
    string mObjectID;

    string mReturnValue;

    string mError;

    IndexFixingCalendarWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class IndexIsValidFixingDateWorker {
  public:
    string mObjectID;
    std::vector<ObjectHandler::property_t> mFixingDate;

    std::vector<bool> mReturnValue;

    string mError;

    IndexIsValidFixingDateWorker(
      string ObjectID
,       std::vector<ObjectHandler::property_t> FixingDate
     )
      {
        mObjectID = ObjectID;
        mFixingDate = FixingDate;
      };

    void Execute();
};

class IndexFixingWorker {
  public:
    string mObjectID;
    std::vector<ObjectHandler::property_t> mFixingDate;
    bool mForecastToday;

    std::vector<double> mReturnValue;

    string mError;

    IndexFixingWorker(
      string ObjectID
,       std::vector<ObjectHandler::property_t> FixingDate
,       bool ForecastToday
     )
      {
        mObjectID = ObjectID;
        mFixingDate = FixingDate;
        mForecastToday = ForecastToday;
      };

    void Execute();
};

class IndexAddFixingsWorker {
  public:
    string mObjectID;
    std::vector<ObjectHandler::property_t> mFixingDates;
    std::vector<double> mFixingValues;
    bool mForceOverwrite;

    string mError;

    IndexAddFixingsWorker(
      string ObjectID
,       std::vector<ObjectHandler::property_t> FixingDates
,       std::vector<double> FixingValues
,       bool ForceOverwrite
     )
      {
        mObjectID = ObjectID;
        mFixingDates = FixingDates;
        mFixingValues = FixingValues;
        mForceOverwrite = ForceOverwrite;
      };

    void Execute();
};

class IndexAddFixings2Worker {
  public:
    string mObjectID;
    std::vector<string> mTimeSeriesID;
    bool mForceOverwrite;

    string mError;

    IndexAddFixings2Worker(
      string ObjectID
,       std::vector<string> TimeSeriesID
,       bool ForceOverwrite
     )
      {
        mObjectID = ObjectID;
        mTimeSeriesID = TimeSeriesID;
        mForceOverwrite = ForceOverwrite;
      };

    void Execute();
};

class IndexClearFixingsWorker {
  public:
    string mObjectID;

    string mError;

    IndexClearFixingsWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class InterestRateIndexFamilyNameWorker {
  public:
    string mObjectID;

    string mReturnValue;

    string mError;

    InterestRateIndexFamilyNameWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class InterestRateIndexTenorWorker {
  public:
    string mObjectID;

    string mReturnValue;

    string mError;

    InterestRateIndexTenorWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class InterestRateIndexFixingDaysWorker {
  public:
    string mObjectID;

    long mReturnValue;

    string mError;

    InterestRateIndexFixingDaysWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class InterestRateIndexCurrencyWorker {
  public:
    string mObjectID;

    string mReturnValue;

    string mError;

    InterestRateIndexCurrencyWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class InterestRateIndexDayCounterWorker {
  public:
    string mObjectID;

    string mReturnValue;

    string mError;

    InterestRateIndexDayCounterWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class InterestRateIndexValueDateWorker {
  public:
    string mObjectID;
    std::vector<ObjectHandler::property_t> mFixingDate;

    std::vector<long> mReturnValue;

    string mError;

    InterestRateIndexValueDateWorker(
      string ObjectID
,       std::vector<ObjectHandler::property_t> FixingDate
     )
      {
        mObjectID = ObjectID;
        mFixingDate = FixingDate;
      };

    void Execute();
};

class InterestRateIndexFixingDateWorker {
  public:
    string mObjectID;
    std::vector<ObjectHandler::property_t> mValueDate;

    std::vector<long> mReturnValue;

    string mError;

    InterestRateIndexFixingDateWorker(
      string ObjectID
,       std::vector<ObjectHandler::property_t> ValueDate
     )
      {
        mObjectID = ObjectID;
        mValueDate = ValueDate;
      };

    void Execute();
};

class InterestRateIndexMaturityWorker {
  public:
    string mObjectID;
    std::vector<ObjectHandler::property_t> mValueDate;

    std::vector<long> mReturnValue;

    string mError;

    InterestRateIndexMaturityWorker(
      string ObjectID
,       std::vector<ObjectHandler::property_t> ValueDate
     )
      {
        mObjectID = ObjectID;
        mValueDate = ValueDate;
      };

    void Execute();
};

class IborIndexBusinessDayConvWorker {
  public:
    string mObjectID;

    string mReturnValue;

    string mError;

    IborIndexBusinessDayConvWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class IborIndexEndOfMonthWorker {
  public:
    string mObjectID;

    bool mReturnValue;

    string mError;

    IborIndexEndOfMonthWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class SwapIndexFixedLegTenorWorker {
  public:
    string mObjectID;

    string mReturnValue;

    string mError;

    SwapIndexFixedLegTenorWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class SwapIndexFixedLegBDCWorker {
  public:
    string mObjectID;

    string mReturnValue;

    string mError;

    SwapIndexFixedLegBDCWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};
 
#endif
