/* 
  Copyright (C) 2016 -2017 Jerry Jin
*/

#ifndef statistics_h
#define statistics_h
#include <nan.h>
#include <string>
#include <queue>
#include <utility>

#include "../quantlibxl.hpp"

#include <oh/objecthandler.hpp>

using namespace node;
using namespace v8;
using namespace std;


class StatisticsWorker {
  public:
    string mObjectID;
    std::vector<double> mValues;
    std::vector<double> mWeights;

    string mReturnValue;

    string mError;

    StatisticsWorker(
      string ObjectID
,       std::vector<double> Values
,       std::vector<double> Weights
     )
      {
        mObjectID = ObjectID;
        mValues = Values;
        mWeights = Weights;
      };

    void Execute();
};

class IncrementalStatisticsWorker {
  public:
    string mObjectID;
    std::vector<double> mValues;
    std::vector<double> mWeights;

    string mReturnValue;

    string mError;

    IncrementalStatisticsWorker(
      string ObjectID
,       std::vector<double> Values
,       std::vector<double> Weights
     )
      {
        mObjectID = ObjectID;
        mValues = Values;
        mWeights = Weights;
      };

    void Execute();
};

class StatisticsSamplesWorker {
  public:
    string mObjectID;

    long mReturnValue;

    string mError;

    StatisticsSamplesWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class StatisticsWeightSumWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    StatisticsWeightSumWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class StatisticsMeanWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    StatisticsMeanWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class StatisticsVarianceWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    StatisticsVarianceWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class StatisticsStandardDeviationWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    StatisticsStandardDeviationWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class StatisticsErrorEstimateWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    StatisticsErrorEstimateWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class StatisticsSkewnessWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    StatisticsSkewnessWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class StatisticsKurtosisWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    StatisticsKurtosisWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class StatisticsMinWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    StatisticsMinWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class StatisticsMaxWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    StatisticsMaxWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class StatisticsPercentileWorker {
  public:
    string mObjectID;
    double mX;

    double mReturnValue;

    string mError;

    StatisticsPercentileWorker(
      string ObjectID
,       double X
     )
      {
        mObjectID = ObjectID;
        mX = X;
      };

    void Execute();
};

class StatisticsTopPercentileWorker {
  public:
    string mObjectID;
    double mX;

    double mReturnValue;

    string mError;

    StatisticsTopPercentileWorker(
      string ObjectID
,       double X
     )
      {
        mObjectID = ObjectID;
        mX = X;
      };

    void Execute();
};

class StatisticsGaussianDownsideVarianceWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    StatisticsGaussianDownsideVarianceWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class StatisticsGaussianDownsideDeviationWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    StatisticsGaussianDownsideDeviationWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class StatisticsGaussianRegretWorker {
  public:
    string mObjectID;
    double mTarget;

    double mReturnValue;

    string mError;

    StatisticsGaussianRegretWorker(
      string ObjectID
,       double Target
     )
      {
        mObjectID = ObjectID;
        mTarget = Target;
      };

    void Execute();
};

class StatisticsGaussianPercentileWorker {
  public:
    string mObjectID;
    double mX;

    double mReturnValue;

    string mError;

    StatisticsGaussianPercentileWorker(
      string ObjectID
,       double X
     )
      {
        mObjectID = ObjectID;
        mX = X;
      };

    void Execute();
};

class StatisticsGaussianTopPercentileWorker {
  public:
    string mObjectID;
    double mX;

    double mReturnValue;

    string mError;

    StatisticsGaussianTopPercentileWorker(
      string ObjectID
,       double X
     )
      {
        mObjectID = ObjectID;
        mX = X;
      };

    void Execute();
};

class StatisticsGaussianPotentialUpsideWorker {
  public:
    string mObjectID;
    double mTarget;

    double mReturnValue;

    string mError;

    StatisticsGaussianPotentialUpsideWorker(
      string ObjectID
,       double Target
     )
      {
        mObjectID = ObjectID;
        mTarget = Target;
      };

    void Execute();
};

class StatisticsGaussianValueAtRiskWorker {
  public:
    string mObjectID;
    double mTarget;

    double mReturnValue;

    string mError;

    StatisticsGaussianValueAtRiskWorker(
      string ObjectID
,       double Target
     )
      {
        mObjectID = ObjectID;
        mTarget = Target;
      };

    void Execute();
};

class StatisticsGaussianExpectedShortfallWorker {
  public:
    string mObjectID;
    double mTarget;

    double mReturnValue;

    string mError;

    StatisticsGaussianExpectedShortfallWorker(
      string ObjectID
,       double Target
     )
      {
        mObjectID = ObjectID;
        mTarget = Target;
      };

    void Execute();
};

class StatisticsGaussianShortfallWorker {
  public:
    string mObjectID;
    double mTarget;

    double mReturnValue;

    string mError;

    StatisticsGaussianShortfallWorker(
      string ObjectID
,       double Target
     )
      {
        mObjectID = ObjectID;
        mTarget = Target;
      };

    void Execute();
};

class StatisticsGaussianAverageShortfallWorker {
  public:
    string mObjectID;
    double mTarget;

    double mReturnValue;

    string mError;

    StatisticsGaussianAverageShortfallWorker(
      string ObjectID
,       double Target
     )
      {
        mObjectID = ObjectID;
        mTarget = Target;
      };

    void Execute();
};

class StatisticsSemiVarianceWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    StatisticsSemiVarianceWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class StatisticsSemiDeviationWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    StatisticsSemiDeviationWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class StatisticsDownsideVarianceWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    StatisticsDownsideVarianceWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class StatisticsDownsideDeviationWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    StatisticsDownsideDeviationWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class StatisticsRegretWorker {
  public:
    string mObjectID;
    double mTarget;

