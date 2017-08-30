/* 
  Copyright (C) 2016 -2017 Jerry Jin
*/

#include <nan.h>
#include <string.h>

#include "date.hpp"

#include <qlo/qladdindefines.hpp>
#include <qlo/date.hpp>
#include <ql/time/date.hpp>
#include <ql/time/imm.hpp>
#include <ql/time/ecb.hpp>
#include <ql/time/asx.hpp>
#include <qlo/loop/loop_date.hpp>
#include <oh/enumerations/typefactory.hpp>
 #include <oh/objecthandler.hpp>
#include <oh/conversions/getobjectvector.hpp>
#include <qlo/valueobjects/vo_all.hpp>
#include <qlo/conversions/all.hpp>
#include "../loop.hpp"


void PeriodFromFrequencyWorker::Execute(){

  try{

  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::Frequency FrequencyEnum =
      ObjectHandler::Create<QuantLib::Frequency>()(mFrequency);

       // invoke the utility function
  QuantLib::Period returnValue = QuantLibAddin::periodFromFrequency(
      FrequencyEnum
     );

  mReturnValue = QuantLibAddin::libraryToScalar(returnValue);

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::PeriodFromFrequency) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("Frequency is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strFrequency(info[0]->ToString());
  string FrequencyCpp(strdup(*strFrequency));

 
  // launch worker
  PeriodFromFrequencyWorker* worker = new PeriodFromFrequencyWorker(
    FrequencyCpp
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

void FrequencyFromPeriodWorker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes
  std::vector<QuantLib::Period> PeriodLib;

       std::vector<QuantLib::Frequency> returnValue;


  // loop on the input parameter and populate the return vector
  QuantLibAddin::qlFrequencyFromPeriodBind bindObject =
      boost::bind(
          &QuantLibAddin::frequencyFromPeriod
          ,_1
    );
  ObjectHandler::loop
      <QuantLibAddin::qlFrequencyFromPeriodBind, QuantLib::Period, QuantLib::Frequency>
          (bindObject,
            PeriodLib,
          returnValue
          );


  for(unsigned int i = 0; i< returnValue.size(); i++){
    std::ostringstream os;
    os << returnValue[i];
    mReturnValue.push_back(os.str());
  }

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::FrequencyFromPeriod) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsArray()) {
      return Nan::ThrowError("Period is required.");
  }
  // convert js argument to c++ type
  std::vector<ObjectHandler::property_t>PeriodCpp;

  Local<Array> PeriodArray = info[0].As<Array>();
  for (unsigned int i = 0; i < PeriodArray->Length(); i++){
    ObjectHandler::property_t tmp =
        ObjectHandler::property_t(static_cast<double>(Nan::To<double>(Nan::Get(PeriodArray, i).ToLocalChecked()).FromJust()));
    PeriodCpp.push_back(tmp);
  }

 
  // launch worker
  FrequencyFromPeriodWorker* worker = new FrequencyFromPeriodWorker(
    PeriodCpp
   );

  worker->Execute();

    Local<Array> tmpArray = Nan::New<Array>(worker->mReturnValue.size());
    for (unsigned int i = 0; i < worker->mReturnValue.size(); i++) {
      Nan::Set(tmpArray,i,Nan::New<String>(worker->mReturnValue[i]).ToLocalChecked());
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

void PeriodLessThanWorker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes
  QuantLib::Period Period1Lib;
  QuantLibAddin::cppToLibrary(mPeriod1, Period1Lib);


  // convert input datatypes to QuantLib datatypes
  QuantLib::Period Period2Lib;
  QuantLibAddin::cppToLibrary(mPeriod2, Period2Lib);

       // invoke the utility function
  mReturnValue = QuantLib::operator<(
      Period1Lib
      ,
       Period2Lib
     );
   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::PeriodLessThan) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("Period1 is required.");
  }
  if (info.Length() == 1 || !info[1]->IsString()) {
      return Nan::ThrowError("Period2 is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strPeriod1(info[0]->ToString());
  string Period1Cpp(strdup(*strPeriod1));

  // convert js argument to c++ type
  String::Utf8Value strPeriod2(info[1]->ToString());
  string Period2Cpp(strdup(*strPeriod2));

 
  // launch worker
  PeriodLessThanWorker* worker = new PeriodLessThanWorker(
    Period1Cpp
,     Period2Cpp
   );

  worker->Execute();


  Local<v8::Value> argv[2] = {
		  Nan::New<String>(worker->mError).ToLocalChecked(),
      Nan::New<Boolean>(worker->mReturnValue)
	};

  v8::Local<v8::Array> results = Nan::New<v8::Array>();
  Nan::Set(results, 0, argv[0]);
  Nan::Set(results, 1, argv[1]);
  info.GetReturnValue().Set(results);
}

void PeriodEquivalentWorker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes
  QuantLib::Period PeriodLib;
  QuantLibAddin::cppToLibrary(mPeriod, PeriodLib);

       // invoke the utility function
  QuantLib::Period returnValue = QuantLibAddin::periodEquivalent(
      PeriodLib
     );

  mReturnValue = QuantLibAddin::libraryToScalar(returnValue);

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::PeriodEquivalent) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("Period is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strPeriod(info[0]->ToString());
  string PeriodCpp(strdup(*strPeriod));

 
  // launch worker
  PeriodEquivalentWorker* worker = new PeriodEquivalentWorker(
    PeriodCpp
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

void DateMinDateWorker::Execute(){

  try{
       // invoke the utility function
  QuantLib::Date returnValue = QuantLib::Date::minDate(
    );

  mReturnValue = QuantLibAddin::libraryToScalar(returnValue);

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::DateMinDate) {

  // validate js arguments
 
  // launch worker
  DateMinDateWorker* worker = new DateMinDateWorker(
  );

  worker->Execute();


  Local<v8::Value> argv[2] = {
		  Nan::New<String>(worker->mError).ToLocalChecked(),
      Nan::New<Number>(worker->mReturnValue)
	};

  v8::Local<v8::Array> results = Nan::New<v8::Array>();
  Nan::Set(results, 0, argv[0]);
  Nan::Set(results, 1, argv[1]);
  info.GetReturnValue().Set(results);
}

void DateMaxDateWorker::Execute(){

  try{
       // invoke the utility function
  QuantLib::Date returnValue = QuantLib::Date::maxDate(
    );

  mReturnValue = QuantLibAddin::libraryToScalar(returnValue);

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::DateMaxDate) {

  // validate js arguments
 
  // launch worker
  DateMaxDateWorker* worker = new DateMaxDateWorker(
  );

  worker->Execute();


  Local<v8::Value> argv[2] = {
		  Nan::New<String>(worker->mError).ToLocalChecked(),
      Nan::New<Number>(worker->mReturnValue)
	};

  v8::Local<v8::Array> results = Nan::New<v8::Array>();
  Nan::Set(results, 0, argv[0]);
  Nan::Set(results, 1, argv[1]);
  info.GetReturnValue().Set(results);
}

void DateIsLeapWorker::Execute(){

  try{
     
  // loop on the input parameter and populate the return vector
  QuantLibAddin::qlDateIsLeapBind bindObject =
      boost::bind(
          &QuantLib::Date::isLeap
          ,_1
    );
  ObjectHandler::loop
      <QuantLibAddin::qlDateIsLeapBind, long, bool>
          (bindObject,
           mYear,
          mReturnValue
          );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::DateIsLeap) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsArray()) {
      return Nan::ThrowError("Year is required.");
  }
  // convert js argument to c++ type
  std::vector<long>YearCpp;

  Local<Array> YearArray = info[0].As<Array>();
  for (unsigned int i = 0; i < YearArray->Length(); i++){
    YearCpp.push_back(Nan::To<int32_t>(Nan::Get(YearArray, i).ToLocalChecked()).FromJust());
  }

 
  // launch worker
  DateIsLeapWorker* worker = new DateIsLeapWorker(
    YearCpp
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

void DateEndOfMonthWorker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes
  std::vector<QuantLib::Date> DateLib = ObjectHandler::vector::convert2<QuantLib::Date>(
      mDate, "Date");

       std::vector<QuantLib::Date> returnValue;


  // loop on the input parameter and populate the return vector
  QuantLibAddin::qlDateEndOfMonthBind bindObject =
      boost::bind(
          &QuantLib::Date::endOfMonth
          ,_1
    );
  ObjectHandler::loop
      <QuantLibAddin::qlDateEndOfMonthBind, QuantLib::Date, QuantLib::Date>
          (bindObject,
            DateLib,
          returnValue
          );


  mReturnValue = QuantLibAddin::libraryToVector(returnValue);

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::DateEndOfMonth) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsArray()) {
      return Nan::ThrowError("Date is required.");
  }
  // convert js argument to c++ type
  std::vector<ObjectHandler::property_t>DateCpp;

  Local<Array> DateArray = info[0].As<Array>();
  for (unsigned int i = 0; i < DateArray->Length(); i++){
    ObjectHandler::property_t tmp =
        ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(Nan::Get(DateArray, i).ToLocalChecked()).FromJust()));
    DateCpp.push_back(tmp);
  }

 
  // launch worker
  DateEndOfMonthWorker* worker = new DateEndOfMonthWorker(
    DateCpp
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

void DateIsEndOfMonthWorker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes
  std::vector<QuantLib::Date> DateLib = ObjectHandler::vector::convert2<QuantLib::Date>(
      mDate, "Date");

     
  // loop on the input parameter and populate the return vector
  QuantLibAddin::qlDateIsEndOfMonthBind bindObject =
      boost::bind(
          &QuantLib::Date::isEndOfMonth
          ,_1
    );
  ObjectHandler::loop
      <QuantLibAddin::qlDateIsEndOfMonthBind, QuantLib::Date, bool>
          (bindObject,
            DateLib,
          mReturnValue
          );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::DateIsEndOfMonth) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsArray()) {
      return Nan::ThrowError("Date is required.");
  }
  // convert js argument to c++ type
  std::vector<ObjectHandler::property_t>DateCpp;

  Local<Array> DateArray = info[0].As<Array>();
  for (unsigned int i = 0; i < DateArray->Length(); i++){
    ObjectHandler::property_t tmp =
        ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(Nan::Get(DateArray, i).ToLocalChecked()).FromJust()));
    DateCpp.push_back(tmp);
  }

 
  // launch worker
  DateIsEndOfMonthWorker* worker = new DateIsEndOfMonthWorker(
    DateCpp
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

void DateNextWeekdayWorker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes
  std::vector<QuantLib::Date> DateLib = ObjectHandler::vector::convert2<QuantLib::Date>(
      mDate, "Date");


  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::Weekday WeekdayEnum =
      ObjectHandler::Create<QuantLib::Weekday>()(mWeekday);

       std::vector<QuantLib::Date> returnValue;


  // loop on the input parameter and populate the return vector
  QuantLibAddin::qlDateNextWeekdayBind bindObject =
      boost::bind(
          &QuantLib::Date::nextWeekday
          ,_1
          ,WeekdayEnum
    );
  ObjectHandler::loop
      <QuantLibAddin::qlDateNextWeekdayBind, QuantLib::Date, QuantLib::Date>
          (bindObject,
            DateLib,
          returnValue
          );


  mReturnValue = QuantLibAddin::libraryToVector(returnValue);

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::DateNextWeekday) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsArray()) {
      return Nan::ThrowError("Date is required.");
  }
  if (info.Length() == 1 || !info[1]->IsString()) {
      return Nan::ThrowError("Weekday is required.");
  }
  // convert js argument to c++ type
  std::vector<ObjectHandler::property_t>DateCpp;

  Local<Array> DateArray = info[0].As<Array>();
  for (unsigned int i = 0; i < DateArray->Length(); i++){
    ObjectHandler::property_t tmp =
        ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(Nan::Get(DateArray, i).ToLocalChecked()).FromJust()));
    DateCpp.push_back(tmp);
  }

  // convert js argument to c++ type
  String::Utf8Value strWeekday(info[1]->ToString());
  string WeekdayCpp(strdup(*strWeekday));

 
  // launch worker
  DateNextWeekdayWorker* worker = new DateNextWeekdayWorker(
    DateCpp
,     WeekdayCpp
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

void DateNthWeekdayWorker::Execute(){

  try{

  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::Weekday WeekdayEnum =
      ObjectHandler::Create<QuantLib::Weekday>()(mWeekday);


  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::Month MonthEnum =
      ObjectHandler::Create<QuantLib::Month>()(mMonth);

       // invoke the utility function
  QuantLib::Date returnValue = QuantLib::Date::nthWeekday(
      mNth
      ,
       WeekdayEnum
      ,
       MonthEnum
      ,
       mYear
     );

  mReturnValue = QuantLibAddin::libraryToScalar(returnValue);

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::DateNthWeekday) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsNumber()) {
      return Nan::ThrowError("Nth is required.");
  }
  if (info.Length() == 1 || !info[1]->IsString()) {
      return Nan::ThrowError("Weekday is required.");
  }
  if (info.Length() == 2 || !info[2]->IsString()) {
      return Nan::ThrowError("Month is required.");
  }
  if (info.Length() == 3 || !info[3]->IsNumber()) {
      return Nan::ThrowError("Year is required.");
  }
  // convert js argument to c++ type
  long NthCpp = Nan::To<int32_t>(info[0]).FromJust();

  // convert js argument to c++ type
  String::Utf8Value strWeekday(info[1]->ToString());
  string WeekdayCpp(strdup(*strWeekday));

  // convert js argument to c++ type
  String::Utf8Value strMonth(info[2]->ToString());
  string MonthCpp(strdup(*strMonth));

  // convert js argument to c++ type
  long YearCpp = Nan::To<int32_t>(info[3]).FromJust();

 
  // launch worker
  DateNthWeekdayWorker* worker = new DateNthWeekdayWorker(
    NthCpp
,     WeekdayCpp
,     MonthCpp
,     YearCpp
   );

  worker->Execute();


  Local<v8::Value> argv[2] = {
		  Nan::New<String>(worker->mError).ToLocalChecked(),
      Nan::New<Number>(worker->mReturnValue)
	};

  v8::Local<v8::Array> results = Nan::New<v8::Array>();
  Nan::Set(results, 0, argv[0]);
  Nan::Set(results, 1, argv[1]);
  info.GetReturnValue().Set(results);
}

