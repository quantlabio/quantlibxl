/* 
  Copyright (C) 2016 -2017 Jerry Jin
*/

#include <nan.h>
#include <string.h>

#include "overnightindexedswap.hpp"

#include <qlo/qladdindefines.hpp>
#include <qlo/overnightindexedswap.hpp>
#include <qlo/indexes/iborindex.hpp>
#include <qlo/schedule.hpp>
#include <qlo/ratehelpers.hpp>
#include <ql/indexes/iborindex.hpp>
#include <ql/termstructures/yield/oisratehelper.hpp>
 #include <oh/objecthandler.hpp>
#include <oh/conversions/getobjectvector.hpp>
#include <qlo/valueobjects/vo_all.hpp>
#include <qlo/conversions/all.hpp>
#include "../loop.hpp"


void OvernightIndexedSwapWorker::Execute(){

  try{

  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::OvernightIndexedSwap::Type PayerReceiverEnum =
      ObjectHandler::Create<QuantLib::OvernightIndexedSwap::Type>()(mPayerReceiver);


  // convert input datatypes to QuantLib datatypes
  std::vector<QuantLib::Real> NominalLib =
      QuantLibAddin::convertVector<double, QuantLib::Real>(mNominal);


  // convert object IDs into library objects
  OH_GET_REFERENCE(ScheduleLibObjPtr, mSchedule,
      QuantLibAddin::Schedule, QuantLib::Schedule)


  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::DayCounter FixDayCounterEnum =
      ObjectHandler::Create<QuantLib::DayCounter>()(mFixDayCounter);


  // convert object IDs into library objects
  OH_GET_REFERENCE(OvernightIndexLibObjPtr, mOvernightIndex,
      QuantLibAddin::OvernightIndex, QuantLib::OvernightIndex)

 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlOvernightIndexedSwap(
          mObjectID,
          mPayerReceiver,
          mNominal,
          mSchedule,
          mFixedRate,
          mFixDayCounter,
          mOvernightIndex,
          mSpread,
          false
      ));

    // Construct the Object
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::OvernightIndexedSwap(
          valueObject,
          PayerReceiverEnum,
          mNominal,
          ScheduleLibObjPtr,
          mFixedRate,
          FixDayCounterEnum,
          OvernightIndexLibObjPtr,
          mSpread,
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

NAN_METHOD(QuantLibXL::OvernightIndexedSwap) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsString()) {
      return Nan::ThrowError("PayerReceiver is required.");
  }
  if (info.Length() == 2 || !info[2]->IsArray()) {
      return Nan::ThrowError("Nominal is required.");
  }
  if (info.Length() == 3 || !info[3]->IsString()) {
      return Nan::ThrowError("Schedule is required.");
  }
  if (info.Length() == 4 || !info[4]->IsNumber()) {
      return Nan::ThrowError("FixedRate is required.");
  }
  if (info.Length() == 5 || !info[5]->IsString()) {
      return Nan::ThrowError("FixDayCounter is required.");
  }
  if (info.Length() == 6 || !info[6]->IsString()) {
      return Nan::ThrowError("OvernightIndex is required.");
  }
  if (info.Length() == 7 || !info[7]->IsNumber()) {
      return Nan::ThrowError("Spread is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  String::Utf8Value strPayerReceiver(info[1]->ToString());
  string PayerReceiverCpp(strdup(*strPayerReceiver));

  // convert js argument to c++ type
  std::vector<double>NominalCpp;

  Local<Array> NominalArray = info[2].As<Array>();
  for (unsigned int i = 0; i < NominalArray->Length(); i++){
    NominalCpp.push_back(Nan::To<double>(Nan::Get(NominalArray, i).ToLocalChecked()).FromJust());
  }

  // convert js argument to c++ type
  String::Utf8Value strSchedule(info[3]->ToString());
  string ScheduleCpp(strdup(*strSchedule));

  // convert js argument to c++ type
  double FixedRateCpp = Nan::To<double>(info[4]).FromJust();

  // convert js argument to c++ type
  String::Utf8Value strFixDayCounter(info[5]->ToString());
  string FixDayCounterCpp(strdup(*strFixDayCounter));

  // convert js argument to c++ type
  String::Utf8Value strOvernightIndex(info[6]->ToString());
  string OvernightIndexCpp(strdup(*strOvernightIndex));

  // convert js argument to c++ type
  double SpreadCpp = Nan::To<double>(info[7]).FromJust();

 
  // launch worker
  OvernightIndexedSwapWorker* worker = new OvernightIndexedSwapWorker(
    ObjectIDCpp
,     PayerReceiverCpp
,     NominalCpp
,     ScheduleCpp
,     FixedRateCpp
,     FixDayCounterCpp
,     OvernightIndexCpp
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

void MakeOISWorker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes
  QuantLib::Natural SettlDaysLib = ObjectHandler::convert2<long>(
      mSettlDays, "SettlDays", QuantLib::Null<QuantLib::Natural>());


  // convert input datatypes to QuantLib datatypes
  QuantLib::Period SwapTenorLib;
  QuantLibAddin::cppToLibrary(mSwapTenor, SwapTenorLib);


  // convert object IDs into library objects
  OH_GET_REFERENCE(OvernightIndexLibObjPtr, mOvernightIndex,
      QuantLibAddin::OvernightIndex, QuantLib::OvernightIndex)


  // convert input datatypes to QuantLib datatypes
  QuantLib::Period ForwardStartLib;
  QuantLibAddin::cppToLibrary(mForwardStart, ForwardStartLib);


  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::DayCounter FixDayCounterEnum =
      ObjectHandler::Create<QuantLib::DayCounter>()(mFixDayCounter);

 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlMakeOIS(
          mObjectID,
          mSettlDays,
          mSwapTenor,
          mOvernightIndex,
          mFixedRate,
          mForwardStart,
          mFixDayCounter,
          mSpread,
          false
      ));

    // Construct the Object
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::OvernightIndexedSwap(
          valueObject,
          SettlDaysLib,
          SwapTenorLib,
          OvernightIndexLibObjPtr,
          mFixedRate,
          ForwardStartLib,
          FixDayCounterEnum,
          mSpread,
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

NAN_METHOD(QuantLibXL::MakeOIS) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 2 || !info[2]->IsString()) {
      return Nan::ThrowError("SwapTenor is required.");
  }
  if (info.Length() == 3 || !info[3]->IsString()) {
      return Nan::ThrowError("OvernightIndex is required.");
  }
  if (info.Length() == 4 || !info[4]->IsNumber()) {
      return Nan::ThrowError("FixedRate is required.");
  }
  if (info.Length() == 5 || !info[5]->IsString()) {
      return Nan::ThrowError("ForwardStart is required.");
  }
  if (info.Length() == 6 || !info[6]->IsString()) {
      return Nan::ThrowError("FixDayCounter is required.");
  }
  if (info.Length() == 7 || !info[7]->IsNumber()) {
      return Nan::ThrowError("Spread is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  ObjectHandler::property_t SettlDaysCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[1]).FromJust()));

  // convert js argument to c++ type
  String::Utf8Value strSwapTenor(info[2]->ToString());
  string SwapTenorCpp(strdup(*strSwapTenor));

  // convert js argument to c++ type
  String::Utf8Value strOvernightIndex(info[3]->ToString());
  string OvernightIndexCpp(strdup(*strOvernightIndex));

  // convert js argument to c++ type
  double FixedRateCpp = Nan::To<double>(info[4]).FromJust();

  // convert js argument to c++ type
  String::Utf8Value strForwardStart(info[5]->ToString());
  string ForwardStartCpp(strdup(*strForwardStart));

  // convert js argument to c++ type
  String::Utf8Value strFixDayCounter(info[6]->ToString());
  string FixDayCounterCpp(strdup(*strFixDayCounter));

  // convert js argument to c++ type
  double SpreadCpp = Nan::To<double>(info[7]).FromJust();

 
  // launch worker
  MakeOISWorker* worker = new MakeOISWorker(
    ObjectIDCpp
,     SettlDaysCpp
,     SwapTenorCpp
,     OvernightIndexCpp
,     FixedRateCpp
,     ForwardStartCpp
,     FixDayCounterCpp
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

void MakeDatedOISWorker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes
  QuantLib::Date StartDateLib = ObjectHandler::convert2<QuantLib::Date>(
      mStartDate, "StartDate");


  // convert input datatypes to QuantLib datatypes
  QuantLib::Date EndDateLib = ObjectHandler::convert2<QuantLib::Date>(
      mEndDate, "EndDate");


  // convert object IDs into library objects
  OH_GET_REFERENCE(OvernightIndexLibObjPtr, mOvernightIndex,
      QuantLibAddin::OvernightIndex, QuantLib::OvernightIndex)


  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::DayCounter FixDayCounterEnum =
      ObjectHandler::Create<QuantLib::DayCounter>()(mFixDayCounter);

 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlMakeDatedOIS(
          mObjectID,
          mStartDate,
          mEndDate,
          mOvernightIndex,
          mFixedRate,
          mFixDayCounter,
          mSpread,
          false
      ));

    // Construct the Object
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::OvernightIndexedSwap(
          valueObject,
          StartDateLib,
          EndDateLib,
          OvernightIndexLibObjPtr,
          mFixedRate,
          FixDayCounterEnum,
          mSpread,
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

NAN_METHOD(QuantLibXL::MakeDatedOIS) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 3 || !info[3]->IsString()) {
      return Nan::ThrowError("OvernightIndex is required.");
  }
  if (info.Length() == 4 || !info[4]->IsNumber()) {
      return Nan::ThrowError("FixedRate is required.");
  }
  if (info.Length() == 5 || !info[5]->IsString()) {
      return Nan::ThrowError("FixDayCounter is required.");
  }
  if (info.Length() == 6 || !info[6]->IsNumber()) {
      return Nan::ThrowError("Spread is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  ObjectHandler::property_t StartDateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[1]).FromJust()));

  // convert js argument to c++ type
  ObjectHandler::property_t EndDateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[2]).FromJust()));

  // convert js argument to c++ type
  String::Utf8Value strOvernightIndex(info[3]->ToString());
  string OvernightIndexCpp(strdup(*strOvernightIndex));

  // convert js argument to c++ type
  double FixedRateCpp = Nan::To<double>(info[4]).FromJust();

  // convert js argument to c++ type
  String::Utf8Value strFixDayCounter(info[5]->ToString());
  string FixDayCounterCpp(strdup(*strFixDayCounter));

  // convert js argument to c++ type
  double SpreadCpp = Nan::To<double>(info[6]).FromJust();

 
  // launch worker
  MakeDatedOISWorker* worker = new MakeDatedOISWorker(
    ObjectIDCpp
,     StartDateCpp
,     EndDateCpp
,     OvernightIndexCpp
,     FixedRateCpp
,     FixDayCounterCpp
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

void OvernightIndexedSwapFromOISRateHelperWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_REFERENCE(OISRateHelperLibObjPtr, mOISRateHelper,
      QuantLibAddin::OISRateHelper, QuantLib::OISRateHelper)

 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlOvernightIndexedSwapFromOISRateHelper(
          mObjectID,
          mOISRateHelper,
          false
      ));

    // Construct the Object
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::OvernightIndexedSwap(
          valueObject,
          OISRateHelperLibObjPtr,
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

NAN_METHOD(QuantLibXL::OvernightIndexedSwapFromOISRateHelper) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsString()) {
      return Nan::ThrowError("OISRateHelper is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  String::Utf8Value strOISRateHelper(info[1]->ToString());
  string OISRateHelperCpp(strdup(*strOISRateHelper));

 
  // launch worker
  OvernightIndexedSwapFromOISRateHelperWorker* worker = new OvernightIndexedSwapFromOISRateHelperWorker(
    ObjectIDCpp
,     OISRateHelperCpp
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

void OvernightIndexedSwapFixedLegBPSWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::OvernightIndexedSwap, QuantLib::OvernightIndexedSwap)


  // invoke the member function
  mReturnValue = ObjectIDLibObjPtr->fixedLegBPS(
      );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::OvernightIndexedSwapFixedLegBPS) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  OvernightIndexedSwapFixedLegBPSWorker* worker = new OvernightIndexedSwapFixedLegBPSWorker(
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

void OvernightIndexedSwapFixedLegNPVWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::OvernightIndexedSwap, QuantLib::OvernightIndexedSwap)


  // invoke the member function
  mReturnValue = ObjectIDLibObjPtr->fixedLegNPV(
      );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::OvernightIndexedSwapFixedLegNPV) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  OvernightIndexedSwapFixedLegNPVWorker* worker = new OvernightIndexedSwapFixedLegNPVWorker(
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

void OvernightIndexedSwapFairRateWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::OvernightIndexedSwap, QuantLib::OvernightIndexedSwap)


  // invoke the member function
  mReturnValue = ObjectIDLibObjPtr->fairRate(
      );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::OvernightIndexedSwapFairRate) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  OvernightIndexedSwapFairRateWorker* worker = new OvernightIndexedSwapFairRateWorker(
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

void OvernightIndexedSwapOvernightLegBPSWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::OvernightIndexedSwap, QuantLib::OvernightIndexedSwap)


  // invoke the member function
  mReturnValue = ObjectIDLibObjPtr->overnightLegBPS(
      );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::OvernightIndexedSwapOvernightLegBPS) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  OvernightIndexedSwapOvernightLegBPSWorker* worker = new OvernightIndexedSwapOvernightLegBPSWorker(
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

void OvernightIndexedSwapOvernightLegNPVWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::OvernightIndexedSwap, QuantLib::OvernightIndexedSwap)


  // invoke the member function
  mReturnValue = ObjectIDLibObjPtr->overnightLegNPV(
      );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::OvernightIndexedSwapOvernightLegNPV) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  OvernightIndexedSwapOvernightLegNPVWorker* worker = new OvernightIndexedSwapOvernightLegNPVWorker(
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

void OvernightIndexedSwapFairSpreadWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::OvernightIndexedSwap, QuantLib::OvernightIndexedSwap)


  // invoke the member function
  mReturnValue = ObjectIDLibObjPtr->fairSpread(
      );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::OvernightIndexedSwapFairSpread) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  OvernightIndexedSwapFairSpreadWorker* worker = new OvernightIndexedSwapFairSpreadWorker(
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

void OvernightIndexedSwapTypeWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::OvernightIndexedSwap, QuantLib::OvernightIndexedSwap)


  // invoke the member function
  QuantLib::OvernightIndexedSwap::Type returnValue = ObjectIDLibObjPtr->type(
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

NAN_METHOD(QuantLibXL::OvernightIndexedSwapType) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  OvernightIndexedSwapTypeWorker* worker = new OvernightIndexedSwapTypeWorker(
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

void OvernightIndexedSwapNominalWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::OvernightIndexedSwap, QuantLib::OvernightIndexedSwap)


  // invoke the member function
  mReturnValue = ObjectIDLibObjPtr->nominal(
      );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::OvernightIndexedSwapNominal) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  OvernightIndexedSwapNominalWorker* worker = new OvernightIndexedSwapNominalWorker(
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

void OvernightIndexedSwapFixedRateWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::OvernightIndexedSwap, QuantLib::OvernightIndexedSwap)


  // invoke the member function
  mReturnValue = ObjectIDLibObjPtr->fixedRate(
      );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::OvernightIndexedSwapFixedRate) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  OvernightIndexedSwapFixedRateWorker* worker = new OvernightIndexedSwapFixedRateWorker(
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

void OvernightIndexedSwapFixedDayCountWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::OvernightIndexedSwap, QuantLib::OvernightIndexedSwap)


  // invoke the member function
  QuantLib::DayCounter returnValue = ObjectIDLibObjPtr->fixedDayCount(
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

NAN_METHOD(QuantLibXL::OvernightIndexedSwapFixedDayCount) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  OvernightIndexedSwapFixedDayCountWorker* worker = new OvernightIndexedSwapFixedDayCountWorker(
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

void OvernightIndexedSwapSpreadWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::OvernightIndexedSwap, QuantLib::OvernightIndexedSwap)


  // invoke the member function
  mReturnValue = ObjectIDLibObjPtr->spread(
      );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::OvernightIndexedSwapSpread) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  OvernightIndexedSwapSpreadWorker* worker = new OvernightIndexedSwapSpreadWorker(
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

void OvernightIndexedSwapFixedLegAnalysisWorker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes
  QuantLib::Date AfterDateLib = ObjectHandler::convert2<QuantLib::Date>(
      mAfterDate, "AfterDate");

       // convert object IDs into library objects
  OH_GET_OBJECT(ObjectIDObjPtr, mObjectID, QuantLibAddin::OvernightIndexedSwap)

  std::vector< std::vector<ObjectHandler::property_t> > returnValue;


  // invoke the member function
  returnValue = ObjectIDObjPtr->fixedLegAnalysis(
        AfterDateLib
       );


  mReturnValue = ObjectHandler::matrix::convert2<string>(returnValue,"returnValue");

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::OvernightIndexedSwapFixedLegAnalysis) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  ObjectHandler::property_t AfterDateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[1]).FromJust()));

 
  // launch worker
  OvernightIndexedSwapFixedLegAnalysisWorker* worker = new OvernightIndexedSwapFixedLegAnalysisWorker(
    ObjectIDCpp
,     AfterDateCpp
   );

  worker->Execute();

    Local<Array> tmpMatrix = Nan::New<Array>(worker->mReturnValue.size());
    for (unsigned int i = 0; i < worker->mReturnValue.size(); i++) {
      Local<Array> tmpArray = Nan::New<Array>(worker->mReturnValue[i].size());
      for (unsigned int j = 0; j < worker->mReturnValue[i].size(); j++) {
        Nan::Set(tmpArray,j,Nan::New<String>(worker->mReturnValue[i][j]).ToLocalChecked());
      }
      Nan::Set(tmpMatrix,i,tmpArray);
    }

  Local<v8::Value> argv[2] = {
		  Nan::New<String>(worker->mError).ToLocalChecked(),
      tmpMatrix
	};

  v8::Local<v8::Array> results = Nan::New<v8::Array>();
  Nan::Set(results, 0, argv[0]);
  Nan::Set(results, 1, argv[1]);
  info.GetReturnValue().Set(results);
}

