/* 
  Copyright (C) 2016 -2017 Jerry Jin
*/

#ifndef date_h
#define date_h
#include <nan.h>
#include <string>
#include <queue>
#include <utility>

#include "../quantlibxl.hpp"

#include <oh/objecthandler.hpp>

using namespace node;
using namespace v8;
using namespace std;


class PeriodFromFrequencyWorker {
  public:
    string mFrequency;

    string mReturnValue;

    string mError;

    PeriodFromFrequencyWorker(
      string Frequency
     )
      {
        mFrequency = Frequency;
      };

    void Execute();
};

class FrequencyFromPeriodWorker {
  public:
    std::vector<ObjectHandler::property_t> mPeriod;

    std::vector<string> mReturnValue;

    string mError;

    FrequencyFromPeriodWorker(
      std::vector<ObjectHandler::property_t> Period
     )
      {
        mPeriod = Period;
      };

    void Execute();
};

class PeriodLessThanWorker {
  public:
    string mPeriod1;
    string mPeriod2;

    bool mReturnValue;

    string mError;

    PeriodLessThanWorker(
      string Period1
,       string Period2
     )
      {
        mPeriod1 = Period1;
        mPeriod2 = Period2;
      };

    void Execute();
};

class PeriodEquivalentWorker {
  public:
    string mPeriod;

    string mReturnValue;

    string mError;

    PeriodEquivalentWorker(
      string Period
     )
      {
        mPeriod = Period;
      };

    void Execute();
};

class DateMinDateWorker {
  public:

    long mReturnValue;

    string mError;

    DateMinDateWorker(
    )
      {
      };

    void Execute();
};

class DateMaxDateWorker {
  public:

    long mReturnValue;

    string mError;

    DateMaxDateWorker(
    )
      {
      };

    void Execute();
};

class DateIsLeapWorker {
  public:
    std::vector<long> mYear;

    std::vector<bool> mReturnValue;

    string mError;

    DateIsLeapWorker(
      std::vector<long> Year
     )
      {
        mYear = Year;
      };

    void Execute();
};

class DateEndOfMonthWorker {
  public:
    std::vector<ObjectHandler::property_t> mDate;

    std::vector<long> mReturnValue;

    string mError;

    DateEndOfMonthWorker(
      std::vector<ObjectHandler::property_t> Date
     )
      {
        mDate = Date;
      };

    void Execute();
};

class DateIsEndOfMonthWorker {
  public:
    std::vector<ObjectHandler::property_t> mDate;

    std::vector<bool> mReturnValue;

    string mError;

    DateIsEndOfMonthWorker(
      std::vector<ObjectHandler::property_t> Date
     )
      {
        mDate = Date;
      };

    void Execute();
};

class DateNextWeekdayWorker {
  public:
    std::vector<ObjectHandler::property_t> mDate;
    string mWeekday;

    std::vector<long> mReturnValue;

    string mError;

    DateNextWeekdayWorker(
      std::vector<ObjectHandler::property_t> Date
,       string Weekday
     )
      {
        mDate = Date;
        mWeekday = Weekday;
      };

    void Execute();
};

class DateNthWeekdayWorker {
  public:
    long mNth;
    string mWeekday;
    string mMonth;
    long mYear;

    long mReturnValue;

    string mError;

    DateNthWeekdayWorker(
      long Nth
,       string Weekday
,       string Month
,       long Year
     )
      {
        mNth = Nth;
        mWeekday = Weekday;
        mMonth = Month;
        mYear = Year;
      };

    void Execute();
};

class IMMIsIMMdateWorker {
  public:
    std::vector<ObjectHandler::property_t> mDate;
    bool mMainCycle;

    std::vector<bool> mReturnValue;

    string mError;

    IMMIsIMMdateWorker(
      std::vector<ObjectHandler::property_t> Date
,       bool MainCycle
     )
      {
        mDate = Date;
        mMainCycle = MainCycle;
      };

    void Execute();
};

class IMMIsIMMcodeWorker {
  public:
    std::vector<string> mCode;
    bool mMainCycle;

    std::vector<bool> mReturnValue;

    string mError;

    IMMIsIMMcodeWorker(
      std::vector<string> Code
,       bool MainCycle
     )
      {
        mCode = Code;
        mMainCycle = MainCycle;
      };

    void Execute();
};

class IMMcodeWorker {
  public:
    std::vector<ObjectHandler::property_t> mIMMdate;

