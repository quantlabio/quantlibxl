/* 
  Copyright (C) 2016 -2017 Jerry Jin
*/

#ifndef calendar_h
#define calendar_h
#include <nan.h>
#include <string>
#include <queue>
#include <utility>

#include "../quantlibxl.hpp"

#include <oh/objecthandler.hpp>

using namespace node;
using namespace v8;
using namespace std;


class CalendarHolidayListWorker {
  public:
    string mCalendar;
    ObjectHandler::property_t mFromDate;
    ObjectHandler::property_t mToDate;
    bool mIncludeWeekEnds;

    std::vector<long> mReturnValue;

    string mError;

    CalendarHolidayListWorker(
      string Calendar
,       ObjectHandler::property_t FromDate
,       ObjectHandler::property_t ToDate
,       bool IncludeWeekEnds
     )
      {
        mCalendar = Calendar;
        mFromDate = FromDate;
        mToDate = ToDate;
        mIncludeWeekEnds = IncludeWeekEnds;
      };

    void Execute();
};

class CalendarNameWorker {
  public:
    string mCalendar;

    string mReturnValue;

    string mError;

    CalendarNameWorker(
      string Calendar
     )
      {
        mCalendar = Calendar;
      };

    void Execute();
};

class CalendarIsBusinessDayWorker {
  public:
    string mCalendar;
    std::vector<ObjectHandler::property_t> mDate;

    std::vector<bool> mReturnValue;

    string mError;

    CalendarIsBusinessDayWorker(
      string Calendar
,       std::vector<ObjectHandler::property_t> Date
     )
      {
        mCalendar = Calendar;
        mDate = Date;
      };

    void Execute();
};

class CalendarIsHolidayWorker {
  public:
    string mCalendar;
    std::vector<ObjectHandler::property_t> mDate;

    std::vector<bool> mReturnValue;

    string mError;

    CalendarIsHolidayWorker(
      string Calendar
,       std::vector<ObjectHandler::property_t> Date
     )
      {
        mCalendar = Calendar;
        mDate = Date;
      };

    void Execute();
};

class CalendarIsEndOfMonthWorker {
  public:
    string mCalendar;
    std::vector<ObjectHandler::property_t> mDate;

    std::vector<bool> mReturnValue;

    string mError;

    CalendarIsEndOfMonthWorker(
      string Calendar
,       std::vector<ObjectHandler::property_t> Date
     )
      {
        mCalendar = Calendar;
        mDate = Date;
      };

    void Execute();
};

class CalendarEndOfMonthWorker {
  public:
    string mCalendar;
    std::vector<ObjectHandler::property_t> mDate;

    std::vector<long> mReturnValue;

    string mError;

    CalendarEndOfMonthWorker(
      string Calendar
,       std::vector<ObjectHandler::property_t> Date
     )
      {
        mCalendar = Calendar;
        mDate = Date;
      };

    void Execute();
};

class CalendarAddHolidayWorker {
  public:
    string mCalendar;
    ObjectHandler::property_t mDate;

    string mError;

    CalendarAddHolidayWorker(
      string Calendar
,       ObjectHandler::property_t Date
     )
      {
        mCalendar = Calendar;
        mDate = Date;
      };

    void Execute();
};

class CalendarRemoveHolidayWorker {
  public:
    string mCalendar;
    ObjectHandler::property_t mDate;

    string mError;

    CalendarRemoveHolidayWorker(
      string Calendar
,       ObjectHandler::property_t Date
     )
      {
        mCalendar = Calendar;
        mDate = Date;
      };

    void Execute();
};

class CalendarAdjustWorker {
  public:
    string mCalendar;
    std::vector<ObjectHandler::property_t> mDate;
    string mBusinessDayConvention;

    std::vector<long> mReturnValue;

    string mError;

    CalendarAdjustWorker(
      string Calendar
,       std::vector<ObjectHandler::property_t> Date
,       string BusinessDayConvention
     )
      {
        mCalendar = Calendar;
        mDate = Date;
        mBusinessDayConvention = BusinessDayConvention;
      };

    void Execute();
};

class CalendarAdvanceWorker {
  public:
    string mCalendar;
    ObjectHandler::property_t mStartDate;
    std::vector<ObjectHandler::property_t> mPeriod;
    string mBusinessDayConvention;
    bool mEndOfMonth;

    std::vector<long> mReturnValue;

    string mError;

    CalendarAdvanceWorker(
      string Calendar
,       ObjectHandler::property_t StartDate
,       std::vector<ObjectHandler::property_t> Period
,       string BusinessDayConvention
,       bool EndOfMonth
     )
      {
        mCalendar = Calendar;
        mStartDate = StartDate;
        mPeriod = Period;
        mBusinessDayConvention = BusinessDayConvention;
        mEndOfMonth = EndOfMonth;
      };

    void Execute();
};

class CalendarBusinessDaysBetweenWorker {
  public:
    string mCalendar;
    std::vector<ObjectHandler::property_t> mFirstDate;
    ObjectHandler::property_t mLastDate;
    bool mIncludeFirst;
    bool mIncludeLast;

    std::vector<long> mReturnValue;

    string mError;

    CalendarBusinessDaysBetweenWorker(
      string Calendar
,       std::vector<ObjectHandler::property_t> FirstDate
,       ObjectHandler::property_t LastDate
,       bool IncludeFirst
,       bool IncludeLast
     )
      {
        mCalendar = Calendar;
        mFirstDate = FirstDate;
        mLastDate = LastDate;
        mIncludeFirst = IncludeFirst;
        mIncludeLast = IncludeLast;
      };

    void Execute();
};
 
#endif
