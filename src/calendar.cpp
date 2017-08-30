/* 
  Copyright (C) 2016 -2017 Jerry Jin
*/

#include <nan.h>
#include <string.h>

#include "calendar.hpp"

#include <qlo/qladdindefines.hpp>
#include <ql/time/date.hpp>
#include <ql/time/calendar.hpp>
#include <qlo/loop/loop_calendar.hpp>
 #include <oh/objecthandler.hpp>
#include <oh/conversions/getobjectvector.hpp>
#include <qlo/valueobjects/vo_all.hpp>
#include <qlo/conversions/all.hpp>
#include "../loop.hpp"


void CalendarHolidayListWorker::Execute(){

  try{

  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::Calendar CalendarEnum =
      ObjectHandler::Create<QuantLib::Calendar>()(mCalendar);


  // convert input datatypes to QuantLib datatypes
  QuantLib::Date FromDateLib = ObjectHandler::convert2<QuantLib::Date>(
      mFromDate, "FromDate");


  // convert input datatypes to QuantLib datatypes
  QuantLib::Date ToDateLib = ObjectHandler::convert2<QuantLib::Date>(
      mToDate, "ToDate");

       // invoke the utility function
  std::vector<QuantLib::Date> returnValue = QuantLib::Calendar::holidayList(
      CalendarEnum
      ,
       FromDateLib
      ,
       ToDateLib
      ,
       mIncludeWeekEnds
   );


  mReturnValue = QuantLibAddin::libraryToVector(returnValue);

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::CalendarHolidayList) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("Calendar is required.");
  }
  if (info.Length() == 3 || !info[3]->IsBoolean()) {
      return Nan::ThrowError("IncludeWeekEnds is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strCalendar(info[0]->ToString());
  string CalendarCpp(strdup(*strCalendar));

  // convert js argument to c++ type
  ObjectHandler::property_t FromDateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[1]).FromJust()));

  // convert js argument to c++ type
  ObjectHandler::property_t ToDateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[2]).FromJust()));

  // convert js argument to c++ type
  bool IncludeWeekEndsCpp = Nan::To<bool>(info[3]).FromJust();

 
  // launch worker
  CalendarHolidayListWorker* worker = new CalendarHolidayListWorker(
    CalendarCpp
,     FromDateCpp
,     ToDateCpp
,     IncludeWeekEndsCpp
   );

  worker->Execute();

    Local<Array> tmpArray = Nan::New<Array>(worker->mReturnValue.size());
    for (unsigned int i = 0; i < worker->mReturnValue.size(); i++) {
      Nan::Set(tmpArray,i,Nan::New<Number>(worker->mReturnValue[i]));
    }

  Local<v8::Value> argv[2] = {
		  Nan::New<String>(worker->mError).ToLocalChecked(),
      tmpArray
	};

  v8::Local<v8::Array> results = Nan::New<v8::Array>();
  Nan::Set(results, 0, argv[0]);
  Nan::Set(results, 1, argv[1]);
  info.GetReturnValue().Set(results);
}

