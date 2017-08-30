/* 
  Copyright (C) 2016 -2017 Jerry Jin
*/

#ifndef pricingengines_h
#define pricingengines_h
#include <nan.h>
#include <string>
#include <queue>
#include <utility>

#include "../quantlibxl.hpp"

#include <oh/objecthandler.hpp>

using namespace node;
using namespace v8;
using namespace std;


class BlackCalculator2Worker {
  public:
    string mObjectID;
    string mPayoffID;
    double mAtmForwardValue;
    double mStdDev;
    double mDeflator;

    string mReturnValue;

    string mError;

    BlackCalculator2Worker(
      string ObjectID
,       string PayoffID
,       double AtmForwardValue
,       double StdDev
,       double Deflator
     )
      {
        mObjectID = ObjectID;
        mPayoffID = PayoffID;
        mAtmForwardValue = AtmForwardValue;
        mStdDev = StdDev;
        mDeflator = Deflator;
      };

    void Execute();
};

class BlackCalculatorWorker {
  public:
    string mObjectID;
    string mOptionType;
    double mStrike;
    double mAtmForwardValue;
    double mStdDev;
    double mDeflator;

    string mReturnValue;

    string mError;

    BlackCalculatorWorker(
      string ObjectID
,       string OptionType
,       double Strike
,       double AtmForwardValue
,       double StdDev
,       double Deflator
     )
      {
        mObjectID = ObjectID;
        mOptionType = OptionType;
        mStrike = Strike;
        mAtmForwardValue = AtmForwardValue;
        mStdDev = StdDev;
        mDeflator = Deflator;
      };

    void Execute();
};

class BlackScholesCalculator2Worker {
  public:
    string mObjectID;
    string mPayoffID;
    double mSpot;
    double mGrowth;
    double mStdDev;
    double mDeflator;

    string mReturnValue;

    string mError;

    BlackScholesCalculator2Worker(
      string ObjectID
,       string PayoffID
,       double Spot
,       double Growth
,       double StdDev
,       double Deflator
     )
      {
        mObjectID = ObjectID;
        mPayoffID = PayoffID;
        mSpot = Spot;
        mGrowth = Growth;
        mStdDev = StdDev;
        mDeflator = Deflator;
      };

    void Execute();
};

class BlackScholesCalculatorWorker {
  public:
    string mObjectID;
    string mOptionType;
    double mStrike;
    double mSpot;
    double mGrowth;
    double mStdDev;
    double mDeflator;

    string mReturnValue;

    string mError;

    BlackScholesCalculatorWorker(
      string ObjectID
,       string OptionType
,       double Strike
,       double Spot
,       double Growth
,       double StdDev
,       double Deflator
     )
      {
        mObjectID = ObjectID;
        mOptionType = OptionType;
        mStrike = Strike;
        mSpot = Spot;
        mGrowth = Growth;
        mStdDev = StdDev;
        mDeflator = Deflator;
      };

    void Execute();
};

class PricingEngineWorker {
  public:
    string mObjectID;
    string mEngineID;
    string mProcessID;

    string mReturnValue;

    string mError;

    PricingEngineWorker(
      string ObjectID
,       string EngineID
,       string ProcessID
     )
      {
        mObjectID = ObjectID;
        mEngineID = EngineID;
        mProcessID = ProcessID;
      };

    void Execute();
};

class DiscountingSwapEngineWorker {
  public:
    string mObjectID;
    ObjectHandler::property_t mYieldCurve;
    bool mIncludeSettlDate;
    ObjectHandler::property_t mSettlementDate;
    ObjectHandler::property_t mNpvDate;

    string mReturnValue;

    string mError;

    DiscountingSwapEngineWorker(
      string ObjectID
,       ObjectHandler::property_t YieldCurve
,       bool IncludeSettlDate
,       ObjectHandler::property_t SettlementDate
,       ObjectHandler::property_t NpvDate
     )
      {
        mObjectID = ObjectID;
        mYieldCurve = YieldCurve;
        mIncludeSettlDate = IncludeSettlDate;
        mSettlementDate = SettlementDate;
        mNpvDate = NpvDate;
      };

