/* 
  Copyright (C) 2016 -2017 Jerry Jin
*/

#include <nan.h>
#include <string.h>

#include "index.hpp"

#include <qlo/qladdindefines.hpp>
#include <qlo/indexes/bmaindex.hpp>
#include <qlo/indexes/ibor/euribor.hpp>
#include <qlo/indexes/ibor/libor.hpp>
#include <qlo/indexes/swap/euriborswap.hpp>
#include <qlo/indexes/swap/liborswap.hpp>
#include <qlo/indexes/swap/isdafixaswap.hpp>
#include <qlo/termstructures.hpp>
#include <qlo/handleimpl.hpp>
#include <qlo/timeseries.hpp>
#include <ql/termstructures/yieldtermstructure.hpp>
#include <ql/indexes/iborindex.hpp>
#include <ql/experimental/coupons/proxyibor.hpp>
#include <ql/indexes/swapindex.hpp>
#include <qlo/loop/loop_index.hpp>
 #include <oh/objecthandler.hpp>
#include <oh/conversions/getobjectvector.hpp>
#include <qlo/valueobjects/vo_all.hpp>
#include <qlo/conversions/all.hpp>
#include "../loop.hpp"


void IborIndexWorker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes
  QuantLib::Period TenorLib;
  QuantLibAddin::cppToLibrary(mTenor, TenorLib);


  // convert input datatypes to QuantLib datatypes
  QuantLib::Natural FixingDaysLib = ObjectHandler::convert2<long>(
      mFixingDays, "FixingDays", QuantLib::Null<QuantLib::Natural>());


  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::Currency CurrencyEnum =
      ObjectHandler::Create<QuantLib::Currency>()(mCurrency);


  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::Calendar CalendarEnum =
      ObjectHandler::Create<QuantLib::Calendar>()(mCalendar);


  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::BusinessDayConvention BDayConventionEnum =
      ObjectHandler::Create<QuantLib::BusinessDayConvention>()(mBDayConvention);


  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::DayCounter DayCounterEnum =
      ObjectHandler::Create<QuantLib::DayCounter>()(mDayCounter);


  // convert object IDs into library objects
  OH_GET_OBJECT(FwdCurveCoerce, mFwdCurve, ObjectHandler::Object)
  QuantLib::Handle<QuantLib::YieldTermStructure> FwdCurveLibObj =
      QuantLibAddin::CoerceHandle<
          QuantLibAddin::YieldTermStructure,
          QuantLib::YieldTermStructure>()(
              FwdCurveCoerce);

 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlIborIndex(
          mObjectID,
          mFamilyName,
          mTenor,
          mFixingDays,
          mCurrency,
          mCalendar,
          mBDayConvention,
          mEndOfMonth,
          mDayCounter,
          mFwdCurve,
          false
      ));

    // Construct the Object
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::IborIndex(
          valueObject,
          mFamilyName,
          TenorLib,
          FixingDaysLib,
          CurrencyEnum,
          CalendarEnum,
          BDayConventionEnum,
          mEndOfMonth,
          DayCounterEnum,
          FwdCurveLibObj,
          false
      ));

    // Store the Object in the Repository
    mReturnValue = ObjectHandler::Repository::instance().storeObject(mObjectID, object, false, valueObject);
    
   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::IborIndex) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsString()) {
      return Nan::ThrowError("FamilyName is required.");
  }
  if (info.Length() == 2 || !info[2]->IsString()) {
      return Nan::ThrowError("Tenor is required.");
  }
  if (info.Length() == 4 || !info[4]->IsString()) {
      return Nan::ThrowError("Currency is required.");
  }
  if (info.Length() == 5 || !info[5]->IsString()) {
      return Nan::ThrowError("Calendar is required.");
  }
  if (info.Length() == 6 || !info[6]->IsString()) {
      return Nan::ThrowError("BDayConvention is required.");
  }
  if (info.Length() == 7 || !info[7]->IsBoolean()) {
      return Nan::ThrowError("EndOfMonth is required.");
  }
  if (info.Length() == 8 || !info[8]->IsString()) {
      return Nan::ThrowError("DayCounter is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  String::Utf8Value strFamilyName(info[1]->ToString());
  string FamilyNameCpp(strdup(*strFamilyName));

  // convert js argument to c++ type
  String::Utf8Value strTenor(info[2]->ToString());
  string TenorCpp(strdup(*strTenor));

  // convert js argument to c++ type
  ObjectHandler::property_t FixingDaysCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[3]).FromJust()));

  // convert js argument to c++ type
  String::Utf8Value strCurrency(info[4]->ToString());
  string CurrencyCpp(strdup(*strCurrency));

  // convert js argument to c++ type
  String::Utf8Value strCalendar(info[5]->ToString());
  string CalendarCpp(strdup(*strCalendar));

  // convert js argument to c++ type
  String::Utf8Value strBDayConvention(info[6]->ToString());
  string BDayConventionCpp(strdup(*strBDayConvention));

  // convert js argument to c++ type
  bool EndOfMonthCpp = Nan::To<bool>(info[7]).FromJust();

  // convert js argument to c++ type
  String::Utf8Value strDayCounter(info[8]->ToString());
  string DayCounterCpp(strdup(*strDayCounter));

  // convert js argument to c++ type
  ObjectHandler::property_t FwdCurveCpp =
      ObjectHandler::property_t(static_cast<double>(Nan::To<double>(info[9]).FromJust()));

 
  // launch worker
  IborIndexWorker* worker = new IborIndexWorker(
    ObjectIDCpp
,     FamilyNameCpp
,     TenorCpp
,     FixingDaysCpp
,     CurrencyCpp
,     CalendarCpp
,     BDayConventionCpp
,     EndOfMonthCpp
,     DayCounterCpp
,     FwdCurveCpp
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

void OvernightIndexWorker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes
  QuantLib::Natural FixingDaysLib = ObjectHandler::convert2<long>(
      mFixingDays, "FixingDays", QuantLib::Null<QuantLib::Natural>());


  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::Currency CurrencyEnum =
      ObjectHandler::Create<QuantLib::Currency>()(mCurrency);


  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::Calendar CalendarEnum =
      ObjectHandler::Create<QuantLib::Calendar>()(mCalendar);


  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::DayCounter DayCounterEnum =
      ObjectHandler::Create<QuantLib::DayCounter>()(mDayCounter);


  // convert object IDs into library objects
  OH_GET_OBJECT(YieldCurveCoerce, mYieldCurve, ObjectHandler::Object)
  QuantLib::Handle<QuantLib::YieldTermStructure> YieldCurveLibObj =
      QuantLibAddin::CoerceHandle<
          QuantLibAddin::YieldTermStructure,
          QuantLib::YieldTermStructure>()(
              YieldCurveCoerce);

 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlOvernightIndex(
          mObjectID,
          mFamilyName,
          mFixingDays,
          mCurrency,
          mCalendar,
          mDayCounter,
          mYieldCurve,
          false
      ));

    // Construct the Object
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::OvernightIndex(
          valueObject,
          mFamilyName,
          FixingDaysLib,
          CurrencyEnum,
          CalendarEnum,
          DayCounterEnum,
          YieldCurveLibObj,
          false
      ));

    // Store the Object in the Repository
    mReturnValue = ObjectHandler::Repository::instance().storeObject(mObjectID, object, false, valueObject);
    
   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::OvernightIndex) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsString()) {
      return Nan::ThrowError("FamilyName is required.");
  }
  if (info.Length() == 3 || !info[3]->IsString()) {
      return Nan::ThrowError("Currency is required.");
  }
  if (info.Length() == 4 || !info[4]->IsString()) {
      return Nan::ThrowError("Calendar is required.");
  }
  if (info.Length() == 5 || !info[5]->IsString()) {
      return Nan::ThrowError("DayCounter is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  String::Utf8Value strFamilyName(info[1]->ToString());
  string FamilyNameCpp(strdup(*strFamilyName));

  // convert js argument to c++ type
  ObjectHandler::property_t FixingDaysCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[2]).FromJust()));

  // convert js argument to c++ type
  String::Utf8Value strCurrency(info[3]->ToString());
  string CurrencyCpp(strdup(*strCurrency));

  // convert js argument to c++ type
  String::Utf8Value strCalendar(info[4]->ToString());
  string CalendarCpp(strdup(*strCalendar));

  // convert js argument to c++ type
  String::Utf8Value strDayCounter(info[5]->ToString());
  string DayCounterCpp(strdup(*strDayCounter));

  // convert js argument to c++ type
  ObjectHandler::property_t YieldCurveCpp =
      ObjectHandler::property_t(static_cast<double>(Nan::To<double>(info[6]).FromJust()));

 
  // launch worker
  OvernightIndexWorker* worker = new OvernightIndexWorker(
    ObjectIDCpp
,     FamilyNameCpp
,     FixingDaysCpp
,     CurrencyCpp
,     CalendarCpp
,     DayCounterCpp
,     YieldCurveCpp
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

void EuriborWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_OBJECT(YieldCurveCoerce, mYieldCurve, ObjectHandler::Object)
  QuantLib::Handle<QuantLib::YieldTermStructure> YieldCurveLibObj =
      QuantLibAddin::CoerceHandle<
          QuantLibAddin::YieldTermStructure,
          QuantLib::YieldTermStructure>()(
              YieldCurveCoerce);

 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlEuribor(
          mObjectID,
          mTenor,
          mYieldCurve,
          false
      ));

    // Construct the Object
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::Euribor(
          valueObject,
          mTenor,
          YieldCurveLibObj,
          false
      ));

    // Store the Object in the Repository
    mReturnValue = ObjectHandler::Repository::instance().storeObject(mObjectID, object, false, valueObject);
    
   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::Euribor) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsString()) {
      return Nan::ThrowError("Tenor is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  String::Utf8Value strTenor(info[1]->ToString());
  string TenorCpp(strdup(*strTenor));

  // convert js argument to c++ type
  ObjectHandler::property_t YieldCurveCpp =
      ObjectHandler::property_t(static_cast<double>(Nan::To<double>(info[2]).FromJust()));

 
  // launch worker
  EuriborWorker* worker = new EuriborWorker(
    ObjectIDCpp
,     TenorCpp
,     YieldCurveCpp
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

void Euribor365Worker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_OBJECT(YieldCurveCoerce, mYieldCurve, ObjectHandler::Object)
  QuantLib::Handle<QuantLib::YieldTermStructure> YieldCurveLibObj =
      QuantLibAddin::CoerceHandle<
          QuantLibAddin::YieldTermStructure,
          QuantLib::YieldTermStructure>()(
              YieldCurveCoerce);

 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlEuribor365(
          mObjectID,
          mTenor,
          mYieldCurve,
          false
      ));

    // Construct the Object
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::Euribor365(
          valueObject,
          mTenor,
          YieldCurveLibObj,
          false
      ));

    // Store the Object in the Repository
    mReturnValue = ObjectHandler::Repository::instance().storeObject(mObjectID, object, false, valueObject);
    
   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::Euribor365) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsString()) {
      return Nan::ThrowError("Tenor is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  String::Utf8Value strTenor(info[1]->ToString());
  string TenorCpp(strdup(*strTenor));

  // convert js argument to c++ type
  ObjectHandler::property_t YieldCurveCpp =
      ObjectHandler::property_t(static_cast<double>(Nan::To<double>(info[2]).FromJust()));

 
  // launch worker
  Euribor365Worker* worker = new Euribor365Worker(
    ObjectIDCpp
,     TenorCpp
,     YieldCurveCpp
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

void EoniaWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_OBJECT(YieldCurveCoerce, mYieldCurve, ObjectHandler::Object)
  QuantLib::Handle<QuantLib::YieldTermStructure> YieldCurveLibObj =
      QuantLibAddin::CoerceHandle<
          QuantLibAddin::YieldTermStructure,
          QuantLib::YieldTermStructure>()(
              YieldCurveCoerce);

 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlEonia(
          mObjectID,
          mYieldCurve,
          false
      ));

    // Construct the Object
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::Eonia(
          valueObject,
          YieldCurveLibObj,
          false
      ));

    // Store the Object in the Repository
    mReturnValue = ObjectHandler::Repository::instance().storeObject(mObjectID, object, false, valueObject);
    
   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::Eonia) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  ObjectHandler::property_t YieldCurveCpp =
      ObjectHandler::property_t(static_cast<double>(Nan::To<double>(info[1]).FromJust()));

 
  // launch worker
  EoniaWorker* worker = new EoniaWorker(
    ObjectIDCpp
,     YieldCurveCpp
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

void LiborWorker::Execute(){

  try{

  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::Currency CurrencyEnum =
      ObjectHandler::Create<QuantLib::Currency>()(mCurrency);


  // convert object IDs into library objects
  OH_GET_OBJECT(YieldCurveCoerce, mYieldCurve, ObjectHandler::Object)
  QuantLib::Handle<QuantLib::YieldTermStructure> YieldCurveLibObj =
      QuantLibAddin::CoerceHandle<
          QuantLibAddin::YieldTermStructure,
          QuantLib::YieldTermStructure>()(
              YieldCurveCoerce);

 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlLibor(
          mObjectID,
          mCurrency,
          mTenor,
          mYieldCurve,
          false
      ));

    // Construct the Object
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::Libor(
          valueObject,
          CurrencyEnum,
          mTenor,
          YieldCurveLibObj,
          false
      ));

    // Store the Object in the Repository
    mReturnValue = ObjectHandler::Repository::instance().storeObject(mObjectID, object, false, valueObject);
    
   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::Libor) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsString()) {
      return Nan::ThrowError("Currency is required.");
  }
  if (info.Length() == 2 || !info[2]->IsString()) {
      return Nan::ThrowError("Tenor is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  String::Utf8Value strCurrency(info[1]->ToString());
  string CurrencyCpp(strdup(*strCurrency));

  // convert js argument to c++ type
  String::Utf8Value strTenor(info[2]->ToString());
  string TenorCpp(strdup(*strTenor));

  // convert js argument to c++ type
  ObjectHandler::property_t YieldCurveCpp =
      ObjectHandler::property_t(static_cast<double>(Nan::To<double>(info[3]).FromJust()));

 
  // launch worker
  LiborWorker* worker = new LiborWorker(
    ObjectIDCpp
,     CurrencyCpp
,     TenorCpp
,     YieldCurveCpp
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

void SoniaWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_OBJECT(YieldCurveCoerce, mYieldCurve, ObjectHandler::Object)
  QuantLib::Handle<QuantLib::YieldTermStructure> YieldCurveLibObj =
      QuantLibAddin::CoerceHandle<
          QuantLibAddin::YieldTermStructure,
          QuantLib::YieldTermStructure>()(
              YieldCurveCoerce);

 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlSonia(
          mObjectID,
          mYieldCurve,
          false
      ));

    // Construct the Object
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::Sonia(
          valueObject,
          YieldCurveLibObj,
          false
      ));

    // Store the Object in the Repository
    mReturnValue = ObjectHandler::Repository::instance().storeObject(mObjectID, object, false, valueObject);
    
   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::Sonia) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  ObjectHandler::property_t YieldCurveCpp =
      ObjectHandler::property_t(static_cast<double>(Nan::To<double>(info[1]).FromJust()));

 
  // launch worker
  SoniaWorker* worker = new SoniaWorker(
    ObjectIDCpp
,     YieldCurveCpp
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

void SwapIndexWorker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes
  QuantLib::Period TenorLib;
  QuantLibAddin::cppToLibrary(mTenor, TenorLib);


  // convert input datatypes to QuantLib datatypes
  QuantLib::Natural FixingDaysLib = ObjectHandler::convert2<long>(
      mFixingDays, "FixingDays", QuantLib::Null<QuantLib::Natural>());


  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::Currency CurrencyEnum =
      ObjectHandler::Create<QuantLib::Currency>()(mCurrency);


  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::Calendar CalendarEnum =
      ObjectHandler::Create<QuantLib::Calendar>()(mCalendar);


  // convert input datatypes to QuantLib datatypes
  QuantLib::Period FixedLegTenorLib;
  QuantLibAddin::cppToLibrary(mFixedLegTenor, FixedLegTenorLib);


  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::BusinessDayConvention FixedLegBDCEnum =
      ObjectHandler::Create<QuantLib::BusinessDayConvention>()(mFixedLegBDC);


  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::DayCounter FixedLegDayCounterEnum =
      ObjectHandler::Create<QuantLib::DayCounter>()(mFixedLegDayCounter);


  // convert object IDs into library objects
  OH_GET_REFERENCE(IborIndexLibObjPtr, mIborIndex,
      QuantLibAddin::IborIndex, QuantLib::IborIndex)


  // convert object IDs into library objects
  OH_GET_OBJECT(DiscCurveCoerce, mDiscCurve, ObjectHandler::Object)
  QuantLib::Handle<QuantLib::YieldTermStructure> DiscCurveLibObj =
      QuantLibAddin::CoerceHandle<
          QuantLibAddin::YieldTermStructure,
          QuantLib::YieldTermStructure>()(
              DiscCurveCoerce);

 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlSwapIndex(
          mObjectID,
          mFamilyName,
          mTenor,
          mFixingDays,
          mCurrency,
          mCalendar,
          mFixedLegTenor,
          mFixedLegBDC,
          mFixedLegDayCounter,
          mIborIndex,
          mDiscCurve,
          false
      ));

    // Construct the Object
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::SwapIndex(
          valueObject,
          mFamilyName,
          TenorLib,
          FixingDaysLib,
          CurrencyEnum,
          CalendarEnum,
          FixedLegTenorLib,
          FixedLegBDCEnum,
          FixedLegDayCounterEnum,
          IborIndexLibObjPtr,
          DiscCurveLibObj,
          false
      ));

    // Store the Object in the Repository
    mReturnValue = ObjectHandler::Repository::instance().storeObject(mObjectID, object, false, valueObject);
    
   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::SwapIndex) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsString()) {
      return Nan::ThrowError("FamilyName is required.");
  }
  if (info.Length() == 2 || !info[2]->IsString()) {
      return Nan::ThrowError("Tenor is required.");
  }
  if (info.Length() == 4 || !info[4]->IsString()) {
      return Nan::ThrowError("Currency is required.");
  }
  if (info.Length() == 5 || !info[5]->IsString()) {
      return Nan::ThrowError("Calendar is required.");
  }
  if (info.Length() == 6 || !info[6]->IsString()) {
      return Nan::ThrowError("FixedLegTenor is required.");
  }
  if (info.Length() == 7 || !info[7]->IsString()) {
      return Nan::ThrowError("FixedLegBDC is required.");
  }
  if (info.Length() == 8 || !info[8]->IsString()) {
      return Nan::ThrowError("FixedLegDayCounter is required.");
  }
  if (info.Length() == 9 || !info[9]->IsString()) {
      return Nan::ThrowError("IborIndex is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  String::Utf8Value strFamilyName(info[1]->ToString());
  string FamilyNameCpp(strdup(*strFamilyName));

  // convert js argument to c++ type
  String::Utf8Value strTenor(info[2]->ToString());
  string TenorCpp(strdup(*strTenor));

  // convert js argument to c++ type
  ObjectHandler::property_t FixingDaysCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[3]).FromJust()));

  // convert js argument to c++ type
  String::Utf8Value strCurrency(info[4]->ToString());
  string CurrencyCpp(strdup(*strCurrency));

  // convert js argument to c++ type
  String::Utf8Value strCalendar(info[5]->ToString());
  string CalendarCpp(strdup(*strCalendar));

  // convert js argument to c++ type
  String::Utf8Value strFixedLegTenor(info[6]->ToString());
  string FixedLegTenorCpp(strdup(*strFixedLegTenor));

  // convert js argument to c++ type
  String::Utf8Value strFixedLegBDC(info[7]->ToString());
  string FixedLegBDCCpp(strdup(*strFixedLegBDC));

  // convert js argument to c++ type
  String::Utf8Value strFixedLegDayCounter(info[8]->ToString());
  string FixedLegDayCounterCpp(strdup(*strFixedLegDayCounter));

  // convert js argument to c++ type
  String::Utf8Value strIborIndex(info[9]->ToString());
  string IborIndexCpp(strdup(*strIborIndex));

  // convert js argument to c++ type
  ObjectHandler::property_t DiscCurveCpp =
      ObjectHandler::property_t(static_cast<double>(Nan::To<double>(info[10]).FromJust()));

 
  // launch worker
  SwapIndexWorker* worker = new SwapIndexWorker(
    ObjectIDCpp
,     FamilyNameCpp
,     TenorCpp
,     FixingDaysCpp
,     CurrencyCpp
,     CalendarCpp
,     FixedLegTenorCpp
,     FixedLegBDCCpp
,     FixedLegDayCounterCpp
,     IborIndexCpp
,     DiscCurveCpp
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

void EuriborSwapWorker::Execute(){

  try{

  // convert input datatypes to QuantLib enumerated datatypes
  QuantLibAddin::SwapIndex::FixingType FixingTypeEnum =
      ObjectHandler::Create<QuantLibAddin::SwapIndex::FixingType>()(mFixingType);


  // convert input datatypes to QuantLib datatypes
  QuantLib::Period TenorLib;
  QuantLibAddin::cppToLibrary(mTenor, TenorLib);


  // convert object IDs into library objects
  OH_GET_OBJECT(FwdCurveCoerce, mFwdCurve, ObjectHandler::Object)
  QuantLib::Handle<QuantLib::YieldTermStructure> FwdCurveLibObj =
      QuantLibAddin::CoerceHandle<
          QuantLibAddin::YieldTermStructure,
          QuantLib::YieldTermStructure>()(
              FwdCurveCoerce);


  // convert object IDs into library objects
  OH_GET_OBJECT(DiscCurveCoerce, mDiscCurve, ObjectHandler::Object)
  QuantLib::Handle<QuantLib::YieldTermStructure> DiscCurveLibObj =
      QuantLibAddin::CoerceHandle<
          QuantLibAddin::YieldTermStructure,
          QuantLib::YieldTermStructure>()(
              DiscCurveCoerce);

 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlEuriborSwap(
          mObjectID,
          mFixingType,
          mTenor,
          mFwdCurve,
          mDiscCurve,
          false
      ));

    // Construct the Object
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::EuriborSwap(
          valueObject,
          FixingTypeEnum,
          TenorLib,
          FwdCurveLibObj,
          DiscCurveLibObj,
          false
      ));

    // Store the Object in the Repository
    mReturnValue = ObjectHandler::Repository::instance().storeObject(mObjectID, object, false, valueObject);
    
   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::EuriborSwap) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsString()) {
      return Nan::ThrowError("FixingType is required.");
  }
  if (info.Length() == 2 || !info[2]->IsString()) {
      return Nan::ThrowError("Tenor is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  String::Utf8Value strFixingType(info[1]->ToString());
  string FixingTypeCpp(strdup(*strFixingType));

  // convert js argument to c++ type
  String::Utf8Value strTenor(info[2]->ToString());
  string TenorCpp(strdup(*strTenor));

  // convert js argument to c++ type
  ObjectHandler::property_t FwdCurveCpp =
      ObjectHandler::property_t(static_cast<double>(Nan::To<double>(info[3]).FromJust()));

  // convert js argument to c++ type
  ObjectHandler::property_t DiscCurveCpp =
      ObjectHandler::property_t(static_cast<double>(Nan::To<double>(info[4]).FromJust()));

 
  // launch worker
  EuriborSwapWorker* worker = new EuriborSwapWorker(
    ObjectIDCpp
,     FixingTypeCpp
,     TenorCpp
,     FwdCurveCpp
,     DiscCurveCpp
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

void LiborSwapWorker::Execute(){

  try{

  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::Currency CurrencyEnum =
      ObjectHandler::Create<QuantLib::Currency>()(mCurrency);


  // convert input datatypes to QuantLib enumerated datatypes
  QuantLibAddin::SwapIndex::FixingType FixingTypeEnum =
      ObjectHandler::Create<QuantLibAddin::SwapIndex::FixingType>()(mFixingType);


  // convert input datatypes to QuantLib datatypes
  QuantLib::Period TenorLib;
  QuantLibAddin::cppToLibrary(mTenor, TenorLib);


  // convert object IDs into library objects
  OH_GET_OBJECT(FwdCurveCoerce, mFwdCurve, ObjectHandler::Object)
  QuantLib::Handle<QuantLib::YieldTermStructure> FwdCurveLibObj =
      QuantLibAddin::CoerceHandle<
          QuantLibAddin::YieldTermStructure,
          QuantLib::YieldTermStructure>()(
              FwdCurveCoerce);


  // convert object IDs into library objects
  OH_GET_OBJECT(DiscCurveCoerce, mDiscCurve, ObjectHandler::Object)
  QuantLib::Handle<QuantLib::YieldTermStructure> DiscCurveLibObj =
      QuantLibAddin::CoerceHandle<
          QuantLibAddin::YieldTermStructure,
          QuantLib::YieldTermStructure>()(
              DiscCurveCoerce);

 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlLiborSwap(
          mObjectID,
          mCurrency,
          mFixingType,
          mTenor,
          mFwdCurve,
          mDiscCurve,
          false
      ));

    // Construct the Object
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::LiborSwap(
          valueObject,
          CurrencyEnum,
          FixingTypeEnum,
          TenorLib,
          FwdCurveLibObj,
          DiscCurveLibObj,
          false
      ));

    // Store the Object in the Repository
    mReturnValue = ObjectHandler::Repository::instance().storeObject(mObjectID, object, false, valueObject);
    
   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::LiborSwap) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsString()) {
      return Nan::ThrowError("Currency is required.");
  }
  if (info.Length() == 2 || !info[2]->IsString()) {
      return Nan::ThrowError("FixingType is required.");
  }
  if (info.Length() == 3 || !info[3]->IsString()) {
      return Nan::ThrowError("Tenor is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  String::Utf8Value strCurrency(info[1]->ToString());
  string CurrencyCpp(strdup(*strCurrency));

  // convert js argument to c++ type
  String::Utf8Value strFixingType(info[2]->ToString());
  string FixingTypeCpp(strdup(*strFixingType));

  // convert js argument to c++ type
  String::Utf8Value strTenor(info[3]->ToString());
  string TenorCpp(strdup(*strTenor));

  // convert js argument to c++ type
  ObjectHandler::property_t FwdCurveCpp =
      ObjectHandler::property_t(static_cast<double>(Nan::To<double>(info[4]).FromJust()));

  // convert js argument to c++ type
  ObjectHandler::property_t DiscCurveCpp =
      ObjectHandler::property_t(static_cast<double>(Nan::To<double>(info[5]).FromJust()));

 
  // launch worker
  LiborSwapWorker* worker = new LiborSwapWorker(
    ObjectIDCpp
,     CurrencyCpp
,     FixingTypeCpp
,     TenorCpp
,     FwdCurveCpp
,     DiscCurveCpp
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

void EuriborSwapIsdaFixAWorker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes
  QuantLib::Period TenorLib;
  QuantLibAddin::cppToLibrary(mTenor, TenorLib);


  // convert object IDs into library objects
  OH_GET_OBJECT(FwdCurveCoerce, mFwdCurve, ObjectHandler::Object)
  QuantLib::Handle<QuantLib::YieldTermStructure> FwdCurveLibObj =
      QuantLibAddin::CoerceHandle<
          QuantLibAddin::YieldTermStructure,
          QuantLib::YieldTermStructure>()(
              FwdCurveCoerce);


  // convert object IDs into library objects
  OH_GET_OBJECT(DiscCurveCoerce, mDiscCurve, ObjectHandler::Object)
  QuantLib::Handle<QuantLib::YieldTermStructure> DiscCurveLibObj =
      QuantLibAddin::CoerceHandle<
          QuantLibAddin::YieldTermStructure,
          QuantLib::YieldTermStructure>()(
              DiscCurveCoerce);

 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlEuriborSwapIsdaFixA(
          mObjectID,
          mTenor,
          mFwdCurve,
          mDiscCurve,
          false
      ));

    // Construct the Object
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::EuriborSwapIsdaFixA(
          valueObject,
          TenorLib,
          FwdCurveLibObj,
          DiscCurveLibObj,
          false
      ));

    // Store the Object in the Repository
    mReturnValue = ObjectHandler::Repository::instance().storeObject(mObjectID, object, false, valueObject);
    
   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::EuriborSwapIsdaFixA) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsString()) {
      return Nan::ThrowError("Tenor is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  String::Utf8Value strTenor(info[1]->ToString());
  string TenorCpp(strdup(*strTenor));

  // convert js argument to c++ type
  ObjectHandler::property_t FwdCurveCpp =
      ObjectHandler::property_t(static_cast<double>(Nan::To<double>(info[2]).FromJust()));

  // convert js argument to c++ type
  ObjectHandler::property_t DiscCurveCpp =
      ObjectHandler::property_t(static_cast<double>(Nan::To<double>(info[3]).FromJust()));

 
  // launch worker
  EuriborSwapIsdaFixAWorker* worker = new EuriborSwapIsdaFixAWorker(
    ObjectIDCpp
,     TenorCpp
,     FwdCurveCpp
,     DiscCurveCpp
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

void BMAIndexWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_OBJECT(YieldCurveCoerce, mYieldCurve, ObjectHandler::Object)
  QuantLib::Handle<QuantLib::YieldTermStructure> YieldCurveLibObj =
      QuantLibAddin::CoerceHandle<
          QuantLibAddin::YieldTermStructure,
          QuantLib::YieldTermStructure>()(
              YieldCurveCoerce);

 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlBMAIndex(
          mObjectID,
          mYieldCurve,
          false
      ));

    // Construct the Object
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::BMAIndex(
          valueObject,
          YieldCurveLibObj,
          false
      ));

    // Store the Object in the Repository
    mReturnValue = ObjectHandler::Repository::instance().storeObject(mObjectID, object, false, valueObject);
    
   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::BMAIndex) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  ObjectHandler::property_t YieldCurveCpp =
      ObjectHandler::property_t(static_cast<double>(Nan::To<double>(info[1]).FromJust()));

 
  // launch worker
  BMAIndexWorker* worker = new BMAIndexWorker(
    ObjectIDCpp
,     YieldCurveCpp
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

void ProxyIborWorker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes
  QuantLib::Period TenorLib;
  QuantLibAddin::cppToLibrary(mTenor, TenorLib);


  // convert input datatypes to QuantLib datatypes
  QuantLib::Natural FixingDaysLib = ObjectHandler::convert2<long>(
      mFixingDays, "FixingDays", QuantLib::Null<QuantLib::Natural>());


  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::Currency CurrencyEnum =
      ObjectHandler::Create<QuantLib::Currency>()(mCurrency);


  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::Calendar CalendarEnum =
      ObjectHandler::Create<QuantLib::Calendar>()(mCalendar);


  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::BusinessDayConvention BDayConventionEnum =
      ObjectHandler::Create<QuantLib::BusinessDayConvention>()(mBDayConvention);


  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::DayCounter DayCounterEnum =
      ObjectHandler::Create<QuantLib::DayCounter>()(mDayCounter);


  // convert object IDs into library objects
  QuantLib::Handle<QuantLib::Quote> GearingLibObj =
      ObjectHandler::convert2< QuantLib::Handle<QuantLib::Quote> >(mGearing, "Gearing");


  // convert object IDs into library objects
  OH_GET_REFERENCE(IborIndexLibObjPtr, mIborIndex,
      QuantLibAddin::IborIndex, QuantLib::IborIndex)


  // convert object IDs into library objects
  QuantLib::Handle<QuantLib::Quote> SpreadLibObj =
      ObjectHandler::convert2< QuantLib::Handle<QuantLib::Quote> >(mSpread, "Spread");

 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlProxyIbor(
          mObjectID,
          mFamilyName,
          mTenor,
          mFixingDays,
          mCurrency,
          mCalendar,
          mBDayConvention,
          mEndOfMonth,
          mDayCounter,
          mGearing,
          mIborIndex,
          mSpread,
          false
      ));

    // Construct the Object
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::ProxyIbor(
          valueObject,
          mFamilyName,
          TenorLib,
          FixingDaysLib,
          CurrencyEnum,
          CalendarEnum,
          BDayConventionEnum,
          mEndOfMonth,
          DayCounterEnum,
          GearingLibObj,
          IborIndexLibObjPtr,
          SpreadLibObj,
          false
      ));

    // Store the Object in the Repository
    mReturnValue = ObjectHandler::Repository::instance().storeObject(mObjectID, object, false, valueObject);
    
   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::ProxyIbor) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsString()) {
      return Nan::ThrowError("FamilyName is required.");
  }
  if (info.Length() == 2 || !info[2]->IsString()) {
      return Nan::ThrowError("Tenor is required.");
  }
  if (info.Length() == 4 || !info[4]->IsString()) {
      return Nan::ThrowError("Currency is required.");
  }
  if (info.Length() == 5 || !info[5]->IsString()) {
      return Nan::ThrowError("Calendar is required.");
  }
  if (info.Length() == 6 || !info[6]->IsString()) {
      return Nan::ThrowError("BDayConvention is required.");
  }
  if (info.Length() == 7 || !info[7]->IsBoolean()) {
      return Nan::ThrowError("EndOfMonth is required.");
  }
  if (info.Length() == 8 || !info[8]->IsString()) {
      return Nan::ThrowError("DayCounter is required.");
  }
  if (info.Length() == 10 || !info[10]->IsString()) {
      return Nan::ThrowError("IborIndex is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  String::Utf8Value strFamilyName(info[1]->ToString());
  string FamilyNameCpp(strdup(*strFamilyName));

  // convert js argument to c++ type
  String::Utf8Value strTenor(info[2]->ToString());
  string TenorCpp(strdup(*strTenor));

  // convert js argument to c++ type
  ObjectHandler::property_t FixingDaysCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[3]).FromJust()));

  // convert js argument to c++ type
  String::Utf8Value strCurrency(info[4]->ToString());
  string CurrencyCpp(strdup(*strCurrency));

  // convert js argument to c++ type
  String::Utf8Value strCalendar(info[5]->ToString());
  string CalendarCpp(strdup(*strCalendar));

  // convert js argument to c++ type
  String::Utf8Value strBDayConvention(info[6]->ToString());
  string BDayConventionCpp(strdup(*strBDayConvention));

  // convert js argument to c++ type
  bool EndOfMonthCpp = Nan::To<bool>(info[7]).FromJust();

  // convert js argument to c++ type
  String::Utf8Value strDayCounter(info[8]->ToString());
  string DayCounterCpp(strdup(*strDayCounter));

  // convert js argument to c++ type
  ObjectHandler::property_t GearingCpp =
      ObjectHandler::property_t(static_cast<double>(Nan::To<double>(info[9]).FromJust()));

  // convert js argument to c++ type
  String::Utf8Value strIborIndex(info[10]->ToString());
  string IborIndexCpp(strdup(*strIborIndex));

  // convert js argument to c++ type
  ObjectHandler::property_t SpreadCpp =
      ObjectHandler::property_t(static_cast<double>(Nan::To<double>(info[11]).FromJust()));

 
  // launch worker
  ProxyIborWorker* worker = new ProxyIborWorker(
    ObjectIDCpp
,     FamilyNameCpp
,     TenorCpp
,     FixingDaysCpp
,     CurrencyCpp
,     CalendarCpp
,     BDayConventionCpp
,     EndOfMonthCpp
,     DayCounterCpp
,     GearingCpp
,     IborIndexCpp
,     SpreadCpp
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

void IndexNameWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::Index, QuantLib::Index)


  // invoke the member function
  mReturnValue = ObjectIDLibObjPtr->name(
      );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::IndexName) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  IndexNameWorker* worker = new IndexNameWorker(
    ObjectIDCpp
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

void IndexFixingCalendarWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::Index, QuantLib::Index)


  // invoke the member function
  QuantLib::Calendar returnValue = ObjectIDLibObjPtr->fixingCalendar(
      );


  std::ostringstream os;
  os << returnValue;
  mReturnValue = os.str();

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::IndexFixingCalendar) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  IndexFixingCalendarWorker* worker = new IndexFixingCalendarWorker(
    ObjectIDCpp
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

void IndexIsValidFixingDateWorker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes
  std::vector<QuantLib::Date> FixingDateLib = ObjectHandler::vector::convert2<QuantLib::Date>(
      mFixingDate, "FixingDate");

       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::Index, QuantLib::Index)


  // loop on the input parameter and populate the return vector
  QuantLibAddin::qlIndexIsValidFixingDateBind bindObject =
      boost::bind((QuantLibAddin::qlIndexIsValidFixingDateSignature)
              &QuantLib::Index::isValidFixingDate,
              ObjectIDLibObjPtr
          ,_1
          );

  ObjectHandler::loop
      <QuantLibAddin::qlIndexIsValidFixingDateBind,
                      QuantLib::Date,
                      bool>
          (bindObject,
            FixingDateLib,
          mReturnValue
          );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::IndexIsValidFixingDate) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsArray()) {
      return Nan::ThrowError("FixingDate is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  std::vector<ObjectHandler::property_t>FixingDateCpp;

  Local<Array> FixingDateArray = info[1].As<Array>();
  for (unsigned int i = 0; i < FixingDateArray->Length(); i++){
    ObjectHandler::property_t tmp =
        ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(Nan::Get(FixingDateArray, i).ToLocalChecked()).FromJust()));
    FixingDateCpp.push_back(tmp);
  }

 
  // launch worker
  IndexIsValidFixingDateWorker* worker = new IndexIsValidFixingDateWorker(
    ObjectIDCpp
,     FixingDateCpp
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

void IndexFixingWorker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes
  std::vector<QuantLib::Date> FixingDateLib = ObjectHandler::vector::convert2<QuantLib::Date>(
      mFixingDate, "FixingDate");

       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::Index, QuantLib::Index)

  std::vector<QuantLib::Real> returnValue;


  // loop on the input parameter and populate the return vector
  QuantLibAddin::qlIndexFixingBind bindObject =
      boost::bind((QuantLibAddin::qlIndexFixingSignature)
              &QuantLib::Index::fixing,
              ObjectIDLibObjPtr
          ,_1
          ,mForecastToday
          );

  ObjectHandler::loop
      <QuantLibAddin::qlIndexFixingBind,
                      QuantLib::Date,
                      QuantLib::Real>
          (bindObject,
            FixingDateLib,
          returnValue
          );


  mReturnValue = QuantLibAddin::libraryToVector(returnValue);

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::IndexFixing) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsArray()) {
      return Nan::ThrowError("FixingDate is required.");
  }
  if (info.Length() == 2 || !info[2]->IsBoolean()) {
      return Nan::ThrowError("ForecastToday is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  std::vector<ObjectHandler::property_t>FixingDateCpp;

  Local<Array> FixingDateArray = info[1].As<Array>();
  for (unsigned int i = 0; i < FixingDateArray->Length(); i++){
    ObjectHandler::property_t tmp =
        ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(Nan::Get(FixingDateArray, i).ToLocalChecked()).FromJust()));
    FixingDateCpp.push_back(tmp);
  }

  // convert js argument to c++ type
  bool ForecastTodayCpp = Nan::To<bool>(info[2]).FromJust();

 
  // launch worker
  IndexFixingWorker* worker = new IndexFixingWorker(
    ObjectIDCpp
,     FixingDateCpp
,     ForecastTodayCpp
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

void IndexAddFixingsWorker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes
  std::vector<QuantLib::Date> FixingDatesLib = ObjectHandler::vector::convert2<QuantLib::Date>(
      mFixingDates, "FixingDates");


  // convert input datatypes to QuantLib datatypes
  std::vector<QuantLib::Real> FixingValuesLib =
      QuantLibAddin::convertVector<double, QuantLib::Real>(mFixingValues);

       // convert object IDs into library objects
  OH_GET_OBJECT(ObjectIDObjPtr, mObjectID, QuantLibAddin::Index)


  // invoke the member function
  ObjectIDObjPtr->addFixings(
        FixingDatesLib
        ,
         mFixingValues
        ,
         mForceOverwrite
       );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::IndexAddFixings) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsArray()) {
      return Nan::ThrowError("FixingDates is required.");
  }
  if (info.Length() == 2 || !info[2]->IsArray()) {
      return Nan::ThrowError("FixingValues is required.");
  }
  if (info.Length() == 3 || !info[3]->IsBoolean()) {
      return Nan::ThrowError("ForceOverwrite is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  std::vector<ObjectHandler::property_t>FixingDatesCpp;

  Local<Array> FixingDatesArray = info[1].As<Array>();
  for (unsigned int i = 0; i < FixingDatesArray->Length(); i++){
    ObjectHandler::property_t tmp =
        ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(Nan::Get(FixingDatesArray, i).ToLocalChecked()).FromJust()));
    FixingDatesCpp.push_back(tmp);
  }

  // convert js argument to c++ type
  std::vector<double>FixingValuesCpp;

  Local<Array> FixingValuesArray = info[2].As<Array>();
  for (unsigned int i = 0; i < FixingValuesArray->Length(); i++){
    FixingValuesCpp.push_back(Nan::To<double>(Nan::Get(FixingValuesArray, i).ToLocalChecked()).FromJust());
  }

  // convert js argument to c++ type
  bool ForceOverwriteCpp = Nan::To<bool>(info[3]).FromJust();

 
  // launch worker
  IndexAddFixingsWorker* worker = new IndexAddFixingsWorker(
    ObjectIDCpp
,     FixingDatesCpp
,     FixingValuesCpp
,     ForceOverwriteCpp
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

void IndexAddFixings2Worker::Execute(){

  try{

  // convert object IDs into library objects
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::Index, QuantLib::Index)

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::IndexAddFixings2) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsArray()) {
      return Nan::ThrowError("TimeSeriesID is required.");
  }
  if (info.Length() == 2 || !info[2]->IsBoolean()) {
      return Nan::ThrowError("ForceOverwrite is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  std::vector<string>TimeSeriesIDCpp;

  Local<Array> TimeSeriesIDArray = info[1].As<Array>();
  for (unsigned int i = 0; i < TimeSeriesIDArray->Length(); i++){
    String::Utf8Value strTimeSeriesID(Nan::Get(TimeSeriesIDArray, i).ToLocalChecked()->ToString());
    TimeSeriesIDCpp.push_back(strdup(*strTimeSeriesID));
  }

  // convert js argument to c++ type
  bool ForceOverwriteCpp = Nan::To<bool>(info[2]).FromJust();

 
  // launch worker
  IndexAddFixings2Worker* worker = new IndexAddFixings2Worker(
    ObjectIDCpp
,     TimeSeriesIDCpp
,     ForceOverwriteCpp
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

void IndexClearFixingsWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::Index, QuantLib::Index)


  // invoke the member function
  ObjectIDLibObjPtr->clearFixings(
      );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::IndexClearFixings) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  IndexClearFixingsWorker* worker = new IndexClearFixingsWorker(
    ObjectIDCpp
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

void InterestRateIndexFamilyNameWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::InterestRateIndex, QuantLib::InterestRateIndex)


  // invoke the member function
  mReturnValue = ObjectIDLibObjPtr->familyName(
      );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::InterestRateIndexFamilyName) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  InterestRateIndexFamilyNameWorker* worker = new InterestRateIndexFamilyNameWorker(
    ObjectIDCpp
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

void InterestRateIndexTenorWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::InterestRateIndex, QuantLib::InterestRateIndex)


  // invoke the member function
  QuantLib::Period returnValue = ObjectIDLibObjPtr->tenor(
      );


  mReturnValue = QuantLibAddin::libraryToScalar(returnValue);

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::InterestRateIndexTenor) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  InterestRateIndexTenorWorker* worker = new InterestRateIndexTenorWorker(
    ObjectIDCpp
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

void InterestRateIndexFixingDaysWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::InterestRateIndex, QuantLib::InterestRateIndex)


  // invoke the member function
  QuantLib::Natural returnValue = ObjectIDLibObjPtr->fixingDays(
      );


  mReturnValue = QuantLibAddin::libraryToScalar(returnValue);

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::InterestRateIndexFixingDays) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  InterestRateIndexFixingDaysWorker* worker = new InterestRateIndexFixingDaysWorker(
    ObjectIDCpp
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

void InterestRateIndexCurrencyWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::InterestRateIndex, QuantLib::InterestRateIndex)


  // invoke the member function
  QuantLib::Currency returnValue = ObjectIDLibObjPtr->currency(
      );


  std::ostringstream os;
  os << returnValue;
  mReturnValue = os.str();

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::InterestRateIndexCurrency) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  InterestRateIndexCurrencyWorker* worker = new InterestRateIndexCurrencyWorker(
    ObjectIDCpp
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

void InterestRateIndexDayCounterWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::InterestRateIndex, QuantLib::InterestRateIndex)


  // invoke the member function
  QuantLib::DayCounter returnValue = ObjectIDLibObjPtr->dayCounter(
      );


  std::ostringstream os;
  os << returnValue;
  mReturnValue = os.str();

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::InterestRateIndexDayCounter) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  InterestRateIndexDayCounterWorker* worker = new InterestRateIndexDayCounterWorker(
    ObjectIDCpp
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

void InterestRateIndexValueDateWorker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes
  std::vector<QuantLib::Date> FixingDateLib = ObjectHandler::vector::convert2<QuantLib::Date>(
      mFixingDate, "FixingDate");

       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::InterestRateIndex, QuantLib::InterestRateIndex)

  std::vector<QuantLib::Date> returnValue;


  // loop on the input parameter and populate the return vector
  QuantLibAddin::qlInterestRateIndexValueDateBind bindObject =
      boost::bind((QuantLibAddin::qlInterestRateIndexValueDateSignature)
              &QuantLib::InterestRateIndex::valueDate,
              ObjectIDLibObjPtr
          ,_1
          );

  ObjectHandler::loop
      <QuantLibAddin::qlInterestRateIndexValueDateBind,
                      QuantLib::Date,
                      QuantLib::Date>
          (bindObject,
            FixingDateLib,
          returnValue
          );


  mReturnValue = QuantLibAddin::libraryToVector(returnValue);

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::InterestRateIndexValueDate) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsArray()) {
      return Nan::ThrowError("FixingDate is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  std::vector<ObjectHandler::property_t>FixingDateCpp;

  Local<Array> FixingDateArray = info[1].As<Array>();
  for (unsigned int i = 0; i < FixingDateArray->Length(); i++){
    ObjectHandler::property_t tmp =
        ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(Nan::Get(FixingDateArray, i).ToLocalChecked()).FromJust()));
    FixingDateCpp.push_back(tmp);
  }

 
  // launch worker
  InterestRateIndexValueDateWorker* worker = new InterestRateIndexValueDateWorker(
    ObjectIDCpp
,     FixingDateCpp
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

void InterestRateIndexFixingDateWorker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes
  std::vector<QuantLib::Date> ValueDateLib = ObjectHandler::vector::convert2<QuantLib::Date>(
      mValueDate, "ValueDate");

       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::InterestRateIndex, QuantLib::InterestRateIndex)

  std::vector<QuantLib::Date> returnValue;


  // loop on the input parameter and populate the return vector
  QuantLibAddin::qlInterestRateIndexFixingDateBind bindObject =
      boost::bind((QuantLibAddin::qlInterestRateIndexFixingDateSignature)
              &QuantLib::InterestRateIndex::fixingDate,
              ObjectIDLibObjPtr
          ,_1
          );

  ObjectHandler::loop
      <QuantLibAddin::qlInterestRateIndexFixingDateBind,
                      QuantLib::Date,
                      QuantLib::Date>
          (bindObject,
            ValueDateLib,
          returnValue
          );


  mReturnValue = QuantLibAddin::libraryToVector(returnValue);

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::InterestRateIndexFixingDate) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsArray()) {
      return Nan::ThrowError("ValueDate is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  std::vector<ObjectHandler::property_t>ValueDateCpp;

  Local<Array> ValueDateArray = info[1].As<Array>();
  for (unsigned int i = 0; i < ValueDateArray->Length(); i++){
    ObjectHandler::property_t tmp =
        ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(Nan::Get(ValueDateArray, i).ToLocalChecked()).FromJust()));
    ValueDateCpp.push_back(tmp);
  }

 
  // launch worker
  InterestRateIndexFixingDateWorker* worker = new InterestRateIndexFixingDateWorker(
    ObjectIDCpp
,     ValueDateCpp
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

void InterestRateIndexMaturityWorker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes
  std::vector<QuantLib::Date> ValueDateLib = ObjectHandler::vector::convert2<QuantLib::Date>(
      mValueDate, "ValueDate");

       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::InterestRateIndex, QuantLib::InterestRateIndex)

  std::vector<QuantLib::Date> returnValue;


  // loop on the input parameter and populate the return vector
  QuantLibAddin::qlInterestRateIndexMaturityBind bindObject =
      boost::bind((QuantLibAddin::qlInterestRateIndexMaturitySignature)
              &QuantLib::InterestRateIndex::maturityDate,
              ObjectIDLibObjPtr
          ,_1
          );

  ObjectHandler::loop
      <QuantLibAddin::qlInterestRateIndexMaturityBind,
                      QuantLib::Date,
                      QuantLib::Date>
          (bindObject,
            ValueDateLib,
          returnValue
          );


  mReturnValue = QuantLibAddin::libraryToVector(returnValue);

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::InterestRateIndexMaturity) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsArray()) {
      return Nan::ThrowError("ValueDate is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  std::vector<ObjectHandler::property_t>ValueDateCpp;

  Local<Array> ValueDateArray = info[1].As<Array>();
  for (unsigned int i = 0; i < ValueDateArray->Length(); i++){
    ObjectHandler::property_t tmp =
        ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(Nan::Get(ValueDateArray, i).ToLocalChecked()).FromJust()));
    ValueDateCpp.push_back(tmp);
  }

 
  // launch worker
  InterestRateIndexMaturityWorker* worker = new InterestRateIndexMaturityWorker(
    ObjectIDCpp
,     ValueDateCpp
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

void IborIndexBusinessDayConvWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::IborIndex, QuantLib::IborIndex)


  // invoke the member function
  QuantLib::BusinessDayConvention returnValue = ObjectIDLibObjPtr->businessDayConvention(
      );


  std::ostringstream os;
  os << returnValue;
  mReturnValue = os.str();

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::IborIndexBusinessDayConv) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  IborIndexBusinessDayConvWorker* worker = new IborIndexBusinessDayConvWorker(
    ObjectIDCpp
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

void IborIndexEndOfMonthWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::IborIndex, QuantLib::IborIndex)


  // invoke the member function
  mReturnValue = ObjectIDLibObjPtr->endOfMonth(
      );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::IborIndexEndOfMonth) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  IborIndexEndOfMonthWorker* worker = new IborIndexEndOfMonthWorker(
    ObjectIDCpp
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

void SwapIndexFixedLegTenorWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::SwapIndex, QuantLib::SwapIndex)


  // invoke the member function
  QuantLib::Period returnValue = ObjectIDLibObjPtr->fixedLegTenor(
      );


  mReturnValue = QuantLibAddin::libraryToScalar(returnValue);

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::SwapIndexFixedLegTenor) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  SwapIndexFixedLegTenorWorker* worker = new SwapIndexFixedLegTenorWorker(
    ObjectIDCpp
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

void SwapIndexFixedLegBDCWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::SwapIndex, QuantLib::SwapIndex)


  // invoke the member function
  QuantLib::BusinessDayConvention returnValue = ObjectIDLibObjPtr->fixedLegConvention(
      );


  std::ostringstream os;
  os << returnValue;
  mReturnValue = os.str();

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::SwapIndexFixedLegBDC) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  SwapIndexFixedLegBDCWorker* worker = new SwapIndexFixedLegBDCWorker(
    ObjectIDCpp
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
 