    double mReturnValue;

    string mError;

    StatisticsRegretWorker(
      string ObjectID
,       double Target
     )
      {
        mObjectID = ObjectID;
        mTarget = Target;
      };

    void Execute();
};

class StatisticsPotentialUpsideWorker {
  public:
    string mObjectID;
    double mCentile;

    double mReturnValue;

    string mError;

    StatisticsPotentialUpsideWorker(
      string ObjectID
,       double Centile
     )
      {
        mObjectID = ObjectID;
        mCentile = Centile;
      };

    void Execute();
};

class StatisticsValueAtRiskWorker {
  public:
    string mObjectID;
    double mTarget;

    double mReturnValue;

    string mError;

    StatisticsValueAtRiskWorker(
      string ObjectID
,       double Target
     )
      {
        mObjectID = ObjectID;
        mTarget = Target;
      };

    void Execute();
};

class StatisticsExpectedShortfallWorker {
  public:
    string mObjectID;
    double mCentile;

    double mReturnValue;

    string mError;

    StatisticsExpectedShortfallWorker(
      string ObjectID
,       double Centile
     )
      {
        mObjectID = ObjectID;
        mCentile = Centile;
      };

    void Execute();
};

class StatisticsShortfallWorker {
  public:
    string mObjectID;
    double mTarget;

    double mReturnValue;

    string mError;

    StatisticsShortfallWorker(
      string ObjectID
,       double Target
     )
      {
        mObjectID = ObjectID;
        mTarget = Target;
      };

    void Execute();
};

class StatisticsAverageShortfallWorker {
  public:
    string mObjectID;
    double mTarget;

    double mReturnValue;

    string mError;

    StatisticsAverageShortfallWorker(
      string ObjectID
,       double Target
     )
      {
        mObjectID = ObjectID;
        mTarget = Target;
      };

    void Execute();
};

class GaussianDownsideVarianceWorker {
  public:
    double mMean;
    double mStdDev;

    double mReturnValue;

    string mError;

    GaussianDownsideVarianceWorker(
      double Mean
,       double StdDev
     )
      {
        mMean = Mean;
        mStdDev = StdDev;
      };

    void Execute();
};

class GaussianDownsideDeviationWorker {
  public:
    double mMean;
    double mStdDev;

    double mReturnValue;

    string mError;

    GaussianDownsideDeviationWorker(
      double Mean
,       double StdDev
     )
      {
        mMean = Mean;
        mStdDev = StdDev;
      };

    void Execute();
};

class GaussianRegretWorker {
  public:
    double mTarget;
    double mMean;
    double mStdDev;

    double mReturnValue;

    string mError;

    GaussianRegretWorker(
      double Target
,       double Mean
,       double StdDev
     )
      {
        mTarget = Target;
        mMean = Mean;
        mStdDev = StdDev;
      };

    void Execute();
};

class GaussianPercentileWorker {
  public:
    double mX;
    double mMean;
    double mStdDev;

    double mReturnValue;

    string mError;

    GaussianPercentileWorker(
      double X
,       double Mean
,       double StdDev
     )
      {
        mX = X;
        mMean = Mean;
        mStdDev = StdDev;
      };

    void Execute();
};

class GaussianTopPercentileWorker {
  public:
    double mX;
    double mMean;
    double mStdDev;

    double mReturnValue;

    string mError;

    GaussianTopPercentileWorker(
      double X
,       double Mean
,       double StdDev
     )
      {
        mX = X;
        mMean = Mean;
        mStdDev = StdDev;
      };

    void Execute();
};

class GaussianPotentialUpsideWorker {
  public:
    double mTarget;
    double mMean;
    double mStdDev;

    double mReturnValue;

    string mError;

    GaussianPotentialUpsideWorker(
      double Target
,       double Mean
,       double StdDev
     )
      {
        mTarget = Target;
        mMean = Mean;
        mStdDev = StdDev;
      };

    void Execute();
};

class GaussianValueAtRiskWorker {
  public:
    double mTarget;
    double mMean;
    double mStdDev;

    double mReturnValue;

    string mError;

    GaussianValueAtRiskWorker(
      double Target
,       double Mean
,       double StdDev
     )
      {
        mTarget = Target;
        mMean = Mean;
        mStdDev = StdDev;
      };

    void Execute();
};

class GaussianExpectedShortfallWorker {
  public:
    double mTarget;
    double mMean;
    double mStdDev;

    double mReturnValue;

    string mError;

    GaussianExpectedShortfallWorker(
      double Target
,       double Mean
,       double StdDev
     )
      {
        mTarget = Target;
        mMean = Mean;
        mStdDev = StdDev;
      };

    void Execute();
};

class GaussianShortfallWorker {
  public:
    double mTarget;
    double mMean;
    double mStdDev;

    double mReturnValue;

    string mError;

    GaussianShortfallWorker(
      double Target
,       double Mean
,       double StdDev
     )
      {
        mTarget = Target;
        mMean = Mean;
        mStdDev = StdDev;
      };

    void Execute();
};

class GaussianAverageShortfallWorker {
  public:
    double mTarget;
    double mMean;
    double mStdDev;

    double mReturnValue;

    string mError;

    GaussianAverageShortfallWorker(
      double Target
,       double Mean
,       double StdDev
     )
      {
        mTarget = Target;
        mMean = Mean;
        mStdDev = StdDev;
      };

    void Execute();
};
 
#endif