void CalendarNameWorker::Execute(){

  try{
       // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::Calendar calendarEnum =
      ObjectHandler::Create<QuantLib::Calendar>()(mCalendar);

  // invoke the member function
  mReturnValue = calendarEnum.name(
      );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::CalendarName) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("Calendar is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strCalendar(info[0]->ToString());
  string CalendarCpp(strdup(*strCalendar));

 
  // launch worker
  CalendarNameWorker* worker = new CalendarNameWorker(
    CalendarCpp
   );

  worker->Execute();


  Local<v8::Value> argv[2] = {
		  Nan::New<String>(worker->mError).ToLocalChecked(),
      Nan::New<String>(worker->mReturnValue).ToLocalChecked()
	};

  v8::Local<v8::Array> results = Nan::New<v8::Array>();
  Nan::Set(results, 0, argv[0]);
  Nan::Set(results, 1, argv[1]);
  info.GetReturnValue().Set(results);
}

void CalendarIsBusinessDayWorker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes
  std::vector<QuantLib::Date> DateLib = ObjectHandler::vector::convert2<QuantLib::Date>(
      mDate, "Date");

       // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::Calendar calendarEnum =
      ObjectHandler::Create<QuantLib::Calendar>()(mCalendar);

  // loop on the input parameter and populate the return vector

  QuantLibAddin::qlCalendarIsBusinessDayBind bindObject =
    boost::bind((QuantLibAddin::qlCalendarIsBusinessDaySignature)
              &QuantLib::Calendar::isBusinessDay,
              calendarEnum
              ,_1
            );
  ObjectHandler::loop
          <QuantLibAddin::qlCalendarIsBusinessDayBind,
                          QuantLib::Date,
                          bool>
          (bindObject, DateLib,
            mReturnValue);
   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::CalendarIsBusinessDay) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("Calendar is required.");
  }
  if (info.Length() == 1 || !info[1]->IsArray()) {
      return Nan::ThrowError("Date is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strCalendar(info[0]->ToString());
  string CalendarCpp(strdup(*strCalendar));

  // convert js argument to c++ type
  std::vector<ObjectHandler::property_t>DateCpp;

  Local<Array> DateArray = info[1].As<Array>();
  for (unsigned int i = 0; i < DateArray->Length(); i++){
    ObjectHandler::property_t tmp =
        ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(Nan::Get(DateArray, i).ToLocalChecked()).FromJust()));
    DateCpp.push_back(tmp);
  }

 
  // launch worker
  CalendarIsBusinessDayWorker* worker = new CalendarIsBusinessDayWorker(
    CalendarCpp
,     DateCpp
   );

  worker->Execute();

    Local<Array> tmpArray = Nan::New<Array>(worker->mReturnValue.size());
    for (unsigned int i = 0; i < worker->mReturnValue.size(); i++) {
      Nan::Set(tmpArray,i,Nan::New<Boolean>(worker->mReturnValue[i]));
    }

  Local<v8::Value> argv[2] = {
		  Nan::New<String>(worker->mError).ToLocalChecked(),
      tmpArray
	};

  v8::Local<v8::Array> results = Nan::New<v8::Array>();
  Nan::Set(results, 0, argv[0]);
  Nan::Set(results, 1, argv[1]);
  info.GetReturnValue().Set(results);
}

void CalendarIsHolidayWorker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes
  std::vector<QuantLib::Date> DateLib = ObjectHandler::vector::convert2<QuantLib::Date>(
      mDate, "Date");

       // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::Calendar calendarEnum =
      ObjectHandler::Create<QuantLib::Calendar>()(mCalendar);

  // loop on the input parameter and populate the return vector

  QuantLibAddin::qlCalendarIsHolidayBind bindObject =
    boost::bind((QuantLibAddin::qlCalendarIsHolidaySignature)
              &QuantLib::Calendar::isHoliday,
              calendarEnum
              ,_1
            );
  ObjectHandler::loop
          <QuantLibAddin::qlCalendarIsHolidayBind,
                          QuantLib::Date,
                          bool>
          (bindObject, DateLib,
            mReturnValue);
   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::CalendarIsHoliday) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("Calendar is required.");
  }
  if (info.Length() == 1 || !info[1]->IsArray()) {
      return Nan::ThrowError("Date is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strCalendar(info[0]->ToString());
  string CalendarCpp(strdup(*strCalendar));

  // convert js argument to c++ type
  std::vector<ObjectHandler::property_t>DateCpp;

  Local<Array> DateArray = info[1].As<Array>();
  for (unsigned int i = 0; i < DateArray->Length(); i++){
    ObjectHandler::property_t tmp =
        ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(Nan::Get(DateArray, i).ToLocalChecked()).FromJust()));
    DateCpp.push_back(tmp);
  }

 
  // launch worker
  CalendarIsHolidayWorker* worker = new CalendarIsHolidayWorker(
    CalendarCpp
,     DateCpp
   );

  worker->Execute();

    Local<Array> tmpArray = Nan::New<Array>(worker->mReturnValue.size());
    for (unsigned int i = 0; i < worker->mReturnValue.size(); i++) {
      Nan::Set(tmpArray,i,Nan::New<Boolean>(worker->mReturnValue[i]));
    }

  Local<v8::Value> argv[2] = {
		  Nan::New<String>(worker->mError).ToLocalChecked(),
      tmpArray
	};

  v8::Local<v8::Array> results = Nan::New<v8::Array>();
  Nan::Set(results, 0, argv[0]);
  Nan::Set(results, 1, argv[1]);
  info.GetReturnValue().Set(results);
}

