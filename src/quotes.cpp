/* 
  Copyright (C) 2016 -2017 Jerry Jin
*/

#include <nan.h>
#include <string.h>

#include "quotes.hpp"

#include <qlo/qladdindefines.hpp>
#include <qlo/quotes.hpp>
#include <qlo/indexes/iborindex.hpp>
#include <qlo/indexes/swapindex.hpp>
#include <qlo/handleimpl.hpp>
#include <qlo/conversions/coercequote.hpp>
#include <ql/quotes/simplequote.hpp>
#include <ql/quotes/derivedquote.hpp>
#include <ql/quotes/eurodollarfuturesquote.hpp>
#include <ql/quotes/forwardvaluequote.hpp>
#include <ql/quotes/futuresconvadjustmentquote.hpp>
#include <ql/quotes/lastfixingquote.hpp>
#include <ql/quotes/impliedstddevquote.hpp>
#include <ql/experimental/risk/sensitivityanalysis.hpp>
#include <ql/indexes/swapindex.hpp>
#include <qlo/capletvolstructure.hpp>
#include <qlo/baseinstruments.hpp>
 #include <oh/objecthandler.hpp>
#include <oh/conversions/getobjectvector.hpp>
#include <qlo/valueobjects/vo_all.hpp>
#include <qlo/conversions/all.hpp>
#include "../loop.hpp"


