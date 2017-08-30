/* 
  Copyright (C) 2016 -2017 Jerry Jin
*/

#include <nan.h>
#include <string.h>

#include "defaulttermstructures.hpp"

#include <qlo/qladdindefines.hpp>
#include <qlo/handleimpl.hpp>
#include <qlo/conversions/coercetermstructure.hpp>
#include <qlo/loop/loop_defaulttermstructures.hpp>
 #include <oh/objecthandler.hpp>
#include <oh/conversions/getobjectvector.hpp>
#include <qlo/valueobjects/vo_all.hpp>
#include <qlo/conversions/all.hpp>
#include "../loop.hpp"


void RelinkableHandleDefaultProbabilityTermStructureWorker::Execute(){

  try{
 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlRelinkableHandleDefaultProbabilityTermStructure(
          mObjectID,
          mCurrentLink,
          false
      ));

    // Construct the Object
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::RelinkableHandleImpl<QuantLibAddin::DefaultProbabilityTermStructure, QuantLib::DefaultProbabilityTermStructure>(
          valueObject,
          mCurrentLink,
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

NAN_METHOD(QuantLibXL::RelinkableHandleDefaultProbabilityTermStructure) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsString()) {
      return Nan::ThrowError("CurrentLink is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  String::Utf8Value strCurrentLink(info[1]->ToString());
  string CurrentLinkCpp(strdup(*strCurrentLink));

 
  // launch worker
  RelinkableHandleDefaultProbabilityTermStructureWorker* worker = new RelinkableHandleDefaultProbabilityTermStructureWorker(
    ObjectIDCpp
,     CurrentLinkCpp
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

void FlatHazardRateWorker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes
  QuantLib::Size NDaysLib;
  QuantLibAddin::cppToLibrary(mNDays, NDaysLib);


  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::Calendar CalendarEnum =
      ObjectHandler::Create<QuantLib::Calendar>()(mCalendar);


  // convert object IDs into library objects
  QuantLib::Handle<QuantLib::Quote> RateLibObj =
      ObjectHandler::convert2< QuantLib::Handle<QuantLib::Quote> >(mRate, "Rate");


  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::DayCounter DayCounterEnum =
      ObjectHandler::Create<QuantLib::DayCounter>()(mDayCounter);

 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlFlatHazardRate(
          mObjectID,
          mNDays,
          mCalendar,
          mRate,
          mDayCounter,
          false
      ));

    // Construct the Object
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::FlatHazardRate(
          valueObject,
          NDaysLib,
          CalendarEnum,
          RateLibObj,
          DayCounterEnum,
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

NAN_METHOD(QuantLibXL::FlatHazardRate) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsNumber()) {
      return Nan::ThrowError("NDays is required.");
  }
  if (info.Length() == 2 || !info[2]->IsString()) {
      return Nan::ThrowError("Calendar is required.");
  }
  if (info.Length() == 4 || !info[4]->IsString()) {
      return Nan::ThrowError("DayCounter is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  long NDaysCpp = Nan::To<int32_t>(info[1]).FromJust();

  // convert js argument to c++ type
  String::Utf8Value strCalendar(info[2]->ToString());
  string CalendarCpp(strdup(*strCalendar));

  // convert js argument to c++ type
  ObjectHandler::property_t RateCpp =
      ObjectHandler::property_t(static_cast<double>(Nan::To<double>(info[3]).FromJust()));

  // convert js argument to c++ type
  String::Utf8Value strDayCounter(info[4]->ToString());
  string DayCounterCpp(strdup(*strDayCounter));

 
  // launch worker
  FlatHazardRateWorker* worker = new FlatHazardRateWorker(
    ObjectIDCpp
,     NDaysCpp
,     CalendarCpp
,     RateCpp
,     DayCounterCpp
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

void DefaultTSDefaultProbabilityWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_OBJECT(ObjectIDTemp, mObjectID, ObjectHandler::Object)
  boost::shared_ptr<QuantLib::DefaultProbabilityTermStructure> ObjectIDLibObjPtr =
      QuantLibAddin::CoerceTermStructure<
          QuantLibAddin::DefaultProbabilityTermStructure,
          QuantLib::DefaultProbabilityTermStructure>()(
              ObjectIDTemp);


  // convert input datatypes to QuantLib datatypes
  std::vector<QuantLib::Date> DatesLib = ObjectHandler::vector::convert2<QuantLib::Date>(
      mDates, "Dates");

     
  // loop on the input parameter and populate the return vector
  QuantLibAddin::qlDefaultTSDefaultProbabilityBind bindObject =
      boost::bind((QuantLibAddin::qlDefaultTSDefaultProbabilitySignature)
              &QuantLib::DefaultProbabilityTermStructure::defaultProbability,
              ObjectIDLibObjPtr
          ,_1
          ,mAllowExtrapolation
          );

  ObjectHandler::loop
      <QuantLibAddin::qlDefaultTSDefaultProbabilityBind,
                      QuantLib::Date,
                      QuantLib::Probability>
          (bindObject,
            DatesLib,
          mReturnValue
          );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::DefaultTSDefaultProbability) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsArray()) {
      return Nan::ThrowError("Dates is required.");
  }
  if (info.Length() == 2 || !info[2]->IsBoolean()) {
      return Nan::ThrowError("AllowExtrapolation is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  std::vector<ObjectHandler::property_t>DatesCpp;

  Local<Array> DatesArray = info[1].As<Array>();
  for (unsigned int i = 0; i < DatesArray->Length(); i++){
    ObjectHandler::property_t tmp =
        ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(Nan::Get(DatesArray, i).ToLocalChecked()).FromJust()));
    DatesCpp.push_back(tmp);
  }

  // convert js argument to c++ type
  bool AllowExtrapolationCpp = Nan::To<bool>(info[2]).FromJust();

 
  // launch worker
  DefaultTSDefaultProbabilityWorker* worker = new DefaultTSDefaultProbabilityWorker(
    ObjectIDCpp
,     DatesCpp
,     AllowExtrapolationCpp
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

void ProbabilityToHRWorker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes

  // convert input datatypes to QuantLib datatypes
  QuantLib::Date DateLib = ObjectHandler::convert2<QuantLib::Date>(
      mDate, "Date");


  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::DayCounter DayCounterEnum =
      ObjectHandler::Create<QuantLib::DayCounter>()(mDayCounter);

       // invoke the utility function
  QuantLib::Real returnValue = QuantLibAddin::probabilityToHazardRate(
      mProbability
      ,
       DateLib
      ,
       DayCounterEnum
     );

  mReturnValue = returnValue;

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::ProbabilityToHR) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsNumber()) {
      return Nan::ThrowError("Probability is required.");
  }
  if (info.Length() == 2 || !info[2]->IsString()) {
      return Nan::ThrowError("DayCounter is required.");
  }
  // convert js argument to c++ type
  double ProbabilityCpp = Nan::To<double>(info[0]).FromJust();

  // convert js argument to c++ type
  ObjectHandler::property_t DateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[1]).FromJust()));

  // convert js argument to c++ type
  String::Utf8Value strDayCounter(info[2]->ToString());
  string DayCounterCpp(strdup(*strDayCounter));

 
  // launch worker
  ProbabilityToHRWorker* worker = new ProbabilityToHRWorker(
    ProbabilityCpp
,     DateCpp
,     DayCounterCpp
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
 