/* 
  Copyright (C) 2016 -2017 Jerry Jin
*/

#ifndef smilesection_h
#define smilesection_h
#include <nan.h>
#include <string>
#include <queue>
#include <utility>

#include "../quantlibxl.hpp"

#include <oh/objecthandler.hpp>

using namespace node;
using namespace v8;
using namespace std;


class FlatSmileSectionWorker {
  public:
    string mObjectID;
    ObjectHandler::property_t mOptionDate;
    double mVolatility;
    string mDayCounter;
    ObjectHandler::property_t mRefDate;
    double mAtmValue;
    string mVolatilityType;
    double mDisplacement;

    string mReturnValue;

    string mError;

    FlatSmileSectionWorker(
      string ObjectID
,       ObjectHandler::property_t OptionDate
,       double Volatility
,       string DayCounter
,       ObjectHandler::property_t RefDate
,       double AtmValue
,       string VolatilityType
,       double Displacement
     )
      {
        mObjectID = ObjectID;
        mOptionDate = OptionDate;
        mVolatility = Volatility;
        mDayCounter = DayCounter;
        mRefDate = RefDate;
        mAtmValue = AtmValue;
        mVolatilityType = VolatilityType;
        mDisplacement = Displacement;
      };

    void Execute();
};

class SabrInterpolatedSmileSectionWorker {
  public:
    string mObjectID;
    ObjectHandler::property_t mOptionDate;
    double mForwardRate;
    std::vector<double> mStrike;
    bool mFloatingStrike;
    double mAtmVolatility;
    std::vector<double> mVolatilitySpreads;
    double mAlpha;
    double mBeta;
    double mNu;
    double mRho;
    bool mAlphaIsFixed;
    bool mBetaIsFixed;
    bool mNuIsFixed;
    bool mRhoIsFixed;
    bool mVegaWeighted;
    string mEndCriteria;
    string mMethod;
    string mDayCounter;

    string mReturnValue;

    string mError;

    SabrInterpolatedSmileSectionWorker(
      string ObjectID
,       ObjectHandler::property_t OptionDate
,       double ForwardRate
,       std::vector<double> Strike
,       bool FloatingStrike
,       double AtmVolatility
,       std::vector<double> VolatilitySpreads
,       double Alpha
,       double Beta
,       double Nu
,       double Rho
,       bool AlphaIsFixed
,       bool BetaIsFixed
,       bool NuIsFixed
,       bool RhoIsFixed
,       bool VegaWeighted
,       string EndCriteria
,       string Method
,       string DayCounter
     )
      {
        mObjectID = ObjectID;
        mOptionDate = OptionDate;
        mForwardRate = ForwardRate;
        mStrike = Strike;
        mFloatingStrike = FloatingStrike;
        mAtmVolatility = AtmVolatility;
        mVolatilitySpreads = VolatilitySpreads;
        mAlpha = Alpha;
        mBeta = Beta;
        mNu = Nu;
        mRho = Rho;
        mAlphaIsFixed = AlphaIsFixed;
        mBetaIsFixed = BetaIsFixed;
        mNuIsFixed = NuIsFixed;
        mRhoIsFixed = RhoIsFixed;
        mVegaWeighted = VegaWeighted;
        mEndCriteria = EndCriteria;
        mMethod = Method;
        mDayCounter = DayCounter;
      };

    void Execute();
};

class SabrInterpolatedSmileSection1Worker {
  public:
    string mObjectID;
    ObjectHandler::property_t mOptionDate;
    ObjectHandler::property_t mForwardRate;
    std::vector<double> mStrike;
    bool mFloatingStrike;
    ObjectHandler::property_t mAtmVolatility;
    std::vector<ObjectHandler::property_t> mVolatilitySpreads;
    double mAlpha;
    double mBeta;
    double mNu;
    double mRho;
    bool mAlphaIsFixed;
    bool mBetaIsFixed;
    bool mNuIsFixed;
    bool mRhoIsFixed;
    bool mVegaWeighted;
    string mEndCriteria;
    string mMethod;
    string mDayCounter;

    string mReturnValue;

    string mError;

    SabrInterpolatedSmileSection1Worker(
      string ObjectID
,       ObjectHandler::property_t OptionDate
,       ObjectHandler::property_t ForwardRate
,       std::vector<double> Strike
,       bool FloatingStrike
,       ObjectHandler::property_t AtmVolatility
,       std::vector<ObjectHandler::property_t> VolatilitySpreads
,       double Alpha
,       double Beta
,       double Nu
,       double Rho
,       bool AlphaIsFixed
,       bool BetaIsFixed
,       bool NuIsFixed
,       bool RhoIsFixed
,       bool VegaWeighted
,       string EndCriteria
,       string Method
,       string DayCounter
     )
      {
        mObjectID = ObjectID;
        mOptionDate = OptionDate;
        mForwardRate = ForwardRate;
        mStrike = Strike;
        mFloatingStrike = FloatingStrike;
        mAtmVolatility = AtmVolatility;
        mVolatilitySpreads = VolatilitySpreads;
        mAlpha = Alpha;
        mBeta = Beta;
        mNu = Nu;
        mRho = Rho;
        mAlphaIsFixed = AlphaIsFixed;
        mBetaIsFixed = BetaIsFixed;
        mNuIsFixed = NuIsFixed;
        mRhoIsFixed = RhoIsFixed;
        mVegaWeighted = VegaWeighted;
        mEndCriteria = EndCriteria;
        mMethod = Method;
        mDayCounter = DayCounter;
      };

