/* 
  Copyright (C) 2016 -2017 Jerry Jin
*/

#ifndef mathf_h
#define mathf_h
#include <nan.h>
#include <string>
#include <queue>
#include <utility>

#include "../quantlibxl.hpp"

#include <oh/objecthandler.hpp>

using namespace node;
using namespace v8;
using namespace std;


class SymmetricSchurDecompositionWorker {
  public:
    string mObjectID;
    std::vector< std::vector<double> > mSymmetricMatrix;

    string mReturnValue;

    string mError;

    SymmetricSchurDecompositionWorker(
      string ObjectID
,       std::vector< std::vector<double> > SymmetricMatrix
     )
      {
        mObjectID = ObjectID;
        mSymmetricMatrix = SymmetricMatrix;
      };

    void Execute();
};

class CovarianceDecompositionWorker {
  public:
    string mObjectID;
    std::vector< std::vector<double> > mSymmetricMatrix;
    double mTolerance;

    string mReturnValue;

    string mError;

    CovarianceDecompositionWorker(
      string ObjectID
,       std::vector< std::vector<double> > SymmetricMatrix
,       double Tolerance
     )
      {
        mObjectID = ObjectID;
        mSymmetricMatrix = SymmetricMatrix;
        mTolerance = Tolerance;
      };

    void Execute();
};

class SymmetricSchurDecompositionEigenvaluesWorker {
  public:
    string mObjectID;

    std::vector<double> mReturnValue;

    string mError;

    SymmetricSchurDecompositionEigenvaluesWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class SymmetricSchurDecompositionEigenvectorsWorker {
  public:
    string mObjectID;

    std::vector< std::vector<double> > mReturnValue;

    string mError;

    SymmetricSchurDecompositionEigenvectorsWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class CovarianceDecompositionVariancesWorker {
  public:
    string mObjectID;

    std::vector<double> mReturnValue;

    string mError;

    CovarianceDecompositionVariancesWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class CovarianceDecompositionStandardDeviationsWorker {
  public:
    string mObjectID;

    std::vector<double> mReturnValue;

    string mError;

    CovarianceDecompositionStandardDeviationsWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class CovarianceDecompositionCorrelationMatrixWorker {
  public:
    string mObjectID;

    std::vector< std::vector<double> > mReturnValue;

    string mError;

    CovarianceDecompositionCorrelationMatrixWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class PrimeNumberWorker {
  public:
    long mN;

    long mReturnValue;

    string mError;

    PrimeNumberWorker(
      long N
     )
      {
        mN = N;
      };

    void Execute();
};

class NormDistWorker {
  public:
    double mX;
    double mMean;
    double mStandard_dev;
    bool mCumulative;

    double mReturnValue;

    string mError;

    NormDistWorker(
      double X
,       double Mean
,       double Standard_dev
,       bool Cumulative
     )
      {
        mX = X;
        mMean = Mean;
        mStandard_dev = Standard_dev;
        mCumulative = Cumulative;
      };

    void Execute();
};

class NormSDistWorker {
  public:
    double mZ;

    double mReturnValue;

    string mError;

    NormSDistWorker(
      double Z
     )
      {
        mZ = Z;
      };

    void Execute();
};

class NormInvWorker {
  public:
    double mProbability;
    double mMean;
    double mStandard_dev;

    double mReturnValue;

    string mError;

    NormInvWorker(
      double Probability
,       double Mean
,       double Standard_dev
     )
      {
        mProbability = Probability;
        mMean = Mean;
        mStandard_dev = Standard_dev;
      };

    void Execute();
};

class NormSInvWorker {
  public:
    double mProbability;

    double mReturnValue;

    string mError;

    NormSInvWorker(
      double Probability
     )
      {
        mProbability = Probability;
      };

    void Execute();
};

class CholeskyDecompositionWorker {
  public:
    std::vector< std::vector<double> > mMatrix;
    bool mFlexible;

    std::vector< std::vector<double> > mReturnValue;

    string mError;

    CholeskyDecompositionWorker(
      std::vector< std::vector<double> > Matrix
,       bool Flexible
     )
      {
        mMatrix = Matrix;
        mFlexible = Flexible;
      };

    void Execute();
};

class PseudoSqrtWorker {
  public:
    std::vector< std::vector<double> > mMatrix;
    string mSalvagingAlgorithm;

    std::vector< std::vector<double> > mReturnValue;

    string mError;

    PseudoSqrtWorker(
      std::vector< std::vector<double> > Matrix
,       string SalvagingAlgorithm
     )
      {
        mMatrix = Matrix;
        mSalvagingAlgorithm = SalvagingAlgorithm;
      };

    void Execute();
};

class RankReducedSqrtWorker {
  public:
    std::vector< std::vector<double> > mMatrix;
    long mMaxRank;
    double mComponentPercentage;
    string mSalvagingAlgorithm;

    std::vector< std::vector<double> > mReturnValue;

    string mError;

    RankReducedSqrtWorker(
      std::vector< std::vector<double> > Matrix
,       long MaxRank
,       double ComponentPercentage
,       string SalvagingAlgorithm
     )
      {
        mMatrix = Matrix;
        mMaxRank = MaxRank;
        mComponentPercentage = ComponentPercentage;
        mSalvagingAlgorithm = SalvagingAlgorithm;
      };

    void Execute();
};

class GetCovarianceWorker {
  public:
    std::vector<double> mVols;
    std::vector< std::vector<double> > mMatrix;
    double mTolerance;

    std::vector< std::vector<double> > mReturnValue;

    string mError;

    GetCovarianceWorker(
      std::vector<double> Vols
,       std::vector< std::vector<double> > Matrix
,       double Tolerance
     )
      {
        mVols = Vols;
        mMatrix = Matrix;
        mTolerance = Tolerance;
      };

    void Execute();
};
 
#endif
