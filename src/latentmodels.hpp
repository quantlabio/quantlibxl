/* 
  Copyright (C) 2016 -2017 Jerry Jin
*/

#ifndef latentmodels_h
#define latentmodels_h
#include <nan.h>
#include <string>
#include <queue>
#include <utility>

#include "../quantlibxl.hpp"

#include <oh/objecthandler.hpp>

using namespace node;
using namespace v8;
using namespace std;


class GaussianDefaultProbLMWorker {
  public:
    string mObjectID;
    string mBasket;
    std::vector< std::vector<double> > mFactors;

    string mReturnValue;

    string mError;

    GaussianDefaultProbLMWorker(
      string ObjectID
,       string Basket
,       std::vector< std::vector<double> > Factors
     )
      {
        mObjectID = ObjectID;
        mBasket = Basket;
        mFactors = Factors;
      };

    void Execute();
};

class TDefaultProbLMWorker {
  public:
    string mObjectID;
    std::vector<long> mTorders;
    string mBasket;
    std::vector< std::vector<double> > mFactors;

    string mReturnValue;

    string mError;

    TDefaultProbLMWorker(
      string ObjectID
,       std::vector<long> Torders
,       string Basket
,       std::vector< std::vector<double> > Factors
     )
      {
        mObjectID = ObjectID;
        mTorders = Torders;
        mBasket = Basket;
        mFactors = Factors;
      };

    void Execute();
};

class GaussianLMDefaultCorrelWorker {
  public:
    string mObjectID;
    ObjectHandler::property_t mCorrelationDate;
    long mNameindexA;
    long mNameindexB;

    double mReturnValue;

    string mError;

    GaussianLMDefaultCorrelWorker(
      string ObjectID
,       ObjectHandler::property_t CorrelationDate
,       long NameindexA
,       long NameindexB
     )
      {
        mObjectID = ObjectID;
        mCorrelationDate = CorrelationDate;
        mNameindexA = NameindexA;
        mNameindexB = NameindexB;
      };

    void Execute();
};

class GaussianLMAssetCorrelWorker {
  public:
    string mObjectID;
    long mNameindexA;
    long mNameindexB;

    double mReturnValue;

    string mError;

    GaussianLMAssetCorrelWorker(
      string ObjectID
,       long NameindexA
,       long NameindexB
     )
      {
        mObjectID = ObjectID;
        mNameindexA = NameindexA;
        mNameindexB = NameindexB;
      };

    void Execute();
};

class GaussianLMProbNHitsWorker {
  public:
    string mObjectID;
    long mNumDefaults;
    ObjectHandler::property_t mProbabilityDate;

    double mReturnValue;

    string mError;

    GaussianLMProbNHitsWorker(
      string ObjectID
,       long NumDefaults
,       ObjectHandler::property_t ProbabilityDate
     )
      {
        mObjectID = ObjectID;
        mNumDefaults = NumDefaults;
        mProbabilityDate = ProbabilityDate;
      };

    void Execute();
};

class TLMDefaultCorrelWorker {
  public:
    string mObjectID;
    ObjectHandler::property_t mCorrelationDate;
    long mNameindexA;
    long mNameindexB;

    double mReturnValue;

    string mError;

    TLMDefaultCorrelWorker(
      string ObjectID
,       ObjectHandler::property_t CorrelationDate
,       long NameindexA
,       long NameindexB
     )
      {
        mObjectID = ObjectID;
        mCorrelationDate = CorrelationDate;
        mNameindexA = NameindexA;
        mNameindexB = NameindexB;
      };

    void Execute();
};

class TLMAssetCorrelWorker {
  public:
    string mObjectID;
    long mNameindexA;
    long mNameindexB;

    double mReturnValue;

    string mError;

    TLMAssetCorrelWorker(
      string ObjectID
,       long NameindexA
,       long NameindexB
     )
      {
        mObjectID = ObjectID;
        mNameindexA = NameindexA;
        mNameindexB = NameindexB;
      };

    void Execute();
};

class TLMProbNHitsWorker {
  public:
    string mObjectID;
    long mNumDefaults;
    ObjectHandler::property_t mProbabilityDate;

    double mReturnValue;

    string mError;

    TLMProbNHitsWorker(
      string ObjectID
,       long NumDefaults
,       ObjectHandler::property_t ProbabilityDate
     )
      {
        mObjectID = ObjectID;
        mNumDefaults = NumDefaults;
        mProbabilityDate = ProbabilityDate;
      };

    void Execute();
};
 
#endif
