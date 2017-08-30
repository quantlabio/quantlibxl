/* 
  Copyright (C) 2016 -2017 Jerry Jin
*/

#ifndef evolutiondescription_h
#define evolutiondescription_h
#include <nan.h>
#include <string>
#include <queue>
#include <utility>

#include "../quantlibxl.hpp"

#include <oh/objecthandler.hpp>

using namespace node;
using namespace v8;
using namespace std;


class EvolutionDescriptionWorker {
  public:
    string mObjectID;
    std::vector<double> mRateTimes;
    std::vector<double> mEvolutionTimes;

    string mReturnValue;

    string mError;

    EvolutionDescriptionWorker(
      string ObjectID
,       std::vector<double> RateTimes
,       std::vector<double> EvolutionTimes
     )
      {
        mObjectID = ObjectID;
        mRateTimes = RateTimes;
        mEvolutionTimes = EvolutionTimes;
      };

    void Execute();
};

class EvolutionDescriptionFromProductWorker {
  public:
    string mObjectID;
    string mProduct;

    string mReturnValue;

    string mError;

    EvolutionDescriptionFromProductWorker(
      string ObjectID
,       string Product
     )
      {
        mObjectID = ObjectID;
        mProduct = Product;
      };

    void Execute();
};

class EvolutionDescriptionRateTimesWorker {
  public:
    string mObjectID;

    std::vector<double> mReturnValue;

    string mError;

    EvolutionDescriptionRateTimesWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class EvolutionDescriptionRateTausWorker {
  public:
    string mObjectID;

    std::vector<double> mReturnValue;

    string mError;

    EvolutionDescriptionRateTausWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class EvolutionDescriptionEvolutionTimesWorker {
  public:
    string mObjectID;

    std::vector<double> mReturnValue;

    string mError;

    EvolutionDescriptionEvolutionTimesWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class EvolutionDescriptionFirstAliveRateWorker {
  public:
    string mObjectID;

    std::vector<long> mReturnValue;

    string mError;

    EvolutionDescriptionFirstAliveRateWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class EvolutionDescriptionNumberOfRatesWorker {
  public:
    string mObjectID;

    long mReturnValue;

    string mError;

    EvolutionDescriptionNumberOfRatesWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class EvolutionDescriptionNumberOfStepsWorker {
  public:
    string mObjectID;

    long mReturnValue;

    string mError;

    EvolutionDescriptionNumberOfStepsWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class TerminalMeasureWorker {
  public:
    string mEvolutionDescription;

    std::vector<long> mReturnValue;

    string mError;

    TerminalMeasureWorker(
      string EvolutionDescription
     )
      {
        mEvolutionDescription = EvolutionDescription;
      };

    void Execute();
};

class MoneyMarketMeasureWorker {
  public:
    string mEvolutionDescription;

    std::vector<long> mReturnValue;

    string mError;

    MoneyMarketMeasureWorker(
      string EvolutionDescription
     )
      {
        mEvolutionDescription = EvolutionDescription;
      };

    void Execute();
};

class MoneyMarketPlusMeasureWorker {
  public:
    string mEvolutionDescription;
    long mOffset;

    std::vector<long> mReturnValue;

    string mError;

    MoneyMarketPlusMeasureWorker(
      string EvolutionDescription
,       long Offset
     )
      {
        mEvolutionDescription = EvolutionDescription;
        mOffset = Offset;
      };

    void Execute();
};

class IsInTerminalMeasureWorker {
  public:
    string mEvolutionDescription;
    std::vector<long> mNumeraires;

    bool mReturnValue;

    string mError;

    IsInTerminalMeasureWorker(
      string EvolutionDescription
,       std::vector<long> Numeraires
     )
      {
        mEvolutionDescription = EvolutionDescription;
        mNumeraires = Numeraires;
      };

    void Execute();
};

class IsInMoneyMarketMeasureWorker {
  public:
    string mEvolutionDescription;
    std::vector<long> mNumeraires;

    bool mReturnValue;

    string mError;

    IsInMoneyMarketMeasureWorker(
      string EvolutionDescription
,       std::vector<long> Numeraires
     )
      {
        mEvolutionDescription = EvolutionDescription;
        mNumeraires = Numeraires;
      };

    void Execute();
};

class IsInMoneyMarketPlusMeasureWorker {
  public:
    string mEvolutionDescription;
    std::vector<long> mNumeraires;
    long mOffset;

    bool mReturnValue;

    string mError;

    IsInMoneyMarketPlusMeasureWorker(
      string EvolutionDescription
,       std::vector<long> Numeraires
,       long Offset
     )
      {
        mEvolutionDescription = EvolutionDescription;
        mNumeraires = Numeraires;
        mOffset = Offset;
      };

    void Execute();
};
 
#endif
