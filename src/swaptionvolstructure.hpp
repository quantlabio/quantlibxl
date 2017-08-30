/* 
  Copyright (C) 2016 -2017 Jerry Jin
*/

#ifndef swaptionvolstructure_h
#define swaptionvolstructure_h
#include <nan.h>
#include <string>
#include <queue>
#include <utility>

#include "../quantlibxl.hpp"

#include <oh/objecthandler.hpp>

using namespace node;
using namespace v8;
using namespace std;


class RelinkableHandleSwaptionVolatilityStructureWorker {
  public:
    string mObjectID;
    string mCurrentLink;

    string mReturnValue;

    string mError;

    RelinkableHandleSwaptionVolatilityStructureWorker(
      string ObjectID
,       string CurrentLink
     )
      {
        mObjectID = ObjectID;
        mCurrentLink = CurrentLink;
      };

    void Execute();
};

class ConstantSwaptionVolatilityWorker {
  public:
    string mObjectID;
    long mNDays;
    string mCalendar;
    string mBusinessDayConvention;
    ObjectHandler::property_t mVolatility;
    string mDayCounter;

    string mReturnValue;

    string mError;

    ConstantSwaptionVolatilityWorker(
      string ObjectID
,       long NDays
,       string Calendar
,       string BusinessDayConvention
,       ObjectHandler::property_t Volatility
,       string DayCounter
     )
      {
        mObjectID = ObjectID;
        mNDays = NDays;
        mCalendar = Calendar;
        mBusinessDayConvention = BusinessDayConvention;
        mVolatility = Volatility;
        mDayCounter = DayCounter;
      };

    void Execute();
};

class SpreadedSwaptionVolatilityWorker {
  public:
    string mObjectID;
    ObjectHandler::property_t mBaseVolStructure;
    ObjectHandler::property_t mSpread;

    string mReturnValue;

    string mError;

