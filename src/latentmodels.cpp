/* 
  Copyright (C) 2016 -2017 Jerry Jin
*/

#include <nan.h>
#include <string.h>

#include "latentmodels.hpp"

#include <qlo/qladdindefines.hpp>
#include <ql/experimental/credit/defaultprobabilitylatentmodel.hpp>
#include <qlo/defaultbasket.hpp>
#include <qlo/credit.hpp>
#include <qlo/latentmodels.hpp>
 #include <oh/objecthandler.hpp>
#include <oh/conversions/getobjectvector.hpp>
#include <qlo/valueobjects/vo_all.hpp>
#include <qlo/conversions/all.hpp>
#include "../loop.hpp"


void GaussianDefaultProbLMWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_REFERENCE(BasketLibObjPtr, mBasket,
      QuantLibAddin::Basket, QuantLib::Basket)

 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlGaussianDefaultProbLM(
          mObjectID,
          mBasket,
          mFactors,
          false
      ));

    // Construct the Object
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::GaussianDefProbLM(
          valueObject,
          BasketLibObjPtr,
          mFactors,
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

NAN_METHOD(QuantLibXL::GaussianDefaultProbLM) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsString()) {
      return Nan::ThrowError("Basket is required.");
  }
  if (info.Length() == 2 || !info[2]->IsArray()) {
      return Nan::ThrowError("Factors is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  String::Utf8Value strBasket(info[1]->ToString());
  string BasketCpp(strdup(*strBasket));

  // convert js argument to c++ type
  std::vector< std::vector<double> >FactorsCpp;

  Local<Array> FactorsMatrix = info[2].As<Array>();
  for (unsigned int i = 0; i < FactorsMatrix->Length(); i++){
	  Local<Array> FactorsArray = FactorsMatrix->Get(i).As<Array>();
	  std::vector<double> tmp;
	  for (unsigned int j = 0; j < FactorsArray->Length(); j++){
		  tmp.push_back(Nan::To<double>(Nan::Get(FactorsArray, j).ToLocalChecked()).FromJust());
	  }
	  FactorsCpp.push_back(tmp);
  }

 
  // launch worker
  GaussianDefaultProbLMWorker* worker = new GaussianDefaultProbLMWorker(
    ObjectIDCpp
,     BasketCpp
,     FactorsCpp
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

void TDefaultProbLMWorker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes
  std::vector<long> TordersCpp;
  std::vector<QuantLib::Integer> TordersLib =
      QuantLibAddin::convertVector<long, QuantLib::Integer>(TordersCpp);


  // convert object IDs into library objects
  OH_GET_REFERENCE(BasketLibObjPtr, mBasket,
      QuantLibAddin::Basket, QuantLib::Basket)

 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlTDefaultProbLM(
          mObjectID,
          TordersCpp,
          mBasket,
          mFactors,
          false
      ));

    // Construct the Object
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::TDefProbLM(
          valueObject,
          TordersLib,
          BasketLibObjPtr,
          mFactors,
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

NAN_METHOD(QuantLibXL::TDefaultProbLM) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsArray()) {
      return Nan::ThrowError("Torders is required.");
  }
  if (info.Length() == 2 || !info[2]->IsString()) {
      return Nan::ThrowError("Basket is required.");
  }
  if (info.Length() == 3 || !info[3]->IsArray()) {
      return Nan::ThrowError("Factors is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  std::vector<long>TordersCpp;

  Local<Array> TordersArray = info[1].As<Array>();
  for (unsigned int i = 0; i < TordersArray->Length(); i++){
    TordersCpp.push_back(Nan::To<int32_t>(Nan::Get(TordersArray, i).ToLocalChecked()).FromJust());
  }

  // convert js argument to c++ type
  String::Utf8Value strBasket(info[2]->ToString());
  string BasketCpp(strdup(*strBasket));

  // convert js argument to c++ type
  std::vector< std::vector<double> >FactorsCpp;

  Local<Array> FactorsMatrix = info[3].As<Array>();
  for (unsigned int i = 0; i < FactorsMatrix->Length(); i++){
	  Local<Array> FactorsArray = FactorsMatrix->Get(i).As<Array>();
	  std::vector<double> tmp;
	  for (unsigned int j = 0; j < FactorsArray->Length(); j++){
		  tmp.push_back(Nan::To<double>(Nan::Get(FactorsArray, j).ToLocalChecked()).FromJust());
	  }
	  FactorsCpp.push_back(tmp);
  }

 
  // launch worker
  TDefaultProbLMWorker* worker = new TDefaultProbLMWorker(
    ObjectIDCpp
,     TordersCpp
,     BasketCpp
,     FactorsCpp
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

void GaussianLMDefaultCorrelWorker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes
  QuantLib::Date CorrelationDateLib = ObjectHandler::convert2<QuantLib::Date>(
      mCorrelationDate, "CorrelationDate");


  // convert input datatypes to QuantLib datatypes
  QuantLib::Size NameindexALib;
  QuantLibAddin::cppToLibrary(mNameindexA, NameindexALib);


  // convert input datatypes to QuantLib datatypes
  QuantLib::Size NameindexBLib;
  QuantLibAddin::cppToLibrary(mNameindexB, NameindexBLib);

       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::GaussianDefProbLM, QuantLib::GaussianDefProbLM)


  // invoke the member function
  QuantLib::Real returnValue = ObjectIDLibObjPtr->defaultCorrelation(
        CorrelationDateLib
        ,
         NameindexALib
        ,
         NameindexBLib
       );


  mReturnValue = returnValue;

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::GaussianLMDefaultCorrel) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 2 || !info[2]->IsNumber()) {
      return Nan::ThrowError("NameindexA is required.");
  }
  if (info.Length() == 3 || !info[3]->IsNumber()) {
      return Nan::ThrowError("NameindexB is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  ObjectHandler::property_t CorrelationDateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[1]).FromJust()));

  // convert js argument to c++ type
  long NameindexACpp = Nan::To<int32_t>(info[2]).FromJust();

  // convert js argument to c++ type
  long NameindexBCpp = Nan::To<int32_t>(info[3]).FromJust();

 
  // launch worker
  GaussianLMDefaultCorrelWorker* worker = new GaussianLMDefaultCorrelWorker(
    ObjectIDCpp
,     CorrelationDateCpp
,     NameindexACpp
,     NameindexBCpp
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

void GaussianLMAssetCorrelWorker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes
  QuantLib::Size NameindexALib;
  QuantLibAddin::cppToLibrary(mNameindexA, NameindexALib);


  // convert input datatypes to QuantLib datatypes
  QuantLib::Size NameindexBLib;
  QuantLibAddin::cppToLibrary(mNameindexB, NameindexBLib);

       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::GaussianDefProbLM, QuantLib::GaussianDefProbLM)


  // invoke the member function
  QuantLib::Real returnValue = ObjectIDLibObjPtr->latentVariableCorrel(
        NameindexALib
        ,
         NameindexBLib
       );


  mReturnValue = returnValue;

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::GaussianLMAssetCorrel) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsNumber()) {
      return Nan::ThrowError("NameindexA is required.");
  }
  if (info.Length() == 2 || !info[2]->IsNumber()) {
      return Nan::ThrowError("NameindexB is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  long NameindexACpp = Nan::To<int32_t>(info[1]).FromJust();

  // convert js argument to c++ type
  long NameindexBCpp = Nan::To<int32_t>(info[2]).FromJust();

 
  // launch worker
  GaussianLMAssetCorrelWorker* worker = new GaussianLMAssetCorrelWorker(
    ObjectIDCpp
,     NameindexACpp
,     NameindexBCpp
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

void GaussianLMProbNHitsWorker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes
  QuantLib::Size NumDefaultsLib;
  QuantLibAddin::cppToLibrary(mNumDefaults, NumDefaultsLib);


  // convert input datatypes to QuantLib datatypes
  QuantLib::Date ProbabilityDateLib = ObjectHandler::convert2<QuantLib::Date>(
      mProbabilityDate, "ProbabilityDate");

       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::GaussianDefProbLM, QuantLib::GaussianDefProbLM)


  // invoke the member function
  QuantLib::Real returnValue = ObjectIDLibObjPtr->probAtLeastNEvents(
        NumDefaultsLib
        ,
         ProbabilityDateLib
       );


  mReturnValue = returnValue;

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::GaussianLMProbNHits) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsNumber()) {
      return Nan::ThrowError("NumDefaults is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  long NumDefaultsCpp = Nan::To<int32_t>(info[1]).FromJust();

  // convert js argument to c++ type
  ObjectHandler::property_t ProbabilityDateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[2]).FromJust()));

 
  // launch worker
  GaussianLMProbNHitsWorker* worker = new GaussianLMProbNHitsWorker(
    ObjectIDCpp
,     NumDefaultsCpp
,     ProbabilityDateCpp
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

void TLMDefaultCorrelWorker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes
  QuantLib::Date CorrelationDateLib = ObjectHandler::convert2<QuantLib::Date>(
      mCorrelationDate, "CorrelationDate");


  // convert input datatypes to QuantLib datatypes
  QuantLib::Size NameindexALib;
  QuantLibAddin::cppToLibrary(mNameindexA, NameindexALib);


  // convert input datatypes to QuantLib datatypes
  QuantLib::Size NameindexBLib;
  QuantLibAddin::cppToLibrary(mNameindexB, NameindexBLib);

       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::TDefProbLM, QuantLib::TDefProbLM)


  // invoke the member function
  QuantLib::Real returnValue = ObjectIDLibObjPtr->defaultCorrelation(
        CorrelationDateLib
        ,
         NameindexALib
        ,
         NameindexBLib
       );


  mReturnValue = returnValue;

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::TLMDefaultCorrel) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 2 || !info[2]->IsNumber()) {
      return Nan::ThrowError("NameindexA is required.");
  }
  if (info.Length() == 3 || !info[3]->IsNumber()) {
      return Nan::ThrowError("NameindexB is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  ObjectHandler::property_t CorrelationDateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[1]).FromJust()));

  // convert js argument to c++ type
  long NameindexACpp = Nan::To<int32_t>(info[2]).FromJust();

  // convert js argument to c++ type
  long NameindexBCpp = Nan::To<int32_t>(info[3]).FromJust();

 
  // launch worker
  TLMDefaultCorrelWorker* worker = new TLMDefaultCorrelWorker(
    ObjectIDCpp
,     CorrelationDateCpp
,     NameindexACpp
,     NameindexBCpp
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

void TLMAssetCorrelWorker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes
  QuantLib::Size NameindexALib;
  QuantLibAddin::cppToLibrary(mNameindexA, NameindexALib);


  // convert input datatypes to QuantLib datatypes
  QuantLib::Size NameindexBLib;
  QuantLibAddin::cppToLibrary(mNameindexB, NameindexBLib);

       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::TDefProbLM, QuantLib::TDefProbLM)


  // invoke the member function
  QuantLib::Real returnValue = ObjectIDLibObjPtr->latentVariableCorrel(
        NameindexALib
        ,
         NameindexBLib
       );


  mReturnValue = returnValue;

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::TLMAssetCorrel) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsNumber()) {
      return Nan::ThrowError("NameindexA is required.");
  }
  if (info.Length() == 2 || !info[2]->IsNumber()) {
      return Nan::ThrowError("NameindexB is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  long NameindexACpp = Nan::To<int32_t>(info[1]).FromJust();

  // convert js argument to c++ type
  long NameindexBCpp = Nan::To<int32_t>(info[2]).FromJust();

 
  // launch worker
  TLMAssetCorrelWorker* worker = new TLMAssetCorrelWorker(
    ObjectIDCpp
,     NameindexACpp
,     NameindexBCpp
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

void TLMProbNHitsWorker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes
  QuantLib::Size NumDefaultsLib;
  QuantLibAddin::cppToLibrary(mNumDefaults, NumDefaultsLib);


  // convert input datatypes to QuantLib datatypes
  QuantLib::Date ProbabilityDateLib = ObjectHandler::convert2<QuantLib::Date>(
      mProbabilityDate, "ProbabilityDate");

       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::TDefProbLM, QuantLib::TDefProbLM)


  // invoke the member function
  QuantLib::Real returnValue = ObjectIDLibObjPtr->probAtLeastNEvents(
        NumDefaultsLib
        ,
         ProbabilityDateLib
       );


  mReturnValue = returnValue;

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::TLMProbNHits) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsNumber()) {
      return Nan::ThrowError("NumDefaults is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  long NumDefaultsCpp = Nan::To<int32_t>(info[1]).FromJust();

  // convert js argument to c++ type
  ObjectHandler::property_t ProbabilityDateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[2]).FromJust()));

 
  // launch worker
  TLMProbNHitsWorker* worker = new TLMProbNHitsWorker(
    ObjectIDCpp
,     NumDefaultsCpp
,     ProbabilityDateCpp
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
 