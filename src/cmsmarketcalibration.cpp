/* 
  Copyright (C) 2016 -2017 Jerry Jin
*/

#include <nan.h>
#include <string.h>

#include "cmsmarketcalibration.hpp"

#include <qlo/qladdindefines.hpp>
#include <qlo/cmsmarketcalibration.hpp>
#include <qlo/cmsmarket.hpp>
#include <qlo/termstructures.hpp>
#include <qlo/optimization.hpp>
#include <ql/termstructures/volatility/swaption/swaptionvolcube1.hpp>
 #include <oh/objecthandler.hpp>
#include <oh/conversions/getobjectvector.hpp>
#include <qlo/valueobjects/vo_all.hpp>
#include <qlo/conversions/all.hpp>
#include "../loop.hpp"


void CmsMarketCalibrationWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_OBJECT(VolCubeCoerce, mVolCube, ObjectHandler::Object)
  QuantLib::Handle<QuantLib::SwaptionVolatilityStructure> VolCubeLibObj =
      QuantLibAddin::CoerceHandle<
          QuantLibAddin::SwaptionVolatilityStructure,
          QuantLib::SwaptionVolatilityStructure>()(
              VolCubeCoerce);


  // convert object IDs into library objects
  OH_GET_REFERENCE(CmsMarketLibObjPtr, mCmsMarket,
      QuantLibAddin::CmsMarket, QuantLib::CmsMarket)


  // convert input datatypes to QuantLib datatypes
  QuantLib::Matrix WeightsLib = QuantLibAddin::vvToQlMatrix(mWeights);


  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::CmsMarketCalibration::CalibrationType CalibrationTypeEnum =
      ObjectHandler::Create<QuantLib::CmsMarketCalibration::CalibrationType>()(mCalibrationType);

 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlCmsMarketCalibration(
          mObjectID,
          mVolCube,
          mCmsMarket,
          mWeights,
          mCalibrationType,
          false
      ));

    // Construct the Object
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::CmsMarketCalibration(
          valueObject,
          VolCubeLibObj,
          CmsMarketLibObjPtr,
          WeightsLib,
          CalibrationTypeEnum,
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

NAN_METHOD(QuantLibXL::CmsMarketCalibration) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 2 || !info[2]->IsString()) {
      return Nan::ThrowError("CmsMarket is required.");
  }
  if (info.Length() == 3 || !info[3]->IsArray()) {
      return Nan::ThrowError("Weights is required.");
  }
  if (info.Length() == 4 || !info[4]->IsString()) {
      return Nan::ThrowError("CalibrationType is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  ObjectHandler::property_t VolCubeCpp =
      ObjectHandler::property_t(static_cast<double>(Nan::To<double>(info[1]).FromJust()));

  // convert js argument to c++ type
  String::Utf8Value strCmsMarket(info[2]->ToString());
  string CmsMarketCpp(strdup(*strCmsMarket));

  // convert js argument to c++ type
  std::vector< std::vector<double> >WeightsCpp;

  Local<Array> WeightsMatrix = info[3].As<Array>();
  for (unsigned int i = 0; i < WeightsMatrix->Length(); i++){
	  Local<Array> WeightsArray = WeightsMatrix->Get(i).As<Array>();
	  std::vector<double> tmp;
	  for (unsigned int j = 0; j < WeightsArray->Length(); j++){
		  tmp.push_back(Nan::To<double>(Nan::Get(WeightsArray, j).ToLocalChecked()).FromJust());
	  }
	  WeightsCpp.push_back(tmp);
  }

  // convert js argument to c++ type
  String::Utf8Value strCalibrationType(info[4]->ToString());
  string CalibrationTypeCpp(strdup(*strCalibrationType));

 
  // launch worker
  CmsMarketCalibrationWorker* worker = new CmsMarketCalibrationWorker(
    ObjectIDCpp
,     VolCubeCpp
,     CmsMarketCpp
,     WeightsCpp
,     CalibrationTypeCpp
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

void CmsMarketCalibrationComputeWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_REFERENCE(EndCriteriaLibObjPtr, mEndCriteria,
      QuantLibAddin::EndCriteria, QuantLib::EndCriteria)


  // convert object IDs into library objects
  OH_GET_REFERENCE(OptimizationMethodLibObjPtr, mOptimizationMethod,
      QuantLibAddin::OptimizationMethod, QuantLib::OptimizationMethod)


  // convert input datatypes to QuantLib datatypes
  QuantLib::Array GuessLib;

       // convert object IDs into library objects
  OH_GET_OBJECT(ObjectIDObjPtr, mObjectID, QuantLibAddin::CmsMarketCalibration)


  // loop on the input parameter and populate the return vector
  QuantLib::Array returnValue = ObjectIDObjPtr->compute(
        EndCriteriaLibObjPtr
        ,
         OptimizationMethodLibObjPtr
        ,
         GuessLib
        ,
         mIsMeanRevFixed
       );


  for(unsigned int i = 0; i < returnValue.size(); i++){
    mReturnValue.push_back(returnValue[i]);
  }

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::CmsMarketCalibrationCompute) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsString()) {
      return Nan::ThrowError("EndCriteria is required.");
  }
  if (info.Length() == 2 || !info[2]->IsString()) {
      return Nan::ThrowError("OptimizationMethod is required.");
  }
  if (info.Length() == 3 || !info[3]->IsArray()) {
      return Nan::ThrowError("Guess is required.");
  }
  if (info.Length() == 4 || !info[4]->IsBoolean()) {
      return Nan::ThrowError("IsMeanRevFixed is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  String::Utf8Value strEndCriteria(info[1]->ToString());
  string EndCriteriaCpp(strdup(*strEndCriteria));

  // convert js argument to c++ type
  String::Utf8Value strOptimizationMethod(info[2]->ToString());
  string OptimizationMethodCpp(strdup(*strOptimizationMethod));

  // convert js argument to c++ type
  std::vector<double>GuessCpp;

  Local<Array> GuessArray = info[3].As<Array>();
  for (unsigned int i = 0; i < GuessArray->Length(); i++){
    GuessCpp.push_back(Nan::To<double>(Nan::Get(GuessArray, i).ToLocalChecked()).FromJust());
  }

  // convert js argument to c++ type
  bool IsMeanRevFixedCpp = Nan::To<bool>(info[4]).FromJust();

 
  // launch worker
  CmsMarketCalibrationComputeWorker* worker = new CmsMarketCalibrationComputeWorker(
    ObjectIDCpp
,     EndCriteriaCpp
,     OptimizationMethodCpp
,     GuessCpp
,     IsMeanRevFixedCpp
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

void CmsMarketCalibrationErrorWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::CmsMarketCalibration, QuantLib::CmsMarketCalibration)


  // invoke the member function
  mReturnValue = ObjectIDLibObjPtr->error(
      );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::CmsMarketCalibrationError) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  CmsMarketCalibrationErrorWorker* worker = new CmsMarketCalibrationErrorWorker(
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

void CmsMarketCalibrationEndCriteriaWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::CmsMarketCalibration, QuantLib::CmsMarketCalibration)


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

NAN_METHOD(QuantLibXL::CmsMarketCalibrationEndCriteria) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  CmsMarketCalibrationEndCriteriaWorker* worker = new CmsMarketCalibrationEndCriteriaWorker(
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

void CmsMarketCalibrationElapsedWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_OBJECT(ObjectIDObjPtr, mObjectID, QuantLibAddin::CmsMarketCalibration)


  // invoke the member function
  mReturnValue = ObjectIDObjPtr->elapsed(
      );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::CmsMarketCalibrationElapsed) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  CmsMarketCalibrationElapsedWorker* worker = new CmsMarketCalibrationElapsedWorker(
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

void CmsMarketCalibrationSparseSabrParametersWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_OBJECT(ObjectIDObjPtr, mObjectID, QuantLibAddin::CmsMarketCalibration)

  std::vector< std::vector<ObjectHandler::property_t> > returnValue;


  // invoke the member function
  returnValue = ObjectIDObjPtr->getSparseSabrParameters(
      );


  mReturnValue = ObjectHandler::matrix::convert2<string>(returnValue,"returnValue");

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::CmsMarketCalibrationSparseSabrParameters) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  CmsMarketCalibrationSparseSabrParametersWorker* worker = new CmsMarketCalibrationSparseSabrParametersWorker(
    ObjectIDCpp
   );

  worker->Execute();

    Local<Array> tmpMatrix = Nan::New<Array>(worker->mReturnValue.size());
    for (unsigned int i = 0; i < worker->mReturnValue.size(); i++) {
      Local<Array> tmpArray = Nan::New<Array>(worker->mReturnValue[i].size());
      for (unsigned int j = 0; j < worker->mReturnValue[i].size(); j++) {
        Nan::Set(tmpArray,j,Nan::New<String>(worker->mReturnValue[i][j]).ToLocalChecked());
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

void CmsMarketCalibrationDenseSabrParametersWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_OBJECT(ObjectIDObjPtr, mObjectID, QuantLibAddin::CmsMarketCalibration)

  std::vector< std::vector<ObjectHandler::property_t> > returnValue;


  // invoke the member function
  returnValue = ObjectIDObjPtr->getDenseSabrParameters(
      );


  mReturnValue = ObjectHandler::matrix::convert2<string>(returnValue,"returnValue");

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::CmsMarketCalibrationDenseSabrParameters) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  CmsMarketCalibrationDenseSabrParametersWorker* worker = new CmsMarketCalibrationDenseSabrParametersWorker(
    ObjectIDCpp
   );

  worker->Execute();

    Local<Array> tmpMatrix = Nan::New<Array>(worker->mReturnValue.size());
    for (unsigned int i = 0; i < worker->mReturnValue.size(); i++) {
      Local<Array> tmpArray = Nan::New<Array>(worker->mReturnValue[i].size());
      for (unsigned int j = 0; j < worker->mReturnValue[i].size(); j++) {
        Nan::Set(tmpArray,j,Nan::New<String>(worker->mReturnValue[i][j]).ToLocalChecked());
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

void SimultaneousCalibrationBrowseCmsMarketWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_OBJECT(ObjectIDObjPtr, mObjectID, QuantLibAddin::CmsMarketCalibration)

  std::vector< std::vector<ObjectHandler::property_t> > returnValue;


  // invoke the member function
  returnValue = ObjectIDObjPtr->getCmsMarket(
      );


  mReturnValue = ObjectHandler::matrix::convert2<string>(returnValue,"returnValue");

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::SimultaneousCalibrationBrowseCmsMarket) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  SimultaneousCalibrationBrowseCmsMarketWorker* worker = new SimultaneousCalibrationBrowseCmsMarketWorker(
    ObjectIDCpp
   );

  worker->Execute();

    Local<Array> tmpMatrix = Nan::New<Array>(worker->mReturnValue.size());
    for (unsigned int i = 0; i < worker->mReturnValue.size(); i++) {
      Local<Array> tmpArray = Nan::New<Array>(worker->mReturnValue[i].size());
      for (unsigned int j = 0; j < worker->mReturnValue[i].size(); j++) {
        Nan::Set(tmpArray,j,Nan::New<String>(worker->mReturnValue[i][j]).ToLocalChecked());
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
 