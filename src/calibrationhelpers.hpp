/* 
  Copyright (C) 2016 -2017 Jerry Jin
*/

#ifndef calibrationhelpers_h
#define calibrationhelpers_h
#include <nan.h>
#include <string>
#include <queue>
#include <utility>

#include "../quantlibxl.hpp"

#include <oh/objecthandler.hpp>

using namespace node;
using namespace v8;
using namespace std;


class SwaptionHelperWorker {
  public:
    string mObjectID;
    string mOptionTenor;
    string mLength;
    ObjectHandler::property_t mVolatility;
    string mIborIndex;
    string mFixedLegTenor;
    string mFixedLegDayCounter;
    string mFloatingLegDayCounter;
    ObjectHandler::property_t mYieldCurve;

    string mReturnValue;

    string mError;

    SwaptionHelperWorker(
      string ObjectID
,       string OptionTenor
,       string Length
,       ObjectHandler::property_t Volatility
,       string IborIndex
,       string FixedLegTenor
,       string FixedLegDayCounter
,       string FloatingLegDayCounter
,       ObjectHandler::property_t YieldCurve
     )
      {
        mObjectID = ObjectID;
        mOptionTenor = OptionTenor;
        mLength = Length;
        mVolatility = Volatility;
        mIborIndex = IborIndex;
        mFixedLegTenor = FixedLegTenor;
        mFixedLegDayCounter = FixedLegDayCounter;
        mFloatingLegDayCounter = FloatingLegDayCounter;
        mYieldCurve = YieldCurve;
      };

    void Execute();
};

class CalibrationHelperSetPricingEngineWorker {
  public:
    string mObjectID;
    string mPricingEngine;

    string mError;

    CalibrationHelperSetPricingEngineWorker(
      string ObjectID
,       string PricingEngine
     )
      {
        mObjectID = ObjectID;
        mPricingEngine = PricingEngine;
      };

    void Execute();
};

class CalibrationHelperImpliedVolatilityWorker {
  public:
    string mObjectID;
    double mTargetValue;
    double mAccuracy;
    long mMaxEvaluations;
    double mMinVol;
    double mMaxVol;

    double mReturnValue;

    string mError;

    CalibrationHelperImpliedVolatilityWorker(
      string ObjectID
,       double TargetValue
,       double Accuracy
,       long MaxEvaluations
,       double MinVol
,       double MaxVol
     )
      {
        mObjectID = ObjectID;
        mTargetValue = TargetValue;
        mAccuracy = Accuracy;
        mMaxEvaluations = MaxEvaluations;
        mMinVol = MinVol;
        mMaxVol = MaxVol;
      };

    void Execute();
};

class SwaptionHelperModelValueWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    SwaptionHelperModelValueWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class OneFactorAffineModelCalibrateWorker {
  public:
    string mObjectID;
    std::vector<string> mCalibrationHelpers;
    string mMethod;
    string mEndCriteria;
    string mConstraint;
    std::vector<double> mWeights;
    std::vector<bool> mFixedCoeff;

    string mError;

    OneFactorAffineModelCalibrateWorker(
      string ObjectID
,       std::vector<string> CalibrationHelpers
,       string Method
,       string EndCriteria
,       string Constraint
,       std::vector<double> Weights
,       std::vector<bool> FixedCoeff
     )
      {
        mObjectID = ObjectID;
        mCalibrationHelpers = CalibrationHelpers;
        mMethod = Method;
        mEndCriteria = EndCriteria;
        mConstraint = Constraint;
        mWeights = Weights;
        mFixedCoeff = FixedCoeff;
      };

    void Execute();
};

class ModelG2CalibrateWorker {
  public:
    string mObjectID;
    std::vector<string> mCalibrationHelpers;
    string mMethod;
    string mEndCriteria;
    string mConstraint;
    std::vector<double> mWeights;
    std::vector<bool> mFixedCoeff;

    string mError;

    ModelG2CalibrateWorker(
      string ObjectID
,       std::vector<string> CalibrationHelpers
,       string Method
,       string EndCriteria
,       string Constraint
,       std::vector<double> Weights
,       std::vector<bool> FixedCoeff
     )
      {
        mObjectID = ObjectID;
        mCalibrationHelpers = CalibrationHelpers;
        mMethod = Method;
        mEndCriteria = EndCriteria;
        mConstraint = Constraint;
        mWeights = Weights;
        mFixedCoeff = FixedCoeff;
      };

    void Execute();
};
 
#endif
