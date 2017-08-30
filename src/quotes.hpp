/* 
  Copyright (C) 2016 -2017 Jerry Jin
*/

#ifndef quotes_h
#define quotes_h
#include <nan.h>
#include <string>
#include <queue>
#include <utility>

#include "../quantlibxl.hpp"

#include <oh/objecthandler.hpp>

using namespace node;
using namespace v8;
using namespace std;


class SimpleQuoteWorker {
  public:
    string mObjectID;
    double mValue;
    double mTickValue;

    string mReturnValue;

    string mError;

    SimpleQuoteWorker(
      string ObjectID
,       double Value
,       double TickValue
     )
      {
        mObjectID = ObjectID;
        mValue = Value;
        mTickValue = TickValue;
      };

    void Execute();
};

class ForwardValueQuoteWorker {
  public:
    string mObjectID;
    string mIborIndex;
    ObjectHandler::property_t mFixingDate;

    string mReturnValue;

    string mError;

    ForwardValueQuoteWorker(
      string ObjectID
,       string IborIndex
,       ObjectHandler::property_t FixingDate
     )
      {
        mObjectID = ObjectID;
        mIborIndex = IborIndex;
        mFixingDate = FixingDate;
      };

    void Execute();
};

class ForwardSwapQuoteWorker {
  public:
    string mObjectID;
    string mSwapIndex;
    ObjectHandler::property_t mSpread;
    string mForwardStart;

    string mReturnValue;

    string mError;

    ForwardSwapQuoteWorker(
      string ObjectID
,       string SwapIndex
,       ObjectHandler::property_t Spread
,       string ForwardStart
     )
      {
        mObjectID = ObjectID;
        mSwapIndex = SwapIndex;
        mSpread = Spread;
        mForwardStart = ForwardStart;
      };

    void Execute();
};

class ImpliedStdDevQuoteWorker {
  public:
    string mObjectID;
    string mOptionType;
    ObjectHandler::property_t mAtmForwardValue;
    ObjectHandler::property_t mOptionPrice;
    double mStrike;
    double mGuess;
    double mAccuracy;

    string mReturnValue;

    string mError;

    ImpliedStdDevQuoteWorker(
      string ObjectID
,       string OptionType
,       ObjectHandler::property_t AtmForwardValue
,       ObjectHandler::property_t OptionPrice
,       double Strike
,       double Guess
,       double Accuracy
     )
      {
        mObjectID = ObjectID;
        mOptionType = OptionType;
        mAtmForwardValue = AtmForwardValue;
        mOptionPrice = OptionPrice;
        mStrike = Strike;
        mGuess = Guess;
        mAccuracy = Accuracy;
      };

    void Execute();
};

class EurodollarFuturesImpliedStdDevQuoteWorker {
  public:
    string mObjectID;
    ObjectHandler::property_t mAtmForwardValue;
    ObjectHandler::property_t mCallPrice;
    ObjectHandler::property_t mPutPrice;
    double mStrike;
    double mGuess;
    double mAccuracy;

    string mReturnValue;

    string mError;

    EurodollarFuturesImpliedStdDevQuoteWorker(
      string ObjectID
,       ObjectHandler::property_t AtmForwardValue
,       ObjectHandler::property_t CallPrice
,       ObjectHandler::property_t PutPrice
,       double Strike
,       double Guess
,       double Accuracy
     )
      {
        mObjectID = ObjectID;
        mAtmForwardValue = AtmForwardValue;
        mCallPrice = CallPrice;
        mPutPrice = PutPrice;
        mStrike = Strike;
        mGuess = Guess;
        mAccuracy = Accuracy;
      };

    void Execute();
};

class CompositeQuoteWorker {
  public:
    string mObjectID;
    ObjectHandler::property_t mElement1;
    ObjectHandler::property_t mElement2;
    string mOperator;

    string mReturnValue;

    string mError;

    CompositeQuoteWorker(
      string ObjectID
,       ObjectHandler::property_t Element1
,       ObjectHandler::property_t Element2
,       string Operator
     )
      {
        mObjectID = ObjectID;
        mElement1 = Element1;
        mElement2 = Element2;
        mOperator = Operator;
      };

    void Execute();
};

class FuturesConvAdjustmentQuoteWorker {
  public:
    string mObjectID;
    string mIborIndex;
    string mImmCode;
    ObjectHandler::property_t mFuturesQuote;
    ObjectHandler::property_t mVolatility;
    ObjectHandler::property_t mMeanReversion;

    string mReturnValue;

    string mError;

    FuturesConvAdjustmentQuoteWorker(
      string ObjectID
,       string IborIndex
,       string ImmCode
,       ObjectHandler::property_t FuturesQuote
,       ObjectHandler::property_t Volatility
,       ObjectHandler::property_t MeanReversion
     )
      {
        mObjectID = ObjectID;
        mIborIndex = IborIndex;
        mImmCode = ImmCode;
        mFuturesQuote = FuturesQuote;
        mVolatility = Volatility;
        mMeanReversion = MeanReversion;
      };

