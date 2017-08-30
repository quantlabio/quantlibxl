/* 
  Copyright (C) 2016 -2017 Jerry Jin
*/

#ifndef interpolation_h
#define interpolation_h
#include <nan.h>
#include <string>
#include <queue>
#include <utility>

#include "../quantlibxl.hpp"

#include <oh/objecthandler.hpp>

using namespace node;
using namespace v8;
using namespace std;


class InterpolationWorker {
  public:
    string mObjectID;
    string mInterpolationType;
    std::vector<double> mXArray;
    std::vector<ObjectHandler::property_t> mYArray;

    string mReturnValue;

    string mError;

    InterpolationWorker(
      string ObjectID
,       string InterpolationType
,       std::vector<double> XArray
,       std::vector<ObjectHandler::property_t> YArray
     )
      {
        mObjectID = ObjectID;
        mInterpolationType = InterpolationType;
        mXArray = XArray;
        mYArray = YArray;
      };

    void Execute();
};

class MixedLinearCubicInterpolationWorker {
  public:
    string mObjectID;
    std::vector<double> mXArray;
    std::vector<ObjectHandler::property_t> mYArray;
    long mSwitchIndex;
    string mDerApprox;
    bool mMonotonic;
    string mLeftConditionType;
    double mLeftConditionValue;
    string mRightConditionType;
    double mRightConditionValue;

    string mReturnValue;

    string mError;

    MixedLinearCubicInterpolationWorker(
      string ObjectID
,       std::vector<double> XArray
,       std::vector<ObjectHandler::property_t> YArray
,       long SwitchIndex
,       string DerApprox
,       bool Monotonic
,       string LeftConditionType
,       double LeftConditionValue
,       string RightConditionType
,       double RightConditionValue
     )
      {
        mObjectID = ObjectID;
        mXArray = XArray;
        mYArray = YArray;
        mSwitchIndex = SwitchIndex;
        mDerApprox = DerApprox;
        mMonotonic = Monotonic;
        mLeftConditionType = LeftConditionType;
        mLeftConditionValue = LeftConditionValue;
        mRightConditionType = RightConditionType;
        mRightConditionValue = RightConditionValue;
      };

    void Execute();
};

class CubicInterpolationWorker {
  public:
    string mObjectID;
    std::vector<double> mXArray;
    std::vector<ObjectHandler::property_t> mYArray;
    string mDerApprox;
    bool mMonotonic;
    string mLeftConditionType;
    double mLeftConditionValue;
    string mRightConditionType;
    double mRightConditionValue;

    string mReturnValue;

    string mError;

    CubicInterpolationWorker(
      string ObjectID
,       std::vector<double> XArray
,       std::vector<ObjectHandler::property_t> YArray
,       string DerApprox
,       bool Monotonic
,       string LeftConditionType
,       double LeftConditionValue
,       string RightConditionType
,       double RightConditionValue
     )
      {
        mObjectID = ObjectID;
        mXArray = XArray;
        mYArray = YArray;
        mDerApprox = DerApprox;
        mMonotonic = Monotonic;
        mLeftConditionType = LeftConditionType;
        mLeftConditionValue = LeftConditionValue;
        mRightConditionType = RightConditionType;
        mRightConditionValue = RightConditionValue;
      };

    void Execute();
};

class AbcdInterpolationWorker {
  public:
    string mObjectID;
    std::vector<double> mXArray;
    std::vector<ObjectHandler::property_t> mYArray;
    double mA;
    double mB;
    double mC;
    double mD;
    bool mAIsFixed;
    bool mBIsFixed;
    bool mCIsFixed;
    bool mDIsFixed;
    bool mVegaWeighted;
    string mEndCriteria;
    string mOptimizationMeth;

    string mReturnValue;

    string mError;

    AbcdInterpolationWorker(
      string ObjectID
,       std::vector<double> XArray
,       std::vector<ObjectHandler::property_t> YArray
,       double A
,       double B
,       double C
,       double D
,       bool AIsFixed
,       bool BIsFixed
,       bool CIsFixed
,       bool DIsFixed
,       bool VegaWeighted
,       string EndCriteria
,       string OptimizationMeth
     )
      {
        mObjectID = ObjectID;
        mXArray = XArray;
        mYArray = YArray;
        mA = A;
        mB = B;
        mC = C;
        mD = D;
        mAIsFixed = AIsFixed;
        mBIsFixed = BIsFixed;
        mCIsFixed = CIsFixed;
        mDIsFixed = DIsFixed;
        mVegaWeighted = VegaWeighted;
        mEndCriteria = EndCriteria;
        mOptimizationMeth = OptimizationMeth;
      };

