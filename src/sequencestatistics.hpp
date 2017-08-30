/* 
  Copyright (C) 2016 -2017 Jerry Jin
*/

#ifndef sequencestatistics_h
#define sequencestatistics_h
#include <nan.h>
#include <string>
#include <queue>
#include <utility>

#include "../quantlibxl.hpp"

#include <oh/objecthandler.hpp>

using namespace node;
using namespace v8;
using namespace std;


class SequenceStatisticsWorker {
  public:
    string mObjectID;
    long mDimension;

    string mReturnValue;

    string mError;

    SequenceStatisticsWorker(
      string ObjectID
,       long Dimension
     )
      {
        mObjectID = ObjectID;
        mDimension = Dimension;
      };

    void Execute();
};

class SequenceStatistics2Worker {
  public:
    string mObjectID;
    long mDimension;
    std::vector< std::vector<double> > mValues;
    std::vector<double> mWeights;

    string mReturnValue;

    string mError;

    SequenceStatistics2Worker(
      string ObjectID
,       long Dimension
,       std::vector< std::vector<double> > Values
,       std::vector<double> Weights
     )
      {
        mObjectID = ObjectID;
        mDimension = Dimension;
        mValues = Values;
        mWeights = Weights;
      };

    void Execute();
};

class SequenceStatisticsIncWorker {
  public:
    string mObjectID;
    long mDimension;

    string mReturnValue;

    string mError;

    SequenceStatisticsIncWorker(
      string ObjectID
,       long Dimension
     )
      {
        mObjectID = ObjectID;
        mDimension = Dimension;
      };

    void Execute();
};

class SequenceStatisticsInc2Worker {
  public:
    string mObjectID;
    long mDimension;
    std::vector< std::vector<double> > mValues;
    std::vector<double> mWeights;

    string mReturnValue;

    string mError;

    SequenceStatisticsInc2Worker(
      string ObjectID
,       long Dimension
,       std::vector< std::vector<double> > Values
,       std::vector<double> Weights
     )
      {
        mObjectID = ObjectID;
        mDimension = Dimension;
        mValues = Values;
        mWeights = Weights;
      };

    void Execute();
};

class SequenceStatisticsSamplesWorker {
  public:
    string mObjectID;

    long mReturnValue;

    string mError;

    SequenceStatisticsSamplesWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class SequenceStatisticsWeightSumWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    SequenceStatisticsWeightSumWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class SequenceStatisticsMeanWorker {
  public:
    string mObjectID;

    std::vector<double> mReturnValue;

    string mError;

    SequenceStatisticsMeanWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class SequenceStatisticsVarianceWorker {
  public:
    string mObjectID;

    std::vector<double> mReturnValue;

    string mError;

    SequenceStatisticsVarianceWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class SequenceStatisticsStandardDeviationWorker {
  public:
    string mObjectID;

    std::vector<double> mReturnValue;

    string mError;

    SequenceStatisticsStandardDeviationWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class SequenceStatisticsDownsideVarianceWorker {
  public:
    string mObjectID;

    std::vector<double> mReturnValue;

    string mError;

    SequenceStatisticsDownsideVarianceWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class SequenceStatisticsDownsideDeviationWorker {
  public:
    string mObjectID;

    std::vector<double> mReturnValue;

    string mError;

    SequenceStatisticsDownsideDeviationWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class SequenceStatisticsSemiVarianceWorker {
  public:
    string mObjectID;

    std::vector<double> mReturnValue;

    string mError;

    SequenceStatisticsSemiVarianceWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class SequenceStatisticsSemiDeviationWorker {
  public:
    string mObjectID;

    std::vector<double> mReturnValue;

    string mError;

    SequenceStatisticsSemiDeviationWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class SequenceStatisticsErrorEstimateWorker {
  public:
    string mObjectID;

    std::vector<double> mReturnValue;

    string mError;

    SequenceStatisticsErrorEstimateWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class SequenceStatisticsSkewnessWorker {
  public:
    string mObjectID;

    std::vector<double> mReturnValue;

    string mError;

    SequenceStatisticsSkewnessWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class SequenceStatisticsKurtosisWorker {
  public:
    string mObjectID;

    std::vector<double> mReturnValue;

    string mError;

    SequenceStatisticsKurtosisWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class SequenceStatisticsMinWorker {
  public:
    string mObjectID;

    std::vector<double> mReturnValue;

    string mError;

    SequenceStatisticsMinWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class SequenceStatisticsMaxWorker {
  public:
    string mObjectID;

    std::vector<double> mReturnValue;

    string mError;

    SequenceStatisticsMaxWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class SequenceStatisticsGaussianPercentileWorker {
  public:
    string mObjectID;
    double mX;

    std::vector<double> mReturnValue;

    string mError;

    SequenceStatisticsGaussianPercentileWorker(
      string ObjectID
,       double X
     )
      {
        mObjectID = ObjectID;
        mX = X;
      };

    void Execute();
};

class SequenceStatisticsPercentileWorker {
  public:
    string mObjectID;
    double mX;

    std::vector<double> mReturnValue;

    string mError;

    SequenceStatisticsPercentileWorker(
      string ObjectID
,       double X
     )
      {
        mObjectID = ObjectID;
        mX = X;
      };

    void Execute();
};

class SequenceStatisticsGaussianPotentialUpsideWorker {
  public:
    string mObjectID;
    double mTarget;

    std::vector<double> mReturnValue;

    string mError;

    SequenceStatisticsGaussianPotentialUpsideWorker(
      string ObjectID
,       double Target
     )
      {
        mObjectID = ObjectID;
        mTarget = Target;
      };

    void Execute();
};

class SequenceStatisticsPotentialUpsideWorker {
  public:
    string mObjectID;
    double mCentile;

    std::vector<double> mReturnValue;

    string mError;

    SequenceStatisticsPotentialUpsideWorker(
      string ObjectID
,       double Centile
     )
      {
        mObjectID = ObjectID;
        mCentile = Centile;
      };

    void Execute();
};

class SequenceStatisticsGaussianValueAtRiskWorker {
  public:
    string mObjectID;
    double mTarget;

    std::vector<double> mReturnValue;

    string mError;

    SequenceStatisticsGaussianValueAtRiskWorker(
      string ObjectID
,       double Target
     )
      {
        mObjectID = ObjectID;
        mTarget = Target;
      };

    void Execute();
};

class SequenceStatisticsValueAtRiskWorker {
  public:
    string mObjectID;
    double mTarget;

    std::vector<double> mReturnValue;

    string mError;

    SequenceStatisticsValueAtRiskWorker(
      string ObjectID
,       double Target
     )
      {
        mObjectID = ObjectID;
        mTarget = Target;
      };

    void Execute();
};

class SequenceStatisticsRegretWorker {
  public:
    string mObjectID;
    double mTarget;

    std::vector<double> mReturnValue;

    string mError;

    SequenceStatisticsRegretWorker(
      string ObjectID
,       double Target
     )
      {
        mObjectID = ObjectID;
        mTarget = Target;
      };

    void Execute();
};

class SequenceStatisticsGaussianShortfallWorker {
  public:
    string mObjectID;
    double mTarget;

    std::vector<double> mReturnValue;

    string mError;

    SequenceStatisticsGaussianShortfallWorker(
      string ObjectID
,       double Target
     )
      {
        mObjectID = ObjectID;
        mTarget = Target;
      };

    void Execute();
};

class SequenceStatisticsShortfallWorker {
  public:
    string mObjectID;
    double mTarget;

    std::vector<double> mReturnValue;

    string mError;

    SequenceStatisticsShortfallWorker(
      string ObjectID
,       double Target
     )
      {
        mObjectID = ObjectID;
        mTarget = Target;
      };

    void Execute();
};

class SequenceStatisticsGaussianAverageShortfallWorker {
  public:
    string mObjectID;
    double mTarget;

    std::vector<double> mReturnValue;

    string mError;

    SequenceStatisticsGaussianAverageShortfallWorker(
      string ObjectID
,       double Target
     )
      {
        mObjectID = ObjectID;
        mTarget = Target;
      };

    void Execute();
};

class SequenceStatisticsAverageShortfallWorker {
  public:
    string mObjectID;
    double mTarget;

    std::vector<double> mReturnValue;

    string mError;

    SequenceStatisticsAverageShortfallWorker(
      string ObjectID
,       double Target
     )
      {
        mObjectID = ObjectID;
        mTarget = Target;
      };

    void Execute();
};

class SequenceStatisticsSizeWorker {
  public:
    string mObjectID;

    long mReturnValue;

    string mError;

    SequenceStatisticsSizeWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class SequenceStatisticsCovarianceWorker {
  public:
    string mObjectID;

    std::vector< std::vector<double> > mReturnValue;

    string mError;

    SequenceStatisticsCovarianceWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class SequenceStatisticsCorrelationWorker {
  public:
    string mObjectID;

    std::vector< std::vector<double> > mReturnValue;

    string mError;

    SequenceStatisticsCorrelationWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};
 
#endif
