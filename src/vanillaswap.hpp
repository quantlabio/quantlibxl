/* 
  Copyright (C) 2016 -2017 Jerry Jin
*/

#ifndef vanillaswap_h
#define vanillaswap_h
#include <nan.h>
#include <string>
#include <queue>
#include <utility>

#include "../quantlibxl.hpp"

#include <oh/objecthandler.hpp>

using namespace node;
using namespace v8;
using namespace std;


class VanillaSwapWorker {
  public:
    string mObjectID;
    string mPayerReceiver;
    double mNominal;
    string mFixSchedule;
    double mFixedRate;
    string mFixDayCounter;
    string mFloatingLegSchedule;
    string mIborIndex;
    double mSpread;
    string mFloatingLegDayCounter;
    string mPaymentConvention;

    string mReturnValue;

    string mError;

    VanillaSwapWorker(
      string ObjectID
,       string PayerReceiver
,       double Nominal
,       string FixSchedule
,       double FixedRate
,       string FixDayCounter
,       string FloatingLegSchedule
,       string IborIndex
,       double Spread
,       string FloatingLegDayCounter
,       string PaymentConvention
     )
      {
        mObjectID = ObjectID;
        mPayerReceiver = PayerReceiver;
        mNominal = Nominal;
        mFixSchedule = FixSchedule;
        mFixedRate = FixedRate;
        mFixDayCounter = FixDayCounter;
        mFloatingLegSchedule = FloatingLegSchedule;
        mIborIndex = IborIndex;
        mSpread = Spread;
        mFloatingLegDayCounter = FloatingLegDayCounter;
        mPaymentConvention = PaymentConvention;
      };

    void Execute();
};

class MakeVanillaSwapWorker {
  public:
    string mObjectID;
    ObjectHandler::property_t mSettlDays;
    string mSwapTenor;
    string mIborIndex;
    double mFixedRate;
    string mForwardStart;
    string mFixDayCounter;
    double mSpread;
    string mPricingEngineID;

    string mReturnValue;

    string mError;

    MakeVanillaSwapWorker(
      string ObjectID
,       ObjectHandler::property_t SettlDays
,       string SwapTenor
,       string IborIndex
,       double FixedRate
,       string ForwardStart
,       string FixDayCounter
,       double Spread
,       string PricingEngineID
     )
      {
        mObjectID = ObjectID;
        mSettlDays = SettlDays;
        mSwapTenor = SwapTenor;
        mIborIndex = IborIndex;
        mFixedRate = FixedRate;
        mForwardStart = ForwardStart;
        mFixDayCounter = FixDayCounter;
        mSpread = Spread;
        mPricingEngineID = PricingEngineID;
      };

    void Execute();
};

class MakeIMMSwapWorker {
  public:
    string mObjectID;
    string mSwapTenor;
    string mIborIndex;
    double mFixedRate;
    ObjectHandler::property_t mFirstImmDate;
    string mFixDayCounter;
    double mSpread;
    string mPricingEngineID;

    string mReturnValue;

    string mError;

    MakeIMMSwapWorker(
      string ObjectID
,       string SwapTenor
,       string IborIndex
,       double FixedRate
,       ObjectHandler::property_t FirstImmDate
,       string FixDayCounter
,       double Spread
,       string PricingEngineID
     )
      {
        mObjectID = ObjectID;
        mSwapTenor = SwapTenor;
        mIborIndex = IborIndex;
        mFixedRate = FixedRate;
        mFirstImmDate = FirstImmDate;
        mFixDayCounter = FixDayCounter;
        mSpread = Spread;
        mPricingEngineID = PricingEngineID;
      };

    void Execute();
};

class VanillaSwapFromSwapIndexWorker {
  public:
    string mObjectID;
    string mSwapIndex;
    ObjectHandler::property_t mFixingDate;

    string mReturnValue;

    string mError;

    VanillaSwapFromSwapIndexWorker(
      string ObjectID
,       string SwapIndex
,       ObjectHandler::property_t FixingDate
     )
      {
        mObjectID = ObjectID;
        mSwapIndex = SwapIndex;
        mFixingDate = FixingDate;
      };

    void Execute();
};

class VanillaSwapFromSwapRateHelperWorker {
  public:
    string mObjectID;
    string mSwapRateHelper;

    string mReturnValue;

    string mError;

    VanillaSwapFromSwapRateHelperWorker(
      string ObjectID
,       string SwapRateHelper
     )
      {
        mObjectID = ObjectID;
        mSwapRateHelper = SwapRateHelper;
      };

    void Execute();
};

class VanillaSwapFixedLegBPSWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    VanillaSwapFixedLegBPSWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class VanillaSwapFixedLegNPVWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    VanillaSwapFixedLegNPVWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class VanillaSwapFairRateWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    VanillaSwapFairRateWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class VanillaSwapFloatingLegBPSWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    VanillaSwapFloatingLegBPSWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class VanillaSwapFloatingLegNPVWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    VanillaSwapFloatingLegNPVWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class VanillaSwapFairSpreadWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    VanillaSwapFairSpreadWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class VanillaSwapTypeWorker {
  public:
    string mObjectID;

    string mReturnValue;

    string mError;

    VanillaSwapTypeWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class VanillaSwapNominalWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    VanillaSwapNominalWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class VanillaSwapFixedRateWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    VanillaSwapFixedRateWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class VanillaSwapFixedDayCountWorker {
  public:
    string mObjectID;

    string mReturnValue;

    string mError;

    VanillaSwapFixedDayCountWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class VanillaSwapSpreadWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    VanillaSwapSpreadWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class VanillaSwapFloatingDayCountWorker {
  public:
    string mObjectID;

    string mReturnValue;

    string mError;

    VanillaSwapFloatingDayCountWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class VanillaSwapPaymentConventionWorker {
  public:
    string mObjectID;

    string mReturnValue;

    string mError;

    VanillaSwapPaymentConventionWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class VanillaSwapFixedLegAnalysisWorker {
  public:
    string mObjectID;
    ObjectHandler::property_t mAfterDate;

    std::vector< std::vector<string> > mReturnValue;

    string mError;

    VanillaSwapFixedLegAnalysisWorker(
      string ObjectID
,       ObjectHandler::property_t AfterDate
     )
      {
        mObjectID = ObjectID;
        mAfterDate = AfterDate;
      };

    void Execute();
};

class VanillaSwapFloatingLegAnalysisWorker {
  public:
    string mObjectID;
    ObjectHandler::property_t mAfterDate;

    std::vector< std::vector<string> > mReturnValue;

    string mError;

    VanillaSwapFloatingLegAnalysisWorker(
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
