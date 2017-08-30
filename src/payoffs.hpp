/* 
  Copyright (C) 2016 -2017 Jerry Jin
*/

#ifndef payoffs_h
#define payoffs_h
#include <nan.h>
#include <string>
#include <queue>
#include <utility>

#include "../quantlibxl.hpp"

#include <oh/objecthandler.hpp>

using namespace node;
using namespace v8;
using namespace std;


class StrikedTypePayoffWorker {
  public:
    string mObjectID;
    string mPayoffID;
    string mOptionType;
    double mStrike;
    double mThirdParameter;

    string mReturnValue;

    string mError;

    StrikedTypePayoffWorker(
      string ObjectID
,       string PayoffID
,       string OptionType
,       double Strike
,       double ThirdParameter
     )
      {
        mObjectID = ObjectID;
        mPayoffID = PayoffID;
        mOptionType = OptionType;
        mStrike = Strike;
        mThirdParameter = ThirdParameter;
      };

    void Execute();
};

class DoubleStickyRatchetPayoffWorker {
  public:
    string mObjectID;
    double mType1;
    double mType2;
    double mGearing1;
    double mGearing2;
    double mGearing3;
    double mSpread1;
    double mSpread2;
    double mSpread3;
    double mInitialValue1;
    double mInitialValue2;
    double mAccrualFactor;

    string mReturnValue;

    string mError;

    DoubleStickyRatchetPayoffWorker(
      string ObjectID
,       double Type1
,       double Type2
,       double Gearing1
,       double Gearing2
,       double Gearing3
,       double Spread1
,       double Spread2
,       double Spread3
,       double InitialValue1
,       double InitialValue2
,       double AccrualFactor
     )
      {
        mObjectID = ObjectID;
        mType1 = Type1;
        mType2 = Type2;
        mGearing1 = Gearing1;
        mGearing2 = Gearing2;
        mGearing3 = Gearing3;
        mSpread1 = Spread1;
        mSpread2 = Spread2;
        mSpread3 = Spread3;
        mInitialValue1 = InitialValue1;
        mInitialValue2 = InitialValue2;
        mAccrualFactor = AccrualFactor;
      };

    void Execute();
};

class RatchetPayoffWorker {
  public:
    string mObjectID;
    double mGearing1;
    double mGearing2;
    double mSpread1;
    double mSpread2;
    double mInitialValue;
    double mAccrualFactor;

    string mReturnValue;

    string mError;

    RatchetPayoffWorker(
      string ObjectID
,       double Gearing1
,       double Gearing2
,       double Spread1
,       double Spread2
,       double InitialValue
,       double AccrualFactor
     )
      {
        mObjectID = ObjectID;
        mGearing1 = Gearing1;
        mGearing2 = Gearing2;
        mSpread1 = Spread1;
        mSpread2 = Spread2;
        mInitialValue = InitialValue;
        mAccrualFactor = AccrualFactor;
      };

    void Execute();
};

class StickyPayoffWorker {
  public:
    string mObjectID;
    double mGearing1;
    double mGearing2;
    double mSpread1;
    double mSpread2;
    double mInitialValue;
    double mAccrualFactor;

    string mReturnValue;

    string mError;

    StickyPayoffWorker(
      string ObjectID
,       double Gearing1
,       double Gearing2
,       double Spread1
,       double Spread2
,       double InitialValue
,       double AccrualFactor
     )
      {
        mObjectID = ObjectID;
        mGearing1 = Gearing1;
        mGearing2 = Gearing2;
        mSpread1 = Spread1;
        mSpread2 = Spread2;
        mInitialValue = InitialValue;
        mAccrualFactor = AccrualFactor;
      };

    void Execute();
};

class RatchetMaxPayoffWorker {
  public:
    string mObjectID;
    double mGearing1;
    double mGearing2;
    double mGearing3;
    double mSpread1;
    double mSpread2;
    double mSpread3;
    double mInitialValue1;
    double mInitialValue2;
    double mAccrualFactor;

    string mReturnValue;

    string mError;