void IMMIsIMMdateWorker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes
  std::vector<QuantLib::Date> DateLib = ObjectHandler::vector::convert2<QuantLib::Date>(
      mDate, "Date");

     
  // loop on the input parameter and populate the return vector
  QuantLibAddin::qlIMMIsIMMdateBind bindObject =
      boost::bind(
          &QuantLib::IMM::isIMMdate
          ,_1
          ,mMainCycle
    );
  ObjectHandler::loop
      <QuantLibAddin::qlIMMIsIMMdateBind, QuantLib::Date, bool>
          (bindObject,
            DateLib,
          mReturnValue
          );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::IMMIsIMMdate) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsArray()) {
      return Nan::ThrowError("Date is required.");
  }
  if (info.Length() == 1 || !info[1]->IsBoolean()) {
      return Nan::ThrowError("MainCycle is required.");
  }
  // convert js argument to c++ type
  std::vector<ObjectHandler::property_t>DateCpp;

  Local<Array> DateArray = info[0].As<Array>();
  for (unsigned int i = 0; i < DateArray->Length(); i++){
    ObjectHandler::property_t tmp =
        ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(Nan::Get(DateArray, i).ToLocalChecked()).FromJust()));
    DateCpp.push_back(tmp);
  }

  // convert js argument to c++ type
  bool MainCycleCpp = Nan::To<bool>(info[1]).FromJust();

 
  // launch worker
  IMMIsIMMdateWorker* worker = new IMMIsIMMdateWorker(
    DateCpp
,     MainCycleCpp
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

void IMMIsIMMcodeWorker::Execute(){

  try{
     
  // loop on the input parameter and populate the return vector
  QuantLibAddin::qlIMMIsIMMcodeBind bindObject =
      boost::bind(
          &QuantLib::IMM::isIMMcode
          ,_1
          ,mMainCycle
    );
  ObjectHandler::loop
      <QuantLibAddin::qlIMMIsIMMcodeBind, string, bool>
          (bindObject,
           mCode,
          mReturnValue
          );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::IMMIsIMMcode) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsArray()) {
      return Nan::ThrowError("Code is required.");
  }
  if (info.Length() == 1 || !info[1]->IsBoolean()) {
      return Nan::ThrowError("MainCycle is required.");
  }
  // convert js argument to c++ type
  std::vector<string>CodeCpp;

  Local<Array> CodeArray = info[0].As<Array>();
  for (unsigned int i = 0; i < CodeArray->Length(); i++){
    String::Utf8Value strCode(Nan::Get(CodeArray, i).ToLocalChecked()->ToString());
    CodeCpp.push_back(strdup(*strCode));
  }

  // convert js argument to c++ type
  bool MainCycleCpp = Nan::To<bool>(info[1]).FromJust();

 
  // launch worker
  IMMIsIMMcodeWorker* worker = new IMMIsIMMcodeWorker(
    CodeCpp
,     MainCycleCpp
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

void IMMcodeWorker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes
  std::vector<QuantLib::Date> IMMdateLib = ObjectHandler::vector::convert2<QuantLib::Date>(
      mIMMdate, "IMMdate");

     
  // loop on the input parameter and populate the return vector
  QuantLibAddin::qlIMMcodeBind bindObject =
      boost::bind(
          &QuantLib::IMM::code
          ,_1
    );
  ObjectHandler::loop
      <QuantLibAddin::qlIMMcodeBind, QuantLib::Date, string>
          (bindObject,
            IMMdateLib,
          mReturnValue
          );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::IMMcode) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsArray()) {
      return Nan::ThrowError("IMMdate is required.");
  }
  // convert js argument to c++ type
  std::vector<ObjectHandler::property_t>IMMdateCpp;

  Local<Array> IMMdateArray = info[0].As<Array>();
  for (unsigned int i = 0; i < IMMdateArray->Length(); i++){
    ObjectHandler::property_t tmp =
        ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(Nan::Get(IMMdateArray, i).ToLocalChecked()).FromJust()));
    IMMdateCpp.push_back(tmp);
  }

 
  // launch worker
  IMMcodeWorker* worker = new IMMcodeWorker(
    IMMdateCpp
   );

  worker->Execute();

    Local<Array> tmpArray = Nan::New<Array>(worker->mReturnValue.size());
    for (unsigned int i = 0; i < worker->mReturnValue.size(); i++) {
      Nan::Set(tmpArray,i,Nan::New<String>(worker->mReturnValue[i]).ToLocalChecked());
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

void IMMNextCodeWorker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes
  QuantLib::Date RefDateLib = ObjectHandler::convert2<QuantLib::Date>(
      mRefDate, "RefDate");

       // invoke the utility function
  mReturnValue = QuantLib::IMM::nextCode(
      RefDateLib
      ,
       mMainCycle
     );
   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::IMMNextCode) {

  // validate js arguments
  if (info.Length() == 1 || !info[1]->IsBoolean()) {
      return Nan::ThrowError("MainCycle is required.");
  }
  // convert js argument to c++ type
  ObjectHandler::property_t RefDateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[0]).FromJust()));

  // convert js argument to c++ type
  bool MainCycleCpp = Nan::To<bool>(info[1]).FromJust();

 
  // launch worker
  IMMNextCodeWorker* worker = new IMMNextCodeWorker(
    RefDateCpp
,     MainCycleCpp
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

void IMMNextCodesWorker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes
  QuantLib::Date RefDateLib = ObjectHandler::convert2<QuantLib::Date>(
      mRefDate, "RefDate");

       // invoke the utility function
  mReturnValue = QuantLibAddin::qlIMMNextCodes(
      RefDateLib
      ,
       mMainCycle
   );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::IMMNextCodes) {

  // validate js arguments
  if (info.Length() == 1 || !info[1]->IsArray()) {
      return Nan::ThrowError("MainCycle is required.");
  }
  // convert js argument to c++ type
  ObjectHandler::property_t RefDateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[0]).FromJust()));

  // convert js argument to c++ type
  std::vector<bool>MainCycleCpp;

  Local<Array> MainCycleArray = info[1].As<Array>();
  for (unsigned int i = 0; i < MainCycleArray->Length(); i++){
    MainCycleCpp.push_back(Nan::To<bool>(Nan::Get(MainCycleArray, i).ToLocalChecked()).FromJust());
  }

 
  // launch worker
  IMMNextCodesWorker* worker = new IMMNextCodesWorker(
    RefDateCpp
,     MainCycleCpp
   );

  worker->Execute();

    Local<Array> tmpArray = Nan::New<Array>(worker->mReturnValue.size());
    for (unsigned int i = 0; i < worker->mReturnValue.size(); i++) {
      Nan::Set(tmpArray,i,Nan::New<String>(worker->mReturnValue[i]).ToLocalChecked());
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

void IMMdateWorker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes
  QuantLib::Date RefDateLib = ObjectHandler::convert2<QuantLib::Date>(
      mRefDate, "RefDate");

       std::vector<QuantLib::Date> returnValue;


  // loop on the input parameter and populate the return vector
  QuantLibAddin::qlIMMdateBind bindObject =
      boost::bind(
          &QuantLib::IMM::date
          ,_1
          ,RefDateLib
    );
  ObjectHandler::loop
      <QuantLibAddin::qlIMMdateBind, string, QuantLib::Date>
          (bindObject,
           mIMMcode,
          returnValue
          );


  mReturnValue = QuantLibAddin::libraryToVector(returnValue);

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::IMMdate) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsArray()) {
      return Nan::ThrowError("IMMcode is required.");
  }
  // convert js argument to c++ type
  std::vector<string>IMMcodeCpp;

  Local<Array> IMMcodeArray = info[0].As<Array>();
  for (unsigned int i = 0; i < IMMcodeArray->Length(); i++){
    String::Utf8Value strIMMcode(Nan::Get(IMMcodeArray, i).ToLocalChecked()->ToString());
    IMMcodeCpp.push_back(strdup(*strIMMcode));
  }

  // convert js argument to c++ type
  ObjectHandler::property_t RefDateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[1]).FromJust()));

 
  // launch worker
  IMMdateWorker* worker = new IMMdateWorker(
    IMMcodeCpp
,     RefDateCpp
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

void IMMNextDateWorker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes
  QuantLib::Date RefDateLib = ObjectHandler::convert2<QuantLib::Date>(
      mRefDate, "RefDate");

       // invoke the utility function
  QuantLib::Date returnValue = QuantLib::IMM::nextDate(
      RefDateLib
      ,
       mMainCycle
     );

  mReturnValue = QuantLibAddin::libraryToScalar(returnValue);

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::IMMNextDate) {

  // validate js arguments
  if (info.Length() == 1 || !info[1]->IsBoolean()) {
      return Nan::ThrowError("MainCycle is required.");
  }
  // convert js argument to c++ type
  ObjectHandler::property_t RefDateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[0]).FromJust()));

  // convert js argument to c++ type
  bool MainCycleCpp = Nan::To<bool>(info[1]).FromJust();

 
  // launch worker
  IMMNextDateWorker* worker = new IMMNextDateWorker(
    RefDateCpp
,     MainCycleCpp
   );

  worker->Execute();


  Local<v8::Value> argv[2] = {
		  Nan::New<String>(worker->mError).ToLocalChecked(),
      Nan::New<Number>(worker->mReturnValue)
	};

  v8::Local<v8::Array> results = Nan::New<v8::Array>();
  Nan::Set(results, 0, argv[0]);
  Nan::Set(results, 1, argv[1]);
  info.GetReturnValue().Set(results);
}

