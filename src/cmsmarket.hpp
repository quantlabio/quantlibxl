/* 
  Copyright (C) 2016 -2017 Jerry Jin
*/

#ifndef cmsmarket_h
#define cmsmarket_h
#include <nan.h>
#include <string>
#include <queue>
#include <utility>

#include "../quantlibxl.hpp"

#include <oh/objecthandler.hpp>

using namespace node;
using namespace v8;
using namespace std;


class CmsMarketWorker {
  public:
    string mObjectID;
    std::vector<ObjectHandler::property_t> mSwapLengths;
    std::vector<string> mSwapIndexes;
    string mIborIndex;
    std::vector< std::vector<ObjectHandler::property_t> > mBidAskSpreads;
    std::vector<string> mCmsCouponPricers;
    ObjectHandler::property_t mYieldCurve;

    string mReturnValue;

    string mError;

    CmsMarketWorker(
      string ObjectID
,       std::vector<ObjectHandler::property_t> SwapLengths
,       std::vector<string> SwapIndexes
,       string IborIndex
,       std::vector< std::vector<ObjectHandler::property_t> > BidAskSpreads
,       std::vector<string> CmsCouponPricers
,       ObjectHandler::property_t YieldCurve
     )
      {
        mObjectID = ObjectID;
        mSwapLengths = SwapLengths;
        mSwapIndexes = SwapIndexes;
        mIborIndex = IborIndex;
        mBidAskSpreads = BidAskSpreads;
        mCmsCouponPricers = CmsCouponPricers;
        mYieldCurve = YieldCurve;
      };

    void Execute();
};

class BrowseCmsMarketWorker {
  public:
    string mObjectID;

    std::vector< std::vector<string> > mReturnValue;

    string mError;

    BrowseCmsMarketWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};
 
#endif
