/* 
  Copyright (C) 2016 -2017 Jerry Jin
*/

#ifndef marketmodelevolvers_h
#define marketmodelevolvers_h
#include <nan.h>
#include <string>
#include <queue>
#include <utility>

#include "../quantlibxl.hpp"

#include <oh/objecthandler.hpp>

using namespace node;
using namespace v8;
using namespace std;


class ForwardRatePcWorker {
  public:
    string mObjectID;
    string mMarketModel;
    string mBrownianGeneratorFactory;
    std::vector<long> mNumeraires;

    string mReturnValue;

    string mError;

    ForwardRatePcWorker(
      string ObjectID
,       string MarketModel
,       string BrownianGeneratorFactory
,       std::vector<long> Numeraires
     )
      {
        mObjectID = ObjectID;
        mMarketModel = MarketModel;
        mBrownianGeneratorFactory = BrownianGeneratorFactory;
        mNumeraires = Numeraires;
      };

    void Execute();
};

class ForwardRateIpcWorker {
  public:
    string mObjectID;
    string mMarketModel;
    string mBrownianGeneratorFactory;
    std::vector<long> mNumeraires;

    string mReturnValue;

    string mError;

    ForwardRateIpcWorker(
      string ObjectID
,       string MarketModel
,       string BrownianGeneratorFactory
,       std::vector<long> Numeraires
     )
      {
        mObjectID = ObjectID;
        mMarketModel = MarketModel;
        mBrownianGeneratorFactory = BrownianGeneratorFactory;
        mNumeraires = Numeraires;
      };

    void Execute();
};

class ForwardRateNormalPcWorker {
  public:
    string mObjectID;
    string mMarketModel;
    string mBrownianGeneratorFactory;
    std::vector<long> mNumeraires;

    string mReturnValue;

    string mError;

    ForwardRateNormalPcWorker(
      string ObjectID
,       string MarketModel
,       string BrownianGeneratorFactory
,       std::vector<long> Numeraires
     )
      {
        mObjectID = ObjectID;
        mMarketModel = MarketModel;
        mBrownianGeneratorFactory = BrownianGeneratorFactory;
        mNumeraires = Numeraires;
      };

    void Execute();
};

class MarketModelEvolverStartNewPathWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    MarketModelEvolverStartNewPathWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class MarketModelEvolverAdvanceStepWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    MarketModelEvolverAdvanceStepWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class MarketModelEvolverCurrentStepWorker {
  public:
    string mObjectID;

    long mReturnValue;

    string mError;

    MarketModelEvolverCurrentStepWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class MarketModelEvolverNumerairesWorker {
  public:
    string mObjectID;

    std::vector<long> mReturnValue;

    string mError;

    MarketModelEvolverNumerairesWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};
 
#endif
