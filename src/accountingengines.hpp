/* 
  Copyright (C) 2016 -2017 Jerry Jin
*/

#ifndef accountingengines_h
#define accountingengines_h
#include <nan.h>
#include <string>
#include <queue>
#include <utility>

#include "../quantlibxl.hpp"

#include <oh/objecthandler.hpp>

using namespace node;
using namespace v8;
using namespace std;


class AccountingEngineWorker {
  public:
    string mObjectID;
    string mMarketModelEvolver;
    string mProduct;
    double mInitialNumeraireValue;

    string mReturnValue;

    string mError;

    AccountingEngineWorker(
      string ObjectID
,       string MarketModelEvolver
,       string Product
,       double InitialNumeraireValue
     )
      {
        mObjectID = ObjectID;
        mMarketModelEvolver = MarketModelEvolver;
        mProduct = Product;
        mInitialNumeraireValue = InitialNumeraireValue;
      };

    void Execute();
};

class AccountingEngineMultiplePathValuesWorker {
  public:
    string mObjectID;
    string mSequenceStats;
    long mPaths;

    string mError;

    AccountingEngineMultiplePathValuesWorker(
      string ObjectID
,       string SequenceStats
,       long Paths
     )
      {
        mObjectID = ObjectID;
        mSequenceStats = SequenceStats;
        mPaths = Paths;
      };

    void Execute();
};
 
#endif