    void Execute();
};

class BinomialPricingEngineWorker {
  public:
    string mObjectID;
    string mEngineID;
    string mProcessID;
    long mTimeSteps;

    string mReturnValue;

    string mError;

    BinomialPricingEngineWorker(
      string ObjectID
,       string EngineID
,       string ProcessID
,       long TimeSteps
     )
      {
        mObjectID = ObjectID;
        mEngineID = EngineID;
        mProcessID = ProcessID;
        mTimeSteps = TimeSteps;
      };

    void Execute();
};

class BlackSwaptionEngineWorker {
  public:
    string mObjectID;
    ObjectHandler::property_t mYieldCurve;
    ObjectHandler::property_t mVolTS;
    double mDisplacement;

    string mReturnValue;

    string mError;

    BlackSwaptionEngineWorker(
      string ObjectID
,       ObjectHandler::property_t YieldCurve
,       ObjectHandler::property_t VolTS
,       double Displacement
     )
      {
        mObjectID = ObjectID;
        mYieldCurve = YieldCurve;
        mVolTS = VolTS;
        mDisplacement = Displacement;
      };

    void Execute();
};

class BlackSwaptionEngine2Worker {
  public:
    string mObjectID;
    ObjectHandler::property_t mYieldCurve;
    ObjectHandler::property_t mVol;
    double mDisplacement;
    string mDayCounter;

    string mReturnValue;

    string mError;

    BlackSwaptionEngine2Worker(
      string ObjectID
,       ObjectHandler::property_t YieldCurve
,       ObjectHandler::property_t Vol
,       double Displacement
,       string DayCounter
     )
      {
        mObjectID = ObjectID;
        mYieldCurve = YieldCurve;
        mVol = Vol;
        mDisplacement = Displacement;
        mDayCounter = DayCounter;
      };

    void Execute();
};

class BlackCapFloorEngineWorker {
  public:
    string mObjectID;
    ObjectHandler::property_t mYieldCurve;
    ObjectHandler::property_t mVolTS;
    double mDisplacement;

    string mReturnValue;

    string mError;

    BlackCapFloorEngineWorker(
      string ObjectID
,       ObjectHandler::property_t YieldCurve
,       ObjectHandler::property_t VolTS
,       double Displacement
     )
      {
        mObjectID = ObjectID;
        mYieldCurve = YieldCurve;
        mVolTS = VolTS;
        mDisplacement = Displacement;
      };

    void Execute();
};

class BlackCapFloorEngine2Worker {
  public:
    string mObjectID;
    ObjectHandler::property_t mYieldCurve;
    ObjectHandler::property_t mVol;
    double mDisplacement;
    string mDayCounter;

    string mReturnValue;

    string mError;

    BlackCapFloorEngine2Worker(
      string ObjectID
,       ObjectHandler::property_t YieldCurve
,       ObjectHandler::property_t Vol
,       double Displacement
,       string DayCounter
     )
      {
        mObjectID = ObjectID;
        mYieldCurve = YieldCurve;
        mVol = Vol;
        mDisplacement = Displacement;
        mDayCounter = DayCounter;
      };

    void Execute();
};

class BachelierCapFloorEngineWorker {
  public:
    string mObjectID;
    ObjectHandler::property_t mYieldCurve;
    ObjectHandler::property_t mVolTS;

    string mReturnValue;

    string mError;

    BachelierCapFloorEngineWorker(
      string ObjectID
,       ObjectHandler::property_t YieldCurve
,       ObjectHandler::property_t VolTS
     )
      {
        mObjectID = ObjectID;
        mYieldCurve = YieldCurve;
        mVolTS = VolTS;
      };

    void Execute();
};

class BachelierCapFloorEngine2Worker {
  public:
    string mObjectID;
    ObjectHandler::property_t mYieldCurve;
    ObjectHandler::property_t mVol;
    string mDayCounter;

    string mReturnValue;

    string mError;

