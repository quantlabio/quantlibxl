/* 
  Copyright (C) 2016 -2017 Jerry Jin
*/

#include <nan.h>
#include <string.h>

#include "volatility.hpp"

#include <qlo/qladdindefines.hpp>
#include <qlo/volatility.hpp>
#include <ql/models/marketmodels/models/piecewiseconstantabcdvariance.hpp>
 #include <oh/objecthandler.hpp>
#include <oh/conversions/getobjectvector.hpp>
#include <qlo/valueobjects/vo_all.hpp>
#include <qlo/conversions/all.hpp>
#include "../loop.hpp"


void PiecewiseConstantAbcdVarianceWorker::Execute(){

  try{
 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlPiecewiseConstantAbcdVariance(
          mObjectID,
          mA,
          mB,
          mC,
          mD,
          mResetIndex,
          mRateTimes,
          false
      ));

    // Construct the Object
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::PiecewiseConstantAbcdVariance(
          valueObject,
          mA,
          mB,
          mC,
          mD,
          mResetIndex,
          mRateTimes,
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

NAN_METHOD(QuantLibXL::PiecewiseConstantAbcdVariance) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsNumber()) {
      return Nan::ThrowError("A is required.");
  }
  if (info.Length() == 2 || !info[2]->IsNumber()) {
      return Nan::ThrowError("B is required.");
  }
  if (info.Length() == 3 || !info[3]->IsNumber()) {
      return Nan::ThrowError("C is required.");
  }
  if (info.Length() == 4 || !info[4]->IsNumber()) {
      return Nan::ThrowError("D is required.");
  }
  if (info.Length() == 5 || !info[5]->IsNumber()) {
      return Nan::ThrowError("ResetIndex is required.");
  }
  if (info.Length() == 6 || !info[6]->IsArray()) {
      return Nan::ThrowError("RateTimes is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  double ACpp = Nan::To<double>(info[1]).FromJust();

  // convert js argument to c++ type
  double BCpp = Nan::To<double>(info[2]).FromJust();

  // convert js argument to c++ type
  double CCpp = Nan::To<double>(info[3]).FromJust();

  // convert js argument to c++ type
  double DCpp = Nan::To<double>(info[4]).FromJust();

  // convert js argument to c++ type
  long ResetIndexCpp = Nan::To<int32_t>(info[5]).FromJust();

  // convert js argument to c++ type
  std::vector<double>RateTimesCpp;

  Local<Array> RateTimesArray = info[6].As<Array>();
  for (unsigned int i = 0; i < RateTimesArray->Length(); i++){
    RateTimesCpp.push_back(Nan::To<double>(Nan::Get(RateTimesArray, i).ToLocalChecked()).FromJust());
  }

 
  // launch worker
  PiecewiseConstantAbcdVarianceWorker* worker = new PiecewiseConstantAbcdVarianceWorker(
    ObjectIDCpp
,     ACpp
,     BCpp
,     CCpp
,     DCpp
,     ResetIndexCpp
,     RateTimesCpp
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

void MarketModelLmExtLinearExponentialVolModelWorker::Execute(){

  try{
 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlMarketModelLmExtLinearExponentialVolModel(
          mObjectID,
          mFixingTimes,
          mA,
          mB,
          mC,
          mD,
          false
      ));

    // Construct the Object
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::LmExtLinearExponentialVolModel(
          valueObject,
          mFixingTimes,
          mA,
          mB,
          mC,
          mD,
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

NAN_METHOD(QuantLibXL::MarketModelLmExtLinearExponentialVolModel) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsArray()) {
      return Nan::ThrowError("FixingTimes is required.");
  }
  if (info.Length() == 2 || !info[2]->IsNumber()) {
      return Nan::ThrowError("A is required.");
  }
  if (info.Length() == 3 || !info[3]->IsNumber()) {
      return Nan::ThrowError("B is required.");
  }
  if (info.Length() == 4 || !info[4]->IsNumber()) {
      return Nan::ThrowError("C is required.");
  }
  if (info.Length() == 5 || !info[5]->IsNumber()) {
      return Nan::ThrowError("D is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  std::vector<double>FixingTimesCpp;

  Local<Array> FixingTimesArray = info[1].As<Array>();
  for (unsigned int i = 0; i < FixingTimesArray->Length(); i++){
    FixingTimesCpp.push_back(Nan::To<double>(Nan::Get(FixingTimesArray, i).ToLocalChecked()).FromJust());
  }

  // convert js argument to c++ type
  double ACpp = Nan::To<double>(info[2]).FromJust();

  // convert js argument to c++ type
  double BCpp = Nan::To<double>(info[3]).FromJust();

  // convert js argument to c++ type
  double CCpp = Nan::To<double>(info[4]).FromJust();

  // convert js argument to c++ type
  double DCpp = Nan::To<double>(info[5]).FromJust();

 
  // launch worker
  MarketModelLmExtLinearExponentialVolModelWorker* worker = new MarketModelLmExtLinearExponentialVolModelWorker(
    ObjectIDCpp
,     FixingTimesCpp
,     ACpp
,     BCpp
,     CCpp
,     DCpp
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

void PiecewiseConstantVarianceVariancesWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::PiecewiseConstantVariance, QuantLib::PiecewiseConstantVariance)


  // loop on the input parameter and populate the return vector
  mReturnValue = ObjectIDLibObjPtr->variances(
      );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::PiecewiseConstantVarianceVariances) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  PiecewiseConstantVarianceVariancesWorker* worker = new PiecewiseConstantVarianceVariancesWorker(
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

void PiecewiseConstantVarianceVolatilitiesWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::PiecewiseConstantVariance, QuantLib::PiecewiseConstantVariance)


  // loop on the input parameter and populate the return vector
  mReturnValue = ObjectIDLibObjPtr->volatilities(
      );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::PiecewiseConstantVarianceVolatilities) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  PiecewiseConstantVarianceVolatilitiesWorker* worker = new PiecewiseConstantVarianceVolatilitiesWorker(
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

void PiecewiseConstantVarianceRateTimesWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::PiecewiseConstantVariance, QuantLib::PiecewiseConstantVariance)


  // loop on the input parameter and populate the return vector
  mReturnValue = ObjectIDLibObjPtr->rateTimes(
      );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::PiecewiseConstantVarianceRateTimes) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  PiecewiseConstantVarianceRateTimesWorker* worker = new PiecewiseConstantVarianceRateTimesWorker(
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

void PiecewiseConstantVarianceVarianceWorker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes
  QuantLib::Size TimeIndexLib;
  QuantLibAddin::cppToLibrary(mTimeIndex, TimeIndexLib);

       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::PiecewiseConstantVariance, QuantLib::PiecewiseConstantVariance)


  // invoke the member function
  mReturnValue = ObjectIDLibObjPtr->variance(
        TimeIndexLib
       );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::PiecewiseConstantVarianceVariance) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsNumber()) {
      return Nan::ThrowError("TimeIndex is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  long TimeIndexCpp = Nan::To<int32_t>(info[1]).FromJust();

 
  // launch worker
  PiecewiseConstantVarianceVarianceWorker* worker = new PiecewiseConstantVarianceVarianceWorker(
    ObjectIDCpp
,     TimeIndexCpp
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

void PiecewiseConstantVarianceVolatilityWorker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes
  QuantLib::Size TimeIndexLib;
  QuantLibAddin::cppToLibrary(mTimeIndex, TimeIndexLib);

       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::PiecewiseConstantVariance, QuantLib::PiecewiseConstantVariance)


  // invoke the member function
  mReturnValue = ObjectIDLibObjPtr->volatility(
        TimeIndexLib
       );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::PiecewiseConstantVarianceVolatility) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsNumber()) {
      return Nan::ThrowError("TimeIndex is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  long TimeIndexCpp = Nan::To<int32_t>(info[1]).FromJust();

 
  // launch worker
  PiecewiseConstantVarianceVolatilityWorker* worker = new PiecewiseConstantVarianceVolatilityWorker(
    ObjectIDCpp
,     TimeIndexCpp
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

void PiecewiseConstantVarianceTotalVarianceWorker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes
  QuantLib::Size TimeIndexLib;
  QuantLibAddin::cppToLibrary(mTimeIndex, TimeIndexLib);

       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::PiecewiseConstantVariance, QuantLib::PiecewiseConstantVariance)


  // invoke the member function
  mReturnValue = ObjectIDLibObjPtr->totalVariance(
        TimeIndexLib
       );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::PiecewiseConstantVarianceTotalVariance) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsNumber()) {
      return Nan::ThrowError("TimeIndex is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  long TimeIndexCpp = Nan::To<int32_t>(info[1]).FromJust();

 
  // launch worker
  PiecewiseConstantVarianceTotalVarianceWorker* worker = new PiecewiseConstantVarianceTotalVarianceWorker(
    ObjectIDCpp
,     TimeIndexCpp
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

void PiecewiseConstantVarianceTotalVolatilityWorker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes
  QuantLib::Size TimeIndexLib;
  QuantLibAddin::cppToLibrary(mTimeIndex, TimeIndexLib);

       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::PiecewiseConstantVariance, QuantLib::PiecewiseConstantVariance)


  // invoke the member function
  mReturnValue = ObjectIDLibObjPtr->totalVolatility(
        TimeIndexLib
       );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::PiecewiseConstantVarianceTotalVolatility) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsNumber()) {
      return Nan::ThrowError("TimeIndex is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  long TimeIndexCpp = Nan::To<int32_t>(info[1]).FromJust();

 
  // launch worker
  PiecewiseConstantVarianceTotalVolatilityWorker* worker = new PiecewiseConstantVarianceTotalVolatilityWorker(
    ObjectIDCpp
,     TimeIndexCpp
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
 