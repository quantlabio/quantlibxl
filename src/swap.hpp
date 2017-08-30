/* 
  Copyright (C) 2016 -2017 Jerry Jin
*/

#ifndef swap_h
#define swap_h
#include <nan.h>
#include <string>
#include <queue>
#include <utility>

#include "../quantlibxl.hpp"

#include <oh/objecthandler.hpp>

using namespace node;
using namespace v8;
using namespace std;


class SwapWorker {
  public:
    string mObjectID;
    std::vector<string> mLegIDs;
    std::vector<bool> mPayer;

    string mReturnValue;

    string mError;

    SwapWorker(
      string ObjectID
,       std::vector<string> LegIDs
,       std::vector<bool> Payer
     )
      {
        mObjectID = ObjectID;
        mLegIDs = LegIDs;
        mPayer = Payer;
      };

    void Execute();
};

class MakeCmsWorker {
  public:
    string mObjectID;
    string mSwapTenor;
    string mSwapIndex;
    string mIborIndex;
    double mIborSpread;
    string mForwardStart;
    string mCmsCouponPricer;

    string mReturnValue;

    string mError;

    MakeCmsWorker(
      string ObjectID
,       string SwapTenor
,       string SwapIndex
,       string IborIndex
,       double IborSpread
,       string ForwardStart
,       string CmsCouponPricer
     )
      {
        mObjectID = ObjectID;
        mSwapTenor = SwapTenor;
        mSwapIndex = SwapIndex;
        mIborIndex = IborIndex;
        mIborSpread = IborSpread;
        mForwardStart = ForwardStart;
        mCmsCouponPricer = CmsCouponPricer;
      };

    void Execute();
};

class SwapLegBPSWorker {
  public:
    string mObjectID;
    long mLegNumber;

    double mReturnValue;

    string mError;

    SwapLegBPSWorker(
      string ObjectID
,       long LegNumber
     )
      {
        mObjectID = ObjectID;
        mLegNumber = LegNumber;
      };

    void Execute();
};

class SwapLegNPVWorker {
  public:
    string mObjectID;
    long mLegNumber;

    double mReturnValue;

    string mError;

    SwapLegNPVWorker(
      string ObjectID
,       long LegNumber
     )
      {
        mObjectID = ObjectID;
        mLegNumber = LegNumber;
      };

    void Execute();
};

class SwapStartDateWorker {
  public:
    string mObjectID;

    long mReturnValue;

    string mError;

    SwapStartDateWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class SwapMaturityDateWorker {
  public:
    string mObjectID;

    long mReturnValue;

    string mError;

    SwapMaturityDateWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class SwapLegAnalysisWorker {
  public:
    string mObjectID;
    long mLegNumber;
    ObjectHandler::property_t mAfterDate;

    std::vector< std::vector<string> > mReturnValue;

    string mError;

    SwapLegAnalysisWorker(
      string ObjectID
,       long LegNumber
,       ObjectHandler::property_t AfterDate
     )
      {
        mObjectID = ObjectID;
        mLegNumber = LegNumber;
        mAfterDate = AfterDate;
      };

    void Execute();
};
 
#endif
