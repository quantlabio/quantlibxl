/* 
  Copyright (C) 2016 -2017 Jerry Jin
*/

#ifndef defaultbasket_h
#define defaultbasket_h
#include <nan.h>
#include <string>
#include <queue>
#include <utility>

#include "../quantlibxl.hpp"

#include <oh/objecthandler.hpp>

using namespace node;
using namespace v8;
using namespace std;


class CreditBasketWorker {
  public:
    string mObjectID;
    std::vector<string> mIssuerNames;
    std::vector<string> mIssuers;
    std::vector<double> mNotionals;
    ObjectHandler::property_t mReferenceDate;
    double mAttachmentRatio;
    double mDettachmentRatio;
    bool mAmortizing;

    string mReturnValue;

    string mError;

    CreditBasketWorker(
      string ObjectID
,       std::vector<string> IssuerNames
,       std::vector<string> Issuers
,       std::vector<double> Notionals
,       ObjectHandler::property_t ReferenceDate
,       double AttachmentRatio
,       double DettachmentRatio
,       bool Amortizing
     )
      {
        mObjectID = ObjectID;
        mIssuerNames = IssuerNames;
        mIssuers = Issuers;
        mNotionals = Notionals;
        mReferenceDate = ReferenceDate;
        mAttachmentRatio = AttachmentRatio;
        mDettachmentRatio = DettachmentRatio;
        mAmortizing = Amortizing;
      };

    void Execute();
};

class CreditBasketSetLossModelWorker {
  public:
    string mObjectID;
    string mDefaultLossModel;

    string mError;

    CreditBasketSetLossModelWorker(
      string ObjectID
,       string DefaultLossModel
     )
      {
        mObjectID = ObjectID;
        mDefaultLossModel = DefaultLossModel;
      };

    void Execute();
};

class CreditBasketSizeWorker {
  public:
    string mObjectID;

    long mReturnValue;

    string mError;

    CreditBasketSizeWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class CreditBasketLiveNotionalWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    CreditBasketLiveNotionalWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class CreditBasketLossWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    CreditBasketLossWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class CreditBasketAttachLiveWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    CreditBasketAttachLiveWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class CreditBasketDetachLiveWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    CreditBasketDetachLiveWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class ExpectedTrancheLossWorker {
  public:
    string mObjectID;
    ObjectHandler::property_t mDateForLoss;

    double mReturnValue;

    string mError;

    ExpectedTrancheLossWorker(
      string ObjectID
,       ObjectHandler::property_t DateForLoss
     )
      {
        mObjectID = ObjectID;
        mDateForLoss = DateForLoss;
      };

    void Execute();
};

class CreditBasketPercentileWorker {
  public:
    string mObjectID;
    ObjectHandler::property_t mDateForLoss;
    double mPercentileValue;

    double mReturnValue;

    string mError;

    CreditBasketPercentileWorker(
      string ObjectID
,       ObjectHandler::property_t DateForLoss
,       double PercentileValue
     )
      {
        mObjectID = ObjectID;
        mDateForLoss = DateForLoss;
        mPercentileValue = PercentileValue;
      };

    void Execute();
};

class CreditBasketESFWorker {
  public:
    string mObjectID;
    ObjectHandler::property_t mDateForLoss;
    double mPercentileValue;

    double mReturnValue;

    string mError;

    CreditBasketESFWorker(
      string ObjectID
,       ObjectHandler::property_t DateForLoss
,       double PercentileValue
     )
      {
        mObjectID = ObjectID;
        mDateForLoss = DateForLoss;
        mPercentileValue = PercentileValue;
      };

    void Execute();
};

class CreditBasketNthEventPWorker {
  public:
    string mObjectID;
    long mEventOrder;
    ObjectHandler::property_t mDateForLoss;

    std::vector<double> mReturnValue;

    string mError;

    CreditBasketNthEventPWorker(
      string ObjectID
,       long EventOrder
,       ObjectHandler::property_t DateForLoss
     )
      {
        mObjectID = ObjectID;
        mEventOrder = EventOrder;
        mDateForLoss = DateForLoss;
      };

    void Execute();
};

class CreditBasketProbLossWorker {
  public:
    string mObjectID;
    ObjectHandler::property_t mDateForLoss;
    double mLossFractionValue;

    double mReturnValue;

    string mError;

    CreditBasketProbLossWorker(
      string ObjectID
,       ObjectHandler::property_t DateForLoss
,       double LossFractionValue
     )
      {
        mObjectID = ObjectID;
        mDateForLoss = DateForLoss;
        mLossFractionValue = LossFractionValue;
      };

    void Execute();
};

class CreditBasketSplitLossWorker {
  public:
    string mObjectID;
    ObjectHandler::property_t mDateForLoss;
    double mLossValue;

    std::vector<double> mReturnValue;

    string mError;

    CreditBasketSplitLossWorker(
      string ObjectID
,       ObjectHandler::property_t DateForLoss
,       double LossValue
     )
      {
        mObjectID = ObjectID;
        mDateForLoss = DateForLoss;
        mLossValue = LossValue;
      };

    void Execute();
};

class CreditBasketDefaulCorrelWorker {
  public:
    string mObjectID;
    ObjectHandler::property_t mDateCorrel;
    long mIndexIssuer1;
    long mIndexIssuer2;

    double mReturnValue;

    string mError;

    CreditBasketDefaulCorrelWorker(
      string ObjectID
,       ObjectHandler::property_t DateCorrel
,       long IndexIssuer1
,       long IndexIssuer2
     )
      {
        mObjectID = ObjectID;
        mDateCorrel = DateCorrel;
        mIndexIssuer1 = IndexIssuer1;
        mIndexIssuer2 = IndexIssuer2;
      };

    void Execute();
};
 
#endif