void IMMNextDatesWorker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes
  QuantLib::Date RefDateLib = ObjectHandler::convert2<QuantLib::Date>(
      mRefDate, "RefDate");

       // invoke the utility function
  std::vector<QuantLib::Date> returnValue = QuantLibAddin::qlIMMNextDates(
      RefDateLib
      ,
       mMainCycle
   );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::IMMNextDates) {

  // validate js arguments
  if (info.Length() == 1 || !info[1]->IsArray()) {
      return Nan::ThrowError("MainCycle is required.");
  }
  // convert js argument to c++ type
  ObjectHandler::property_t RefDateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[0]).FromJust()));

  // convert js argument to c++ type
  std::vector<bool>MainCycleCpp;

  Local<Array> MainCycleArray = info[1].As<Array>();
  for (unsigned int i = 0; i < MainCycleArray->Length(); i++){
    MainCycleCpp.push_back(Nan::To<bool>(Nan::Get(MainCycleArray, i).ToLocalChecked()).FromJust());
  }

 
  // launch worker
  IMMNextDatesWorker* worker = new IMMNextDatesWorker(
    RefDateCpp
,     MainCycleCpp
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

void ASXIsASXdateWorker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes
  std::vector<QuantLib::Date> DateLib = ObjectHandler::vector::convert2<QuantLib::Date>(
      mDate, "Date");

     
  // loop on the input parameter and populate the return vector
  QuantLibAddin::qlASXIsASXdateBind bindObject =
      boost::bind(
          &QuantLib::ASX::isASXdate
          ,_1
          ,mMainCycle
    );
  ObjectHandler::loop
      <QuantLibAddin::qlASXIsASXdateBind, QuantLib::Date, bool>
          (bindObject,
            DateLib,
          mReturnValue
          );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::ASXIsASXdate) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsArray()) {
      return Nan::ThrowError("Date is required.");
  }
  if (info.Length() == 1 || !info[1]->IsBoolean()) {
      return Nan::ThrowError("MainCycle is required.");
  }
  // convert js argument to c++ type
  std::vector<ObjectHandler::property_t>DateCpp;

  Local<Array> DateArray = info[0].As<Array>();
  for (unsigned int i = 0; i < DateArray->Length(); i++){
    ObjectHandler::property_t tmp =
        ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(Nan::Get(DateArray, i).ToLocalChecked()).FromJust()));
    DateCpp.push_back(tmp);
  }

  // convert js argument to c++ type
  bool MainCycleCpp = Nan::To<bool>(info[1]).FromJust();

 
  // launch worker
  ASXIsASXdateWorker* worker = new ASXIsASXdateWorker(
    DateCpp
,     MainCycleCpp
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

void ASXIsASXcodeWorker::Execute(){

  try{
     
  // loop on the input parameter and populate the return vector
  QuantLibAddin::qlASXIsASXcodeBind bindObject =
      boost::bind(
          &QuantLib::ASX::isASXcode
          ,_1
          ,mMainCycle
    );
  ObjectHandler::loop
      <QuantLibAddin::qlASXIsASXcodeBind, string, bool>
          (bindObject,
           mCode,
          mReturnValue
          );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::ASXIsASXcode) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsArray()) {
      return Nan::ThrowError("Code is required.");
  }
  if (info.Length() == 1 || !info[1]->IsBoolean()) {
      return Nan::ThrowError("MainCycle is required.");
  }
  // convert js argument to c++ type
  std::vector<string>CodeCpp;

  Local<Array> CodeArray = info[0].As<Array>();
  for (unsigned int i = 0; i < CodeArray->Length(); i++){
    String::Utf8Value strCode(Nan::Get(CodeArray, i).ToLocalChecked()->ToString());
    CodeCpp.push_back(strdup(*strCode));
  }

  // convert js argument to c++ type
  bool MainCycleCpp = Nan::To<bool>(info[1]).FromJust();

 
  // launch worker
  ASXIsASXcodeWorker* worker = new ASXIsASXcodeWorker(
    CodeCpp
,     MainCycleCpp
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

void ASXcodeWorker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes
  std::vector<QuantLib::Date> ASXdateLib = ObjectHandler::vector::convert2<QuantLib::Date>(
      mASXdate, "ASXdate");

     
  // loop on the input parameter and populate the return vector
  QuantLibAddin::qlASXcodeBind bindObject =
      boost::bind(
          &QuantLib::ASX::code
          ,_1
    );
  ObjectHandler::loop
      <QuantLibAddin::qlASXcodeBind, QuantLib::Date, string>
          (bindObject,
            ASXdateLib,
          mReturnValue
          );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::ASXcode) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsArray()) {
      return Nan::ThrowError("ASXdate is required.");
  }
  // convert js argument to c++ type
  std::vector<ObjectHandler::property_t>ASXdateCpp;

  Local<Array> ASXdateArray = info[0].As<Array>();
  for (unsigned int i = 0; i < ASXdateArray->Length(); i++){
    ObjectHandler::property_t tmp =
        ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(Nan::Get(ASXdateArray, i).ToLocalChecked()).FromJust()));
    ASXdateCpp.push_back(tmp);
  }

 
  // launch worker
  ASXcodeWorker* worker = new ASXcodeWorker(
    ASXdateCpp
   );

  worker->Execute();

    Local<Array> tmpArray = Nan::New<Array>(worker->mReturnValue.size());
    for (unsigned int i = 0; i < worker->mReturnValue.size(); i++) {
      Nan::Set(tmpArray,i,Nan::New<String>(worker->mReturnValue[i]).ToLocalChecked());
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

void ASXNextCodeWorker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes
  QuantLib::Date RefDateLib = ObjectHandler::convert2<QuantLib::Date>(
      mRefDate, "RefDate");

       // invoke the utility function
  mReturnValue = QuantLib::ASX::nextCode(
      RefDateLib
      ,
       mMainCycle
     );
   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::ASXNextCode) {

  // validate js arguments
  if (info.Length() == 1 || !info[1]->IsBoolean()) {
      return Nan::ThrowError("MainCycle is required.");
  }
  // convert js argument to c++ type
  ObjectHandler::property_t RefDateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[0]).FromJust()));

  // convert js argument to c++ type
  bool MainCycleCpp = Nan::To<bool>(info[1]).FromJust();

 
  // launch worker
  ASXNextCodeWorker* worker = new ASXNextCodeWorker(
    RefDateCpp
,     MainCycleCpp
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

void ASXNextCodesWorker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes
  QuantLib::Date RefDateLib = ObjectHandler::convert2<QuantLib::Date>(
      mRefDate, "RefDate");

       // invoke the utility function
  mReturnValue = QuantLibAddin::qlASXNextCodes(
      RefDateLib
      ,
       mMainCycle
   );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::ASXNextCodes) {

  // validate js arguments
  if (info.Length() == 1 || !info[1]->IsArray()) {
      return Nan::ThrowError("MainCycle is required.");
  }
  // convert js argument to c++ type
  ObjectHandler::property_t RefDateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[0]).FromJust()));

  // convert js argument to c++ type
  std::vector<bool>MainCycleCpp;

  Local<Array> MainCycleArray = info[1].As<Array>();
  for (unsigned int i = 0; i < MainCycleArray->Length(); i++){
    MainCycleCpp.push_back(Nan::To<bool>(Nan::Get(MainCycleArray, i).ToLocalChecked()).FromJust());
  }

 
  // launch worker
  ASXNextCodesWorker* worker = new ASXNextCodesWorker(
    RefDateCpp
,     MainCycleCpp
   );

  worker->Execute();

    Local<Array> tmpArray = Nan::New<Array>(worker->mReturnValue.size());
    for (unsigned int i = 0; i < worker->mReturnValue.size(); i++) {
      Nan::Set(tmpArray,i,Nan::New<String>(worker->mReturnValue[i]).ToLocalChecked());
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

void ASXdateWorker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes
  QuantLib::Date RefDateLib = ObjectHandler::convert2<QuantLib::Date>(
      mRefDate, "RefDate");

       std::vector<QuantLib::Date> returnValue;


  // loop on the input parameter and populate the return vector
  QuantLibAddin::qlASXdateBind bindObject =
      boost::bind(
          &QuantLib::ASX::date
          ,_1
          ,RefDateLib
    );
  ObjectHandler::loop
      <QuantLibAddin::qlASXdateBind, string, QuantLib::Date>
          (bindObject,
           mASXcode,
          returnValue
          );


  mReturnValue = QuantLibAddin::libraryToVector(returnValue);

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::ASXdate) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsArray()) {
      return Nan::ThrowError("ASXcode is required.");
  }
  // convert js argument to c++ type
  std::vector<string>ASXcodeCpp;

  Local<Array> ASXcodeArray = info[0].As<Array>();
  for (unsigned int i = 0; i < ASXcodeArray->Length(); i++){
    String::Utf8Value strASXcode(Nan::Get(ASXcodeArray, i).ToLocalChecked()->ToString());
    ASXcodeCpp.push_back(strdup(*strASXcode));
  }

  // convert js argument to c++ type
  ObjectHandler::property_t RefDateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[1]).FromJust()));

 
  // launch worker
  ASXdateWorker* worker = new ASXdateWorker(
    ASXcodeCpp
,     RefDateCpp
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

void ASXNextDateWorker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes
  QuantLib::Date RefDateLib = ObjectHandler::convert2<QuantLib::Date>(
      mRefDate, "RefDate");

       // invoke the utility function
  QuantLib::Date returnValue = QuantLib::ASX::nextDate(
      RefDateLib
      ,
       mMainCycle
     );

  mReturnValue = QuantLibAddin::libraryToScalar(returnValue);

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::ASXNextDate) {

  // validate js arguments
  if (info.Length() == 1 || !info[1]->IsBoolean()) {
      return Nan::ThrowError("MainCycle is required.");
  }
  // convert js argument to c++ type
  ObjectHandler::property_t RefDateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[0]).FromJust()));

  // convert js argument to c++ type
  bool MainCycleCpp = Nan::To<bool>(info[1]).FromJust();

 
  // launch worker
  ASXNextDateWorker* worker = new ASXNextDateWorker(
    RefDateCpp
,     MainCycleCpp
   );

  worker->Execute();


  Local<v8::Value> argv[2] = {
		  Nan::New<String>(worker->mError).ToLocalChecked(),
      Nan::New<Number>(worker->mReturnValue)
	};

  v8::Local<v8::Array> results = Nan::New<v8::Array>();
  Nan::Set(results, 0, argv[0]);
  Nan::Set(results, 1, argv[1]);
  info.GetReturnValue().Set(results);
}

