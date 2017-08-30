/* 
  Copyright (C) 2016 -2017 Jerry Jin
*/

#ifndef btp_h
#define btp_h
#include <nan.h>
#include <string>
#include <queue>
#include <utility>

#include "../quantlibxl.hpp"

#include <oh/objecthandler.hpp>

using namespace node;
using namespace v8;
using namespace std;


class CCTEUWorker {
  public:
    string mObjectID;
    string mDescription;
    ObjectHandler::property_t mMaturityDate;
    double mSpread;
    ObjectHandler::property_t mFwdCurve;
    ObjectHandler::property_t mStartDate;
    ObjectHandler::property_t mIssueDate;

    string mReturnValue;

    string mError;

    CCTEUWorker(
      string ObjectID
,       string Description
,       ObjectHandler::property_t MaturityDate
,       double Spread
,       ObjectHandler::property_t FwdCurve
,       ObjectHandler::property_t StartDate
,       ObjectHandler::property_t IssueDate
     )
      {
        mObjectID = ObjectID;
        mDescription = Description;
        mMaturityDate = MaturityDate;
        mSpread = Spread;
        mFwdCurve = FwdCurve;
        mStartDate = StartDate;
        mIssueDate = IssueDate;
      };

    void Execute();
};

class BTPWorker {
  public:
    string mObjectID;
    string mDescription;
    ObjectHandler::property_t mMaturityDate;
    double mCoupon;
    ObjectHandler::property_t mStartDate;
    ObjectHandler::property_t mIssueDate;

    string mReturnValue;

    string mError;

    BTPWorker(
      string ObjectID
,       string Description
,       ObjectHandler::property_t MaturityDate
,       double Coupon
,       ObjectHandler::property_t StartDate
,       ObjectHandler::property_t IssueDate
     )
      {
        mObjectID = ObjectID;
        mDescription = Description;
        mMaturityDate = MaturityDate;
        mCoupon = Coupon;
        mStartDate = StartDate;
        mIssueDate = IssueDate;
      };

    void Execute();
};

class BTP2Worker {
  public:
    string mObjectID;
    string mDescription;
    ObjectHandler::property_t mMaturityDate;
    double mCoupon;
    double mRedemption;
    ObjectHandler::property_t mStartDate;
    ObjectHandler::property_t mIssueDate;

    string mReturnValue;

    string mError;

    BTP2Worker(
      string ObjectID
,       string Description
,       ObjectHandler::property_t MaturityDate
,       double Coupon
,       double Redemption
,       ObjectHandler::property_t StartDate
,       ObjectHandler::property_t IssueDate
     )
      {
        mObjectID = ObjectID;
        mDescription = Description;
        mMaturityDate = MaturityDate;
        mCoupon = Coupon;
        mRedemption = Redemption;
        mStartDate = StartDate;
        mIssueDate = IssueDate;
      };

    void Execute();
};

class RendistatoBasketWorker {
  public:
    string mObjectID;
    std::vector<string> mBTPs;
    std::vector<double> mOutstandings;
    std::vector<ObjectHandler::property_t> mPrices;

    string mReturnValue;

    string mError;

    RendistatoBasketWorker(
      string ObjectID
,       std::vector<string> BTPs
,       std::vector<double> Outstandings
,       std::vector<ObjectHandler::property_t> Prices
     )
      {
        mObjectID = ObjectID;
        mBTPs = BTPs;
        mOutstandings = Outstandings;
        mPrices = Prices;
      };

    void Execute();
};

class RendistatoCalculatorWorker {
  public:
    string mObjectID;
    string mRendistatoBasket;
    string mEuribor;
    ObjectHandler::property_t mYieldCurve;

    string mReturnValue;

    string mError;

    RendistatoCalculatorWorker(
      string ObjectID
,       string RendistatoBasket
,       string Euribor
,       ObjectHandler::property_t YieldCurve
     )
      {
        mObjectID = ObjectID;
        mRendistatoBasket = RendistatoBasket;
        mEuribor = Euribor;
        mYieldCurve = YieldCurve;
      };

    void Execute();
};

class RendistatoEquivalentSwapLengthQuoteWorker {
  public:
    string mObjectID;
    string mRendistatoCalculator;

    string mReturnValue;

    string mError;

    RendistatoEquivalentSwapLengthQuoteWorker(
      string ObjectID
,       string RendistatoCalculator
     )
      {
        mObjectID = ObjectID;
        mRendistatoCalculator = RendistatoCalculator;
      };

    void Execute();
};

class RendistatoEquivalentSwapSpreadQuoteWorker {
  public:
    string mObjectID;
    string mRendistatoCalculator;

    string mReturnValue;

    string mError;

    RendistatoEquivalentSwapSpreadQuoteWorker(
      string ObjectID
,       string RendistatoCalculator
     )
      {
        mObjectID = ObjectID;
        mRendistatoCalculator = RendistatoCalculator;
      };

    void Execute();
};

class RendistatoBasketSizeWorker {
  public:
    string mObjectID;

    long mReturnValue;

    string mError;

    RendistatoBasketSizeWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class RendistatoBasketOutstandingWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    RendistatoBasketOutstandingWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class RendistatoBasketOutstandingsWorker {
  public:
    string mObjectID;

    std::vector<double> mReturnValue;

    string mError;

    RendistatoBasketOutstandingsWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class RendistatoBasketWeightsWorker {
  public:
    string mObjectID;

    std::vector<double> mReturnValue;

    string mError;

    RendistatoBasketWeightsWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class RendistatoCalculatorYieldWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    RendistatoCalculatorYieldWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class RendistatoCalculatorDurationWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    RendistatoCalculatorDurationWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class RendistatoCalculatorYieldsWorker {
  public:
    string mObjectID;

    std::vector<double> mReturnValue;

    string mError;

    RendistatoCalculatorYieldsWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class RendistatoCalculatorDurationsWorker {
  public:
    string mObjectID;

    std::vector<double> mReturnValue;

    string mError;

    RendistatoCalculatorDurationsWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class RendistatoCalculatorSwapLengthsWorker {
  public:
    string mObjectID;

    std::vector<double> mReturnValue;

    string mError;

    RendistatoCalculatorSwapLengthsWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class RendistatoCalculatorSwapRatesWorker {
  public:
    string mObjectID;

    std::vector<double> mReturnValue;

    string mError;

    RendistatoCalculatorSwapRatesWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class RendistatoCalculatorSwapYieldsWorker {
  public:
    string mObjectID;

    std::vector<double> mReturnValue;

    string mError;

    RendistatoCalculatorSwapYieldsWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class RendistatoCalculatorSwapDurationsWorker {
  public:
    string mObjectID;

    std::vector<double> mReturnValue;

    string mError;

    RendistatoCalculatorSwapDurationsWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class RendistatoCalculatorEquivalentSwapRateWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    RendistatoCalculatorEquivalentSwapRateWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class RendistatoCalculatorEquivalentSwapYieldWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    RendistatoCalculatorEquivalentSwapYieldWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class RendistatoCalculatorEquivalentSwapDurationWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    RendistatoCalculatorEquivalentSwapDurationWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class RendistatoCalculatorEquivalentSwapSpreadWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    RendistatoCalculatorEquivalentSwapSpreadWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class RendistatoCalculatorEquivalentSwapLengthWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    RendistatoCalculatorEquivalentSwapLengthWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};
 
#endif
