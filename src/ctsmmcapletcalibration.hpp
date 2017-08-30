/* 
  Copyright (C) 2016 -2017 Jerry Jin
*/

#ifndef ctsmmcapletcalibration_h
#define ctsmmcapletcalibration_h
#include <nan.h>
#include <string>
#include <queue>
#include <utility>

#include "../quantlibxl.hpp"

#include <oh/objecthandler.hpp>

using namespace node;
using namespace v8;
using namespace std;


class CTSMMCapletOriginalCalibrationWorker {
  public:
    string mObjectID;
    string mEvolution;
    string mCorrelations;
    std::vector<string> mSwapPiecewiseConstantVariances;
    std::vector<double> mCapletVols;
    string mCurveState;
    double mDisplacement;
    std::vector<double> mAlphas;
    bool mLowestRoot;
    bool mUseFullApprox;

    string mReturnValue;

    string mError;

    CTSMMCapletOriginalCalibrationWorker(
      string ObjectID
,       string Evolution
,       string Correlations
,       std::vector<string> SwapPiecewiseConstantVariances
,       std::vector<double> CapletVols
,       string CurveState
,       double Displacement
,       std::vector<double> Alphas
,       bool LowestRoot
,       bool UseFullApprox
     )
      {
        mObjectID = ObjectID;
        mEvolution = Evolution;
        mCorrelations = Correlations;
        mSwapPiecewiseConstantVariances = SwapPiecewiseConstantVariances;
        mCapletVols = CapletVols;
        mCurveState = CurveState;
        mDisplacement = Displacement;
        mAlphas = Alphas;
        mLowestRoot = LowestRoot;
        mUseFullApprox = UseFullApprox;
      };

    void Execute();
};

class CTSMMCapletAlphaFormCalibrationWorker {
  public:
    string mObjectID;
    string mEvolution;
    string mCorrelations;
    std::vector<string> mSwapPiecewiseConstantVariances;
    std::vector<double> mCapletVols;
    string mCurveState;
    double mDisplacement;
    std::vector<double> mAlphaInitial;
    std::vector<double> mAlphaMax;
    std::vector<double> mAlphaMin;
    bool mMaximizeHomogeneity;
    string mAlphaForm;

    string mReturnValue;

    string mError;

    CTSMMCapletAlphaFormCalibrationWorker(
      string ObjectID
,       string Evolution
,       string Correlations
,       std::vector<string> SwapPiecewiseConstantVariances
,       std::vector<double> CapletVols
,       string CurveState
,       double Displacement
,       std::vector<double> AlphaInitial
,       std::vector<double> AlphaMax
,       std::vector<double> AlphaMin
,       bool MaximizeHomogeneity
,       string AlphaForm
     )
      {
        mObjectID = ObjectID;
        mEvolution = Evolution;
        mCorrelations = Correlations;
        mSwapPiecewiseConstantVariances = SwapPiecewiseConstantVariances;
        mCapletVols = CapletVols;
        mCurveState = CurveState;
        mDisplacement = Displacement;
        mAlphaInitial = AlphaInitial;
        mAlphaMax = AlphaMax;
        mAlphaMin = AlphaMin;
        mMaximizeHomogeneity = MaximizeHomogeneity;
        mAlphaForm = AlphaForm;
      };

    void Execute();
};

class CTSMMCapletMaxHomogeneityCalibrationWorker {
  public:
    string mObjectID;
    string mEvolution;
    string mCorrelations;
    std::vector<string> mSwapPiecewiseConstantVariances;
    std::vector<double> mCapletVols;
    string mCurveState;
    double mDisplacement;
    double mCaplet0Swaption1Priority;

    string mReturnValue;

    string mError;

    CTSMMCapletMaxHomogeneityCalibrationWorker(
      string ObjectID
,       string Evolution
,       string Correlations
,       std::vector<string> SwapPiecewiseConstantVariances
,       std::vector<double> CapletVols
,       string CurveState
,       double Displacement
,       double Caplet0Swaption1Priority
     )
      {
        mObjectID = ObjectID;
        mEvolution = Evolution;
        mCorrelations = Correlations;
        mSwapPiecewiseConstantVariances = SwapPiecewiseConstantVariances;
        mCapletVols = CapletVols;
        mCurveState = CurveState;
        mDisplacement = Displacement;
        mCaplet0Swaption1Priority = Caplet0Swaption1Priority;
      };