    void Execute();
};

class SABRInterpolationWorker {
  public:
    string mObjectID;
    std::vector<double> mXArray;
    std::vector<ObjectHandler::property_t> mYArray;
    double mExpiry;
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
    string mOptimizationMeth;

    string mReturnValue;

    string mError;

    SABRInterpolationWorker(
      string ObjectID
,       std::vector<double> XArray
,       std::vector<ObjectHandler::property_t> YArray
,       double Expiry
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
,       string OptimizationMeth
     )
      {
        mObjectID = ObjectID;
        mXArray = XArray;
        mYArray = YArray;
        mExpiry = Expiry;
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
        mOptimizationMeth = OptimizationMeth;
      };

    void Execute();
};

class Interpolation2DWorker {
  public:
    string mObjectID;
    string mInterpolationType;
    std::vector<double> mXArray;
    std::vector<double> mYArray;
    std::vector< std::vector<double> > mZMatrix;

    string mReturnValue;

    string mError;

    Interpolation2DWorker(
      string ObjectID
,       string InterpolationType
,       std::vector<double> XArray
,       std::vector<double> YArray
,       std::vector< std::vector<double> > ZMatrix
     )
      {
        mObjectID = ObjectID;
        mInterpolationType = InterpolationType;
        mXArray = XArray;
        mYArray = YArray;
        mZMatrix = ZMatrix;
      };

    void Execute();
};

class ExtrapolatorEnableExtrapolationWorker {
  public:
    string mObjectID;
    bool mExtrapolationFlag;

    string mError;

    ExtrapolatorEnableExtrapolationWorker(
      string ObjectID
,       bool ExtrapolationFlag
     )
      {
        mObjectID = ObjectID;
        mExtrapolationFlag = ExtrapolationFlag;
      };

    void Execute();
};

class InterpolationInterpolateWorker {
  public:
    string mObjectID;
    std::vector<double> mXValues;
    bool mAllowExtrapolation;

    std::vector<double> mReturnValue;

    string mError;

    InterpolationInterpolateWorker(
      string ObjectID
,       std::vector<double> XValues
,       bool AllowExtrapolation
     )
      {
        mObjectID = ObjectID;
        mXValues = XValues;
        mAllowExtrapolation = AllowExtrapolation;
      };

    void Execute();
};

class InterpolationDerivativeWorker {
  public:
    string mObjectID;
    std::vector<double> mXValues;
    bool mAllowExtrapolation;

    std::vector<double> mReturnValue;

    string mError;

    InterpolationDerivativeWorker(
      string ObjectID
,       std::vector<double> XValues
,       bool AllowExtrapolation
     )
      {
        mObjectID = ObjectID;
        mXValues = XValues;
        mAllowExtrapolation = AllowExtrapolation;
      };

    void Execute();
};

class InterpolationSecondDerivativeWorker {
  public:
    string mObjectID;
    std::vector<double> mXValues;
    bool mAllowExtrapolation;

    std::vector<double> mReturnValue;

    string mError;

    InterpolationSecondDerivativeWorker(
      string ObjectID
,       std::vector<double> XValues
,       bool AllowExtrapolation
     )
      {
        mObjectID = ObjectID;
        mXValues = XValues;
        mAllowExtrapolation = AllowExtrapolation;
      };

    void Execute();
};

class InterpolationPrimitiveWorker {
  public:
    string mObjectID;
    std::vector<double> mXValues;
    bool mAllowExtrapolation;

    std::vector<double> mReturnValue;

    string mError;

    InterpolationPrimitiveWorker(
      string ObjectID
,       std::vector<double> XValues
,       bool AllowExtrapolation
     )
      {
        mObjectID = ObjectID;
        mXValues = XValues;
        mAllowExtrapolation = AllowExtrapolation;
      };

    void Execute();
};

class InterpolationIsInRangeWorker {
  public:
    string mObjectID;
    std::vector<double> mXValues;

    std::vector<bool> mReturnValue;

    string mError;

    InterpolationIsInRangeWorker(
      string ObjectID
,       std::vector<double> XValues
     )
      {
        mObjectID = ObjectID;
        mXValues = XValues;
      };

    void Execute();
};

class InterpolationXminWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    InterpolationXminWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class InterpolationXmaxWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    InterpolationXmaxWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class CubicInterpolationPrimitiveConstantsWorker {
  public:
    string mObjectID;

    std::vector<double> mReturnValue;

    string mError;

    CubicInterpolationPrimitiveConstantsWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class CubicInterpolationACoefficientsWorker {
  public:
    string mObjectID;

    std::vector<double> mReturnValue;

    string mError;

    CubicInterpolationACoefficientsWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class CubicInterpolationBCoefficientsWorker {
  public:
    string mObjectID;

    std::vector<double> mReturnValue;

    string mError;

    CubicInterpolationBCoefficientsWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class CubicInterpolationCCoefficientsWorker {
  public:
    string mObjectID;

    std::vector<double> mReturnValue;

    string mError;

    CubicInterpolationCCoefficientsWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class CubicInterpolationMonotonicityAdjustmentsWorker {
  public:
    string mObjectID;

    std::vector<bool> mReturnValue;

    string mError;

    CubicInterpolationMonotonicityAdjustmentsWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class AbcdInterpolationAWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    AbcdInterpolationAWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class AbcdInterpolationBWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    AbcdInterpolationBWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class AbcdInterpolationCWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    AbcdInterpolationCWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class AbcdInterpolationDWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    AbcdInterpolationDWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class AbcdInterpolationRmsErrorWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    AbcdInterpolationRmsErrorWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class AbcdInterpolationMaxErrorWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    AbcdInterpolationMaxErrorWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class AbcdInterpolationEndCriteriaWorker {
  public:
    string mObjectID;

    string mReturnValue;

    string mError;

    AbcdInterpolationEndCriteriaWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class SABRInterpolationExpiryWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    SABRInterpolationExpiryWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class SABRInterpolationForwardWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    SABRInterpolationForwardWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class SABRInterpolationAlphaWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    SABRInterpolationAlphaWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class SABRInterpolationBetaWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    SABRInterpolationBetaWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class SABRInterpolationNuWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    SABRInterpolationNuWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class SABRInterpolationRhoWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    SABRInterpolationRhoWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class SABRInterpolationRmsErrorWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    SABRInterpolationRmsErrorWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class SABRInterpolationMaxErrorWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    SABRInterpolationMaxErrorWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class SABRInterpolationEndCriteriaWorker {
  public:
    string mObjectID;

    string mReturnValue;

    string mError;

    SABRInterpolationEndCriteriaWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class SABRInterpolationWeightsWorker {
  public:
    string mObjectID;

    std::vector<double> mReturnValue;

    string mError;

    SABRInterpolationWeightsWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class Interpolation2DXminWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    Interpolation2DXminWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class Interpolation2DXmaxWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    Interpolation2DXmaxWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class Interpolation2DXvaluesWorker {
  public:
    string mObjectID;

    std::vector<double> mReturnValue;

    string mError;

    Interpolation2DXvaluesWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class Interpolation2DYminWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    Interpolation2DYminWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class Interpolation2DYmaxWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    Interpolation2DYmaxWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class Interpolation2DYvaluesWorker {
  public:
    string mObjectID;

    std::vector<double> mReturnValue;

    string mError;

    Interpolation2DYvaluesWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class Interpolation2DzDataWorker {
  public:
    string mObjectID;

    std::vector< std::vector<double> > mReturnValue;

    string mError;

    Interpolation2DzDataWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class Interpolation2DIsInRangeWorker {
  public:
    string mObjectID;
    std::vector<double> mXValues;
    double mYValue;

    std::vector<bool> mReturnValue;

    string mError;

    Interpolation2DIsInRangeWorker(
      string ObjectID
,       std::vector<double> XValues
,       double YValue
     )
      {
        mObjectID = ObjectID;
        mXValues = XValues;
        mYValue = YValue;
      };

    void Execute();
};

class Interpolation2DInterpolateWorker {
  public:
    string mObjectID;
    std::vector<double> mXValue;
    double mYValue;
    bool mAllowExtrapolation;

    std::vector<double> mReturnValue;

    string mError;

    Interpolation2DInterpolateWorker(
      string ObjectID
,       std::vector<double> XValue
,       double YValue
,       bool AllowExtrapolation
     )
      {
        mObjectID = ObjectID;
        mXValue = XValue;
        mYValue = YValue;
        mAllowExtrapolation = AllowExtrapolation;
      };

    void Execute();
};
 
#endif
