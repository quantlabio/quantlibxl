/* 
  Copyright (C) 2016 -2017 Jerry Jin
*/

#ifndef basketlossmodels_h
#define basketlossmodels_h
#include <nan.h>
#include <string>
#include <queue>
#include <utility>

#include "../quantlibxl.hpp"

#include <oh/objecthandler.hpp>

using namespace node;
using namespace v8;
using namespace std;


class GaussianLHPLossmodelWorker {
  public:
    string mObjectID;
    double mCorrelation;
    std::vector<double> mRecoveryRates;

    string mReturnValue;

    string mError;

    GaussianLHPLossmodelWorker(
      string ObjectID
,       double Correlation
,       std::vector<double> RecoveryRates
     )
      {
        mObjectID = ObjectID;
        mCorrelation = Correlation;
        mRecoveryRates = RecoveryRates;
      };

    void Execute();
};

class IHGaussPoolLossModelWorker {
  public:
    string mObjectID;
    double mCorrelation;
    std::vector<double> mRecoveryRates;
    long mNumBuckets;

    string mReturnValue;

    string mError;

    IHGaussPoolLossModelWorker(
      string ObjectID
,       double Correlation
,       std::vector<double> RecoveryRates
,       long NumBuckets
     )
      {
        mObjectID = ObjectID;
        mCorrelation = Correlation;
        mRecoveryRates = RecoveryRates;
        mNumBuckets = NumBuckets;
      };

    void Execute();
};

class IHStudentPoolLossModelWorker {
  public:
    string mObjectID;
    double mCorrelation;
    std::vector<double> mRecoveryRates;
    std::vector<double> mTtraits;
    long mNumBuckets;

    string mReturnValue;

    string mError;

    IHStudentPoolLossModelWorker(
      string ObjectID
,       double Correlation
,       std::vector<double> RecoveryRates
,       std::vector<double> Ttraits
,       long NumBuckets
     )
      {
        mObjectID = ObjectID;
        mCorrelation = Correlation;
        mRecoveryRates = RecoveryRates;
        mTtraits = Ttraits;
        mNumBuckets = NumBuckets;
      };

    void Execute();
};

class GBinomialLossmodelWorker {
  public:
    string mObjectID;
    std::vector< std::vector<double> > mFactors;
    std::vector<double> mRecoveryRates;

    string mReturnValue;

    string mError;

    GBinomialLossmodelWorker(
      string ObjectID
,       std::vector< std::vector<double> > Factors
,       std::vector<double> RecoveryRates
     )
      {
        mObjectID = ObjectID;
        mFactors = Factors;
        mRecoveryRates = RecoveryRates;
      };

    void Execute();
};

class TBinomialLossmodelWorker {
  public:
    string mObjectID;
    std::vector< std::vector<double> > mFactors;
    std::vector<double> mRecoveryRates;
    std::vector<double> mTtraits;

    string mReturnValue;

    string mError;

    TBinomialLossmodelWorker(
      string ObjectID
,       std::vector< std::vector<double> > Factors
,       std::vector<double> RecoveryRates
,       std::vector<double> Ttraits
     )
      {
        mObjectID = ObjectID;
        mFactors = Factors;
        mRecoveryRates = RecoveryRates;
        mTtraits = Ttraits;
      };

    void Execute();
};

class BaseCorrelationLossModelWorker {
  public:
    string mObjectID;
    string mBaseModel;
    string mBaseCorrelationSurface;
    std::vector<double> mRecoveries;
    std::vector<double> mInitiTraits;

    string mReturnValue;

    string mError;

    BaseCorrelationLossModelWorker(
      string ObjectID
,       string BaseModel
,       string BaseCorrelationSurface
,       std::vector<double> Recoveries
,       std::vector<double> InitiTraits
     )
      {
        mObjectID = ObjectID;
        mBaseModel = BaseModel;
        mBaseCorrelationSurface = BaseCorrelationSurface;
        mRecoveries = Recoveries;
        mInitiTraits = InitiTraits;
      };

    void Execute();
};

class GMCLossModelWorker {
  public:
    string mObjectID;
    std::vector< std::vector<double> > mFactors;
    std::vector<double> mRecoveryRates;
    long mNumSimulations;

    string mReturnValue;

    string mError;

