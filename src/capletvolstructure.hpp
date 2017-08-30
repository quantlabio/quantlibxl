/* 
  Copyright (C) 2016 -2017 Jerry Jin
*/

#ifndef capletvolstructure_h
#define capletvolstructure_h
#include <nan.h>
#include <string>
#include <queue>
#include <utility>

#include "../quantlibxl.hpp"

#include <oh/objecthandler.hpp>

using namespace node;
using namespace v8;
using namespace std;


class RelinkableHandleOptionletVolatilityStructureWorker {
  public:
    string mObjectID;
    string mCurrentLink;

    string mReturnValue;

    string mError;

    RelinkableHandleOptionletVolatilityStructureWorker(
      string ObjectID
,       string CurrentLink
     )
      {
        mObjectID = ObjectID;
        mCurrentLink = CurrentLink;
      };

    void Execute();
};

class ConstantOptionletVolatilityWorker {
  public:
    string mObjectID;
    long mNDays;
    string mCalendar;
    string mBusinessDayConvention;
    ObjectHandler::property_t mVolatility;
    string mDayCounter;
    string mVolatilityType;
    double mDisplacement;

    string mReturnValue;

    string mError;

    ConstantOptionletVolatilityWorker(
      string ObjectID
,       long NDays
,       string Calendar
,       string BusinessDayConvention
,       ObjectHandler::property_t Volatility
,       string DayCounter
,       string VolatilityType
,       double Displacement
     )
      {
        mObjectID = ObjectID;
        mNDays = NDays;
        mCalendar = Calendar;
        mBusinessDayConvention = BusinessDayConvention;
        mVolatility = Volatility;
        mDayCounter = DayCounter;
        mVolatilityType = VolatilityType;
        mDisplacement = Displacement;
      };

    void Execute();
};

class SpreadedOptionletVolatilityWorker {
  public:
    string mObjectID;
    ObjectHandler::property_t mBaseVolStructure;
    ObjectHandler::property_t mSpread;

    string mReturnValue;

    string mError;

    SpreadedOptionletVolatilityWorker(
      string ObjectID
,       ObjectHandler::property_t BaseVolStructure
,       ObjectHandler::property_t Spread
     )
      {
        mObjectID = ObjectID;
        mBaseVolStructure = BaseVolStructure;
        mSpread = Spread;
      };

    void Execute();
};

class StrippedOptionletAdapterWorker {
  public:
    string mObjectID;
    string mStrippedOptionletBase;

    string mReturnValue;

    string mError;

    StrippedOptionletAdapterWorker(
      string ObjectID
,       string StrippedOptionletBase
     )
      {
        mObjectID = ObjectID;
        mStrippedOptionletBase = StrippedOptionletBase;
      };

    void Execute();
};

class StrippedOptionletWorker {
  public:
    string mObjectID;
    long mSettlementDays;
    string mCalendar;
    string mBusinessDayConvention;
    string mIborIndex;
    std::vector<ObjectHandler::property_t> mOptionletDates;
    std::vector<double> mStrikes;
    std::vector< std::vector<ObjectHandler::property_t> > mVolatilities;
    string mDayCounter;
    string mVolatilityType;
    double mDisplacement;

    string mReturnValue;

    string mError;

    StrippedOptionletWorker(
      string ObjectID
,       long SettlementDays
,       string Calendar
,       string BusinessDayConvention
,       string IborIndex
,       std::vector<ObjectHandler::property_t> OptionletDates
,       std::vector<double> Strikes
,       std::vector< std::vector<ObjectHandler::property_t> > Volatilities
,       string DayCounter
,       string VolatilityType
,       double Displacement
     )
      {
        mObjectID = ObjectID;
        mSettlementDays = SettlementDays;
        mCalendar = Calendar;
        mBusinessDayConvention = BusinessDayConvention;
        mIborIndex = IborIndex;
        mOptionletDates = OptionletDates;
        mStrikes = Strikes;
        mVolatilities = Volatilities;
        mDayCounter = DayCounter;
        mVolatilityType = VolatilityType;
        mDisplacement = Displacement;
      };

