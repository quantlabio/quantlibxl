/* 
  Copyright (C) 2016 -2017 Jerry Jin
*/

#include <nan.h>
#include <string.h>

#include "basketlossmodels.hpp"

#include <qlo/qladdindefines.hpp>
#include <ql/experimental/credit/gaussianlhplossmodel.hpp>
#include <ql/experimental/credit/binomiallossmodel.hpp>
#include <ql/experimental/credit/inhomogeneouspooldef.hpp>
#include <ql/experimental/credit/correlationstructure.hpp>
#include <qlo/basketlossmodels.hpp>
#include <qlo/defaulttermstructures.hpp>
 #include <oh/objecthandler.hpp>
#include <oh/conversions/getobjectvector.hpp>
#include <qlo/valueobjects/vo_all.hpp>
#include <qlo/conversions/all.hpp>
#include "../loop.hpp"


void GaussianLHPLossmodelWorker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes
 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlGaussianLHPLossmodel(
          mObjectID,
          mCorrelation,
          mRecoveryRates,
          false
      ));

    // Construct the Object
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::GaussianLHPLossModel(
          valueObject,
          mCorrelation,
          mRecoveryRates,
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

NAN_METHOD(QuantLibXL::GaussianLHPLossmodel) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsNumber()) {
      return Nan::ThrowError("Correlation is required.");
  }
  if (info.Length() == 2 || !info[2]->IsArray()) {
      return Nan::ThrowError("RecoveryRates is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  double CorrelationCpp = Nan::To<double>(info[1]).FromJust();

  // convert js argument to c++ type
  std::vector<double>RecoveryRatesCpp;

  Local<Array> RecoveryRatesArray = info[2].As<Array>();
  for (unsigned int i = 0; i < RecoveryRatesArray->Length(); i++){
    RecoveryRatesCpp.push_back(Nan::To<double>(Nan::Get(RecoveryRatesArray, i).ToLocalChecked()).FromJust());
  }

 
  // launch worker
  GaussianLHPLossmodelWorker* worker = new GaussianLHPLossmodelWorker(
    ObjectIDCpp
,     CorrelationCpp
,     RecoveryRatesCpp
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

void IHGaussPoolLossModelWorker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes

  // convert input datatypes to QuantLib datatypes
  QuantLib::Size NumBucketsLib;
  QuantLibAddin::cppToLibrary(mNumBuckets, NumBucketsLib);

 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlIHGaussPoolLossModel(
          mObjectID,
          mCorrelation,
          mRecoveryRates,
          mNumBuckets,
          false
      ));

    // Construct the Object
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::IHGaussPoolLossModel(
          valueObject,
          mCorrelation,
          mRecoveryRates,
          NumBucketsLib,
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

NAN_METHOD(QuantLibXL::IHGaussPoolLossModel) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsNumber()) {
      return Nan::ThrowError("Correlation is required.");
  }
  if (info.Length() == 2 || !info[2]->IsArray()) {
      return Nan::ThrowError("RecoveryRates is required.");
  }
  if (info.Length() == 3 || !info[3]->IsNumber()) {
      return Nan::ThrowError("NumBuckets is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  double CorrelationCpp = Nan::To<double>(info[1]).FromJust();

  // convert js argument to c++ type
  std::vector<double>RecoveryRatesCpp;

  Local<Array> RecoveryRatesArray = info[2].As<Array>();
  for (unsigned int i = 0; i < RecoveryRatesArray->Length(); i++){
    RecoveryRatesCpp.push_back(Nan::To<double>(Nan::Get(RecoveryRatesArray, i).ToLocalChecked()).FromJust());
  }

  // convert js argument to c++ type
  long NumBucketsCpp = Nan::To<int32_t>(info[3]).FromJust();

 
  // launch worker
  IHGaussPoolLossModelWorker* worker = new IHGaussPoolLossModelWorker(
    ObjectIDCpp
,     CorrelationCpp
,     RecoveryRatesCpp
,     NumBucketsCpp
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

void IHStudentPoolLossModelWorker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes

  // convert input datatypes to QuantLib datatypes
  QuantLib::Size NumBucketsLib;
  QuantLibAddin::cppToLibrary(mNumBuckets, NumBucketsLib);

 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlIHStudentPoolLossModel(
          mObjectID,
          mCorrelation,
          mRecoveryRates,
          mTtraits,
          mNumBuckets,
          false
      ));

    // Construct the Object
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::IHStudentPoolLossModel(
          valueObject,
          mCorrelation,
          mRecoveryRates,
          mTtraits,
          NumBucketsLib,
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

NAN_METHOD(QuantLibXL::IHStudentPoolLossModel) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsNumber()) {
      return Nan::ThrowError("Correlation is required.");
  }
  if (info.Length() == 2 || !info[2]->IsArray()) {
      return Nan::ThrowError("RecoveryRates is required.");
  }
  if (info.Length() == 3 || !info[3]->IsArray()) {
      return Nan::ThrowError("Ttraits is required.");
  }
  if (info.Length() == 4 || !info[4]->IsNumber()) {
      return Nan::ThrowError("NumBuckets is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  double CorrelationCpp = Nan::To<double>(info[1]).FromJust();

  // convert js argument to c++ type
  std::vector<double>RecoveryRatesCpp;

  Local<Array> RecoveryRatesArray = info[2].As<Array>();
  for (unsigned int i = 0; i < RecoveryRatesArray->Length(); i++){
    RecoveryRatesCpp.push_back(Nan::To<double>(Nan::Get(RecoveryRatesArray, i).ToLocalChecked()).FromJust());
  }

  // convert js argument to c++ type
  std::vector<double>TtraitsCpp;

  Local<Array> TtraitsArray = info[3].As<Array>();
  for (unsigned int i = 0; i < TtraitsArray->Length(); i++){
    TtraitsCpp.push_back(Nan::To<double>(Nan::Get(TtraitsArray, i).ToLocalChecked()).FromJust());
  }

  // convert js argument to c++ type
  long NumBucketsCpp = Nan::To<int32_t>(info[4]).FromJust();

 
  // launch worker
  IHStudentPoolLossModelWorker* worker = new IHStudentPoolLossModelWorker(
    ObjectIDCpp
,     CorrelationCpp
,     RecoveryRatesCpp
,     TtraitsCpp
,     NumBucketsCpp
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

void GBinomialLossmodelWorker::Execute(){

  try{
 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlGBinomialLossmodel(
          mObjectID,
          mFactors,
          mRecoveryRates,
          false
      ));

    // Construct the Object
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::GaussianBinomialLossModel(
          valueObject,
          mFactors,
          mRecoveryRates,
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

NAN_METHOD(QuantLibXL::GBinomialLossmodel) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsArray()) {
      return Nan::ThrowError("Factors is required.");
  }
  if (info.Length() == 2 || !info[2]->IsArray()) {
      return Nan::ThrowError("RecoveryRates is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  std::vector< std::vector<double> >FactorsCpp;

  Local<Array> FactorsMatrix = info[1].As<Array>();
  for (unsigned int i = 0; i < FactorsMatrix->Length(); i++){
	  Local<Array> FactorsArray = FactorsMatrix->Get(i).As<Array>();
	  std::vector<double> tmp;
	  for (unsigned int j = 0; j < FactorsArray->Length(); j++){
		  tmp.push_back(Nan::To<double>(Nan::Get(FactorsArray, j).ToLocalChecked()).FromJust());
	  }
	  FactorsCpp.push_back(tmp);
  }

  // convert js argument to c++ type
  std::vector<double>RecoveryRatesCpp;

  Local<Array> RecoveryRatesArray = info[2].As<Array>();
  for (unsigned int i = 0; i < RecoveryRatesArray->Length(); i++){
    RecoveryRatesCpp.push_back(Nan::To<double>(Nan::Get(RecoveryRatesArray, i).ToLocalChecked()).FromJust());
  }

 
  // launch worker
  GBinomialLossmodelWorker* worker = new GBinomialLossmodelWorker(
    ObjectIDCpp
,     FactorsCpp
,     RecoveryRatesCpp
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

void TBinomialLossmodelWorker::Execute(){

  try{
 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlTBinomialLossmodel(
          mObjectID,
          mFactors,
          mRecoveryRates,
          mTtraits,
          false
      ));

    // Construct the Object
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::TBinomialLossModel(
          valueObject,
          mFactors,
          mRecoveryRates,
          mTtraits,
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

NAN_METHOD(QuantLibXL::TBinomialLossmodel) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsArray()) {
      return Nan::ThrowError("Factors is required.");
  }
  if (info.Length() == 2 || !info[2]->IsArray()) {
      return Nan::ThrowError("RecoveryRates is required.");
  }
  if (info.Length() == 3 || !info[3]->IsArray()) {
      return Nan::ThrowError("Ttraits is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  std::vector< std::vector<double> >FactorsCpp;

  Local<Array> FactorsMatrix = info[1].As<Array>();
  for (unsigned int i = 0; i < FactorsMatrix->Length(); i++){
	  Local<Array> FactorsArray = FactorsMatrix->Get(i).As<Array>();
	  std::vector<double> tmp;
	  for (unsigned int j = 0; j < FactorsArray->Length(); j++){
		  tmp.push_back(Nan::To<double>(Nan::Get(FactorsArray, j).ToLocalChecked()).FromJust());
	  }
	  FactorsCpp.push_back(tmp);
  }

  // convert js argument to c++ type
  std::vector<double>RecoveryRatesCpp;

  Local<Array> RecoveryRatesArray = info[2].As<Array>();
  for (unsigned int i = 0; i < RecoveryRatesArray->Length(); i++){
    RecoveryRatesCpp.push_back(Nan::To<double>(Nan::Get(RecoveryRatesArray, i).ToLocalChecked()).FromJust());
  }

  // convert js argument to c++ type
  std::vector<double>TtraitsCpp;

  Local<Array> TtraitsArray = info[3].As<Array>();
  for (unsigned int i = 0; i < TtraitsArray->Length(); i++){
    TtraitsCpp.push_back(Nan::To<double>(Nan::Get(TtraitsArray, i).ToLocalChecked()).FromJust());
  }

 
  // launch worker
  TBinomialLossmodelWorker* worker = new TBinomialLossmodelWorker(
    ObjectIDCpp
,     FactorsCpp
,     RecoveryRatesCpp
,     TtraitsCpp
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

void BaseCorrelationLossModelWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_REFERENCE(BaseCorrelationSurfaceLibObjPtr, mBaseCorrelationSurface,
      QuantLibAddin::CorrelationTermStructure, QuantLib::CorrelationTermStructure)


  // convert input datatypes to QuantLib datatypes
  std::vector<QuantLib::Real> RecoveriesLib =
      QuantLibAddin::convertVector<double, QuantLib::Real>(mRecoveries);


  // convert input datatypes to QuantLib datatypes
  std::vector<QuantLib::Real> InitiTraitsLib =
      QuantLibAddin::convertVector<double, QuantLib::Real>(mInitiTraits);

 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlBaseCorrelationLossModel(
          mObjectID,
          mBaseModel,
          mBaseCorrelationSurface,
          mRecoveries,
          mInitiTraits,
          false
      ));

    // Construct the Object
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::BaseCorrelationLossModel(
          valueObject,
          mBaseModel,
          BaseCorrelationSurfaceLibObjPtr,
          mRecoveries,
          mInitiTraits,
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

NAN_METHOD(QuantLibXL::BaseCorrelationLossModel) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsString()) {
      return Nan::ThrowError("BaseModel is required.");
  }
  if (info.Length() == 2 || !info[2]->IsString()) {
      return Nan::ThrowError("BaseCorrelationSurface is required.");
  }
  if (info.Length() == 3 || !info[3]->IsArray()) {
      return Nan::ThrowError("Recoveries is required.");
  }
  if (info.Length() == 4 || !info[4]->IsArray()) {
      return Nan::ThrowError("InitiTraits is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  String::Utf8Value strBaseModel(info[1]->ToString());
  string BaseModelCpp(strdup(*strBaseModel));

  // convert js argument to c++ type
  String::Utf8Value strBaseCorrelationSurface(info[2]->ToString());
  string BaseCorrelationSurfaceCpp(strdup(*strBaseCorrelationSurface));

  // convert js argument to c++ type
  std::vector<double>RecoveriesCpp;

  Local<Array> RecoveriesArray = info[3].As<Array>();
  for (unsigned int i = 0; i < RecoveriesArray->Length(); i++){
    RecoveriesCpp.push_back(Nan::To<double>(Nan::Get(RecoveriesArray, i).ToLocalChecked()).FromJust());
  }

  // convert js argument to c++ type
  std::vector<double>InitiTraitsCpp;

  Local<Array> InitiTraitsArray = info[4].As<Array>();
  for (unsigned int i = 0; i < InitiTraitsArray->Length(); i++){
    InitiTraitsCpp.push_back(Nan::To<double>(Nan::Get(InitiTraitsArray, i).ToLocalChecked()).FromJust());
  }

 
  // launch worker
  BaseCorrelationLossModelWorker* worker = new BaseCorrelationLossModelWorker(
    ObjectIDCpp
,     BaseModelCpp
,     BaseCorrelationSurfaceCpp
,     RecoveriesCpp
,     InitiTraitsCpp
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

void GMCLossModelWorker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes
  QuantLib::Size NumSimulationsLib;
  QuantLibAddin::cppToLibrary(mNumSimulations, NumSimulationsLib);

 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlGMCLossModel(
          mObjectID,
          mFactors,
          mRecoveryRates,
          mNumSimulations,
          false
      ));

    // Construct the Object
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::GaussianRandomDefaultLM(
          valueObject,
          mFactors,
          mRecoveryRates,
          NumSimulationsLib,
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

NAN_METHOD(QuantLibXL::GMCLossModel) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsArray()) {
      return Nan::ThrowError("Factors is required.");
  }
  if (info.Length() == 2 || !info[2]->IsArray()) {
      return Nan::ThrowError("RecoveryRates is required.");
  }
  if (info.Length() == 3 || !info[3]->IsNumber()) {
      return Nan::ThrowError("NumSimulations is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  std::vector< std::vector<double> >FactorsCpp;

  Local<Array> FactorsMatrix = info[1].As<Array>();
  for (unsigned int i = 0; i < FactorsMatrix->Length(); i++){
	  Local<Array> FactorsArray = FactorsMatrix->Get(i).As<Array>();
	  std::vector<double> tmp;
	  for (unsigned int j = 0; j < FactorsArray->Length(); j++){
		  tmp.push_back(Nan::To<double>(Nan::Get(FactorsArray, j).ToLocalChecked()).FromJust());
	  }
	  FactorsCpp.push_back(tmp);
  }

  // convert js argument to c++ type
  std::vector<double>RecoveryRatesCpp;

  Local<Array> RecoveryRatesArray = info[2].As<Array>();
  for (unsigned int i = 0; i < RecoveryRatesArray->Length(); i++){
    RecoveryRatesCpp.push_back(Nan::To<double>(Nan::Get(RecoveryRatesArray, i).ToLocalChecked()).FromJust());
  }

  // convert js argument to c++ type
  long NumSimulationsCpp = Nan::To<int32_t>(info[3]).FromJust();

 
  // launch worker
  GMCLossModelWorker* worker = new GMCLossModelWorker(
    ObjectIDCpp
,     FactorsCpp
,     RecoveryRatesCpp
,     NumSimulationsCpp
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

void GRandomRRMCLossModelWorker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes

  // convert input datatypes to QuantLib datatypes
  QuantLib::Size NumSimulationsLib;
  QuantLibAddin::cppToLibrary(mNumSimulations, NumSimulationsLib);

 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlGRandomRRMCLossModel(
          mObjectID,
          mFactors,
          mRecoveryRates,
          mModelA,
          mNumSimulations,
          false
      ));

    // Construct the Object
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::GaussianRandomLossLM(
          valueObject,
          mFactors,
          mRecoveryRates,
          mModelA,
          NumSimulationsLib,
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

NAN_METHOD(QuantLibXL::GRandomRRMCLossModel) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsArray()) {
      return Nan::ThrowError("Factors is required.");
  }
  if (info.Length() == 2 || !info[2]->IsArray()) {
      return Nan::ThrowError("RecoveryRates is required.");
  }
  if (info.Length() == 3 || !info[3]->IsNumber()) {
      return Nan::ThrowError("ModelA is required.");
  }
  if (info.Length() == 4 || !info[4]->IsNumber()) {
      return Nan::ThrowError("NumSimulations is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  std::vector< std::vector<double> >FactorsCpp;

  Local<Array> FactorsMatrix = info[1].As<Array>();
  for (unsigned int i = 0; i < FactorsMatrix->Length(); i++){
	  Local<Array> FactorsArray = FactorsMatrix->Get(i).As<Array>();
	  std::vector<double> tmp;
	  for (unsigned int j = 0; j < FactorsArray->Length(); j++){
		  tmp.push_back(Nan::To<double>(Nan::Get(FactorsArray, j).ToLocalChecked()).FromJust());
	  }
	  FactorsCpp.push_back(tmp);
  }

  // convert js argument to c++ type
  std::vector<double>RecoveryRatesCpp;

  Local<Array> RecoveryRatesArray = info[2].As<Array>();
  for (unsigned int i = 0; i < RecoveryRatesArray->Length(); i++){
    RecoveryRatesCpp.push_back(Nan::To<double>(Nan::Get(RecoveryRatesArray, i).ToLocalChecked()).FromJust());
  }

  // convert js argument to c++ type
  double ModelACpp = Nan::To<double>(info[3]).FromJust();

  // convert js argument to c++ type
  long NumSimulationsCpp = Nan::To<int32_t>(info[4]).FromJust();

 
  // launch worker
  GRandomRRMCLossModelWorker* worker = new GRandomRRMCLossModelWorker(
    ObjectIDCpp
,     FactorsCpp
,     RecoveryRatesCpp
,     ModelACpp
,     NumSimulationsCpp
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

void TMCLossModelWorker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes
  QuantLib::Size NumSimulationsLib;
  QuantLibAddin::cppToLibrary(mNumSimulations, NumSimulationsLib);

 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlTMCLossModel(
          mObjectID,
          mFactors,
          mRecoveryRates,
          mTtraits,
          mNumSimulations,
          false
      ));

    // Construct the Object
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::TRandomDefaultLM(
          valueObject,
          mFactors,
          mRecoveryRates,
          mTtraits,
          NumSimulationsLib,
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

NAN_METHOD(QuantLibXL::TMCLossModel) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsArray()) {
      return Nan::ThrowError("Factors is required.");
  }
  if (info.Length() == 2 || !info[2]->IsArray()) {
      return Nan::ThrowError("RecoveryRates is required.");
  }
  if (info.Length() == 3 || !info[3]->IsArray()) {
      return Nan::ThrowError("Ttraits is required.");
  }
  if (info.Length() == 4 || !info[4]->IsNumber()) {
      return Nan::ThrowError("NumSimulations is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  std::vector< std::vector<double> >FactorsCpp;

  Local<Array> FactorsMatrix = info[1].As<Array>();
  for (unsigned int i = 0; i < FactorsMatrix->Length(); i++){
	  Local<Array> FactorsArray = FactorsMatrix->Get(i).As<Array>();
	  std::vector<double> tmp;
	  for (unsigned int j = 0; j < FactorsArray->Length(); j++){
		  tmp.push_back(Nan::To<double>(Nan::Get(FactorsArray, j).ToLocalChecked()).FromJust());
	  }
	  FactorsCpp.push_back(tmp);
  }

  // convert js argument to c++ type
  std::vector<double>RecoveryRatesCpp;

  Local<Array> RecoveryRatesArray = info[2].As<Array>();
  for (unsigned int i = 0; i < RecoveryRatesArray->Length(); i++){
    RecoveryRatesCpp.push_back(Nan::To<double>(Nan::Get(RecoveryRatesArray, i).ToLocalChecked()).FromJust());
  }

  // convert js argument to c++ type
  std::vector<double>TtraitsCpp;

  Local<Array> TtraitsArray = info[3].As<Array>();
  for (unsigned int i = 0; i < TtraitsArray->Length(); i++){
    TtraitsCpp.push_back(Nan::To<double>(Nan::Get(TtraitsArray, i).ToLocalChecked()).FromJust());
  }

  // convert js argument to c++ type
  long NumSimulationsCpp = Nan::To<int32_t>(info[4]).FromJust();

 
  // launch worker
  TMCLossModelWorker* worker = new TMCLossModelWorker(
    ObjectIDCpp
,     FactorsCpp
,     RecoveryRatesCpp
,     TtraitsCpp
,     NumSimulationsCpp
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

void TRandomRRMCLossModelWorker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes

  // convert input datatypes to QuantLib datatypes
  QuantLib::Size NumSimulationsLib;
  QuantLibAddin::cppToLibrary(mNumSimulations, NumSimulationsLib);

 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlTRandomRRMCLossModel(
          mObjectID,
          mFactors,
          mRecoveryRates,
          mTtraits,
          mModelA,
          mNumSimulations,
          false
      ));

    // Construct the Object
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::TRandomLossLM(
          valueObject,
          mFactors,
          mRecoveryRates,
          mTtraits,
          mModelA,
          NumSimulationsLib,
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

NAN_METHOD(QuantLibXL::TRandomRRMCLossModel) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsArray()) {
      return Nan::ThrowError("Factors is required.");
  }
  if (info.Length() == 2 || !info[2]->IsArray()) {
      return Nan::ThrowError("RecoveryRates is required.");
  }
  if (info.Length() == 3 || !info[3]->IsArray()) {
      return Nan::ThrowError("Ttraits is required.");
  }
  if (info.Length() == 4 || !info[4]->IsNumber()) {
      return Nan::ThrowError("ModelA is required.");
  }
  if (info.Length() == 5 || !info[5]->IsNumber()) {
      return Nan::ThrowError("NumSimulations is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  std::vector< std::vector<double> >FactorsCpp;

  Local<Array> FactorsMatrix = info[1].As<Array>();
  for (unsigned int i = 0; i < FactorsMatrix->Length(); i++){
	  Local<Array> FactorsArray = FactorsMatrix->Get(i).As<Array>();
	  std::vector<double> tmp;
	  for (unsigned int j = 0; j < FactorsArray->Length(); j++){
		  tmp.push_back(Nan::To<double>(Nan::Get(FactorsArray, j).ToLocalChecked()).FromJust());
	  }
	  FactorsCpp.push_back(tmp);
  }

  // convert js argument to c++ type
  std::vector<double>RecoveryRatesCpp;

  Local<Array> RecoveryRatesArray = info[2].As<Array>();
  for (unsigned int i = 0; i < RecoveryRatesArray->Length(); i++){
    RecoveryRatesCpp.push_back(Nan::To<double>(Nan::Get(RecoveryRatesArray, i).ToLocalChecked()).FromJust());
  }

  // convert js argument to c++ type
  std::vector<double>TtraitsCpp;

  Local<Array> TtraitsArray = info[3].As<Array>();
  for (unsigned int i = 0; i < TtraitsArray->Length(); i++){
    TtraitsCpp.push_back(Nan::To<double>(Nan::Get(TtraitsArray, i).ToLocalChecked()).FromJust());
  }

  // convert js argument to c++ type
  double ModelACpp = Nan::To<double>(info[4]).FromJust();

  // convert js argument to c++ type
  long NumSimulationsCpp = Nan::To<int32_t>(info[5]).FromJust();

 
  // launch worker
  TRandomRRMCLossModelWorker* worker = new TRandomRRMCLossModelWorker(
    ObjectIDCpp
,     FactorsCpp
,     RecoveryRatesCpp
,     TtraitsCpp
,     ModelACpp
,     NumSimulationsCpp
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

void GSaddlePointLossmodelWorker::Execute(){

  try{
 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlGSaddlePointLossmodel(
          mObjectID,
          mFactors,
          mRecoveryRates,
          false
      ));

    // Construct the Object
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::SaddlePointLossModel(
          valueObject,
          mFactors,
          mRecoveryRates,
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

NAN_METHOD(QuantLibXL::GSaddlePointLossmodel) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsArray()) {
      return Nan::ThrowError("Factors is required.");
  }
  if (info.Length() == 2 || !info[2]->IsArray()) {
      return Nan::ThrowError("RecoveryRates is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  std::vector< std::vector<double> >FactorsCpp;

  Local<Array> FactorsMatrix = info[1].As<Array>();
  for (unsigned int i = 0; i < FactorsMatrix->Length(); i++){
	  Local<Array> FactorsArray = FactorsMatrix->Get(i).As<Array>();
	  std::vector<double> tmp;
	  for (unsigned int j = 0; j < FactorsArray->Length(); j++){
		  tmp.push_back(Nan::To<double>(Nan::Get(FactorsArray, j).ToLocalChecked()).FromJust());
	  }
	  FactorsCpp.push_back(tmp);
  }

  // convert js argument to c++ type
  std::vector<double>RecoveryRatesCpp;

  Local<Array> RecoveryRatesArray = info[2].As<Array>();
  for (unsigned int i = 0; i < RecoveryRatesArray->Length(); i++){
    RecoveryRatesCpp.push_back(Nan::To<double>(Nan::Get(RecoveryRatesArray, i).ToLocalChecked()).FromJust());
  }

 
  // launch worker
  GSaddlePointLossmodelWorker* worker = new GSaddlePointLossmodelWorker(
    ObjectIDCpp
,     FactorsCpp
,     RecoveryRatesCpp
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

void TSaddlePointLossmodelWorker::Execute(){

  try{
 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlTSaddlePointLossmodel(
          mObjectID,
          mFactors,
          mRecoveryRates,
          mTtraits,
          false
      ));

    // Construct the Object
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::TSaddlePointLossModel(
          valueObject,
          mFactors,
          mRecoveryRates,
          mTtraits,
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

NAN_METHOD(QuantLibXL::TSaddlePointLossmodel) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsArray()) {
      return Nan::ThrowError("Factors is required.");
  }
  if (info.Length() == 2 || !info[2]->IsArray()) {
      return Nan::ThrowError("RecoveryRates is required.");
  }
  if (info.Length() == 3 || !info[3]->IsArray()) {
      return Nan::ThrowError("Ttraits is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  std::vector< std::vector<double> >FactorsCpp;

  Local<Array> FactorsMatrix = info[1].As<Array>();
  for (unsigned int i = 0; i < FactorsMatrix->Length(); i++){
	  Local<Array> FactorsArray = FactorsMatrix->Get(i).As<Array>();
	  std::vector<double> tmp;
	  for (unsigned int j = 0; j < FactorsArray->Length(); j++){
		  tmp.push_back(Nan::To<double>(Nan::Get(FactorsArray, j).ToLocalChecked()).FromJust());
	  }
	  FactorsCpp.push_back(tmp);
  }

  // convert js argument to c++ type
  std::vector<double>RecoveryRatesCpp;

  Local<Array> RecoveryRatesArray = info[2].As<Array>();
  for (unsigned int i = 0; i < RecoveryRatesArray->Length(); i++){
    RecoveryRatesCpp.push_back(Nan::To<double>(Nan::Get(RecoveryRatesArray, i).ToLocalChecked()).FromJust());
  }

  // convert js argument to c++ type
  std::vector<double>TtraitsCpp;

  Local<Array> TtraitsArray = info[3].As<Array>();
  for (unsigned int i = 0; i < TtraitsArray->Length(); i++){
    TtraitsCpp.push_back(Nan::To<double>(Nan::Get(TtraitsArray, i).ToLocalChecked()).FromJust());
  }

 
  // launch worker
  TSaddlePointLossmodelWorker* worker = new TSaddlePointLossmodelWorker(
    ObjectIDCpp
,     FactorsCpp
,     RecoveryRatesCpp
,     TtraitsCpp
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

void GRecursiveLossmodelWorker::Execute(){

  try{
 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlGRecursiveLossmodel(
          mObjectID,
          mFactors,
          mRecoveryRates,
          false
      ));

    // Construct the Object
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::RecursiveGaussLossModel(
          valueObject,
          mFactors,
          mRecoveryRates,
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

NAN_METHOD(QuantLibXL::GRecursiveLossmodel) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsArray()) {
      return Nan::ThrowError("Factors is required.");
  }
  if (info.Length() == 2 || !info[2]->IsArray()) {
      return Nan::ThrowError("RecoveryRates is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  std::vector< std::vector<double> >FactorsCpp;

  Local<Array> FactorsMatrix = info[1].As<Array>();
  for (unsigned int i = 0; i < FactorsMatrix->Length(); i++){
	  Local<Array> FactorsArray = FactorsMatrix->Get(i).As<Array>();
	  std::vector<double> tmp;
	  for (unsigned int j = 0; j < FactorsArray->Length(); j++){
		  tmp.push_back(Nan::To<double>(Nan::Get(FactorsArray, j).ToLocalChecked()).FromJust());
	  }
	  FactorsCpp.push_back(tmp);
  }

  // convert js argument to c++ type
  std::vector<double>RecoveryRatesCpp;

  Local<Array> RecoveryRatesArray = info[2].As<Array>();
  for (unsigned int i = 0; i < RecoveryRatesArray->Length(); i++){
    RecoveryRatesCpp.push_back(Nan::To<double>(Nan::Get(RecoveryRatesArray, i).ToLocalChecked()).FromJust());
  }

 
  // launch worker
  GRecursiveLossmodelWorker* worker = new GRecursiveLossmodelWorker(
    ObjectIDCpp
,     FactorsCpp
,     RecoveryRatesCpp
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
 