    GMCLossModelWorker(
      string ObjectID
,       std::vector< std::vector<double> > Factors
,       std::vector<double> RecoveryRates
,       long NumSimulations
     )
      {
        mObjectID = ObjectID;
        mFactors = Factors;
        mRecoveryRates = RecoveryRates;
        mNumSimulations = NumSimulations;
      };

    void Execute();
};

class GRandomRRMCLossModelWorker {
  public:
    string mObjectID;
    std::vector< std::vector<double> > mFactors;
    std::vector<double> mRecoveryRates;
    double mModelA;
    long mNumSimulations;

    string mReturnValue;

    string mError;

    GRandomRRMCLossModelWorker(
      string ObjectID
,       std::vector< std::vector<double> > Factors
,       std::vector<double> RecoveryRates
,       double ModelA
,       long NumSimulations
     )
      {
        mObjectID = ObjectID;
        mFactors = Factors;
        mRecoveryRates = RecoveryRates;
        mModelA = ModelA;
        mNumSimulations = NumSimulations;
      };

    void Execute();
};

class TMCLossModelWorker {
  public:
    string mObjectID;
    std::vector< std::vector<double> > mFactors;
    std::vector<double> mRecoveryRates;
    std::vector<double> mTtraits;
    long mNumSimulations;

    string mReturnValue;

    string mError;

    TMCLossModelWorker(
      string ObjectID
,       std::vector< std::vector<double> > Factors
,       std::vector<double> RecoveryRates
,       std::vector<double> Ttraits
,       long NumSimulations
     )
      {
        mObjectID = ObjectID;
        mFactors = Factors;
        mRecoveryRates = RecoveryRates;
        mTtraits = Ttraits;
        mNumSimulations = NumSimulations;
      };

    void Execute();
};

class TRandomRRMCLossModelWorker {
  public:
    string mObjectID;
    std::vector< std::vector<double> > mFactors;
    std::vector<double> mRecoveryRates;
    std::vector<double> mTtraits;
    double mModelA;
    long mNumSimulations;

    string mReturnValue;

    string mError;

    TRandomRRMCLossModelWorker(
      string ObjectID
,       std::vector< std::vector<double> > Factors
,       std::vector<double> RecoveryRates
,       std::vector<double> Ttraits
,       double ModelA
,       long NumSimulations
     )
      {
        mObjectID = ObjectID;
        mFactors = Factors;
        mRecoveryRates = RecoveryRates;
        mTtraits = Ttraits;
        mModelA = ModelA;
        mNumSimulations = NumSimulations;
      };

    void Execute();
};

class GSaddlePointLossmodelWorker {
  public:
    string mObjectID;
    std::vector< std::vector<double> > mFactors;
    std::vector<double> mRecoveryRates;

    string mReturnValue;

    string mError;

    GSaddlePointLossmodelWorker(
      string ObjectID
,       std::vector< std::vector<double> > Factors
,       std::vector<double> RecoveryRates
     )
      {
        mObjectID = ObjectID;
        mFactors = Factors;
        mRecoveryRates = RecoveryRates;
      };

    void Execute();
};

class TSaddlePointLossmodelWorker {
  public:
    string mObjectID;
    std::vector< std::vector<double> > mFactors;
    std::vector<double> mRecoveryRates;
    std::vector<double> mTtraits;

    string mReturnValue;

    string mError;

    TSaddlePointLossmodelWorker(
      string ObjectID
,       std::vector< std::vector<double> > Factors
,       std::vector<double> RecoveryRates
,       std::vector<double> Ttraits
     )
      {
        mObjectID = ObjectID;
        mFactors = Factors;
        mRecoveryRates = RecoveryRates;
        mTtraits = Ttraits;
      };

    void Execute();
};

class GRecursiveLossmodelWorker {
  public:
    string mObjectID;
    std::vector< std::vector<double> > mFactors;
    std::vector<double> mRecoveryRates;

    string mReturnValue;

    string mError;

    GRecursiveLossmodelWorker(
      string ObjectID
,       std::vector< std::vector<double> > Factors
,       std::vector<double> RecoveryRates
     )
      {
        mObjectID = ObjectID;
        mFactors = Factors;
        mRecoveryRates = RecoveryRates;
      };

    void Execute();
};
 
#endif