void OvernightIndexedSwapOvernightLegAnalysisWorker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes
  QuantLib::Date AfterDateLib = ObjectHandler::convert2<QuantLib::Date>(
      mAfterDate, "AfterDate");

       // convert object IDs into library objects
  OH_GET_OBJECT(ObjectIDObjPtr, mObjectID, QuantLibAddin::OvernightIndexedSwap)

  std::vector< std::vector<ObjectHandler::property_t> > returnValue;


  // invoke the member function
  returnValue = ObjectIDObjPtr->overnightLegAnalysis(
        AfterDateLib
       );


  mReturnValue = ObjectHandler::matrix::convert2<string>(returnValue,"returnValue");

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::OvernightIndexedSwapOvernightLegAnalysis) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  ObjectHandler::property_t AfterDateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[1]).FromJust()));

 
  // launch worker
  OvernightIndexedSwapOvernightLegAnalysisWorker* worker = new OvernightIndexedSwapOvernightLegAnalysisWorker(
    ObjectIDCpp
,     AfterDateCpp
   );

  worker->Execute();

    Local<Array> tmpMatrix = Nan::New<Array>(worker->mReturnValue.size());
    for (unsigned int i = 0; i < worker->mReturnValue.size(); i++) {
      Local<Array> tmpArray = Nan::New<Array>(worker->mReturnValue[i].size());
      for (unsigned int j = 0; j < worker->mReturnValue[i].size(); j++) {
        Nan::Set(tmpArray,j,Nan::New<String>(worker->mReturnValue[i][j]).ToLocalChecked());
      }
      Nan::Set(tmpMatrix,i,tmpArray);
    }

  Local<v8::Value> argv[2] = {
		  Nan::New<String>(worker->mError).ToLocalChecked(),
      tmpMatrix
	};

  v8::Local<v8::Array> results = Nan::New<v8::Array>();
  Nan::Set(results, 0, argv[0]);
  Nan::Set(results, 1, argv[1]);
  info.GetReturnValue().Set(results);
}
 