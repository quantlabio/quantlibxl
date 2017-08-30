/* 
  Copyright (C) 2016 -2017 Jerry Jin
*/

#ifndef swaption_h
#define swaption_h
#include <nan.h>
#include <string>
#include <queue>
#include <utility>

#include "../quantlibxl.hpp"

#include <oh/objecthandler.hpp>

using namespace node;
using namespace v8;
using namespace std;


class SwaptionWorker {
  public:
    string mObjectID;
    string mVanillaSwap;
    string mExercise;
    string mSettlementType;

    string mReturnValue;

    string mError;

    SwaptionWorker(
      string ObjectID
,       string VanillaSwap
,       string Exercise
,       string SettlementType
     )
      {
        mObjectID = ObjectID;
        mVanillaSwap = VanillaSwap;
        mExercise = Exercise;
        mSettlementType = SettlementType;
      };

    void Execute();
};

class MakeSwaptionWorker {
  public:
    string mObjectID;
    string mSwapIndex;
    string mOptionTenor;
    double mStrike;
    string mPricingEngineID;

    string mReturnValue;

    string mError;

    MakeSwaptionWorker(
      string ObjectID
,       string SwapIndex
,       string OptionTenor
,       double Strike
,       string PricingEngineID
     )
      {
        mObjectID = ObjectID;
        mSwapIndex = SwapIndex;
        mOptionTenor = OptionTenor;
        mStrike = Strike;
        mPricingEngineID = PricingEngineID;
      };

    void Execute();
};

class SwaptionTypeWorker {
  public:
    string mObjectID;

    string mReturnValue;

    string mError;

    SwaptionTypeWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class SwaptionSettlementTypeWorker {
  public:
    string mObjectID;

    string mReturnValue;

    string mError;

    SwaptionSettlementTypeWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class SwaptionImpliedVolatilityWorker {
  public:
    string mObjectID;
    double mPrice;
    ObjectHandler::property_t mYieldCurve;
    double mGuess;
    double mAccuracy;
    ObjectHandler::property_t mMaxIter;
    double mMinVol;
    double mMaxVol;
    double mDisplacement;

    double mReturnValue;

    string mError;

    SwaptionImpliedVolatilityWorker(
      string ObjectID
,       double Price
,       ObjectHandler::property_t YieldCurve
,       double Guess
,       double Accuracy
,       ObjectHandler::property_t MaxIter
,       double MinVol
,       double MaxVol
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
        mDisplacement = Displacement;
      };

    void Execute();
};
 
#endif
