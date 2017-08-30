/* 
  Copyright (C) 2016 -2017 Jerry Jin
*/

#ifndef cmsmarketcalibration_h
#define cmsmarketcalibration_h
#include <nan.h>
#include <string>
#include <queue>
#include <utility>

#include "../quantlibxl.hpp"

#include <oh/objecthandler.hpp>

using namespace node;
using namespace v8;
using namespace std;


class CmsMarketCalibrationWorker {
  public:
    string mObjectID;
    ObjectHandler::property_t mVolCube;
    string mCmsMarket;
    std::vector< std::vector<double> > mWeights;
    string mCalibrationType;

    string mReturnValue;

    string mError;

    CmsMarketCalibrationWorker(
      string ObjectID
,       ObjectHandler::property_t VolCube
,       string CmsMarket
,       std::vector< std::vector<double> > Weights
,       string CalibrationType
     )
      {
        mObjectID = ObjectID;
        mVolCube = VolCube;
        mCmsMarket = CmsMarket;
        mWeights = Weights;
        mCalibrationType = CalibrationType;
      };

    void Execute();
};

class CmsMarketCalibrationComputeWorker {
  public:
    string mObjectID;
    string mEndCriteria;
    string mOptimizationMethod;
    std::vector<double> mGuess;
    bool mIsMeanRevFixed;

    std::vector<double> mReturnValue;

    string mError;

    CmsMarketCalibrationComputeWorker(
      string ObjectID
,       string EndCriteria
,       string OptimizationMethod
,       std::vector<double> Guess
,       bool IsMeanRevFixed
     )
      {
        mObjectID = ObjectID;
        mEndCriteria = EndCriteria;
        mOptimizationMethod = OptimizationMethod;
        mGuess = Guess;
        mIsMeanRevFixed = IsMeanRevFixed;
      };

    void Execute();
};

class CmsMarketCalibrationErrorWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    CmsMarketCalibrationErrorWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class CmsMarketCalibrationEndCriteriaWorker {
  public:
    string mObjectID;

    string mReturnValue;

    string mError;

    CmsMarketCalibrationEndCriteriaWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class CmsMarketCalibrationElapsedWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    CmsMarketCalibrationElapsedWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class CmsMarketCalibrationSparseSabrParametersWorker {
  public:
    string mObjectID;

    std::vector< std::vector<string> > mReturnValue;

    string mError;

    CmsMarketCalibrationSparseSabrParametersWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class CmsMarketCalibrationDenseSabrParametersWorker {
  public:
    string mObjectID;

    std::vector< std::vector<string> > mReturnValue;

    string mError;

    CmsMarketCalibrationDenseSabrParametersWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class SimultaneousCalibrationBrowseCmsMarketWorker {
  public:
    string mObjectID;

    std::vector< std::vector<string> > mReturnValue;

    string mError;

    SimultaneousCalibrationBrowseCmsMarketWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};
 
#endif
