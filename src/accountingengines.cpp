/* 
  Copyright (C) 2016 -2017 Jerry Jin
*/

#include <nan.h>
#include <string.h>

#include "accountingengines.hpp"

#include <qlo/qladdindefines.hpp>
#include <qlo/accountingengines.hpp>
#include <qlo/marketmodelevolvers.hpp>
#include <qlo/products.hpp>
#include <qlo/sequencestatistics.hpp>
#include <ql/models/marketmodels/accountingengine.hpp>
 #include <oh/objecthandler.hpp>
#include <oh/conversions/getobjectvector.hpp>
#include <qlo/valueobjects/vo_all.hpp>
#include <qlo/conversions/all.hpp>
#include "../loop.hpp"


void AccountingEngineWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_REFERENCE(MarketModelEvolverLibObjPtr, mMarketModelEvolver,
      QuantLibAddin::MarketModelEvolver, QuantLib::MarketModelEvolver)


  // convert object IDs into library objects
  OH_GET_UNDERLYING(ProductLibObj, mProduct,
      QuantLibAddin::MarketModelMultiProduct, QuantLib::MarketModelMultiProduct)

 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlAccountingEngine(
          mObjectID,
          mMarketModelEvolver,
          mProduct,
          mInitialNumeraireValue,
          false
      ));

    // Construct the Object
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::AccountingEngine(
          valueObject,
          MarketModelEvolverLibObjPtr,
          ProductLibObj,
          mInitialNumeraireValue,
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

NAN_METHOD(QuantLibXL::AccountingEngine) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsString()) {
      return Nan::ThrowError("MarketModelEvolver is required.");
  }
  if (info.Length() == 2 || !info[2]->IsString()) {
      return Nan::ThrowError("Product is required.");
  }
  if (info.Length() == 3 || !info[3]->IsNumber()) {
      return Nan::ThrowError("InitialNumeraireValue is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  String::Utf8Value strMarketModelEvolver(info[1]->ToString());
  string MarketModelEvolverCpp(strdup(*strMarketModelEvolver));

  // convert js argument to c++ type
  String::Utf8Value strProduct(info[2]->ToString());
  string ProductCpp(strdup(*strProduct));

  // convert js argument to c++ type
  double InitialNumeraireValueCpp = Nan::To<double>(info[3]).FromJust();

 
  // launch worker
  AccountingEngineWorker* worker = new AccountingEngineWorker(
    ObjectIDCpp
,     MarketModelEvolverCpp
,     ProductCpp
,     InitialNumeraireValueCpp
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

void AccountingEngineMultiplePathValuesWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_UNDERLYING_NONCONST(SequenceStatsLibObj, mSequenceStats,
      QuantLibAddin::SequenceStatisticsInc, QuantLib::SequenceStatisticsInc)

       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::AccountingEngine, QuantLib::AccountingEngine)


  // invoke the member function
  ObjectIDLibObjPtr->multiplePathValues(
        SequenceStatsLibObj
        ,
         mPaths
       );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::AccountingEngineMultiplePathValues) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsString()) {
      return Nan::ThrowError("SequenceStats is required.");
  }
  if (info.Length() == 2 || !info[2]->IsNumber()) {
      return Nan::ThrowError("Paths is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  String::Utf8Value strSequenceStats(info[1]->ToString());
  string SequenceStatsCpp(strdup(*strSequenceStats));

  // convert js argument to c++ type
  long PathsCpp = Nan::To<int32_t>(info[2]).FromJust();

 
  // launch worker
  AccountingEngineMultiplePathValuesWorker* worker = new AccountingEngineMultiplePathValuesWorker(
    ObjectIDCpp
,     SequenceStatsCpp
,     PathsCpp
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
 