void CalendarIsEndOfMonthWorker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes
  std::vector<QuantLib::Date> DateLib = ObjectHandler::vector::convert2<QuantLib::Date>(
      mDate, "Date");

       // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::Calendar calendarEnum =
      ObjectHandler::Create<QuantLib::Calendar>()(mCalendar);

  // loop on the input parameter and populate the return vector

  QuantLibAddin::qlCalendarIsEndOfMonthBind bindObject =
    boost::bind((QuantLibAddin::qlCalendarIsEndOfMonthSignature)
              &QuantLib::Calendar::isEndOfMonth,
              calendarEnum
              ,_1
            );
  ObjectHandler::loop
          <QuantLibAddin::qlCalendarIsEndOfMonthBind,
                          QuantLib::Date,
                          bool>
          (bindObject, DateLib,
            mReturnValue);
   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::CalendarIsEndOfMonth) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("Calendar is required.");
  }
  if (info.Length() == 1 || !info[1]->IsArray()) {
      return Nan::ThrowError("Date is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strCalendar(info[0]->ToString());
  string CalendarCpp(strdup(*strCalendar));

  // convert js argument to c++ type
  std::vector<ObjectHandler::property_t>DateCpp;

  Local<Array> DateArray = info[1].As<Array>();
  for (unsigned int i = 0; i < DateArray->Length(); i++){
    ObjectHandler::property_t tmp =
        ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(Nan::Get(DateArray, i).ToLocalChecked()).FromJust()));
    DateCpp.push_back(tmp);
  }

 
  // launch worker
  CalendarIsEndOfMonthWorker* worker = new CalendarIsEndOfMonthWorker(
    CalendarCpp
,     DateCpp
   );

  worker->Execute();

    Local<Array> tmpArray = Nan::New<Array>(worker->mReturnValue.size());
    for (unsigned int i = 0; i < worker->mReturnValue.size(); i++) {
      Nan::Set(tmpArray,i,Nan::New<Boolean>(worker->mReturnValue[i]));
    }

  Local<v8::Value> argv[2] = {
		  Nan::New<String>(worker->mError).ToLocalChecked(),
      tmpArray
	};

  v8::Local<v8::Array> results = Nan::New<v8::Array>();
  Nan::Set(results, 0, argv[0]);
  Nan::Set(results, 1, argv[1]);
  info.GetReturnValue().Set(results);
}

void CalendarEndOfMonthWorker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes
  std::vector<QuantLib::Date> DateLib = ObjectHandler::vector::convert2<QuantLib::Date>(
      mDate, "Date");

       // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::Calendar calendarEnum =
      ObjectHandler::Create<QuantLib::Calendar>()(mCalendar);

  // loop on the input parameter and populate the return vector
  std::vector<QuantLib::Date> returnValue;

  QuantLibAddin::qlCalendarEndOfMonthBind bindObject =
    boost::bind((QuantLibAddin::qlCalendarEndOfMonthSignature)
              &QuantLib::Calendar::endOfMonth,
              calendarEnum
              ,_1
            );
  ObjectHandler::loop
          <QuantLibAddin::qlCalendarEndOfMonthBind,
                          QuantLib::Date,
                          QuantLib::Date>
          (bindObject, DateLib,
            returnValue);

  mReturnValue = QuantLibAddin::libraryToVector(returnValue);

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::CalendarEndOfMonth) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("Calendar is required.");
  }
  if (info.Length() == 1 || !info[1]->IsArray()) {
      return Nan::ThrowError("Date is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strCalendar(info[0]->ToString());
  string CalendarCpp(strdup(*strCalendar));

  // convert js argument to c++ type
  std::vector<ObjectHandler::property_t>DateCpp;

  Local<Array> DateArray = info[1].As<Array>();
  for (unsigned int i = 0; i < DateArray->Length(); i++){
    ObjectHandler::property_t tmp =
        ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(Nan::Get(DateArray, i).ToLocalChecked()).FromJust()));
    DateCpp.push_back(tmp);
  }

 
  // launch worker
  CalendarEndOfMonthWorker* worker = new CalendarEndOfMonthWorker(
    CalendarCpp
,     DateCpp
   );

  worker->Execute();

    Local<Array> tmpArray = Nan::New<Array>(worker->mReturnValue.size());
    for (unsigned int i = 0; i < worker->mReturnValue.size(); i++) {
      Nan::Set(tmpArray,i,Nan::New<Number>(worker->mReturnValue[i]));
    }

  Local<v8::Value> argv[2] = {
		  Nan::New<String>(worker->mError).ToLocalChecked(),
      tmpArray
	};

  v8::Local<v8::Array> results = Nan::New<v8::Array>();
  Nan::Set(results, 0, argv[0]);
  Nan::Set(results, 1, argv[1]);
  info.GetReturnValue().Set(results);
}

