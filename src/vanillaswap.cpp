/* 
  Copyright (C) 2016 -2017 Jerry Jin
*/

#include <nan.h>
#include <string.h>

#include "vanillaswap.hpp"

#include <qlo/qladdindefines.hpp>
#include <qlo/vanillaswap.hpp>
#include <qlo/indexes/iborindex.hpp>
#include <qlo/indexes/swapindex.hpp>
#include <qlo/ratehelpers.hpp>
#include <qlo/schedule.hpp>
#include <qlo/pricingengines.hpp>
#include <qlo/termstructures.hpp>
#include <ql/indexes/iborindex.hpp>
#include <ql/indexes/swapindex.hpp>
#include <ql/termstructures/yield/ratehelpers.hpp>
 #include <oh/objecthandler.hpp>
#include <oh/conversions/getobjectvector.hpp>
#include <qlo/valueobjects/vo_all.hpp>
#include <qlo/conversions/all.hpp>
#include "../loop.hpp"


void VanillaSwapWorker::Execute(){

  try{

  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::VanillaSwap::Type PayerReceiverEnum =
      ObjectHandler::Create<QuantLib::VanillaSwap::Type>()(mPayerReceiver);


  // convert object IDs into library objects
  OH_GET_REFERENCE(FixScheduleLibObjPtr, mFixSchedule,
      QuantLibAddin::Schedule, QuantLib::Schedule)


  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::DayCounter FixDayCounterEnum =
      ObjectHandler::Create<QuantLib::DayCounter>()(mFixDayCounter);


  // convert object IDs into library objects
  OH_GET_REFERENCE(FloatingLegScheduleLibObjPtr, mFloatingLegSchedule,
      QuantLibAddin::Schedule, QuantLib::Schedule)


  // convert object IDs into library objects
  OH_GET_REFERENCE(IborIndexLibObjPtr, mIborIndex,
      QuantLibAddin::IborIndex, QuantLib::IborIndex)


  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::DayCounter FloatingLegDayCounterEnum =
      ObjectHandler::Create<QuantLib::DayCounter>()(mFloatingLegDayCounter);


  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::BusinessDayConvention PaymentConventionEnum =
      ObjectHandler::Create<QuantLib::BusinessDayConvention>()(mPaymentConvention);

 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlVanillaSwap(
          mObjectID,
          mPayerReceiver,
          mNominal,
          mFixSchedule,
          mFixedRate,
          mFixDayCounter,
          mFloatingLegSchedule,
          mIborIndex,
          mSpread,
          mFloatingLegDayCounter,
          mPaymentConvention,
          false
      ));

    // Construct the Object
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::VanillaSwap(
          valueObject,
          PayerReceiverEnum,
          mNominal,
          FixScheduleLibObjPtr,
          mFixedRate,
          FixDayCounterEnum,
          FloatingLegScheduleLibObjPtr,
          IborIndexLibObjPtr,
          mSpread,
          FloatingLegDayCounterEnum,
          PaymentConventionEnum,
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

NAN_METHOD(QuantLibXL::VanillaSwap) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsString()) {
      return Nan::ThrowError("PayerReceiver is required.");
  }
  if (info.Length() == 2 || !info[2]->IsNumber()) {
      return Nan::ThrowError("Nominal is required.");
  }
  if (info.Length() == 3 || !info[3]->IsString()) {
      return Nan::ThrowError("FixSchedule is required.");
  }
  if (info.Length() == 4 || !info[4]->IsNumber()) {
      return Nan::ThrowError("FixedRate is required.");
  }
  if (info.Length() == 5 || !info[5]->IsString()) {
      return Nan::ThrowError("FixDayCounter is required.");
  }
  if (info.Length() == 6 || !info[6]->IsString()) {
      return Nan::ThrowError("FloatingLegSchedule is required.");
  }
  if (info.Length() == 7 || !info[7]->IsString()) {
      return Nan::ThrowError("IborIndex is required.");
  }
  if (info.Length() == 8 || !info[8]->IsNumber()) {
      return Nan::ThrowError("Spread is required.");
  }
  if (info.Length() == 9 || !info[9]->IsString()) {
      return Nan::ThrowError("FloatingLegDayCounter is required.");
  }
  if (info.Length() == 10 || !info[10]->IsString()) {
      return Nan::ThrowError("PaymentConvention is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  String::Utf8Value strPayerReceiver(info[1]->ToString());
  string PayerReceiverCpp(strdup(*strPayerReceiver));

  // convert js argument to c++ type
  double NominalCpp = Nan::To<double>(info[2]).FromJust();

  // convert js argument to c++ type
  String::Utf8Value strFixSchedule(info[3]->ToString());
  string FixScheduleCpp(strdup(*strFixSchedule));

  // convert js argument to c++ type
  double FixedRateCpp = Nan::To<double>(info[4]).FromJust();

  // convert js argument to c++ type
  String::Utf8Value strFixDayCounter(info[5]->ToString());
  string FixDayCounterCpp(strdup(*strFixDayCounter));

  // convert js argument to c++ type
  String::Utf8Value strFloatingLegSchedule(info[6]->ToString());
  string FloatingLegScheduleCpp(strdup(*strFloatingLegSchedule));

  // convert js argument to c++ type
  String::Utf8Value strIborIndex(info[7]->ToString());
  string IborIndexCpp(strdup(*strIborIndex));

  // convert js argument to c++ type
  double SpreadCpp = Nan::To<double>(info[8]).FromJust();

  // convert js argument to c++ type
  String::Utf8Value strFloatingLegDayCounter(info[9]->ToString());
  string FloatingLegDayCounterCpp(strdup(*strFloatingLegDayCounter));

  // convert js argument to c++ type
  String::Utf8Value strPaymentConvention(info[10]->ToString());
  string PaymentConventionCpp(strdup(*strPaymentConvention));

 
  // launch worker
  VanillaSwapWorker* worker = new VanillaSwapWorker(
    ObjectIDCpp
,     PayerReceiverCpp
,     NominalCpp
,     FixScheduleCpp
,     FixedRateCpp
,     FixDayCounterCpp
,     FloatingLegScheduleCpp
,     IborIndexCpp
,     SpreadCpp
,     FloatingLegDayCounterCpp
,     PaymentConventionCpp
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

void MakeVanillaSwapWorker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes
  QuantLib::Natural SettlDaysLib = ObjectHandler::convert2<long>(
      mSettlDays, "SettlDays", QuantLib::Null<QuantLib::Natural>());


  // convert input datatypes to QuantLib datatypes
  QuantLib::Period SwapTenorLib;
  QuantLibAddin::cppToLibrary(mSwapTenor, SwapTenorLib);


  // convert object IDs into library objects
  OH_GET_REFERENCE(IborIndexLibObjPtr, mIborIndex,
      QuantLibAddin::IborIndex, QuantLib::IborIndex)


  // convert input datatypes to QuantLib datatypes
  QuantLib::Period ForwardStartLib;
  QuantLibAddin::cppToLibrary(mForwardStart, ForwardStartLib);


  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::DayCounter FixDayCounterEnum =
      ObjectHandler::Create<QuantLib::DayCounter>()(mFixDayCounter);


  // convert object IDs into library objects
  OH_GET_REFERENCE(PricingEngineIDLibObjPtr, mPricingEngineID,
      QuantLibAddin::PricingEngine, QuantLib::PricingEngine)

 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlMakeVanillaSwap(
          mObjectID,
          mSettlDays,
          mSwapTenor,
          mIborIndex,
          mFixedRate,
          mForwardStart,
          mFixDayCounter,
          mSpread,
          mPricingEngineID,
          false
      ));

    // Construct the Object
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::VanillaSwap(
          valueObject,
          SettlDaysLib,
          SwapTenorLib,
          IborIndexLibObjPtr,
          mFixedRate,
          ForwardStartLib,
          FixDayCounterEnum,
          mSpread,
          PricingEngineIDLibObjPtr,
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

NAN_METHOD(QuantLibXL::MakeVanillaSwap) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 2 || !info[2]->IsString()) {
      return Nan::ThrowError("SwapTenor is required.");
  }
  if (info.Length() == 3 || !info[3]->IsString()) {
      return Nan::ThrowError("IborIndex is required.");
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
  if (info.Length() == 8 || !info[8]->IsString()) {
      return Nan::ThrowError("PricingEngineID is required.");
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
  String::Utf8Value strIborIndex(info[3]->ToString());
  string IborIndexCpp(strdup(*strIborIndex));

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

  // convert js argument to c++ type
  String::Utf8Value strPricingEngineID(info[8]->ToString());
  string PricingEngineIDCpp(strdup(*strPricingEngineID));

 
  // launch worker
  MakeVanillaSwapWorker* worker = new MakeVanillaSwapWorker(
    ObjectIDCpp
,     SettlDaysCpp
,     SwapTenorCpp
,     IborIndexCpp
,     FixedRateCpp
,     ForwardStartCpp
,     FixDayCounterCpp
,     SpreadCpp
,     PricingEngineIDCpp
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

void MakeIMMSwapWorker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes
  QuantLib::Period SwapTenorLib;
  QuantLibAddin::cppToLibrary(mSwapTenor, SwapTenorLib);


  // convert object IDs into library objects
  OH_GET_REFERENCE(IborIndexLibObjPtr, mIborIndex,
      QuantLibAddin::IborIndex, QuantLib::IborIndex)


  // convert input datatypes to QuantLib datatypes
  QuantLib::Date FirstImmDateLib = ObjectHandler::convert2<QuantLib::Date>(
      mFirstImmDate, "FirstImmDate");


  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::DayCounter FixDayCounterEnum =
      ObjectHandler::Create<QuantLib::DayCounter>()(mFixDayCounter);


  // convert object IDs into library objects
  OH_GET_REFERENCE(PricingEngineIDLibObjPtr, mPricingEngineID,
      QuantLibAddin::PricingEngine, QuantLib::PricingEngine)

 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlMakeIMMSwap(
          mObjectID,
          mSwapTenor,
          mIborIndex,
          mFixedRate,
          mFirstImmDate,
          mFixDayCounter,
          mSpread,
          mPricingEngineID,
          false
      ));

    // Construct the Object
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::VanillaSwap(
          valueObject,
          SwapTenorLib,
          IborIndexLibObjPtr,
          mFixedRate,
          FirstImmDateLib,
          FixDayCounterEnum,
          mSpread,
          PricingEngineIDLibObjPtr,
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

NAN_METHOD(QuantLibXL::MakeIMMSwap) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsString()) {
      return Nan::ThrowError("SwapTenor is required.");
  }
  if (info.Length() == 2 || !info[2]->IsString()) {
      return Nan::ThrowError("IborIndex is required.");
  }
  if (info.Length() == 3 || !info[3]->IsNumber()) {
      return Nan::ThrowError("FixedRate is required.");
  }
  if (info.Length() == 5 || !info[5]->IsString()) {
      return Nan::ThrowError("FixDayCounter is required.");
  }
  if (info.Length() == 6 || !info[6]->IsNumber()) {
      return Nan::ThrowError("Spread is required.");
  }
  if (info.Length() == 7 || !info[7]->IsString()) {
      return Nan::ThrowError("PricingEngineID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  String::Utf8Value strSwapTenor(info[1]->ToString());
  string SwapTenorCpp(strdup(*strSwapTenor));

  // convert js argument to c++ type
  String::Utf8Value strIborIndex(info[2]->ToString());
  string IborIndexCpp(strdup(*strIborIndex));

  // convert js argument to c++ type
  double FixedRateCpp = Nan::To<double>(info[3]).FromJust();

  // convert js argument to c++ type
  ObjectHandler::property_t FirstImmDateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[4]).FromJust()));

  // convert js argument to c++ type
  String::Utf8Value strFixDayCounter(info[5]->ToString());
  string FixDayCounterCpp(strdup(*strFixDayCounter));

  // convert js argument to c++ type
  double SpreadCpp = Nan::To<double>(info[6]).FromJust();

  // convert js argument to c++ type
  String::Utf8Value strPricingEngineID(info[7]->ToString());
  string PricingEngineIDCpp(strdup(*strPricingEngineID));

 
  // launch worker
  MakeIMMSwapWorker* worker = new MakeIMMSwapWorker(
    ObjectIDCpp
,     SwapTenorCpp
,     IborIndexCpp
,     FixedRateCpp
,     FirstImmDateCpp
,     FixDayCounterCpp
,     SpreadCpp
,     PricingEngineIDCpp
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

void VanillaSwapFromSwapIndexWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_REFERENCE(SwapIndexLibObjPtr, mSwapIndex,
      QuantLibAddin::SwapIndex, QuantLib::SwapIndex)


  // convert input datatypes to QuantLib datatypes
  QuantLib::Date FixingDateLib = ObjectHandler::convert2<QuantLib::Date>(
      mFixingDate, "FixingDate");

 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlVanillaSwapFromSwapIndex(
          mObjectID,
          mSwapIndex,
          mFixingDate,
          false
      ));

    // Construct the Object
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::VanillaSwap(
          valueObject,
          SwapIndexLibObjPtr,
          FixingDateLib,
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

NAN_METHOD(QuantLibXL::VanillaSwapFromSwapIndex) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsString()) {
      return Nan::ThrowError("SwapIndex is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  String::Utf8Value strSwapIndex(info[1]->ToString());
  string SwapIndexCpp(strdup(*strSwapIndex));

  // convert js argument to c++ type
  ObjectHandler::property_t FixingDateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[2]).FromJust()));

 
  // launch worker
  VanillaSwapFromSwapIndexWorker* worker = new VanillaSwapFromSwapIndexWorker(
    ObjectIDCpp
,     SwapIndexCpp
,     FixingDateCpp
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

void VanillaSwapFromSwapRateHelperWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_REFERENCE(SwapRateHelperLibObjPtr, mSwapRateHelper,
      QuantLibAddin::SwapRateHelper, QuantLib::SwapRateHelper)

 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlVanillaSwapFromSwapRateHelper(
          mObjectID,
          mSwapRateHelper,
          false
      ));

    // Construct the Object
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::VanillaSwap(
          valueObject,
          SwapRateHelperLibObjPtr,
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

NAN_METHOD(QuantLibXL::VanillaSwapFromSwapRateHelper) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsString()) {
      return Nan::ThrowError("SwapRateHelper is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  String::Utf8Value strSwapRateHelper(info[1]->ToString());
  string SwapRateHelperCpp(strdup(*strSwapRateHelper));

 
  // launch worker
  VanillaSwapFromSwapRateHelperWorker* worker = new VanillaSwapFromSwapRateHelperWorker(
    ObjectIDCpp
,     SwapRateHelperCpp
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

void VanillaSwapFixedLegBPSWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::VanillaSwap, QuantLib::VanillaSwap)


  // invoke the member function
  mReturnValue = ObjectIDLibObjPtr->fixedLegBPS(
      );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::VanillaSwapFixedLegBPS) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  VanillaSwapFixedLegBPSWorker* worker = new VanillaSwapFixedLegBPSWorker(
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

void VanillaSwapFixedLegNPVWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::VanillaSwap, QuantLib::VanillaSwap)


  // invoke the member function
  mReturnValue = ObjectIDLibObjPtr->fixedLegNPV(
      );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::VanillaSwapFixedLegNPV) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  VanillaSwapFixedLegNPVWorker* worker = new VanillaSwapFixedLegNPVWorker(
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

void VanillaSwapFairRateWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::VanillaSwap, QuantLib::VanillaSwap)


  // invoke the member function
  mReturnValue = ObjectIDLibObjPtr->fairRate(
      );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::VanillaSwapFairRate) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  VanillaSwapFairRateWorker* worker = new VanillaSwapFairRateWorker(
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

void VanillaSwapFloatingLegBPSWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::VanillaSwap, QuantLib::VanillaSwap)


  // invoke the member function
  mReturnValue = ObjectIDLibObjPtr->floatingLegBPS(
      );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::VanillaSwapFloatingLegBPS) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  VanillaSwapFloatingLegBPSWorker* worker = new VanillaSwapFloatingLegBPSWorker(
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

void VanillaSwapFloatingLegNPVWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::VanillaSwap, QuantLib::VanillaSwap)


  // invoke the member function
  mReturnValue = ObjectIDLibObjPtr->floatingLegNPV(
      );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::VanillaSwapFloatingLegNPV) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  VanillaSwapFloatingLegNPVWorker* worker = new VanillaSwapFloatingLegNPVWorker(
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

void VanillaSwapFairSpreadWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::VanillaSwap, QuantLib::VanillaSwap)


  // invoke the member function
  mReturnValue = ObjectIDLibObjPtr->fairSpread(
      );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::VanillaSwapFairSpread) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  VanillaSwapFairSpreadWorker* worker = new VanillaSwapFairSpreadWorker(
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

void VanillaSwapTypeWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::VanillaSwap, QuantLib::VanillaSwap)


  // invoke the member function
  QuantLib::VanillaSwap::Type returnValue = ObjectIDLibObjPtr->type(
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

NAN_METHOD(QuantLibXL::VanillaSwapType) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  VanillaSwapTypeWorker* worker = new VanillaSwapTypeWorker(
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

void VanillaSwapNominalWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::VanillaSwap, QuantLib::VanillaSwap)


  // invoke the member function
  mReturnValue = ObjectIDLibObjPtr->nominal(
      );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::VanillaSwapNominal) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  VanillaSwapNominalWorker* worker = new VanillaSwapNominalWorker(
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

void VanillaSwapFixedRateWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::VanillaSwap, QuantLib::VanillaSwap)


  // invoke the member function
  mReturnValue = ObjectIDLibObjPtr->fixedRate(
      );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::VanillaSwapFixedRate) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  VanillaSwapFixedRateWorker* worker = new VanillaSwapFixedRateWorker(
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

void VanillaSwapFixedDayCountWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::VanillaSwap, QuantLib::VanillaSwap)


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