    void Execute();
};

class SabrSmileSectionWorker {
  public:
    string mObjectID;
    double mOptionTime;
    std::vector<double> mStrikes;
    std::vector<ObjectHandler::property_t> mStdDevs;
    ObjectHandler::property_t mForward;
    double mAlpha;
    double mBeta;
    double mNu;
    double mRho;
    bool mAlphaIsFixed;
    bool mBetaIsFixed;
    bool mNuIsFixed;
    bool mRhoIsFixed;
    bool mVegaWeighted;
    string mEndCriteria;
    string mMethod;

    string mReturnValue;

    string mError;

    SabrSmileSectionWorker(
      string ObjectID
,       double OptionTime
,       std::vector<double> Strikes
,       std::vector<ObjectHandler::property_t> StdDevs
,       ObjectHandler::property_t Forward
,       double Alpha
,       double Beta
,       double Nu
,       double Rho
,       bool AlphaIsFixed
,       bool BetaIsFixed
,       bool NuIsFixed
,       bool RhoIsFixed
,       bool VegaWeighted
,       string EndCriteria
,       string Method
     )
      {
        mObjectID = ObjectID;
        mOptionTime = OptionTime;
        mStrikes = Strikes;
        mStdDevs = StdDevs;
        mForward = Forward;
        mAlpha = Alpha;
        mBeta = Beta;
        mNu = Nu;
        mRho = Rho;
        mAlphaIsFixed = AlphaIsFixed;
        mBetaIsFixed = BetaIsFixed;
        mNuIsFixed = NuIsFixed;
        mRhoIsFixed = RhoIsFixed;
        mVegaWeighted = VegaWeighted;
        mEndCriteria = EndCriteria;
        mMethod = Method;
      };

    void Execute();
};

class InterpolatedSmileSectionWorker {
  public:
    string mObjectID;
    ObjectHandler::property_t mOptionDate;
    std::vector<double> mStrikes;
    std::vector<ObjectHandler::property_t> mStdDevs;
    ObjectHandler::property_t mAtmLevel;
    string mDayCounter;
    string mVolatilityType;
    double mDisplacement;

    string mReturnValue;

    string mError;

    InterpolatedSmileSectionWorker(
      string ObjectID
,       ObjectHandler::property_t OptionDate
,       std::vector<double> Strikes
,       std::vector<ObjectHandler::property_t> StdDevs
,       ObjectHandler::property_t AtmLevel
,       string DayCounter
,       string VolatilityType
,       double Displacement
     )
      {
        mObjectID = ObjectID;
        mOptionDate = OptionDate;
        mStrikes = Strikes;
        mStdDevs = StdDevs;
        mAtmLevel = AtmLevel;
        mDayCounter = DayCounter;
        mVolatilityType = VolatilityType;
        mDisplacement = Displacement;
      };

    void Execute();
};

class SmileSectionFromSabrVolSurfaceWorker {
  public:
    string mObjectID;
    ObjectHandler::property_t mSabrVolSurface;
    double mOptionTime;

    string mReturnValue;

    string mError;

    SmileSectionFromSabrVolSurfaceWorker(
      string ObjectID
,       ObjectHandler::property_t SabrVolSurface
,       double OptionTime
     )
      {
        mObjectID = ObjectID;
        mSabrVolSurface = SabrVolSurface;
        mOptionTime = OptionTime;
      };

    void Execute();
};

class SmileSectionVolatilityWorker {
  public:
    string mObjectID;
    double mStrike;

    double mReturnValue;

    string mError;

    SmileSectionVolatilityWorker(
      string ObjectID
,       double Strike
     )
      {
        mObjectID = ObjectID;
        mStrike = Strike;
      };

    void Execute();
};

class SmileSectionVarianceWorker {
  public:
    string mObjectID;
    double mStrike;

    double mReturnValue;

    string mError;

    SmileSectionVarianceWorker(
      string ObjectID
,       double Strike
     )
      {
        mObjectID = ObjectID;
        mStrike = Strike;
      };

    void Execute();
};

class SmileSectionAtmLevelWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    SmileSectionAtmLevelWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class SmileSectionExerciseDateWorker {
  public:
    string mObjectID;

    long mReturnValue;

    string mError;

    SmileSectionExerciseDateWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class SmileSectionDayCounterWorker {
  public:
    string mObjectID;

    string mReturnValue;

    string mError;

    SmileSectionDayCounterWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class SabrInterpolatedSmileSectionAlphaWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    SabrInterpolatedSmileSectionAlphaWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class SabrInterpolatedSmileSectionBetaWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    SabrInterpolatedSmileSectionBetaWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class SabrInterpolatedSmileSectionNuWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    SabrInterpolatedSmileSectionNuWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class SabrInterpolatedSmileSectionRhoWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    SabrInterpolatedSmileSectionRhoWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class SabrInterpolatedSmileSectionErrorWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    SabrInterpolatedSmileSectionErrorWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class SabrInterpolatedSmileSectionMaxErrorWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    SabrInterpolatedSmileSectionMaxErrorWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class SabrInterpolatedSmileSectionEndCriteriaWorker {
  public:
    string mObjectID;

    string mReturnValue;

    string mError;

    SabrInterpolatedSmileSectionEndCriteriaWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};
 
#endif
