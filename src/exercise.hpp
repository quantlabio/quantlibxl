/* 
  Copyright (C) 2016 -2017 Jerry Jin
*/

#ifndef exercise_h
#define exercise_h
#include <nan.h>
#include <string>
#include <queue>
#include <utility>

#include "../quantlibxl.hpp"

#include <oh/objecthandler.hpp>

using namespace node;
using namespace v8;
using namespace std;


class AmericanExerciseWorker {
  public:
    string mObjectID;
    ObjectHandler::property_t mEarliestDate;
    ObjectHandler::property_t mLatestDate;
    bool mPayoffAtExpiry;

    string mReturnValue;

    string mError;

    AmericanExerciseWorker(
      string ObjectID
,       ObjectHandler::property_t EarliestDate
,       ObjectHandler::property_t LatestDate
,       bool PayoffAtExpiry
     )
      {
        mObjectID = ObjectID;
        mEarliestDate = EarliestDate;
        mLatestDate = LatestDate;
        mPayoffAtExpiry = PayoffAtExpiry;
      };

    void Execute();
};

class EuropeanExerciseWorker {
  public:
    string mObjectID;
    ObjectHandler::property_t mExpiryDate;

    string mReturnValue;

    string mError;

    EuropeanExerciseWorker(
      string ObjectID
,       ObjectHandler::property_t ExpiryDate
     )
      {
        mObjectID = ObjectID;
        mExpiryDate = ExpiryDate;
      };

    void Execute();
};

class BermudanExerciseWorker {
  public:
    string mObjectID;
    std::vector<ObjectHandler::property_t> mDates;
    bool mPayoffAtExpiry;

    string mReturnValue;

    string mError;

    BermudanExerciseWorker(
      string ObjectID
,       std::vector<ObjectHandler::property_t> Dates
,       bool PayoffAtExpiry
     )
      {
        mObjectID = ObjectID;
        mDates = Dates;
        mPayoffAtExpiry = PayoffAtExpiry;
      };

    void Execute();
};

class ExerciseDatesWorker {
  public:
    string mObjectID;

    std::vector<long> mReturnValue;

    string mError;

    ExerciseDatesWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class ExerciseLastDateWorker {
  public:
    string mObjectID;

    long mReturnValue;

    string mError;

    ExerciseLastDateWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};
 
#endif