    std::vector<string> mReturnValue;

    string mError;

    IMMcodeWorker(
      std::vector<ObjectHandler::property_t> IMMdate
     )
      {
        mIMMdate = IMMdate;
      };

    void Execute();
};

class IMMNextCodeWorker {
  public:
    ObjectHandler::property_t mRefDate;
    bool mMainCycle;

    string mReturnValue;

    string mError;

    IMMNextCodeWorker(
      ObjectHandler::property_t RefDate
,       bool MainCycle
     )
      {
        mRefDate = RefDate;
        mMainCycle = MainCycle;
      };

    void Execute();
};

class IMMNextCodesWorker {
  public:
    ObjectHandler::property_t mRefDate;
    std::vector<bool> mMainCycle;

    std::vector<string> mReturnValue;

    string mError;

    IMMNextCodesWorker(
      ObjectHandler::property_t RefDate
,       std::vector<bool> MainCycle
     )
      {
        mRefDate = RefDate;
        mMainCycle = MainCycle;
      };

    void Execute();
};

class IMMdateWorker {
  public:
    std::vector<string> mIMMcode;
    ObjectHandler::property_t mRefDate;

    std::vector<long> mReturnValue;

    string mError;

    IMMdateWorker(
      std::vector<string> IMMcode
,       ObjectHandler::property_t RefDate
     )
      {
        mIMMcode = IMMcode;
        mRefDate = RefDate;
      };

    void Execute();
};

class IMMNextDateWorker {
  public:
    ObjectHandler::property_t mRefDate;
    bool mMainCycle;

    long mReturnValue;

    string mError;

    IMMNextDateWorker(
      ObjectHandler::property_t RefDate
,       bool MainCycle
     )
      {
        mRefDate = RefDate;
        mMainCycle = MainCycle;
      };

    void Execute();
};

class IMMNextDatesWorker {
  public:
    ObjectHandler::property_t mRefDate;
    std::vector<bool> mMainCycle;

    std::vector<long> mReturnValue;

    string mError;

    IMMNextDatesWorker(
      ObjectHandler::property_t RefDate
,       std::vector<bool> MainCycle
     )
      {
        mRefDate = RefDate;
        mMainCycle = MainCycle;
      };

    void Execute();
};

class ASXIsASXdateWorker {
  public:
    std::vector<ObjectHandler::property_t> mDate;
    bool mMainCycle;

    std::vector<bool> mReturnValue;

    string mError;

    ASXIsASXdateWorker(
      std::vector<ObjectHandler::property_t> Date
,       bool MainCycle
     )
      {
        mDate = Date;
        mMainCycle = MainCycle;
      };

    void Execute();
};

class ASXIsASXcodeWorker {
  public:
    std::vector<string> mCode;
    bool mMainCycle;

    std::vector<bool> mReturnValue;

    string mError;

    ASXIsASXcodeWorker(
      std::vector<string> Code
,       bool MainCycle
     )
      {
        mCode = Code;
        mMainCycle = MainCycle;
      };

    void Execute();
};

class ASXcodeWorker {
  public:
    std::vector<ObjectHandler::property_t> mASXdate;

    std::vector<string> mReturnValue;

    string mError;

    ASXcodeWorker(
      std::vector<ObjectHandler::property_t> ASXdate
     )
      {
        mASXdate = ASXdate;
      };

    void Execute();
};

class ASXNextCodeWorker {
  public:
    ObjectHandler::property_t mRefDate;
    bool mMainCycle;

    string mReturnValue;

    string mError;

    ASXNextCodeWorker(
      ObjectHandler::property_t RefDate
,       bool MainCycle
     )
      {
        mRefDate = RefDate;
        mMainCycle = MainCycle;
      };

    void Execute();
};

class ASXNextCodesWorker {
  public:
    ObjectHandler::property_t mRefDate;
    std::vector<bool> mMainCycle;

    std::vector<string> mReturnValue;

    string mError;

    ASXNextCodesWorker(
      ObjectHandler::property_t RefDate
,       std::vector<bool> MainCycle
     )
      {
        mRefDate = RefDate;
        mMainCycle = MainCycle;
      };

    void Execute();
};

class ASXdateWorker {
  public:
    std::vector<string> mASXcode;
    ObjectHandler::property_t mRefDate;

    std::vector<long> mReturnValue;

    string mError;

