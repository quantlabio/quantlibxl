/* 
  Copyright (C) 2016 -2017 Jerry Jin
*/

#ifndef optimization_h
#define optimization_h
#include <nan.h>
#include <string>
#include <queue>
#include <utility>

#include "../quantlibxl.hpp"

#include <oh/objecthandler.hpp>

using namespace node;
using namespace v8;
using namespace std;


class EndCriteriaWorker {
  public:
    string mObjectID;
    long mMaxIterations;
    long mMaxStationaryStateIterations;
    double mRootEpsilon;
    double mFunctionEpsilon;
    double mGradientNormEpsilon;

    string mReturnValue;

    string mError;

    EndCriteriaWorker(
      string ObjectID
,       long MaxIterations
,       long MaxStationaryStateIterations
,       double RootEpsilon
,       double FunctionEpsilon
,       double GradientNormEpsilon
     )
      {
        mObjectID = ObjectID;
        mMaxIterations = MaxIterations;
        mMaxStationaryStateIterations = MaxStationaryStateIterations;
        mRootEpsilon = RootEpsilon;
        mFunctionEpsilon = FunctionEpsilon;
        mGradientNormEpsilon = GradientNormEpsilon;
      };

    void Execute();
};

class NoConstraintWorker {
  public:
    string mObjectID;

    string mReturnValue;

    string mError;

    NoConstraintWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class SimplexWorker {
  public:
    string mObjectID;
    double mLambda;

    string mReturnValue;

    string mError;

    SimplexWorker(
      string ObjectID
,       double Lambda
     )
      {
        mObjectID = ObjectID;
        mLambda = Lambda;
      };

    void Execute();
};

class LevenbergMarquardtWorker {
  public:
    string mObjectID;
    double mEpsfcn;
    double mXtol;
    double mGtol;

    string mReturnValue;

    string mError;

    LevenbergMarquardtWorker(
      string ObjectID
,       double Epsfcn
,       double Xtol
,       double Gtol
     )
      {
        mObjectID = ObjectID;
        mEpsfcn = Epsfcn;
        mXtol = Xtol;
        mGtol = Gtol;
      };

    void Execute();
};

class ConjugateGradientWorker {
  public:
    string mObjectID;
    string mLineSearch;

    string mReturnValue;

    string mError;

    ConjugateGradientWorker(
      string ObjectID
,       string LineSearch
     )
      {
        mObjectID = ObjectID;
        mLineSearch = LineSearch;
      };

    void Execute();
};

class SteepestDescentWorker {
  public:
    string mObjectID;
    string mLineSearch;

    string mReturnValue;

    string mError;

    SteepestDescentWorker(
      string ObjectID
,       string LineSearch
     )
      {
        mObjectID = ObjectID;
        mLineSearch = LineSearch;
      };

    void Execute();
};

class ArmijoLineSearchWorker {
  public:
    string mObjectID;
    double mEpsilon;
    double mAlpha;
    double mBeta;

    string mReturnValue;

    string mError;

    ArmijoLineSearchWorker(
      string ObjectID
,       double Epsilon
,       double Alpha
,       double Beta
     )
      {
        mObjectID = ObjectID;
        mEpsilon = Epsilon;
        mAlpha = Alpha;
        mBeta = Beta;
      };

    void Execute();
};

class EndCriteriaMaxIterationsWorker {
  public:
    string mObjectID;

    long mReturnValue;

    string mError;

    EndCriteriaMaxIterationsWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class EndCriteriaMaxStationaryStateIterationsWorker {
  public:
    string mObjectID;

    long mReturnValue;

    string mError;

    EndCriteriaMaxStationaryStateIterationsWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class EndCriteriaFunctionEpsilonWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    EndCriteriaFunctionEpsilonWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class EndCriteriaGradientNormEpsilonWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    EndCriteriaGradientNormEpsilonWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class SphereCylinderOptimizerClosestWorker {
  public:
    double mR;
    double mS;
    double mAlpha;
    double mZ1;
    double mZ2;
    double mZ3;
    ObjectHandler::property_t mMaxIter;
    double mTol;

    std::vector<double> mReturnValue;

    string mError;

    SphereCylinderOptimizerClosestWorker(
      double R
,       double S
,       double Alpha
,       double Z1
,       double Z2
,       double Z3
,       ObjectHandler::property_t MaxIter
,       double Tol
     )
      {
        mR = R;
        mS = S;
        mAlpha = Alpha;
        mZ1 = Z1;
        mZ2 = Z2;
        mZ3 = Z3;
        mMaxIter = MaxIter;
        mTol = Tol;
      };

    void Execute();
};

class SecondsToStringWorker {
  public:
    double mSeconds;

    string mReturnValue;

    string mError;

    SecondsToStringWorker(
      double Seconds
     )
      {
        mSeconds = Seconds;
      };

    void Execute();
};
 
#endif