void CalendarAddHolidayWorker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes
  QuantLib::Date DateLib = ObjectHandler::convert2<QuantLib::Date>(
      mDate, "Date");

       // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::Calendar calendarEnum =
      ObjectHandler::Create<QuantLib::Calendar>()(mCalendar);

  // invoke the member function
  calendarEnum.addHoliday(
            DateLib
       );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::CalendarAddHoliday) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("Calendar is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strCalendar(info[0]->ToString());
  string CalendarCpp(strdup(*strCalendar));

  // convert js argument to c++ type
  ObjectHandler::property_t DateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[1]).FromJust()));

 
  // launch worker
  CalendarAddHolidayWorker* worker = new CalendarAddHolidayWorker(
    CalendarCpp
,     DateCpp
   );

  worker->Execute();


  Local<v8::Value> argv[2] = {
		  Nan::New<String>(worker->mError).ToLocalChecked(),
      Nan::Null()
	};

  v8::Local<v8::Array> results = Nan::New<v8::Array>();
  Nan::Set(results, 0, argv[0]);
  Nan::Set(results, 1, argv[1]);
  info.GetReturnValue().Set(results);
}

void CalendarRemoveHolidayWorker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes
  QuantLib::Date DateLib = ObjectHandler::convert2<QuantLib::Date>(
      mDate, "Date");

       // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::Calendar calendarEnum =
      ObjectHandler::Create<QuantLib::Calendar>()(mCalendar);

  // invoke the member function
  calendarEnum.removeHoliday(
            DateLib
       );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::CalendarRemoveHoliday) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("Calendar is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strCalendar(info[0]->ToString());
  string CalendarCpp(strdup(*strCalendar));

  // convert js argument to c++ type
  ObjectHandler::property_t DateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[1]).FromJust()));

 
  // launch worker
  CalendarRemoveHolidayWorker* worker = new CalendarRemoveHolidayWorker(
    CalendarCpp
,     DateCpp
   );

  worker->Execute();


  Local<v8::Value> argv[2] = {
		  Nan::New<String>(worker->mError).ToLocalChecked(),
      Nan::Null()
	};

  v8::Local<v8::Array> results = Nan::New<v8::Array>();
  Nan::Set(results, 0, argv[0]);
  Nan::Set(results, 1, argv[1]);
  info.GetReturnValue().Set(results);
}