    RatchetMaxPayoffWorker(
      string ObjectID
,       double Gearing1
,       double Gearing2
,       double Gearing3
,       double Spread1
,       double Spread2
,       double Spread3
,       double InitialValue1
,       double InitialValue2
,       double AccrualFactor
     )
      {
        mObjectID = ObjectID;
        mGearing1 = Gearing1;
        mGearing2 = Gearing2;
        mGearing3 = Gearing3;
        mSpread1 = Spread1;
        mSpread2 = Spread2;
        mSpread3 = Spread3;
        mInitialValue1 = InitialValue1;
        mInitialValue2 = InitialValue2;
        mAccrualFactor = AccrualFactor;
      };

    void Execute();
};

class RatchetMinPayoffWorker {
  public:
    string mObjectID;
    double mGearing1;
    double mGearing2;
    double mGearing3;
    double mSpread1;
    double mSpread2;
    double mSpread3;
    double mInitialValue1;
    double mInitialValue2;
    double mAccrualFactor;

    string mReturnValue;

    string mError;

    RatchetMinPayoffWorker(
      string ObjectID
,       double Gearing1
,       double Gearing2
,       double Gearing3
,       double Spread1
,       double Spread2
,       double Spread3
,       double InitialValue1
,       double InitialValue2
,       double AccrualFactor
     )
      {
        mObjectID = ObjectID;
        mGearing1 = Gearing1;
        mGearing2 = Gearing2;
        mGearing3 = Gearing3;
        mSpread1 = Spread1;
        mSpread2 = Spread2;
        mSpread3 = Spread3;
        mInitialValue1 = InitialValue1;
        mInitialValue2 = InitialValue2;
        mAccrualFactor = AccrualFactor;
      };

    void Execute();
};

class StickyMaxPayoffWorker {
  public:
    string mObjectID;
    double mGearing1;
    double mGearing2;
    double mGearing3;
    double mSpread1;
    double mSpread2;
    double mSpread3;
    double mInitialValue1;
    double mInitialValue2;
    double mAccrualFactor;

    string mReturnValue;

    string mError;

    StickyMaxPayoffWorker(
      string ObjectID
,       double Gearing1
,       double Gearing2
,       double Gearing3
,       double Spread1
,       double Spread2
,       double Spread3
,       double InitialValue1
,       double InitialValue2
,       double AccrualFactor
     )
      {
        mObjectID = ObjectID;
        mGearing1 = Gearing1;
        mGearing2 = Gearing2;
        mGearing3 = Gearing3;
        mSpread1 = Spread1;
        mSpread2 = Spread2;
        mSpread3 = Spread3;
        mInitialValue1 = InitialValue1;
        mInitialValue2 = InitialValue2;
        mAccrualFactor = AccrualFactor;
      };

    void Execute();
};

class StickyMinPayoffWorker {
  public:
    string mObjectID;
    double mGearing1;
    double mGearing2;
    double mGearing3;
    double mSpread1;
    double mSpread2;
    double mSpread3;
    double mInitialValue1;
    double mInitialValue2;
    double mAccrualFactor;

    string mReturnValue;

    string mError;

    StickyMinPayoffWorker(
      string ObjectID
,       double Gearing1
,       double Gearing2
,       double Gearing3
,       double Spread1
,       double Spread2
,       double Spread3
,       double InitialValue1
,       double InitialValue2
,       double AccrualFactor
     )
      {
        mObjectID = ObjectID;
        mGearing1 = Gearing1;
        mGearing2 = Gearing2;
        mGearing3 = Gearing3;
        mSpread1 = Spread1;
        mSpread2 = Spread2;
        mSpread3 = Spread3;
        mInitialValue1 = InitialValue1;
        mInitialValue2 = InitialValue2;
        mAccrualFactor = AccrualFactor;
      };

    void Execute();
};

class PayoffNameWorker {
  public:
    string mObjectID;

    string mReturnValue;

    string mError;

    PayoffNameWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class PayoffDescriptionWorker {
  public:
    string mObjectID;

    string mReturnValue;

    string mError;

    PayoffDescriptionWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class PayoffValueWorker {
  public:
    string mObjectID;
    double mUnderlying;

    double mReturnValue;

    string mError;

    PayoffValueWorker(
      string ObjectID
,       double Underlying
     )
      {
        mObjectID = ObjectID;
        mUnderlying = Underlying;
      };

    void Execute();
};

class PayoffOptionTypeWorker {
  public:
    string mObjectID;

    string mReturnValue;

    string mError;

    PayoffOptionTypeWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class PayoffStrikeWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    PayoffStrikeWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class PayoffThirdParameterWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    PayoffThirdParameterWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};
 
#endif