    BachelierCapFloorEngine2Worker(
      string ObjectID
,       ObjectHandler::property_t YieldCurve
,       ObjectHandler::property_t Vol
,       string DayCounter
     )
      {
        mObjectID = ObjectID;
        mYieldCurve = YieldCurve;
        mVol = Vol;
        mDayCounter = DayCounter;
      };

    void Execute();
};

class AnalyticCapFloorEngineWorker {
  public:
    string mObjectID;
    string mHandleModel;

    string mReturnValue;

    string mError;

    AnalyticCapFloorEngineWorker(
      string ObjectID
,       string HandleModel
     )
      {
        mObjectID = ObjectID;
        mHandleModel = HandleModel;
      };

    void Execute();
};

class BondEngineWorker {
  public:
    string mObjectID;
    ObjectHandler::property_t mYieldCurve;

    string mReturnValue;

    string mError;

    BondEngineWorker(
      string ObjectID
,       ObjectHandler::property_t YieldCurve
     )
      {
        mObjectID = ObjectID;
        mYieldCurve = YieldCurve;
      };

    void Execute();
};

class JamshidianSwaptionEngineWorker {
  public:
    string mObjectID;
    string mModel;
    ObjectHandler::property_t mYieldCurve;

    string mReturnValue;

    string mError;

    JamshidianSwaptionEngineWorker(
      string ObjectID
,       string Model
,       ObjectHandler::property_t YieldCurve
     )
      {
        mObjectID = ObjectID;
        mModel = Model;
        mYieldCurve = YieldCurve;
      };

    void Execute();
};

class TreeSwaptionEngineWorker {
  public:
    string mObjectID;
    string mModel;
    long mNsteps;
    ObjectHandler::property_t mYieldCurve;

    string mReturnValue;

    string mError;

    TreeSwaptionEngineWorker(
      string ObjectID
,       string Model
,       long Nsteps
,       ObjectHandler::property_t YieldCurve
     )
      {
        mObjectID = ObjectID;
        mModel = Model;
        mNsteps = Nsteps;
        mYieldCurve = YieldCurve;
      };

    void Execute();
};

class ModelG2SwaptionEngineWorker {
  public:
    string mObjectID;
    string mModel;
    double mRange;
    long mIntervals;

    string mReturnValue;

    string mError;

    ModelG2SwaptionEngineWorker(
      string ObjectID
,       string Model
,       double Range
,       long Intervals
     )
      {
        mObjectID = ObjectID;
        mModel = Model;
        mRange = Range;
        mIntervals = Intervals;
      };

    void Execute();
};

class BlackCalculatorValueWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    BlackCalculatorValueWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class BlackCalculatorDeltaForwardWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    BlackCalculatorDeltaForwardWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class BlackCalculatorDeltaWorker {
  public:
    string mObjectID;
    double mSpot;

    double mReturnValue;

    string mError;

    BlackCalculatorDeltaWorker(
      string ObjectID
,       double Spot
     )
      {
        mObjectID = ObjectID;
        mSpot = Spot;
      };

    void Execute();
};

class BlackCalculatorElasticityForwardWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    BlackCalculatorElasticityForwardWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class BlackCalculatorElasticityWorker {
  public:
    string mObjectID;
    double mSpot;

    double mReturnValue;

    string mError;

    BlackCalculatorElasticityWorker(
      string ObjectID
,       double Spot
     )
      {
        mObjectID = ObjectID;
        mSpot = Spot;
      };

    void Execute();
};

class BlackCalculatorGammaForwardWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    BlackCalculatorGammaForwardWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class BlackCalculatorGammaWorker {
  public:
    string mObjectID;
    double mSpot;

    double mReturnValue;

    string mError;

    BlackCalculatorGammaWorker(
      string ObjectID
,       double Spot
     )
      {
        mObjectID = ObjectID;
        mSpot = Spot;
      };

    void Execute();
};

class BlackCalculatorThetaWorker {
  public:
    string mObjectID;
    double mSpot;
    double mTimeToMaturity;

    double mReturnValue;

    string mError;