void ASXNextDatesWorker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes
  QuantLib::Date RefDateLib = ObjectHandler::convert2<QuantLib::Date>(
      mRefDate, "RefDate");

       // invoke the utility function
  std::vector<QuantLib::Date> returnValue = QuantLibAddin::qlASXNextDates(
      RefDateLib
      ,
       mMainCycle
   );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::ASXNextDates) {

  // validate js arguments
  if (info.Length() == 1 || !info[1]->IsArray()) {
      return Nan::ThrowError("MainCycle is required.");
  }
  // convert js argument to c++ type
  ObjectHandler::property_t RefDateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[0]).FromJust()));

  // convert js argument to c++ type
  std::vector<bool>MainCycleCpp;

  Local<Array> MainCycleArray = info[1].As<Array>();
  for (unsigned int i = 0; i < MainCycleArray->Length(); i++){
    MainCycleCpp.push_back(Nan::To<bool>(Nan::Get(MainCycleArray, i).ToLocalChecked()).FromJust());
  }

 
  // launch worker
  ASXNextDatesWorker* worker = new ASXNextDatesWorker(
    RefDateCpp
,     MainCycleCpp
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

void ECBKnownDatesWorker::Execute(){

  try{
       // invoke the utility function
  std::vector<QuantLib::Date> returnValue = QuantLibAddin::qlECBKnownDates(
  );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::ECBKnownDates) {

  // validate js arguments
 
  // launch worker
  ECBKnownDatesWorker* worker = new ECBKnownDatesWorker(
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

void ECBAddDateWorker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes
  QuantLib::Date DateLib = ObjectHandler::convert2<QuantLib::Date>(
      mDate, "Date");

       // invoke the utility function
  QuantLib::ECB::addDate(
      DateLib
     );
   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::ECBAddDate) {

  // validate js arguments
  // convert js argument to c++ type
  ObjectHandler::property_t DateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[0]).FromJust()));

 
  // launch worker
  ECBAddDateWorker* worker = new ECBAddDateWorker(
    DateCpp
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

void ECBRemoveDateWorker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes
  QuantLib::Date DateLib = ObjectHandler::convert2<QuantLib::Date>(
      mDate, "Date");

       // invoke the utility function
  QuantLib::ECB::removeDate(
      DateLib
     );
   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::ECBRemoveDate) {

  // validate js arguments
  // convert js argument to c++ type
  ObjectHandler::property_t DateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[0]).FromJust()));

 
  // launch worker
  ECBRemoveDateWorker* worker = new ECBRemoveDateWorker(
    DateCpp
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

void ECBdate2Worker::Execute(){

  try{

  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::Month MonthEnum =
      ObjectHandler::Create<QuantLib::Month>()(mMonth);

       // invoke the utility function
  QuantLib::Date returnValue = QuantLib::ECB::date(
      MonthEnum
      ,
       mYear
     );

  mReturnValue = QuantLibAddin::libraryToScalar(returnValue);

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::ECBdate2) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("Month is required.");
  }
  if (info.Length() == 1 || !info[1]->IsNumber()) {
      return Nan::ThrowError("Year is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strMonth(info[0]->ToString());
  string MonthCpp(strdup(*strMonth));

  // convert js argument to c++ type
  long YearCpp = Nan::To<int32_t>(info[1]).FromJust();

 
  // launch worker
  ECBdate2Worker* worker = new ECBdate2Worker(
    MonthCpp
,     YearCpp
   );

  worker->Execute();


  Local<v8::Value> argv[2] = {
		  Nan::New<String>(worker->mError).ToLocalChecked(),
      Nan::New<Number>(worker->mReturnValue)
	};

  v8::Local<v8::Array> results = Nan::New<v8::Array>();
  Nan::Set(results, 0, argv[0]);
  Nan::Set(results, 1, argv[1]);
  info.GetReturnValue().Set(results);
}

void ECBdateWorker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes
  QuantLib::Date RefDateLib = ObjectHandler::convert2<QuantLib::Date>(
      mRefDate, "RefDate");

       // invoke the utility function
  QuantLib::Date returnValue = QuantLib::ECB::date(
      mECBcode
      ,
       RefDateLib
     );

  mReturnValue = QuantLibAddin::libraryToScalar(returnValue);

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::ECBdate) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ECBcode is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strECBcode(info[0]->ToString());
  string ECBcodeCpp(strdup(*strECBcode));

  // convert js argument to c++ type
  ObjectHandler::property_t RefDateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[1]).FromJust()));

 
  // launch worker
  ECBdateWorker* worker = new ECBdateWorker(
    ECBcodeCpp
,     RefDateCpp
   );

  worker->Execute();


  Local<v8::Value> argv[2] = {
		  Nan::New<String>(worker->mError).ToLocalChecked(),
      Nan::New<Number>(worker->mReturnValue)
	};

  v8::Local<v8::Array> results = Nan::New<v8::Array>();
  Nan::Set(results, 0, argv[0]);
  Nan::Set(results, 1, argv[1]);
  info.GetReturnValue().Set(results);
}

