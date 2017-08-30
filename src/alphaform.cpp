/* 
  Copyright (C) 2016 -2017 Jerry Jin
*/

#include <nan.h>
#include <string.h>

#include "alphaform.hpp"

#include <qlo/qladdindefines.hpp>
#include <ql/models/marketmodels/models/alphaform.hpp>
#include <ql/models/marketmodels/models/alphaformconcrete.hpp>
#include <qlo/alphaform.hpp>
 #include <oh/objecthandler.hpp>
#include <oh/conversions/getobjectvector.hpp>
#include <qlo/valueobjects/vo_all.hpp>
#include <qlo/conversions/all.hpp>
#include "../loop.hpp"


void AlphaFormInverseLinearWorker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes
 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlAlphaFormInverseLinear(
          mObjectID,
          mRateTimes,
          mAlpha,
          false
      ));

    // Construct the Object
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::AlphaFormInverseLinear(
          valueObject,
          mRateTimes,
          mAlpha,
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

NAN_METHOD(QuantLibXL::AlphaFormInverseLinear) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsArray()) {
      return Nan::ThrowError("RateTimes is required.");
  }
  if (info.Length() == 2 || !info[2]->IsNumber()) {
      return Nan::ThrowError("Alpha is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  std::vector<double>RateTimesCpp;

  Local<Array> RateTimesArray = info[1].As<Array>();
  for (unsigned int i = 0; i < RateTimesArray->Length(); i++){
    RateTimesCpp.push_back(Nan::To<double>(Nan::Get(RateTimesArray, i).ToLocalChecked()).FromJust());
  }

  // convert js argument to c++ type
  double AlphaCpp = Nan::To<double>(info[2]).FromJust();

 
  // launch worker
  AlphaFormInverseLinearWorker* worker = new AlphaFormInverseLinearWorker(
    ObjectIDCpp
,     RateTimesCpp
,     AlphaCpp
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

void AlphaFormLinearHyperbolicWorker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes
 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlAlphaFormLinearHyperbolic(
          mObjectID,
          mRateTimes,
          mAlpha,
          false
      ));

    // Construct the Object
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::AlphaFormLinearHyperbolic(
          valueObject,
          mRateTimes,
          mAlpha,
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

NAN_METHOD(QuantLibXL::AlphaFormLinearHyperbolic) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsArray()) {
      return Nan::ThrowError("RateTimes is required.");
  }
  if (info.Length() == 2 || !info[2]->IsNumber()) {
      return Nan::ThrowError("Alpha is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  std::vector<double>RateTimesCpp;

  Local<Array> RateTimesArray = info[1].As<Array>();
  for (unsigned int i = 0; i < RateTimesArray->Length(); i++){
    RateTimesCpp.push_back(Nan::To<double>(Nan::Get(RateTimesArray, i).ToLocalChecked()).FromJust());
  }

  // convert js argument to c++ type
  double AlphaCpp = Nan::To<double>(info[2]).FromJust();

 
  // launch worker
  AlphaFormLinearHyperbolicWorker* worker = new AlphaFormLinearHyperbolicWorker(
    ObjectIDCpp
,     RateTimesCpp
,     AlphaCpp
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

void AlphaFormOperatorWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::AlphaForm, QuantLib::AlphaForm)


  // convert input datatypes to QuantLib datatypes
  QuantLib::Size TimeLib;
  QuantLibAddin::cppToLibrary(mTime, TimeLib);

     
  // invoke the member function
  QuantLib::Real returnValue = ObjectIDLibObjPtr->operator()(
        TimeLib
       );


  mReturnValue = returnValue;

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::AlphaFormOperator) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsNumber()) {
      return Nan::ThrowError("Time is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  long TimeCpp = Nan::To<int32_t>(info[1]).FromJust();

 
  // launch worker
  AlphaFormOperatorWorker* worker = new AlphaFormOperatorWorker(
    ObjectIDCpp
,     TimeCpp
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

void AlphaFormSetAlphaWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::AlphaForm, QuantLib::AlphaForm)


  // convert input datatypes to QuantLib datatypes
     
  // invoke the member function
  ObjectIDLibObjPtr->setAlpha(
        mAlpha
       );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::AlphaFormSetAlpha) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsNumber()) {
      return Nan::ThrowError("Alpha is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  double AlphaCpp = Nan::To<double>(info[1]).FromJust();

 
  // launch worker
  AlphaFormSetAlphaWorker* worker = new AlphaFormSetAlphaWorker(
    ObjectIDCpp
,     AlphaCpp
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
 