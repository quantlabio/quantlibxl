/* 
  Copyright (C) 2016 -2017 Jerry Jin
*/

#ifndef capfloor_h
#define capfloor_h
#include <nan.h>
#include <string>
#include <queue>
#include <utility>

#include "../quantlibxl.hpp"

#include <oh/objecthandler.hpp>

using namespace node;
using namespace v8;
using namespace std;


class CapFloorWorker {
  public:
    string mObjectID;
    string mOptionType;
    string mLegID;
    std::vector<double> mStrikes;

    string mReturnValue;

    string mError;

    CapFloorWorker(
      string ObjectID
,       string OptionType
,       string LegID
,       std::vector<double> Strikes
     )
      {
        mObjectID = ObjectID;
        mOptionType = OptionType;
        mLegID = LegID;
        mStrikes = Strikes;
      };

    void Execute();
};

class MakeCapFloorWorker {
  public:
    string mObjectID;
    string mOptionType;
    string mLength;
    string mIborIndex;
    double mStrike;
    string mForwardStart;
    string mPricingEngineID;

    string mReturnValue;

    string mError;

    MakeCapFloorWorker(
      string ObjectID
,       string OptionType
,       string Length
,       string IborIndex
,       double Strike
,       string ForwardStart
,       string PricingEngineID
     )
      {
        mObjectID = ObjectID;
        mOptionType = OptionType;
        mLength = Length;
        mIborIndex = IborIndex;
        mStrike = Strike;
        mForwardStart = ForwardStart;
        mPricingEngineID = PricingEngineID;
      };

    void Execute();
};

class CapFloorTypeWorker {
  public:
    string mObjectID;

    string mReturnValue;

    string mError;

    CapFloorTypeWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class CapFloorCapRatesWorker {
  public:
    string mObjectID;

    std::vector<double> mReturnValue;

    string mError;

    CapFloorCapRatesWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class CapFloorFloorRatesWorker {
  public:
    string mObjectID;

    std::vector<double> mReturnValue;

    string mError;

    CapFloorFloorRatesWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class CapFloorAtmRateWorker {
  public:
    string mObjectID;
    string mYieldCurve;

    double mReturnValue;

    string mError;

    CapFloorAtmRateWorker(
      string ObjectID
,       string YieldCurve
     )
      {
        mObjectID = ObjectID;
        mYieldCurve = YieldCurve;
      };

    void Execute();
};

class CapFloorStartDateWorker {
  public:
    string mObjectID;

    long mReturnValue;

    string mError;

    CapFloorStartDateWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class CapFloorMaturityDateWorker {
  public:
    string mObjectID;

    long mReturnValue;

    string mError;

    CapFloorMaturityDateWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class CapFloorImpliedVolatilityWorker {
  public:
    string mObjectID;
    double mPrice;
    ObjectHandler::property_t mYieldCurve;
    double mGuess;
    double mAccuracy;
    ObjectHandler::property_t mMaxIter;
    double mMinVol;
    double mMaxVol;
    string mVolatilityType;
    double mDisplacement;

    double mReturnValue;

    string mError;

    CapFloorImpliedVolatilityWorker(
      string ObjectID
,       double Price
,       ObjectHandler::property_t YieldCurve
,       double Guess
,       double Accuracy
,       ObjectHandler::property_t MaxIter
,       double MinVol
,       double MaxVol
,       string VolatilityType
,       double Displacement
     )
      {
        mObjectID = ObjectID;
        mPrice = Price;
        mYieldCurve = YieldCurve;
        mGuess = Guess;
        mAccuracy = Accuracy;
        mMaxIter = MaxIter;
        mMinVol = MinVol;
        mMaxVol = MaxVol;
        mVolatilityType = VolatilityType;
        mDisplacement = Displacement;
      };

    void Execute();
};

class CapFloorLegAnalysisWorker {
  public:
    string mObjectID;
    ObjectHandler::property_t mAfterDate;

    std::vector< std::vector<string> > mReturnValue;

    string mError;

    CapFloorLegAnalysisWorker(
      string ObjectID
,       ObjectHandler::property_t AfterDate
     )
      {
        mObjectID = ObjectID;
        mAfterDate = AfterDate;
      };

    void Execute();
};
 
#endif