NAN_METHOD(QuantLibXL::VanillaSwapFixedDayCount) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  VanillaSwapFixedDayCountWorker* worker = new VanillaSwapFixedDayCountWorker(
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

void VanillaSwapSpreadWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::VanillaSwap, QuantLib::VanillaSwap)


  // invoke the member function
  mReturnValue = ObjectIDLibObjPtr->spread(
      );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::VanillaSwapSpread) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  VanillaSwapSpreadWorker* worker = new VanillaSwapSpreadWorker(
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

void VanillaSwapFloatingDayCountWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::VanillaSwap, QuantLib::VanillaSwap)


  // invoke the member function
  QuantLib::DayCounter returnValue = ObjectIDLibObjPtr->floatingDayCount(
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

NAN_METHOD(QuantLibXL::VanillaSwapFloatingDayCount) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  VanillaSwapFloatingDayCountWorker* worker = new VanillaSwapFloatingDayCountWorker(
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

void VanillaSwapPaymentConventionWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::VanillaSwap, QuantLib::VanillaSwap)


  // invoke the member function
  QuantLib::BusinessDayConvention returnValue = ObjectIDLibObjPtr->paymentConvention(
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

NAN_METHOD(QuantLibXL::VanillaSwapPaymentConvention) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  VanillaSwapPaymentConventionWorker* worker = new VanillaSwapPaymentConventionWorker(
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

void VanillaSwapFixedLegAnalysisWorker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes
  QuantLib::Date AfterDateLib = ObjectHandler::convert2<QuantLib::Date>(
      mAfterDate, "AfterDate");

       // convert object IDs into library objects
  OH_GET_OBJECT(ObjectIDObjPtr, mObjectID, QuantLibAddin::VanillaSwap)

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

NAN_METHOD(QuantLibXL::VanillaSwapFixedLegAnalysis) {

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
  VanillaSwapFixedLegAnalysisWorker* worker = new VanillaSwapFixedLegAnalysisWorker(
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

void VanillaSwapFloatingLegAnalysisWorker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes
  QuantLib::Date AfterDateLib = ObjectHandler::convert2<QuantLib::Date>(
      mAfterDate, "AfterDate");

       // convert object IDs into library objects
  OH_GET_OBJECT(ObjectIDObjPtr, mObjectID, QuantLibAddin::VanillaSwap)

  std::vector< std::vector<ObjectHandler::property_t> > returnValue;


  // invoke the member function
  returnValue = ObjectIDObjPtr->floatingLegAnalysis(
        AfterDateLib
       );


  mReturnValue = ObjectHandler::matrix::convert2<string>(returnValue,"returnValue");

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::VanillaSwapFloatingLegAnalysis) {

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
  VanillaSwapFloatingLegAnalysisWorker* worker = new VanillaSwapFloatingLegAnalysisWorker(
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
 