    ASXdateWorker(
      std::vector<string> ASXcode
,       ObjectHandler::property_t RefDate
     )
      {
        mASXcode = ASXcode;
        mRefDate = RefDate;
      };

    void Execute();
};

class ASXNextDateWorker {
  public:
    ObjectHandler::property_t mRefDate;
    bool mMainCycle;

    long mReturnValue;

    string mError;

    ASXNextDateWorker(
      ObjectHandler::property_t RefDate
,       bool MainCycle
     )
      {
        mRefDate = RefDate;
        mMainCycle = MainCycle;
      };

    void Execute();
};

class ASXNextDatesWorker {
  public:
    ObjectHandler::property_t mRefDate;
    std::vector<bool> mMainCycle;

    std::vector<long> mReturnValue;

    string mError;

    ASXNextDatesWorker(
      ObjectHandler::property_t RefDate
,       std::vector<bool> MainCycle
     )
      {
        mRefDate = RefDate;
        mMainCycle = MainCycle;
      };

    void Execute();
};

class ECBKnownDatesWorker {
  public:

    std::vector<long> mReturnValue;

    string mError;

    ECBKnownDatesWorker(
    )
      {
      };

    void Execute();
};

class ECBAddDateWorker {
  public:
    ObjectHandler::property_t mDate;

    string mError;

    ECBAddDateWorker(
      ObjectHandler::property_t Date
     )
      {
        mDate = Date;
      };

    void Execute();
};

class ECBRemoveDateWorker {
  public:
    ObjectHandler::property_t mDate;

    string mError;

    ECBRemoveDateWorker(
      ObjectHandler::property_t Date
     )
      {
        mDate = Date;
      };

    void Execute();
};

class ECBdate2Worker {
  public:
    string mMonth;
    long mYear;

    long mReturnValue;

    string mError;

    ECBdate2Worker(
      string Month
,       long Year
     )
      {
        mMonth = Month;
        mYear = Year;
      };

    void Execute();
};

class ECBdateWorker {
  public:
    string mECBcode;
    ObjectHandler::property_t mRefDate;

    long mReturnValue;

    string mError;

    ECBdateWorker(
      string ECBcode
,       ObjectHandler::property_t RefDate
     )
      {
        mECBcode = ECBcode;
        mRefDate = RefDate;
      };

    void Execute();
};

class ECBcodeWorker {
  public:
    ObjectHandler::property_t mECBdate;

    string mReturnValue;

    string mError;

    ECBcodeWorker(
      ObjectHandler::property_t ECBdate
     )
      {
        mECBdate = ECBdate;
      };

    void Execute();
};

class ECBNextDateWorker {
  public:
    ObjectHandler::property_t mDate;

    long mReturnValue;

    string mError;

    ECBNextDateWorker(
      ObjectHandler::property_t Date
     )
      {
        mDate = Date;
      };

    void Execute();
};

class ECBNextDate2Worker {
  public:
    string mCode;

    long mReturnValue;

    string mError;

    ECBNextDate2Worker(
      string Code
     )
      {
        mCode = Code;
      };

    void Execute();
};

class ECBNextDatesWorker {
  public:
    ObjectHandler::property_t mDate;

    std::vector<long> mReturnValue;

    string mError;

    ECBNextDatesWorker(
      ObjectHandler::property_t Date
     )
      {
        mDate = Date;
      };

    void Execute();
};

class ECBIsECBdateWorker {
  public:
    std::vector<ObjectHandler::property_t> mDate;

    std::vector<bool> mReturnValue;

    string mError;

    ECBIsECBdateWorker(
      std::vector<ObjectHandler::property_t> Date
     )
      {
        mDate = Date;
      };

    void Execute();
};

class ECBIsECBcodeWorker {
  public:
    std::vector<string> mCode;

    std::vector<bool> mReturnValue;

    string mError;

    ECBIsECBcodeWorker(
      std::vector<string> Code
     )
      {
        mCode = Code;
      };

    void Execute();
};

class ECBNextCodeWorker {
  public:
    ObjectHandler::property_t mRefDate;

    string mReturnValue;

    string mError;

    ECBNextCodeWorker(
      ObjectHandler::property_t RefDate
     )
      {
        mRefDate = RefDate;
      };

    void Execute();
};

class ECBNextCode2Worker {
  public:
    string mCode;

    string mReturnValue;

    string mError;

    ECBNextCode2Worker(
      string Code
     )
      {
        mCode = Code;
      };

    void Execute();
};
 
#endif
