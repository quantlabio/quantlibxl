/* 
  Copyright (C) 2016 -2017 Jerry Jin
*/

#ifndef correlation_h
#define correlation_h
#include <nan.h>
#include <string>
#include <queue>
#include <utility>

#include "../quantlibxl.hpp"

#include <oh/objecthandler.hpp>

using namespace node;
using namespace v8;
using namespace std;


class MarketModelLmLinearExponentialCorrelationModelWorker {
  public:
    string mObjectID;
    long mSize;
    double mRho;
    double mBeta;
    long mFactors;

    string mReturnValue;

    string mError;

    MarketModelLmLinearExponentialCorrelationModelWorker(
      string ObjectID
,       long Size
,       double Rho
,       double Beta
,       long Factors
     )
      {
        mObjectID = ObjectID;
        mSize = Size;
        mRho = Rho;
        mBeta = Beta;
        mFactors = Factors;
      };

    void Execute();
};

class HistoricalForwardRatesAnalysisWorker {
  public:
    string mObjectID;
    string mSequenceStats;
    ObjectHandler::property_t mStartDate;
    ObjectHandler::property_t mEndDate;
    string mStep;
    string mIborIndex;
    string mInitialGap;
    string mHorizon;
    std::vector<string> mIborIndexes;
    std::vector<string> mSwapIndexes;
    string mDayCounter;
    string mTraitsID;
    string mInterpolatorID;
    double mBootstrapAccuracy;

    string mReturnValue;

    string mError;

    HistoricalForwardRatesAnalysisWorker(
      string ObjectID
,       string SequenceStats
,       ObjectHandler::property_t StartDate
,       ObjectHandler::property_t EndDate
,       string Step
,       string IborIndex
,       string InitialGap
,       string Horizon
,       std::vector<string> IborIndexes
,       std::vector<string> SwapIndexes
,       string DayCounter
,       string TraitsID
,       string InterpolatorID
,       double BootstrapAccuracy
     )
      {
        mObjectID = ObjectID;
        mSequenceStats = SequenceStats;
        mStartDate = StartDate;
        mEndDate = EndDate;
        mStep = Step;
        mIborIndex = IborIndex;
        mInitialGap = InitialGap;
        mHorizon = Horizon;
        mIborIndexes = IborIndexes;
        mSwapIndexes = SwapIndexes;
        mDayCounter = DayCounter;
        mTraitsID = TraitsID;
        mInterpolatorID = InterpolatorID;
        mBootstrapAccuracy = BootstrapAccuracy;
      };

    void Execute();
};

class HistoricalRatesAnalysisWorker {
  public:
    string mObjectID;
    string mSequenceStats;
    ObjectHandler::property_t mStartDate;
    ObjectHandler::property_t mEndDate;
    string mStep;
    std::vector<string> mInterestRateIndexes;

    string mReturnValue;

    string mError;

    HistoricalRatesAnalysisWorker(
      string ObjectID
,       string SequenceStats
,       ObjectHandler::property_t StartDate
,       ObjectHandler::property_t EndDate
,       string Step
,       std::vector<string> InterestRateIndexes
     )
      {
        mObjectID = ObjectID;
        mSequenceStats = SequenceStats;
        mStartDate = StartDate;
        mEndDate = EndDate;
        mStep = Step;
        mInterestRateIndexes = InterestRateIndexes;
      };

    void Execute();
};

class TimeHomogeneousForwardCorrelationWorker {
  public:
    string mObjectID;
    std::vector< std::vector<double> > mFwdCorrMatrix;
    std::vector<double> mRateTimes;

    string mReturnValue;

    string mError;

    TimeHomogeneousForwardCorrelationWorker(
      string ObjectID
,       std::vector< std::vector<double> > FwdCorrMatrix
,       std::vector<double> RateTimes
     )
      {
        mObjectID = ObjectID;
        mFwdCorrMatrix = FwdCorrMatrix;
        mRateTimes = RateTimes;
      };

    void Execute();
};

class ExponentialForwardCorrelationWorker {
  public:
    string mObjectID;
    std::vector<double> mRateTimes;
    double mLongTermCorr;
    double mBeta;
    double mGamma;
    std::vector<double> mTimes;

