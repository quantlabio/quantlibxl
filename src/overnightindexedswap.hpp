/* 
  Copyright (C) 2016 -2017 Jerry Jin
*/

#ifndef overnightindexedswap_h
#define overnightindexedswap_h
#include <nan.h>
#include <string>
#include <queue>
#include <utility>

#include "../quantlibxl.hpp"

#include <oh/objecthandler.hpp>

using namespace node;
using namespace v8;
using namespace std;


class OvernightIndexedSwapWorker {
  public:
    string mObjectID;
    string mPayerReceiver;
    std::vector<double> mNominal;
    string mSchedule;
    double mFixedRate;
    string mFixDayCounter;
    string mOvernightIndex;
    double mSpread;

    string mReturnValue;

    string mError;

    OvernightIndexedSwapWorker(
      string ObjectID
,       string PayerReceiver
,       std::vector<double> Nominal
,       string Schedule
,       double FixedRate
,       string FixDayCounter
,       string OvernightIndex
,       double Spread
     )
      {
        mObjectID = ObjectID;
        mPayerReceiver = PayerReceiver;
        mNominal = Nominal;
        mSchedule = Schedule;
        mFixedRate = FixedRate;
        mFixDayCounter = FixDayCounter;
        mOvernightIndex = OvernightIndex;
        mSpread = Spread;
      };

    void Execute();
};

class MakeOISWorker {
  public:
    string mObjectID;
    ObjectHandler::property_t mSettlDays;
    string mSwapTenor;
    string mOvernightIndex;
    double mFixedRate;
    string mForwardStart;
    string mFixDayCounter;
    double mSpread;

    string mReturnValue;

    string mError;

    MakeOISWorker(
      string ObjectID
,       ObjectHandler::property_t SettlDays
,       string SwapTenor
,       string OvernightIndex
,       double FixedRate
,       string ForwardStart
,       string FixDayCounter
,       double Spread
     )
      {
        mObjectID = ObjectID;
        mSettlDays = SettlDays;
        mSwapTenor = SwapTenor;
        mOvernightIndex = OvernightIndex;
        mFixedRate = FixedRate;
        mForwardStart = ForwardStart;
        mFixDayCounter = FixDayCounter;
        mSpread = Spread;
      };

    void Execute();
};

class MakeDatedOISWorker {
  public:
    string mObjectID;
    ObjectHandler::property_t mStartDate;
    ObjectHandler::property_t mEndDate;
    string mOvernightIndex;
    double mFixedRate;
    string mFixDayCounter;
    double mSpread;

    string mReturnValue;

    string mError;

    MakeDatedOISWorker(
      string ObjectID
,       ObjectHandler::property_t StartDate
,       ObjectHandler::property_t EndDate
,       string OvernightIndex
,       double FixedRate
,       string FixDayCounter
,       double Spread
     )
      {
        mObjectID = ObjectID;
        mStartDate = StartDate;
        mEndDate = EndDate;
        mOvernightIndex = OvernightIndex;
        mFixedRate = FixedRate;
        mFixDayCounter = FixDayCounter;
        mSpread = Spread;
      };

    void Execute();
};

class OvernightIndexedSwapFromOISRateHelperWorker {
  public:
    string mObjectID;
    string mOISRateHelper;

    string mReturnValue;

    string mError;

    OvernightIndexedSwapFromOISRateHelperWorker(
      string ObjectID
,       string OISRateHelper
     )
      {
        mObjectID = ObjectID;
        mOISRateHelper = OISRateHelper;
      };

    void Execute();
};

class OvernightIndexedSwapFixedLegBPSWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    OvernightIndexedSwapFixedLegBPSWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class OvernightIndexedSwapFixedLegNPVWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    OvernightIndexedSwapFixedLegNPVWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class OvernightIndexedSwapFairRateWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    OvernightIndexedSwapFairRateWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class OvernightIndexedSwapOvernightLegBPSWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    OvernightIndexedSwapOvernightLegBPSWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class OvernightIndexedSwapOvernightLegNPVWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    OvernightIndexedSwapOvernightLegNPVWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class OvernightIndexedSwapFairSpreadWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    OvernightIndexedSwapFairSpreadWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class OvernightIndexedSwapTypeWorker {
  public:
    string mObjectID;

    string mReturnValue;

    string mError;

    OvernightIndexedSwapTypeWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class OvernightIndexedSwapNominalWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    OvernightIndexedSwapNominalWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class OvernightIndexedSwapFixedRateWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    OvernightIndexedSwapFixedRateWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class OvernightIndexedSwapFixedDayCountWorker {
  public:
    string mObjectID;

    string mReturnValue;

    string mError;

    OvernightIndexedSwapFixedDayCountWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class OvernightIndexedSwapSpreadWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    OvernightIndexedSwapSpreadWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class OvernightIndexedSwapFixedLegAnalysisWorker {
  public:
    string mObjectID;
    ObjectHandler::property_t mAfterDate;

    std::vector< std::vector<string> > mReturnValue;

    string mError;

    OvernightIndexedSwapFixedLegAnalysisWorker(
      string ObjectID
,       ObjectHandler::property_t AfterDate
     )
      {
        mObjectID = ObjectID;
        mAfterDate = AfterDate;
      };

    void Execute();
};

class OvernightIndexedSwapOvernightLegAnalysisWorker {
  public:
    string mObjectID;
    ObjectHandler::property_t mAfterDate;

    std::vector< std::vector<string> > mReturnValue;

    string mError;

    OvernightIndexedSwapOvernightLegAnalysisWorker(
      string ObjectID
,       ObjectHandler::property_t AfterDate
     )
      {
        mObjectID = ObjectID;
        mAfterDate = AfterDate;
      };

    void Execute();
};
 
#endif
