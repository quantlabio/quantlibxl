/* 
  Copyright (C) 2016 -2017 Jerry Jin
*/

#ifndef volatilities_h
#define volatilities_h
#include <nan.h>
#include <string>
#include <queue>
#include <utility>

#include "../quantlibxl.hpp"

#include <oh/objecthandler.hpp>

using namespace node;
using namespace v8;
using namespace std;


class BlackConstantVolWorker {
  public:
    string mObjectID;
    ObjectHandler::property_t mSettlementDate;
    string mCalendar;
    double mVolatility;
    string mDayCounter;

    string mReturnValue;

    string mError;

    BlackConstantVolWorker(
      string ObjectID
,       ObjectHandler::property_t SettlementDate
,       string Calendar
,       double Volatility
,       string DayCounter
     )
      {
        mObjectID = ObjectID;
        mSettlementDate = SettlementDate;
        mCalendar = Calendar;
        mVolatility = Volatility;
        mDayCounter = DayCounter;
      };

    void Execute();
};

class BlackVarianceSurfaceWorker {
  public:
    string mObjectID;
    ObjectHandler::property_t mSettlementDate;
    string mCalendar;
    std::vector<ObjectHandler::property_t> mDates;
    std::vector<double> mStrikes;
    std::vector< std::vector<double> > mVolatilities;
    string mDayCounter;

    string mReturnValue;

    string mError;

    BlackVarianceSurfaceWorker(
      string ObjectID
,       ObjectHandler::property_t SettlementDate
,       string Calendar
,       std::vector<ObjectHandler::property_t> Dates
,       std::vector<double> Strikes
,       std::vector< std::vector<double> > Volatilities
,       string DayCounter
     )
      {
        mObjectID = ObjectID;
        mSettlementDate = SettlementDate;
        mCalendar = Calendar;
        mDates = Dates;
        mStrikes = Strikes;
        mVolatilities = Volatilities;
        mDayCounter = DayCounter;
      };

    void Execute();
};

class AbcdAtmVolCurveWorker {
  public:
    string mObjectID;
    ObjectHandler::property_t mSettlementDays;
    string mCalendar;
    std::vector<ObjectHandler::property_t> mOptionTenors;
    std::vector<ObjectHandler::property_t> mVolatilitiesQuotes;
    std::vector<bool> mInclusionInInterpolation;
    string mConvention;
    string mDayCounter;

    string mReturnValue;

    string mError;

    AbcdAtmVolCurveWorker(
      string ObjectID
,       ObjectHandler::property_t SettlementDays
,       string Calendar
,       std::vector<ObjectHandler::property_t> OptionTenors
,       std::vector<ObjectHandler::property_t> VolatilitiesQuotes
,       std::vector<bool> InclusionInInterpolation
,       string Convention
,       string DayCounter
     )
      {
        mObjectID = ObjectID;
        mSettlementDays = SettlementDays;
        mCalendar = Calendar;
        mOptionTenors = OptionTenors;
        mVolatilitiesQuotes = VolatilitiesQuotes;
        mInclusionInInterpolation = InclusionInInterpolation;
        mConvention = Convention;
        mDayCounter = DayCounter;
      };

    void Execute();
};

class SabrVolSurfaceWorker {
  public:
    string mObjectID;
    string mInterestRateIndex;
    ObjectHandler::property_t mBlackAtmVolCurve;
    std::vector<ObjectHandler::property_t> mOptionTenors;
    std::vector<double> mAtmRateSpreads;
    std::vector< std::vector<ObjectHandler::property_t> > mVolatilitiesQuotes;

    string mReturnValue;

    string mError;

    SabrVolSurfaceWorker(
      string ObjectID
,       string InterestRateIndex
,       ObjectHandler::property_t BlackAtmVolCurve
,       std::vector<ObjectHandler::property_t> OptionTenors
,       std::vector<double> AtmRateSpreads
,       std::vector< std::vector<ObjectHandler::property_t> > VolatilitiesQuotes
     )
      {
        mObjectID = ObjectID;
        mInterestRateIndex = InterestRateIndex;
        mBlackAtmVolCurve = BlackAtmVolCurve;
        mOptionTenors = OptionTenors;
        mAtmRateSpreads = AtmRateSpreads;
        mVolatilitiesQuotes = VolatilitiesQuotes;
      };

    void Execute();
};

class VolatilityTermStructureBusinessDayConventionWorker {
  public:
    string mObjectID;

    string mReturnValue;

    string mError;

    VolatilityTermStructureBusinessDayConventionWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class VolatilityTermStructureOptionDateFromTenorWorker {
  public:
    string mObjectID;
    string mTenor;

    long mReturnValue;

    string mError;

    VolatilityTermStructureOptionDateFromTenorWorker(
      string ObjectID
,       string Tenor
     )
      {
        mObjectID = ObjectID;
        mTenor = Tenor;
      };

    void Execute();
};

class VolatilityTermStructureMinStrikeWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    VolatilityTermStructureMinStrikeWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class VolatilityTermStructureMaxStrikeWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    VolatilityTermStructureMaxStrikeWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class BlackAtmVolCurveAtmVolWorker {
  public:
    string mObjectID;
    ObjectHandler::property_t mOptionDate;
    bool mAllowExtrapolation;

    double mReturnValue;

    string mError;

    BlackAtmVolCurveAtmVolWorker(
      string ObjectID
,       ObjectHandler::property_t OptionDate
,       bool AllowExtrapolation
     )
      {
        mObjectID = ObjectID;
        mOptionDate = OptionDate;
        mAllowExtrapolation = AllowExtrapolation;
      };

    void Execute();
};

class BlackAtmVolCurveAtmVol2Worker {
  public:
    string mObjectID;
    string mOptionTenor;
    bool mAllowExtrapolation;

    double mReturnValue;

    string mError;

    BlackAtmVolCurveAtmVol2Worker(
      string ObjectID
,       string OptionTenor
,       bool AllowExtrapolation
     )
      {
        mObjectID = ObjectID;
        mOptionTenor = OptionTenor;
        mAllowExtrapolation = AllowExtrapolation;
      };

    void Execute();
};

class BlackAtmVolCurveAtmVol3Worker {
  public:
    string mObjectID;
    double mOptionTime;
    bool mAllowExtrapolation;

    double mReturnValue;

    string mError;

    BlackAtmVolCurveAtmVol3Worker(
      string ObjectID
,       double OptionTime
,       bool AllowExtrapolation
     )
      {
        mObjectID = ObjectID;
        mOptionTime = OptionTime;
        mAllowExtrapolation = AllowExtrapolation;
      };

    void Execute();
};

class BlackAtmVolCurveAtmVarianceWorker {
  public:
    string mObjectID;
    ObjectHandler::property_t mOptionDate;
    bool mAllowExtrapolation;

    double mReturnValue;

    string mError;

    BlackAtmVolCurveAtmVarianceWorker(
      string ObjectID
,       ObjectHandler::property_t OptionDate
,       bool AllowExtrapolation
     )
      {
        mObjectID = ObjectID;
        mOptionDate = OptionDate;
        mAllowExtrapolation = AllowExtrapolation;
      };

    void Execute();
};

class BlackAtmVolCurveAtmVariance2Worker {
  public:
    string mObjectID;
    string mOptionTenor;
    bool mAllowExtrapolation;

    double mReturnValue;

    string mError;

    BlackAtmVolCurveAtmVariance2Worker(
      string ObjectID
,       string OptionTenor
,       bool AllowExtrapolation
     )
      {
        mObjectID = ObjectID;
        mOptionTenor = OptionTenor;
        mAllowExtrapolation = AllowExtrapolation;
      };

    void Execute();
};

class BlackAtmVolCurveAtmVariance3Worker {
  public:
    string mObjectID;
    double mOptionTime;
    bool mAllowExtrapolation;

    double mReturnValue;

    string mError;

    BlackAtmVolCurveAtmVariance3Worker(
      string ObjectID
,       double OptionTime
,       bool AllowExtrapolation
     )
      {
        mObjectID = ObjectID;
        mOptionTime = OptionTime;
        mAllowExtrapolation = AllowExtrapolation;
      };

    void Execute();
};

class BlackVolTermStructureBlackVolWorker {
  public:
    string mObjectID;
    ObjectHandler::property_t mOptionDate;
    double mStrike;
    bool mAllowExtrapolation;

    double mReturnValue;

    string mError;

    BlackVolTermStructureBlackVolWorker(
      string ObjectID
,       ObjectHandler::property_t OptionDate
,       double Strike
,       bool AllowExtrapolation
     )
      {
        mObjectID = ObjectID;
        mOptionDate = OptionDate;
        mStrike = Strike;
        mAllowExtrapolation = AllowExtrapolation;
      };

    void Execute();
};

class BlackVolTermStructureBlackVarianceWorker {
  public:
    string mObjectID;
    ObjectHandler::property_t mOptionDate;
    double mStrike;
    bool mAllowExtrapolation;

    double mReturnValue;

    string mError;

    BlackVolTermStructureBlackVarianceWorker(
      string ObjectID
,       ObjectHandler::property_t OptionDate
,       double Strike
,       bool AllowExtrapolation
     )
      {
        mObjectID = ObjectID;
        mOptionDate = OptionDate;
        mStrike = Strike;
        mAllowExtrapolation = AllowExtrapolation;
      };

    void Execute();
};

class BlackVolTermStructureBlackForwardVolWorker {
  public:
    string mObjectID;
    ObjectHandler::property_t mForwardDate;
    ObjectHandler::property_t mOptionDate;
    double mStrike;
    bool mAllowExtrapolation;