void SimpleQuoteWorker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes

  // convert input datatypes to QuantLib datatypes
 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlSimpleQuote(
          mObjectID,
          mValue,
          mTickValue,
          false
      ));

    // Construct the Object
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::SimpleQuote(
          valueObject,
          mValue,
          mTickValue,
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

NAN_METHOD(QuantLibXL::SimpleQuote) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsNumber()) {
      return Nan::ThrowError("Value is required.");
  }
  if (info.Length() == 2 || !info[2]->IsNumber()) {
      return Nan::ThrowError("TickValue is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  double ValueCpp = Nan::To<double>(info[1]).FromJust();

  // convert js argument to c++ type
  double TickValueCpp = Nan::To<double>(info[2]).FromJust();

 
  // launch worker
  SimpleQuoteWorker* worker = new SimpleQuoteWorker(
    ObjectIDCpp
,     ValueCpp
,     TickValueCpp
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

void ForwardValueQuoteWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_REFERENCE(IborIndexLibObjPtr, mIborIndex,
      QuantLibAddin::IborIndex, QuantLib::IborIndex)


  // convert input datatypes to QuantLib datatypes
  QuantLib::Date FixingDateLib = ObjectHandler::convert2<QuantLib::Date>(
      mFixingDate, "FixingDate");

 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlForwardValueQuote(
          mObjectID,
          mIborIndex,
          mFixingDate,
          false
      ));

    // Construct the Object
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::ForwardValueQuote(
          valueObject,
          IborIndexLibObjPtr,
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

NAN_METHOD(QuantLibXL::ForwardValueQuote) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsString()) {
      return Nan::ThrowError("IborIndex is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  String::Utf8Value strIborIndex(info[1]->ToString());
  string IborIndexCpp(strdup(*strIborIndex));

  // convert js argument to c++ type
  ObjectHandler::property_t FixingDateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[2]).FromJust()));

 
  // launch worker
  ForwardValueQuoteWorker* worker = new ForwardValueQuoteWorker(
    ObjectIDCpp
,     IborIndexCpp
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

void ForwardSwapQuoteWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_REFERENCE(SwapIndexLibObjPtr, mSwapIndex,
      QuantLibAddin::SwapIndex, QuantLib::SwapIndex)


  // convert object IDs into library objects
  QuantLib::Handle<QuantLib::Quote> SpreadLibObj =
      ObjectHandler::convert2< QuantLib::Handle<QuantLib::Quote> >(mSpread, "Spread");


  // convert input datatypes to QuantLib datatypes
  QuantLib::Period ForwardStartLib;
  QuantLibAddin::cppToLibrary(mForwardStart, ForwardStartLib);

 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlForwardSwapQuote(
          mObjectID,
          mSwapIndex,
          mSpread,
          mForwardStart,
          false
      ));

    // Construct the Object
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::ForwardSwapQuote(
          valueObject,
          SwapIndexLibObjPtr,
          SpreadLibObj,
          ForwardStartLib,
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

NAN_METHOD(QuantLibXL::ForwardSwapQuote) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsString()) {
      return Nan::ThrowError("SwapIndex is required.");
  }
  if (info.Length() == 3 || !info[3]->IsString()) {
      return Nan::ThrowError("ForwardStart is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  String::Utf8Value strSwapIndex(info[1]->ToString());
  string SwapIndexCpp(strdup(*strSwapIndex));

  // convert js argument to c++ type
  ObjectHandler::property_t SpreadCpp =
      ObjectHandler::property_t(static_cast<double>(Nan::To<double>(info[2]).FromJust()));

  // convert js argument to c++ type
  String::Utf8Value strForwardStart(info[3]->ToString());
  string ForwardStartCpp(strdup(*strForwardStart));

 
  // launch worker
  ForwardSwapQuoteWorker* worker = new ForwardSwapQuoteWorker(
    ObjectIDCpp
,     SwapIndexCpp
,     SpreadCpp
,     ForwardStartCpp
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

void ImpliedStdDevQuoteWorker::Execute(){

  try{

  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::Option::Type OptionTypeEnum =
      ObjectHandler::Create<QuantLib::Option::Type>()(mOptionType);


  // convert object IDs into library objects
  QuantLib::Handle<QuantLib::Quote> AtmForwardValueLibObj =
      ObjectHandler::convert2< QuantLib::Handle<QuantLib::Quote> >(mAtmForwardValue, "AtmForwardValue");


  // convert object IDs into library objects
  QuantLib::Handle<QuantLib::Quote> OptionPriceLibObj =
      ObjectHandler::convert2< QuantLib::Handle<QuantLib::Quote> >(mOptionPrice, "OptionPrice");


  // convert input datatypes to QuantLib datatypes

  // convert input datatypes to QuantLib datatypes

  // convert input datatypes to QuantLib datatypes
 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlImpliedStdDevQuote(
          mObjectID,
          mOptionType,
          mAtmForwardValue,
          mOptionPrice,
          mStrike,
          mGuess,
          mAccuracy,
          false
      ));

    // Construct the Object
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::ImpliedStdDevQuote(
          valueObject,
          OptionTypeEnum,
          AtmForwardValueLibObj,
          OptionPriceLibObj,
          mStrike,
          mGuess,
          mAccuracy,
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

NAN_METHOD(QuantLibXL::ImpliedStdDevQuote) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsString()) {
      return Nan::ThrowError("OptionType is required.");
  }
  if (info.Length() == 4 || !info[4]->IsNumber()) {
      return Nan::ThrowError("Strike is required.");
  }
  if (info.Length() == 5 || !info[5]->IsNumber()) {
      return Nan::ThrowError("Guess is required.");
  }
  if (info.Length() == 6 || !info[6]->IsNumber()) {
      return Nan::ThrowError("Accuracy is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  String::Utf8Value strOptionType(info[1]->ToString());
  string OptionTypeCpp(strdup(*strOptionType));

  // convert js argument to c++ type
  ObjectHandler::property_t AtmForwardValueCpp =
      ObjectHandler::property_t(static_cast<double>(Nan::To<double>(info[2]).FromJust()));

  // convert js argument to c++ type
  ObjectHandler::property_t OptionPriceCpp =
      ObjectHandler::property_t(static_cast<double>(Nan::To<double>(info[3]).FromJust()));

  // convert js argument to c++ type
  double StrikeCpp = Nan::To<double>(info[4]).FromJust();

  // convert js argument to c++ type
  double GuessCpp = Nan::To<double>(info[5]).FromJust();

  // convert js argument to c++ type
  double AccuracyCpp = Nan::To<double>(info[6]).FromJust();

 
  // launch worker
  ImpliedStdDevQuoteWorker* worker = new ImpliedStdDevQuoteWorker(
    ObjectIDCpp
,     OptionTypeCpp
,     AtmForwardValueCpp
,     OptionPriceCpp
,     StrikeCpp
,     GuessCpp
,     AccuracyCpp
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

void EurodollarFuturesImpliedStdDevQuoteWorker::Execute(){

  try{

  // convert object IDs into library objects
  QuantLib::Handle<QuantLib::Quote> AtmForwardValueLibObj =
      ObjectHandler::convert2< QuantLib::Handle<QuantLib::Quote> >(mAtmForwardValue, "AtmForwardValue");


  // convert object IDs into library objects
  QuantLib::Handle<QuantLib::Quote> CallPriceLibObj =
      ObjectHandler::convert2< QuantLib::Handle<QuantLib::Quote> >(mCallPrice, "CallPrice");


  // convert object IDs into library objects
  QuantLib::Handle<QuantLib::Quote> PutPriceLibObj =
      ObjectHandler::convert2< QuantLib::Handle<QuantLib::Quote> >(mPutPrice, "PutPrice");


  // convert input datatypes to QuantLib datatypes

  // convert input datatypes to QuantLib datatypes

  // convert input datatypes to QuantLib datatypes
 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlEurodollarFuturesImpliedStdDevQuote(
          mObjectID,
          mAtmForwardValue,
          mCallPrice,
          mPutPrice,
          mStrike,
          mGuess,
          mAccuracy,
          false
      ));

    // Construct the Object
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::EurodollarFuturesImpliedStdDevQuote(
          valueObject,
          AtmForwardValueLibObj,
          CallPriceLibObj,
          PutPriceLibObj,
          mStrike,
          mGuess,
          mAccuracy,
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

NAN_METHOD(QuantLibXL::EurodollarFuturesImpliedStdDevQuote) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 4 || !info[4]->IsNumber()) {
      return Nan::ThrowError("Strike is required.");
  }
  if (info.Length() == 5 || !info[5]->IsNumber()) {
      return Nan::ThrowError("Guess is required.");
  }
  if (info.Length() == 6 || !info[6]->IsNumber()) {
      return Nan::ThrowError("Accuracy is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  ObjectHandler::property_t AtmForwardValueCpp =
      ObjectHandler::property_t(static_cast<double>(Nan::To<double>(info[1]).FromJust()));

  // convert js argument to c++ type
  ObjectHandler::property_t CallPriceCpp =
      ObjectHandler::property_t(static_cast<double>(Nan::To<double>(info[2]).FromJust()));

  // convert js argument to c++ type
  ObjectHandler::property_t PutPriceCpp =
      ObjectHandler::property_t(static_cast<double>(Nan::To<double>(info[3]).FromJust()));

  // convert js argument to c++ type
  double StrikeCpp = Nan::To<double>(info[4]).FromJust();

  // convert js argument to c++ type
  double GuessCpp = Nan::To<double>(info[5]).FromJust();

  // convert js argument to c++ type
  double AccuracyCpp = Nan::To<double>(info[6]).FromJust();

 
  // launch worker
  EurodollarFuturesImpliedStdDevQuoteWorker* worker = new EurodollarFuturesImpliedStdDevQuoteWorker(
    ObjectIDCpp
,     AtmForwardValueCpp
,     CallPriceCpp
,     PutPriceCpp
,     StrikeCpp
,     GuessCpp
,     AccuracyCpp
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

void CompositeQuoteWorker::Execute(){

  try{

  // convert object IDs into library objects
  QuantLib::Handle<QuantLib::Quote> Element1LibObj =
      ObjectHandler::convert2< QuantLib::Handle<QuantLib::Quote> >(mElement1, "Element1");


  // convert object IDs into library objects
  QuantLib::Handle<QuantLib::Quote> Element2LibObj =
      ObjectHandler::convert2< QuantLib::Handle<QuantLib::Quote> >(mElement2, "Element2");

 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlCompositeQuote(
          mObjectID,
          mElement1,
          mElement2,
          mOperator,
          false
      ));

    // Construct the Object
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::CompositeQuote(
          valueObject,
          Element1LibObj,
          Element2LibObj,
          mOperator,
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

NAN_METHOD(QuantLibXL::CompositeQuote) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 3 || !info[3]->IsString()) {
      return Nan::ThrowError("Operator is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  ObjectHandler::property_t Element1Cpp =
      ObjectHandler::property_t(static_cast<double>(Nan::To<double>(info[1]).FromJust()));

  // convert js argument to c++ type
  ObjectHandler::property_t Element2Cpp =
      ObjectHandler::property_t(static_cast<double>(Nan::To<double>(info[2]).FromJust()));

  // convert js argument to c++ type
  String::Utf8Value strOperator(info[3]->ToString());
  string OperatorCpp(strdup(*strOperator));

 
  // launch worker
  CompositeQuoteWorker* worker = new CompositeQuoteWorker(
    ObjectIDCpp
,     Element1Cpp
,     Element2Cpp
,     OperatorCpp
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

void FuturesConvAdjustmentQuoteWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_REFERENCE(IborIndexLibObjPtr, mIborIndex,
      QuantLibAddin::IborIndex, QuantLib::IborIndex)


  // convert object IDs into library objects
  QuantLib::Handle<QuantLib::Quote> FuturesQuoteLibObj =
      ObjectHandler::convert2< QuantLib::Handle<QuantLib::Quote> >(mFuturesQuote, "FuturesQuote");


  // convert object IDs into library objects
  QuantLib::Handle<QuantLib::Quote> VolatilityLibObj =
      ObjectHandler::convert2< QuantLib::Handle<QuantLib::Quote> >(mVolatility, "Volatility");


  // convert object IDs into library objects
  QuantLib::Handle<QuantLib::Quote> MeanReversionLibObj =
      ObjectHandler::convert2< QuantLib::Handle<QuantLib::Quote> >(mMeanReversion, "MeanReversion");

 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlFuturesConvAdjustmentQuote(
          mObjectID,
          mIborIndex,
          mImmCode,
          mFuturesQuote,
          mVolatility,
          mMeanReversion,
          false
      ));

    // Construct the Object
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::FuturesConvAdjustmentQuote(
          valueObject,
          IborIndexLibObjPtr,
          mImmCode,
          FuturesQuoteLibObj,
          VolatilityLibObj,
          MeanReversionLibObj,
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

NAN_METHOD(QuantLibXL::FuturesConvAdjustmentQuote) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsString()) {
      return Nan::ThrowError("IborIndex is required.");
  }
  if (info.Length() == 2 || !info[2]->IsString()) {
      return Nan::ThrowError("ImmCode is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  String::Utf8Value strIborIndex(info[1]->ToString());
  string IborIndexCpp(strdup(*strIborIndex));

  // convert js argument to c++ type
  String::Utf8Value strImmCode(info[2]->ToString());
  string ImmCodeCpp(strdup(*strImmCode));

  // convert js argument to c++ type
  ObjectHandler::property_t FuturesQuoteCpp =
      ObjectHandler::property_t(static_cast<double>(Nan::To<double>(info[3]).FromJust()));

  // convert js argument to c++ type
  ObjectHandler::property_t VolatilityCpp =
      ObjectHandler::property_t(static_cast<double>(Nan::To<double>(info[4]).FromJust()));

  // convert js argument to c++ type
  ObjectHandler::property_t MeanReversionCpp =
      ObjectHandler::property_t(static_cast<double>(Nan::To<double>(info[5]).FromJust()));

 
  // launch worker
  FuturesConvAdjustmentQuoteWorker* worker = new FuturesConvAdjustmentQuoteWorker(
    ObjectIDCpp
,     IborIndexCpp
,     ImmCodeCpp
,     FuturesQuoteCpp
,     VolatilityCpp
,     MeanReversionCpp
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

void LastFixingQuoteWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_REFERENCE(IndexLibObjPtr, mIndex,
      QuantLibAddin::Index, QuantLib::Index)

 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlLastFixingQuote(
          mObjectID,
          mIndex,
          false
      ));

    // Construct the Object
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::LastFixingQuote(
          valueObject,
          IndexLibObjPtr,
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

NAN_METHOD(QuantLibXL::LastFixingQuote) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsString()) {
      return Nan::ThrowError("Index is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  String::Utf8Value strIndex(info[1]->ToString());
  string IndexCpp(strdup(*strIndex));

 
  // launch worker
  LastFixingQuoteWorker* worker = new LastFixingQuoteWorker(
    ObjectIDCpp
,     IndexCpp
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

void RelinkableHandleQuoteWorker::Execute(){

  try{
 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlRelinkableHandleQuote(
          mObjectID,
          mCurrentLink,
          false
      ));

    // Construct the Object
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::RelinkableHandleImpl<QuantLibAddin::Quote, QuantLib::Quote>(
          valueObject,
          mCurrentLink,
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

NAN_METHOD(QuantLibXL::RelinkableHandleQuote) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsString()) {
      return Nan::ThrowError("CurrentLink is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  String::Utf8Value strCurrentLink(info[1]->ToString());
  string CurrentLinkCpp(strdup(*strCurrentLink));

 
  // launch worker
  RelinkableHandleQuoteWorker* worker = new RelinkableHandleQuoteWorker(
    ObjectIDCpp
,     CurrentLinkCpp
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

void QuoteValueWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::Quote, QuantLib::Quote)


  // invoke the member function
  QuantLib::Real returnValue = ObjectIDLibObjPtr->value(
      );


  mReturnValue = returnValue;

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::QuoteValue) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  QuoteValueWorker* worker = new QuoteValueWorker(
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

void QuoteIsValidWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::Quote, QuantLib::Quote)


  // invoke the member function
  mReturnValue = ObjectIDLibObjPtr->isValid(
      );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::QuoteIsValid) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  QuoteIsValidWorker* worker = new QuoteIsValidWorker(
    ObjectIDCpp
   );

  worker->Execute();


  Local<v8::Value> argv[2] = {
		  Nan::New<String>(worker->mError).ToLocalChecked(),
      Nan::New<Boolean>(worker->mReturnValue)
	};

  v8::Local<v8::Array> results = Nan::New<v8::Array>();
  Nan::Set(results, 0, argv[0]);
  Nan::Set(results, 1, argv[1]);
  info.GetReturnValue().Set(results);
}

void SimpleQuoteResetWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::SimpleQuote, QuantLib::SimpleQuote)


  // invoke the member function
  ObjectIDLibObjPtr->reset(
      );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::SimpleQuoteReset) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  SimpleQuoteResetWorker* worker = new SimpleQuoteResetWorker(
    ObjectIDCpp
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

void SimpleQuoteSetValueWorker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes
       // convert object IDs into library objects
  OH_GET_OBJECT(ObjectIDObjPtr, mObjectID, QuantLibAddin::SimpleQuote)


  // invoke the member function
  QuantLib::Real returnValue = ObjectIDObjPtr->setValue(
        mValue
       );


  mReturnValue = returnValue;

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::SimpleQuoteSetValue) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsNumber()) {
      return Nan::ThrowError("Value is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  double ValueCpp = Nan::To<double>(info[1]).FromJust();

 
  // launch worker
  SimpleQuoteSetValueWorker* worker = new SimpleQuoteSetValueWorker(
    ObjectIDCpp
,     ValueCpp
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

void SimpleQuoteSetTickValueWorker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes
       // convert object IDs into library objects
  OH_GET_OBJECT(ObjectIDObjPtr, mObjectID, QuantLibAddin::SimpleQuote)


  // invoke the member function
  ObjectIDObjPtr->setTickValue(
        mValue
       );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::SimpleQuoteSetTickValue) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsNumber()) {
      return Nan::ThrowError("Value is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  double ValueCpp = Nan::To<double>(info[1]).FromJust();

 
  // launch worker
  SimpleQuoteSetTickValueWorker* worker = new SimpleQuoteSetTickValueWorker(
    ObjectIDCpp
,     ValueCpp
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

void SimpleQuoteTickValueWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_OBJECT(ObjectIDObjPtr, mObjectID, QuantLibAddin::SimpleQuote)


  // invoke the member function
  QuantLib::Real returnValue = ObjectIDObjPtr->tickValue(
      );


  mReturnValue = returnValue;

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::SimpleQuoteTickValue) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  SimpleQuoteTickValueWorker* worker = new SimpleQuoteTickValueWorker(
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

void FuturesConvAdjustmentQuoteVolatilityWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::FuturesConvAdjustmentQuote, QuantLib::FuturesConvAdjustmentQuote)


  // invoke the member function
  QuantLib::Real returnValue = ObjectIDLibObjPtr->volatility(
      );


  mReturnValue = returnValue;

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::FuturesConvAdjustmentQuoteVolatility) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  FuturesConvAdjustmentQuoteVolatilityWorker* worker = new FuturesConvAdjustmentQuoteVolatilityWorker(
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

void FuturesConvAdjustmentQuoteMeanReversionWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::FuturesConvAdjustmentQuote, QuantLib::FuturesConvAdjustmentQuote)


  // invoke the member function
  QuantLib::Real returnValue = ObjectIDLibObjPtr->meanReversion(
      );


  mReturnValue = returnValue;

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::FuturesConvAdjustmentQuoteMeanReversion) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  FuturesConvAdjustmentQuoteMeanReversionWorker* worker = new FuturesConvAdjustmentQuoteMeanReversionWorker(
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

void FuturesConvAdjustmentQuoteImmDateWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::FuturesConvAdjustmentQuote, QuantLib::FuturesConvAdjustmentQuote)


  // invoke the member function
  QuantLib::Date returnValue = ObjectIDLibObjPtr->immDate(
      );


  mReturnValue = QuantLibAddin::libraryToScalar(returnValue);

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::FuturesConvAdjustmentQuoteImmDate) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  FuturesConvAdjustmentQuoteImmDateWorker* worker = new FuturesConvAdjustmentQuoteImmDateWorker(
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

void FuturesConvAdjustmentQuoteFuturesValueWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::FuturesConvAdjustmentQuote, QuantLib::FuturesConvAdjustmentQuote)


  // invoke the member function
  QuantLib::Real returnValue = ObjectIDLibObjPtr->futuresValue(
      );


  mReturnValue = returnValue;

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::FuturesConvAdjustmentQuoteFuturesValue) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  FuturesConvAdjustmentQuoteFuturesValueWorker* worker = new FuturesConvAdjustmentQuoteFuturesValueWorker(
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

void LastFixingQuoteReferenceDateWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::LastFixingQuote, QuantLib::LastFixingQuote)


  // invoke the member function
  QuantLib::Date returnValue = ObjectIDLibObjPtr->referenceDate(
      );


  mReturnValue = QuantLibAddin::libraryToScalar(returnValue);

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::LastFixingQuoteReferenceDate) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  LastFixingQuoteReferenceDateWorker* worker = new LastFixingQuoteReferenceDateWorker(
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

void BucketAnalysisWorker::Execute(){

  try{

  // convert object IDs into library objects
  std::vector< std::vector< QuantLib::Handle<QuantLib::Quote> > > SimpleQuoteLibObj =
      ObjectHandler::matrix::convert2< QuantLib::Handle<QuantLib::Quote> >(mSimpleQuote, "SimpleQuote");


  // convert object IDs into library objects
  std::vector< boost::shared_ptr<QuantLib::Instrument> > InstrumentsLibObjPtr =
      ObjectHandler::getLibraryObjectVector<QuantLibAddin::Instrument, QuantLib::Instrument>(mInstruments);


  // convert input datatypes to QuantLib datatypes
  std::vector<QuantLib::Real> QuantitiesLib =
      QuantLibAddin::convertVector<double, QuantLib::Real>(mQuantities);


  // convert input datatypes to QuantLib datatypes

  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::SensitivityAnalysis SensitivityAnalysisEnum =
      ObjectHandler::Create<QuantLib::SensitivityAnalysis>()(mSensitivityAnalysis);

       std::vector< std::vector<QuantLib::Real> > returnValue;
  

  // invoke the utility function
  returnValue = QuantLibAddin::bucketAnalysis(
        SimpleQuoteLibObj
       ,
         InstrumentsLibObjPtr
       ,
         mQuantities
       ,
         mShift
       ,
         SensitivityAnalysisEnum
       );


  for (unsigned int i = 0; i < returnValue.size(); i++){
	  std::vector<double> tmp = QuantLibAddin::libraryToVector(returnValue[i]);
	  mReturnValue.push_back(tmp);
  }

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::BucketAnalysis) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsArray()) {
      return Nan::ThrowError("SimpleQuote is required.");
  }
  if (info.Length() == 1 || !info[1]->IsArray()) {
      return Nan::ThrowError("Instruments is required.");
  }
  if (info.Length() == 2 || !info[2]->IsArray()) {
      return Nan::ThrowError("Quantities is required.");
  }
  if (info.Length() == 3 || !info[3]->IsNumber()) {
      return Nan::ThrowError("Shift is required.");
  }
  if (info.Length() == 4 || !info[4]->IsString()) {
      return Nan::ThrowError("SensitivityAnalysis is required.");
  }
  // convert js argument to c++ type
  std::vector< std::vector<ObjectHandler::property_t> >SimpleQuoteCpp;

  Local<Array> SimpleQuoteMatrix = info[0].As<Array>();
  for (unsigned int i = 0; i < SimpleQuoteMatrix->Length(); i++){
	  Local<Array> SimpleQuoteArray = SimpleQuoteMatrix->Get(i).As<Array>();
	  std::vector<ObjectHandler::property_t> tmp;
	  for (unsigned int j = 0; j < SimpleQuoteArray->Length(); j++){
      ObjectHandler::property_t temp =
          ObjectHandler::property_t(static_cast<double>(Nan::To<double>(Nan::Get(SimpleQuoteArray, j).ToLocalChecked()).FromJust()));
		  tmp.push_back(temp);
	  }
	  SimpleQuoteCpp.push_back(tmp);
  }

  // convert js argument to c++ type
  std::vector<string>InstrumentsCpp;

  Local<Array> InstrumentsArray = info[1].As<Array>();
  for (unsigned int i = 0; i < InstrumentsArray->Length(); i++){
    String::Utf8Value strInstruments(Nan::Get(InstrumentsArray, i).ToLocalChecked()->ToString());
    InstrumentsCpp.push_back(strdup(*strInstruments));
  }

  // convert js argument to c++ type
  std::vector<double>QuantitiesCpp;

  Local<Array> QuantitiesArray = info[2].As<Array>();
  for (unsigned int i = 0; i < QuantitiesArray->Length(); i++){
    QuantitiesCpp.push_back(Nan::To<double>(Nan::Get(QuantitiesArray, i).ToLocalChecked()).FromJust());
  }

  // convert js argument to c++ type
  double ShiftCpp = Nan::To<double>(info[3]).FromJust();

  // convert js argument to c++ type
  String::Utf8Value strSensitivityAnalysis(info[4]->ToString());
  string SensitivityAnalysisCpp(strdup(*strSensitivityAnalysis));

 
  // launch worker
  BucketAnalysisWorker* worker = new BucketAnalysisWorker(
    SimpleQuoteCpp
,     InstrumentsCpp
,     QuantitiesCpp
,     ShiftCpp
,     SensitivityAnalysisCpp
   );

  worker->Execute();

    Local<Array> tmpMatrix = Nan::New<Array>(worker->mReturnValue.size());
    for (unsigned int i = 0; i < worker->mReturnValue.size(); i++) {
      Local<Array> tmpArray = Nan::New<Array>(worker->mReturnValue[i].size());
      for (unsigned int j = 0; j < worker->mReturnValue[i].size(); j++) {
        Nan::Set(tmpArray,j,Nan::New<Number>(worker->mReturnValue[i][j]));
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

void BucketAnalysisDeltaWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_OBJECT(SimpleQuoteCoerce, mSimpleQuote, ObjectHandler::Object)
  QuantLib::Handle<QuantLib::SimpleQuote> SimpleQuoteLibObj =
      QuantLibAddin::CoerceHandle<
          QuantLibAddin::SimpleQuote,
          QuantLib::SimpleQuote>()(
              SimpleQuoteCoerce);


  // convert object IDs into library objects
  std::vector< QuantLib::Handle<QuantLib::Quote> > ParametersLibObj =
      ObjectHandler::vector::convert2< QuantLib::Handle<QuantLib::Quote> >(mParameters, "Parameters");


  // convert input datatypes to QuantLib datatypes

  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::SensitivityAnalysis SensitivityAnalysisEnum =
      ObjectHandler::Create<QuantLib::SensitivityAnalysis>()(mSensitivityAnalysis);

       // invoke the utility function
  std::vector<QuantLib::Real> returnValue = QuantLibAddin::bucketAnalysisDelta(
      SimpleQuoteLibObj
      ,
       ParametersLibObj
      ,
       mShift
      ,
       SensitivityAnalysisEnum
   );


  mReturnValue = QuantLibAddin::libraryToVector(returnValue);

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::BucketAnalysisDelta) {

  // validate js arguments
  if (info.Length() == 1 || !info[1]->IsArray()) {
      return Nan::ThrowError("Parameters is required.");
  }
  if (info.Length() == 2 || !info[2]->IsNumber()) {
      return Nan::ThrowError("Shift is required.");
  }
  if (info.Length() == 3 || !info[3]->IsString()) {
      return Nan::ThrowError("SensitivityAnalysis is required.");
  }
  // convert js argument to c++ type
  ObjectHandler::property_t SimpleQuoteCpp =
      ObjectHandler::property_t(static_cast<double>(Nan::To<double>(info[0]).FromJust()));

  // convert js argument to c++ type
  std::vector<ObjectHandler::property_t>ParametersCpp;

  Local<Array> ParametersArray = info[1].As<Array>();
  for (unsigned int i = 0; i < ParametersArray->Length(); i++){
    ObjectHandler::property_t tmp =
        ObjectHandler::property_t(static_cast<double>(Nan::To<double>(Nan::Get(ParametersArray, i).ToLocalChecked()).FromJust()));
    ParametersCpp.push_back(tmp);
  }

  // convert js argument to c++ type
  double ShiftCpp = Nan::To<double>(info[2]).FromJust();

  // convert js argument to c++ type
  String::Utf8Value strSensitivityAnalysis(info[3]->ToString());
  string SensitivityAnalysisCpp(strdup(*strSensitivityAnalysis));

 
  // launch worker
  BucketAnalysisDeltaWorker* worker = new BucketAnalysisDeltaWorker(
    SimpleQuoteCpp
,     ParametersCpp
,     ShiftCpp
,     SensitivityAnalysisCpp
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

void BucketAnalysisDelta2Worker::Execute(){

  try{

  // convert object IDs into library objects
  std::vector< QuantLib::Handle<QuantLib::Quote> > SimpleQuoteLibObj =
      ObjectHandler::vector::convert2< QuantLib::Handle<QuantLib::Quote> >(mSimpleQuote, "SimpleQuote");


  // convert object IDs into library objects
  std::vector< QuantLib::Handle<QuantLib::Quote> > ParametersLibObj =
      ObjectHandler::vector::convert2< QuantLib::Handle<QuantLib::Quote> >(mParameters, "Parameters");


  // convert input datatypes to QuantLib datatypes

  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::SensitivityAnalysis SensitivityAnalysisEnum =
      ObjectHandler::Create<QuantLib::SensitivityAnalysis>()(mSensitivityAnalysis);

       std::vector< std::vector<QuantLib::Real> > returnValue;
  

  // invoke the utility function
  returnValue = QuantLibAddin::bucketAnalysisDelta2(
        SimpleQuoteLibObj
       ,
         ParametersLibObj
       ,
         mShift
       ,
         SensitivityAnalysisEnum
       );


  for (unsigned int i = 0; i < returnValue.size(); i++){
	  std::vector<double> tmp = QuantLibAddin::libraryToVector(returnValue[i]);
	  mReturnValue.push_back(tmp);
  }

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::BucketAnalysisDelta2) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsArray()) {
      return Nan::ThrowError("SimpleQuote is required.");
  }
  if (info.Length() == 1 || !info[1]->IsArray()) {
      return Nan::ThrowError("Parameters is required.");
  }
  if (info.Length() == 2 || !info[2]->IsNumber()) {
      return Nan::ThrowError("Shift is required.");
  }
  if (info.Length() == 3 || !info[3]->IsString()) {
      return Nan::ThrowError("SensitivityAnalysis is required.");
  }
  // convert js argument to c++ type
  std::vector<ObjectHandler::property_t>SimpleQuoteCpp;

  Local<Array> SimpleQuoteArray = info[0].As<Array>();
  for (unsigned int i = 0; i < SimpleQuoteArray->Length(); i++){
    ObjectHandler::property_t tmp =
        ObjectHandler::property_t(static_cast<double>(Nan::To<double>(Nan::Get(SimpleQuoteArray, i).ToLocalChecked()).FromJust()));
    SimpleQuoteCpp.push_back(tmp);
  }

  // convert js argument to c++ type
  std::vector<ObjectHandler::property_t>ParametersCpp;

  Local<Array> ParametersArray = info[1].As<Array>();
  for (unsigned int i = 0; i < ParametersArray->Length(); i++){
    ObjectHandler::property_t tmp =
        ObjectHandler::property_t(static_cast<double>(Nan::To<double>(Nan::Get(ParametersArray, i).ToLocalChecked()).FromJust()));
    ParametersCpp.push_back(tmp);
  }

  // convert js argument to c++ type
  double ShiftCpp = Nan::To<double>(info[2]).FromJust();

  // convert js argument to c++ type
  String::Utf8Value strSensitivityAnalysis(info[3]->ToString());
  string SensitivityAnalysisCpp(strdup(*strSensitivityAnalysis));

 
  // launch worker
  BucketAnalysisDelta2Worker* worker = new BucketAnalysisDelta2Worker(
    SimpleQuoteCpp
,     ParametersCpp
,     ShiftCpp
,     SensitivityAnalysisCpp
   );

  worker->Execute();

    Local<Array> tmpMatrix = Nan::New<Array>(worker->mReturnValue.size());
    for (unsigned int i = 0; i < worker->mReturnValue.size(); i++) {
      Local<Array> tmpArray = Nan::New<Array>(worker->mReturnValue[i].size());
      for (unsigned int j = 0; j < worker->mReturnValue[i].size(); j++) {
        Nan::Set(tmpArray,j,Nan::New<Number>(worker->mReturnValue[i][j]));
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
 