    BlackCalculatorThetaWorker(
      string ObjectID
,       double Spot
,       double TimeToMaturity
     )
      {
        mObjectID = ObjectID;
        mSpot = Spot;
        mTimeToMaturity = TimeToMaturity;
      };

    void Execute();
};

class BlackCalculatorThetaPerDayWorker {
  public:
    string mObjectID;
    double mSpot;
    double mTimeToMaturity;

    double mReturnValue;

    string mError;

    BlackCalculatorThetaPerDayWorker(
      string ObjectID
,       double Spot
,       double TimeToMaturity
     )
      {
        mObjectID = ObjectID;
        mSpot = Spot;
        mTimeToMaturity = TimeToMaturity;
      };

    void Execute();
};

class BlackCalculatorVegaWorker {
  public:
    string mObjectID;
    double mTimeToMaturity;

    double mReturnValue;

    string mError;

    BlackCalculatorVegaWorker(
      string ObjectID
,       double TimeToMaturity
     )
      {
        mObjectID = ObjectID;
        mTimeToMaturity = TimeToMaturity;
      };

    void Execute();
};

class BlackCalculatorRhoWorker {
  public:
    string mObjectID;
    double mTimeToMaturity;

    double mReturnValue;

    string mError;

    BlackCalculatorRhoWorker(
      string ObjectID
,       double TimeToMaturity
     )
      {
        mObjectID = ObjectID;
        mTimeToMaturity = TimeToMaturity;
      };

    void Execute();
};

class BlackCalculatorDividendRhoWorker {
  public:
    string mObjectID;
    double mTimeToMaturity;

    double mReturnValue;

    string mError;

    BlackCalculatorDividendRhoWorker(
      string ObjectID
,       double TimeToMaturity
     )
      {
        mObjectID = ObjectID;
        mTimeToMaturity = TimeToMaturity;
      };

    void Execute();
};

class BlackCalculatorItmCashProbabilityWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    BlackCalculatorItmCashProbabilityWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class BlackCalculatorItmAssetProbabilityWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    BlackCalculatorItmAssetProbabilityWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class BlackCalculatorStrikeSensitivityWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    BlackCalculatorStrikeSensitivityWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class BlackCalculatorAlphaWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    BlackCalculatorAlphaWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class BlackCalculatorBetaWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    BlackCalculatorBetaWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class BlackScholesCalculatorDeltaWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    BlackScholesCalculatorDeltaWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class BlackScholesCalculatorElasticityWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    BlackScholesCalculatorElasticityWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class BlackScholesCalculatorGammaWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    BlackScholesCalculatorGammaWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class BlackScholesCalculatorThetaWorker {
  public:
    string mObjectID;
    double mTimeToMaturity;

    double mReturnValue;

    string mError;

    BlackScholesCalculatorThetaWorker(
      string ObjectID
,       double TimeToMaturity
     )
      {
        mObjectID = ObjectID;
        mTimeToMaturity = TimeToMaturity;
      };

    void Execute();
};

class BlackScholesCalculatorThetaPerDayWorker {
  public:
    string mObjectID;
    double mTimeToMaturity;

    double mReturnValue;

    string mError;

    BlackScholesCalculatorThetaPerDayWorker(
      string ObjectID
,       double TimeToMaturity
     )
      {
        mObjectID = ObjectID;
        mTimeToMaturity = TimeToMaturity;
      };

    void Execute();
};

class BlackFormulaWorker {
  public:
    string mOptionType;
    double mStrike;
    double mAtmForwardValue;
    double mStdDev;
    double mDeflator;
    double mDisplacement;

    double mReturnValue;

    string mError;

    BlackFormulaWorker(
      string OptionType
,       double Strike
,       double AtmForwardValue
,       double StdDev
,       double Deflator
,       double Displacement
     )
      {
        mOptionType = OptionType;
        mStrike = Strike;
        mAtmForwardValue = AtmForwardValue;
        mStdDev = StdDev;
        mDeflator = Deflator;
        mDisplacement = Displacement;
      };

    void Execute();
};

class BlackFormulaCashItmProbabilityWorker {
  public:
    string mOptionType;
    double mStrike;
    double mAtmForwardValue;
    double mStdDev;
    double mDisplacement;