    double mReturnValue;

    string mError;

    BlackVolTermStructureBlackForwardVolWorker(
      string ObjectID
,       ObjectHandler::property_t ForwardDate
,       ObjectHandler::property_t OptionDate
,       double Strike
,       bool AllowExtrapolation
     )
      {
        mObjectID = ObjectID;
        mForwardDate = ForwardDate;
        mOptionDate = OptionDate;
        mStrike = Strike;
        mAllowExtrapolation = AllowExtrapolation;
      };

    void Execute();
};

class BlackVolTermStructureBlackForwardVarianceWorker {
  public:
    string mObjectID;
    ObjectHandler::property_t mForwardDate;
    ObjectHandler::property_t mOptionDate;
    double mStrike;
    bool mAllowExtrapolation;

    double mReturnValue;

    string mError;

    BlackVolTermStructureBlackForwardVarianceWorker(
      string ObjectID
,       ObjectHandler::property_t ForwardDate
,       ObjectHandler::property_t OptionDate
,       double Strike
,       bool AllowExtrapolation
     )
      {
        mObjectID = ObjectID;
        mForwardDate = ForwardDate;
        mOptionDate = OptionDate;
        mStrike = Strike;
        mAllowExtrapolation = AllowExtrapolation;
      };

    void Execute();
};

class AbcdAtmVolCurveOptionTenorsWorker {
  public:
    string mObjectID;

    std::vector<string> mReturnValue;

    string mError;

    AbcdAtmVolCurveOptionTenorsWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class AbcdAtmVolCurveOptionTenorsInInterpolationWorker {
  public:
    string mObjectID;

    std::vector<string> mReturnValue;

    string mError;

    AbcdAtmVolCurveOptionTenorsInInterpolationWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class AbcdAtmVolCurveOptionDatesWorker {
  public:
    string mObjectID;

    std::vector<long> mReturnValue;

    string mError;

    AbcdAtmVolCurveOptionDatesWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class AbcdAtmVolCurveOptionTimesWorker {
  public:
    string mObjectID;

    std::vector<double> mReturnValue;

    string mError;

    AbcdAtmVolCurveOptionTimesWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class AbcdAtmVolCurveRmsErrorWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    AbcdAtmVolCurveRmsErrorWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class AbcdAtmVolCurveMaxErrorWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    AbcdAtmVolCurveMaxErrorWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class AbcdAtmVolCurveAWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    AbcdAtmVolCurveAWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class AbcdAtmVolCurveBWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    AbcdAtmVolCurveBWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class AbcdAtmVolCurveCWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    AbcdAtmVolCurveCWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class AbcdAtmVolCurveDWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    AbcdAtmVolCurveDWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class AbcdAtmVolCurveKatOptionTenorsWorker {
  public:
    string mObjectID;

    std::vector<double> mReturnValue;

    string mError;

    AbcdAtmVolCurveKatOptionTenorsWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class AbcdAtmVolCurveKWorker {
  public:
    string mObjectID;
    double mTime;

    double mReturnValue;

    string mError;

    AbcdAtmVolCurveKWorker(
      string ObjectID
,       double Time
     )
      {
        mObjectID = ObjectID;
        mTime = Time;
      };

    void Execute();
};

class VolatilitySpreadsWorker {
  public:
    string mObjectID;
    ObjectHandler::property_t mOptionDate;

    std::vector<double> mReturnValue;

    string mError;

    VolatilitySpreadsWorker(
      string ObjectID
,       ObjectHandler::property_t OptionDate
     )
      {
        mObjectID = ObjectID;
        mOptionDate = OptionDate;
      };

    void Execute();
};

class VolatilitySpreads2Worker {
  public:
    string mObjectID;
    string mOptionTenor;

    std::vector<double> mReturnValue;

    string mError;

    VolatilitySpreads2Worker(
      string ObjectID
,       string OptionTenor
     )
      {
        mObjectID = ObjectID;
        mOptionTenor = OptionTenor;
      };

    void Execute();
};

class AtmCurveWorker {
  public:
    string mObjectID;

    string mReturnValue;

    string mError;

    AtmCurveWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class SabrVolatilityWorker {
  public:
    double mStrike;
    double mForward;
    double mExpTime;
    double mAlpha;
    double mBeta;
    double mNu;
    double mRho;

    double mReturnValue;

    string mError;

    SabrVolatilityWorker(
      double Strike
,       double Forward
,       double ExpTime
,       double Alpha
,       double Beta
,       double Nu
,       double Rho
     )
      {
        mStrike = Strike;
        mForward = Forward;
        mExpTime = ExpTime;
        mAlpha = Alpha;
        mBeta = Beta;
        mNu = Nu;
        mRho = Rho;
      };

    void Execute();
};
 
#endif