    SpreadedSwaptionVolatilityWorker(
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

class SwaptionVTSMatrixWorker {
  public:
    string mObjectID;
    string mCalendar;
    string mBusinessDayConvention;
    std::vector<ObjectHandler::property_t> mOptionTenors;
    std::vector<ObjectHandler::property_t> mSwapTenors;
    std::vector< std::vector<ObjectHandler::property_t> > mVolatilities;
    string mDayCounter;

    string mReturnValue;

    string mError;

    SwaptionVTSMatrixWorker(
      string ObjectID
,       string Calendar
,       string BusinessDayConvention
,       std::vector<ObjectHandler::property_t> OptionTenors
,       std::vector<ObjectHandler::property_t> SwapTenors
,       std::vector< std::vector<ObjectHandler::property_t> > Volatilities
,       string DayCounter
     )
      {
        mObjectID = ObjectID;
        mCalendar = Calendar;
        mBusinessDayConvention = BusinessDayConvention;
        mOptionTenors = OptionTenors;
        mSwapTenors = SwapTenors;
        mVolatilities = Volatilities;
        mDayCounter = DayCounter;
      };

    void Execute();
};

class SwaptionVolCube2Worker {
  public:
    string mObjectID;
    ObjectHandler::property_t mAtmVolStructure;
    std::vector<ObjectHandler::property_t> mOptionTenor;
    std::vector<ObjectHandler::property_t> mSwapTenor;
    std::vector<double> mStrikeSpreads;
    std::vector< std::vector<ObjectHandler::property_t> > mSpreadVols;
    string mSwapIndexBase;
    string mShortSwapIndexBase;
    bool mVegaWeightedSmileFit;

    string mReturnValue;

    string mError;

    SwaptionVolCube2Worker(
      string ObjectID
,       ObjectHandler::property_t AtmVolStructure
,       std::vector<ObjectHandler::property_t> OptionTenor
,       std::vector<ObjectHandler::property_t> SwapTenor
,       std::vector<double> StrikeSpreads
,       std::vector< std::vector<ObjectHandler::property_t> > SpreadVols
,       string SwapIndexBase
,       string ShortSwapIndexBase
,       bool VegaWeightedSmileFit
     )
      {
        mObjectID = ObjectID;
        mAtmVolStructure = AtmVolStructure;
        mOptionTenor = OptionTenor;
        mSwapTenor = SwapTenor;
        mStrikeSpreads = StrikeSpreads;
        mSpreadVols = SpreadVols;
        mSwapIndexBase = SwapIndexBase;
        mShortSwapIndexBase = ShortSwapIndexBase;
        mVegaWeightedSmileFit = VegaWeightedSmileFit;
      };

    void Execute();
};

class SwaptionVolCube1Worker {
  public:
    string mObjectID;
    ObjectHandler::property_t mAtmVolStructure;
    std::vector<ObjectHandler::property_t> mOptionTenors;
    std::vector<ObjectHandler::property_t> mSwapTenors;
    std::vector<double> mStrikeSpreads;
    std::vector< std::vector<ObjectHandler::property_t> > mSpreadVols;
    string mSwapIndexBase;
    string mShortSwapIndexBase;
    bool mVegaWeightedSmileFit;
    std::vector< std::vector<ObjectHandler::property_t> > mGuess;
    std::vector<bool> mIsFixed;
    bool mIsAtmCalibrated;
    string mEndCriteria;
    double mMaxErrorTol;
    string mOptMethod;

    string mReturnValue;

    string mError;

    SwaptionVolCube1Worker(
      string ObjectID
,       ObjectHandler::property_t AtmVolStructure
,       std::vector<ObjectHandler::property_t> OptionTenors
,       std::vector<ObjectHandler::property_t> SwapTenors
,       std::vector<double> StrikeSpreads
,       std::vector< std::vector<ObjectHandler::property_t> > SpreadVols
,       string SwapIndexBase
,       string ShortSwapIndexBase
,       bool VegaWeightedSmileFit
,       std::vector< std::vector<ObjectHandler::property_t> > Guess
,       std::vector<bool> IsFixed
,       bool IsAtmCalibrated
,       string EndCriteria
,       double MaxErrorTol
,       string OptMethod
     )
      {
        mObjectID = ObjectID;
        mAtmVolStructure = AtmVolStructure;
        mOptionTenors = OptionTenors;
        mSwapTenors = SwapTenors;
        mStrikeSpreads = StrikeSpreads;
        mSpreadVols = SpreadVols;
        mSwapIndexBase = SwapIndexBase;
        mShortSwapIndexBase = ShortSwapIndexBase;
        mVegaWeightedSmileFit = VegaWeightedSmileFit;
        mGuess = Guess;
        mIsFixed = IsFixed;
        mIsAtmCalibrated = IsAtmCalibrated;
        mEndCriteria = EndCriteria;
        mMaxErrorTol = MaxErrorTol;
        mOptMethod = OptMethod;
      };

    void Execute();
};

class SmileSectionByCubeWorker {
  public:
    string mObjectID;
    string mVolCube;
    ObjectHandler::property_t mOptionDate;
    string mSwapTenor;

    string mReturnValue;

    string mError;

    SmileSectionByCubeWorker(
      string ObjectID
,       string VolCube
,       ObjectHandler::property_t OptionDate
,       string SwapTenor
     )
      {
        mObjectID = ObjectID;
        mVolCube = VolCube;
        mOptionDate = OptionDate;
        mSwapTenor = SwapTenor;
      };

    void Execute();
};

class SmileSectionByCube2Worker {
  public:
    string mObjectID;
    string mVolCube;
    string mOptionDate;
    string mSwapTenor;

    string mReturnValue;

    string mError;

    SmileSectionByCube2Worker(
      string ObjectID
,       string VolCube
,       string OptionDate
,       string SwapTenor
     )
      {
        mObjectID = ObjectID;
        mVolCube = VolCube;
        mOptionDate = OptionDate;
        mSwapTenor = SwapTenor;
      };

    void Execute();
};

class SwaptionVTSVolatilityWorker {
  public:
    string mObjectID;
    ObjectHandler::property_t mOptionDate;
    string mSwapTenor;
    std::vector<double> mStrike;
    bool mAllowExtrapolation;

    std::vector<double> mReturnValue;

    string mError;

    SwaptionVTSVolatilityWorker(
      string ObjectID
,       ObjectHandler::property_t OptionDate
,       string SwapTenor
,       std::vector<double> Strike
,       bool AllowExtrapolation
     )
      {
        mObjectID = ObjectID;
        mOptionDate = OptionDate;
        mSwapTenor = SwapTenor;
        mStrike = Strike;
        mAllowExtrapolation = AllowExtrapolation;
      };

    void Execute();
};

class SwaptionVTSVolatility2Worker {
  public:
    string mObjectID;
    string mOptionTenor;
    string mSwapTenor;
    std::vector<double> mStrike;
    bool mAllowExtrapolation;

    std::vector<double> mReturnValue;

    string mError;

    SwaptionVTSVolatility2Worker(
      string ObjectID
,       string OptionTenor
,       string SwapTenor
,       std::vector<double> Strike
,       bool AllowExtrapolation
     )
      {
        mObjectID = ObjectID;
        mOptionTenor = OptionTenor;
        mSwapTenor = SwapTenor;
        mStrike = Strike;
        mAllowExtrapolation = AllowExtrapolation;
      };

    void Execute();
};

class SwaptionVTSBlackVarianceWorker {
  public:
    string mObjectID;
    std::vector<ObjectHandler::property_t> mOptionDate;
    string mSwapTenor;
    double mStrike;
    bool mAllowExtrapolation;

    std::vector<double> mReturnValue;

    string mError;

    SwaptionVTSBlackVarianceWorker(
      string ObjectID
,       std::vector<ObjectHandler::property_t> OptionDate
,       string SwapTenor
,       double Strike
,       bool AllowExtrapolation
     )
      {
        mObjectID = ObjectID;
        mOptionDate = OptionDate;
        mSwapTenor = SwapTenor;
        mStrike = Strike;
        mAllowExtrapolation = AllowExtrapolation;
      };

    void Execute();
};

class SwaptionVTSBlackVariance2Worker {
  public:
    string mObjectID;
    std::vector<ObjectHandler::property_t> mOptionTenor;
    string mSwapTenor;
    double mStrike;
    bool mAllowExtrapolation;

    std::vector<double> mReturnValue;

    string mError;

    SwaptionVTSBlackVariance2Worker(
      string ObjectID
,       std::vector<ObjectHandler::property_t> OptionTenor
,       string SwapTenor
,       double Strike
,       bool AllowExtrapolation
     )
      {
        mObjectID = ObjectID;
        mOptionTenor = OptionTenor;
        mSwapTenor = SwapTenor;
        mStrike = Strike;
        mAllowExtrapolation = AllowExtrapolation;
      };

    void Execute();
};

class SwaptionVTSMaxSwapTenorWorker {
  public:
    string mObjectID;

    string mReturnValue;

    string mError;

    SwaptionVTSMaxSwapTenorWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class SwaptionVTSBusinessDayConventionWorker {
  public:
    string mObjectID;

    string mReturnValue;

    string mError;

    SwaptionVTSBusinessDayConventionWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class SwaptionVTSOptionDateFromTenorWorker {
  public:
    string mObjectID;
    std::vector<ObjectHandler::property_t> mOptionTenor;

    std::vector<long> mReturnValue;

    string mError;

    SwaptionVTSOptionDateFromTenorWorker(
      string ObjectID
,       std::vector<ObjectHandler::property_t> OptionTenor
     )
      {
        mObjectID = ObjectID;
        mOptionTenor = OptionTenor;
      };

    void Execute();
};

class SwaptionVTSSwapLengthWorker {
  public:
    string mObjectID;
    std::vector<ObjectHandler::property_t> mSwapTenor;

    std::vector<double> mReturnValue;

    string mError;

    SwaptionVTSSwapLengthWorker(
      string ObjectID
,       std::vector<ObjectHandler::property_t> SwapTenor
     )
      {
        mObjectID = ObjectID;
        mSwapTenor = SwapTenor;
      };

    void Execute();
};

class SwaptionVTSSwapLength2Worker {
  public:
    string mObjectID;
    ObjectHandler::property_t mSwapStart;
    ObjectHandler::property_t mSwapEnd;

    double mReturnValue;

    string mError;

    SwaptionVTSSwapLength2Worker(
      string ObjectID
,       ObjectHandler::property_t SwapStart
,       ObjectHandler::property_t SwapEnd
     )
      {
        mObjectID = ObjectID;
        mSwapStart = SwapStart;
        mSwapEnd = SwapEnd;
      };

    void Execute();
};

class SwaptionVTSMatrixOptionDatesWorker {
  public:
    string mObjectID;

    std::vector<long> mReturnValue;

    string mError;

    SwaptionVTSMatrixOptionDatesWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class SwaptionVTSMatrixOptionTenorsWorker {
  public:
    string mObjectID;

    std::vector<string> mReturnValue;

    string mError;

    SwaptionVTSMatrixOptionTenorsWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class SwaptionVTSMatrixSwapTenorsWorker {
  public:
    string mObjectID;

    std::vector<string> mReturnValue;

    string mError;

    SwaptionVTSMatrixSwapTenorsWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class SwaptionVTSMatrixLocateWorker {
  public:
    string mObjectID;
    ObjectHandler::property_t mOptionDate;
    string mSwapTenor;

    std::vector<long> mReturnValue;

    string mError;

    SwaptionVTSMatrixLocateWorker(
      string ObjectID
,       ObjectHandler::property_t OptionDate
,       string SwapTenor
     )
      {
        mObjectID = ObjectID;
        mOptionDate = OptionDate;
        mSwapTenor = SwapTenor;
      };

    void Execute();
};

class SwaptionVTSatmStrikeWorker {
  public:
    string mObjectID;
    std::vector<ObjectHandler::property_t> mOptionDate;
    string mSwapTenor;

    std::vector<double> mReturnValue;

    string mError;

    SwaptionVTSatmStrikeWorker(
      string ObjectID
,       std::vector<ObjectHandler::property_t> OptionDate
,       string SwapTenor
     )
      {
        mObjectID = ObjectID;
        mOptionDate = OptionDate;
        mSwapTenor = SwapTenor;
      };

    void Execute();
};

class SwaptionVTSatmStrike2Worker {
  public:
    string mObjectID;
    std::vector<ObjectHandler::property_t> mOptionTenor;
    string mSwapTenor;

    std::vector<double> mReturnValue;

    string mError;

    SwaptionVTSatmStrike2Worker(
      string ObjectID
,       std::vector<ObjectHandler::property_t> OptionTenor
,       string SwapTenor
     )
      {
        mObjectID = ObjectID;
        mOptionTenor = OptionTenor;
        mSwapTenor = SwapTenor;
      };

    void Execute();
};

class SparseSabrParametersWorker {
  public:
    string mObjectID;

    std::vector< std::vector<string> > mReturnValue;

    string mError;

    SparseSabrParametersWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class DenseSabrParametersWorker {
  public:
    string mObjectID;

    std::vector< std::vector<string> > mReturnValue;

    string mError;

    DenseSabrParametersWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class MarketVolCubeWorker {
  public:
    string mObjectID;

    std::vector< std::vector<string> > mReturnValue;

    string mError;

    MarketVolCubeWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class VolCubeAtmCalibratedWorker {
  public:
    string mObjectID;

    std::vector< std::vector<string> > mReturnValue;

    string mError;

    VolCubeAtmCalibratedWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};
 
#endif
