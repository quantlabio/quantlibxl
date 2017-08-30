/* 
  Copyright (C) 2016 -2017 Jerry Jin
*/

#ifndef products_h
#define products_h
#include <nan.h>
#include <string>
#include <queue>
#include <utility>

#include "../quantlibxl.hpp"

#include <oh/objecthandler.hpp>

using namespace node;
using namespace v8;
using namespace std;


class MarketModelMultiProductCompositeWorker {
  public:
    string mObjectID;

    string mReturnValue;

    string mError;

    MarketModelMultiProductCompositeWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class MarketModelOneStepForwardsWorker {
  public:
    string mObjectID;
    std::vector<double> mRateTimes;
    std::vector<double> mAccruals;
    std::vector<double> mPaymentTimes;
    std::vector<double> mStrikes;

    string mReturnValue;

    string mError;

    MarketModelOneStepForwardsWorker(
      string ObjectID
,       std::vector<double> RateTimes
,       std::vector<double> Accruals
,       std::vector<double> PaymentTimes
,       std::vector<double> Strikes
     )
      {
        mObjectID = ObjectID;
        mRateTimes = RateTimes;
        mAccruals = Accruals;
        mPaymentTimes = PaymentTimes;
        mStrikes = Strikes;
      };

    void Execute();
};

class MarketModelMultiStepRatchetWorker {
  public:
    string mObjectID;
    std::vector<double> mRateTimes;
    std::vector<double> mAccruals;
    std::vector<double> mPaymentTimes;
    double mGearingOfFloor;
    double mGearingOfFixing;
    double mSpreadOfFloor;
    double mSpreadOfFixing;
    double mInitialFloor;
    bool mPayer;

    string mReturnValue;

    string mError;

    MarketModelMultiStepRatchetWorker(
      string ObjectID
,       std::vector<double> RateTimes
,       std::vector<double> Accruals
,       std::vector<double> PaymentTimes
,       double GearingOfFloor
,       double GearingOfFixing
,       double SpreadOfFloor
,       double SpreadOfFixing
,       double InitialFloor
,       bool Payer
     )
      {
        mObjectID = ObjectID;
        mRateTimes = RateTimes;
        mAccruals = Accruals;
        mPaymentTimes = PaymentTimes;
        mGearingOfFloor = GearingOfFloor;
        mGearingOfFixing = GearingOfFixing;
        mSpreadOfFloor = SpreadOfFloor;
        mSpreadOfFixing = SpreadOfFixing;
        mInitialFloor = InitialFloor;
        mPayer = Payer;
      };

    void Execute();
};

class MarketModelOneStepOptionletsWorker {
  public:
    string mObjectID;
    std::vector<double> mRateTimes;
    std::vector<double> mAccruals;
    std::vector<double> mPaymentTimes;
    std::vector<string> mPayoffs;

    string mReturnValue;

    string mError;

    MarketModelOneStepOptionletsWorker(
      string ObjectID
,       std::vector<double> RateTimes
,       std::vector<double> Accruals
,       std::vector<double> PaymentTimes
,       std::vector<string> Payoffs
     )
      {
        mObjectID = ObjectID;
        mRateTimes = RateTimes;
        mAccruals = Accruals;
        mPaymentTimes = PaymentTimes;
        mPayoffs = Payoffs;
      };

    void Execute();
};

class MarketModelMultiProductCompositeAddWorker {
  public:
    string mObjectID;
    string mProduct;

    string mError;

    MarketModelMultiProductCompositeAddWorker(
      string ObjectID
,       string Product
     )
      {
        mObjectID = ObjectID;
        mProduct = Product;
      };

    void Execute();
};

class MarketModelMultiProductCompositeFinalizeWorker {
  public:
    string mObjectID;

    string mError;

    MarketModelMultiProductCompositeFinalizeWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class MarketModelMultiProductSuggestedNumerairesWorker {
  public:
    string mObjectID;

    std::vector<long> mReturnValue;

    string mError;

    MarketModelMultiProductSuggestedNumerairesWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class MarketModelMultiProductPossibleCashFlowTimesWorker {
  public:
    string mObjectID;

    std::vector<double> mReturnValue;

    string mError;

    MarketModelMultiProductPossibleCashFlowTimesWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class MarketModelMultiProductNumberOfProductsWorker {
  public:
    string mObjectID;

    long mReturnValue;

    string mError;

    MarketModelMultiProductNumberOfProductsWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class MarketModelMultiProductMaxNumberOfCashFlowsPerProductPerStepWorker {
  public:
    string mObjectID;

    long mReturnValue;

    string mError;

    MarketModelMultiProductMaxNumberOfCashFlowsPerProductPerStepWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};
 
#endif