void ECBcodeWorker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes
  QuantLib::Date ECBdateLib = ObjectHandler::convert2<QuantLib::Date>(
      mECBdate, "ECBdate");

       // invoke the utility function
  mReturnValue = QuantLib::ECB::code(
      ECBdateLib
     );
   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::ECBcode) {

  // validate js arguments
  // convert js argument to c++ type
  ObjectHandler::property_t ECBdateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[0]).FromJust()));

 
  // launch worker
  ECBcodeWorker* worker = new ECBcodeWorker(
    ECBdateCpp
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

void ECBNextDateWorker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes
  QuantLib::Date DateLib = ObjectHandler::convert2<QuantLib::Date>(
      mDate, "Date");

       // invoke the utility function
  QuantLib::Date returnValue = QuantLib::ECB::nextDate(
      DateLib
     );

  mReturnValue = QuantLibAddin::libraryToScalar(returnValue);

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::ECBNextDate) {

  // validate js arguments
  // convert js argument to c++ type
  ObjectHandler::property_t DateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[0]).FromJust()));

 
  // launch worker
  ECBNextDateWorker* worker = new ECBNextDateWorker(
    DateCpp
   );

  worker->Execute();


  Local<v8::Value> argv[2] = {
		  Nan::New<String>(worker->mError).ToLocalChecked(),
      Nan::New<Number>(worker->mReturnValue)
	};

  v8::Local<v8::Array> results = Nan::New<v8::Array>();
  Nan::Set(results, 0, argv[0]);
  Nan::Set(results, 1, argv[1]);
  info.GetReturnValue().Set(results);
}

