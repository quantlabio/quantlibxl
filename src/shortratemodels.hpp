/* 
  Copyright (C) 2016 -2017 Jerry Jin
*/

#ifndef shortratemodels_h
#define shortratemodels_h
#include <nan.h>
#include <string>
#include <queue>
#include <utility>

#include "../quantlibxl.hpp"

#include <oh/objecthandler.hpp>

using namespace node;
using namespace v8;
using namespace std;


class HullWhiteWorker {
  public:
    string mObjectID;
    ObjectHandler::property_t mYieldCurve;
    double mA;
    double mSigma;

    string mReturnValue;

    string mError;

    HullWhiteWorker(
      string ObjectID
,       ObjectHandler::property_t YieldCurve
,       double A
,       double Sigma
     )
      {
        mObjectID = ObjectID;
        mYieldCurve = YieldCurve;
        mA = A;
        mSigma = Sigma;
      };

    void Execute();
};

class VasicekWorker {
  public:
    string mObjectID;
    double mR0;
    double mA;
    double mB;
    double mSigma;
    double mLambda;

    string mReturnValue;

    string mError;

    VasicekWorker(
      string ObjectID
,       double R0
,       double A
,       double B
,       double Sigma
,       double Lambda
     )
      {
        mObjectID = ObjectID;
        mR0 = R0;
        mA = A;
        mB = B;
        mSigma = Sigma;
        mLambda = Lambda;
      };

    void Execute();
};

class ModelG2Worker {
  public:
    string mObjectID;
    ObjectHandler::property_t mYieldCurve;
    double mA;
    double mSigma;
    double mB;
    double mEta;
    double mCorrelation;

    string mReturnValue;

    string mError;

    ModelG2Worker(
      string ObjectID
,       ObjectHandler::property_t YieldCurve
,       double A
,       double Sigma
,       double B
,       double Eta
,       double Correlation
     )
      {
        mObjectID = ObjectID;
        mYieldCurve = YieldCurve;
        mA = A;
        mSigma = Sigma;
        mB = B;
        mEta = Eta;
        mCorrelation = Correlation;
      };

    void Execute();
};

class VasicekAWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    VasicekAWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class VasicekBWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    VasicekBWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class VasicekLambdaWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    VasicekLambdaWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class VasicekSigmaWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    VasicekSigmaWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class ModelG2AWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    ModelG2AWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class ModelG2sigmaWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    ModelG2sigmaWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class ModelG2BWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    ModelG2BWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class ModelG2etaWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    ModelG2etaWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class ModelG2rhoWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    ModelG2rhoWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class FuturesConvexityBiasWorker {
  public:
    double mFuturesPrice;
    double mT1;
    double mT2;
    double mSigma;
    double mA;

    double mReturnValue;

    string mError;

    FuturesConvexityBiasWorker(
      double FuturesPrice
,       double T1
,       double T2
,       double Sigma
,       double A
     )
      {
        mFuturesPrice = FuturesPrice;
        mT1 = T1;
        mT2 = T2;
        mSigma = Sigma;
        mA = A;
      };

    void Execute();
};
 
#endif
