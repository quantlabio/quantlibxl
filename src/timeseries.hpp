/* 
  Copyright (C) 2016 -2017 Jerry Jin
*/

#ifndef timeseries_h
#define timeseries_h
#include <nan.h>
#include <string>
#include <queue>
#include <utility>

#include "../quantlibxl.hpp"

#include <oh/objecthandler.hpp>

using namespace node;
using namespace v8;
using namespace std;


class TimeSeriesWorker {
  public:
    string mObjectID;
    std::vector<ObjectHandler::property_t> mDates;
    std::vector<double> mValues;

    string mReturnValue;

    string mError;

    TimeSeriesWorker(
      string ObjectID
,       std::vector<ObjectHandler::property_t> Dates
,       std::vector<double> Values
     )
      {
        mObjectID = ObjectID;
        mDates = Dates;
        mValues = Values;
      };

    void Execute();
};

class TimeSeriesFromIndexWorker {
  public:
    string mObjectID;
    string mIndex;

    string mReturnValue;

    string mError;

    TimeSeriesFromIndexWorker(
      string ObjectID
,       string Index
     )
      {
        mObjectID = ObjectID;
        mIndex = Index;
      };

    void Execute();
};

class TimeSeriesFirstDateWorker {
  public:
    string mObjectID;

    long mReturnValue;

    string mError;

    TimeSeriesFirstDateWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class TimeSeriesLastDateWorker {
  public:
    string mObjectID;

    long mReturnValue;

    string mError;

    TimeSeriesLastDateWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class TimeSeriesSizeWorker {
  public:
    string mObjectID;

    long mReturnValue;

    string mError;

    TimeSeriesSizeWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class TimeSeriesEmptyWorker {
  public:
    string mObjectID;

    bool mReturnValue;

    string mError;

    TimeSeriesEmptyWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class TimeSeriesDatesWorker {
  public:
    string mObjectID;

    std::vector<long> mReturnValue;

    string mError;

    TimeSeriesDatesWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class TimeSeriesValuesWorker {
  public:
    string mObjectID;

    std::vector<double> mReturnValue;

    string mError;

    TimeSeriesValuesWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class TimeSeriesValueWorker {
  public:
    string mObjectID;
    std::vector<ObjectHandler::property_t> mDates;

    std::vector<double> mReturnValue;

    string mError;

    TimeSeriesValueWorker(
      string ObjectID
,       std::vector<ObjectHandler::property_t> Dates
     )
      {
        mObjectID = ObjectID;
        mDates = Dates;
      };

    void Execute();
};
 
#endif