    void Execute();
};

class LastFixingQuoteWorker {
  public:
    string mObjectID;
    string mIndex;

    string mReturnValue;

    string mError;

    LastFixingQuoteWorker(
      string ObjectID
,       string Index
     )
      {
        mObjectID = ObjectID;
        mIndex = Index;
      };

    void Execute();
};

class RelinkableHandleQuoteWorker {
  public:
    string mObjectID;
    string mCurrentLink;

    string mReturnValue;

    string mError;

    RelinkableHandleQuoteWorker(
      string ObjectID
,       string CurrentLink
     )
      {
        mObjectID = ObjectID;
        mCurrentLink = CurrentLink;
      };

    void Execute();
};

class QuoteValueWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    QuoteValueWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class QuoteIsValidWorker {
  public:
    string mObjectID;

    bool mReturnValue;

    string mError;

    QuoteIsValidWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class SimpleQuoteResetWorker {
  public:
    string mObjectID;

    string mError;

    SimpleQuoteResetWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class SimpleQuoteSetValueWorker {
  public:
    string mObjectID;
    double mValue;

    double mReturnValue;

    string mError;

    SimpleQuoteSetValueWorker(
      string ObjectID
,       double Value
     )
      {
        mObjectID = ObjectID;
        mValue = Value;
      };

    void Execute();
};

class SimpleQuoteSetTickValueWorker {
  public:
    string mObjectID;
    double mValue;

    string mError;

    SimpleQuoteSetTickValueWorker(
      string ObjectID
,       double Value
     )
      {
        mObjectID = ObjectID;
        mValue = Value;
      };

    void Execute();
};

class SimpleQuoteTickValueWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    SimpleQuoteTickValueWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class FuturesConvAdjustmentQuoteVolatilityWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    FuturesConvAdjustmentQuoteVolatilityWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class FuturesConvAdjustmentQuoteMeanReversionWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    FuturesConvAdjustmentQuoteMeanReversionWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class FuturesConvAdjustmentQuoteImmDateWorker {
  public:
    string mObjectID;

    long mReturnValue;

    string mError;

    FuturesConvAdjustmentQuoteImmDateWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class FuturesConvAdjustmentQuoteFuturesValueWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    FuturesConvAdjustmentQuoteFuturesValueWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class LastFixingQuoteReferenceDateWorker {
  public:
    string mObjectID;

    long mReturnValue;

    string mError;

    LastFixingQuoteReferenceDateWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class BucketAnalysisWorker {
  public:
    std::vector< std::vector<ObjectHandler::property_t> > mSimpleQuote;
    std::vector<string> mInstruments;
    std::vector<double> mQuantities;
    double mShift;
    string mSensitivityAnalysis;

    std::vector< std::vector<double> > mReturnValue;

    string mError;

    BucketAnalysisWorker(
      std::vector< std::vector<ObjectHandler::property_t> > SimpleQuote
,       std::vector<string> Instruments
,       std::vector<double> Quantities
,       double Shift
,       string SensitivityAnalysis
     )
      {
        mSimpleQuote = SimpleQuote;
        mInstruments = Instruments;
        mQuantities = Quantities;
        mShift = Shift;
        mSensitivityAnalysis = SensitivityAnalysis;
      };

    void Execute();
};

class BucketAnalysisDeltaWorker {
  public:
    ObjectHandler::property_t mSimpleQuote;
    std::vector<ObjectHandler::property_t> mParameters;
    double mShift;
    string mSensitivityAnalysis;

    std::vector<double> mReturnValue;

    string mError;

    BucketAnalysisDeltaWorker(
      ObjectHandler::property_t SimpleQuote
,       std::vector<ObjectHandler::property_t> Parameters
,       double Shift
,       string SensitivityAnalysis
     )
      {
        mSimpleQuote = SimpleQuote;
        mParameters = Parameters;
        mShift = Shift;
        mSensitivityAnalysis = SensitivityAnalysis;
      };

    void Execute();
};

class BucketAnalysisDelta2Worker {
  public:
    std::vector<ObjectHandler::property_t> mSimpleQuote;
    std::vector<ObjectHandler::property_t> mParameters;
    double mShift;
    string mSensitivityAnalysis;

    std::vector< std::vector<double> > mReturnValue;

    string mError;

    BucketAnalysisDelta2Worker(
      std::vector<ObjectHandler::property_t> SimpleQuote
,       std::vector<ObjectHandler::property_t> Parameters
,       double Shift
,       string SensitivityAnalysis
     )
      {
        mSimpleQuote = SimpleQuote;
        mParameters = Parameters;
        mShift = Shift;
        mSensitivityAnalysis = SensitivityAnalysis;
      };

    void Execute();
};
 
#endif
