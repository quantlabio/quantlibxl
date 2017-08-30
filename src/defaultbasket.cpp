/* 
  Copyright (C) 2016 -2017 Jerry Jin
*/

#include <nan.h>
#include <string.h>

#include "defaultbasket.hpp"

#include <qlo/qladdindefines.hpp>
#include <ql/experimental/credit/basket.hpp>
#include <qlo/credit.hpp>
#include <qlo/defaultbasket.hpp>
#include <qlo/basketlossmodels.hpp>
 #include <oh/objecthandler.hpp>
#include <oh/conversions/getobjectvector.hpp>
#include <qlo/valueobjects/vo_all.hpp>
#include <qlo/conversions/all.hpp>
#include "../loop.hpp"


void CreditBasketWorker::Execute(){

  try{

  // convert object IDs into library objects
  std::vector< boost::shared_ptr<QuantLib::Issuer> > IssuersLibObjPtr =
      ObjectHandler::getLibraryObjectVector<QuantLibAddin::Issuer, QuantLib::Issuer>(mIssuers);


  // convert input datatypes to QuantLib datatypes
  QuantLib::Date ReferenceDateLib = ObjectHandler::convert2<QuantLib::Date>(
      mReferenceDate, "ReferenceDate");

 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlCreditBasket(
          mObjectID,
          mIssuerNames,
          mIssuers,
          mNotionals,
          mReferenceDate,
          mAttachmentRatio,
          mDettachmentRatio,
          mAmortizing,
          false
      ));

    // Construct the Object
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::Basket(
          valueObject,
          mIssuerNames,
          IssuersLibObjPtr,
          mNotionals,
          ReferenceDateLib,
          mAttachmentRatio,
          mDettachmentRatio,
          mAmortizing,
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

NAN_METHOD(QuantLibXL::CreditBasket) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsArray()) {
      return Nan::ThrowError("IssuerNames is required.");
  }
  if (info.Length() == 2 || !info[2]->IsArray()) {
      return Nan::ThrowError("Issuers is required.");
  }
  if (info.Length() == 3 || !info[3]->IsArray()) {
      return Nan::ThrowError("Notionals is required.");
  }
  if (info.Length() == 5 || !info[5]->IsNumber()) {
      return Nan::ThrowError("AttachmentRatio is required.");
  }
  if (info.Length() == 6 || !info[6]->IsNumber()) {
      return Nan::ThrowError("DettachmentRatio is required.");
  }
  if (info.Length() == 7 || !info[7]->IsBoolean()) {
      return Nan::ThrowError("Amortizing is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  std::vector<string>IssuerNamesCpp;

  Local<Array> IssuerNamesArray = info[1].As<Array>();
  for (unsigned int i = 0; i < IssuerNamesArray->Length(); i++){
    String::Utf8Value strIssuerNames(Nan::Get(IssuerNamesArray, i).ToLocalChecked()->ToString());
    IssuerNamesCpp.push_back(strdup(*strIssuerNames));
  }

  // convert js argument to c++ type
  std::vector<string>IssuersCpp;

  Local<Array> IssuersArray = info[2].As<Array>();
  for (unsigned int i = 0; i < IssuersArray->Length(); i++){
    String::Utf8Value strIssuers(Nan::Get(IssuersArray, i).ToLocalChecked()->ToString());
    IssuersCpp.push_back(strdup(*strIssuers));
  }

  // convert js argument to c++ type
  std::vector<double>NotionalsCpp;

  Local<Array> NotionalsArray = info[3].As<Array>();
  for (unsigned int i = 0; i < NotionalsArray->Length(); i++){
    NotionalsCpp.push_back(Nan::To<double>(Nan::Get(NotionalsArray, i).ToLocalChecked()).FromJust());
  }

  // convert js argument to c++ type
  ObjectHandler::property_t ReferenceDateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[4]).FromJust()));

  // convert js argument to c++ type
  double AttachmentRatioCpp = Nan::To<double>(info[5]).FromJust();

  // convert js argument to c++ type
  double DettachmentRatioCpp = Nan::To<double>(info[6]).FromJust();

  // convert js argument to c++ type
  bool AmortizingCpp = Nan::To<bool>(info[7]).FromJust();

 
  // launch worker
  CreditBasketWorker* worker = new CreditBasketWorker(
    ObjectIDCpp
,     IssuerNamesCpp
,     IssuersCpp
,     NotionalsCpp
,     ReferenceDateCpp
,     AttachmentRatioCpp
,     DettachmentRatioCpp
,     AmortizingCpp
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

void CreditBasketSetLossModelWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_REFERENCE(DefaultLossModelLibObjPtr, mDefaultLossModel,
      QuantLibAddin::DefaultLossModel, QuantLib::DefaultLossModel)

       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::Basket, QuantLib::Basket)


  // invoke the member function
  ObjectIDLibObjPtr->setLossModel(
        DefaultLossModelLibObjPtr
       );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::CreditBasketSetLossModel) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsString()) {
      return Nan::ThrowError("DefaultLossModel is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  String::Utf8Value strDefaultLossModel(info[1]->ToString());
  string DefaultLossModelCpp(strdup(*strDefaultLossModel));

 
  // launch worker
  CreditBasketSetLossModelWorker* worker = new CreditBasketSetLossModelWorker(
    ObjectIDCpp
,     DefaultLossModelCpp
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

void CreditBasketSizeWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::Basket, QuantLib::Basket)


  // invoke the member function
  QuantLib::Size returnValue = ObjectIDLibObjPtr->size(
      );


  mReturnValue = QuantLibAddin::libraryToScalar(returnValue);

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::CreditBasketSize) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  CreditBasketSizeWorker* worker = new CreditBasketSizeWorker(
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

void CreditBasketLiveNotionalWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::Basket, QuantLib::Basket)


  // invoke the member function
  QuantLib::Real returnValue = ObjectIDLibObjPtr->remainingNotional(
      );


  mReturnValue = returnValue;

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::CreditBasketLiveNotional) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  CreditBasketLiveNotionalWorker* worker = new CreditBasketLiveNotionalWorker(
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

void CreditBasketLossWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::Basket, QuantLib::Basket)


  // invoke the member function
  QuantLib::Real returnValue = ObjectIDLibObjPtr->cumulatedLoss(
      );


  mReturnValue = returnValue;

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::CreditBasketLoss) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  CreditBasketLossWorker* worker = new CreditBasketLossWorker(
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

void CreditBasketAttachLiveWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::Basket, QuantLib::Basket)


  // invoke the member function
  QuantLib::Real returnValue = ObjectIDLibObjPtr->remainingAttachmentAmount(
      );


  mReturnValue = returnValue;

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::CreditBasketAttachLive) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  CreditBasketAttachLiveWorker* worker = new CreditBasketAttachLiveWorker(
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

void CreditBasketDetachLiveWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::Basket, QuantLib::Basket)


  // invoke the member function
  QuantLib::Real returnValue = ObjectIDLibObjPtr->remainingDetachmentAmount(
      );


  mReturnValue = returnValue;

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::CreditBasketDetachLive) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  CreditBasketDetachLiveWorker* worker = new CreditBasketDetachLiveWorker(
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

void ExpectedTrancheLossWorker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes
  QuantLib::Date DateForLossLib = ObjectHandler::convert2<QuantLib::Date>(
      mDateForLoss, "DateForLoss");

       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::Basket, QuantLib::Basket)


  // invoke the member function
  QuantLib::Real returnValue = ObjectIDLibObjPtr->expectedTrancheLoss(
        DateForLossLib
       );


  mReturnValue = returnValue;

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::ExpectedTrancheLoss) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  ObjectHandler::property_t DateForLossCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[1]).FromJust()));

 
  // launch worker
  ExpectedTrancheLossWorker* worker = new ExpectedTrancheLossWorker(
    ObjectIDCpp
,     DateForLossCpp
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

void CreditBasketPercentileWorker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes
  QuantLib::Date DateForLossLib = ObjectHandler::convert2<QuantLib::Date>(
      mDateForLoss, "DateForLoss");


  // convert input datatypes to QuantLib datatypes
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::Basket, QuantLib::Basket)


  // invoke the member function
  QuantLib::Real returnValue = ObjectIDLibObjPtr->percentile(
        DateForLossLib
        ,
         mPercentileValue
       );


  mReturnValue = returnValue;

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::CreditBasketPercentile) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 2 || !info[2]->IsNumber()) {
      return Nan::ThrowError("PercentileValue is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  ObjectHandler::property_t DateForLossCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[1]).FromJust()));

  // convert js argument to c++ type
  double PercentileValueCpp = Nan::To<double>(info[2]).FromJust();

 
  // launch worker
  CreditBasketPercentileWorker* worker = new CreditBasketPercentileWorker(
    ObjectIDCpp
,     DateForLossCpp
,     PercentileValueCpp
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

void CreditBasketESFWorker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes
  QuantLib::Date DateForLossLib = ObjectHandler::convert2<QuantLib::Date>(
      mDateForLoss, "DateForLoss");


  // convert input datatypes to QuantLib datatypes
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::Basket, QuantLib::Basket)


  // invoke the member function
  QuantLib::Real returnValue = ObjectIDLibObjPtr->expectedShortfall(
        DateForLossLib
        ,
         mPercentileValue
       );


  mReturnValue = returnValue;

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::CreditBasketESF) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 2 || !info[2]->IsNumber()) {
      return Nan::ThrowError("PercentileValue is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  ObjectHandler::property_t DateForLossCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[1]).FromJust()));

  // convert js argument to c++ type
  double PercentileValueCpp = Nan::To<double>(info[2]).FromJust();

 
  // launch worker
  CreditBasketESFWorker* worker = new CreditBasketESFWorker(
    ObjectIDCpp
,     DateForLossCpp
,     PercentileValueCpp
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

void CreditBasketNthEventPWorker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes
  QuantLib::Size EventOrderLib;
  QuantLibAddin::cppToLibrary(mEventOrder, EventOrderLib);


  // convert input datatypes to QuantLib datatypes
  QuantLib::Date DateForLossLib = ObjectHandler::convert2<QuantLib::Date>(
      mDateForLoss, "DateForLoss");

       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::Basket, QuantLib::Basket)


  // loop on the input parameter and populate the return vector
  std::vector<QuantLib::Real> returnValue = ObjectIDLibObjPtr->probsBeingNthEvent(
        EventOrderLib
        ,
         DateForLossLib
       );


  mReturnValue = QuantLibAddin::libraryToVector(returnValue);

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::CreditBasketNthEventP) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsNumber()) {
      return Nan::ThrowError("EventOrder is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  long EventOrderCpp = Nan::To<int32_t>(info[1]).FromJust();

  // convert js argument to c++ type
  ObjectHandler::property_t DateForLossCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[2]).FromJust()));

 
  // launch worker
  CreditBasketNthEventPWorker* worker = new CreditBasketNthEventPWorker(
    ObjectIDCpp
,     EventOrderCpp
,     DateForLossCpp
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

void CreditBasketProbLossWorker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes
  QuantLib::Date DateForLossLib = ObjectHandler::convert2<QuantLib::Date>(
      mDateForLoss, "DateForLoss");


  // convert input datatypes to QuantLib datatypes
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::Basket, QuantLib::Basket)


  // invoke the member function
  QuantLib::Real returnValue = ObjectIDLibObjPtr->probOverLoss(
        DateForLossLib
        ,
         mLossFractionValue
       );


  mReturnValue = returnValue;

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::CreditBasketProbLoss) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 2 || !info[2]->IsNumber()) {
      return Nan::ThrowError("LossFractionValue is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  ObjectHandler::property_t DateForLossCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[1]).FromJust()));

  // convert js argument to c++ type
  double LossFractionValueCpp = Nan::To<double>(info[2]).FromJust();

 
  // launch worker
  CreditBasketProbLossWorker* worker = new CreditBasketProbLossWorker(
    ObjectIDCpp
,     DateForLossCpp
,     LossFractionValueCpp
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

void CreditBasketSplitLossWorker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes
  QuantLib::Date DateForLossLib = ObjectHandler::convert2<QuantLib::Date>(
      mDateForLoss, "DateForLoss");


  // convert input datatypes to QuantLib datatypes
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::Basket, QuantLib::Basket)


  // loop on the input parameter and populate the return vector
  std::vector<QuantLib::Real> returnValue = ObjectIDLibObjPtr->splitVaRLevel(
        DateForLossLib
        ,
         mLossValue
       );


  mReturnValue = QuantLibAddin::libraryToVector(returnValue);

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::CreditBasketSplitLoss) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 2 || !info[2]->IsNumber()) {
      return Nan::ThrowError("LossValue is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  ObjectHandler::property_t DateForLossCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[1]).FromJust()));

  // convert js argument to c++ type
  double LossValueCpp = Nan::To<double>(info[2]).FromJust();

 
  // launch worker
  CreditBasketSplitLossWorker* worker = new CreditBasketSplitLossWorker(
    ObjectIDCpp
,     DateForLossCpp
,     LossValueCpp
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

void CreditBasketDefaulCorrelWorker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes
  QuantLib::Date DateCorrelLib = ObjectHandler::convert2<QuantLib::Date>(
      mDateCorrel, "DateCorrel");


  // convert input datatypes to QuantLib datatypes
  QuantLib::Size IndexIssuer1Lib;
  QuantLibAddin::cppToLibrary(mIndexIssuer1, IndexIssuer1Lib);


  // convert input datatypes to QuantLib datatypes
  QuantLib::Size IndexIssuer2Lib;
  QuantLibAddin::cppToLibrary(mIndexIssuer2, IndexIssuer2Lib);

       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::Basket, QuantLib::Basket)


  // invoke the member function
  QuantLib::Real returnValue = ObjectIDLibObjPtr->defaultCorrelation(
        DateCorrelLib
        ,
         IndexIssuer1Lib
        ,
         IndexIssuer2Lib
       );


  mReturnValue = returnValue;

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::CreditBasketDefaulCorrel) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 2 || !info[2]->IsNumber()) {
      return Nan::ThrowError("IndexIssuer1 is required.");
  }
  if (info.Length() == 3 || !info[3]->IsNumber()) {
      return Nan::ThrowError("IndexIssuer2 is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  ObjectHandler::property_t DateCorrelCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[1]).FromJust()));

  // convert js argument to c++ type
  long IndexIssuer1Cpp = Nan::To<int32_t>(info[2]).FromJust();

  // convert js argument to c++ type
  long IndexIssuer2Cpp = Nan::To<int32_t>(info[3]).FromJust();

 
  // launch worker
  CreditBasketDefaulCorrelWorker* worker = new CreditBasketDefaulCorrelWorker(
    ObjectIDCpp
,     DateCorrelCpp
,     IndexIssuer1Cpp
,     IndexIssuer2Cpp
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
 