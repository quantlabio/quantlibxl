/* 
  Copyright (C) 2016 -2017 Jerry Jin
*/

#include <nan.h>
#include <string.h>

#include "curvestate.hpp"

#include <qlo/qladdindefines.hpp>
#include <ql/models/marketmodels/swapforwardmappings.hpp>
#include <ql/models/marketmodels/curvestates/cmswapcurvestate.hpp>
#include <ql/models/marketmodels/curvestates/coterminalswapcurvestate.hpp>
#include <ql/models/marketmodels/curvestates/lmmcurvestate.hpp>
#include <qlo/curvestate.hpp>
 #include <oh/objecthandler.hpp>
#include <oh/conversions/getobjectvector.hpp>
#include <qlo/valueobjects/vo_all.hpp>
#include <qlo/conversions/all.hpp>
#include "../loop.hpp"


void CMSwapCurveStateWorker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes
  QuantLib::Size SpanningForwardsLib;
  QuantLibAddin::cppToLibrary(mSpanningForwards, SpanningForwardsLib);

 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlCMSwapCurveState(
          mObjectID,
          mRateTimes,
          mSpanningForwards,
          false
      ));

    // Construct the Object
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::CMSwapCurveState(
          valueObject,
          mRateTimes,
          SpanningForwardsLib,
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

NAN_METHOD(QuantLibXL::CMSwapCurveState) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsArray()) {
      return Nan::ThrowError("RateTimes is required.");
  }
  if (info.Length() == 2 || !info[2]->IsNumber()) {
      return Nan::ThrowError("SpanningForwards is required.");
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
  long SpanningForwardsCpp = Nan::To<int32_t>(info[2]).FromJust();

 
  // launch worker
  CMSwapCurveStateWorker* worker = new CMSwapCurveStateWorker(
    ObjectIDCpp
,     RateTimesCpp
,     SpanningForwardsCpp
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

void CoterminalSwapCurveStateWorker::Execute(){

  try{
 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlCoterminalSwapCurveState(
          mObjectID,
          mRateTimes,
          false
      ));

    // Construct the Object
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::CoterminalSwapCurveState(
          valueObject,
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

NAN_METHOD(QuantLibXL::CoterminalSwapCurveState) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsArray()) {
      return Nan::ThrowError("RateTimes is required.");
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

 
  // launch worker
  CoterminalSwapCurveStateWorker* worker = new CoterminalSwapCurveStateWorker(
    ObjectIDCpp
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

void LMMCurveStateWorker::Execute(){

  try{
 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlLMMCurveState(
          mObjectID,
          mRateTimes,
          false
      ));

    // Construct the Object
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::LMMCurveState(
          valueObject,
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

NAN_METHOD(QuantLibXL::LMMCurveState) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsArray()) {
      return Nan::ThrowError("RateTimes is required.");
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

 
  // launch worker
  LMMCurveStateWorker* worker = new LMMCurveStateWorker(
    ObjectIDCpp
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

void CurveStateRateTimesWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::CurveState, QuantLib::CurveState)

     
  // loop on the input parameter and populate the return vector
  mReturnValue = ObjectIDLibObjPtr->rateTimes(
      );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::CurveStateRateTimes) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  CurveStateRateTimesWorker* worker = new CurveStateRateTimesWorker(
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

void CurveStateRateTausWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::CurveState, QuantLib::CurveState)

     
  // loop on the input parameter and populate the return vector
  mReturnValue = ObjectIDLibObjPtr->rateTaus(
      );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::CurveStateRateTaus) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  CurveStateRateTausWorker* worker = new CurveStateRateTausWorker(
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

void CurveStateForwardRatesWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::CurveState, QuantLib::CurveState)

     
  // loop on the input parameter and populate the return vector
  mReturnValue = ObjectIDLibObjPtr->forwardRates(
      );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::CurveStateForwardRates) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  CurveStateForwardRatesWorker* worker = new CurveStateForwardRatesWorker(
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

void CurveStateCoterminalSwapRatesWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::CurveState, QuantLib::CurveState)

     
  // loop on the input parameter and populate the return vector
  mReturnValue = ObjectIDLibObjPtr->coterminalSwapRates(
      );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::CurveStateCoterminalSwapRates) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  CurveStateCoterminalSwapRatesWorker* worker = new CurveStateCoterminalSwapRatesWorker(
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

void CurveStateCMSwapRatesWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::CurveState, QuantLib::CurveState)


  // convert input datatypes to QuantLib datatypes
  QuantLib::Size SpanningForwardsLib;
  QuantLibAddin::cppToLibrary(mSpanningForwards, SpanningForwardsLib);

     
  // loop on the input parameter and populate the return vector
  mReturnValue = ObjectIDLibObjPtr->cmSwapRates(
        SpanningForwardsLib
       );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::CurveStateCMSwapRates) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsNumber()) {
      return Nan::ThrowError("SpanningForwards is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  long SpanningForwardsCpp = Nan::To<int32_t>(info[1]).FromJust();

 
  // launch worker
  CurveStateCMSwapRatesWorker* worker = new CurveStateCMSwapRatesWorker(
    ObjectIDCpp
,     SpanningForwardsCpp
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

void CMSwapCurveStateSetOnCMSwapRatesWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::CMSwapCurveState, QuantLib::CMSwapCurveState)

     
  // invoke the member function
  ObjectIDLibObjPtr->setOnCMSwapRates(
        mCMSwapRates
       );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::CMSwapCurveStateSetOnCMSwapRates) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsArray()) {
      return Nan::ThrowError("CMSwapRates is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  std::vector<double>CMSwapRatesCpp;

  Local<Array> CMSwapRatesArray = info[1].As<Array>();
  for (unsigned int i = 0; i < CMSwapRatesArray->Length(); i++){
    CMSwapRatesCpp.push_back(Nan::To<double>(Nan::Get(CMSwapRatesArray, i).ToLocalChecked()).FromJust());
  }

 
  // launch worker
  CMSwapCurveStateSetOnCMSwapRatesWorker* worker = new CMSwapCurveStateSetOnCMSwapRatesWorker(
    ObjectIDCpp
,     CMSwapRatesCpp
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

void CoterminalSwapCurveStateSetOnCoterminalSwapRatesWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::CoterminalSwapCurveState, QuantLib::CoterminalSwapCurveState)

     
  // invoke the member function
  ObjectIDLibObjPtr->setOnCoterminalSwapRates(
        mCoterminalSwaps
       );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::CoterminalSwapCurveStateSetOnCoterminalSwapRates) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsArray()) {
      return Nan::ThrowError("CoterminalSwaps is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  std::vector<double>CoterminalSwapsCpp;

  Local<Array> CoterminalSwapsArray = info[1].As<Array>();
  for (unsigned int i = 0; i < CoterminalSwapsArray->Length(); i++){
    CoterminalSwapsCpp.push_back(Nan::To<double>(Nan::Get(CoterminalSwapsArray, i).ToLocalChecked()).FromJust());
  }

 
  // launch worker
  CoterminalSwapCurveStateSetOnCoterminalSwapRatesWorker* worker = new CoterminalSwapCurveStateSetOnCoterminalSwapRatesWorker(
    ObjectIDCpp
,     CoterminalSwapsCpp
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

void LMMCurveStateSetOnForwardRatesWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::LMMCurveState, QuantLib::LMMCurveState)

     
  // invoke the member function
  ObjectIDLibObjPtr->setOnForwardRates(
        mRates
       );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::LMMCurveStateSetOnForwardRates) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsArray()) {
      return Nan::ThrowError("Rates is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  std::vector<double>RatesCpp;

  Local<Array> RatesArray = info[1].As<Array>();
  for (unsigned int i = 0; i < RatesArray->Length(); i++){
    RatesCpp.push_back(Nan::To<double>(Nan::Get(RatesArray, i).ToLocalChecked()).FromJust());
  }

 
  // launch worker
  LMMCurveStateSetOnForwardRatesWorker* worker = new LMMCurveStateSetOnForwardRatesWorker(
    ObjectIDCpp
,     RatesCpp
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

void LMMCurveStateSetOnDiscountRatiosWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::LMMCurveState, QuantLib::LMMCurveState)

     
  // invoke the member function
  ObjectIDLibObjPtr->setOnDiscountRatios(
        mDiscountRatios
       );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::LMMCurveStateSetOnDiscountRatios) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsArray()) {
      return Nan::ThrowError("DiscountRatios is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  std::vector<double>DiscountRatiosCpp;

  Local<Array> DiscountRatiosArray = info[1].As<Array>();
  for (unsigned int i = 0; i < DiscountRatiosArray->Length(); i++){
    DiscountRatiosCpp.push_back(Nan::To<double>(Nan::Get(DiscountRatiosArray, i).ToLocalChecked()).FromJust());
  }

 
  // launch worker
  LMMCurveStateSetOnDiscountRatiosWorker* worker = new LMMCurveStateSetOnDiscountRatiosWorker(
    ObjectIDCpp
,     DiscountRatiosCpp
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

void ForwardsFromDiscountRatiosWorker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes
  QuantLib::Size FirstValidIndexLib;
  QuantLibAddin::cppToLibrary(mFirstValidIndex, FirstValidIndexLib);

       // invoke the utility function
  mReturnValue = QuantLibAddin::qlForwardsFromDiscountRatios(
      FirstValidIndexLib
      ,
       mDiscountRatios
      ,
       mTaus
   );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::ForwardsFromDiscountRatios) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsNumber()) {
      return Nan::ThrowError("FirstValidIndex is required.");
  }
  if (info.Length() == 1 || !info[1]->IsArray()) {
      return Nan::ThrowError("DiscountRatios is required.");
  }
  if (info.Length() == 2 || !info[2]->IsArray()) {
      return Nan::ThrowError("Taus is required.");
  }
  // convert js argument to c++ type
  long FirstValidIndexCpp = Nan::To<int32_t>(info[0]).FromJust();

  // convert js argument to c++ type
  std::vector<double>DiscountRatiosCpp;

  Local<Array> DiscountRatiosArray = info[1].As<Array>();
  for (unsigned int i = 0; i < DiscountRatiosArray->Length(); i++){
    DiscountRatiosCpp.push_back(Nan::To<double>(Nan::Get(DiscountRatiosArray, i).ToLocalChecked()).FromJust());
  }

  // convert js argument to c++ type
  std::vector<double>TausCpp;

  Local<Array> TausArray = info[2].As<Array>();
  for (unsigned int i = 0; i < TausArray->Length(); i++){
    TausCpp.push_back(Nan::To<double>(Nan::Get(TausArray, i).ToLocalChecked()).FromJust());
  }

 
  // launch worker
  ForwardsFromDiscountRatiosWorker* worker = new ForwardsFromDiscountRatiosWorker(
    FirstValidIndexCpp
,     DiscountRatiosCpp
,     TausCpp
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

void CoterminalSwapRatesFromDiscountRatiosWorker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes
  QuantLib::Size FirstValidIndexLib;
  QuantLibAddin::cppToLibrary(mFirstValidIndex, FirstValidIndexLib);

       // invoke the utility function
  mReturnValue = QuantLibAddin::qlCoterminalSwapRatesFromDiscountRatios(
      FirstValidIndexLib
      ,
       mDiscountRatios
      ,
       mTaus
   );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::CoterminalSwapRatesFromDiscountRatios) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsNumber()) {
      return Nan::ThrowError("FirstValidIndex is required.");
  }
  if (info.Length() == 1 || !info[1]->IsArray()) {
      return Nan::ThrowError("DiscountRatios is required.");
  }
  if (info.Length() == 2 || !info[2]->IsArray()) {
      return Nan::ThrowError("Taus is required.");
  }
  // convert js argument to c++ type
  long FirstValidIndexCpp = Nan::To<int32_t>(info[0]).FromJust();

  // convert js argument to c++ type
  std::vector<double>DiscountRatiosCpp;

  Local<Array> DiscountRatiosArray = info[1].As<Array>();
  for (unsigned int i = 0; i < DiscountRatiosArray->Length(); i++){
    DiscountRatiosCpp.push_back(Nan::To<double>(Nan::Get(DiscountRatiosArray, i).ToLocalChecked()).FromJust());
  }

  // convert js argument to c++ type
  std::vector<double>TausCpp;

  Local<Array> TausArray = info[2].As<Array>();
  for (unsigned int i = 0; i < TausArray->Length(); i++){
    TausCpp.push_back(Nan::To<double>(Nan::Get(TausArray, i).ToLocalChecked()).FromJust());
  }

 
  // launch worker
  CoterminalSwapRatesFromDiscountRatiosWorker* worker = new CoterminalSwapRatesFromDiscountRatiosWorker(
    FirstValidIndexCpp
,     DiscountRatiosCpp
,     TausCpp
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

void CoterminalSwapAnnuitiesFromDiscountRatiosWorker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes
  QuantLib::Size FirstValidIndexLib;
  QuantLibAddin::cppToLibrary(mFirstValidIndex, FirstValidIndexLib);

       // invoke the utility function
  mReturnValue = QuantLibAddin::qlCoterminalSwapAnnuitiesFromDiscountRatios(
      FirstValidIndexLib
      ,
       mDiscountRatios
      ,
       mTaus
   );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::CoterminalSwapAnnuitiesFromDiscountRatios) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsNumber()) {
      return Nan::ThrowError("FirstValidIndex is required.");
  }
  if (info.Length() == 1 || !info[1]->IsArray()) {
      return Nan::ThrowError("DiscountRatios is required.");
  }
  if (info.Length() == 2 || !info[2]->IsArray()) {
      return Nan::ThrowError("Taus is required.");
  }
  // convert js argument to c++ type
  long FirstValidIndexCpp = Nan::To<int32_t>(info[0]).FromJust();

  // convert js argument to c++ type
  std::vector<double>DiscountRatiosCpp;

  Local<Array> DiscountRatiosArray = info[1].As<Array>();
  for (unsigned int i = 0; i < DiscountRatiosArray->Length(); i++){
    DiscountRatiosCpp.push_back(Nan::To<double>(Nan::Get(DiscountRatiosArray, i).ToLocalChecked()).FromJust());
  }

  // convert js argument to c++ type
  std::vector<double>TausCpp;

  Local<Array> TausArray = info[2].As<Array>();
  for (unsigned int i = 0; i < TausArray->Length(); i++){
    TausCpp.push_back(Nan::To<double>(Nan::Get(TausArray, i).ToLocalChecked()).FromJust());
  }

 
  // launch worker
  CoterminalSwapAnnuitiesFromDiscountRatiosWorker* worker = new CoterminalSwapAnnuitiesFromDiscountRatiosWorker(
    FirstValidIndexCpp
,     DiscountRatiosCpp
,     TausCpp
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

void ConstantMaturitySwapRatesFromDiscountRatiosWorker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes
  QuantLib::Size SpanningForwardsLib;
  QuantLibAddin::cppToLibrary(mSpanningForwards, SpanningForwardsLib);


  // convert input datatypes to QuantLib datatypes
  QuantLib::Size FirstValidIndexLib;
  QuantLibAddin::cppToLibrary(mFirstValidIndex, FirstValidIndexLib);

       // invoke the utility function
  mReturnValue = QuantLibAddin::qlConstantMaturitySwapRatesFromDiscountRatios(
      SpanningForwardsLib
      ,
       FirstValidIndexLib
      ,
       mDiscountRatios
      ,
       mTaus
   );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::ConstantMaturitySwapRatesFromDiscountRatios) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsNumber()) {
      return Nan::ThrowError("SpanningForwards is required.");
  }
  if (info.Length() == 1 || !info[1]->IsNumber()) {
      return Nan::ThrowError("FirstValidIndex is required.");
  }
  if (info.Length() == 2 || !info[2]->IsArray()) {
      return Nan::ThrowError("DiscountRatios is required.");
  }
  if (info.Length() == 3 || !info[3]->IsArray()) {
      return Nan::ThrowError("Taus is required.");
  }
  // convert js argument to c++ type
  long SpanningForwardsCpp = Nan::To<int32_t>(info[0]).FromJust();

  // convert js argument to c++ type
  long FirstValidIndexCpp = Nan::To<int32_t>(info[1]).FromJust();

  // convert js argument to c++ type
  std::vector<double>DiscountRatiosCpp;

  Local<Array> DiscountRatiosArray = info[2].As<Array>();
  for (unsigned int i = 0; i < DiscountRatiosArray->Length(); i++){
    DiscountRatiosCpp.push_back(Nan::To<double>(Nan::Get(DiscountRatiosArray, i).ToLocalChecked()).FromJust());
  }

  // convert js argument to c++ type
  std::vector<double>TausCpp;

  Local<Array> TausArray = info[3].As<Array>();
  for (unsigned int i = 0; i < TausArray->Length(); i++){
    TausCpp.push_back(Nan::To<double>(Nan::Get(TausArray, i).ToLocalChecked()).FromJust());
  }

 
  // launch worker
  ConstantMaturitySwapRatesFromDiscountRatiosWorker* worker = new ConstantMaturitySwapRatesFromDiscountRatiosWorker(
    SpanningForwardsCpp
,     FirstValidIndexCpp
,     DiscountRatiosCpp
,     TausCpp
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

void ConstantMaturitySwapAnnuitiesFromDiscountRatiosWorker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes
  QuantLib::Size SpanningForwardsLib;
  QuantLibAddin::cppToLibrary(mSpanningForwards, SpanningForwardsLib);


  // convert input datatypes to QuantLib datatypes
  QuantLib::Size FirstValidIndexLib;
  QuantLibAddin::cppToLibrary(mFirstValidIndex, FirstValidIndexLib);

       // invoke the utility function
  mReturnValue = QuantLibAddin::qlConstantMaturitySwapAnnuitiesFromDiscountRatios(
      SpanningForwardsLib
      ,
       FirstValidIndexLib
      ,
       mDiscountRatios
      ,
       mTaus
   );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::ConstantMaturitySwapAnnuitiesFromDiscountRatios) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsNumber()) {
      return Nan::ThrowError("SpanningForwards is required.");
  }
  if (info.Length() == 1 || !info[1]->IsNumber()) {
      return Nan::ThrowError("FirstValidIndex is required.");
  }
  if (info.Length() == 2 || !info[2]->IsArray()) {
      return Nan::ThrowError("DiscountRatios is required.");
  }
  if (info.Length() == 3 || !info[3]->IsArray()) {
      return Nan::ThrowError("Taus is required.");
  }
  // convert js argument to c++ type
  long SpanningForwardsCpp = Nan::To<int32_t>(info[0]).FromJust();

  // convert js argument to c++ type
  long FirstValidIndexCpp = Nan::To<int32_t>(info[1]).FromJust();

  // convert js argument to c++ type
  std::vector<double>DiscountRatiosCpp;

  Local<Array> DiscountRatiosArray = info[2].As<Array>();
  for (unsigned int i = 0; i < DiscountRatiosArray->Length(); i++){
    DiscountRatiosCpp.push_back(Nan::To<double>(Nan::Get(DiscountRatiosArray, i).ToLocalChecked()).FromJust());
  }

  // convert js argument to c++ type
  std::vector<double>TausCpp;

  Local<Array> TausArray = info[3].As<Array>();
  for (unsigned int i = 0; i < TausArray->Length(); i++){
    TausCpp.push_back(Nan::To<double>(Nan::Get(TausArray, i).ToLocalChecked()).FromJust());
  }

 
  // launch worker
  ConstantMaturitySwapAnnuitiesFromDiscountRatiosWorker* worker = new ConstantMaturitySwapAnnuitiesFromDiscountRatiosWorker(
    SpanningForwardsCpp
,     FirstValidIndexCpp
,     DiscountRatiosCpp
,     TausCpp
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
 