    string mReturnValue;

    string mError;

    ExponentialForwardCorrelationWorker(
      string ObjectID
,       std::vector<double> RateTimes
,       double LongTermCorr
,       double Beta
,       double Gamma
,       std::vector<double> Times
     )
      {
        mObjectID = ObjectID;
        mRateTimes = RateTimes;
        mLongTermCorr = LongTermCorr;
        mBeta = Beta;
        mGamma = Gamma;
        mTimes = Times;
      };

    void Execute();
};

class CotSwapFromFwdCorrelationWorker {
  public:
    string mObjectID;
    string mFwdCorr;
    string mCurveState;
    double mDisplacement;

    string mReturnValue;

    string mError;

    CotSwapFromFwdCorrelationWorker(
      string ObjectID
,       string FwdCorr
,       string CurveState
,       double Displacement
     )
      {
        mObjectID = ObjectID;
        mFwdCorr = FwdCorr;
        mCurveState = CurveState;
        mDisplacement = Displacement;
      };

    void Execute();
};

class HistoricalForwardRatesAnalysisSkippedDatesWorker {
  public:
    string mObjectID;

    std::vector<long> mReturnValue;

    string mError;

    HistoricalForwardRatesAnalysisSkippedDatesWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class HistoricalForwardRatesAnalysisSkippedDatesErrorMessageWorker {
  public:
    string mObjectID;

    std::vector<string> mReturnValue;

    string mError;

    HistoricalForwardRatesAnalysisSkippedDatesErrorMessageWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class HistoricalForwardRatesAnalysisFailedDatesWorker {
  public:
    string mObjectID;

    std::vector<long> mReturnValue;

    string mError;

    HistoricalForwardRatesAnalysisFailedDatesWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class HistoricalForwardRatesAnalysisFailedDatesErrorMessageWorker {
  public:
    string mObjectID;

    std::vector<string> mReturnValue;

    string mError;

    HistoricalForwardRatesAnalysisFailedDatesErrorMessageWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class HistoricalForwardRatesAnalysisFixingPeriodsWorker {
  public:
    string mObjectID;

    std::vector<string> mReturnValue;

    string mError;

    HistoricalForwardRatesAnalysisFixingPeriodsWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class HistoricalRatesAnalysisSkippedDatesWorker {
  public:
    string mObjectID;

    std::vector<long> mReturnValue;

    string mError;

    HistoricalRatesAnalysisSkippedDatesWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class HistoricalRatesAnalysisSkippedDatesErrorMessageWorker {
  public:
    string mObjectID;

    std::vector<string> mReturnValue;

    string mError;

    HistoricalRatesAnalysisSkippedDatesErrorMessageWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class PiecewiseConstantCorrelationCorrelationWorker {
  public:
    string mObjectID;
    long mTimeIndex;

    std::vector< std::vector<double> > mReturnValue;

    string mError;

    PiecewiseConstantCorrelationCorrelationWorker(
      string ObjectID
,       long TimeIndex
     )
      {
        mObjectID = ObjectID;
        mTimeIndex = TimeIndex;
      };

    void Execute();
};

class PiecewiseConstantCorrelationTimesWorker {
  public:
    string mObjectID;

    std::vector<double> mReturnValue;

    string mError;

    PiecewiseConstantCorrelationTimesWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class PiecewiseConstantCorrelationNumberOfRatesWorker {
  public:
    string mObjectID;

    long mReturnValue;

    string mError;

    PiecewiseConstantCorrelationNumberOfRatesWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class ExponentialCorrelationsWorker {
  public:
    std::vector<double> mRateTimes;
    double mLongTermCorr;
    double mBeta;
    double mGamma;
    double mTime;

    std::vector< std::vector<double> > mReturnValue;

    string mError;

    ExponentialCorrelationsWorker(
      std::vector<double> RateTimes
,       double LongTermCorr
,       double Beta
,       double Gamma
,       double Time
     )
      {
        mRateTimes = RateTimes;
        mLongTermCorr = LongTermCorr;
        mBeta = Beta;
        mGamma = Gamma;
        mTime = Time;
      };

    void Execute();
};
 
#endif
