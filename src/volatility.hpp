/* 
  Copyright (C) 2016 -2017 Jerry Jin
*/

#ifndef volatility_h
#define volatility_h
#include <nan.h>
#include <string>
#include <queue>
#include <utility>

#include "../quantlibxl.hpp"

#include <oh/objecthandler.hpp>

using namespace node;
using namespace v8;
using namespace std;


class PiecewiseConstantAbcdVarianceWorker {
  public:
    string mObjectID;
    double mA;
    double mB;
    double mC;
    double mD;
    long mResetIndex;
    std::vector<double> mRateTimes;

    string mReturnValue;

    string mError;

    PiecewiseConstantAbcdVarianceWorker(
      string ObjectID
,       double A
,       double B
,       double C
,       double D
,       long ResetIndex
,       std::vector<double> RateTimes
     )
      {
        mObjectID = ObjectID;
        mA = A;
        mB = B;
        mC = C;
        mD = D;
        mResetIndex = ResetIndex;
        mRateTimes = RateTimes;
      };

    void Execute();
};

class MarketModelLmExtLinearExponentialVolModelWorker {
  public:
    string mObjectID;
    std::vector<double> mFixingTimes;
    double mA;
    double mB;
    double mC;
    double mD;

    string mReturnValue;

    string mError;

    MarketModelLmExtLinearExponentialVolModelWorker(
      string ObjectID
,       std::vector<double> FixingTimes
,       double A
,       double B
,       double C
,       double D
     )
      {
        mObjectID = ObjectID;
        mFixingTimes = FixingTimes;
        mA = A;
        mB = B;
        mC = C;
        mD = D;
      };

    void Execute();
};

class PiecewiseConstantVarianceVariancesWorker {
  public:
    string mObjectID;

    std::vector<double> mReturnValue;

    string mError;

    PiecewiseConstantVarianceVariancesWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class PiecewiseConstantVarianceVolatilitiesWorker {
  public:
    string mObjectID;

    std::vector<double> mReturnValue;

    string mError;

    PiecewiseConstantVarianceVolatilitiesWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class PiecewiseConstantVarianceRateTimesWorker {
  public:
    string mObjectID;

    std::vector<double> mReturnValue;

    string mError;

    PiecewiseConstantVarianceRateTimesWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class PiecewiseConstantVarianceVarianceWorker {
  public:
    string mObjectID;
    long mTimeIndex;

    double mReturnValue;

    string mError;

    PiecewiseConstantVarianceVarianceWorker(
      string ObjectID
,       long TimeIndex
     )
      {
        mObjectID = ObjectID;
        mTimeIndex = TimeIndex;
      };

    void Execute();
};

class PiecewiseConstantVarianceVolatilityWorker {
  public:
    string mObjectID;
    long mTimeIndex;

    double mReturnValue;

    string mError;

    PiecewiseConstantVarianceVolatilityWorker(
      string ObjectID
,       long TimeIndex
     )
      {
        mObjectID = ObjectID;
        mTimeIndex = TimeIndex;
      };

    void Execute();
};

class PiecewiseConstantVarianceTotalVarianceWorker {
  public:
    string mObjectID;
    long mTimeIndex;

    double mReturnValue;

    string mError;

    PiecewiseConstantVarianceTotalVarianceWorker(
      string ObjectID
,       long TimeIndex
     )
      {
        mObjectID = ObjectID;
        mTimeIndex = TimeIndex;
      };

    void Execute();
};

class PiecewiseConstantVarianceTotalVolatilityWorker {
  public:
    string mObjectID;
    long mTimeIndex;

    double mReturnValue;

    string mError;

    PiecewiseConstantVarianceTotalVolatilityWorker(
      string ObjectID
,       long TimeIndex
     )
      {
        mObjectID = ObjectID;
        mTimeIndex = TimeIndex;
      };

    void Execute();
};
 
#endif
