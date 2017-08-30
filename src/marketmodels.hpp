/* 
  Copyright (C) 2016 -2017 Jerry Jin
*/

#ifndef marketmodels_h
#define marketmodels_h
#include <nan.h>
#include <string>
#include <queue>
#include <utility>

#include "../quantlibxl.hpp"

#include <oh/objecthandler.hpp>

using namespace node;
using namespace v8;
using namespace std;


class FlatVolWorker {
  public:
    string mObjectID;
    std::vector<double> mVolatilities;
    string mCorrelations;
    string mEvolutionDescription;
    long mFactors;
    std::vector<double> mInitialRates;
    std::vector<double> mDisplacements;

    string mReturnValue;

    string mError;

    FlatVolWorker(
      string ObjectID
,       std::vector<double> Volatilities
,       string Correlations
,       string EvolutionDescription
,       long Factors
,       std::vector<double> InitialRates
,       std::vector<double> Displacements
     )
      {
        mObjectID = ObjectID;
        mVolatilities = Volatilities;
        mCorrelations = Correlations;
        mEvolutionDescription = EvolutionDescription;
        mFactors = Factors;
        mInitialRates = InitialRates;
        mDisplacements = Displacements;
      };

    void Execute();
};

class AbcdVolWorker {
  public:
    string mObjectID;
    double mA;
    double mB;
    double mC;
    double mD;
    std::vector<double> mKs;
    string mCorrelations;
    string mEvolutionDescription;
    long mFactors;
    std::vector<double> mInitialRates;
    std::vector<double> mDisplacements;

    string mReturnValue;

    string mError;

    AbcdVolWorker(
      string ObjectID
,       double A
,       double B
,       double C
,       double D
,       std::vector<double> Ks
,       string Correlations
,       string EvolutionDescription
,       long Factors
,       std::vector<double> InitialRates
,       std::vector<double> Displacements
     )
      {
        mObjectID = ObjectID;
        mA = A;
        mB = B;
        mC = C;
        mD = D;
        mKs = Ks;
        mCorrelations = Correlations;
        mEvolutionDescription = EvolutionDescription;
        mFactors = Factors;
        mInitialRates = InitialRates;
        mDisplacements = Displacements;
      };

    void Execute();
};

class PseudoRootFacadeWorker {
  public:
    string mObjectID;
    string mCalibrator;

    string mReturnValue;

    string mError;

    PseudoRootFacadeWorker(
      string ObjectID
,       string Calibrator
     )
      {
        mObjectID = ObjectID;
        mCalibrator = Calibrator;
      };

    void Execute();
};

class CotSwapToFwdAdapterWorker {
  public:
    string mObjectID;
    string mCoterminalModel;

    string mReturnValue;

    string mError;

    CotSwapToFwdAdapterWorker(
      string ObjectID
,       string CoterminalModel
     )
      {
        mObjectID = ObjectID;
        mCoterminalModel = CoterminalModel;
      };

    void Execute();
};

class FwdPeriodAdapterWorker {
  public:
    string mObjectID;
    string mLargeModel;
    long mPeriod;
    long mOffset;
    std::vector<double> mDisplacements;

    string mReturnValue;

    string mError;

    FwdPeriodAdapterWorker(
      string ObjectID
,       string LargeModel
,       long Period
,       long Offset
,       std::vector<double> Displacements
     )
      {
        mObjectID = ObjectID;
        mLargeModel = LargeModel;
        mPeriod = Period;
        mOffset = Offset;
        mDisplacements = Displacements;
      };

    void Execute();
};

class FwdToCotSwapAdapterWorker {
  public:
    string mObjectID;
    string mForwardModel;

    string mReturnValue;

    string mError;

    FwdToCotSwapAdapterWorker(
      string ObjectID
,       string ForwardModel
     )
      {
        mObjectID = ObjectID;
        mForwardModel = ForwardModel;
      };

    void Execute();
};

class FlatVolFactoryWorker {
  public:
    string mObjectID;
    double mLongTermCorr;
    double mBeta;
    std::vector<double> mTimes;
    std::vector<double> mVolatilities;
    ObjectHandler::property_t mYieldCurve;
    double mDisplacement;

    string mReturnValue;

    string mError;

    FlatVolFactoryWorker(
      string ObjectID
,       double LongTermCorr
,       double Beta
,       std::vector<double> Times
,       std::vector<double> Volatilities
,       ObjectHandler::property_t YieldCurve
,       double Displacement
     )
      {
        mObjectID = ObjectID;
        mLongTermCorr = LongTermCorr;
        mBeta = Beta;
        mTimes = Times;
        mVolatilities = Volatilities;
        mYieldCurve = YieldCurve;
        mDisplacement = Displacement;
      };

    void Execute();
};

class MarketModelInitialRatesWorker {
  public:
    string mObjectID;

    std::vector<double> mReturnValue;

    string mError;

    MarketModelInitialRatesWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class MarketModelDisplacementsWorker {
  public:
    string mObjectID;

    std::vector<double> mReturnValue;

    string mError;

    MarketModelDisplacementsWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class MarketModelNumberOfRatesWorker {
  public:
    string mObjectID;

    long mReturnValue;

    string mError;

    MarketModelNumberOfRatesWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class MarketModelNumberOfFactorsWorker {
  public:
    string mObjectID;

    long mReturnValue;

    string mError;

    MarketModelNumberOfFactorsWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class MarketModelNumberOfStepsWorker {
  public:
    string mObjectID;

    long mReturnValue;

    string mError;

    MarketModelNumberOfStepsWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class MarketModelPseudoRootWorker {
  public:
    string mObjectID;
    long mIndex;

    std::vector< std::vector<double> > mReturnValue;

    string mError;

    MarketModelPseudoRootWorker(
      string ObjectID
,       long Index
     )
      {
        mObjectID = ObjectID;
        mIndex = Index;
      };

    void Execute();
};

class MarketModelCovarianceWorker {
  public:
    string mObjectID;
    long mIndex;

    std::vector< std::vector<double> > mReturnValue;

    string mError;

    MarketModelCovarianceWorker(
      string ObjectID
,       long Index
     )
      {
        mObjectID = ObjectID;
        mIndex = Index;
      };

    void Execute();
};

class MarketModelTotalCovarianceWorker {
  public:
    string mObjectID;
    long mIndex;

    std::vector< std::vector<double> > mReturnValue;

    string mError;

    MarketModelTotalCovarianceWorker(
      string ObjectID
,       long Index
     )
      {
        mObjectID = ObjectID;
        mIndex = Index;
      };

    void Execute();
};

class MarketModelTimeDependentVolatilityWorker {
  public:
    string mObjectID;
    long mIndex;

    std::vector<double> mReturnValue;

    string mError;

    MarketModelTimeDependentVolatilityWorker(
      string ObjectID
,       long Index
     )
      {
        mObjectID = ObjectID;
        mIndex = Index;
      };

    void Execute();
};

class CoterminalSwapForwardJacobianWorker {
  public:
    string mCurveState;

    std::vector< std::vector<double> > mReturnValue;

    string mError;

    CoterminalSwapForwardJacobianWorker(
      string CurveState
     )
      {
        mCurveState = CurveState;
      };

    void Execute();
};

class CoterminalSwapZedMatrixWorker {
  public:
    string mCurveState;
    double mDisplacement;

    std::vector< std::vector<double> > mReturnValue;

    string mError;

    CoterminalSwapZedMatrixWorker(
      string CurveState
,       double Displacement
     )
      {
        mCurveState = CurveState;
        mDisplacement = Displacement;
      };

    void Execute();
};

class CoinitialSwapForwardJacobianWorker {
  public:
    string mCurveState;

    std::vector< std::vector<double> > mReturnValue;

    string mError;

    CoinitialSwapForwardJacobianWorker(
      string CurveState
     )
      {
        mCurveState = CurveState;
      };

    void Execute();
};

class CoinitialSwapZedMatrixWorker {
  public:
    string mCurveState;
    double mDisplacement;

    std::vector< std::vector<double> > mReturnValue;

    string mError;

    CoinitialSwapZedMatrixWorker(
      string CurveState
,       double Displacement
     )
      {
        mCurveState = CurveState;
        mDisplacement = Displacement;
      };

    void Execute();
};

class CmSwapForwardJacobianWorker {
  public:
    string mCurveState;
    long mSpanningForwards;

    std::vector< std::vector<double> > mReturnValue;

    string mError;

    CmSwapForwardJacobianWorker(
      string CurveState
,       long SpanningForwards
     )
      {
        mCurveState = CurveState;
        mSpanningForwards = SpanningForwards;
      };

    void Execute();
};

class CmSwapZedMatrixWorker {
  public:
    string mCurveState;
    long mSpanningForwards;
    double mDisplacement;

    std::vector< std::vector<double> > mReturnValue;

    string mError;

    CmSwapZedMatrixWorker(
      string CurveState
,       long SpanningForwards
,       double Displacement
     )
      {
        mCurveState = CurveState;
        mSpanningForwards = SpanningForwards;
        mDisplacement = Displacement;
      };

    void Execute();
};

class AnnuityWorker {
  public:
    string mCurveState;
    long mStartIndex;
    long mEndIndex;
    long mNumeraireIndex;

    double mReturnValue;

    string mError;

    AnnuityWorker(
      string CurveState
,       long StartIndex
,       long EndIndex
,       long NumeraireIndex
     )
      {
        mCurveState = CurveState;
        mStartIndex = StartIndex;
        mEndIndex = EndIndex;
        mNumeraireIndex = NumeraireIndex;
      };

    void Execute();
};

class SwapDerivativeWorker {
  public:
    string mCurveState;
    long mStartIndex;
    long mEndIndex;
    long mFwdRateIndex;

    double mReturnValue;

    string mError;

    SwapDerivativeWorker(
      string CurveState
,       long StartIndex
,       long EndIndex
,       long FwdRateIndex
     )
      {
        mCurveState = CurveState;
        mStartIndex = StartIndex;
        mEndIndex = EndIndex;
        mFwdRateIndex = FwdRateIndex;
      };

    void Execute();
};

class RateVolDifferencesWorker {
  public:
    string mMarketModel1;
    string mMarketModel2;

    std::vector<double> mReturnValue;

    string mError;

    RateVolDifferencesWorker(
      string MarketModel1
,       string MarketModel2
     )
      {
        mMarketModel1 = MarketModel1;
        mMarketModel2 = MarketModel2;
      };

    void Execute();
};

class RateInstVolDifferencesWorker {
  public:
    string mMarketModel1;
    string mMarketModel2;
    long mIndex;

    std::vector<double> mReturnValue;

    string mError;

    RateInstVolDifferencesWorker(
      string MarketModel1
,       string MarketModel2
,       long Index
     )
      {
        mMarketModel1 = MarketModel1;
        mMarketModel2 = MarketModel2;
        mIndex = Index;
      };

    void Execute();
};
 
#endif
