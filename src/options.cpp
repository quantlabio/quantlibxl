/* 
  Copyright (C) 2016 -2017 Jerry Jin
*/

#include <nan.h>
#include <string.h>

#include "options.hpp"

#include <qlo/qladdindefines.hpp>
#include <qlo/options.hpp>
#include <qlo/payoffs.hpp>
#include <qlo/exercise.hpp>
#include <ql/instruments/oneassetoption.hpp>
 #include <oh/objecthandler.hpp>
#include <oh/conversions/getobjectvector.hpp>
#include <qlo/valueobjects/vo_all.hpp>
#include <qlo/conversions/all.hpp>
#include "../loop.hpp"


void BarrierOptionWorker::Execute(){

  try{

  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::Barrier::Type BarrierTypeEnum =
      ObjectHandler::Create<QuantLib::Barrier::Type>()(mBarrierType);


  // convert input datatypes to QuantLib datatypes

  // convert input datatypes to QuantLib datatypes

  // convert object IDs into library objects
  OH_GET_REFERENCE(PayoffLibObjPtr, mPayoff,
      QuantLibAddin::StrikedTypePayoff, QuantLib::StrikedTypePayoff)


  // convert object IDs into library objects
  OH_GET_REFERENCE(ExerciseLibObjPtr, mExercise,
      QuantLibAddin::Exercise, QuantLib::Exercise)

 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlBarrierOption(
          mObjectID,
          mBarrierType,
          mBarrier,
          mRebate,
          mPayoff,
          mExercise,
          false
      ));

    // Construct the Object
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::BarrierOption(
          valueObject,
          BarrierTypeEnum,
          mBarrier,
          mRebate,
          PayoffLibObjPtr,
          ExerciseLibObjPtr,
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

NAN_METHOD(QuantLibXL::BarrierOption) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsString()) {
      return Nan::ThrowError("BarrierType is required.");
  }
  if (info.Length() == 2 || !info[2]->IsNumber()) {
      return Nan::ThrowError("Barrier is required.");
  }
  if (info.Length() == 3 || !info[3]->IsNumber()) {
      return Nan::ThrowError("Rebate is required.");
  }
  if (info.Length() == 4 || !info[4]->IsString()) {
      return Nan::ThrowError("Payoff is required.");
  }
  if (info.Length() == 5 || !info[5]->IsString()) {
      return Nan::ThrowError("Exercise is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  String::Utf8Value strBarrierType(info[1]->ToString());
  string BarrierTypeCpp(strdup(*strBarrierType));

  // convert js argument to c++ type
  double BarrierCpp = Nan::To<double>(info[2]).FromJust();

  // convert js argument to c++ type
  double RebateCpp = Nan::To<double>(info[3]).FromJust();

  // convert js argument to c++ type
  String::Utf8Value strPayoff(info[4]->ToString());
  string PayoffCpp(strdup(*strPayoff));

  // convert js argument to c++ type
  String::Utf8Value strExercise(info[5]->ToString());
  string ExerciseCpp(strdup(*strExercise));

 
  // launch worker
  BarrierOptionWorker* worker = new BarrierOptionWorker(
    ObjectIDCpp
,     BarrierTypeCpp
,     BarrierCpp
,     RebateCpp
,     PayoffCpp
,     ExerciseCpp
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

void CaAsianOptionWorker::Execute(){

  try{

  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::Average::Type AverageTypeEnum =
      ObjectHandler::Create<QuantLib::Average::Type>()(mAverageType);


  // convert object IDs into library objects
  OH_GET_REFERENCE(PayoffLibObjPtr, mPayoff,
      QuantLibAddin::StrikedTypePayoff, QuantLib::StrikedTypePayoff)


  // convert object IDs into library objects
  OH_GET_REFERENCE(ExerciseLibObjPtr, mExercise,
      QuantLibAddin::Exercise, QuantLib::Exercise)

 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlCaAsianOption(
          mObjectID,
          mAverageType,
          mPayoff,
          mExercise,
          false
      ));

    // Construct the Object
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::ContinuousAveragingAsianOption(
          valueObject,
          AverageTypeEnum,
          PayoffLibObjPtr,
          ExerciseLibObjPtr,
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

NAN_METHOD(QuantLibXL::CaAsianOption) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsString()) {
      return Nan::ThrowError("AverageType is required.");
  }
  if (info.Length() == 2 || !info[2]->IsString()) {
      return Nan::ThrowError("Payoff is required.");
  }
  if (info.Length() == 3 || !info[3]->IsString()) {
      return Nan::ThrowError("Exercise is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  String::Utf8Value strAverageType(info[1]->ToString());
  string AverageTypeCpp(strdup(*strAverageType));

  // convert js argument to c++ type
  String::Utf8Value strPayoff(info[2]->ToString());
  string PayoffCpp(strdup(*strPayoff));

  // convert js argument to c++ type
  String::Utf8Value strExercise(info[3]->ToString());
  string ExerciseCpp(strdup(*strExercise));

 
  // launch worker
  CaAsianOptionWorker* worker = new CaAsianOptionWorker(
    ObjectIDCpp
,     AverageTypeCpp
,     PayoffCpp
,     ExerciseCpp
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

void DaAsianOptionWorker::Execute(){

  try{

  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::Average::Type AverageTypeEnum =
      ObjectHandler::Create<QuantLib::Average::Type>()(mAverageType);


  // convert input datatypes to QuantLib datatypes

  // convert input datatypes to QuantLib datatypes
  QuantLib::Size PastFixingsLib;
  QuantLibAddin::cppToLibrary(mPastFixings, PastFixingsLib);


  // convert input datatypes to QuantLib datatypes
  std::vector<QuantLib::Date> FixingDatesLib = ObjectHandler::vector::convert2<QuantLib::Date>(
      mFixingDates, "FixingDates");


  // convert object IDs into library objects
  OH_GET_REFERENCE(PayoffLibObjPtr, mPayoff,
      QuantLibAddin::StrikedTypePayoff, QuantLib::StrikedTypePayoff)


  // convert object IDs into library objects
  OH_GET_REFERENCE(ExerciseLibObjPtr, mExercise,
      QuantLibAddin::Exercise, QuantLib::Exercise)

 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlDaAsianOption(
          mObjectID,
          mAverageType,
          mRunningAccumulator,
          mPastFixings,
          mFixingDates,
          mPayoff,
          mExercise,
          false
      ));

    // Construct the Object
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::DiscreteAveragingAsianOption(
          valueObject,
          AverageTypeEnum,
          mRunningAccumulator,
          PastFixingsLib,
          FixingDatesLib,
          PayoffLibObjPtr,
          ExerciseLibObjPtr,
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

NAN_METHOD(QuantLibXL::DaAsianOption) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsString()) {
      return Nan::ThrowError("AverageType is required.");
  }
  if (info.Length() == 2 || !info[2]->IsNumber()) {
      return Nan::ThrowError("RunningAccumulator is required.");
  }
  if (info.Length() == 3 || !info[3]->IsNumber()) {
      return Nan::ThrowError("PastFixings is required.");
  }
  if (info.Length() == 4 || !info[4]->IsArray()) {
      return Nan::ThrowError("FixingDates is required.");
  }
  if (info.Length() == 5 || !info[5]->IsString()) {
      return Nan::ThrowError("Payoff is required.");
  }
  if (info.Length() == 6 || !info[6]->IsString()) {
      return Nan::ThrowError("Exercise is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  String::Utf8Value strAverageType(info[1]->ToString());
  string AverageTypeCpp(strdup(*strAverageType));

  // convert js argument to c++ type
  double RunningAccumulatorCpp = Nan::To<double>(info[2]).FromJust();

  // convert js argument to c++ type
  long PastFixingsCpp = Nan::To<int32_t>(info[3]).FromJust();

  // convert js argument to c++ type
  std::vector<ObjectHandler::property_t>FixingDatesCpp;

  Local<Array> FixingDatesArray = info[4].As<Array>();
  for (unsigned int i = 0; i < FixingDatesArray->Length(); i++){
    ObjectHandler::property_t tmp =
        ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(Nan::Get(FixingDatesArray, i).ToLocalChecked()).FromJust()));
    FixingDatesCpp.push_back(tmp);
  }

  // convert js argument to c++ type
  String::Utf8Value strPayoff(info[5]->ToString());
  string PayoffCpp(strdup(*strPayoff));

  // convert js argument to c++ type
  String::Utf8Value strExercise(info[6]->ToString());
  string ExerciseCpp(strdup(*strExercise));

 
  // launch worker
  DaAsianOptionWorker* worker = new DaAsianOptionWorker(
    ObjectIDCpp
,     AverageTypeCpp
,     RunningAccumulatorCpp
,     PastFixingsCpp
,     FixingDatesCpp
,     PayoffCpp
,     ExerciseCpp
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

void DividendVanillaOptionWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_REFERENCE(PayoffLibObjPtr, mPayoff,
      QuantLibAddin::StrikedTypePayoff, QuantLib::StrikedTypePayoff)


  // convert object IDs into library objects
  OH_GET_REFERENCE(ExerciseLibObjPtr, mExercise,
      QuantLibAddin::Exercise, QuantLib::Exercise)


  // convert input datatypes to QuantLib datatypes
  std::vector<QuantLib::Date> DividendDatesLib = ObjectHandler::vector::convert2<QuantLib::Date>(
      mDividendDates, "DividendDates");


  // convert input datatypes to QuantLib datatypes
  std::vector<QuantLib::Real> DividendsLib =
      QuantLibAddin::convertVector<double, QuantLib::Real>(mDividends);

 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlDividendVanillaOption(
          mObjectID,
          mPayoff,
          mExercise,
          mDividendDates,
          mDividends,
          false
      ));

    // Construct the Object
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::DividendVanillaOption(
          valueObject,
          PayoffLibObjPtr,
          ExerciseLibObjPtr,
          DividendDatesLib,
          mDividends,
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

NAN_METHOD(QuantLibXL::DividendVanillaOption) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsString()) {
      return Nan::ThrowError("Payoff is required.");
  }
  if (info.Length() == 2 || !info[2]->IsString()) {
      return Nan::ThrowError("Exercise is required.");
  }
  if (info.Length() == 3 || !info[3]->IsArray()) {
      return Nan::ThrowError("DividendDates is required.");
  }
  if (info.Length() == 4 || !info[4]->IsArray()) {
      return Nan::ThrowError("Dividends is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  String::Utf8Value strPayoff(info[1]->ToString());
  string PayoffCpp(strdup(*strPayoff));

  // convert js argument to c++ type
  String::Utf8Value strExercise(info[2]->ToString());
  string ExerciseCpp(strdup(*strExercise));

  // convert js argument to c++ type
  std::vector<ObjectHandler::property_t>DividendDatesCpp;

  Local<Array> DividendDatesArray = info[3].As<Array>();
  for (unsigned int i = 0; i < DividendDatesArray->Length(); i++){
    ObjectHandler::property_t tmp =
        ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(Nan::Get(DividendDatesArray, i).ToLocalChecked()).FromJust()));
    DividendDatesCpp.push_back(tmp);
  }

  // convert js argument to c++ type
  std::vector<double>DividendsCpp;

  Local<Array> DividendsArray = info[4].As<Array>();
  for (unsigned int i = 0; i < DividendsArray->Length(); i++){
    DividendsCpp.push_back(Nan::To<double>(Nan::Get(DividendsArray, i).ToLocalChecked()).FromJust());
  }

 
  // launch worker
  DividendVanillaOptionWorker* worker = new DividendVanillaOptionWorker(
    ObjectIDCpp
,     PayoffCpp
,     ExerciseCpp
,     DividendDatesCpp
,     DividendsCpp
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

void ForwardVanillaOptionWorker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes

  // convert input datatypes to QuantLib datatypes
  QuantLib::Date ResetDateLib = ObjectHandler::convert2<QuantLib::Date>(
      mResetDate, "ResetDate");


  // convert object IDs into library objects
  OH_GET_REFERENCE(PayoffLibObjPtr, mPayoff,
      QuantLibAddin::StrikedTypePayoff, QuantLib::StrikedTypePayoff)


  // convert object IDs into library objects
  OH_GET_REFERENCE(ExerciseLibObjPtr, mExercise,
      QuantLibAddin::Exercise, QuantLib::Exercise)

 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlForwardVanillaOption(
          mObjectID,
          mMoneyness,
          mResetDate,
          mPayoff,
          mExercise,
          false
      ));

    // Construct the Object
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::ForwardVanillaOption(
          valueObject,
          mMoneyness,
          ResetDateLib,
          PayoffLibObjPtr,
          ExerciseLibObjPtr,
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

NAN_METHOD(QuantLibXL::ForwardVanillaOption) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsNumber()) {
      return Nan::ThrowError("Moneyness is required.");
  }
  if (info.Length() == 3 || !info[3]->IsString()) {
      return Nan::ThrowError("Payoff is required.");
  }
  if (info.Length() == 4 || !info[4]->IsString()) {
      return Nan::ThrowError("Exercise is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  double MoneynessCpp = Nan::To<double>(info[1]).FromJust();

  // convert js argument to c++ type
  ObjectHandler::property_t ResetDateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[2]).FromJust()));

  // convert js argument to c++ type
  String::Utf8Value strPayoff(info[3]->ToString());
  string PayoffCpp(strdup(*strPayoff));

  // convert js argument to c++ type
  String::Utf8Value strExercise(info[4]->ToString());
  string ExerciseCpp(strdup(*strExercise));

 
  // launch worker
  ForwardVanillaOptionWorker* worker = new ForwardVanillaOptionWorker(
    ObjectIDCpp
,     MoneynessCpp
,     ResetDateCpp
,     PayoffCpp
,     ExerciseCpp
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

void VanillaOptionWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_REFERENCE(PayoffLibObjPtr, mPayoff,
      QuantLibAddin::StrikedTypePayoff, QuantLib::StrikedTypePayoff)


  // convert object IDs into library objects
  OH_GET_REFERENCE(ExerciseLibObjPtr, mExercise,
      QuantLibAddin::Exercise, QuantLib::Exercise)

 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlVanillaOption(
          mObjectID,
          mPayoff,
          mExercise,
          false
      ));

    // Construct the Object
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::VanillaOption(
          valueObject,
          PayoffLibObjPtr,
          ExerciseLibObjPtr,
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

NAN_METHOD(QuantLibXL::VanillaOption) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsString()) {
      return Nan::ThrowError("Payoff is required.");
  }
  if (info.Length() == 2 || !info[2]->IsString()) {
      return Nan::ThrowError("Exercise is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  String::Utf8Value strPayoff(info[1]->ToString());
  string PayoffCpp(strdup(*strPayoff));

  // convert js argument to c++ type
  String::Utf8Value strExercise(info[2]->ToString());
  string ExerciseCpp(strdup(*strExercise));

 
  // launch worker
  VanillaOptionWorker* worker = new VanillaOptionWorker(
    ObjectIDCpp
,     PayoffCpp
,     ExerciseCpp
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

void EuropeanOptionWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_REFERENCE(PayoffLibObjPtr, mPayoff,
      QuantLibAddin::StrikedTypePayoff, QuantLib::StrikedTypePayoff)


  // convert object IDs into library objects
  OH_GET_REFERENCE(ExerciseLibObjPtr, mExercise,
      QuantLibAddin::Exercise, QuantLib::Exercise)

 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlEuropeanOption(
          mObjectID,
          mPayoff,
          mExercise,
          false
      ));

    // Construct the Object
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::EuropeanOption(
          valueObject,
          PayoffLibObjPtr,
          ExerciseLibObjPtr,
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

NAN_METHOD(QuantLibXL::EuropeanOption) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsString()) {
      return Nan::ThrowError("Payoff is required.");
  }
  if (info.Length() == 2 || !info[2]->IsString()) {
      return Nan::ThrowError("Exercise is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  String::Utf8Value strPayoff(info[1]->ToString());
  string PayoffCpp(strdup(*strPayoff));

  // convert js argument to c++ type
  String::Utf8Value strExercise(info[2]->ToString());
  string ExerciseCpp(strdup(*strExercise));

 
  // launch worker
  EuropeanOptionWorker* worker = new EuropeanOptionWorker(
    ObjectIDCpp
,     PayoffCpp
,     ExerciseCpp
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

void QuantoVanillaOptionWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_REFERENCE(PayoffLibObjPtr, mPayoff,
      QuantLibAddin::StrikedTypePayoff, QuantLib::StrikedTypePayoff)


  // convert object IDs into library objects
  OH_GET_REFERENCE(ExerciseLibObjPtr, mExercise,
      QuantLibAddin::Exercise, QuantLib::Exercise)

 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlQuantoVanillaOption(
          mObjectID,
          mPayoff,
          mExercise,
          false
      ));

    // Construct the Object
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::QuantoVanillaOption(
          valueObject,
          PayoffLibObjPtr,
          ExerciseLibObjPtr,
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

NAN_METHOD(QuantLibXL::QuantoVanillaOption) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsString()) {
      return Nan::ThrowError("Payoff is required.");
  }
  if (info.Length() == 2 || !info[2]->IsString()) {
      return Nan::ThrowError("Exercise is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  String::Utf8Value strPayoff(info[1]->ToString());
  string PayoffCpp(strdup(*strPayoff));

  // convert js argument to c++ type
  String::Utf8Value strExercise(info[2]->ToString());
  string ExerciseCpp(strdup(*strExercise));

 
  // launch worker
  QuantoVanillaOptionWorker* worker = new QuantoVanillaOptionWorker(
    ObjectIDCpp
,     PayoffCpp
,     ExerciseCpp
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

void QuantoForwardVanillaOptionWorker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes

  // convert input datatypes to QuantLib datatypes
  QuantLib::Date ResetDateLib = ObjectHandler::convert2<QuantLib::Date>(
      mResetDate, "ResetDate");


  // convert object IDs into library objects
  OH_GET_REFERENCE(PayoffLibObjPtr, mPayoff,
      QuantLibAddin::StrikedTypePayoff, QuantLib::StrikedTypePayoff)


  // convert object IDs into library objects
  OH_GET_REFERENCE(ExerciseLibObjPtr, mExercise,
      QuantLibAddin::Exercise, QuantLib::Exercise)

 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlQuantoForwardVanillaOption(
          mObjectID,
          mMoneyness,
          mResetDate,
          mPayoff,
          mExercise,
          false
      ));

    // Construct the Object
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::QuantoForwardVanillaOption(
          valueObject,
          mMoneyness,
          ResetDateLib,
          PayoffLibObjPtr,
          ExerciseLibObjPtr,
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

NAN_METHOD(QuantLibXL::QuantoForwardVanillaOption) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsNumber()) {
      return Nan::ThrowError("Moneyness is required.");
  }
  if (info.Length() == 3 || !info[3]->IsString()) {
      return Nan::ThrowError("Payoff is required.");
  }
  if (info.Length() == 4 || !info[4]->IsString()) {
      return Nan::ThrowError("Exercise is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  double MoneynessCpp = Nan::To<double>(info[1]).FromJust();

  // convert js argument to c++ type
  ObjectHandler::property_t ResetDateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[2]).FromJust()));

  // convert js argument to c++ type
  String::Utf8Value strPayoff(info[3]->ToString());
  string PayoffCpp(strdup(*strPayoff));

  // convert js argument to c++ type
  String::Utf8Value strExercise(info[4]->ToString());
  string ExerciseCpp(strdup(*strExercise));

 
  // launch worker
  QuantoForwardVanillaOptionWorker* worker = new QuantoForwardVanillaOptionWorker(
    ObjectIDCpp
,     MoneynessCpp
,     ResetDateCpp
,     PayoffCpp
,     ExerciseCpp
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

void DeltaWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::OneAssetOption, QuantLib::OneAssetOption)


  // invoke the member function
  QuantLib::Real returnValue = ObjectIDLibObjPtr->delta(
      );


  mReturnValue = returnValue;

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::Delta) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  DeltaWorker* worker = new DeltaWorker(
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

void DeltaForwardWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::OneAssetOption, QuantLib::OneAssetOption)


  // invoke the member function
  QuantLib::Real returnValue = ObjectIDLibObjPtr->deltaForward(
      );


  mReturnValue = returnValue;

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::DeltaForward) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  DeltaForwardWorker* worker = new DeltaForwardWorker(
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

void ElasticityWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::OneAssetOption, QuantLib::OneAssetOption)


  // invoke the member function
  QuantLib::Real returnValue = ObjectIDLibObjPtr->elasticity(
      );


  mReturnValue = returnValue;

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::Elasticity) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  ElasticityWorker* worker = new ElasticityWorker(
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

void GammaWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::OneAssetOption, QuantLib::OneAssetOption)


  // invoke the member function
  QuantLib::Real returnValue = ObjectIDLibObjPtr->gamma(
      );


  mReturnValue = returnValue;

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::Gamma) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  GammaWorker* worker = new GammaWorker(
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

void ThetaWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::OneAssetOption, QuantLib::OneAssetOption)


  // invoke the member function
  QuantLib::Real returnValue = ObjectIDLibObjPtr->theta(
      );


  mReturnValue = returnValue;

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::Theta) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  ThetaWorker* worker = new ThetaWorker(
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

void ThetaPerDayWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::OneAssetOption, QuantLib::OneAssetOption)


  // invoke the member function
  QuantLib::Real returnValue = ObjectIDLibObjPtr->thetaPerDay(
      );


  mReturnValue = returnValue;

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::ThetaPerDay) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  ThetaPerDayWorker* worker = new ThetaPerDayWorker(
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

void VegaWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::OneAssetOption, QuantLib::OneAssetOption)


  // invoke the member function
  QuantLib::Real returnValue = ObjectIDLibObjPtr->vega(
      );


  mReturnValue = returnValue;

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::Vega) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  VegaWorker* worker = new VegaWorker(
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

void RhoWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::OneAssetOption, QuantLib::OneAssetOption)


  // invoke the member function
  QuantLib::Real returnValue = ObjectIDLibObjPtr->rho(
      );


  mReturnValue = returnValue;

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::Rho) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  RhoWorker* worker = new RhoWorker(
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

void DividendRhoWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::OneAssetOption, QuantLib::OneAssetOption)


  // invoke the member function
  QuantLib::Real returnValue = ObjectIDLibObjPtr->dividendRho(
      );


  mReturnValue = returnValue;

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::DividendRho) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  DividendRhoWorker* worker = new DividendRhoWorker(
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

void ItmCashProbabilityWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::OneAssetOption, QuantLib::OneAssetOption)


  // invoke the member function
  QuantLib::Real returnValue = ObjectIDLibObjPtr->itmCashProbability(
      );


  mReturnValue = returnValue;

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::ItmCashProbability) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  ItmCashProbabilityWorker* worker = new ItmCashProbabilityWorker(
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
 