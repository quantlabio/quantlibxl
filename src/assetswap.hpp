/* 
  Copyright (C) 2016 -2017 Jerry Jin
*/

#ifndef assetswap_h
#define assetswap_h
#include <nan.h>
#include <string>
#include <queue>
#include <utility>

#include "../quantlibxl.hpp"

#include <oh/objecthandler.hpp>

using namespace node;
using namespace v8;
using namespace std;


class AssetSwapWorker {
  public:
    string mObjectID;
    bool mPayBondCoupon;
    string mBond;
    double mCleanPrice;
    string mIborIndex;
    double mSpread;
    string mFloatingLegSchedule;
    string mFloatingLegDayCounter;
    bool mParAssetSwap;

    string mReturnValue;

    string mError;

    AssetSwapWorker(
      string ObjectID
,       bool PayBondCoupon
,       string Bond
,       double CleanPrice
,       string IborIndex
,       double Spread
,       string FloatingLegSchedule
,       string FloatingLegDayCounter
,       bool ParAssetSwap
     )
      {
        mObjectID = ObjectID;
        mPayBondCoupon = PayBondCoupon;
        mBond = Bond;
        mCleanPrice = CleanPrice;
        mIborIndex = IborIndex;
        mSpread = Spread;
        mFloatingLegSchedule = FloatingLegSchedule;
        mFloatingLegDayCounter = FloatingLegDayCounter;
        mParAssetSwap = ParAssetSwap;
      };

    void Execute();
};

class AssetSwap2Worker {
  public:
    string mObjectID;
    bool mParAssetSwap;
    string mBond;
    double mCleanPrice;
    double mNonParRepayment;
    double mGearing;
    string mIborIndex;
    double mSpread;
    string mFloatingLegDayCounter;
    ObjectHandler::property_t mDealMaturity;
    bool mPayBondCoupon;

    string mReturnValue;

    string mError;

    AssetSwap2Worker(
      string ObjectID
,       bool ParAssetSwap
,       string Bond
,       double CleanPrice
,       double NonParRepayment
,       double Gearing
,       string IborIndex
,       double Spread
,       string FloatingLegDayCounter
,       ObjectHandler::property_t DealMaturity
,       bool PayBondCoupon
     )
      {
        mObjectID = ObjectID;
        mParAssetSwap = ParAssetSwap;
        mBond = Bond;
        mCleanPrice = CleanPrice;
        mNonParRepayment = NonParRepayment;
        mGearing = Gearing;
        mIborIndex = IborIndex;
        mSpread = Spread;
        mFloatingLegDayCounter = FloatingLegDayCounter;
        mDealMaturity = DealMaturity;
        mPayBondCoupon = PayBondCoupon;
      };

    void Execute();
};

class AssetSwapBondLegAnalysisWorker {
  public:
    string mObjectID;
    ObjectHandler::property_t mAfterDate;

    std::vector< std::vector<string> > mReturnValue;

    string mError;

    AssetSwapBondLegAnalysisWorker(
      string ObjectID
,       ObjectHandler::property_t AfterDate
     )
      {
        mObjectID = ObjectID;
        mAfterDate = AfterDate;
      };

    void Execute();
};

class AssetSwapFloatingLegAnalysisWorker {
  public:
    string mObjectID;
    ObjectHandler::property_t mAfterDate;

    std::vector< std::vector<string> > mReturnValue;

    string mError;

    AssetSwapFloatingLegAnalysisWorker(
      string ObjectID
,       ObjectHandler::property_t AfterDate
     )
      {
        mObjectID = ObjectID;
        mAfterDate = AfterDate;
      };

    void Execute();
};

class AssetSwapFairSpreadWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    AssetSwapFairSpreadWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class AssetSwapFloatingLegBPSWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    AssetSwapFloatingLegBPSWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class AssetSwapFairCleanPriceWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    AssetSwapFairCleanPriceWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class AssetSwapFairNonParRepaymentWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    AssetSwapFairNonParRepaymentWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class AssetSwapParSwapWorker {
  public:
    string mObjectID;

    bool mReturnValue;

    string mError;

    AssetSwapParSwapWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class AssetSwapPayBondCouponWorker {
  public:
    string mObjectID;

    bool mReturnValue;

    string mError;

    AssetSwapPayBondCouponWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};
 
#endif