void CalendarAdjustWorker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes
  std::vector<QuantLib::Date> DateLib = ObjectHandler::vector::convert2<QuantLib::Date>(
      mDate, "Date");


  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::BusinessDayConvention BusinessDayConventionEnum =
      ObjectHandler::Create<QuantLib::BusinessDayConvention>()(mBusinessDayConvention);

       // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::Calendar calendarEnum =
      ObjectHandler::Create<QuantLib::Calendar>()(mCalendar);

  // loop on the input parameter and populate the return vector
  std::vector<QuantLib::Date> returnValue;

  QuantLibAddin::qlCalendarAdjustBind bindObject =
    boost::bind((QuantLibAddin::qlCalendarAdjustSignature)
              &QuantLib::Calendar::adjust,
              calendarEnum
              ,_1
              ,BusinessDayConventionEnum
            );
  ObjectHandler::loop
          <QuantLibAddin::qlCalendarAdjustBind,
                          QuantLib::Date,
                          QuantLib::Date>
          (bindObject, DateLib,
            returnValue);

  mReturnValue = QuantLibAddin::libraryToVector(returnValue);

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::CalendarAdjust) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("Calendar is required.");
  }
  if (info.Length() == 1 || !info[1]->IsArray()) {
      return Nan::ThrowError("Date is required.");
  }
  if (info.Length() == 2 || !info[2]->IsString()) {
      return Nan::ThrowError("BusinessDayConvention is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strCalendar(info[0]->ToString());
  string CalendarCpp(strdup(*strCalendar));

  // convert js argument to c++ type
  std::vector<ObjectHandler::property_t>DateCpp;

  Local<Array> DateArray = info[1].As<Array>();
  for (unsigned int i = 0; i < DateArray->Length(); i++){
    ObjectHandler::property_t tmp =
        ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(Nan::Get(DateArray, i).ToLocalChecked()).FromJust()));
    DateCpp.push_back(tmp);
  }

  // convert js argument to c++ type
  String::Utf8Value strBusinessDayConvention(info[2]->ToString());
  string BusinessDayConventionCpp(strdup(*strBusinessDayConvention));

 
  // launch worker
  CalendarAdjustWorker* worker = new CalendarAdjustWorker(
    CalendarCpp
,     DateCpp
,     BusinessDayConventionCpp
   );

  worker->Execute();

    Local<Array> tmpArray = Nan::New<Array>(worker->mReturnValue.size());
    for (unsigned int i = 0; i < worker->mReturnValue.size(); i++) {
      Nan::Set(tmpArray,i,Nan::New<Number>(worker->mReturnValue[i]));
    }

  Local<v8::Value> argv[2] = {
		  Nan::New<String>(worker->mError).ToLocalChecked(),
      tmpArray
	};

  v8::Local<v8::Array> results = Nan::New<v8::Array>();
  Nan::Set(results, 0, argv[0]);
  Nan::Set(results, 1, argv[1]);
  info.GetReturnValue().Set(results);
}

void CalendarAdvanceWorker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes
  QuantLib::Date StartDateLib = ObjectHandler::convert2<QuantLib::Date>(
      mStartDate, "StartDate");


  // convert input datatypes to QuantLib datatypes
  std::vector<QuantLib::Period> PeriodLib;


  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::BusinessDayConvention BusinessDayConventionEnum =
      ObjectHandler::Create<QuantLib::BusinessDayConvention>()(mBusinessDayConvention);

       // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::Calendar calendarEnum =
      ObjectHandler::Create<QuantLib::Calendar>()(mCalendar);

  // loop on the input parameter and populate the return vector
  std::vector<QuantLib::Date> returnValue;

  QuantLibAddin::qlCalendarAdvanceBind bindObject =
    boost::bind((QuantLibAddin::qlCalendarAdvanceSignature)
              &QuantLib::Calendar::advance,
              calendarEnum
              ,StartDateLib
              ,_1
              ,BusinessDayConventionEnum
              ,mEndOfMonth
            );
  ObjectHandler::loop
          <QuantLibAddin::qlCalendarAdvanceBind,
                          QuantLib::Period,
                          QuantLib::Date>
          (bindObject, PeriodLib,
            returnValue);

  mReturnValue = QuantLibAddin::libraryToVector(returnValue);

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::CalendarAdvance) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("Calendar is required.");
  }
  if (info.Length() == 2 || !info[2]->IsArray()) {
      return Nan::ThrowError("Period is required.");
  }
  if (info.Length() == 3 || !info[3]->IsString()) {
      return Nan::ThrowError("BusinessDayConvention is required.");
  }
  if (info.Length() == 4 || !info[4]->IsBoolean()) {
      return Nan::ThrowError("EndOfMonth is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strCalendar(info[0]->ToString());
  string CalendarCpp(strdup(*strCalendar));

  // convert js argument to c++ type
  ObjectHandler::property_t StartDateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[1]).FromJust()));

  // convert js argument to c++ type
  std::vector<ObjectHandler::property_t>PeriodCpp;

  Local<Array> PeriodArray = info[2].As<Array>();
  for (unsigned int i = 0; i < PeriodArray->Length(); i++){
    ObjectHandler::property_t tmp =
        ObjectHandler::property_t(static_cast<double>(Nan::To<double>(Nan::Get(PeriodArray, i).ToLocalChecked()).FromJust()));
    PeriodCpp.push_back(tmp);
  }

  // convert js argument to c++ type
  String::Utf8Value strBusinessDayConvention(info[3]->ToString());
  string BusinessDayConventionCpp(strdup(*strBusinessDayConvention));

  // convert js argument to c++ type
  bool EndOfMonthCpp = Nan::To<bool>(info[4]).FromJust();

 
  // launch worker
  CalendarAdvanceWorker* worker = new CalendarAdvanceWorker(
    CalendarCpp
,     StartDateCpp
,     PeriodCpp
,     BusinessDayConventionCpp
,     EndOfMonthCpp
   );

  worker->Execute();

    Local<Array> tmpArray = Nan::New<Array>(worker->mReturnValue.size());
    for (unsigned int i = 0; i < worker->mReturnValue.size(); i++) {
      Nan::Set(tmpArray,i,Nan::New<Number>(worker->mReturnValue[i]));
    }

  Local<v8::Value> argv[2] = {
		  Nan::New<String>(worker->mError).ToLocalChecked(),
      tmpArray
	};

  v8::Local<v8::Array> results = Nan::New<v8::Array>();
  Nan::Set(results, 0, argv[0]);
  Nan::Set(results, 1, argv[1]);
  info.GetReturnValue().Set(results);
}