void ECBNextDate2Worker::Execute(){

  try{
       // invoke the utility function
  QuantLib::Date returnValue = QuantLib::ECB::nextDate(
      mCode
     );

  mReturnValue = QuantLibAddin::libraryToScalar(returnValue);

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::ECBNextDate2) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("Code is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strCode(info[0]->ToString());
  string CodeCpp(strdup(*strCode));

 
  // launch worker
  ECBNextDate2Worker* worker = new ECBNextDate2Worker(
    CodeCpp
   );

  worker->Execute();


  Local<v8::Value> argv[2] = {
		  Nan::New<String>(worker->mError).ToLocalChecked(),
      Nan::New<Number>(worker->mReturnValue)
	};

  v8::Local<v8::Array> results = Nan::New<v8::Array>();
  Nan::Set(results, 0, argv[0]);
  Nan::Set(results, 1, argv[1]);
  info.GetReturnValue().Set(results);
}

void ECBNextDatesWorker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes
  QuantLib::Date DateLib = ObjectHandler::convert2<QuantLib::Date>(
      mDate, "Date");

       // invoke the utility function
  std::vector<QuantLib::Date> returnValue = QuantLib::ECB::nextDates(
      DateLib
   );


  mReturnValue = QuantLibAddin::libraryToVector(returnValue);

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::ECBNextDates) {

  // validate js arguments
  // convert js argument to c++ type
  ObjectHandler::property_t DateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[0]).FromJust()));

 
  // launch worker
  ECBNextDatesWorker* worker = new ECBNextDatesWorker(
    DateCpp
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

void ECBIsECBdateWorker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes
  std::vector<QuantLib::Date> DateLib = ObjectHandler::vector::convert2<QuantLib::Date>(
      mDate, "Date");

     
  // loop on the input parameter and populate the return vector
  QuantLibAddin::qlECBIsECBdateBind bindObject =
      boost::bind(
          &QuantLib::ECB::isECBdate
          ,_1
    );
  ObjectHandler::loop
      <QuantLibAddin::qlECBIsECBdateBind, QuantLib::Date, bool>
          (bindObject,
            DateLib,
          mReturnValue
          );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::ECBIsECBdate) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsArray()) {
      return Nan::ThrowError("Date is required.");
  }
  // convert js argument to c++ type
  std::vector<ObjectHandler::property_t>DateCpp;

  Local<Array> DateArray = info[0].As<Array>();
  for (unsigned int i = 0; i < DateArray->Length(); i++){
    ObjectHandler::property_t tmp =
        ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(Nan::Get(DateArray, i).ToLocalChecked()).FromJust()));
    DateCpp.push_back(tmp);
  }

 
  // launch worker
  ECBIsECBdateWorker* worker = new ECBIsECBdateWorker(
    DateCpp
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

void ECBIsECBcodeWorker::Execute(){

  try{
     
  // loop on the input parameter and populate the return vector
  QuantLibAddin::qlECBIsECBcodeBind bindObject =
      boost::bind(
          &QuantLib::ECB::isECBcode
          ,_1
    );
  ObjectHandler::loop
      <QuantLibAddin::qlECBIsECBcodeBind, string, bool>
          (bindObject,
           mCode,
          mReturnValue
          );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::ECBIsECBcode) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsArray()) {
      return Nan::ThrowError("Code is required.");
  }
  // convert js argument to c++ type
  std::vector<string>CodeCpp;

  Local<Array> CodeArray = info[0].As<Array>();
  for (unsigned int i = 0; i < CodeArray->Length(); i++){
    String::Utf8Value strCode(Nan::Get(CodeArray, i).ToLocalChecked()->ToString());
    CodeCpp.push_back(strdup(*strCode));
  }

 
  // launch worker
  ECBIsECBcodeWorker* worker = new ECBIsECBcodeWorker(
    CodeCpp
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

void ECBNextCodeWorker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes
  QuantLib::Date RefDateLib = ObjectHandler::convert2<QuantLib::Date>(
      mRefDate, "RefDate");

       // invoke the utility function
  mReturnValue = QuantLib::ECB::nextCode(
      RefDateLib
     );
   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::ECBNextCode) {

  // validate js arguments
  // convert js argument to c++ type
  ObjectHandler::property_t RefDateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[0]).FromJust()));

 
  // launch worker
  ECBNextCodeWorker* worker = new ECBNextCodeWorker(
    RefDateCpp
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

void ECBNextCode2Worker::Execute(){

  try{
       // invoke the utility function
  mReturnValue = QuantLib::ECB::nextCode(
      mCode
     );
   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::ECBNextCode2) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("Code is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strCode(info[0]->ToString());
  string CodeCpp(strdup(*strCode));

 
  // launch worker
  ECBNextCode2Worker* worker = new ECBNextCode2Worker(
    CodeCpp
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
 