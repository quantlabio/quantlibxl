/* 
  Copyright (C) 2016 -2017 Jerry Jin
*/

#ifndef alphaform_h
#define alphaform_h
#include <nan.h>
#include <string>
#include <queue>
#include <utility>

#include "../quantlibxl.hpp"

#include <oh/objecthandler.hpp>

using namespace node;
using namespace v8;
using namespace std;


class AlphaFormInverseLinearWorker {
  public:
    string mObjectID;
    std::vector<double> mRateTimes;
    double mAlpha;

    string mReturnValue;

    string mError;

    AlphaFormInverseLinearWorker(
      string ObjectID
,       std::vector<double> RateTimes
,       double Alpha
     )
      {
        mObjectID = ObjectID;
        mRateTimes = RateTimes;
        mAlpha = Alpha;
      };

    void Execute();
};

class AlphaFormLinearHyperbolicWorker {
  public:
    string mObjectID;
    std::vector<double> mRateTimes;
    double mAlpha;

    string mReturnValue;

    string mError;

    AlphaFormLinearHyperbolicWorker(
      string ObjectID
,       std::vector<double> RateTimes
,       double Alpha
     )
      {
        mObjectID = ObjectID;
        mRateTimes = RateTimes;
        mAlpha = Alpha;
      };

    void Execute();
};

class AlphaFormOperatorWorker {
  public:
    string mObjectID;
    long mTime;

    double mReturnValue;

    string mError;

    AlphaFormOperatorWorker(
      string ObjectID
,       long Time
     )
      {
        mObjectID = ObjectID;
        mTime = Time;
      };

    void Execute();
};

class AlphaFormSetAlphaWorker {
  public:
    string mObjectID;
    double mAlpha;

    string mError;

    AlphaFormSetAlphaWorker(
      string ObjectID
,       double Alpha
     )
      {
        mObjectID = ObjectID;
        mAlpha = Alpha;
      };

    void Execute();
};
 
#endif