void CalendarBusinessDaysBetweenWorker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes
  std::vector<QuantLib::Date> FirstDateLib = ObjectHandler::vector::convert2<QuantLib::Date>(
      mFirstDate, "FirstDate");


  // convert input datatypes to QuantLib datatypes
  QuantLib::Date LastDateLib = ObjectHandler::convert2<QuantLib::Date>(
      mLastDate, "LastDate");

       // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::Calendar calendarEnum =
      ObjectHandler::Create<QuantLib::Calendar>()(mCalendar);

  // loop on the input parameter and populate the return vector

  QuantLibAddin::qlCalendarBusinessDaysBetweenBind bindObject =
    boost::bind((QuantLibAddin::qlCalendarBusinessDaysBetweenSignature)
              &QuantLib::Calendar::businessDaysBetween,
              calendarEnum
              ,_1
              ,LastDateLib
              ,mIncludeFirst
              ,mIncludeLast
            );
  ObjectHandler::loop
          <QuantLibAddin::qlCalendarBusinessDaysBetweenBind,
                          QuantLib::Date,
                          long>
          (bindObject, FirstDateLib,
            mReturnValue);
   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::CalendarBusinessDaysBetween) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("Calendar is required.");
  }
  if (info.Length() == 1 || !info[1]->IsArray()) {
      return Nan::ThrowError("FirstDate is required.");
  }
  if (info.Length() == 3 || !info[3]->IsBoolean()) {
      return Nan::ThrowError("IncludeFirst is required.");
  }
  if (info.Length() == 4 || !info[4]->IsBoolean()) {
      return Nan::ThrowError("IncludeLast is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strCalendar(info[0]->ToString());
  string CalendarCpp(strdup(*strCalendar));

  // convert js argument to c++ type
  std::vector<ObjectHandler::property_t>FirstDateCpp;

  Local<Array> FirstDateArray = info[1].As<Array>();
  for (unsigned int i = 0; i < FirstDateArray->Length(); i++){
    ObjectHandler::property_t tmp =
        ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(Nan::Get(FirstDateArray, i).ToLocalChecked()).FromJust()));
    FirstDateCpp.push_back(tmp);
  }

  // convert js argument to c++ type
  ObjectHandler::property_t LastDateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[2]).FromJust()));

  // convert js argument to c++ type
  bool IncludeFirstCpp = Nan::To<bool>(info[3]).FromJust();

  // convert js argument to c++ type
  bool IncludeLastCpp = Nan::To<bool>(info[4]).FromJust();

 
  // launch worker
  CalendarBusinessDaysBetweenWorker* worker = new CalendarBusinessDaysBetweenWorker(
    CalendarCpp
,     FirstDateCpp
,     LastDateCpp
,     IncludeFirstCpp
,     IncludeLastCpp
   );

  worker->Execute();

    Local<Array> tmpArray = Nan::New<Array>(worker->mReturnValue.size());
    for (unsigned int i = 0; i < worker->mReturnValue.size(); i++) {
      Nan::Set(tmpArray,i,Nan::New<Number>(worker->mReturnValue[i]));
    }

  Local<v8::Value> argv[2] = {
		  Nan::New<String>(worker->mError).ToLocalChecked(),
      tmpArray
	};

  v8::Local<v8::Array> results = Nan::New<v8::Array>();
  Nan::Set(results, 0, argv[0]);
  Nan::Set(results, 1, argv[1]);
  info.GetReturnValue().Set(results);
}
 