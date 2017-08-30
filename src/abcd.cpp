/* 
  Copyright (C) 2016 -2017 Jerry Jin
*/

#include <nan.h>
#include <string.h>

#include "abcd.hpp"

#include <qlo/qladdindefines.hpp>
#include <qlo/abcd.hpp>
#include <qlo/optimization.hpp>
#include <ql/termstructures/volatility/abcd.hpp>
#include <ql/termstructures/volatility/abcdcalibration.hpp>
#include <qlo/loop/loop_abcd.hpp>
 #include <oh/objecthandler.hpp>
#include <oh/conversions/getobjectvector.hpp>
#include <qlo/valueobjects/vo_all.hpp>
#include <qlo/conversions/all.hpp>
#include "../loop.hpp"


void AbcdFunctionWorker::Execute(){

  try{
 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlAbcdFunction(
          mObjectID,
          mA,
          mB,
          mC,
          mD,
          false
      ));

    // Construct the Object
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::AbcdFunction(
          valueObject,
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

NAN_METHOD(QuantLibXL::AbcdFunction) {

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

 
  // launch worker
  AbcdFunctionWorker* worker = new AbcdFunctionWorker(
    ObjectIDCpp
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

void AbcdCalibrationWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_REFERENCE(EndCriteriaLibObjPtr, mEndCriteria,
      QuantLibAddin::EndCriteria, QuantLib::EndCriteria)


  // convert object IDs into library objects
  OH_GET_REFERENCE(MethodLibObjPtr, mMethod,
      QuantLibAddin::OptimizationMethod, QuantLib::OptimizationMethod)

 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlAbcdCalibration(
          mObjectID,
          mTimes,
          mBlackVols,
          mA,
          mB,
          mC,
          mD,
          mAIsFixed,
          mBIsFixed,
          mCIsFixed,
          mDIsFixed,
          mVegaWeighted,
          mEndCriteria,
          mMethod,
          false
      ));

    // Construct the Object
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::AbcdCalibration(
          valueObject,
          mTimes,
          mBlackVols,
          mA,
          mB,
          mC,
          mD,
          mAIsFixed,
          mBIsFixed,
          mCIsFixed,
          mDIsFixed,
          mVegaWeighted,
          EndCriteriaLibObjPtr,
          MethodLibObjPtr,
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

NAN_METHOD(QuantLibXL::AbcdCalibration) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsArray()) {
      return Nan::ThrowError("Times is required.");
  }
  if (info.Length() == 2 || !info[2]->IsArray()) {
      return Nan::ThrowError("BlackVols is required.");
  }
  if (info.Length() == 3 || !info[3]->IsNumber()) {
      return Nan::ThrowError("A is required.");
  }
  if (info.Length() == 4 || !info[4]->IsNumber()) {
      return Nan::ThrowError("B is required.");
  }
  if (info.Length() == 5 || !info[5]->IsNumber()) {
      return Nan::ThrowError("C is required.");
  }
  if (info.Length() == 6 || !info[6]->IsNumber()) {
      return Nan::ThrowError("D is required.");
  }
  if (info.Length() == 7 || !info[7]->IsBoolean()) {
      return Nan::ThrowError("AIsFixed is required.");
  }
  if (info.Length() == 8 || !info[8]->IsBoolean()) {
      return Nan::ThrowError("BIsFixed is required.");
  }
  if (info.Length() == 9 || !info[9]->IsBoolean()) {
      return Nan::ThrowError("CIsFixed is required.");
  }
  if (info.Length() == 10 || !info[10]->IsBoolean()) {
      return Nan::ThrowError("DIsFixed is required.");
  }
  if (info.Length() == 11 || !info[11]->IsBoolean()) {
      return Nan::ThrowError("VegaWeighted is required.");
  }
  if (info.Length() == 12 || !info[12]->IsString()) {
      return Nan::ThrowError("EndCriteria is required.");
  }
  if (info.Length() == 13 || !info[13]->IsString()) {
      return Nan::ThrowError("Method is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  std::vector<double>TimesCpp;

  Local<Array> TimesArray = info[1].As<Array>();
  for (unsigned int i = 0; i < TimesArray->Length(); i++){
    TimesCpp.push_back(Nan::To<double>(Nan::Get(TimesArray, i).ToLocalChecked()).FromJust());
  }

  // convert js argument to c++ type
  std::vector<double>BlackVolsCpp;

  Local<Array> BlackVolsArray = info[2].As<Array>();
  for (unsigned int i = 0; i < BlackVolsArray->Length(); i++){
    BlackVolsCpp.push_back(Nan::To<double>(Nan::Get(BlackVolsArray, i).ToLocalChecked()).FromJust());
  }

  // convert js argument to c++ type
  double ACpp = Nan::To<double>(info[3]).FromJust();

  // convert js argument to c++ type
  double BCpp = Nan::To<double>(info[4]).FromJust();

  // convert js argument to c++ type
  double CCpp = Nan::To<double>(info[5]).FromJust();

  // convert js argument to c++ type
  double DCpp = Nan::To<double>(info[6]).FromJust();

  // convert js argument to c++ type
  bool AIsFixedCpp = Nan::To<bool>(info[7]).FromJust();

  // convert js argument to c++ type
  bool BIsFixedCpp = Nan::To<bool>(info[8]).FromJust();

  // convert js argument to c++ type
  bool CIsFixedCpp = Nan::To<bool>(info[9]).FromJust();

  // convert js argument to c++ type
  bool DIsFixedCpp = Nan::To<bool>(info[10]).FromJust();

  // convert js argument to c++ type
  bool VegaWeightedCpp = Nan::To<bool>(info[11]).FromJust();

  // convert js argument to c++ type
  String::Utf8Value strEndCriteria(info[12]->ToString());
  string EndCriteriaCpp(strdup(*strEndCriteria));

  // convert js argument to c++ type
  String::Utf8Value strMethod(info[13]->ToString());
  string MethodCpp(strdup(*strMethod));

 
  // launch worker
  AbcdCalibrationWorker* worker = new AbcdCalibrationWorker(
    ObjectIDCpp
,     TimesCpp
,     BlackVolsCpp
,     ACpp
,     BCpp
,     CCpp
,     DCpp
,     AIsFixedCpp
,     BIsFixedCpp
,     CIsFixedCpp
,     DIsFixedCpp
,     VegaWeightedCpp
,     EndCriteriaCpp
,     MethodCpp
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

void AbcdFunctionInstantaneousValueWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::AbcdFunction, QuantLib::AbcdFunction)


  // loop on the input parameter and populate the return vector
  QuantLibAddin::qlAbcdFunctionInstantaneousValueBind bindObject =
      boost::bind((QuantLibAddin::qlAbcdFunctionInstantaneousValueSignature)
              &QuantLib::AbcdFunction::operator(),
              ObjectIDLibObjPtr
          ,_1
          );

  ObjectHandler::loop
      <QuantLibAddin::qlAbcdFunctionInstantaneousValueBind,
                      double,
                      double>
          (bindObject,
           mU,
          mReturnValue
          );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::AbcdFunctionInstantaneousValue) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsArray()) {
      return Nan::ThrowError("U is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  std::vector<double>UCpp;

  Local<Array> UArray = info[1].As<Array>();
  for (unsigned int i = 0; i < UArray->Length(); i++){
    UCpp.push_back(Nan::To<double>(Nan::Get(UArray, i).ToLocalChecked()).FromJust());
  }

 
  // launch worker
  AbcdFunctionInstantaneousValueWorker* worker = new AbcdFunctionInstantaneousValueWorker(
    ObjectIDCpp
,     UCpp
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

void AbcdFunctionInstantaneousCovarianceWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::AbcdFunction, QuantLib::AbcdFunction)


  // loop on the input parameter and populate the return vector
  QuantLibAddin::qlAbcdFunctionInstantaneousCovarianceBind bindObject =
      boost::bind((QuantLibAddin::qlAbcdFunctionInstantaneousCovarianceSignature)
              &QuantLib::AbcdFunction::instantaneousCovariance,
              ObjectIDLibObjPtr
          ,_1
          ,mT
          ,mS
          );

  ObjectHandler::loop
      <QuantLibAddin::qlAbcdFunctionInstantaneousCovarianceBind,
                      double,
                      double>
          (bindObject,
           mU,
          mReturnValue
          );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::AbcdFunctionInstantaneousCovariance) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsArray()) {
      return Nan::ThrowError("U is required.");
  }
  if (info.Length() == 2 || !info[2]->IsNumber()) {
      return Nan::ThrowError("T is required.");
  }
  if (info.Length() == 3 || !info[3]->IsNumber()) {
      return Nan::ThrowError("S is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  std::vector<double>UCpp;

  Local<Array> UArray = info[1].As<Array>();
  for (unsigned int i = 0; i < UArray->Length(); i++){
    UCpp.push_back(Nan::To<double>(Nan::Get(UArray, i).ToLocalChecked()).FromJust());
  }

  // convert js argument to c++ type
  double TCpp = Nan::To<double>(info[2]).FromJust();

  // convert js argument to c++ type
  double SCpp = Nan::To<double>(info[3]).FromJust();

 
  // launch worker
  AbcdFunctionInstantaneousCovarianceWorker* worker = new AbcdFunctionInstantaneousCovarianceWorker(
    ObjectIDCpp
,     UCpp
,     TCpp
,     SCpp
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

void AbcdFunctionInstantaneousVarianceWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::AbcdFunction, QuantLib::AbcdFunction)


  // loop on the input parameter and populate the return vector
  QuantLibAddin::qlAbcdFunctionInstantaneousVarianceBind bindObject =
      boost::bind((QuantLibAddin::qlAbcdFunctionInstantaneousVarianceSignature)
              &QuantLib::AbcdFunction::instantaneousVariance,
              ObjectIDLibObjPtr
          ,_1
          ,mT
          );

  ObjectHandler::loop
      <QuantLibAddin::qlAbcdFunctionInstantaneousVarianceBind,
                      double,
                      double>
          (bindObject,
           mU,
          mReturnValue
          );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::AbcdFunctionInstantaneousVariance) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsArray()) {
      return Nan::ThrowError("U is required.");
  }
  if (info.Length() == 2 || !info[2]->IsNumber()) {
      return Nan::ThrowError("T is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  std::vector<double>UCpp;

  Local<Array> UArray = info[1].As<Array>();
  for (unsigned int i = 0; i < UArray->Length(); i++){
    UCpp.push_back(Nan::To<double>(Nan::Get(UArray, i).ToLocalChecked()).FromJust());
  }

  // convert js argument to c++ type
  double TCpp = Nan::To<double>(info[2]).FromJust();

 
  // launch worker
  AbcdFunctionInstantaneousVarianceWorker* worker = new AbcdFunctionInstantaneousVarianceWorker(
    ObjectIDCpp
,     UCpp
,     TCpp
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

void AbcdFunctionInstantaneousVolatilityWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::AbcdFunction, QuantLib::AbcdFunction)


  // loop on the input parameter and populate the return vector
  QuantLibAddin::qlAbcdFunctionInstantaneousVolatilityBind bindObject =
      boost::bind((QuantLibAddin::qlAbcdFunctionInstantaneousVolatilitySignature)
              &QuantLib::AbcdFunction::instantaneousVolatility,
              ObjectIDLibObjPtr
          ,_1
          ,mT
          );

  ObjectHandler::loop
      <QuantLibAddin::qlAbcdFunctionInstantaneousVolatilityBind,
                      double,
                      QuantLib::Volatility>
          (bindObject,
           mU,
          mReturnValue
          );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::AbcdFunctionInstantaneousVolatility) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsArray()) {
      return Nan::ThrowError("U is required.");
  }
  if (info.Length() == 2 || !info[2]->IsNumber()) {
      return Nan::ThrowError("T is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  std::vector<double>UCpp;

  Local<Array> UArray = info[1].As<Array>();
  for (unsigned int i = 0; i < UArray->Length(); i++){
    UCpp.push_back(Nan::To<double>(Nan::Get(UArray, i).ToLocalChecked()).FromJust());
  }

  // convert js argument to c++ type
  double TCpp = Nan::To<double>(info[2]).FromJust();

 
  // launch worker
  AbcdFunctionInstantaneousVolatilityWorker* worker = new AbcdFunctionInstantaneousVolatilityWorker(
    ObjectIDCpp
,     UCpp
,     TCpp
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

void AbcdFunctionCovarianceWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::AbcdFunction, QuantLib::AbcdFunction)


  // loop on the input parameter and populate the return vector
  QuantLibAddin::qlAbcdFunctionCovarianceBind bindObject =
      boost::bind((QuantLibAddin::qlAbcdFunctionCovarianceSignature)
              &QuantLib::AbcdFunction::covariance,
              ObjectIDLibObjPtr
          ,mTMin
          ,_1
          ,mT
          ,mS
          );

  ObjectHandler::loop
      <QuantLibAddin::qlAbcdFunctionCovarianceBind,
                      double,
                      double>
          (bindObject,
           mTMax,
          mReturnValue
          );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::AbcdFunctionCovariance) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsNumber()) {
      return Nan::ThrowError("TMin is required.");
  }
  if (info.Length() == 2 || !info[2]->IsArray()) {
      return Nan::ThrowError("TMax is required.");
  }
  if (info.Length() == 3 || !info[3]->IsNumber()) {
      return Nan::ThrowError("T is required.");
  }
  if (info.Length() == 4 || !info[4]->IsNumber()) {
      return Nan::ThrowError("S is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  double TMinCpp = Nan::To<double>(info[1]).FromJust();

  // convert js argument to c++ type
  std::vector<double>TMaxCpp;

  Local<Array> TMaxArray = info[2].As<Array>();
  for (unsigned int i = 0; i < TMaxArray->Length(); i++){
    TMaxCpp.push_back(Nan::To<double>(Nan::Get(TMaxArray, i).ToLocalChecked()).FromJust());
  }

  // convert js argument to c++ type
  double TCpp = Nan::To<double>(info[3]).FromJust();

  // convert js argument to c++ type
  double SCpp = Nan::To<double>(info[4]).FromJust();

 
  // launch worker
  AbcdFunctionCovarianceWorker* worker = new AbcdFunctionCovarianceWorker(
    ObjectIDCpp
,     TMinCpp
,     TMaxCpp
,     TCpp
,     SCpp
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

void AbcdFunctionVarianceWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::AbcdFunction, QuantLib::AbcdFunction)


  // loop on the input parameter and populate the return vector
  QuantLibAddin::qlAbcdFunctionVarianceBind bindObject =
      boost::bind((QuantLibAddin::qlAbcdFunctionVarianceSignature)
              &QuantLib::AbcdFunction::variance,
              ObjectIDLibObjPtr
          ,mTMin
          ,_1
          ,mT
          );

  ObjectHandler::loop
      <QuantLibAddin::qlAbcdFunctionVarianceBind,
                      double,
                      double>
          (bindObject,
           mTMax,
          mReturnValue
          );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::AbcdFunctionVariance) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsNumber()) {
      return Nan::ThrowError("TMin is required.");
  }
  if (info.Length() == 2 || !info[2]->IsArray()) {
      return Nan::ThrowError("TMax is required.");
  }
  if (info.Length() == 3 || !info[3]->IsNumber()) {
      return Nan::ThrowError("T is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  double TMinCpp = Nan::To<double>(info[1]).FromJust();

  // convert js argument to c++ type
  std::vector<double>TMaxCpp;

  Local<Array> TMaxArray = info[2].As<Array>();
  for (unsigned int i = 0; i < TMaxArray->Length(); i++){
    TMaxCpp.push_back(Nan::To<double>(Nan::Get(TMaxArray, i).ToLocalChecked()).FromJust());
  }

  // convert js argument to c++ type
  double TCpp = Nan::To<double>(info[3]).FromJust();

 
  // launch worker
  AbcdFunctionVarianceWorker* worker = new AbcdFunctionVarianceWorker(
    ObjectIDCpp
,     TMinCpp
,     TMaxCpp
,     TCpp
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

void AbcdFunctionVolatilityWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::AbcdFunction, QuantLib::AbcdFunction)


  // loop on the input parameter and populate the return vector
  QuantLibAddin::qlAbcdFunctionVolatilityBind bindObject =
      boost::bind((QuantLibAddin::qlAbcdFunctionVolatilitySignature)
              &QuantLib::AbcdFunction::volatility,
              ObjectIDLibObjPtr
          ,mTMin
          ,_1
          ,mT
          );

  ObjectHandler::loop
      <QuantLibAddin::qlAbcdFunctionVolatilityBind,
                      double,
                      QuantLib::Volatility>
          (bindObject,
           mTMax,
          mReturnValue
          );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::AbcdFunctionVolatility) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsNumber()) {
      return Nan::ThrowError("TMin is required.");
  }
  if (info.Length() == 2 || !info[2]->IsArray()) {
      return Nan::ThrowError("TMax is required.");
  }
  if (info.Length() == 3 || !info[3]->IsNumber()) {
      return Nan::ThrowError("T is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  double TMinCpp = Nan::To<double>(info[1]).FromJust();

  // convert js argument to c++ type
  std::vector<double>TMaxCpp;

  Local<Array> TMaxArray = info[2].As<Array>();
  for (unsigned int i = 0; i < TMaxArray->Length(); i++){
    TMaxCpp.push_back(Nan::To<double>(Nan::Get(TMaxArray, i).ToLocalChecked()).FromJust());
  }

  // convert js argument to c++ type
  double TCpp = Nan::To<double>(info[3]).FromJust();

 
  // launch worker
  AbcdFunctionVolatilityWorker* worker = new AbcdFunctionVolatilityWorker(
    ObjectIDCpp
,     TMinCpp
,     TMaxCpp
,     TCpp
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

void AbcdFunctionShortTermVolatilityWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::AbcdFunction, QuantLib::AbcdFunction)


  // invoke the member function
  mReturnValue = ObjectIDLibObjPtr->shortTermVolatility(
      );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::AbcdFunctionShortTermVolatility) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  AbcdFunctionShortTermVolatilityWorker* worker = new AbcdFunctionShortTermVolatilityWorker(
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

void AbcdFunctionLongTermVolatilityWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::AbcdFunction, QuantLib::AbcdFunction)


  // invoke the member function
  mReturnValue = ObjectIDLibObjPtr->longTermVolatility(
      );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::AbcdFunctionLongTermVolatility) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  AbcdFunctionLongTermVolatilityWorker* worker = new AbcdFunctionLongTermVolatilityWorker(
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

void AbcdFunctionMaximumLocationWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::AbcdFunction, QuantLib::AbcdFunction)


  // invoke the member function
  mReturnValue = ObjectIDLibObjPtr->maximumLocation(
      );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::AbcdFunctionMaximumLocation) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  AbcdFunctionMaximumLocationWorker* worker = new AbcdFunctionMaximumLocationWorker(
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

void AbcdFunctionMaximumVolatilityWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::AbcdFunction, QuantLib::AbcdFunction)


  // invoke the member function
  mReturnValue = ObjectIDLibObjPtr->maximumVolatility(
      );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::AbcdFunctionMaximumVolatility) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  AbcdFunctionMaximumVolatilityWorker* worker = new AbcdFunctionMaximumVolatilityWorker(
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

void AbcdFunctionAWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::AbcdFunction, QuantLib::AbcdFunction)


  // invoke the member function
  mReturnValue = ObjectIDLibObjPtr->a(
      );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::AbcdFunctionA) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  AbcdFunctionAWorker* worker = new AbcdFunctionAWorker(
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

void AbcdFunctionBWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::AbcdFunction, QuantLib::AbcdFunction)


  // invoke the member function
  mReturnValue = ObjectIDLibObjPtr->b(
      );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::AbcdFunctionB) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  AbcdFunctionBWorker* worker = new AbcdFunctionBWorker(
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

void AbcdFunctionCWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::AbcdFunction, QuantLib::AbcdFunction)


  // invoke the member function
  mReturnValue = ObjectIDLibObjPtr->c(
      );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::AbcdFunctionC) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  AbcdFunctionCWorker* worker = new AbcdFunctionCWorker(
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

void AbcdFunctionDWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::AbcdFunction, QuantLib::AbcdFunction)


  // invoke the member function
  mReturnValue = ObjectIDLibObjPtr->d(
      );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::AbcdFunctionD) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  AbcdFunctionDWorker* worker = new AbcdFunctionDWorker(
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

void AbcdDFunctionWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::AbcdFunction, QuantLib::AbcdFunction)


  // invoke the member function
  mReturnValue = ObjectIDLibObjPtr->d(
      );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::AbcdDFunction) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  AbcdDFunctionWorker* worker = new AbcdDFunctionWorker(
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

void AbcdCalibrationComputeWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::AbcdCalibration, QuantLib::AbcdCalibration)


  // invoke the member function
  ObjectIDLibObjPtr->compute(
      );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::AbcdCalibrationCompute) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  AbcdCalibrationComputeWorker* worker = new AbcdCalibrationComputeWorker(
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

void AbcdCalibrationKWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::AbcdCalibration, QuantLib::AbcdCalibration)


  // loop on the input parameter and populate the return vector
  mReturnValue = ObjectIDLibObjPtr->k(
        mTimes
        ,
         mBlackVols
       );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::AbcdCalibrationK) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsArray()) {
      return Nan::ThrowError("Times is required.");
  }
  if (info.Length() == 2 || !info[2]->IsArray()) {
      return Nan::ThrowError("BlackVols is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  std::vector<double>TimesCpp;

  Local<Array> TimesArray = info[1].As<Array>();
  for (unsigned int i = 0; i < TimesArray->Length(); i++){
    TimesCpp.push_back(Nan::To<double>(Nan::Get(TimesArray, i).ToLocalChecked()).FromJust());
  }

  // convert js argument to c++ type
  std::vector<double>BlackVolsCpp;

  Local<Array> BlackVolsArray = info[2].As<Array>();
  for (unsigned int i = 0; i < BlackVolsArray->Length(); i++){
    BlackVolsCpp.push_back(Nan::To<double>(Nan::Get(BlackVolsArray, i).ToLocalChecked()).FromJust());
  }

 
  // launch worker
  AbcdCalibrationKWorker* worker = new AbcdCalibrationKWorker(
    ObjectIDCpp
,     TimesCpp
,     BlackVolsCpp
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

void AbcdCalibrationErrorWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::AbcdCalibration, QuantLib::AbcdCalibration)


  // invoke the member function
  mReturnValue = ObjectIDLibObjPtr->error(
      );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::AbcdCalibrationError) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  AbcdCalibrationErrorWorker* worker = new AbcdCalibrationErrorWorker(
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

void AbcdCalibrationMaxErrorWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::AbcdCalibration, QuantLib::AbcdCalibration)


  // invoke the member function
  mReturnValue = ObjectIDLibObjPtr->maxError(
      );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::AbcdCalibrationMaxError) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  AbcdCalibrationMaxErrorWorker* worker = new AbcdCalibrationMaxErrorWorker(
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

void AbcdCalibrationEndCriteriaWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::AbcdCalibration, QuantLib::AbcdCalibration)


  // invoke the member function
  QuantLib::EndCriteria::Type returnValue = ObjectIDLibObjPtr->endCriteria(
      );


  std::ostringstream os;
  os << returnValue;
  mReturnValue = os.str();

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::AbcdCalibrationEndCriteria) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  AbcdCalibrationEndCriteriaWorker* worker = new AbcdCalibrationEndCriteriaWorker(
    ObjectIDCpp
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

void AbcdCalibrationAWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::AbcdCalibration, QuantLib::AbcdCalibration)


  // invoke the member function
  mReturnValue = ObjectIDLibObjPtr->a(
      );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::AbcdCalibrationA) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  AbcdCalibrationAWorker* worker = new AbcdCalibrationAWorker(
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

void AbcdCalibrationBWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::AbcdCalibration, QuantLib::AbcdCalibration)


  // invoke the member function
  mReturnValue = ObjectIDLibObjPtr->b(
      );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::AbcdCalibrationB) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  AbcdCalibrationBWorker* worker = new AbcdCalibrationBWorker(
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

void AbcdCalibrationCWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::AbcdCalibration, QuantLib::AbcdCalibration)


  // invoke the member function
  mReturnValue = ObjectIDLibObjPtr->c(
      );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::AbcdCalibrationC) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  AbcdCalibrationCWorker* worker = new AbcdCalibrationCWorker(
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

void AbcdCalibrationDWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::AbcdCalibration, QuantLib::AbcdCalibration)


  // invoke the member function
  mReturnValue = ObjectIDLibObjPtr->d(
      );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::AbcdCalibrationD) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  AbcdCalibrationDWorker* worker = new AbcdCalibrationDWorker(
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
 