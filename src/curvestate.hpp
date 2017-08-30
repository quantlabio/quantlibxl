/* 
  Copyright (C) 2016 -2017 Jerry Jin
*/

#ifndef curvestate_h
#define curvestate_h
#include <nan.h>
#include <string>
#include <queue>
#include <utility>

#include "../quantlibxl.hpp"

#include <oh/objecthandler.hpp>

using namespace node;
using namespace v8;
using namespace std;


class CMSwapCurveStateWorker {
  public:
    string mObjectID;
    std::vector<double> mRateTimes;
    long mSpanningForwards;

    string mReturnValue;

    string mError;

    CMSwapCurveStateWorker(
      string ObjectID
,       std::vector<double> RateTimes
,       long SpanningForwards
     )
      {
        mObjectID = ObjectID;
        mRateTimes = RateTimes;
        mSpanningForwards = SpanningForwards;
      };

    void Execute();
};

class CoterminalSwapCurveStateWorker {
  public:
    string mObjectID;
    std::vector<double> mRateTimes;

    string mReturnValue;

    string mError;

    CoterminalSwapCurveStateWorker(
      string ObjectID
,       std::vector<double> RateTimes
     )
      {
        mObjectID = ObjectID;
        mRateTimes = RateTimes;
      };

    void Execute();
};

class LMMCurveStateWorker {
  public:
    string mObjectID;
    std::vector<double> mRateTimes;

    string mReturnValue;

    string mError;

    LMMCurveStateWorker(
      string ObjectID
,       std::vector<double> RateTimes
     )
      {
        mObjectID = ObjectID;
        mRateTimes = RateTimes;
      };

    void Execute();
};

class CurveStateRateTimesWorker {
  public:
    string mObjectID;

    std::vector<double> mReturnValue;

    string mError;

    CurveStateRateTimesWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class CurveStateRateTausWorker {
  public:
    string mObjectID;

    std::vector<double> mReturnValue;

    string mError;

    CurveStateRateTausWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class CurveStateForwardRatesWorker {
  public:
    string mObjectID;

    std::vector<double> mReturnValue;

    string mError;

    CurveStateForwardRatesWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class CurveStateCoterminalSwapRatesWorker {
  public:
    string mObjectID;

    std::vector<double> mReturnValue;

    string mError;

    CurveStateCoterminalSwapRatesWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class CurveStateCMSwapRatesWorker {
  public:
    string mObjectID;
    long mSpanningForwards;

    std::vector<double> mReturnValue;

    string mError;

    CurveStateCMSwapRatesWorker(
      string ObjectID
,       long SpanningForwards
     )
      {
        mObjectID = ObjectID;
        mSpanningForwards = SpanningForwards;
      };

    void Execute();
};

class CMSwapCurveStateSetOnCMSwapRatesWorker {
  public:
    string mObjectID;
    std::vector<double> mCMSwapRates;

    string mError;

    CMSwapCurveStateSetOnCMSwapRatesWorker(
      string ObjectID
,       std::vector<double> CMSwapRates
     )
      {
        mObjectID = ObjectID;
        mCMSwapRates = CMSwapRates;
      };

    void Execute();
};

class CoterminalSwapCurveStateSetOnCoterminalSwapRatesWorker {
  public:
    string mObjectID;
    std::vector<double> mCoterminalSwaps;

    string mError;

    CoterminalSwapCurveStateSetOnCoterminalSwapRatesWorker(
      string ObjectID
,       std::vector<double> CoterminalSwaps
     )
      {
        mObjectID = ObjectID;
        mCoterminalSwaps = CoterminalSwaps;
      };

    void Execute();
};

class LMMCurveStateSetOnForwardRatesWorker {
  public:
    string mObjectID;
    std::vector<double> mRates;

    string mError;

    LMMCurveStateSetOnForwardRatesWorker(
      string ObjectID
,       std::vector<double> Rates
     )
      {
        mObjectID = ObjectID;
        mRates = Rates;
      };

    void Execute();
};

class LMMCurveStateSetOnDiscountRatiosWorker {
  public:
    string mObjectID;
    std::vector<double> mDiscountRatios;

    string mError;

    LMMCurveStateSetOnDiscountRatiosWorker(
      string ObjectID
,       std::vector<double> DiscountRatios
     )
      {
        mObjectID = ObjectID;
        mDiscountRatios = DiscountRatios;
      };

    void Execute();
};

class ForwardsFromDiscountRatiosWorker {
  public:
    long mFirstValidIndex;
    std::vector<double> mDiscountRatios;
    std::vector<double> mTaus;

    std::vector<double> mReturnValue;

    string mError;

    ForwardsFromDiscountRatiosWorker(
      long FirstValidIndex
,       std::vector<double> DiscountRatios
,       std::vector<double> Taus
     )
      {
        mFirstValidIndex = FirstValidIndex;
        mDiscountRatios = DiscountRatios;
        mTaus = Taus;
      };

    void Execute();
};

class CoterminalSwapRatesFromDiscountRatiosWorker {
  public:
    long mFirstValidIndex;
    std::vector<double> mDiscountRatios;
    std::vector<double> mTaus;

    std::vector<double> mReturnValue;

    string mError;

    CoterminalSwapRatesFromDiscountRatiosWorker(
      long FirstValidIndex
,       std::vector<double> DiscountRatios
,       std::vector<double> Taus
     )
      {
        mFirstValidIndex = FirstValidIndex;
        mDiscountRatios = DiscountRatios;
        mTaus = Taus;
      };

    void Execute();
};

class CoterminalSwapAnnuitiesFromDiscountRatiosWorker {
  public:
    long mFirstValidIndex;
    std::vector<double> mDiscountRatios;
    std::vector<double> mTaus;

    std::vector<double> mReturnValue;

    string mError;

    CoterminalSwapAnnuitiesFromDiscountRatiosWorker(
      long FirstValidIndex
,       std::vector<double> DiscountRatios
,       std::vector<double> Taus
     )
      {
        mFirstValidIndex = FirstValidIndex;
        mDiscountRatios = DiscountRatios;
        mTaus = Taus;
      };

    void Execute();
};

class ConstantMaturitySwapRatesFromDiscountRatiosWorker {
  public:
    long mSpanningForwards;
    long mFirstValidIndex;
    std::vector<double> mDiscountRatios;
    std::vector<double> mTaus;

    std::vector<double> mReturnValue;

    string mError;

    ConstantMaturitySwapRatesFromDiscountRatiosWorker(
      long SpanningForwards
,       long FirstValidIndex
,       std::vector<double> DiscountRatios
,       std::vector<double> Taus
     )
      {
        mSpanningForwards = SpanningForwards;
        mFirstValidIndex = FirstValidIndex;
        mDiscountRatios = DiscountRatios;
        mTaus = Taus;
      };

    void Execute();
};

class ConstantMaturitySwapAnnuitiesFromDiscountRatiosWorker {
  public:
    long mSpanningForwards;
    long mFirstValidIndex;
    std::vector<double> mDiscountRatios;
    std::vector<double> mTaus;

    std::vector<double> mReturnValue;

    string mError;

    ConstantMaturitySwapAnnuitiesFromDiscountRatiosWorker(
      long SpanningForwards
,       long FirstValidIndex
,       std::vector<double> DiscountRatios
,       std::vector<double> Taus
     )
      {
        mSpanningForwards = SpanningForwards;
        mFirstValidIndex = FirstValidIndex;
        mDiscountRatios = DiscountRatios;
        mTaus = Taus;
      };

    void Execute();
};
 
#endif
