/* 
  Copyright (C) 2016 -2017 Jerry Jin
*/

#ifndef options_h
#define options_h
#include <nan.h>
#include <string>
#include <queue>
#include <utility>

#include "../quantlibxl.hpp"

#include <oh/objecthandler.hpp>

using namespace node;
using namespace v8;
using namespace std;


class BarrierOptionWorker {
  public:
    string mObjectID;
    string mBarrierType;
    double mBarrier;
    double mRebate;
    string mPayoff;
    string mExercise;

    string mReturnValue;

    string mError;

    BarrierOptionWorker(
      string ObjectID
,       string BarrierType
,       double Barrier
,       double Rebate
,       string Payoff
,       string Exercise
     )
      {
        mObjectID = ObjectID;
        mBarrierType = BarrierType;
        mBarrier = Barrier;
        mRebate = Rebate;
        mPayoff = Payoff;
        mExercise = Exercise;
      };

    void Execute();
};

class CaAsianOptionWorker {
  public:
    string mObjectID;
    string mAverageType;
    string mPayoff;
    string mExercise;

    string mReturnValue;

    string mError;

    CaAsianOptionWorker(
      string ObjectID
,       string AverageType
,       string Payoff
,       string Exercise
     )
      {
        mObjectID = ObjectID;
        mAverageType = AverageType;
        mPayoff = Payoff;
        mExercise = Exercise;
      };

    void Execute();
};

class DaAsianOptionWorker {
  public:
    string mObjectID;
    string mAverageType;
    double mRunningAccumulator;
    long mPastFixings;
    std::vector<ObjectHandler::property_t> mFixingDates;
    string mPayoff;
    string mExercise;

    string mReturnValue;

    string mError;

    DaAsianOptionWorker(
      string ObjectID
,       string AverageType
,       double RunningAccumulator
,       long PastFixings
,       std::vector<ObjectHandler::property_t> FixingDates
,       string Payoff
,       string Exercise
     )
      {
        mObjectID = ObjectID;
        mAverageType = AverageType;
        mRunningAccumulator = RunningAccumulator;
        mPastFixings = PastFixings;
        mFixingDates = FixingDates;
        mPayoff = Payoff;
        mExercise = Exercise;
      };

    void Execute();
};

class DividendVanillaOptionWorker {
  public:
    string mObjectID;
    string mPayoff;
    string mExercise;
    std::vector<ObjectHandler::property_t> mDividendDates;
    std::vector<double> mDividends;

    string mReturnValue;

    string mError;

    DividendVanillaOptionWorker(
      string ObjectID
,       string Payoff
,       string Exercise
,       std::vector<ObjectHandler::property_t> DividendDates
,       std::vector<double> Dividends
     )
      {
        mObjectID = ObjectID;
        mPayoff = Payoff;
        mExercise = Exercise;
        mDividendDates = DividendDates;
        mDividends = Dividends;
      };

    void Execute();
};

class ForwardVanillaOptionWorker {
  public:
    string mObjectID;
    double mMoneyness;
    ObjectHandler::property_t mResetDate;
    string mPayoff;
    string mExercise;

    string mReturnValue;

    string mError;

    ForwardVanillaOptionWorker(
      string ObjectID
,       double Moneyness
,       ObjectHandler::property_t ResetDate
,       string Payoff
,       string Exercise
     )
      {
        mObjectID = ObjectID;
        mMoneyness = Moneyness;
        mResetDate = ResetDate;
        mPayoff = Payoff;
        mExercise = Exercise;
      };

    void Execute();
};

class VanillaOptionWorker {
  public:
    string mObjectID;
    string mPayoff;
    string mExercise;

    string mReturnValue;

    string mError;

    VanillaOptionWorker(
      string ObjectID
,       string Payoff
,       string Exercise
     )
      {
        mObjectID = ObjectID;
        mPayoff = Payoff;
        mExercise = Exercise;
      };

    void Execute();
};

class EuropeanOptionWorker {
  public:
    string mObjectID;
    string mPayoff;
    string mExercise;

    string mReturnValue;

    string mError;

    EuropeanOptionWorker(
      string ObjectID
,       string Payoff
,       string Exercise
     )
      {
        mObjectID = ObjectID;
        mPayoff = Payoff;
        mExercise = Exercise;
      };

    void Execute();
};

class QuantoVanillaOptionWorker {
  public:
    string mObjectID;
    string mPayoff;
    string mExercise;

    string mReturnValue;

    string mError;

    QuantoVanillaOptionWorker(
      string ObjectID
,       string Payoff
,       string Exercise
     )
      {
        mObjectID = ObjectID;
        mPayoff = Payoff;
        mExercise = Exercise;
      };

    void Execute();
};

class QuantoForwardVanillaOptionWorker {
  public:
    string mObjectID;
    double mMoneyness;
    ObjectHandler::property_t mResetDate;
    string mPayoff;
    string mExercise;

    string mReturnValue;

    string mError;

    QuantoForwardVanillaOptionWorker(
      string ObjectID
,       double Moneyness
,       ObjectHandler::property_t ResetDate
,       string Payoff
,       string Exercise
     )
      {
        mObjectID = ObjectID;
        mMoneyness = Moneyness;
        mResetDate = ResetDate;
        mPayoff = Payoff;
        mExercise = Exercise;
      };

    void Execute();
};

class DeltaWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    DeltaWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class DeltaForwardWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    DeltaForwardWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class ElasticityWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    ElasticityWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class GammaWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    GammaWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class ThetaWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    ThetaWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class ThetaPerDayWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    ThetaPerDayWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class VegaWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    VegaWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class RhoWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    RhoWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class DividendRhoWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    DividendRhoWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class ItmCashProbabilityWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    ItmCashProbabilityWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};
 
#endif