    void Execute();
};

class CTSMMCapletCalibrationCalibrateWorker {
  public:
    string mObjectID;
    ObjectHandler::property_t mNumberOfFactors;
    ObjectHandler::property_t mMaxIter;
    double mTol;
    ObjectHandler::property_t mInnerMaxIter;
    double mInnerTol;

    bool mReturnValue;

    string mError;

    CTSMMCapletCalibrationCalibrateWorker(
      string ObjectID
,       ObjectHandler::property_t NumberOfFactors
,       ObjectHandler::property_t MaxIter
,       double Tol
,       ObjectHandler::property_t InnerMaxIter
,       double InnerTol
     )
      {
        mObjectID = ObjectID;
        mNumberOfFactors = NumberOfFactors;
        mMaxIter = MaxIter;
        mTol = Tol;
        mInnerMaxIter = InnerMaxIter;
        mInnerTol = InnerTol;
      };

    void Execute();
};

class CTSMMCapletCalibrationFailuresWorker {
  public:
    string mObjectID;

    long mReturnValue;

    string mError;

    CTSMMCapletCalibrationFailuresWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class CTSMMCapletCalibrationDeformationSizeWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    CTSMMCapletCalibrationDeformationSizeWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class CTSMMCapletCalibrationMarketCapletVolsWorker {
  public:
    string mObjectID;

    std::vector<double> mReturnValue;

    string mError;

    CTSMMCapletCalibrationMarketCapletVolsWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class CTSMMCapletCalibrationModelCapletVolsWorker {
  public:
    string mObjectID;

    std::vector<double> mReturnValue;

    string mError;

    CTSMMCapletCalibrationModelCapletVolsWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class CTSMMCapletCalibrationCapletRmsErrorWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    CTSMMCapletCalibrationCapletRmsErrorWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class CTSMMCapletCalibrationCapletMaxErrorWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    CTSMMCapletCalibrationCapletMaxErrorWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class CTSMMCapletCalibrationMarketSwaptionVolsWorker {
  public:
    string mObjectID;

    std::vector<double> mReturnValue;

    string mError;

    CTSMMCapletCalibrationMarketSwaptionVolsWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class CTSMMCapletCalibrationModelSwaptionVolsWorker {
  public:
    string mObjectID;

    std::vector<double> mReturnValue;

    string mError;

    CTSMMCapletCalibrationModelSwaptionVolsWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class CTSMMCapletCalibrationSwaptionRmsErrorWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    CTSMMCapletCalibrationSwaptionRmsErrorWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class CTSMMCapletCalibrationSwaptionMaxErrorWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    CTSMMCapletCalibrationSwaptionMaxErrorWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class CTSMMCapletCalibrationSwapPseudoRootWorker {
  public:
    string mObjectID;
    long mIndex;

    std::vector< std::vector<double> > mReturnValue;

    string mError;

    CTSMMCapletCalibrationSwapPseudoRootWorker(
      string ObjectID
,       long Index
     )
      {
        mObjectID = ObjectID;
        mIndex = Index;
      };

    void Execute();
};

class CTSMMCapletCalibrationTimeDependentCalibratedSwaptionVolsWorker {
  public:
    string mObjectID;
    long mIndex;

    std::vector<double> mReturnValue;

    string mError;

    CTSMMCapletCalibrationTimeDependentCalibratedSwaptionVolsWorker(
      string ObjectID
,       long Index
     )
      {
        mObjectID = ObjectID;
        mIndex = Index;
      };

    void Execute();
};

class CTSMMCapletCalibrationTimeDependentUnCalibratedSwaptionVolsWorker {
  public:
    string mObjectID;
    long mIndex;

    std::vector<double> mReturnValue;

    string mError;

    CTSMMCapletCalibrationTimeDependentUnCalibratedSwaptionVolsWorker(
      string ObjectID
,       long Index
     )
      {
        mObjectID = ObjectID;
        mIndex = Index;
      };

    void Execute();
};

class CTSMMCapletAlphaFormCalibrationAlphaWorker {
  public:
    string mObjectID;

    std::vector<double> mReturnValue;

    string mError;

    CTSMMCapletAlphaFormCalibrationAlphaWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};
 
#endif