    double mReturnValue;

    string mError;

    BlackFormulaCashItmProbabilityWorker(
      string OptionType
,       double Strike
,       double AtmForwardValue
,       double StdDev
,       double Displacement
     )
      {
        mOptionType = OptionType;
        mStrike = Strike;
        mAtmForwardValue = AtmForwardValue;
        mStdDev = StdDev;
        mDisplacement = Displacement;
      };

    void Execute();
};

class BlackFormulaImpliedStdDevApproximationWorker {
  public:
    string mOptionType;
    double mStrike;
    double mAtmForwardValue;
    double mOptionPrice;
    double mDeflator;
    double mDisplacement;

    double mReturnValue;

    string mError;

    BlackFormulaImpliedStdDevApproximationWorker(
      string OptionType
,       double Strike
,       double AtmForwardValue
,       double OptionPrice
,       double Deflator
,       double Displacement
     )
      {
        mOptionType = OptionType;
        mStrike = Strike;
        mAtmForwardValue = AtmForwardValue;
        mOptionPrice = OptionPrice;
        mDeflator = Deflator;
        mDisplacement = Displacement;
      };

    void Execute();
};

class BlackFormulaImpliedStdDevWorker {
  public:
    string mOptionType;
    double mStrike;
    double mAtmForwardValue;
    double mOptionPrice;
    double mDeflator;
    double mDisplacement;
    double mGuess;
    double mAccuracy;
    ObjectHandler::property_t mMaxIter;

    double mReturnValue;

    string mError;

    BlackFormulaImpliedStdDevWorker(
      string OptionType
,       double Strike
,       double AtmForwardValue
,       double OptionPrice
,       double Deflator
,       double Displacement
,       double Guess
,       double Accuracy
,       ObjectHandler::property_t MaxIter
     )
      {
        mOptionType = OptionType;
        mStrike = Strike;
        mAtmForwardValue = AtmForwardValue;
        mOptionPrice = OptionPrice;
        mDeflator = Deflator;
        mDisplacement = Displacement;
        mGuess = Guess;
        mAccuracy = Accuracy;
        mMaxIter = MaxIter;
      };

    void Execute();
};

class BlackFormulaStdDevDerivativeWorker {
  public:
    double mStrike;
    double mAtmForwardValue;
    double mStdDev;
    double mDeflator;
    double mDisplacement;

    double mReturnValue;

    string mError;

    BlackFormulaStdDevDerivativeWorker(
      double Strike
,       double AtmForwardValue
,       double StdDev
,       double Deflator
,       double Displacement
     )
      {
        mStrike = Strike;
        mAtmForwardValue = AtmForwardValue;
        mStdDev = StdDev;
        mDeflator = Deflator;
        mDisplacement = Displacement;
      };

    void Execute();
};

class BachelierBlackFormulaWorker {
  public:
    string mOptionType;
    double mStrike;
    double mAtmForwardValue;
    double mStdDev;
    double mDeflator;

    double mReturnValue;

    string mError;

    BachelierBlackFormulaWorker(
      string OptionType
,       double Strike
,       double AtmForwardValue
,       double StdDev
,       double Deflator
     )
      {
        mOptionType = OptionType;
        mStrike = Strike;
        mAtmForwardValue = AtmForwardValue;
        mStdDev = StdDev;
        mDeflator = Deflator;
      };

    void Execute();
};

class BachelierBlackFormulaImpliedVolWorker {
  public:
    string mOptionType;
    double mStrike;
    double mAtmForwardValue;
    double mTimeToExpiry;
    double mOptionPrice;
    double mDeflator;

    double mReturnValue;

    string mError;

    BachelierBlackFormulaImpliedVolWorker(
      string OptionType
,       double Strike
,       double AtmForwardValue
,       double TimeToExpiry
,       double OptionPrice
,       double Deflator
     )
      {
        mOptionType = OptionType;
        mStrike = Strike;
        mAtmForwardValue = AtmForwardValue;
        mTimeToExpiry = TimeToExpiry;
        mOptionPrice = OptionPrice;
        mDeflator = Deflator;
      };

