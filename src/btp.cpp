/* 
  Copyright (C) 2016 -2017 Jerry Jin
*/

#include <nan.h>
#include <string.h>

#include "btp.hpp"

#include <qlo/qladdindefines.hpp>
#include <qlo/btp.hpp>
#include <qlo/indexes/ibor/euribor.hpp>
#include <qlo/termstructures.hpp>
#include <ql/instruments/bonds/btp.hpp>
 #include <oh/objecthandler.hpp>
#include <oh/conversions/getobjectvector.hpp>
#include <qlo/valueobjects/vo_all.hpp>
#include <qlo/conversions/all.hpp>
#include "../loop.hpp"


void CCTEUWorker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes
  QuantLib::Date MaturityDateLib = ObjectHandler::convert2<QuantLib::Date>(
      mMaturityDate, "MaturityDate");


  // convert object IDs into library objects
  OH_GET_OBJECT(FwdCurveCoerce, mFwdCurve, ObjectHandler::Object)
  QuantLib::Handle<QuantLib::YieldTermStructure> FwdCurveLibObj =
      QuantLibAddin::CoerceHandle<
          QuantLibAddin::YieldTermStructure,
          QuantLib::YieldTermStructure>()(
              FwdCurveCoerce);


  // convert input datatypes to QuantLib datatypes
  QuantLib::Date StartDateLib = ObjectHandler::convert2<QuantLib::Date>(
      mStartDate, "StartDate");


  // convert input datatypes to QuantLib datatypes
  QuantLib::Date IssueDateLib = ObjectHandler::convert2<QuantLib::Date>(
      mIssueDate, "IssueDate");

 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlCCTEU(
          mObjectID,
          mDescription,
          mMaturityDate,
          mSpread,
          mFwdCurve,
          mStartDate,
          mIssueDate,
          false
      ));

    // Construct the Object
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::CCTEU(
          valueObject,
          mDescription,
          MaturityDateLib,
          mSpread,
          FwdCurveLibObj,
          StartDateLib,
          IssueDateLib,
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

NAN_METHOD(QuantLibXL::CCTEU) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsString()) {
      return Nan::ThrowError("Description is required.");
  }
  if (info.Length() == 3 || !info[3]->IsNumber()) {
      return Nan::ThrowError("Spread is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  String::Utf8Value strDescription(info[1]->ToString());
  string DescriptionCpp(strdup(*strDescription));

  // convert js argument to c++ type
  ObjectHandler::property_t MaturityDateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[2]).FromJust()));

  // convert js argument to c++ type
  double SpreadCpp = Nan::To<double>(info[3]).FromJust();

  // convert js argument to c++ type
  ObjectHandler::property_t FwdCurveCpp =
      ObjectHandler::property_t(static_cast<double>(Nan::To<double>(info[4]).FromJust()));

  // convert js argument to c++ type
  ObjectHandler::property_t StartDateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[5]).FromJust()));

  // convert js argument to c++ type
  ObjectHandler::property_t IssueDateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[6]).FromJust()));

 
  // launch worker
  CCTEUWorker* worker = new CCTEUWorker(
    ObjectIDCpp
,     DescriptionCpp
,     MaturityDateCpp
,     SpreadCpp
,     FwdCurveCpp
,     StartDateCpp
,     IssueDateCpp
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

void BTPWorker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes
  QuantLib::Date MaturityDateLib = ObjectHandler::convert2<QuantLib::Date>(
      mMaturityDate, "MaturityDate");


  // convert input datatypes to QuantLib datatypes
  QuantLib::Date StartDateLib = ObjectHandler::convert2<QuantLib::Date>(
      mStartDate, "StartDate");


  // convert input datatypes to QuantLib datatypes
  QuantLib::Date IssueDateLib = ObjectHandler::convert2<QuantLib::Date>(
      mIssueDate, "IssueDate");

 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlBTP(
          mObjectID,
          mDescription,
          mMaturityDate,
          mCoupon,
          mStartDate,
          mIssueDate,
          false
      ));

    // Construct the Object
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::BTP(
          valueObject,
          mDescription,
          MaturityDateLib,
          mCoupon,
          StartDateLib,
          IssueDateLib,
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

NAN_METHOD(QuantLibXL::BTP) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsString()) {
      return Nan::ThrowError("Description is required.");
  }
  if (info.Length() == 3 || !info[3]->IsNumber()) {
      return Nan::ThrowError("Coupon is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  String::Utf8Value strDescription(info[1]->ToString());
  string DescriptionCpp(strdup(*strDescription));

  // convert js argument to c++ type
  ObjectHandler::property_t MaturityDateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[2]).FromJust()));

  // convert js argument to c++ type
  double CouponCpp = Nan::To<double>(info[3]).FromJust();

  // convert js argument to c++ type
  ObjectHandler::property_t StartDateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[4]).FromJust()));

  // convert js argument to c++ type
  ObjectHandler::property_t IssueDateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[5]).FromJust()));

 
  // launch worker
  BTPWorker* worker = new BTPWorker(
    ObjectIDCpp
,     DescriptionCpp
,     MaturityDateCpp
,     CouponCpp
,     StartDateCpp
,     IssueDateCpp
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

void BTP2Worker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes
  QuantLib::Date MaturityDateLib = ObjectHandler::convert2<QuantLib::Date>(
      mMaturityDate, "MaturityDate");


  // convert input datatypes to QuantLib datatypes

  // convert input datatypes to QuantLib datatypes
  QuantLib::Date StartDateLib = ObjectHandler::convert2<QuantLib::Date>(
      mStartDate, "StartDate");


  // convert input datatypes to QuantLib datatypes
  QuantLib::Date IssueDateLib = ObjectHandler::convert2<QuantLib::Date>(
      mIssueDate, "IssueDate");

 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlBTP2(
          mObjectID,
          mDescription,
          mMaturityDate,
          mCoupon,
          mRedemption,
          mStartDate,
          mIssueDate,
          false
      ));

    // Construct the Object
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::BTP(
          valueObject,
          mDescription,
          MaturityDateLib,
          mCoupon,
          mRedemption,
          StartDateLib,
          IssueDateLib,
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

NAN_METHOD(QuantLibXL::BTP2) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsString()) {
      return Nan::ThrowError("Description is required.");
  }
  if (info.Length() == 3 || !info[3]->IsNumber()) {
      return Nan::ThrowError("Coupon is required.");
  }
  if (info.Length() == 4 || !info[4]->IsNumber()) {
      return Nan::ThrowError("Redemption is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  String::Utf8Value strDescription(info[1]->ToString());
  string DescriptionCpp(strdup(*strDescription));

  // convert js argument to c++ type
  ObjectHandler::property_t MaturityDateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[2]).FromJust()));

  // convert js argument to c++ type
  double CouponCpp = Nan::To<double>(info[3]).FromJust();

  // convert js argument to c++ type
  double RedemptionCpp = Nan::To<double>(info[4]).FromJust();

  // convert js argument to c++ type
  ObjectHandler::property_t StartDateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[5]).FromJust()));

  // convert js argument to c++ type
  ObjectHandler::property_t IssueDateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[6]).FromJust()));

 
  // launch worker
  BTP2Worker* worker = new BTP2Worker(
    ObjectIDCpp
,     DescriptionCpp
,     MaturityDateCpp
,     CouponCpp
,     RedemptionCpp
,     StartDateCpp
,     IssueDateCpp
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

void RendistatoBasketWorker::Execute(){

  try{

  // convert object IDs into library objects
  std::vector< boost::shared_ptr<QuantLib::BTP> > BTPsLibObjPtr =
      ObjectHandler::getLibraryObjectVector<QuantLibAddin::BTP, QuantLib::BTP>(mBTPs);


  // convert input datatypes to QuantLib datatypes
  std::vector<QuantLib::Real> OutstandingsLib =
      QuantLibAddin::convertVector<double, QuantLib::Real>(mOutstandings);


  // convert object IDs into library objects
  std::vector< QuantLib::Handle<QuantLib::Quote> > PricesLibObj =
      ObjectHandler::vector::convert2< QuantLib::Handle<QuantLib::Quote> >(mPrices, "Prices");

 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlRendistatoBasket(
          mObjectID,
          mBTPs,
          mOutstandings,
          mPrices,
          false
      ));

    // Construct the Object
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::RendistatoBasket(
          valueObject,
          BTPsLibObjPtr,
          mOutstandings,
          PricesLibObj,
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

NAN_METHOD(QuantLibXL::RendistatoBasket) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsArray()) {
      return Nan::ThrowError("BTPs is required.");
  }
  if (info.Length() == 2 || !info[2]->IsArray()) {
      return Nan::ThrowError("Outstandings is required.");
  }
  if (info.Length() == 3 || !info[3]->IsArray()) {
      return Nan::ThrowError("Prices is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  std::vector<string>BTPsCpp;

  Local<Array> BTPsArray = info[1].As<Array>();
  for (unsigned int i = 0; i < BTPsArray->Length(); i++){
    String::Utf8Value strBTPs(Nan::Get(BTPsArray, i).ToLocalChecked()->ToString());
    BTPsCpp.push_back(strdup(*strBTPs));
  }

  // convert js argument to c++ type
  std::vector<double>OutstandingsCpp;

  Local<Array> OutstandingsArray = info[2].As<Array>();
  for (unsigned int i = 0; i < OutstandingsArray->Length(); i++){
    OutstandingsCpp.push_back(Nan::To<double>(Nan::Get(OutstandingsArray, i).ToLocalChecked()).FromJust());
  }

  // convert js argument to c++ type
  std::vector<ObjectHandler::property_t>PricesCpp;

  Local<Array> PricesArray = info[3].As<Array>();
  for (unsigned int i = 0; i < PricesArray->Length(); i++){
    ObjectHandler::property_t tmp =
        ObjectHandler::property_t(static_cast<double>(Nan::To<double>(Nan::Get(PricesArray, i).ToLocalChecked()).FromJust()));
    PricesCpp.push_back(tmp);
  }

 
  // launch worker
  RendistatoBasketWorker* worker = new RendistatoBasketWorker(
    ObjectIDCpp
,     BTPsCpp
,     OutstandingsCpp
,     PricesCpp
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

void RendistatoCalculatorWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_REFERENCE(RendistatoBasketLibObjPtr, mRendistatoBasket,
      QuantLibAddin::RendistatoBasket, QuantLib::RendistatoBasket)


  // convert object IDs into library objects
  OH_GET_REFERENCE(EuriborLibObjPtr, mEuribor,
      QuantLibAddin::Euribor, QuantLib::Euribor)


  // convert object IDs into library objects
  OH_GET_OBJECT(YieldCurveCoerce, mYieldCurve, ObjectHandler::Object)
  QuantLib::Handle<QuantLib::YieldTermStructure> YieldCurveLibObj =
      QuantLibAddin::CoerceHandle<
          QuantLibAddin::YieldTermStructure,
          QuantLib::YieldTermStructure>()(
              YieldCurveCoerce);

 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlRendistatoCalculator(
          mObjectID,
          mRendistatoBasket,
          mEuribor,
          mYieldCurve,
          false
      ));

    // Construct the Object
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::RendistatoCalculator(
          valueObject,
          RendistatoBasketLibObjPtr,
          EuriborLibObjPtr,
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

NAN_METHOD(QuantLibXL::RendistatoCalculator) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsString()) {
      return Nan::ThrowError("RendistatoBasket is required.");
  }
  if (info.Length() == 2 || !info[2]->IsString()) {
      return Nan::ThrowError("Euribor is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  String::Utf8Value strRendistatoBasket(info[1]->ToString());
  string RendistatoBasketCpp(strdup(*strRendistatoBasket));

  // convert js argument to c++ type
  String::Utf8Value strEuribor(info[2]->ToString());
  string EuriborCpp(strdup(*strEuribor));

  // convert js argument to c++ type
  ObjectHandler::property_t YieldCurveCpp =
      ObjectHandler::property_t(static_cast<double>(Nan::To<double>(info[3]).FromJust()));

 
  // launch worker
  RendistatoCalculatorWorker* worker = new RendistatoCalculatorWorker(
    ObjectIDCpp
,     RendistatoBasketCpp
,     EuriborCpp
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

void RendistatoEquivalentSwapLengthQuoteWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_REFERENCE(RendistatoCalculatorLibObjPtr, mRendistatoCalculator,
      QuantLibAddin::RendistatoCalculator, QuantLib::RendistatoCalculator)

 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlRendistatoEquivalentSwapLengthQuote(
          mObjectID,
          mRendistatoCalculator,
          false
      ));

    // Construct the Object
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::RendistatoEquivalentSwapLengthQuote(
          valueObject,
          RendistatoCalculatorLibObjPtr,
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

NAN_METHOD(QuantLibXL::RendistatoEquivalentSwapLengthQuote) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsString()) {
      return Nan::ThrowError("RendistatoCalculator is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  String::Utf8Value strRendistatoCalculator(info[1]->ToString());
  string RendistatoCalculatorCpp(strdup(*strRendistatoCalculator));

 
  // launch worker
  RendistatoEquivalentSwapLengthQuoteWorker* worker = new RendistatoEquivalentSwapLengthQuoteWorker(
    ObjectIDCpp
,     RendistatoCalculatorCpp
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

void RendistatoEquivalentSwapSpreadQuoteWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_REFERENCE(RendistatoCalculatorLibObjPtr, mRendistatoCalculator,
      QuantLibAddin::RendistatoCalculator, QuantLib::RendistatoCalculator)

 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlRendistatoEquivalentSwapSpreadQuote(
          mObjectID,
          mRendistatoCalculator,
          false
      ));

    // Construct the Object
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::RendistatoEquivalentSwapSpreadQuote(
          valueObject,
          RendistatoCalculatorLibObjPtr,
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

NAN_METHOD(QuantLibXL::RendistatoEquivalentSwapSpreadQuote) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsString()) {
      return Nan::ThrowError("RendistatoCalculator is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  String::Utf8Value strRendistatoCalculator(info[1]->ToString());
  string RendistatoCalculatorCpp(strdup(*strRendistatoCalculator));

 
  // launch worker
  RendistatoEquivalentSwapSpreadQuoteWorker* worker = new RendistatoEquivalentSwapSpreadQuoteWorker(
    ObjectIDCpp
,     RendistatoCalculatorCpp
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

void RendistatoBasketSizeWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::RendistatoBasket, QuantLib::RendistatoBasket)


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

NAN_METHOD(QuantLibXL::RendistatoBasketSize) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  RendistatoBasketSizeWorker* worker = new RendistatoBasketSizeWorker(
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

void RendistatoBasketOutstandingWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::RendistatoBasket, QuantLib::RendistatoBasket)


  // invoke the member function
  QuantLib::Real returnValue = ObjectIDLibObjPtr->outstanding(
      );


  mReturnValue = returnValue;

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::RendistatoBasketOutstanding) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  RendistatoBasketOutstandingWorker* worker = new RendistatoBasketOutstandingWorker(
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

void RendistatoBasketOutstandingsWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::RendistatoBasket, QuantLib::RendistatoBasket)


  // loop on the input parameter and populate the return vector
  std::vector<QuantLib::Real> returnValue = ObjectIDLibObjPtr->outstandings(
      );


  mReturnValue = QuantLibAddin::libraryToVector(returnValue);

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::RendistatoBasketOutstandings) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  RendistatoBasketOutstandingsWorker* worker = new RendistatoBasketOutstandingsWorker(
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

void RendistatoBasketWeightsWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::RendistatoBasket, QuantLib::RendistatoBasket)


  // loop on the input parameter and populate the return vector
  std::vector<QuantLib::Real> returnValue = ObjectIDLibObjPtr->weights(
      );


  mReturnValue = QuantLibAddin::libraryToVector(returnValue);

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::RendistatoBasketWeights) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  RendistatoBasketWeightsWorker* worker = new RendistatoBasketWeightsWorker(
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

void RendistatoCalculatorYieldWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::RendistatoCalculator, QuantLib::RendistatoCalculator)


  // invoke the member function
  mReturnValue = ObjectIDLibObjPtr->yield(
      );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::RendistatoCalculatorYield) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  RendistatoCalculatorYieldWorker* worker = new RendistatoCalculatorYieldWorker(
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

void RendistatoCalculatorDurationWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::RendistatoCalculator, QuantLib::RendistatoCalculator)


  // invoke the member function
  mReturnValue = ObjectIDLibObjPtr->duration(
      );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::RendistatoCalculatorDuration) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  RendistatoCalculatorDurationWorker* worker = new RendistatoCalculatorDurationWorker(
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

void RendistatoCalculatorYieldsWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::RendistatoCalculator, QuantLib::RendistatoCalculator)


  // loop on the input parameter and populate the return vector
  mReturnValue = ObjectIDLibObjPtr->yields(
      );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::RendistatoCalculatorYields) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  RendistatoCalculatorYieldsWorker* worker = new RendistatoCalculatorYieldsWorker(
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

void RendistatoCalculatorDurationsWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::RendistatoCalculator, QuantLib::RendistatoCalculator)


  // loop on the input parameter and populate the return vector
  mReturnValue = ObjectIDLibObjPtr->durations(
      );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::RendistatoCalculatorDurations) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  RendistatoCalculatorDurationsWorker* worker = new RendistatoCalculatorDurationsWorker(
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

void RendistatoCalculatorSwapLengthsWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::RendistatoCalculator, QuantLib::RendistatoCalculator)


  // loop on the input parameter and populate the return vector
  mReturnValue = ObjectIDLibObjPtr->swapLengths(
      );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::RendistatoCalculatorSwapLengths) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  RendistatoCalculatorSwapLengthsWorker* worker = new RendistatoCalculatorSwapLengthsWorker(
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

void RendistatoCalculatorSwapRatesWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::RendistatoCalculator, QuantLib::RendistatoCalculator)


  // loop on the input parameter and populate the return vector
  mReturnValue = ObjectIDLibObjPtr->swapRates(
      );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::RendistatoCalculatorSwapRates) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  RendistatoCalculatorSwapRatesWorker* worker = new RendistatoCalculatorSwapRatesWorker(
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

void RendistatoCalculatorSwapYieldsWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::RendistatoCalculator, QuantLib::RendistatoCalculator)


  // loop on the input parameter and populate the return vector
  mReturnValue = ObjectIDLibObjPtr->swapYields(
      );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::RendistatoCalculatorSwapYields) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  RendistatoCalculatorSwapYieldsWorker* worker = new RendistatoCalculatorSwapYieldsWorker(
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

void RendistatoCalculatorSwapDurationsWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::RendistatoCalculator, QuantLib::RendistatoCalculator)


  // loop on the input parameter and populate the return vector
  mReturnValue = ObjectIDLibObjPtr->swapDurations(
      );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::RendistatoCalculatorSwapDurations) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  RendistatoCalculatorSwapDurationsWorker* worker = new RendistatoCalculatorSwapDurationsWorker(
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

void RendistatoCalculatorEquivalentSwapRateWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::RendistatoCalculator, QuantLib::RendistatoCalculator)


  // invoke the member function
  mReturnValue = ObjectIDLibObjPtr->equivalentSwapRate(
      );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::RendistatoCalculatorEquivalentSwapRate) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  RendistatoCalculatorEquivalentSwapRateWorker* worker = new RendistatoCalculatorEquivalentSwapRateWorker(
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

void RendistatoCalculatorEquivalentSwapYieldWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::RendistatoCalculator, QuantLib::RendistatoCalculator)


  // invoke the member function
  mReturnValue = ObjectIDLibObjPtr->equivalentSwapYield(
      );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::RendistatoCalculatorEquivalentSwapYield) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  RendistatoCalculatorEquivalentSwapYieldWorker* worker = new RendistatoCalculatorEquivalentSwapYieldWorker(
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

void RendistatoCalculatorEquivalentSwapDurationWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::RendistatoCalculator, QuantLib::RendistatoCalculator)


  // invoke the member function
  mReturnValue = ObjectIDLibObjPtr->equivalentSwapDuration(
      );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::RendistatoCalculatorEquivalentSwapDuration) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  RendistatoCalculatorEquivalentSwapDurationWorker* worker = new RendistatoCalculatorEquivalentSwapDurationWorker(
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

void RendistatoCalculatorEquivalentSwapSpreadWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::RendistatoCalculator, QuantLib::RendistatoCalculator)


  // invoke the member function
  mReturnValue = ObjectIDLibObjPtr->equivalentSwapSpread(
      );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::RendistatoCalculatorEquivalentSwapSpread) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  RendistatoCalculatorEquivalentSwapSpreadWorker* worker = new RendistatoCalculatorEquivalentSwapSpreadWorker(
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

void RendistatoCalculatorEquivalentSwapLengthWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::RendistatoCalculator, QuantLib::RendistatoCalculator)


  // invoke the member function
  mReturnValue = ObjectIDLibObjPtr->equivalentSwapLength(
      );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::RendistatoCalculatorEquivalentSwapLength) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  RendistatoCalculatorEquivalentSwapLengthWorker* worker = new RendistatoCalculatorEquivalentSwapLengthWorker(
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
 