    void Execute();
};

class OptionletStripper1Worker {
  public:
    string mObjectID;
    string mTermVolSurface;
    string mIborIndex;
    double mSwitchStrike;
    double mAccuracy;
    ObjectHandler::property_t mMaxIter;
    string mVolatilityType;
    double mDisplacement;

    string mReturnValue;

    string mError;

    OptionletStripper1Worker(
      string ObjectID
,       string TermVolSurface
,       string IborIndex
,       double SwitchStrike
,       double Accuracy
,       ObjectHandler::property_t MaxIter
,       string VolatilityType
,       double Displacement
     )
      {
        mObjectID = ObjectID;
        mTermVolSurface = TermVolSurface;
        mIborIndex = IborIndex;
        mSwitchStrike = SwitchStrike;
        mAccuracy = Accuracy;
        mMaxIter = MaxIter;
        mVolatilityType = VolatilityType;
        mDisplacement = Displacement;
      };

    void Execute();
};

class OptionletStripper2Worker {
  public:
    string mObjectID;
    string mOptionletStripper1;
    ObjectHandler::property_t mTermVolCurve;

    string mReturnValue;

    string mError;

    OptionletStripper2Worker(
      string ObjectID
,       string OptionletStripper1
,       ObjectHandler::property_t TermVolCurve
     )
      {
        mObjectID = ObjectID;
        mOptionletStripper1 = OptionletStripper1;
        mTermVolCurve = TermVolCurve;
      };

    void Execute();
};

class CapFloorTermVolCurveWorker {
  public:
    string mObjectID;
    long mSettlementDays;
    string mCalendar;
    string mBusinessDayConvention;
    std::vector<ObjectHandler::property_t> mOptionTenors;
    std::vector<ObjectHandler::property_t> mVolatilities;
    string mDayCounter;

    string mReturnValue;

    string mError;

    CapFloorTermVolCurveWorker(
      string ObjectID
,       long SettlementDays
,       string Calendar
,       string BusinessDayConvention
,       std::vector<ObjectHandler::property_t> OptionTenors
,       std::vector<ObjectHandler::property_t> Volatilities
,       string DayCounter
     )
      {
        mObjectID = ObjectID;
        mSettlementDays = SettlementDays;
        mCalendar = Calendar;
        mBusinessDayConvention = BusinessDayConvention;
        mOptionTenors = OptionTenors;
        mVolatilities = Volatilities;
        mDayCounter = DayCounter;
      };

    void Execute();
};

class CapFloorTermVolSurfaceWorker {
  public:
    string mObjectID;
    long mSettlementDays;
    string mCalendar;
    string mBusinessDayConvention;
    std::vector<ObjectHandler::property_t> mOptionTenors;
    std::vector<double> mStrikes;
    std::vector< std::vector<ObjectHandler::property_t> > mVolatilities;
    string mDayCounter;

    string mReturnValue;

    string mError;

    CapFloorTermVolSurfaceWorker(
      string ObjectID
,       long SettlementDays
,       string Calendar
,       string BusinessDayConvention
,       std::vector<ObjectHandler::property_t> OptionTenors
,       std::vector<double> Strikes
,       std::vector< std::vector<ObjectHandler::property_t> > Volatilities
,       string DayCounter
     )
      {
        mObjectID = ObjectID;
        mSettlementDays = SettlementDays;
        mCalendar = Calendar;
        mBusinessDayConvention = BusinessDayConvention;
        mOptionTenors = OptionTenors;
        mStrikes = Strikes;
        mVolatilities = Volatilities;
        mDayCounter = DayCounter;
      };

    void Execute();
};

class OptionletVTSVolatilityWorker {
  public:
    string mObjectID;
    ObjectHandler::property_t mOptionDate;
    std::vector<double> mStrike;
    bool mAllowExtrapolation;

    std::vector<double> mReturnValue;

    string mError;