    void Execute();
};

class BlackFormula2Worker {
  public:
    string mPayoff;
    double mAtmForwardValue;
    double mStdDev;
    double mDeflator;
    double mDisplacement;

    double mReturnValue;

    string mError;

    BlackFormula2Worker(
      string Payoff
,       double AtmForwardValue
,       double StdDev
,       double Deflator
,       double Displacement
     )
      {
        mPayoff = Payoff;
        mAtmForwardValue = AtmForwardValue;
        mStdDev = StdDev;
        mDeflator = Deflator;
        mDisplacement = Displacement;
      };

    void Execute();
};

class BlackFormulaCashItmProbability2Worker {
  public:
    string mPayoff;
    double mAtmForwardValue;
    double mStdDev;
    double mDisplacement;

    double mReturnValue;

    string mError;

    BlackFormulaCashItmProbability2Worker(
      string Payoff
,       double AtmForwardValue
,       double StdDev
,       double Displacement
     )
      {
        mPayoff = Payoff;
        mAtmForwardValue = AtmForwardValue;
        mStdDev = StdDev;
        mDisplacement = Displacement;
      };

    void Execute();
};

class BlackFormulaImpliedStdDevApproximation2Worker {
  public:
    string mPayoff;
    double mAtmForwardValue;
    double mOptionPrice;
    double mDeflator;
    double mDisplacement;

    double mReturnValue;

    string mError;

    BlackFormulaImpliedStdDevApproximation2Worker(
      string Payoff
,       double AtmForwardValue
,       double OptionPrice
,       double Deflator
,       double Displacement
     )
      {
        mPayoff = Payoff;
        mAtmForwardValue = AtmForwardValue;
        mOptionPrice = OptionPrice;
        mDeflator = Deflator;
        mDisplacement = Displacement;
      };

    void Execute();
};

class BlackFormulaImpliedStdDev2Worker {
  public:
    string mPayoffID;
    double mAtmForwardValue;
    double mOptionPrice;
    double mDeflator;
    double mDisplacement;
    double mGuess;
    double mAccuracy;
    ObjectHandler::property_t mMaxIter;

    double mReturnValue;

    string mError;

    BlackFormulaImpliedStdDev2Worker(
      string PayoffID
,       double AtmForwardValue
,       double OptionPrice
,       double Deflator
,       double Displacement
,       double Guess
,       double Accuracy
,       ObjectHandler::property_t MaxIter
     )
      {
        mPayoffID = PayoffID;
        mAtmForwardValue = AtmForwardValue;
        mOptionPrice = OptionPrice;
        mDeflator = Deflator;
        mDisplacement = Displacement;
        mGuess = Guess;
        mAccuracy = Accuracy;
        mMaxIter = MaxIter;
      };

    void Execute();
};

class BlackFormulaStdDevDerivative2Worker {
  public:
    string mPayoffID;
    double mAtmForwardValue;
    double mStdDev;
    double mDeflator;
    double mDisplacement;

    double mReturnValue;

    string mError;

    BlackFormulaStdDevDerivative2Worker(
      string PayoffID
,       double AtmForwardValue
,       double StdDev
,       double Deflator
,       double Displacement
     )
      {
        mPayoffID = PayoffID;
        mAtmForwardValue = AtmForwardValue;
        mStdDev = StdDev;
        mDeflator = Deflator;
        mDisplacement = Displacement;
      };

    void Execute();
};

class BachelierBlackFormula2Worker {
  public:
    string mPayoff;
    double mAtmForwardValue;
    double mStdDev;
    double mDeflator;

    double mReturnValue;

    string mError;

    BachelierBlackFormula2Worker(
      string Payoff
,       double AtmForwardValue
,       double StdDev
,       double Deflator
     )
      {
        mPayoff = Payoff;
        mAtmForwardValue = AtmForwardValue;
        mStdDev = StdDev;
        mDeflator = Deflator;
      };

    void Execute();
};
 
#endif
