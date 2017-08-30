/* 
  Copyright (C) 2016 -2017 Jerry Jin
*/

#include <nan.h>
#include <string.h>

#include "pricingengines.hpp"

#include <qlo/qladdindefines.hpp>
#include <qlo/pricingengines.hpp>
#include <qlo/termstructures.hpp>
#include <qlo/shortratemodels.hpp>
#include <qlo/payoffs.hpp>
#include <qlo/marketmodels.hpp>
#include <qlo/processes.hpp>
#include <ql/pricingengines/blackformula.hpp>
#include <ql/pricingengines/blackscholescalculator.hpp>
#include <ql/termstructures/volatility/optionlet/optionletvolatilitystructure.hpp>
#include <ql/termstructures/volatility/swaption/swaptionvolstructure.hpp>
#include <ql/pricingengines/swaption/jamshidianswaptionengine.hpp>
#include <ql/pricingengines/swaption/g2swaptionengine.hpp>
 #include <oh/objecthandler.hpp>
#include <oh/conversions/getobjectvector.hpp>
#include <qlo/valueobjects/vo_all.hpp>
#include <qlo/conversions/all.hpp>
#include "../loop.hpp"


void BlackCalculator2Worker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_REFERENCE(PayoffIDLibObjPtr, mPayoffID,
      QuantLibAddin::StrikedTypePayoff, QuantLib::StrikedTypePayoff)


  // convert input datatypes to QuantLib datatypes

  // convert input datatypes to QuantLib datatypes

  // convert input datatypes to QuantLib datatypes
 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlBlackCalculator2(
          mObjectID,
          mPayoffID,
          mAtmForwardValue,
          mStdDev,
          mDeflator,
          false
      ));

    // Construct the Object
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::BlackCalculator(
          valueObject,
          PayoffIDLibObjPtr,
          mAtmForwardValue,
          mStdDev,
          mDeflator,
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

NAN_METHOD(QuantLibXL::BlackCalculator2) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsString()) {
      return Nan::ThrowError("PayoffID is required.");
  }
  if (info.Length() == 2 || !info[2]->IsNumber()) {
      return Nan::ThrowError("AtmForwardValue is required.");
  }
  if (info.Length() == 3 || !info[3]->IsNumber()) {
      return Nan::ThrowError("StdDev is required.");
  }
  if (info.Length() == 4 || !info[4]->IsNumber()) {
      return Nan::ThrowError("Deflator is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  String::Utf8Value strPayoffID(info[1]->ToString());
  string PayoffIDCpp(strdup(*strPayoffID));

  // convert js argument to c++ type
  double AtmForwardValueCpp = Nan::To<double>(info[2]).FromJust();

  // convert js argument to c++ type
  double StdDevCpp = Nan::To<double>(info[3]).FromJust();

  // convert js argument to c++ type
  double DeflatorCpp = Nan::To<double>(info[4]).FromJust();

 
  // launch worker
  BlackCalculator2Worker* worker = new BlackCalculator2Worker(
    ObjectIDCpp
,     PayoffIDCpp
,     AtmForwardValueCpp
,     StdDevCpp
,     DeflatorCpp
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

void BlackCalculatorWorker::Execute(){

  try{

  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::Option::Type OptionTypeEnum =
      ObjectHandler::Create<QuantLib::Option::Type>()(mOptionType);


  // convert input datatypes to QuantLib datatypes

  // convert input datatypes to QuantLib datatypes

  // convert input datatypes to QuantLib datatypes

  // convert input datatypes to QuantLib datatypes
 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlBlackCalculator(
          mObjectID,
          mOptionType,
          mStrike,
          mAtmForwardValue,
          mStdDev,
          mDeflator,
          false
      ));

    // Construct the Object
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::BlackCalculator(
          valueObject,
          OptionTypeEnum,
          mStrike,
          mAtmForwardValue,
          mStdDev,
          mDeflator,
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

NAN_METHOD(QuantLibXL::BlackCalculator) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsString()) {
      return Nan::ThrowError("OptionType is required.");
  }
  if (info.Length() == 2 || !info[2]->IsNumber()) {
      return Nan::ThrowError("Strike is required.");
  }
  if (info.Length() == 3 || !info[3]->IsNumber()) {
      return Nan::ThrowError("AtmForwardValue is required.");
  }
  if (info.Length() == 4 || !info[4]->IsNumber()) {
      return Nan::ThrowError("StdDev is required.");
  }
  if (info.Length() == 5 || !info[5]->IsNumber()) {
      return Nan::ThrowError("Deflator is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  String::Utf8Value strOptionType(info[1]->ToString());
  string OptionTypeCpp(strdup(*strOptionType));

  // convert js argument to c++ type
  double StrikeCpp = Nan::To<double>(info[2]).FromJust();

  // convert js argument to c++ type
  double AtmForwardValueCpp = Nan::To<double>(info[3]).FromJust();

  // convert js argument to c++ type
  double StdDevCpp = Nan::To<double>(info[4]).FromJust();

  // convert js argument to c++ type
  double DeflatorCpp = Nan::To<double>(info[5]).FromJust();

 
  // launch worker
  BlackCalculatorWorker* worker = new BlackCalculatorWorker(
    ObjectIDCpp
,     OptionTypeCpp
,     StrikeCpp
,     AtmForwardValueCpp
,     StdDevCpp
,     DeflatorCpp
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

void BlackScholesCalculator2Worker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_REFERENCE(PayoffIDLibObjPtr, mPayoffID,
      QuantLibAddin::StrikedTypePayoff, QuantLib::StrikedTypePayoff)


  // convert input datatypes to QuantLib datatypes

  // convert input datatypes to QuantLib datatypes

  // convert input datatypes to QuantLib datatypes
 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlBlackScholesCalculator2(
          mObjectID,
          mPayoffID,
          mSpot,
          mGrowth,
          mStdDev,
          mDeflator,
          false
      ));

    // Construct the Object
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::BlackScholesCalculator(
          valueObject,
          PayoffIDLibObjPtr,
          mSpot,
          mGrowth,
          mStdDev,
          mDeflator,
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

NAN_METHOD(QuantLibXL::BlackScholesCalculator2) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsString()) {
      return Nan::ThrowError("PayoffID is required.");
  }
  if (info.Length() == 2 || !info[2]->IsNumber()) {
      return Nan::ThrowError("Spot is required.");
  }
  if (info.Length() == 3 || !info[3]->IsNumber()) {
      return Nan::ThrowError("Growth is required.");
  }
  if (info.Length() == 4 || !info[4]->IsNumber()) {
      return Nan::ThrowError("StdDev is required.");
  }
  if (info.Length() == 5 || !info[5]->IsNumber()) {
      return Nan::ThrowError("Deflator is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  String::Utf8Value strPayoffID(info[1]->ToString());
  string PayoffIDCpp(strdup(*strPayoffID));

  // convert js argument to c++ type
  double SpotCpp = Nan::To<double>(info[2]).FromJust();

  // convert js argument to c++ type
  double GrowthCpp = Nan::To<double>(info[3]).FromJust();

  // convert js argument to c++ type
  double StdDevCpp = Nan::To<double>(info[4]).FromJust();

  // convert js argument to c++ type
  double DeflatorCpp = Nan::To<double>(info[5]).FromJust();

 
  // launch worker
  BlackScholesCalculator2Worker* worker = new BlackScholesCalculator2Worker(
    ObjectIDCpp
,     PayoffIDCpp
,     SpotCpp
,     GrowthCpp
,     StdDevCpp
,     DeflatorCpp
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

void BlackScholesCalculatorWorker::Execute(){

  try{

  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::Option::Type OptionTypeEnum =
      ObjectHandler::Create<QuantLib::Option::Type>()(mOptionType);


  // convert input datatypes to QuantLib datatypes

  // convert input datatypes to QuantLib datatypes

  // convert input datatypes to QuantLib datatypes

  // convert input datatypes to QuantLib datatypes
 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlBlackScholesCalculator(
          mObjectID,
          mOptionType,
          mStrike,
          mSpot,
          mGrowth,
          mStdDev,
          mDeflator,
          false
      ));

    // Construct the Object
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::BlackScholesCalculator(
          valueObject,
          OptionTypeEnum,
          mStrike,
          mSpot,
          mGrowth,
          mStdDev,
          mDeflator,
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

NAN_METHOD(QuantLibXL::BlackScholesCalculator) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsString()) {
      return Nan::ThrowError("OptionType is required.");
  }
  if (info.Length() == 2 || !info[2]->IsNumber()) {
      return Nan::ThrowError("Strike is required.");
  }
  if (info.Length() == 3 || !info[3]->IsNumber()) {
      return Nan::ThrowError("Spot is required.");
  }
  if (info.Length() == 4 || !info[4]->IsNumber()) {
      return Nan::ThrowError("Growth is required.");
  }
  if (info.Length() == 5 || !info[5]->IsNumber()) {
      return Nan::ThrowError("StdDev is required.");
  }
  if (info.Length() == 6 || !info[6]->IsNumber()) {
      return Nan::ThrowError("Deflator is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  String::Utf8Value strOptionType(info[1]->ToString());
  string OptionTypeCpp(strdup(*strOptionType));

  // convert js argument to c++ type
  double StrikeCpp = Nan::To<double>(info[2]).FromJust();

  // convert js argument to c++ type
  double SpotCpp = Nan::To<double>(info[3]).FromJust();

  // convert js argument to c++ type
  double GrowthCpp = Nan::To<double>(info[4]).FromJust();

  // convert js argument to c++ type
  double StdDevCpp = Nan::To<double>(info[5]).FromJust();

  // convert js argument to c++ type
  double DeflatorCpp = Nan::To<double>(info[6]).FromJust();

 
  // launch worker
  BlackScholesCalculatorWorker* worker = new BlackScholesCalculatorWorker(
    ObjectIDCpp
,     OptionTypeCpp
,     StrikeCpp
,     SpotCpp
,     GrowthCpp
,     StdDevCpp
,     DeflatorCpp
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

void PricingEngineWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_REFERENCE(ProcessIDLibObjPtr, mProcessID,
      QuantLibAddin::GeneralizedBlackScholesProcess, QuantLib::GeneralizedBlackScholesProcess)

 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlPricingEngine(
          mObjectID,
          mEngineID,
          mProcessID,
          false
      ));

    // Construct the Object
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::PricingEngine(
          valueObject,
          mEngineID,
          ProcessIDLibObjPtr,
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

NAN_METHOD(QuantLibXL::PricingEngine) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsString()) {
      return Nan::ThrowError("EngineID is required.");
  }
  if (info.Length() == 2 || !info[2]->IsString()) {
      return Nan::ThrowError("ProcessID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  String::Utf8Value strEngineID(info[1]->ToString());
  string EngineIDCpp(strdup(*strEngineID));

  // convert js argument to c++ type
  String::Utf8Value strProcessID(info[2]->ToString());
  string ProcessIDCpp(strdup(*strProcessID));

 
  // launch worker
  PricingEngineWorker* worker = new PricingEngineWorker(
    ObjectIDCpp
,     EngineIDCpp
,     ProcessIDCpp
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

void DiscountingSwapEngineWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_OBJECT(YieldCurveCoerce, mYieldCurve, ObjectHandler::Object)
  QuantLib::Handle<QuantLib::YieldTermStructure> YieldCurveLibObj =
      QuantLibAddin::CoerceHandle<
          QuantLibAddin::YieldTermStructure,
          QuantLib::YieldTermStructure>()(
              YieldCurveCoerce);


  // convert input datatypes to QuantLib datatypes
  QuantLib::Date SettlementDateLib = ObjectHandler::convert2<QuantLib::Date>(
      mSettlementDate, "SettlementDate");


  // convert input datatypes to QuantLib datatypes
  QuantLib::Date NpvDateLib = ObjectHandler::convert2<QuantLib::Date>(
      mNpvDate, "NpvDate");

 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlDiscountingSwapEngine(
          mObjectID,
          mYieldCurve,
          mIncludeSettlDate,
          mSettlementDate,
          mNpvDate,
          false
      ));

    // Construct the Object
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::DiscountingSwapEngine(
          valueObject,
          YieldCurveLibObj,
          mIncludeSettlDate,
          SettlementDateLib,
          NpvDateLib,
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

NAN_METHOD(QuantLibXL::DiscountingSwapEngine) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 2 || !info[2]->IsBoolean()) {
      return Nan::ThrowError("IncludeSettlDate is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  ObjectHandler::property_t YieldCurveCpp =
      ObjectHandler::property_t(static_cast<double>(Nan::To<double>(info[1]).FromJust()));

  // convert js argument to c++ type
  bool IncludeSettlDateCpp = Nan::To<bool>(info[2]).FromJust();

  // convert js argument to c++ type
  ObjectHandler::property_t SettlementDateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[3]).FromJust()));

  // convert js argument to c++ type
  ObjectHandler::property_t NpvDateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[4]).FromJust()));

 
  // launch worker
  DiscountingSwapEngineWorker* worker = new DiscountingSwapEngineWorker(
    ObjectIDCpp
,     YieldCurveCpp
,     IncludeSettlDateCpp
,     SettlementDateCpp
,     NpvDateCpp
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

void BinomialPricingEngineWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_REFERENCE(ProcessIDLibObjPtr, mProcessID,
      QuantLibAddin::GeneralizedBlackScholesProcess, QuantLib::GeneralizedBlackScholesProcess)

 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlBinomialPricingEngine(
          mObjectID,
          mEngineID,
          mProcessID,
          mTimeSteps,
          false
      ));

    // Construct the Object
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::PricingEngine(
          valueObject,
          mEngineID,
          ProcessIDLibObjPtr,
          mTimeSteps,
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

NAN_METHOD(QuantLibXL::BinomialPricingEngine) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsString()) {
      return Nan::ThrowError("EngineID is required.");
  }
  if (info.Length() == 2 || !info[2]->IsString()) {
      return Nan::ThrowError("ProcessID is required.");
  }
  if (info.Length() == 3 || !info[3]->IsNumber()) {
      return Nan::ThrowError("TimeSteps is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  String::Utf8Value strEngineID(info[1]->ToString());
  string EngineIDCpp(strdup(*strEngineID));

  // convert js argument to c++ type
  String::Utf8Value strProcessID(info[2]->ToString());
  string ProcessIDCpp(strdup(*strProcessID));

  // convert js argument to c++ type
  long TimeStepsCpp = Nan::To<int32_t>(info[3]).FromJust();

 
  // launch worker
  BinomialPricingEngineWorker* worker = new BinomialPricingEngineWorker(
    ObjectIDCpp
,     EngineIDCpp
,     ProcessIDCpp
,     TimeStepsCpp
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

void BlackSwaptionEngineWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_OBJECT(YieldCurveCoerce, mYieldCurve, ObjectHandler::Object)
  QuantLib::Handle<QuantLib::YieldTermStructure> YieldCurveLibObj =
      QuantLibAddin::CoerceHandle<
          QuantLibAddin::YieldTermStructure,
          QuantLib::YieldTermStructure>()(
              YieldCurveCoerce);


  // convert object IDs into library objects
  OH_GET_OBJECT(VolTSCoerce, mVolTS, ObjectHandler::Object)
  QuantLib::Handle<QuantLib::SwaptionVolatilityStructure> VolTSLibObj =
      QuantLibAddin::CoerceHandle<
          QuantLibAddin::SwaptionVolatilityStructure,
          QuantLib::SwaptionVolatilityStructure>()(
              VolTSCoerce);


  // convert input datatypes to QuantLib datatypes
 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlBlackSwaptionEngine(
          mObjectID,
          mYieldCurve,
          mVolTS,
          mDisplacement,
          false
      ));

    // Construct the Object
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::BlackSwaptionEngine(
          valueObject,
          YieldCurveLibObj,
          VolTSLibObj,
          mDisplacement,
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

NAN_METHOD(QuantLibXL::BlackSwaptionEngine) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 3 || !info[3]->IsNumber()) {
      return Nan::ThrowError("Displacement is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  ObjectHandler::property_t YieldCurveCpp =
      ObjectHandler::property_t(static_cast<double>(Nan::To<double>(info[1]).FromJust()));

  // convert js argument to c++ type
  ObjectHandler::property_t VolTSCpp =
      ObjectHandler::property_t(static_cast<double>(Nan::To<double>(info[2]).FromJust()));

  // convert js argument to c++ type
  double DisplacementCpp = Nan::To<double>(info[3]).FromJust();

 
  // launch worker
  BlackSwaptionEngineWorker* worker = new BlackSwaptionEngineWorker(
    ObjectIDCpp
,     YieldCurveCpp
,     VolTSCpp
,     DisplacementCpp
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

void BlackSwaptionEngine2Worker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_OBJECT(YieldCurveCoerce, mYieldCurve, ObjectHandler::Object)
  QuantLib::Handle<QuantLib::YieldTermStructure> YieldCurveLibObj =
      QuantLibAddin::CoerceHandle<
          QuantLibAddin::YieldTermStructure,
          QuantLib::YieldTermStructure>()(
              YieldCurveCoerce);


  // convert object IDs into library objects
  QuantLib::Handle<QuantLib::Quote> VolLibObj =
      ObjectHandler::convert2< QuantLib::Handle<QuantLib::Quote> >(mVol, "Vol");


  // convert input datatypes to QuantLib datatypes

  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::DayCounter DayCounterEnum =
      ObjectHandler::Create<QuantLib::DayCounter>()(mDayCounter);

 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlBlackSwaptionEngine2(
          mObjectID,
          mYieldCurve,
          mVol,
          mDisplacement,
          mDayCounter,
          false
      ));

    // Construct the Object
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::BlackSwaptionEngine(
          valueObject,
          YieldCurveLibObj,
          VolLibObj,
          mDisplacement,
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

NAN_METHOD(QuantLibXL::BlackSwaptionEngine2) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 3 || !info[3]->IsNumber()) {
      return Nan::ThrowError("Displacement is required.");
  }
  if (info.Length() == 4 || !info[4]->IsString()) {
      return Nan::ThrowError("DayCounter is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  ObjectHandler::property_t YieldCurveCpp =
      ObjectHandler::property_t(static_cast<double>(Nan::To<double>(info[1]).FromJust()));

  // convert js argument to c++ type
  ObjectHandler::property_t VolCpp =
      ObjectHandler::property_t(static_cast<double>(Nan::To<double>(info[2]).FromJust()));

  // convert js argument to c++ type
  double DisplacementCpp = Nan::To<double>(info[3]).FromJust();

  // convert js argument to c++ type
  String::Utf8Value strDayCounter(info[4]->ToString());
  string DayCounterCpp(strdup(*strDayCounter));

 
  // launch worker
  BlackSwaptionEngine2Worker* worker = new BlackSwaptionEngine2Worker(
    ObjectIDCpp
,     YieldCurveCpp
,     VolCpp
,     DisplacementCpp
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

void BlackCapFloorEngineWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_OBJECT(YieldCurveCoerce, mYieldCurve, ObjectHandler::Object)
  QuantLib::Handle<QuantLib::YieldTermStructure> YieldCurveLibObj =
      QuantLibAddin::CoerceHandle<
          QuantLibAddin::YieldTermStructure,
          QuantLib::YieldTermStructure>()(
              YieldCurveCoerce);


  // convert object IDs into library objects
  OH_GET_OBJECT(VolTSCoerce, mVolTS, ObjectHandler::Object)
  QuantLib::Handle<QuantLib::OptionletVolatilityStructure> VolTSLibObj =
      QuantLibAddin::CoerceHandle<
          QuantLibAddin::OptionletVolatilityStructure,
          QuantLib::OptionletVolatilityStructure>()(
              VolTSCoerce);


  // convert input datatypes to QuantLib datatypes
 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlBlackCapFloorEngine(
          mObjectID,
          mYieldCurve,
          mVolTS,
          mDisplacement,
          false
      ));

    // Construct the Object
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::BlackCapFloorEngine(
          valueObject,
          YieldCurveLibObj,
          VolTSLibObj,
          mDisplacement,
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

NAN_METHOD(QuantLibXL::BlackCapFloorEngine) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 3 || !info[3]->IsNumber()) {
      return Nan::ThrowError("Displacement is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  ObjectHandler::property_t YieldCurveCpp =
      ObjectHandler::property_t(static_cast<double>(Nan::To<double>(info[1]).FromJust()));

  // convert js argument to c++ type
  ObjectHandler::property_t VolTSCpp =
      ObjectHandler::property_t(static_cast<double>(Nan::To<double>(info[2]).FromJust()));

  // convert js argument to c++ type
  double DisplacementCpp = Nan::To<double>(info[3]).FromJust();

 
  // launch worker
  BlackCapFloorEngineWorker* worker = new BlackCapFloorEngineWorker(
    ObjectIDCpp
,     YieldCurveCpp
,     VolTSCpp
,     DisplacementCpp
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

void BlackCapFloorEngine2Worker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_OBJECT(YieldCurveCoerce, mYieldCurve, ObjectHandler::Object)
  QuantLib::Handle<QuantLib::YieldTermStructure> YieldCurveLibObj =
      QuantLibAddin::CoerceHandle<
          QuantLibAddin::YieldTermStructure,
          QuantLib::YieldTermStructure>()(
              YieldCurveCoerce);


  // convert object IDs into library objects
  QuantLib::Handle<QuantLib::Quote> VolLibObj =
      ObjectHandler::convert2< QuantLib::Handle<QuantLib::Quote> >(mVol, "Vol");


  // convert input datatypes to QuantLib datatypes

  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::DayCounter DayCounterEnum =
      ObjectHandler::Create<QuantLib::DayCounter>()(mDayCounter);

 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlBlackCapFloorEngine2(
          mObjectID,
          mYieldCurve,
          mVol,
          mDisplacement,
          mDayCounter,
          false
      ));

    // Construct the Object
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::BlackCapFloorEngine(
          valueObject,
          YieldCurveLibObj,
          VolLibObj,
          mDisplacement,
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

NAN_METHOD(QuantLibXL::BlackCapFloorEngine2) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 3 || !info[3]->IsNumber()) {
      return Nan::ThrowError("Displacement is required.");
  }
  if (info.Length() == 4 || !info[4]->IsString()) {
      return Nan::ThrowError("DayCounter is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  ObjectHandler::property_t YieldCurveCpp =
      ObjectHandler::property_t(static_cast<double>(Nan::To<double>(info[1]).FromJust()));

  // convert js argument to c++ type
  ObjectHandler::property_t VolCpp =
      ObjectHandler::property_t(static_cast<double>(Nan::To<double>(info[2]).FromJust()));

  // convert js argument to c++ type
  double DisplacementCpp = Nan::To<double>(info[3]).FromJust();

  // convert js argument to c++ type
  String::Utf8Value strDayCounter(info[4]->ToString());
  string DayCounterCpp(strdup(*strDayCounter));

 
  // launch worker
  BlackCapFloorEngine2Worker* worker = new BlackCapFloorEngine2Worker(
    ObjectIDCpp
,     YieldCurveCpp
,     VolCpp
,     DisplacementCpp
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

void BachelierCapFloorEngineWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_OBJECT(YieldCurveCoerce, mYieldCurve, ObjectHandler::Object)
  QuantLib::Handle<QuantLib::YieldTermStructure> YieldCurveLibObj =
      QuantLibAddin::CoerceHandle<
          QuantLibAddin::YieldTermStructure,
          QuantLib::YieldTermStructure>()(
              YieldCurveCoerce);


  // convert object IDs into library objects
  OH_GET_OBJECT(VolTSCoerce, mVolTS, ObjectHandler::Object)
  QuantLib::Handle<QuantLib::OptionletVolatilityStructure> VolTSLibObj =
      QuantLibAddin::CoerceHandle<
          QuantLibAddin::OptionletVolatilityStructure,
          QuantLib::OptionletVolatilityStructure>()(
              VolTSCoerce);

 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlBachelierCapFloorEngine(
          mObjectID,
          mYieldCurve,
          mVolTS,
          false
      ));

    // Construct the Object
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::BachelierCapFloorEngine(
          valueObject,
          YieldCurveLibObj,
          VolTSLibObj,
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

NAN_METHOD(QuantLibXL::BachelierCapFloorEngine) {

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

  // convert js argument to c++ type
  ObjectHandler::property_t VolTSCpp =
      ObjectHandler::property_t(static_cast<double>(Nan::To<double>(info[2]).FromJust()));

 
  // launch worker
  BachelierCapFloorEngineWorker* worker = new BachelierCapFloorEngineWorker(
    ObjectIDCpp
,     YieldCurveCpp
,     VolTSCpp
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

void BachelierCapFloorEngine2Worker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_OBJECT(YieldCurveCoerce, mYieldCurve, ObjectHandler::Object)
  QuantLib::Handle<QuantLib::YieldTermStructure> YieldCurveLibObj =
      QuantLibAddin::CoerceHandle<
          QuantLibAddin::YieldTermStructure,
          QuantLib::YieldTermStructure>()(
              YieldCurveCoerce);


  // convert object IDs into library objects
  QuantLib::Handle<QuantLib::Quote> VolLibObj =
      ObjectHandler::convert2< QuantLib::Handle<QuantLib::Quote> >(mVol, "Vol");


  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::DayCounter DayCounterEnum =
      ObjectHandler::Create<QuantLib::DayCounter>()(mDayCounter);

 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlBachelierCapFloorEngine2(
          mObjectID,
          mYieldCurve,
          mVol,
          mDayCounter,
          false
      ));

    // Construct the Object
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::BachelierCapFloorEngine(
          valueObject,
          YieldCurveLibObj,
          VolLibObj,
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

NAN_METHOD(QuantLibXL::BachelierCapFloorEngine2) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 3 || !info[3]->IsString()) {
      return Nan::ThrowError("DayCounter is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  ObjectHandler::property_t YieldCurveCpp =
      ObjectHandler::property_t(static_cast<double>(Nan::To<double>(info[1]).FromJust()));

  // convert js argument to c++ type
  ObjectHandler::property_t VolCpp =
      ObjectHandler::property_t(static_cast<double>(Nan::To<double>(info[2]).FromJust()));

  // convert js argument to c++ type
  String::Utf8Value strDayCounter(info[3]->ToString());
  string DayCounterCpp(strdup(*strDayCounter));

 
  // launch worker
  BachelierCapFloorEngine2Worker* worker = new BachelierCapFloorEngine2Worker(
    ObjectIDCpp
,     YieldCurveCpp
,     VolCpp
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

void AnalyticCapFloorEngineWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_REFERENCE(HandleModelLibObjPtr, mHandleModel,
      QuantLibAddin::AffineModel, QuantLib::AffineModel)

 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlAnalyticCapFloorEngine(
          mObjectID,
          mHandleModel,
          false
      ));

    // Construct the Object
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::AnalyticCapFloorEngine(
          valueObject,
          HandleModelLibObjPtr,
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

NAN_METHOD(QuantLibXL::AnalyticCapFloorEngine) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsString()) {
      return Nan::ThrowError("HandleModel is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  String::Utf8Value strHandleModel(info[1]->ToString());
  string HandleModelCpp(strdup(*strHandleModel));

 
  // launch worker
  AnalyticCapFloorEngineWorker* worker = new AnalyticCapFloorEngineWorker(
    ObjectIDCpp
,     HandleModelCpp
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

void BondEngineWorker::Execute(){

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
      new QuantLibAddin::ValueObjects::qlBondEngine(
          mObjectID,
          mYieldCurve,
          false
      ));

    // Construct the Object
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::BondEngine(
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

NAN_METHOD(QuantLibXL::BondEngine) {

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
  BondEngineWorker* worker = new BondEngineWorker(
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

void JamshidianSwaptionEngineWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_REFERENCE(ModelLibObjPtr, mModel,
      QuantLibAddin::OneFactorAffineModel, QuantLib::OneFactorAffineModel)


  // convert object IDs into library objects
  OH_GET_OBJECT(YieldCurveCoerce, mYieldCurve, ObjectHandler::Object)
  QuantLib::Handle<QuantLib::YieldTermStructure> YieldCurveLibObj =
      QuantLibAddin::CoerceHandle<
          QuantLibAddin::YieldTermStructure,
          QuantLib::YieldTermStructure>()(
              YieldCurveCoerce);

 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlJamshidianSwaptionEngine(
          mObjectID,
          mModel,
          mYieldCurve,
          false
      ));

    // Construct the Object
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::JamshidianSwaptionEngine(
          valueObject,
          ModelLibObjPtr,
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

NAN_METHOD(QuantLibXL::JamshidianSwaptionEngine) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsString()) {
      return Nan::ThrowError("Model is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  String::Utf8Value strModel(info[1]->ToString());
  string ModelCpp(strdup(*strModel));

  // convert js argument to c++ type
  ObjectHandler::property_t YieldCurveCpp =
      ObjectHandler::property_t(static_cast<double>(Nan::To<double>(info[2]).FromJust()));

 
  // launch worker
  JamshidianSwaptionEngineWorker* worker = new JamshidianSwaptionEngineWorker(
    ObjectIDCpp
,     ModelCpp
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

void TreeSwaptionEngineWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_REFERENCE(ModelLibObjPtr, mModel,
      QuantLibAddin::OneFactorAffineModel, QuantLib::OneFactorAffineModel)


  // convert input datatypes to QuantLib datatypes
  QuantLib::Size NstepsLib;
  QuantLibAddin::cppToLibrary(mNsteps, NstepsLib);


  // convert object IDs into library objects
  OH_GET_OBJECT(YieldCurveCoerce, mYieldCurve, ObjectHandler::Object)
  QuantLib::Handle<QuantLib::YieldTermStructure> YieldCurveLibObj =
      QuantLibAddin::CoerceHandle<
          QuantLibAddin::YieldTermStructure,
          QuantLib::YieldTermStructure>()(
              YieldCurveCoerce);

 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlTreeSwaptionEngine(
          mObjectID,
          mModel,
          mNsteps,
          mYieldCurve,
          false
      ));

    // Construct the Object
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::TreeSwaptionEngine(
          valueObject,
          ModelLibObjPtr,
          NstepsLib,
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

NAN_METHOD(QuantLibXL::TreeSwaptionEngine) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsString()) {
      return Nan::ThrowError("Model is required.");
  }
  if (info.Length() == 2 || !info[2]->IsNumber()) {
      return Nan::ThrowError("Nsteps is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  String::Utf8Value strModel(info[1]->ToString());
  string ModelCpp(strdup(*strModel));

  // convert js argument to c++ type
  long NstepsCpp = Nan::To<int32_t>(info[2]).FromJust();

  // convert js argument to c++ type
  ObjectHandler::property_t YieldCurveCpp =
      ObjectHandler::property_t(static_cast<double>(Nan::To<double>(info[3]).FromJust()));

 
  // launch worker
  TreeSwaptionEngineWorker* worker = new TreeSwaptionEngineWorker(
    ObjectIDCpp
,     ModelCpp
,     NstepsCpp
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

void ModelG2SwaptionEngineWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_REFERENCE(ModelLibObjPtr, mModel,
      QuantLibAddin::G2, QuantLib::G2)


  // convert input datatypes to QuantLib datatypes

  // convert input datatypes to QuantLib datatypes
  QuantLib::Size IntervalsLib;
  QuantLibAddin::cppToLibrary(mIntervals, IntervalsLib);

 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlModelG2SwaptionEngine(
          mObjectID,
          mModel,
          mRange,
          mIntervals,
          false
      ));

    // Construct the Object
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::G2SwaptionEngine(
          valueObject,
          ModelLibObjPtr,
          mRange,
          IntervalsLib,
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

NAN_METHOD(QuantLibXL::ModelG2SwaptionEngine) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsString()) {
      return Nan::ThrowError("Model is required.");
  }
  if (info.Length() == 2 || !info[2]->IsNumber()) {
      return Nan::ThrowError("Range is required.");
  }
  if (info.Length() == 3 || !info[3]->IsNumber()) {
      return Nan::ThrowError("Intervals is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  String::Utf8Value strModel(info[1]->ToString());
  string ModelCpp(strdup(*strModel));

  // convert js argument to c++ type
  double RangeCpp = Nan::To<double>(info[2]).FromJust();

  // convert js argument to c++ type
  long IntervalsCpp = Nan::To<int32_t>(info[3]).FromJust();

 
  // launch worker
  ModelG2SwaptionEngineWorker* worker = new ModelG2SwaptionEngineWorker(
    ObjectIDCpp
,     ModelCpp
,     RangeCpp
,     IntervalsCpp
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

void BlackCalculatorValueWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::BlackCalculator, QuantLib::BlackCalculator)


  // invoke the member function
  mReturnValue = ObjectIDLibObjPtr->value(
      );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::BlackCalculatorValue) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  BlackCalculatorValueWorker* worker = new BlackCalculatorValueWorker(
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

void BlackCalculatorDeltaForwardWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::BlackCalculator, QuantLib::BlackCalculator)


  // invoke the member function
  mReturnValue = ObjectIDLibObjPtr->deltaForward(
      );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::BlackCalculatorDeltaForward) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  BlackCalculatorDeltaForwardWorker* worker = new BlackCalculatorDeltaForwardWorker(
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

void BlackCalculatorDeltaWorker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::BlackCalculator, QuantLib::BlackCalculator)


  // invoke the member function
  mReturnValue = ObjectIDLibObjPtr->delta(
        mSpot
       );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::BlackCalculatorDelta) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsNumber()) {
      return Nan::ThrowError("Spot is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  double SpotCpp = Nan::To<double>(info[1]).FromJust();

 
  // launch worker
  BlackCalculatorDeltaWorker* worker = new BlackCalculatorDeltaWorker(
    ObjectIDCpp
,     SpotCpp
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

void BlackCalculatorElasticityForwardWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::BlackCalculator, QuantLib::BlackCalculator)


  // invoke the member function
  mReturnValue = ObjectIDLibObjPtr->elasticityForward(
      );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::BlackCalculatorElasticityForward) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  BlackCalculatorElasticityForwardWorker* worker = new BlackCalculatorElasticityForwardWorker(
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

void BlackCalculatorElasticityWorker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::BlackCalculator, QuantLib::BlackCalculator)


  // invoke the member function
  mReturnValue = ObjectIDLibObjPtr->elasticity(
        mSpot
       );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::BlackCalculatorElasticity) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsNumber()) {
      return Nan::ThrowError("Spot is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  double SpotCpp = Nan::To<double>(info[1]).FromJust();

 
  // launch worker
  BlackCalculatorElasticityWorker* worker = new BlackCalculatorElasticityWorker(
    ObjectIDCpp
,     SpotCpp
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

void BlackCalculatorGammaForwardWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::BlackCalculator, QuantLib::BlackCalculator)


  // invoke the member function
  mReturnValue = ObjectIDLibObjPtr->gammaForward(
      );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::BlackCalculatorGammaForward) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  BlackCalculatorGammaForwardWorker* worker = new BlackCalculatorGammaForwardWorker(
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

void BlackCalculatorGammaWorker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::BlackCalculator, QuantLib::BlackCalculator)


  // invoke the member function
  mReturnValue = ObjectIDLibObjPtr->gamma(
        mSpot
       );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::BlackCalculatorGamma) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsNumber()) {
      return Nan::ThrowError("Spot is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  double SpotCpp = Nan::To<double>(info[1]).FromJust();

 
  // launch worker
  BlackCalculatorGammaWorker* worker = new BlackCalculatorGammaWorker(
    ObjectIDCpp
,     SpotCpp
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

void BlackCalculatorThetaWorker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::BlackCalculator, QuantLib::BlackCalculator)


  // invoke the member function
  mReturnValue = ObjectIDLibObjPtr->theta(
        mSpot
        ,
         mTimeToMaturity
       );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::BlackCalculatorTheta) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsNumber()) {
      return Nan::ThrowError("Spot is required.");
  }
  if (info.Length() == 2 || !info[2]->IsNumber()) {
      return Nan::ThrowError("TimeToMaturity is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  double SpotCpp = Nan::To<double>(info[1]).FromJust();

  // convert js argument to c++ type
  double TimeToMaturityCpp = Nan::To<double>(info[2]).FromJust();

 
  // launch worker
  BlackCalculatorThetaWorker* worker = new BlackCalculatorThetaWorker(
    ObjectIDCpp
,     SpotCpp
,     TimeToMaturityCpp
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

void BlackCalculatorThetaPerDayWorker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::BlackCalculator, QuantLib::BlackCalculator)


  // invoke the member function
  mReturnValue = ObjectIDLibObjPtr->thetaPerDay(
        mSpot
        ,
         mTimeToMaturity
       );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::BlackCalculatorThetaPerDay) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsNumber()) {
      return Nan::ThrowError("Spot is required.");
  }
  if (info.Length() == 2 || !info[2]->IsNumber()) {
      return Nan::ThrowError("TimeToMaturity is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  double SpotCpp = Nan::To<double>(info[1]).FromJust();

  // convert js argument to c++ type
  double TimeToMaturityCpp = Nan::To<double>(info[2]).FromJust();

 
  // launch worker
  BlackCalculatorThetaPerDayWorker* worker = new BlackCalculatorThetaPerDayWorker(
    ObjectIDCpp
,     SpotCpp
,     TimeToMaturityCpp
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

void BlackCalculatorVegaWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::BlackCalculator, QuantLib::BlackCalculator)


  // invoke the member function
  mReturnValue = ObjectIDLibObjPtr->vega(
        mTimeToMaturity
       );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::BlackCalculatorVega) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsNumber()) {
      return Nan::ThrowError("TimeToMaturity is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  double TimeToMaturityCpp = Nan::To<double>(info[1]).FromJust();

 
  // launch worker
  BlackCalculatorVegaWorker* worker = new BlackCalculatorVegaWorker(
    ObjectIDCpp
,     TimeToMaturityCpp
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

void BlackCalculatorRhoWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::BlackCalculator, QuantLib::BlackCalculator)


  // invoke the member function
  mReturnValue = ObjectIDLibObjPtr->rho(
        mTimeToMaturity
       );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::BlackCalculatorRho) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsNumber()) {
      return Nan::ThrowError("TimeToMaturity is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  double TimeToMaturityCpp = Nan::To<double>(info[1]).FromJust();

 
  // launch worker
  BlackCalculatorRhoWorker* worker = new BlackCalculatorRhoWorker(
    ObjectIDCpp
,     TimeToMaturityCpp
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

void BlackCalculatorDividendRhoWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::BlackCalculator, QuantLib::BlackCalculator)


  // invoke the member function
  mReturnValue = ObjectIDLibObjPtr->dividendRho(
        mTimeToMaturity
       );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::BlackCalculatorDividendRho) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsNumber()) {
      return Nan::ThrowError("TimeToMaturity is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  double TimeToMaturityCpp = Nan::To<double>(info[1]).FromJust();

 
  // launch worker
  BlackCalculatorDividendRhoWorker* worker = new BlackCalculatorDividendRhoWorker(
    ObjectIDCpp
,     TimeToMaturityCpp
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

void BlackCalculatorItmCashProbabilityWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::BlackCalculator, QuantLib::BlackCalculator)


  // invoke the member function
  mReturnValue = ObjectIDLibObjPtr->itmCashProbability(
      );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::BlackCalculatorItmCashProbability) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  BlackCalculatorItmCashProbabilityWorker* worker = new BlackCalculatorItmCashProbabilityWorker(
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

void BlackCalculatorItmAssetProbabilityWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::BlackCalculator, QuantLib::BlackCalculator)


  // invoke the member function
  mReturnValue = ObjectIDLibObjPtr->itmAssetProbability(
      );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::BlackCalculatorItmAssetProbability) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  BlackCalculatorItmAssetProbabilityWorker* worker = new BlackCalculatorItmAssetProbabilityWorker(
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

void BlackCalculatorStrikeSensitivityWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::BlackCalculator, QuantLib::BlackCalculator)


  // invoke the member function
  mReturnValue = ObjectIDLibObjPtr->strikeSensitivity(
      );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::BlackCalculatorStrikeSensitivity) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  BlackCalculatorStrikeSensitivityWorker* worker = new BlackCalculatorStrikeSensitivityWorker(
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

void BlackCalculatorAlphaWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::BlackCalculator, QuantLib::BlackCalculator)


  // invoke the member function
  mReturnValue = ObjectIDLibObjPtr->alpha(
      );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::BlackCalculatorAlpha) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  BlackCalculatorAlphaWorker* worker = new BlackCalculatorAlphaWorker(
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

void BlackCalculatorBetaWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::BlackCalculator, QuantLib::BlackCalculator)


  // invoke the member function
  mReturnValue = ObjectIDLibObjPtr->beta(
      );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::BlackCalculatorBeta) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  BlackCalculatorBetaWorker* worker = new BlackCalculatorBetaWorker(
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

void BlackScholesCalculatorDeltaWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::BlackScholesCalculator, QuantLib::BlackScholesCalculator)


  // invoke the member function
  mReturnValue = ObjectIDLibObjPtr->delta(
      );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::BlackScholesCalculatorDelta) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  BlackScholesCalculatorDeltaWorker* worker = new BlackScholesCalculatorDeltaWorker(
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

void BlackScholesCalculatorElasticityWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::BlackScholesCalculator, QuantLib::BlackScholesCalculator)


  // invoke the member function
  mReturnValue = ObjectIDLibObjPtr->elasticity(
      );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::BlackScholesCalculatorElasticity) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  BlackScholesCalculatorElasticityWorker* worker = new BlackScholesCalculatorElasticityWorker(
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

void BlackScholesCalculatorGammaWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::BlackScholesCalculator, QuantLib::BlackScholesCalculator)


  // invoke the member function
  mReturnValue = ObjectIDLibObjPtr->gamma(
      );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::BlackScholesCalculatorGamma) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  BlackScholesCalculatorGammaWorker* worker = new BlackScholesCalculatorGammaWorker(
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

void BlackScholesCalculatorThetaWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::BlackScholesCalculator, QuantLib::BlackScholesCalculator)


  // invoke the member function
  mReturnValue = ObjectIDLibObjPtr->theta(
        mTimeToMaturity
       );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::BlackScholesCalculatorTheta) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsNumber()) {
      return Nan::ThrowError("TimeToMaturity is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  double TimeToMaturityCpp = Nan::To<double>(info[1]).FromJust();

 
  // launch worker
  BlackScholesCalculatorThetaWorker* worker = new BlackScholesCalculatorThetaWorker(
    ObjectIDCpp
,     TimeToMaturityCpp
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

void BlackScholesCalculatorThetaPerDayWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::BlackScholesCalculator, QuantLib::BlackScholesCalculator)


  // invoke the member function
  mReturnValue = ObjectIDLibObjPtr->thetaPerDay(
        mTimeToMaturity
       );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::BlackScholesCalculatorThetaPerDay) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsNumber()) {
      return Nan::ThrowError("TimeToMaturity is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  double TimeToMaturityCpp = Nan::To<double>(info[1]).FromJust();

 
  // launch worker
  BlackScholesCalculatorThetaPerDayWorker* worker = new BlackScholesCalculatorThetaPerDayWorker(
    ObjectIDCpp
,     TimeToMaturityCpp
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

void BlackFormulaWorker::Execute(){

  try{

  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::Option::Type OptionTypeEnum =
      ObjectHandler::Create<QuantLib::Option::Type>()(mOptionType);


  // convert input datatypes to QuantLib datatypes

  // convert input datatypes to QuantLib datatypes

  // convert input datatypes to QuantLib datatypes

  // convert input datatypes to QuantLib datatypes

  // convert input datatypes to QuantLib datatypes
       // invoke the utility function
  QuantLib::Real returnValue = QuantLib::blackFormula(
      OptionTypeEnum
      ,
       mStrike
      ,
       mAtmForwardValue
      ,
       mStdDev
      ,
       mDeflator
      ,
       mDisplacement
     );

  mReturnValue = returnValue;

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::BlackFormula) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("OptionType is required.");
  }
  if (info.Length() == 1 || !info[1]->IsNumber()) {
      return Nan::ThrowError("Strike is required.");
  }
  if (info.Length() == 2 || !info[2]->IsNumber()) {
      return Nan::ThrowError("AtmForwardValue is required.");
  }
  if (info.Length() == 3 || !info[3]->IsNumber()) {
      return Nan::ThrowError("StdDev is required.");
  }
  if (info.Length() == 4 || !info[4]->IsNumber()) {
      return Nan::ThrowError("Deflator is required.");
  }
  if (info.Length() == 5 || !info[5]->IsNumber()) {
      return Nan::ThrowError("Displacement is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strOptionType(info[0]->ToString());
  string OptionTypeCpp(strdup(*strOptionType));

  // convert js argument to c++ type
  double StrikeCpp = Nan::To<double>(info[1]).FromJust();

  // convert js argument to c++ type
  double AtmForwardValueCpp = Nan::To<double>(info[2]).FromJust();

  // convert js argument to c++ type
  double StdDevCpp = Nan::To<double>(info[3]).FromJust();

  // convert js argument to c++ type
  double DeflatorCpp = Nan::To<double>(info[4]).FromJust();

  // convert js argument to c++ type
  double DisplacementCpp = Nan::To<double>(info[5]).FromJust();

 
  // launch worker
  BlackFormulaWorker* worker = new BlackFormulaWorker(
    OptionTypeCpp
,     StrikeCpp
,     AtmForwardValueCpp
,     StdDevCpp
,     DeflatorCpp
,     DisplacementCpp
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

void BlackFormulaCashItmProbabilityWorker::Execute(){

  try{

  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::Option::Type OptionTypeEnum =
      ObjectHandler::Create<QuantLib::Option::Type>()(mOptionType);


  // convert input datatypes to QuantLib datatypes

  // convert input datatypes to QuantLib datatypes

  // convert input datatypes to QuantLib datatypes

  // convert input datatypes to QuantLib datatypes
       // invoke the utility function
  QuantLib::Real returnValue = QuantLib::blackFormulaCashItmProbability(
      OptionTypeEnum
      ,
       mStrike
      ,
       mAtmForwardValue
      ,
       mStdDev
      ,
       mDisplacement
     );

  mReturnValue = returnValue;

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::BlackFormulaCashItmProbability) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("OptionType is required.");
  }
  if (info.Length() == 1 || !info[1]->IsNumber()) {
      return Nan::ThrowError("Strike is required.");
  }
  if (info.Length() == 2 || !info[2]->IsNumber()) {
      return Nan::ThrowError("AtmForwardValue is required.");
  }
  if (info.Length() == 3 || !info[3]->IsNumber()) {
      return Nan::ThrowError("StdDev is required.");
  }
  if (info.Length() == 4 || !info[4]->IsNumber()) {
      return Nan::ThrowError("Displacement is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strOptionType(info[0]->ToString());
  string OptionTypeCpp(strdup(*strOptionType));

  // convert js argument to c++ type
  double StrikeCpp = Nan::To<double>(info[1]).FromJust();

  // convert js argument to c++ type
  double AtmForwardValueCpp = Nan::To<double>(info[2]).FromJust();

  // convert js argument to c++ type
  double StdDevCpp = Nan::To<double>(info[3]).FromJust();

  // convert js argument to c++ type
  double DisplacementCpp = Nan::To<double>(info[4]).FromJust();

 
  // launch worker
  BlackFormulaCashItmProbabilityWorker* worker = new BlackFormulaCashItmProbabilityWorker(
    OptionTypeCpp
,     StrikeCpp
,     AtmForwardValueCpp
,     StdDevCpp
,     DisplacementCpp
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

void BlackFormulaImpliedStdDevApproximationWorker::Execute(){

  try{

  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::Option::Type OptionTypeEnum =
      ObjectHandler::Create<QuantLib::Option::Type>()(mOptionType);


  // convert input datatypes to QuantLib datatypes

  // convert input datatypes to QuantLib datatypes

  // convert input datatypes to QuantLib datatypes

  // convert input datatypes to QuantLib datatypes

  // convert input datatypes to QuantLib datatypes
       // invoke the utility function
  QuantLib::Real returnValue = QuantLib::blackFormulaImpliedStdDevApproximation(
      OptionTypeEnum
      ,
       mStrike
      ,
       mAtmForwardValue
      ,
       mOptionPrice
      ,
       mDeflator
      ,
       mDisplacement
     );

  mReturnValue = returnValue;

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::BlackFormulaImpliedStdDevApproximation) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("OptionType is required.");
  }
  if (info.Length() == 1 || !info[1]->IsNumber()) {
      return Nan::ThrowError("Strike is required.");
  }
  if (info.Length() == 2 || !info[2]->IsNumber()) {
      return Nan::ThrowError("AtmForwardValue is required.");
  }
  if (info.Length() == 3 || !info[3]->IsNumber()) {
      return Nan::ThrowError("OptionPrice is required.");
  }
  if (info.Length() == 4 || !info[4]->IsNumber()) {
      return Nan::ThrowError("Deflator is required.");
  }
  if (info.Length() == 5 || !info[5]->IsNumber()) {
      return Nan::ThrowError("Displacement is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strOptionType(info[0]->ToString());
  string OptionTypeCpp(strdup(*strOptionType));

  // convert js argument to c++ type
  double StrikeCpp = Nan::To<double>(info[1]).FromJust();

  // convert js argument to c++ type
  double AtmForwardValueCpp = Nan::To<double>(info[2]).FromJust();

  // convert js argument to c++ type
  double OptionPriceCpp = Nan::To<double>(info[3]).FromJust();

  // convert js argument to c++ type
  double DeflatorCpp = Nan::To<double>(info[4]).FromJust();

  // convert js argument to c++ type
  double DisplacementCpp = Nan::To<double>(info[5]).FromJust();

 
  // launch worker
  BlackFormulaImpliedStdDevApproximationWorker* worker = new BlackFormulaImpliedStdDevApproximationWorker(
    OptionTypeCpp
,     StrikeCpp
,     AtmForwardValueCpp
,     OptionPriceCpp
,     DeflatorCpp
,     DisplacementCpp
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

void BlackFormulaImpliedStdDevWorker::Execute(){

  try{

  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::Option::Type OptionTypeEnum =
      ObjectHandler::Create<QuantLib::Option::Type>()(mOptionType);


  // convert input datatypes to QuantLib datatypes

  // convert input datatypes to QuantLib datatypes

  // convert input datatypes to QuantLib datatypes

  // convert input datatypes to QuantLib datatypes

  // convert input datatypes to QuantLib datatypes

  // convert input datatypes to QuantLib datatypes

  // convert input datatypes to QuantLib datatypes

  // convert input datatypes to QuantLib datatypes
  QuantLib::Natural MaxIterLib = ObjectHandler::convert2<long>(
      mMaxIter, "MaxIter", QuantLib::Null<QuantLib::Natural>());

       // invoke the utility function
  QuantLib::Real returnValue = QuantLib::blackFormulaImpliedStdDev(
      OptionTypeEnum
      ,
       mStrike
      ,
       mAtmForwardValue
      ,
       mOptionPrice
      ,
       mDeflator
      ,
       mDisplacement
      ,
       mGuess
      ,
       mAccuracy
      ,
       MaxIterLib
     );

  mReturnValue = returnValue;

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::BlackFormulaImpliedStdDev) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("OptionType is required.");
  }
  if (info.Length() == 1 || !info[1]->IsNumber()) {
      return Nan::ThrowError("Strike is required.");
  }
  if (info.Length() == 2 || !info[2]->IsNumber()) {
      return Nan::ThrowError("AtmForwardValue is required.");
  }
  if (info.Length() == 3 || !info[3]->IsNumber()) {
      return Nan::ThrowError("OptionPrice is required.");
  }
  if (info.Length() == 4 || !info[4]->IsNumber()) {
      return Nan::ThrowError("Deflator is required.");
  }
  if (info.Length() == 5 || !info[5]->IsNumber()) {
      return Nan::ThrowError("Displacement is required.");
  }
  if (info.Length() == 6 || !info[6]->IsNumber()) {
      return Nan::ThrowError("Guess is required.");
  }
  if (info.Length() == 7 || !info[7]->IsNumber()) {
      return Nan::ThrowError("Accuracy is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strOptionType(info[0]->ToString());
  string OptionTypeCpp(strdup(*strOptionType));

  // convert js argument to c++ type
  double StrikeCpp = Nan::To<double>(info[1]).FromJust();

  // convert js argument to c++ type
  double AtmForwardValueCpp = Nan::To<double>(info[2]).FromJust();

  // convert js argument to c++ type
  double OptionPriceCpp = Nan::To<double>(info[3]).FromJust();

  // convert js argument to c++ type
  double DeflatorCpp = Nan::To<double>(info[4]).FromJust();

  // convert js argument to c++ type
  double DisplacementCpp = Nan::To<double>(info[5]).FromJust();

  // convert js argument to c++ type
  double GuessCpp = Nan::To<double>(info[6]).FromJust();

  // convert js argument to c++ type
  double AccuracyCpp = Nan::To<double>(info[7]).FromJust();

  // convert js argument to c++ type
  ObjectHandler::property_t MaxIterCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[8]).FromJust()));

 
  // launch worker
  BlackFormulaImpliedStdDevWorker* worker = new BlackFormulaImpliedStdDevWorker(
    OptionTypeCpp
,     StrikeCpp
,     AtmForwardValueCpp
,     OptionPriceCpp
,     DeflatorCpp
,     DisplacementCpp
,     GuessCpp
,     AccuracyCpp
,     MaxIterCpp
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

void BlackFormulaStdDevDerivativeWorker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes

  // convert input datatypes to QuantLib datatypes

  // convert input datatypes to QuantLib datatypes

  // convert input datatypes to QuantLib datatypes

  // convert input datatypes to QuantLib datatypes
       // invoke the utility function
  QuantLib::Real returnValue = QuantLib::blackFormulaStdDevDerivative(
      mStrike
      ,
       mAtmForwardValue
      ,
       mStdDev
      ,
       mDeflator
      ,
       mDisplacement
     );

  mReturnValue = returnValue;

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::BlackFormulaStdDevDerivative) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsNumber()) {
      return Nan::ThrowError("Strike is required.");
  }
  if (info.Length() == 1 || !info[1]->IsNumber()) {
      return Nan::ThrowError("AtmForwardValue is required.");
  }
  if (info.Length() == 2 || !info[2]->IsNumber()) {
      return Nan::ThrowError("StdDev is required.");
  }
  if (info.Length() == 3 || !info[3]->IsNumber()) {
      return Nan::ThrowError("Deflator is required.");
  }
  if (info.Length() == 4 || !info[4]->IsNumber()) {
      return Nan::ThrowError("Displacement is required.");
  }
  // convert js argument to c++ type
  double StrikeCpp = Nan::To<double>(info[0]).FromJust();

  // convert js argument to c++ type
  double AtmForwardValueCpp = Nan::To<double>(info[1]).FromJust();

  // convert js argument to c++ type
  double StdDevCpp = Nan::To<double>(info[2]).FromJust();

  // convert js argument to c++ type
  double DeflatorCpp = Nan::To<double>(info[3]).FromJust();

  // convert js argument to c++ type
  double DisplacementCpp = Nan::To<double>(info[4]).FromJust();

 
  // launch worker
  BlackFormulaStdDevDerivativeWorker* worker = new BlackFormulaStdDevDerivativeWorker(
    StrikeCpp
,     AtmForwardValueCpp
,     StdDevCpp
,     DeflatorCpp
,     DisplacementCpp
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

void BachelierBlackFormulaWorker::Execute(){

  try{

  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::Option::Type OptionTypeEnum =
      ObjectHandler::Create<QuantLib::Option::Type>()(mOptionType);


  // convert input datatypes to QuantLib datatypes

  // convert input datatypes to QuantLib datatypes

  // convert input datatypes to QuantLib datatypes

  // convert input datatypes to QuantLib datatypes
       // invoke the utility function
  QuantLib::Real returnValue = QuantLib::bachelierBlackFormula(
      OptionTypeEnum
      ,
       mStrike
      ,
       mAtmForwardValue
      ,
       mStdDev
      ,
       mDeflator
     );

  mReturnValue = returnValue;

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::BachelierBlackFormula) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("OptionType is required.");
  }
  if (info.Length() == 1 || !info[1]->IsNumber()) {
      return Nan::ThrowError("Strike is required.");
  }
  if (info.Length() == 2 || !info[2]->IsNumber()) {
      return Nan::ThrowError("AtmForwardValue is required.");
  }
  if (info.Length() == 3 || !info[3]->IsNumber()) {
      return Nan::ThrowError("StdDev is required.");
  }
  if (info.Length() == 4 || !info[4]->IsNumber()) {
      return Nan::ThrowError("Deflator is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strOptionType(info[0]->ToString());
  string OptionTypeCpp(strdup(*strOptionType));

  // convert js argument to c++ type
  double StrikeCpp = Nan::To<double>(info[1]).FromJust();

  // convert js argument to c++ type
  double AtmForwardValueCpp = Nan::To<double>(info[2]).FromJust();

  // convert js argument to c++ type
  double StdDevCpp = Nan::To<double>(info[3]).FromJust();

  // convert js argument to c++ type
  double DeflatorCpp = Nan::To<double>(info[4]).FromJust();

 
  // launch worker
  BachelierBlackFormulaWorker* worker = new BachelierBlackFormulaWorker(
    OptionTypeCpp
,     StrikeCpp
,     AtmForwardValueCpp
,     StdDevCpp
,     DeflatorCpp
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

void BachelierBlackFormulaImpliedVolWorker::Execute(){

  try{

  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::Option::Type OptionTypeEnum =
      ObjectHandler::Create<QuantLib::Option::Type>()(mOptionType);


  // convert input datatypes to QuantLib datatypes

  // convert input datatypes to QuantLib datatypes

  // convert input datatypes to QuantLib datatypes

  // convert input datatypes to QuantLib datatypes

  // convert input datatypes to QuantLib datatypes
       // invoke the utility function
  QuantLib::Real returnValue = QuantLib::bachelierBlackFormulaImpliedVol(
      OptionTypeEnum
      ,
       mStrike
      ,
       mAtmForwardValue
      ,
       mTimeToExpiry
      ,
       mOptionPrice
      ,
       mDeflator
     );

  mReturnValue = returnValue;

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::BachelierBlackFormulaImpliedVol) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("OptionType is required.");
  }
  if (info.Length() == 1 || !info[1]->IsNumber()) {
      return Nan::ThrowError("Strike is required.");
  }
  if (info.Length() == 2 || !info[2]->IsNumber()) {
      return Nan::ThrowError("AtmForwardValue is required.");
  }
  if (info.Length() == 3 || !info[3]->IsNumber()) {
      return Nan::ThrowError("TimeToExpiry is required.");
  }
  if (info.Length() == 4 || !info[4]->IsNumber()) {
      return Nan::ThrowError("OptionPrice is required.");
  }
  if (info.Length() == 5 || !info[5]->IsNumber()) {
      return Nan::ThrowError("Deflator is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strOptionType(info[0]->ToString());
  string OptionTypeCpp(strdup(*strOptionType));

  // convert js argument to c++ type
  double StrikeCpp = Nan::To<double>(info[1]).FromJust();

  // convert js argument to c++ type
  double AtmForwardValueCpp = Nan::To<double>(info[2]).FromJust();

  // convert js argument to c++ type
  double TimeToExpiryCpp = Nan::To<double>(info[3]).FromJust();

  // convert js argument to c++ type
  double OptionPriceCpp = Nan::To<double>(info[4]).FromJust();

  // convert js argument to c++ type
  double DeflatorCpp = Nan::To<double>(info[5]).FromJust();

 
  // launch worker
  BachelierBlackFormulaImpliedVolWorker* worker = new BachelierBlackFormulaImpliedVolWorker(
    OptionTypeCpp
,     StrikeCpp
,     AtmForwardValueCpp
,     TimeToExpiryCpp
,     OptionPriceCpp
,     DeflatorCpp
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

void BlackFormula2Worker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_REFERENCE(PayoffLibObjPtr, mPayoff,
      QuantLibAddin::PlainVanillaPayoff, QuantLib::PlainVanillaPayoff)


  // convert input datatypes to QuantLib datatypes

  // convert input datatypes to QuantLib datatypes

  // convert input datatypes to QuantLib datatypes

  // convert input datatypes to QuantLib datatypes
       // invoke the utility function
  QuantLib::Real returnValue = QuantLib::blackFormula(
      PayoffLibObjPtr
      ,
       mAtmForwardValue
      ,
       mStdDev
      ,
       mDeflator
      ,
       mDisplacement
     );

  mReturnValue = returnValue;

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::BlackFormula2) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("Payoff is required.");
  }
  if (info.Length() == 1 || !info[1]->IsNumber()) {
      return Nan::ThrowError("AtmForwardValue is required.");
  }
  if (info.Length() == 2 || !info[2]->IsNumber()) {
      return Nan::ThrowError("StdDev is required.");
  }
  if (info.Length() == 3 || !info[3]->IsNumber()) {
      return Nan::ThrowError("Deflator is required.");
  }
  if (info.Length() == 4 || !info[4]->IsNumber()) {
      return Nan::ThrowError("Displacement is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strPayoff(info[0]->ToString());
  string PayoffCpp(strdup(*strPayoff));

  // convert js argument to c++ type
  double AtmForwardValueCpp = Nan::To<double>(info[1]).FromJust();

  // convert js argument to c++ type
  double StdDevCpp = Nan::To<double>(info[2]).FromJust();

  // convert js argument to c++ type
  double DeflatorCpp = Nan::To<double>(info[3]).FromJust();

  // convert js argument to c++ type
  double DisplacementCpp = Nan::To<double>(info[4]).FromJust();

 
  // launch worker
  BlackFormula2Worker* worker = new BlackFormula2Worker(
    PayoffCpp
,     AtmForwardValueCpp
,     StdDevCpp
,     DeflatorCpp
,     DisplacementCpp
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

void BlackFormulaCashItmProbability2Worker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_REFERENCE(PayoffLibObjPtr, mPayoff,
      QuantLibAddin::PlainVanillaPayoff, QuantLib::PlainVanillaPayoff)


  // convert input datatypes to QuantLib datatypes

  // convert input datatypes to QuantLib datatypes

  // convert input datatypes to QuantLib datatypes
       // invoke the utility function
  QuantLib::Real returnValue = QuantLib::blackFormulaCashItmProbability(
      PayoffLibObjPtr
      ,
       mAtmForwardValue
      ,
       mStdDev
      ,
       mDisplacement
     );

  mReturnValue = returnValue;

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::BlackFormulaCashItmProbability2) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("Payoff is required.");
  }
  if (info.Length() == 1 || !info[1]->IsNumber()) {
      return Nan::ThrowError("AtmForwardValue is required.");
  }
  if (info.Length() == 2 || !info[2]->IsNumber()) {
      return Nan::ThrowError("StdDev is required.");
  }
  if (info.Length() == 3 || !info[3]->IsNumber()) {
      return Nan::ThrowError("Displacement is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strPayoff(info[0]->ToString());
  string PayoffCpp(strdup(*strPayoff));

  // convert js argument to c++ type
  double AtmForwardValueCpp = Nan::To<double>(info[1]).FromJust();

  // convert js argument to c++ type
  double StdDevCpp = Nan::To<double>(info[2]).FromJust();

  // convert js argument to c++ type
  double DisplacementCpp = Nan::To<double>(info[3]).FromJust();

 
  // launch worker
  BlackFormulaCashItmProbability2Worker* worker = new BlackFormulaCashItmProbability2Worker(
    PayoffCpp
,     AtmForwardValueCpp
,     StdDevCpp
,     DisplacementCpp
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

void BlackFormulaImpliedStdDevApproximation2Worker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_REFERENCE(PayoffLibObjPtr, mPayoff,
      QuantLibAddin::PlainVanillaPayoff, QuantLib::PlainVanillaPayoff)


  // convert input datatypes to QuantLib datatypes

  // convert input datatypes to QuantLib datatypes

  // convert input datatypes to QuantLib datatypes

  // convert input datatypes to QuantLib datatypes
       // invoke the utility function
  QuantLib::Real returnValue = QuantLib::blackFormulaImpliedStdDevApproximation(
      PayoffLibObjPtr
      ,
       mAtmForwardValue
      ,
       mOptionPrice
      ,
       mDeflator
      ,
       mDisplacement
     );

  mReturnValue = returnValue;

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::BlackFormulaImpliedStdDevApproximation2) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("Payoff is required.");
  }
  if (info.Length() == 1 || !info[1]->IsNumber()) {
      return Nan::ThrowError("AtmForwardValue is required.");
  }
  if (info.Length() == 2 || !info[2]->IsNumber()) {
      return Nan::ThrowError("OptionPrice is required.");
  }
  if (info.Length() == 3 || !info[3]->IsNumber()) {
      return Nan::ThrowError("Deflator is required.");
  }
  if (info.Length() == 4 || !info[4]->IsNumber()) {
      return Nan::ThrowError("Displacement is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strPayoff(info[0]->ToString());
  string PayoffCpp(strdup(*strPayoff));

  // convert js argument to c++ type
  double AtmForwardValueCpp = Nan::To<double>(info[1]).FromJust();

  // convert js argument to c++ type
  double OptionPriceCpp = Nan::To<double>(info[2]).FromJust();

  // convert js argument to c++ type
  double DeflatorCpp = Nan::To<double>(info[3]).FromJust();

  // convert js argument to c++ type
  double DisplacementCpp = Nan::To<double>(info[4]).FromJust();

 
  // launch worker
  BlackFormulaImpliedStdDevApproximation2Worker* worker = new BlackFormulaImpliedStdDevApproximation2Worker(
    PayoffCpp
,     AtmForwardValueCpp
,     OptionPriceCpp
,     DeflatorCpp
,     DisplacementCpp
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

void BlackFormulaImpliedStdDev2Worker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_REFERENCE(PayoffIDLibObjPtr, mPayoffID,
      QuantLibAddin::PlainVanillaPayoff, QuantLib::PlainVanillaPayoff)


  // convert input datatypes to QuantLib datatypes

  // convert input datatypes to QuantLib datatypes

  // convert input datatypes to QuantLib datatypes

  // convert input datatypes to QuantLib datatypes

  // convert input datatypes to QuantLib datatypes

  // convert input datatypes to QuantLib datatypes

  // convert input datatypes to QuantLib datatypes
  QuantLib::Natural MaxIterLib = ObjectHandler::convert2<long>(
      mMaxIter, "MaxIter", QuantLib::Null<QuantLib::Natural>());

       // invoke the utility function
  QuantLib::Real returnValue = QuantLib::blackFormulaImpliedStdDev(
      PayoffIDLibObjPtr
      ,
       mAtmForwardValue
      ,
       mOptionPrice
      ,
       mDeflator
      ,
       mDisplacement
      ,
       mGuess
      ,
       mAccuracy
      ,
       MaxIterLib
     );

  mReturnValue = returnValue;

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::BlackFormulaImpliedStdDev2) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("PayoffID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsNumber()) {
      return Nan::ThrowError("AtmForwardValue is required.");
  }
  if (info.Length() == 2 || !info[2]->IsNumber()) {
      return Nan::ThrowError("OptionPrice is required.");
  }
  if (info.Length() == 3 || !info[3]->IsNumber()) {
      return Nan::ThrowError("Deflator is required.");
  }
  if (info.Length() == 4 || !info[4]->IsNumber()) {
      return Nan::ThrowError("Displacement is required.");
  }
  if (info.Length() == 5 || !info[5]->IsNumber()) {
      return Nan::ThrowError("Guess is required.");
  }
  if (info.Length() == 6 || !info[6]->IsNumber()) {
      return Nan::ThrowError("Accuracy is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strPayoffID(info[0]->ToString());
  string PayoffIDCpp(strdup(*strPayoffID));

  // convert js argument to c++ type
  double AtmForwardValueCpp = Nan::To<double>(info[1]).FromJust();

  // convert js argument to c++ type
  double OptionPriceCpp = Nan::To<double>(info[2]).FromJust();

  // convert js argument to c++ type
  double DeflatorCpp = Nan::To<double>(info[3]).FromJust();

  // convert js argument to c++ type
  double DisplacementCpp = Nan::To<double>(info[4]).FromJust();

  // convert js argument to c++ type
  double GuessCpp = Nan::To<double>(info[5]).FromJust();

  // convert js argument to c++ type
  double AccuracyCpp = Nan::To<double>(info[6]).FromJust();

  // convert js argument to c++ type
  ObjectHandler::property_t MaxIterCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[7]).FromJust()));

 
  // launch worker
  BlackFormulaImpliedStdDev2Worker* worker = new BlackFormulaImpliedStdDev2Worker(
    PayoffIDCpp
,     AtmForwardValueCpp
,     OptionPriceCpp
,     DeflatorCpp
,     DisplacementCpp
,     GuessCpp
,     AccuracyCpp
,     MaxIterCpp
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

void BlackFormulaStdDevDerivative2Worker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_REFERENCE(PayoffIDLibObjPtr, mPayoffID,
      QuantLibAddin::PlainVanillaPayoff, QuantLib::PlainVanillaPayoff)


  // convert input datatypes to QuantLib datatypes

  // convert input datatypes to QuantLib datatypes

  // convert input datatypes to QuantLib datatypes

  // convert input datatypes to QuantLib datatypes
       // invoke the utility function
  QuantLib::Real returnValue = QuantLib::blackFormulaStdDevDerivative(
      PayoffIDLibObjPtr
      ,
       mAtmForwardValue
      ,
       mStdDev
      ,
       mDeflator
      ,
       mDisplacement
     );

  mReturnValue = returnValue;

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::BlackFormulaStdDevDerivative2) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("PayoffID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsNumber()) {
      return Nan::ThrowError("AtmForwardValue is required.");
  }
  if (info.Length() == 2 || !info[2]->IsNumber()) {
      return Nan::ThrowError("StdDev is required.");
  }
  if (info.Length() == 3 || !info[3]->IsNumber()) {
      return Nan::ThrowError("Deflator is required.");
  }
  if (info.Length() == 4 || !info[4]->IsNumber()) {
      return Nan::ThrowError("Displacement is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strPayoffID(info[0]->ToString());
  string PayoffIDCpp(strdup(*strPayoffID));

  // convert js argument to c++ type
  double AtmForwardValueCpp = Nan::To<double>(info[1]).FromJust();

  // convert js argument to c++ type
  double StdDevCpp = Nan::To<double>(info[2]).FromJust();

  // convert js argument to c++ type
  double DeflatorCpp = Nan::To<double>(info[3]).FromJust();

  // convert js argument to c++ type
  double DisplacementCpp = Nan::To<double>(info[4]).FromJust();

 
  // launch worker
  BlackFormulaStdDevDerivative2Worker* worker = new BlackFormulaStdDevDerivative2Worker(
    PayoffIDCpp
,     AtmForwardValueCpp
,     StdDevCpp
,     DeflatorCpp
,     DisplacementCpp
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

void BachelierBlackFormula2Worker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_REFERENCE(PayoffLibObjPtr, mPayoff,
      QuantLibAddin::PlainVanillaPayoff, QuantLib::PlainVanillaPayoff)


  // convert input datatypes to QuantLib datatypes

  // convert input datatypes to QuantLib datatypes

  // convert input datatypes to QuantLib datatypes
       // invoke the utility function
  QuantLib::Real returnValue = QuantLib::bachelierBlackFormula(
      PayoffLibObjPtr
      ,
       mAtmForwardValue
      ,
       mStdDev
      ,
       mDeflator
     );

  mReturnValue = returnValue;

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::BachelierBlackFormula2) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("Payoff is required.");
  }
  if (info.Length() == 1 || !info[1]->IsNumber()) {
      return Nan::ThrowError("AtmForwardValue is required.");
  }
  if (info.Length() == 2 || !info[2]->IsNumber()) {
      return Nan::ThrowError("StdDev is required.");
  }
  if (info.Length() == 3 || !info[3]->IsNumber()) {
      return Nan::ThrowError("Deflator is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strPayoff(info[0]->ToString());
  string PayoffCpp(strdup(*strPayoff));

  // convert js argument to c++ type
  double AtmForwardValueCpp = Nan::To<double>(info[1]).FromJust();

  // convert js argument to c++ type
  double StdDevCpp = Nan::To<double>(info[2]).FromJust();

  // convert js argument to c++ type
  double DeflatorCpp = Nan::To<double>(info[3]).FromJust();

 
  // launch worker
  BachelierBlackFormula2Worker* worker = new BachelierBlackFormula2Worker(
    PayoffCpp
,     AtmForwardValueCpp
,     StdDevCpp
,     DeflatorCpp
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
 