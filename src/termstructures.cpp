/* 
  Copyright (C) 2016 -2017 Jerry Jin
*/

#include <nan.h>
#include <string.h>

#include "termstructures.hpp"

#include <qlo/qladdindefines.hpp>
#include <qlo/handleimpl.hpp>
#include <qlo/conversions/coercetermstructure.hpp>
#include <qlo/ratehelpers.hpp>
#include <qlo/loop/loop_termstructures.hpp>
 #include <oh/objecthandler.hpp>
#include <oh/conversions/getobjectvector.hpp>
#include <qlo/valueobjects/vo_all.hpp>
#include <qlo/conversions/all.hpp>
#include "../loop.hpp"


void RelinkableHandleYieldTermStructureWorker::Execute(){

  try{
 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlRelinkableHandleYieldTermStructure(
          mObjectID,
          mCurrentLink,
          false
      ));

    // Construct the Object
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::RelinkableHandleImpl<QuantLibAddin::YieldTermStructure, QuantLib::YieldTermStructure>(
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

NAN_METHOD(QuantLibXL::RelinkableHandleYieldTermStructure) {

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
  RelinkableHandleYieldTermStructureWorker* worker = new RelinkableHandleYieldTermStructureWorker(
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

void DiscountCurveWorker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes
  std::vector<QuantLib::Date> CurveDatesLib = ObjectHandler::vector::convert2<QuantLib::Date>(
      mCurveDates, "CurveDates");


  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::DayCounter DayCounterEnum =
      ObjectHandler::Create<QuantLib::DayCounter>()(mDayCounter);

 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlDiscountCurve(
          mObjectID,
          mCurveDates,
          mCurveDiscounts,
          mDayCounter,
          false
      ));

    // Construct the Object
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::DiscountCurve(
          valueObject,
          CurveDatesLib,
          mCurveDiscounts,
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

NAN_METHOD(QuantLibXL::DiscountCurve) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsArray()) {
      return Nan::ThrowError("CurveDates is required.");
  }
  if (info.Length() == 2 || !info[2]->IsArray()) {
      return Nan::ThrowError("CurveDiscounts is required.");
  }
  if (info.Length() == 3 || !info[3]->IsString()) {
      return Nan::ThrowError("DayCounter is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  std::vector<ObjectHandler::property_t>CurveDatesCpp;

  Local<Array> CurveDatesArray = info[1].As<Array>();
  for (unsigned int i = 0; i < CurveDatesArray->Length(); i++){
    ObjectHandler::property_t tmp =
        ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(Nan::Get(CurveDatesArray, i).ToLocalChecked()).FromJust()));
    CurveDatesCpp.push_back(tmp);
  }

  // convert js argument to c++ type
  std::vector<double>CurveDiscountsCpp;

  Local<Array> CurveDiscountsArray = info[2].As<Array>();
  for (unsigned int i = 0; i < CurveDiscountsArray->Length(); i++){
    CurveDiscountsCpp.push_back(Nan::To<double>(Nan::Get(CurveDiscountsArray, i).ToLocalChecked()).FromJust());
  }

  // convert js argument to c++ type
  String::Utf8Value strDayCounter(info[3]->ToString());
  string DayCounterCpp(strdup(*strDayCounter));

 
  // launch worker
  DiscountCurveWorker* worker = new DiscountCurveWorker(
    ObjectIDCpp
,     CurveDatesCpp
,     CurveDiscountsCpp
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

void ZeroCurveWorker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes
  std::vector<QuantLib::Date> CurveDatesLib = ObjectHandler::vector::convert2<QuantLib::Date>(
      mCurveDates, "CurveDates");


  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::DayCounter DayCounterEnum =
      ObjectHandler::Create<QuantLib::DayCounter>()(mDayCounter);

 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlZeroCurve(
          mObjectID,
          mCurveDates,
          mCurveYields,
          mDayCounter,
          false
      ));

    // Construct the Object
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::ZeroCurve(
          valueObject,
          CurveDatesLib,
          mCurveYields,
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

NAN_METHOD(QuantLibXL::ZeroCurve) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsArray()) {
      return Nan::ThrowError("CurveDates is required.");
  }
  if (info.Length() == 2 || !info[2]->IsArray()) {
      return Nan::ThrowError("CurveYields is required.");
  }
  if (info.Length() == 3 || !info[3]->IsString()) {
      return Nan::ThrowError("DayCounter is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  std::vector<ObjectHandler::property_t>CurveDatesCpp;

  Local<Array> CurveDatesArray = info[1].As<Array>();
  for (unsigned int i = 0; i < CurveDatesArray->Length(); i++){
    ObjectHandler::property_t tmp =
        ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(Nan::Get(CurveDatesArray, i).ToLocalChecked()).FromJust()));
    CurveDatesCpp.push_back(tmp);
  }

  // convert js argument to c++ type
  std::vector<double>CurveYieldsCpp;

  Local<Array> CurveYieldsArray = info[2].As<Array>();
  for (unsigned int i = 0; i < CurveYieldsArray->Length(); i++){
    CurveYieldsCpp.push_back(Nan::To<double>(Nan::Get(CurveYieldsArray, i).ToLocalChecked()).FromJust());
  }

  // convert js argument to c++ type
  String::Utf8Value strDayCounter(info[3]->ToString());
  string DayCounterCpp(strdup(*strDayCounter));

 
  // launch worker
  ZeroCurveWorker* worker = new ZeroCurveWorker(
    ObjectIDCpp
,     CurveDatesCpp
,     CurveYieldsCpp
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

void ForwardCurveWorker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes
  std::vector<QuantLib::Date> CurveDatesLib = ObjectHandler::vector::convert2<QuantLib::Date>(
      mCurveDates, "CurveDates");


  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::DayCounter DayCounterEnum =
      ObjectHandler::Create<QuantLib::DayCounter>()(mDayCounter);

 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlForwardCurve(
          mObjectID,
          mCurveDates,
          mForwardYields,
          mDayCounter,
          false
      ));

    // Construct the Object
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::ForwardCurve(
          valueObject,
          CurveDatesLib,
          mForwardYields,
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

NAN_METHOD(QuantLibXL::ForwardCurve) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsArray()) {
      return Nan::ThrowError("CurveDates is required.");
  }
  if (info.Length() == 2 || !info[2]->IsArray()) {
      return Nan::ThrowError("ForwardYields is required.");
  }
  if (info.Length() == 3 || !info[3]->IsString()) {
      return Nan::ThrowError("DayCounter is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  std::vector<ObjectHandler::property_t>CurveDatesCpp;

  Local<Array> CurveDatesArray = info[1].As<Array>();
  for (unsigned int i = 0; i < CurveDatesArray->Length(); i++){
    ObjectHandler::property_t tmp =
        ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(Nan::Get(CurveDatesArray, i).ToLocalChecked()).FromJust()));
    CurveDatesCpp.push_back(tmp);
  }

  // convert js argument to c++ type
  std::vector<double>ForwardYieldsCpp;

  Local<Array> ForwardYieldsArray = info[2].As<Array>();
  for (unsigned int i = 0; i < ForwardYieldsArray->Length(); i++){
    ForwardYieldsCpp.push_back(Nan::To<double>(Nan::Get(ForwardYieldsArray, i).ToLocalChecked()).FromJust());
  }

  // convert js argument to c++ type
  String::Utf8Value strDayCounter(info[3]->ToString());
  string DayCounterCpp(strdup(*strDayCounter));

 
  // launch worker
  ForwardCurveWorker* worker = new ForwardCurveWorker(
    ObjectIDCpp
,     CurveDatesCpp
,     ForwardYieldsCpp
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

void FlatForwardWorker::Execute(){

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


  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::Compounding CompoundingEnum =
      ObjectHandler::Create<QuantLib::Compounding>()(mCompounding);


  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::Frequency FrequencyEnum =
      ObjectHandler::Create<QuantLib::Frequency>()(mFrequency);

 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlFlatForward(
          mObjectID,
          mNDays,
          mCalendar,
          mRate,
          mDayCounter,
          mCompounding,
          mFrequency,
          false
      ));

    // Construct the Object
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::FlatForward(
          valueObject,
          NDaysLib,
          CalendarEnum,
          RateLibObj,
          DayCounterEnum,
          CompoundingEnum,
          FrequencyEnum,
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

NAN_METHOD(QuantLibXL::FlatForward) {

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
  if (info.Length() == 5 || !info[5]->IsString()) {
      return Nan::ThrowError("Compounding is required.");
  }
  if (info.Length() == 6 || !info[6]->IsString()) {
      return Nan::ThrowError("Frequency is required.");
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

  // convert js argument to c++ type
  String::Utf8Value strCompounding(info[5]->ToString());
  string CompoundingCpp(strdup(*strCompounding));

  // convert js argument to c++ type
  String::Utf8Value strFrequency(info[6]->ToString());
  string FrequencyCpp(strdup(*strFrequency));

 
  // launch worker
  FlatForwardWorker* worker = new FlatForwardWorker(
    ObjectIDCpp
,     NDaysCpp
,     CalendarCpp
,     RateCpp
,     DayCounterCpp
,     CompoundingCpp
,     FrequencyCpp
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

void ForwardSpreadedTermStructureWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_OBJECT(BaseYieldCurveCoerce, mBaseYieldCurve, ObjectHandler::Object)
  QuantLib::Handle<QuantLib::YieldTermStructure> BaseYieldCurveLibObj =
      QuantLibAddin::CoerceHandle<
          QuantLibAddin::YieldTermStructure,
          QuantLib::YieldTermStructure>()(
              BaseYieldCurveCoerce);


  // convert object IDs into library objects
  QuantLib::Handle<QuantLib::Quote> SpreadLibObj =
      ObjectHandler::convert2< QuantLib::Handle<QuantLib::Quote> >(mSpread, "Spread");

 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlForwardSpreadedTermStructure(
          mObjectID,
          mBaseYieldCurve,
          mSpread,
          false
      ));

    // Construct the Object
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::ForwardSpreadedTermStructure(
          valueObject,
          BaseYieldCurveLibObj,
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

NAN_METHOD(QuantLibXL::ForwardSpreadedTermStructure) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  ObjectHandler::property_t BaseYieldCurveCpp =
      ObjectHandler::property_t(static_cast<double>(Nan::To<double>(info[1]).FromJust()));

  // convert js argument to c++ type
  ObjectHandler::property_t SpreadCpp =
      ObjectHandler::property_t(static_cast<double>(Nan::To<double>(info[2]).FromJust()));

 
  // launch worker
  ForwardSpreadedTermStructureWorker* worker = new ForwardSpreadedTermStructureWorker(
    ObjectIDCpp
,     BaseYieldCurveCpp
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

void ImpliedTermStructureWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_OBJECT(BaseYieldCurveCoerce, mBaseYieldCurve, ObjectHandler::Object)
  QuantLib::Handle<QuantLib::YieldTermStructure> BaseYieldCurveLibObj =
      QuantLibAddin::CoerceHandle<
          QuantLibAddin::YieldTermStructure,
          QuantLib::YieldTermStructure>()(
              BaseYieldCurveCoerce);


  // convert input datatypes to QuantLib datatypes
  QuantLib::Date ReferenceDateLib = ObjectHandler::convert2<QuantLib::Date>(
      mReferenceDate, "ReferenceDate");

 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlImpliedTermStructure(
          mObjectID,
          mBaseYieldCurve,
          mReferenceDate,
          false
      ));

    // Construct the Object
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::ImpliedTermStructure(
          valueObject,
          BaseYieldCurveLibObj,
          ReferenceDateLib,
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

NAN_METHOD(QuantLibXL::ImpliedTermStructure) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  ObjectHandler::property_t BaseYieldCurveCpp =
      ObjectHandler::property_t(static_cast<double>(Nan::To<double>(info[1]).FromJust()));

  // convert js argument to c++ type
  ObjectHandler::property_t ReferenceDateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[2]).FromJust()));

 
  // launch worker
  ImpliedTermStructureWorker* worker = new ImpliedTermStructureWorker(
    ObjectIDCpp
,     BaseYieldCurveCpp
,     ReferenceDateCpp
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

void InterpolatedYieldCurveWorker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes
  std::vector<QuantLib::Date> DatesLib = ObjectHandler::vector::convert2<QuantLib::Date>(
      mDates, "Dates");


  // convert input datatypes to QuantLib datatypes
  std::vector<QuantLib::Real> DataLib =
      QuantLibAddin::convertVector<double, QuantLib::Real>(mData);


  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::Calendar CalendarEnum =
      ObjectHandler::Create<QuantLib::Calendar>()(mCalendar);


  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::DayCounter DayCounterEnum =
      ObjectHandler::Create<QuantLib::DayCounter>()(mDayCounter);


  // convert object IDs into library objects
  std::vector< QuantLib::Handle<QuantLib::Quote> > JumpsLibObj =
      ObjectHandler::vector::convert2< QuantLib::Handle<QuantLib::Quote> >(mJumps, "Jumps");


  // convert input datatypes to QuantLib datatypes
  std::vector<QuantLib::Date> JumpDatesLib = ObjectHandler::vector::convert2<QuantLib::Date>(
      mJumpDates, "JumpDates");


  // convert input datatypes to QuantLib datatypes
  QuantLib::Size NRateHelperLib;
  QuantLibAddin::cppToLibrary(mNRateHelper, NRateHelperLib);

 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlInterpolatedYieldCurve(
          mObjectID,
          mDates,
          mData,
          mCalendar,
          mDayCounter,
          mJumps,
          mJumpDates,
          mTraitsID,
          mInterpolatorID,
          mMixedInterpolationBehavior,
          mNRateHelper,
          false
      ));

    // Construct the Object
	std::map<std::string, QuantLib::MixedInterpolation::Behavior> strEnum;
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::InterpolatedYieldCurve(
          valueObject,
          DatesLib,
          mData,
          CalendarEnum,
          DayCounterEnum,
          JumpsLibObj,
          JumpDatesLib,
          mTraitsID,
          mInterpolatorID,
		  strEnum[mMixedInterpolationBehavior],
          NRateHelperLib,
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

NAN_METHOD(QuantLibXL::InterpolatedYieldCurve) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsArray()) {
      return Nan::ThrowError("Dates is required.");
  }
  if (info.Length() == 2 || !info[2]->IsArray()) {
      return Nan::ThrowError("Data is required.");
  }
  if (info.Length() == 3 || !info[3]->IsString()) {
      return Nan::ThrowError("Calendar is required.");
  }
  if (info.Length() == 4 || !info[4]->IsString()) {
      return Nan::ThrowError("DayCounter is required.");
  }
  if (info.Length() == 5 || !info[5]->IsArray()) {
      return Nan::ThrowError("Jumps is required.");
  }
  if (info.Length() == 6 || !info[6]->IsArray()) {
      return Nan::ThrowError("JumpDates is required.");
  }
  if (info.Length() == 7 || !info[7]->IsString()) {
      return Nan::ThrowError("TraitsID is required.");
  }
  if (info.Length() == 8 || !info[8]->IsString()) {
      return Nan::ThrowError("InterpolatorID is required.");
  }
  if (info.Length() == 9 || !info[9]->IsString()) {
      return Nan::ThrowError("MixedInterpolationBehavior is required.");
  }
  if (info.Length() == 10 || !info[10]->IsNumber()) {
      return Nan::ThrowError("NRateHelper is required.");
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
  std::vector<double>DataCpp;

  Local<Array> DataArray = info[2].As<Array>();
  for (unsigned int i = 0; i < DataArray->Length(); i++){
    DataCpp.push_back(Nan::To<double>(Nan::Get(DataArray, i).ToLocalChecked()).FromJust());
  }

  // convert js argument to c++ type
  String::Utf8Value strCalendar(info[3]->ToString());
  string CalendarCpp(strdup(*strCalendar));

  // convert js argument to c++ type
  String::Utf8Value strDayCounter(info[4]->ToString());
  string DayCounterCpp(strdup(*strDayCounter));

  // convert js argument to c++ type
  std::vector<ObjectHandler::property_t>JumpsCpp;

  Local<Array> JumpsArray = info[5].As<Array>();
  for (unsigned int i = 0; i < JumpsArray->Length(); i++){
    ObjectHandler::property_t tmp =
        ObjectHandler::property_t(static_cast<double>(Nan::To<double>(Nan::Get(JumpsArray, i).ToLocalChecked()).FromJust()));
    JumpsCpp.push_back(tmp);
  }

  // convert js argument to c++ type
  std::vector<ObjectHandler::property_t>JumpDatesCpp;

  Local<Array> JumpDatesArray = info[6].As<Array>();
  for (unsigned int i = 0; i < JumpDatesArray->Length(); i++){
    ObjectHandler::property_t tmp =
        ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(Nan::Get(JumpDatesArray, i).ToLocalChecked()).FromJust()));
    JumpDatesCpp.push_back(tmp);
  }

  // convert js argument to c++ type
  String::Utf8Value strTraitsID(info[7]->ToString());
  string TraitsIDCpp(strdup(*strTraitsID));

  // convert js argument to c++ type
  String::Utf8Value strInterpolatorID(info[8]->ToString());
  string InterpolatorIDCpp(strdup(*strInterpolatorID));

  // convert js argument to c++ type
  String::Utf8Value strMixedInterpolationBehavior(info[9]->ToString());
  string MixedInterpolationBehaviorCpp(strdup(*strMixedInterpolationBehavior));

  // convert js argument to c++ type
  long NRateHelperCpp = Nan::To<int32_t>(info[10]).FromJust();

 
  // launch worker
  InterpolatedYieldCurveWorker* worker = new InterpolatedYieldCurveWorker(
    ObjectIDCpp
,     DatesCpp
,     DataCpp
,     CalendarCpp
,     DayCounterCpp
,     JumpsCpp
,     JumpDatesCpp
,     TraitsIDCpp
,     InterpolatorIDCpp
,     MixedInterpolationBehaviorCpp
,     NRateHelperCpp
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

void TermStructureDayCounterWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_OBJECT(ObjectIDTemp, mObjectID, ObjectHandler::Object)
  boost::shared_ptr<QuantLib::TermStructure> ObjectIDLibObjPtr =
      QuantLibAddin::CoerceTermStructure<
          QuantLibAddin::TermStructure,
          QuantLib::TermStructure>()(
              ObjectIDTemp);

     
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

NAN_METHOD(QuantLibXL::TermStructureDayCounter) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  TermStructureDayCounterWorker* worker = new TermStructureDayCounterWorker(
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

void TermStructureMaxDateWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_OBJECT(ObjectIDTemp, mObjectID, ObjectHandler::Object)
  boost::shared_ptr<QuantLib::TermStructure> ObjectIDLibObjPtr =
      QuantLibAddin::CoerceTermStructure<
          QuantLibAddin::TermStructure,
          QuantLib::TermStructure>()(
              ObjectIDTemp);

     
  // invoke the member function
  QuantLib::Date returnValue = ObjectIDLibObjPtr->maxDate(
      );


  mReturnValue = QuantLibAddin::libraryToScalar(returnValue);

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::TermStructureMaxDate) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  TermStructureMaxDateWorker* worker = new TermStructureMaxDateWorker(
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

void TermStructureReferenceDateWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_OBJECT(ObjectIDTemp, mObjectID, ObjectHandler::Object)
  boost::shared_ptr<QuantLib::TermStructure> ObjectIDLibObjPtr =
      QuantLibAddin::CoerceTermStructure<
          QuantLibAddin::TermStructure,
          QuantLib::TermStructure>()(
              ObjectIDTemp);

     
  // invoke the member function
  QuantLib::Date returnValue = ObjectIDLibObjPtr->referenceDate(
      );


  mReturnValue = QuantLibAddin::libraryToScalar(returnValue);

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::TermStructureReferenceDate) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  TermStructureReferenceDateWorker* worker = new TermStructureReferenceDateWorker(
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

void TermStructureTimeFromReferenceWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_OBJECT(ObjectIDTemp, mObjectID, ObjectHandler::Object)
  boost::shared_ptr<QuantLib::TermStructure> ObjectIDLibObjPtr =
      QuantLibAddin::CoerceTermStructure<
          QuantLibAddin::TermStructure,
          QuantLib::TermStructure>()(
              ObjectIDTemp);


  // convert input datatypes to QuantLib datatypes
  std::vector<QuantLib::Date> DateLib = ObjectHandler::vector::convert2<QuantLib::Date>(
      mDate, "Date");

     
  // loop on the input parameter and populate the return vector
  QuantLibAddin::qlTermStructureTimeFromReferenceBind bindObject =
      boost::bind((QuantLibAddin::qlTermStructureTimeFromReferenceSignature)
              &QuantLib::TermStructure::timeFromReference,
              ObjectIDLibObjPtr
          ,_1
          );

  ObjectHandler::loop
      <QuantLibAddin::qlTermStructureTimeFromReferenceBind,
                      QuantLib::Date,
                      QuantLib::Time>
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

NAN_METHOD(QuantLibXL::TermStructureTimeFromReference) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsArray()) {
      return Nan::ThrowError("Date is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  std::vector<ObjectHandler::property_t>DateCpp;

  Local<Array> DateArray = info[1].As<Array>();
  for (unsigned int i = 0; i < DateArray->Length(); i++){
    ObjectHandler::property_t tmp =
        ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(Nan::Get(DateArray, i).ToLocalChecked()).FromJust()));
    DateCpp.push_back(tmp);
  }

 
  // launch worker
  TermStructureTimeFromReferenceWorker* worker = new TermStructureTimeFromReferenceWorker(
    ObjectIDCpp
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

void TermStructureCalendarWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_OBJECT(ObjectIDTemp, mObjectID, ObjectHandler::Object)
  boost::shared_ptr<QuantLib::TermStructure> ObjectIDLibObjPtr =
      QuantLibAddin::CoerceTermStructure<
          QuantLibAddin::TermStructure,
          QuantLib::TermStructure>()(
              ObjectIDTemp);

     
  // invoke the member function
  QuantLib::Calendar returnValue = ObjectIDLibObjPtr->calendar(
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

NAN_METHOD(QuantLibXL::TermStructureCalendar) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  TermStructureCalendarWorker* worker = new TermStructureCalendarWorker(
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

void TermStructureSettlementDaysWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_OBJECT(ObjectIDTemp, mObjectID, ObjectHandler::Object)
  boost::shared_ptr<QuantLib::TermStructure> ObjectIDLibObjPtr =
      QuantLibAddin::CoerceTermStructure<
          QuantLibAddin::TermStructure,
          QuantLib::TermStructure>()(
              ObjectIDTemp);

     
  // invoke the member function
  QuantLib::Natural returnValue = ObjectIDLibObjPtr->settlementDays(
      );


  mReturnValue = QuantLibAddin::libraryToScalar(returnValue);

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::TermStructureSettlementDays) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  TermStructureSettlementDaysWorker* worker = new TermStructureSettlementDaysWorker(
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

void YieldTSDiscountWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_OBJECT(ObjectIDTemp, mObjectID, ObjectHandler::Object)
  boost::shared_ptr<QuantLib::YieldTermStructure> ObjectIDLibObjPtr =
      QuantLibAddin::CoerceTermStructure<
          QuantLibAddin::YieldTermStructure,
          QuantLib::YieldTermStructure>()(
              ObjectIDTemp);


  // convert input datatypes to QuantLib datatypes
  std::vector<QuantLib::Date> DfDatesLib = ObjectHandler::vector::convert2<QuantLib::Date>(
      mDfDates, "DfDates");

     
  // loop on the input parameter and populate the return vector
  QuantLibAddin::qlYieldTSDiscountBind bindObject =
      boost::bind((QuantLibAddin::qlYieldTSDiscountSignature)
              &QuantLib::YieldTermStructure::discount,
              ObjectIDLibObjPtr
          ,_1
          ,mAllowExtrapolation
          );

  ObjectHandler::loop
      <QuantLibAddin::qlYieldTSDiscountBind,
                      QuantLib::Date,
                      QuantLib::DiscountFactor>
          (bindObject,
            DfDatesLib,
          mReturnValue
          );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::YieldTSDiscount) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsArray()) {
      return Nan::ThrowError("DfDates is required.");
  }
  if (info.Length() == 2 || !info[2]->IsBoolean()) {
      return Nan::ThrowError("AllowExtrapolation is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  std::vector<ObjectHandler::property_t>DfDatesCpp;

  Local<Array> DfDatesArray = info[1].As<Array>();
  for (unsigned int i = 0; i < DfDatesArray->Length(); i++){
    ObjectHandler::property_t tmp =
        ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(Nan::Get(DfDatesArray, i).ToLocalChecked()).FromJust()));
    DfDatesCpp.push_back(tmp);
  }

  // convert js argument to c++ type
  bool AllowExtrapolationCpp = Nan::To<bool>(info[2]).FromJust();

 
  // launch worker
  YieldTSDiscountWorker* worker = new YieldTSDiscountWorker(
    ObjectIDCpp
,     DfDatesCpp
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

void YieldTSForwardRateWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_OBJECT(ObjectIDTemp, mObjectID, ObjectHandler::Object)
  boost::shared_ptr<QuantLib::YieldTermStructure> ObjectIDLibObjPtr =
      QuantLibAddin::CoerceTermStructure<
          QuantLibAddin::YieldTermStructure,
          QuantLib::YieldTermStructure>()(
              ObjectIDTemp);


  // convert input datatypes to QuantLib datatypes
  QuantLib::Date D1Lib = ObjectHandler::convert2<QuantLib::Date>(
      mD1, "D1");


  // convert input datatypes to QuantLib datatypes
  std::vector<QuantLib::Date> D2Lib = ObjectHandler::vector::convert2<QuantLib::Date>(
      mD2, "D2");


  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::DayCounter ResultDayCounterEnum =
      ObjectHandler::Create<QuantLib::DayCounter>()(mResultDayCounter);


  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::Compounding CompoundingEnum =
      ObjectHandler::Create<QuantLib::Compounding>()(mCompounding);


  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::Frequency FrequencyEnum =
      ObjectHandler::Create<QuantLib::Frequency>()(mFrequency);

       std::vector<QuantLib::InterestRate> returnValue;


  // loop on the input parameter and populate the return vector
  QuantLibAddin::qlYieldTSForwardRateBind bindObject =
      boost::bind((QuantLibAddin::qlYieldTSForwardRateSignature)
              &QuantLib::YieldTermStructure::forwardRate,
              ObjectIDLibObjPtr
          ,D1Lib
          ,_1
          ,ResultDayCounterEnum
          ,CompoundingEnum
          ,FrequencyEnum
          ,mAllowExtrapolation
          );

  ObjectHandler::loop
      <QuantLibAddin::qlYieldTSForwardRateBind,
                      QuantLib::Date,
                      QuantLib::InterestRate>
          (bindObject,
            D2Lib,
          returnValue
          );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::YieldTSForwardRate) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 2 || !info[2]->IsArray()) {
      return Nan::ThrowError("D2 is required.");
  }
  if (info.Length() == 3 || !info[3]->IsString()) {
      return Nan::ThrowError("ResultDayCounter is required.");
  }
  if (info.Length() == 4 || !info[4]->IsString()) {
      return Nan::ThrowError("Compounding is required.");
  }
  if (info.Length() == 5 || !info[5]->IsString()) {
      return Nan::ThrowError("Frequency is required.");
  }
  if (info.Length() == 6 || !info[6]->IsBoolean()) {
      return Nan::ThrowError("AllowExtrapolation is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  ObjectHandler::property_t D1Cpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[1]).FromJust()));

  // convert js argument to c++ type
  std::vector<ObjectHandler::property_t>D2Cpp;

  Local<Array> D2Array = info[2].As<Array>();
  for (unsigned int i = 0; i < D2Array->Length(); i++){
    ObjectHandler::property_t tmp =
        ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(Nan::Get(D2Array, i).ToLocalChecked()).FromJust()));
    D2Cpp.push_back(tmp);
  }

  // convert js argument to c++ type
  String::Utf8Value strResultDayCounter(info[3]->ToString());
  string ResultDayCounterCpp(strdup(*strResultDayCounter));

  // convert js argument to c++ type
  String::Utf8Value strCompounding(info[4]->ToString());
  string CompoundingCpp(strdup(*strCompounding));

  // convert js argument to c++ type
  String::Utf8Value strFrequency(info[5]->ToString());
  string FrequencyCpp(strdup(*strFrequency));

  // convert js argument to c++ type
  bool AllowExtrapolationCpp = Nan::To<bool>(info[6]).FromJust();

 
  // launch worker
  YieldTSForwardRateWorker* worker = new YieldTSForwardRateWorker(
    ObjectIDCpp
,     D1Cpp
,     D2Cpp
,     ResultDayCounterCpp
,     CompoundingCpp
,     FrequencyCpp
,     AllowExtrapolationCpp
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

void YieldTSForwardRate2Worker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_OBJECT(ObjectIDTemp, mObjectID, ObjectHandler::Object)
  boost::shared_ptr<QuantLib::YieldTermStructure> ObjectIDLibObjPtr =
      QuantLibAddin::CoerceTermStructure<
          QuantLibAddin::YieldTermStructure,
          QuantLib::YieldTermStructure>()(
              ObjectIDTemp);


  // convert input datatypes to QuantLib datatypes
  std::vector<QuantLib::Date> DateLib = ObjectHandler::vector::convert2<QuantLib::Date>(
      mDate, "Date");


  // convert input datatypes to QuantLib datatypes
  QuantLib::Period PeriodLib;
  QuantLibAddin::cppToLibrary(mPeriod, PeriodLib);


  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::DayCounter ResultDayCounterEnum =
      ObjectHandler::Create<QuantLib::DayCounter>()(mResultDayCounter);


  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::Compounding CompoundingEnum =
      ObjectHandler::Create<QuantLib::Compounding>()(mCompounding);


  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::Frequency FrequencyEnum =
      ObjectHandler::Create<QuantLib::Frequency>()(mFrequency);

       std::vector<QuantLib::InterestRate> returnValue;


  // loop on the input parameter and populate the return vector
  QuantLibAddin::qlYieldTSForwardRate2Bind bindObject =
      boost::bind((QuantLibAddin::qlYieldTSForwardRate2Signature)
              &QuantLib::YieldTermStructure::forwardRate,
              ObjectIDLibObjPtr
          ,_1
          ,PeriodLib
          ,ResultDayCounterEnum
          ,CompoundingEnum
          ,FrequencyEnum
          ,mAllowExtrapolation
          );

  ObjectHandler::loop
      <QuantLibAddin::qlYieldTSForwardRate2Bind,
                      QuantLib::Date,
                      QuantLib::InterestRate>
          (bindObject,
            DateLib,
          returnValue
          );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::YieldTSForwardRate2) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsArray()) {
      return Nan::ThrowError("Date is required.");
  }
  if (info.Length() == 2 || !info[2]->IsString()) {
      return Nan::ThrowError("Period is required.");
  }
  if (info.Length() == 3 || !info[3]->IsString()) {
      return Nan::ThrowError("ResultDayCounter is required.");
  }
  if (info.Length() == 4 || !info[4]->IsString()) {
      return Nan::ThrowError("Compounding is required.");
  }
  if (info.Length() == 5 || !info[5]->IsString()) {
      return Nan::ThrowError("Frequency is required.");
  }
  if (info.Length() == 6 || !info[6]->IsBoolean()) {
      return Nan::ThrowError("AllowExtrapolation is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  std::vector<ObjectHandler::property_t>DateCpp;

  Local<Array> DateArray = info[1].As<Array>();
  for (unsigned int i = 0; i < DateArray->Length(); i++){
    ObjectHandler::property_t tmp =
        ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(Nan::Get(DateArray, i).ToLocalChecked()).FromJust()));
    DateCpp.push_back(tmp);
  }

  // convert js argument to c++ type
  String::Utf8Value strPeriod(info[2]->ToString());
  string PeriodCpp(strdup(*strPeriod));

  // convert js argument to c++ type
  String::Utf8Value strResultDayCounter(info[3]->ToString());
  string ResultDayCounterCpp(strdup(*strResultDayCounter));

  // convert js argument to c++ type
  String::Utf8Value strCompounding(info[4]->ToString());
  string CompoundingCpp(strdup(*strCompounding));

  // convert js argument to c++ type
  String::Utf8Value strFrequency(info[5]->ToString());
  string FrequencyCpp(strdup(*strFrequency));

  // convert js argument to c++ type
  bool AllowExtrapolationCpp = Nan::To<bool>(info[6]).FromJust();

 
  // launch worker
  YieldTSForwardRate2Worker* worker = new YieldTSForwardRate2Worker(
    ObjectIDCpp
,     DateCpp
,     PeriodCpp
,     ResultDayCounterCpp
,     CompoundingCpp
,     FrequencyCpp
,     AllowExtrapolationCpp
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

void YieldTSZeroRateWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_OBJECT(ObjectIDTemp, mObjectID, ObjectHandler::Object)
  boost::shared_ptr<QuantLib::YieldTermStructure> ObjectIDLibObjPtr =
      QuantLibAddin::CoerceTermStructure<
          QuantLibAddin::YieldTermStructure,
          QuantLib::YieldTermStructure>()(
              ObjectIDTemp);


  // convert input datatypes to QuantLib datatypes
  std::vector<QuantLib::Date> DatesLib = ObjectHandler::vector::convert2<QuantLib::Date>(
      mDates, "Dates");


  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::DayCounter ResultDayCounterEnum =
      ObjectHandler::Create<QuantLib::DayCounter>()(mResultDayCounter);


  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::Compounding CompoundingEnum =
      ObjectHandler::Create<QuantLib::Compounding>()(mCompounding);


  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::Frequency FrequencyEnum =
      ObjectHandler::Create<QuantLib::Frequency>()(mFrequency);

       std::vector<QuantLib::InterestRate> returnValue;


  // loop on the input parameter and populate the return vector
  QuantLibAddin::qlYieldTSZeroRateBind bindObject =
      boost::bind((QuantLibAddin::qlYieldTSZeroRateSignature)
              &QuantLib::YieldTermStructure::zeroRate,
              ObjectIDLibObjPtr
          ,_1
          ,ResultDayCounterEnum
          ,CompoundingEnum
          ,FrequencyEnum
          ,mAllowExtrapolation
          );

  ObjectHandler::loop
      <QuantLibAddin::qlYieldTSZeroRateBind,
                      QuantLib::Date,
                      QuantLib::InterestRate>
          (bindObject,
            DatesLib,
          returnValue
          );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::YieldTSZeroRate) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsArray()) {
      return Nan::ThrowError("Dates is required.");
  }
  if (info.Length() == 2 || !info[2]->IsString()) {
      return Nan::ThrowError("ResultDayCounter is required.");
  }
  if (info.Length() == 3 || !info[3]->IsString()) {
      return Nan::ThrowError("Compounding is required.");
  }
  if (info.Length() == 4 || !info[4]->IsString()) {
      return Nan::ThrowError("Frequency is required.");
  }
  if (info.Length() == 5 || !info[5]->IsBoolean()) {
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
  String::Utf8Value strResultDayCounter(info[2]->ToString());
  string ResultDayCounterCpp(strdup(*strResultDayCounter));

  // convert js argument to c++ type
  String::Utf8Value strCompounding(info[3]->ToString());
  string CompoundingCpp(strdup(*strCompounding));

  // convert js argument to c++ type
  String::Utf8Value strFrequency(info[4]->ToString());
  string FrequencyCpp(strdup(*strFrequency));

  // convert js argument to c++ type
  bool AllowExtrapolationCpp = Nan::To<bool>(info[5]).FromJust();

 
  // launch worker
  YieldTSZeroRateWorker* worker = new YieldTSZeroRateWorker(
    ObjectIDCpp
,     DatesCpp
,     ResultDayCounterCpp
,     CompoundingCpp
,     FrequencyCpp
,     AllowExtrapolationCpp
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

void InterpolatedYieldCurveTimesWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_OBJECT(ObjectIDObjPtr, mObjectID, QuantLibAddin::InterpolatedYieldCurve)

     
  // loop on the input parameter and populate the return vector
  mReturnValue = ObjectIDObjPtr->times(
      );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::InterpolatedYieldCurveTimes) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  InterpolatedYieldCurveTimesWorker* worker = new InterpolatedYieldCurveTimesWorker(
    ObjectIDCpp
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

void InterpolatedYieldCurveDatesWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_OBJECT(ObjectIDObjPtr, mObjectID, QuantLibAddin::InterpolatedYieldCurve)

     
  // loop on the input parameter and populate the return vector
  std::vector<QuantLib::Date> returnValue = ObjectIDObjPtr->dates(
      );


  mReturnValue = QuantLibAddin::libraryToVector(returnValue);

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::InterpolatedYieldCurveDates) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  InterpolatedYieldCurveDatesWorker* worker = new InterpolatedYieldCurveDatesWorker(
    ObjectIDCpp
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

void InterpolatedYieldCurveDataWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_OBJECT(ObjectIDObjPtr, mObjectID, QuantLibAddin::InterpolatedYieldCurve)

     
  // loop on the input parameter and populate the return vector
  std::vector<QuantLib::Real> returnValue = ObjectIDObjPtr->data(
      );


  mReturnValue = QuantLibAddin::libraryToVector(returnValue);

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::InterpolatedYieldCurveData) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  InterpolatedYieldCurveDataWorker* worker = new InterpolatedYieldCurveDataWorker(
    ObjectIDCpp
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

void InterpolatedYieldCurveJumpTimesWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_OBJECT(ObjectIDObjPtr, mObjectID, QuantLibAddin::InterpolatedYieldCurve)

     
  // loop on the input parameter and populate the return vector
  mReturnValue = ObjectIDObjPtr->jumpTimes(
      );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::InterpolatedYieldCurveJumpTimes) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  InterpolatedYieldCurveJumpTimesWorker* worker = new InterpolatedYieldCurveJumpTimesWorker(
    ObjectIDCpp
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

void InterpolatedYieldCurveJumpDatesWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_OBJECT(ObjectIDObjPtr, mObjectID, QuantLibAddin::InterpolatedYieldCurve)

     
  // loop on the input parameter and populate the return vector
  std::vector<QuantLib::Date> returnValue = ObjectIDObjPtr->jumpDates(
      );


  mReturnValue = QuantLibAddin::libraryToVector(returnValue);

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::InterpolatedYieldCurveJumpDates) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  InterpolatedYieldCurveJumpDatesWorker* worker = new InterpolatedYieldCurveJumpDatesWorker(
    ObjectIDCpp
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
 