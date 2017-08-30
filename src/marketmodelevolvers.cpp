/* 
  Copyright (C) 2016 -2017 Jerry Jin
*/

#include <nan.h>
#include <string.h>

#include "marketmodelevolvers.hpp"

#include <qlo/qladdindefines.hpp>
#include <qlo/marketmodelevolvers.hpp>
#include <qlo/browniangenerators.hpp>
#include <qlo/marketmodels.hpp>
#include <ql/models/marketmodels/evolver.hpp>
 #include <oh/objecthandler.hpp>
#include <oh/conversions/getobjectvector.hpp>
#include <qlo/valueobjects/vo_all.hpp>
#include <qlo/conversions/all.hpp>
#include "../loop.hpp"


void ForwardRatePcWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_REFERENCE(MarketModelLibObjPtr, mMarketModel,
      QuantLibAddin::MarketModel, QuantLib::MarketModel)


  // convert object IDs into library objects
  OH_GET_UNDERLYING(BrownianGeneratorFactoryLibObj, mBrownianGeneratorFactory,
      QuantLibAddin::BrownianGeneratorFactory, QuantLib::BrownianGeneratorFactory)


  // convert input datatypes to QuantLib datatypes
  std::vector<long> NumerairesCpp;
  std::vector<QuantLib::Size> NumerairesLib =
      QuantLibAddin::convertVector<long, QuantLib::Size>(NumerairesCpp);

 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlForwardRatePc(
          mObjectID,
          mMarketModel,
          mBrownianGeneratorFactory,
          NumerairesCpp,
          false
      ));

    // Construct the Object
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::LogNormalFwdRatePc(
          valueObject,
          MarketModelLibObjPtr,
          BrownianGeneratorFactoryLibObj,
          NumerairesLib,
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

NAN_METHOD(QuantLibXL::ForwardRatePc) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsString()) {
      return Nan::ThrowError("MarketModel is required.");
  }
  if (info.Length() == 2 || !info[2]->IsString()) {
      return Nan::ThrowError("BrownianGeneratorFactory is required.");
  }
  if (info.Length() == 3 || !info[3]->IsArray()) {
      return Nan::ThrowError("Numeraires is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  String::Utf8Value strMarketModel(info[1]->ToString());
  string MarketModelCpp(strdup(*strMarketModel));

  // convert js argument to c++ type
  String::Utf8Value strBrownianGeneratorFactory(info[2]->ToString());
  string BrownianGeneratorFactoryCpp(strdup(*strBrownianGeneratorFactory));

  // convert js argument to c++ type
  std::vector<long>NumerairesCpp;

  Local<Array> NumerairesArray = info[3].As<Array>();
  for (unsigned int i = 0; i < NumerairesArray->Length(); i++){
    NumerairesCpp.push_back(Nan::To<int32_t>(Nan::Get(NumerairesArray, i).ToLocalChecked()).FromJust());
  }

 
  // launch worker
  ForwardRatePcWorker* worker = new ForwardRatePcWorker(
    ObjectIDCpp
,     MarketModelCpp
,     BrownianGeneratorFactoryCpp
,     NumerairesCpp
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

void ForwardRateIpcWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_REFERENCE(MarketModelLibObjPtr, mMarketModel,
      QuantLibAddin::MarketModel, QuantLib::MarketModel)


  // convert object IDs into library objects
  OH_GET_UNDERLYING(BrownianGeneratorFactoryLibObj, mBrownianGeneratorFactory,
      QuantLibAddin::BrownianGeneratorFactory, QuantLib::BrownianGeneratorFactory)


  // convert input datatypes to QuantLib datatypes
  std::vector<long> NumerairesCpp;
  std::vector<QuantLib::Size> NumerairesLib =
      QuantLibAddin::convertVector<long, QuantLib::Size>(NumerairesCpp);

 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlForwardRateIpc(
          mObjectID,
          mMarketModel,
          mBrownianGeneratorFactory,
          NumerairesCpp,
          false
      ));

    // Construct the Object
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::LogNormalFwdRateIpc(
          valueObject,
          MarketModelLibObjPtr,
          BrownianGeneratorFactoryLibObj,
          NumerairesLib,
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

NAN_METHOD(QuantLibXL::ForwardRateIpc) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsString()) {
      return Nan::ThrowError("MarketModel is required.");
  }
  if (info.Length() == 2 || !info[2]->IsString()) {
      return Nan::ThrowError("BrownianGeneratorFactory is required.");
  }
  if (info.Length() == 3 || !info[3]->IsArray()) {
      return Nan::ThrowError("Numeraires is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  String::Utf8Value strMarketModel(info[1]->ToString());
  string MarketModelCpp(strdup(*strMarketModel));

  // convert js argument to c++ type
  String::Utf8Value strBrownianGeneratorFactory(info[2]->ToString());
  string BrownianGeneratorFactoryCpp(strdup(*strBrownianGeneratorFactory));

  // convert js argument to c++ type
  std::vector<long>NumerairesCpp;

  Local<Array> NumerairesArray = info[3].As<Array>();
  for (unsigned int i = 0; i < NumerairesArray->Length(); i++){
    NumerairesCpp.push_back(Nan::To<int32_t>(Nan::Get(NumerairesArray, i).ToLocalChecked()).FromJust());
  }

 
  // launch worker
  ForwardRateIpcWorker* worker = new ForwardRateIpcWorker(
    ObjectIDCpp
,     MarketModelCpp
,     BrownianGeneratorFactoryCpp
,     NumerairesCpp
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

void ForwardRateNormalPcWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_REFERENCE(MarketModelLibObjPtr, mMarketModel,
      QuantLibAddin::MarketModel, QuantLib::MarketModel)


  // convert object IDs into library objects
  OH_GET_UNDERLYING(BrownianGeneratorFactoryLibObj, mBrownianGeneratorFactory,
      QuantLibAddin::BrownianGeneratorFactory, QuantLib::BrownianGeneratorFactory)


  // convert input datatypes to QuantLib datatypes
  std::vector<long> NumerairesCpp;
  std::vector<QuantLib::Size> NumerairesLib =
      QuantLibAddin::convertVector<long, QuantLib::Size>(NumerairesCpp);

 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlForwardRateNormalPc(
          mObjectID,
          mMarketModel,
          mBrownianGeneratorFactory,
          NumerairesCpp,
          false
      ));

    // Construct the Object
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::NormalFwdRatePc(
          valueObject,
          MarketModelLibObjPtr,
          BrownianGeneratorFactoryLibObj,
          NumerairesLib,
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

NAN_METHOD(QuantLibXL::ForwardRateNormalPc) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsString()) {
      return Nan::ThrowError("MarketModel is required.");
  }
  if (info.Length() == 2 || !info[2]->IsString()) {
      return Nan::ThrowError("BrownianGeneratorFactory is required.");
  }
  if (info.Length() == 3 || !info[3]->IsArray()) {
      return Nan::ThrowError("Numeraires is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  String::Utf8Value strMarketModel(info[1]->ToString());
  string MarketModelCpp(strdup(*strMarketModel));

  // convert js argument to c++ type
  String::Utf8Value strBrownianGeneratorFactory(info[2]->ToString());
  string BrownianGeneratorFactoryCpp(strdup(*strBrownianGeneratorFactory));

  // convert js argument to c++ type
  std::vector<long>NumerairesCpp;

  Local<Array> NumerairesArray = info[3].As<Array>();
  for (unsigned int i = 0; i < NumerairesArray->Length(); i++){
    NumerairesCpp.push_back(Nan::To<int32_t>(Nan::Get(NumerairesArray, i).ToLocalChecked()).FromJust());
  }

 
  // launch worker
  ForwardRateNormalPcWorker* worker = new ForwardRateNormalPcWorker(
    ObjectIDCpp
,     MarketModelCpp
,     BrownianGeneratorFactoryCpp
,     NumerairesCpp
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

void MarketModelEvolverStartNewPathWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::MarketModelEvolver, QuantLib::MarketModelEvolver)


  // invoke the member function
  mReturnValue = ObjectIDLibObjPtr->startNewPath(
      );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::MarketModelEvolverStartNewPath) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  MarketModelEvolverStartNewPathWorker* worker = new MarketModelEvolverStartNewPathWorker(
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

void MarketModelEvolverAdvanceStepWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::MarketModelEvolver, QuantLib::MarketModelEvolver)


  // invoke the member function
  mReturnValue = ObjectIDLibObjPtr->advanceStep(
      );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::MarketModelEvolverAdvanceStep) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  MarketModelEvolverAdvanceStepWorker* worker = new MarketModelEvolverAdvanceStepWorker(
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

void MarketModelEvolverCurrentStepWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::MarketModelEvolver, QuantLib::MarketModelEvolver)


  // invoke the member function
  QuantLib::Size returnValue = ObjectIDLibObjPtr->currentStep(
      );


  mReturnValue = QuantLibAddin::libraryToScalar(returnValue);

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::MarketModelEvolverCurrentStep) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  MarketModelEvolverCurrentStepWorker* worker = new MarketModelEvolverCurrentStepWorker(
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

void MarketModelEvolverNumerairesWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::MarketModelEvolver, QuantLib::MarketModelEvolver)


  // loop on the input parameter and populate the return vector
  std::vector<QuantLib::Size> returnValue = ObjectIDLibObjPtr->numeraires(
      );


  mReturnValue = QuantLibAddin::convertVector<QuantLib::Size, long>(returnValue);

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::MarketModelEvolverNumeraires) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  MarketModelEvolverNumerairesWorker* worker = new MarketModelEvolverNumerairesWorker(
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
 