    OptionletVTSVolatilityWorker(
      string ObjectID
,       ObjectHandler::property_t OptionDate
,       std::vector<double> Strike
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

class OptionletVTSVolatility2Worker {
  public:
    string mObjectID;
    string mOptionTenor;
    std::vector<double> mStrike;
    bool mAllowExtrapolation;

    std::vector<double> mReturnValue;

    string mError;

    OptionletVTSVolatility2Worker(
      string ObjectID
,       string OptionTenor
,       std::vector<double> Strike
,       bool AllowExtrapolation
     )
      {
        mObjectID = ObjectID;
        mOptionTenor = OptionTenor;
        mStrike = Strike;
        mAllowExtrapolation = AllowExtrapolation;
      };

    void Execute();
};

class OptionletVTSBlackVarianceWorker {
  public:
    string mObjectID;
    std::vector<ObjectHandler::property_t> mOptionDate;
    double mStrike;
    bool mAllowExtrapolation;

    std::vector<double> mReturnValue;

    string mError;

    OptionletVTSBlackVarianceWorker(
      string ObjectID
,       std::vector<ObjectHandler::property_t> OptionDate
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

class OptionletVTSBlackVariance2Worker {
  public:
    string mObjectID;
    std::vector<ObjectHandler::property_t> mOptionTenor;
    double mStrike;
    bool mAllowExtrapolation;

    std::vector<double> mReturnValue;

    string mError;

    OptionletVTSBlackVariance2Worker(
      string ObjectID
,       std::vector<ObjectHandler::property_t> OptionTenor
,       double Strike
,       bool AllowExtrapolation
     )
      {
        mObjectID = ObjectID;
        mOptionTenor = OptionTenor;
        mStrike = Strike;
        mAllowExtrapolation = AllowExtrapolation;
      };

    void Execute();
};

class StrippedOptionletBaseStrikesWorker {
  public:
    string mObjectID;
    long mIndex;

    std::vector<double> mReturnValue;

    string mError;

    StrippedOptionletBaseStrikesWorker(
      string ObjectID
,       long Index
     )
      {
        mObjectID = ObjectID;
        mIndex = Index;
      };

    void Execute();
};

class StrippedOptionletBaseOptionletVolatilitiesWorker {
  public:
    string mObjectID;
    long mIndex;

    std::vector<double> mReturnValue;

    string mError;

    StrippedOptionletBaseOptionletVolatilitiesWorker(
      string ObjectID
,       long Index
     )
      {
        mObjectID = ObjectID;
        mIndex = Index;
      };

    void Execute();
};

class StrippedOptionletBaseOptionletFixingDatesWorker {
  public:
    string mObjectID;

    std::vector<long> mReturnValue;

    string mError;

    StrippedOptionletBaseOptionletFixingDatesWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class StrippedOptionletBaseOptionletFixingTimesWorker {
  public:
    string mObjectID;

    std::vector<double> mReturnValue;

    string mError;

    StrippedOptionletBaseOptionletFixingTimesWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class StrippedOptionletBaseAtmOptionletRatesWorker {
  public:
    string mObjectID;

    std::vector<double> mReturnValue;

    string mError;

    StrippedOptionletBaseAtmOptionletRatesWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class StrippedOptionletBaseDayCounterWorker {
  public:
    string mObjectID;

    string mReturnValue;

    string mError;

    StrippedOptionletBaseDayCounterWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class StrippedOptionletBaseCalendarWorker {
  public:
    string mObjectID;

    string mReturnValue;

    string mError;

    StrippedOptionletBaseCalendarWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class StrippedOptionletBaseSettlementDaysWorker {
  public:
    string mObjectID;

    long mReturnValue;

    string mError;

    StrippedOptionletBaseSettlementDaysWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class StrippedOptionletBaseBusinessDayConventionWorker {
  public:
    string mObjectID;

    string mReturnValue;

    string mError;

    StrippedOptionletBaseBusinessDayConventionWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class OptionletStripperOptionletFixingTenorsWorker {
  public:
    string mObjectID;

    std::vector<string> mReturnValue;

    string mError;

    OptionletStripperOptionletFixingTenorsWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class OptionletStripperOptionletPaymentDatesWorker {
  public:
    string mObjectID;

    std::vector<long> mReturnValue;

    string mError;

    OptionletStripperOptionletPaymentDatesWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class OptionletStripperOptionletAccrualPeriodsWorker {
  public:
    string mObjectID;

    std::vector<double> mReturnValue;

    string mError;

    OptionletStripperOptionletAccrualPeriodsWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class OptionletStripper1CapFloorPricesWorker {
  public:
    string mObjectID;

    std::vector< std::vector<double> > mReturnValue;

    string mError;

    OptionletStripper1CapFloorPricesWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class OptionletStripper1CapFloorVolatilitiesWorker {
  public:
    string mObjectID;

    std::vector< std::vector<double> > mReturnValue;

    string mError;

    OptionletStripper1CapFloorVolatilitiesWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class OptionletStripper1OptionletPricesWorker {
  public:
    string mObjectID;

    std::vector< std::vector<double> > mReturnValue;

    string mError;

    OptionletStripper1OptionletPricesWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class OptionletStripper1SwitchStrikeWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    OptionletStripper1SwitchStrikeWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class OptionletStripper2SpreadsVolWorker {
  public:
    string mObjectID;

    std::vector<double> mReturnValue;

    string mError;

    OptionletStripper2SpreadsVolWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class OptionletStripper2AtmCapFloorPricesWorker {
  public:
    string mObjectID;

    std::vector<double> mReturnValue;

    string mError;

    OptionletStripper2AtmCapFloorPricesWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class OptionletStripper2AtmCapFloorStrikesWorker {
  public:
    string mObjectID;

    std::vector<double> mReturnValue;

    string mError;

    OptionletStripper2AtmCapFloorStrikesWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class CapFloorTermVTSVolatilityWorker {
  public:
    string mObjectID;
    ObjectHandler::property_t mOptionDate;
    std::vector<double> mStrike;
    bool mAllowExtrapolation;

    std::vector<double> mReturnValue;

    string mError;

    CapFloorTermVTSVolatilityWorker(
      string ObjectID
,       ObjectHandler::property_t OptionDate
,       std::vector<double> Strike
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

class CapFloorTermVTSVolatility2Worker {
  public:
    string mObjectID;
    string mOptionTenor;
    std::vector<double> mStrike;
    bool mAllowExtrapolation;

    std::vector<double> mReturnValue;

    string mError;

    CapFloorTermVTSVolatility2Worker(
      string ObjectID
,       string OptionTenor
,       std::vector<double> Strike
,       bool AllowExtrapolation
     )
      {
        mObjectID = ObjectID;
        mOptionTenor = OptionTenor;
        mStrike = Strike;
        mAllowExtrapolation = AllowExtrapolation;
      };

    void Execute();
};

class CapFloorTermVolCurveOptionTenorsWorker {
  public:
    string mObjectID;

    std::vector<string> mReturnValue;

    string mError;

    CapFloorTermVolCurveOptionTenorsWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class CapFloorTermVolCurveOptionDatesWorker {
  public:
    string mObjectID;

    std::vector<long> mReturnValue;

    string mError;

    CapFloorTermVolCurveOptionDatesWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class CapFloorTermVolSurfaceOptionTenorsWorker {
  public:
    string mObjectID;

    std::vector<string> mReturnValue;

    string mError;

    CapFloorTermVolSurfaceOptionTenorsWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class CapFloorTermVolSurfaceOptionDatesWorker {
  public:
    string mObjectID;

    std::vector<long> mReturnValue;

    string mError;

    CapFloorTermVolSurfaceOptionDatesWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class CapFloorTermVolSurfaceStrikesWorker {
  public:
    string mObjectID;

    std::vector<double> mReturnValue;

    string mError;

    CapFloorTermVolSurfaceStrikesWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};
 
#endif
