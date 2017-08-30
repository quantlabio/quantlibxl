/* 
  Copyright (C) 2016 -2017 Jerry Jin
*/

#ifndef schedule_h
#define schedule_h
#include <nan.h>
#include <string>
#include <queue>
#include <utility>

#include "../quantlibxl.hpp"

#include <oh/objecthandler.hpp>

using namespace node;
using namespace v8;
using namespace std;


class ScheduleWorker {
  public:
    string mObjectID;
    ObjectHandler::property_t mEffectiveDate;
    ObjectHandler::property_t mTerminationDate;
    string mTenor;
    string mCalendar;
    string mConvention;
    string mTermDateConv;
    string mGenRule;
    bool mEndOfMonth;
    ObjectHandler::property_t mFirstDate;
    ObjectHandler::property_t mNextToLastDate;

    string mReturnValue;

    string mError;

    ScheduleWorker(
      string ObjectID
,       ObjectHandler::property_t EffectiveDate
,       ObjectHandler::property_t TerminationDate
,       string Tenor
,       string Calendar
,       string Convention
,       string TermDateConv
,       string GenRule
,       bool EndOfMonth
,       ObjectHandler::property_t FirstDate
,       ObjectHandler::property_t NextToLastDate
     )
      {
        mObjectID = ObjectID;
        mEffectiveDate = EffectiveDate;
        mTerminationDate = TerminationDate;
        mTenor = Tenor;
        mCalendar = Calendar;
        mConvention = Convention;
        mTermDateConv = TermDateConv;
        mGenRule = GenRule;
        mEndOfMonth = EndOfMonth;
        mFirstDate = FirstDate;
        mNextToLastDate = NextToLastDate;
      };

    void Execute();
};

class ScheduleFromDateVectorWorker {
  public:
    string mObjectID;
    std::vector<ObjectHandler::property_t> mEffectiveDate;

    string mReturnValue;

    string mError;

    ScheduleFromDateVectorWorker(
      string ObjectID
,       std::vector<ObjectHandler::property_t> EffectiveDate
     )
      {
        mObjectID = ObjectID;
        mEffectiveDate = EffectiveDate;
      };

    void Execute();
};

class ScheduleTruncatedWorker {
  public:
    string mObjectID;
    string mOriginalSchedule;
    ObjectHandler::property_t mTruncationDate;

    string mReturnValue;

    string mError;

    ScheduleTruncatedWorker(
      string ObjectID
,       string OriginalSchedule
,       ObjectHandler::property_t TruncationDate
     )
      {
        mObjectID = ObjectID;
        mOriginalSchedule = OriginalSchedule;
        mTruncationDate = TruncationDate;
      };

    void Execute();
};

class ScheduleSizeWorker {
  public:
    string mObjectID;

    long mReturnValue;

    string mError;

    ScheduleSizeWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class SchedulePreviousDateWorker {
  public:
    string mObjectID;
    ObjectHandler::property_t mRefDate;

    long mReturnValue;

    string mError;

    SchedulePreviousDateWorker(
      string ObjectID
,       ObjectHandler::property_t RefDate
     )
      {
        mObjectID = ObjectID;
        mRefDate = RefDate;
      };

    void Execute();
};

class ScheduleNextDateWorker {
  public:
    string mObjectID;
    ObjectHandler::property_t mRefDate;

    long mReturnValue;

    string mError;

    ScheduleNextDateWorker(
      string ObjectID
,       ObjectHandler::property_t RefDate
     )
      {
        mObjectID = ObjectID;
        mRefDate = RefDate;
      };

    void Execute();
};

class ScheduleDatesWorker {
  public:
    string mObjectID;

    std::vector<long> mReturnValue;

    string mError;

    ScheduleDatesWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class ScheduleIsRegularWorker {
  public:
    string mObjectID;
    long mIndex;

    bool mReturnValue;

    string mError;

    ScheduleIsRegularWorker(
      string ObjectID
,       long Index
     )
      {
        mObjectID = ObjectID;
        mIndex = Index;
      };

    void Execute();
};

class ScheduleEmptyWorker {
  public:
    string mObjectID;

    bool mReturnValue;

    string mError;

    ScheduleEmptyWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class ScheduleCalendarWorker {
  public:
    string mObjectID;

    string mReturnValue;

    string mError;

    ScheduleCalendarWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class ScheduleStartDateWorker {
  public:
    string mObjectID;

    long mReturnValue;

    string mError;

    ScheduleStartDateWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class ScheduleEndDateWorker {
  public:
    string mObjectID;

    long mReturnValue;

    string mError;

    ScheduleEndDateWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class ScheduleTenorWorker {
  public:
    string mObjectID;

    string mReturnValue;

    string mError;

    ScheduleTenorWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class ScheduleBDCWorker {
  public:
    string mObjectID;

    string mReturnValue;

    string mError;

    ScheduleBDCWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class ScheduleTerminationDateBDCWorker {
  public:
    string mObjectID;

    string mReturnValue;

    string mError;

    ScheduleTerminationDateBDCWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class ScheduleRuleWorker {
  public:
    string mObjectID;

    string mReturnValue;

    string mError;

    ScheduleRuleWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class ScheduleEndOfMonthWorker {
  public:
    string mObjectID;

    bool mReturnValue;

    string mError;

    ScheduleEndOfMonthWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};
 
#endif
