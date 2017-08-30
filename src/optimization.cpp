/* 
  Copyright (C) 2016 -2017 Jerry Jin
*/

#include <nan.h>
#include <string.h>

#include "optimization.hpp"

#include <qlo/qladdindefines.hpp>
#include <qlo/optimization.hpp>
#include <ql/math/optimization/spherecylinder.hpp>
#include <ql/math/optimization/endcriteria.hpp>
 #include <oh/objecthandler.hpp>
#include <oh/conversions/getobjectvector.hpp>
#include <qlo/valueobjects/vo_all.hpp>
#include <qlo/conversions/all.hpp>
#include "../loop.hpp"


void EndCriteriaWorker::Execute(){

  try{
 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlEndCriteria(
          mObjectID,
          mMaxIterations,
          mMaxStationaryStateIterations,
          mRootEpsilon,
          mFunctionEpsilon,
          mGradientNormEpsilon,
          false
      ));

    // Construct the Object
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::EndCriteria(
          valueObject,
          mMaxIterations,
          mMaxStationaryStateIterations,
          mRootEpsilon,
          mFunctionEpsilon,
          mGradientNormEpsilon,
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

NAN_METHOD(QuantLibXL::EndCriteria) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsNumber()) {
      return Nan::ThrowError("MaxIterations is required.");
  }
  if (info.Length() == 2 || !info[2]->IsNumber()) {
      return Nan::ThrowError("MaxStationaryStateIterations is required.");
  }
  if (info.Length() == 3 || !info[3]->IsNumber()) {
      return Nan::ThrowError("RootEpsilon is required.");
  }
  if (info.Length() == 4 || !info[4]->IsNumber()) {
      return Nan::ThrowError("FunctionEpsilon is required.");
  }
  if (info.Length() == 5 || !info[5]->IsNumber()) {
      return Nan::ThrowError("GradientNormEpsilon is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  long MaxIterationsCpp = Nan::To<int32_t>(info[1]).FromJust();

  // convert js argument to c++ type
  long MaxStationaryStateIterationsCpp = Nan::To<int32_t>(info[2]).FromJust();

  // convert js argument to c++ type
  double RootEpsilonCpp = Nan::To<double>(info[3]).FromJust();

  // convert js argument to c++ type
  double FunctionEpsilonCpp = Nan::To<double>(info[4]).FromJust();

  // convert js argument to c++ type
  double GradientNormEpsilonCpp = Nan::To<double>(info[5]).FromJust();

 
  // launch worker
  EndCriteriaWorker* worker = new EndCriteriaWorker(
    ObjectIDCpp
,     MaxIterationsCpp
,     MaxStationaryStateIterationsCpp
,     RootEpsilonCpp
,     FunctionEpsilonCpp
,     GradientNormEpsilonCpp
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

void NoConstraintWorker::Execute(){

  try{
 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlNoConstraint(
          mObjectID,
          false
      ));

    // Construct the Object
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::NoConstraint(
          valueObject,
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

NAN_METHOD(QuantLibXL::NoConstraint) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  NoConstraintWorker* worker = new NoConstraintWorker(
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

void SimplexWorker::Execute(){

  try{
 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlSimplex(
          mObjectID,
          mLambda,
          false
      ));

    // Construct the Object
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::Simplex(
          valueObject,
          mLambda,
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

NAN_METHOD(QuantLibXL::Simplex) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsNumber()) {
      return Nan::ThrowError("Lambda is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  double LambdaCpp = Nan::To<double>(info[1]).FromJust();

 
  // launch worker
  SimplexWorker* worker = new SimplexWorker(
    ObjectIDCpp
,     LambdaCpp
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

void LevenbergMarquardtWorker::Execute(){

  try{
 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlLevenbergMarquardt(
          mObjectID,
          mEpsfcn,
          mXtol,
          mGtol,
          false
      ));

    // Construct the Object
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::LevenbergMarquardt(
          valueObject,
          mEpsfcn,
          mXtol,
          mGtol,
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

NAN_METHOD(QuantLibXL::LevenbergMarquardt) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsNumber()) {
      return Nan::ThrowError("Epsfcn is required.");
  }
  if (info.Length() == 2 || !info[2]->IsNumber()) {
      return Nan::ThrowError("Xtol is required.");
  }
  if (info.Length() == 3 || !info[3]->IsNumber()) {
      return Nan::ThrowError("Gtol is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  double EpsfcnCpp = Nan::To<double>(info[1]).FromJust();

  // convert js argument to c++ type
  double XtolCpp = Nan::To<double>(info[2]).FromJust();

  // convert js argument to c++ type
  double GtolCpp = Nan::To<double>(info[3]).FromJust();

 
  // launch worker
  LevenbergMarquardtWorker* worker = new LevenbergMarquardtWorker(
    ObjectIDCpp
,     EpsfcnCpp
,     XtolCpp
,     GtolCpp
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

void ConjugateGradientWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_REFERENCE(LineSearchLibObjPtr, mLineSearch,
      QuantLibAddin::LineSearch, QuantLib::LineSearch)

 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlConjugateGradient(
          mObjectID,
          mLineSearch,
          false
      ));

    // Construct the Object
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::ConjugateGradient(
          valueObject,
          LineSearchLibObjPtr,
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

NAN_METHOD(QuantLibXL::ConjugateGradient) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsString()) {
      return Nan::ThrowError("LineSearch is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  String::Utf8Value strLineSearch(info[1]->ToString());
  string LineSearchCpp(strdup(*strLineSearch));

 
  // launch worker
  ConjugateGradientWorker* worker = new ConjugateGradientWorker(
    ObjectIDCpp
,     LineSearchCpp
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

void SteepestDescentWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_REFERENCE(LineSearchLibObjPtr, mLineSearch,
      QuantLibAddin::LineSearch, QuantLib::LineSearch)

 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlSteepestDescent(
          mObjectID,
          mLineSearch,
          false
      ));

    // Construct the Object
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::SteepestDescent(
          valueObject,
          LineSearchLibObjPtr,
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

NAN_METHOD(QuantLibXL::SteepestDescent) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsString()) {
      return Nan::ThrowError("LineSearch is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  String::Utf8Value strLineSearch(info[1]->ToString());
  string LineSearchCpp(strdup(*strLineSearch));

 
  // launch worker
  SteepestDescentWorker* worker = new SteepestDescentWorker(
    ObjectIDCpp
,     LineSearchCpp
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

void ArmijoLineSearchWorker::Execute(){

  try{
 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlArmijoLineSearch(
          mObjectID,
          mEpsilon,
          mAlpha,
          mBeta,
          false
      ));

    // Construct the Object
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::ArmijoLineSearch(
          valueObject,
          mEpsilon,
          mAlpha,
          mBeta,
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

NAN_METHOD(QuantLibXL::ArmijoLineSearch) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsNumber()) {
      return Nan::ThrowError("Epsilon is required.");
  }
  if (info.Length() == 2 || !info[2]->IsNumber()) {
      return Nan::ThrowError("Alpha is required.");
  }
  if (info.Length() == 3 || !info[3]->IsNumber()) {
      return Nan::ThrowError("Beta is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  double EpsilonCpp = Nan::To<double>(info[1]).FromJust();

  // convert js argument to c++ type
  double AlphaCpp = Nan::To<double>(info[2]).FromJust();

  // convert js argument to c++ type
  double BetaCpp = Nan::To<double>(info[3]).FromJust();

 
  // launch worker
  ArmijoLineSearchWorker* worker = new ArmijoLineSearchWorker(
    ObjectIDCpp
,     EpsilonCpp
,     AlphaCpp
,     BetaCpp
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

void EndCriteriaMaxIterationsWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::EndCriteria, QuantLib::EndCriteria)


  // invoke the member function
  QuantLib::Size returnValue = ObjectIDLibObjPtr->maxIterations(
      );


  mReturnValue = QuantLibAddin::libraryToScalar(returnValue);

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::EndCriteriaMaxIterations) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  EndCriteriaMaxIterationsWorker* worker = new EndCriteriaMaxIterationsWorker(
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

void EndCriteriaMaxStationaryStateIterationsWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::EndCriteria, QuantLib::EndCriteria)


  // invoke the member function
  QuantLib::Size returnValue = ObjectIDLibObjPtr->maxStationaryStateIterations(
      );


  mReturnValue = QuantLibAddin::libraryToScalar(returnValue);

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::EndCriteriaMaxStationaryStateIterations) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  EndCriteriaMaxStationaryStateIterationsWorker* worker = new EndCriteriaMaxStationaryStateIterationsWorker(
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

void EndCriteriaFunctionEpsilonWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::EndCriteria, QuantLib::EndCriteria)


  // invoke the member function
  QuantLib::Real returnValue = ObjectIDLibObjPtr->functionEpsilon(
      );


  mReturnValue = returnValue;

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::EndCriteriaFunctionEpsilon) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  EndCriteriaFunctionEpsilonWorker* worker = new EndCriteriaFunctionEpsilonWorker(
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

void EndCriteriaGradientNormEpsilonWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::EndCriteria, QuantLib::EndCriteria)


  // invoke the member function
  QuantLib::Real returnValue = ObjectIDLibObjPtr->gradientNormEpsilon(
      );


  mReturnValue = returnValue;

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::EndCriteriaGradientNormEpsilon) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  EndCriteriaGradientNormEpsilonWorker* worker = new EndCriteriaGradientNormEpsilonWorker(
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

void SphereCylinderOptimizerClosestWorker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes

  // convert input datatypes to QuantLib datatypes

  // convert input datatypes to QuantLib datatypes

  // convert input datatypes to QuantLib datatypes

  // convert input datatypes to QuantLib datatypes

  // convert input datatypes to QuantLib datatypes

  // convert input datatypes to QuantLib datatypes
  QuantLib::Natural MaxIterLib = ObjectHandler::convert2<long>(
      mMaxIter, "MaxIter", QuantLib::Null<QuantLib::Natural>());


  // convert input datatypes to QuantLib datatypes
       // invoke the utility function
  std::vector<QuantLib::Real> returnValue = QuantLib::sphereCylinderOptimizerClosest(
      mR
      ,
       mS
      ,
       mAlpha
      ,
       mZ1
      ,
       mZ2
      ,
       mZ3
      ,
       MaxIterLib
      ,
       mTol
   );


  mReturnValue = QuantLibAddin::libraryToVector(returnValue);

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::SphereCylinderOptimizerClosest) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsNumber()) {
      return Nan::ThrowError("R is required.");
  }
  if (info.Length() == 1 || !info[1]->IsNumber()) {
      return Nan::ThrowError("S is required.");
  }
  if (info.Length() == 2 || !info[2]->IsNumber()) {
      return Nan::ThrowError("Alpha is required.");
  }
  if (info.Length() == 3 || !info[3]->IsNumber()) {
      return Nan::ThrowError("Z1 is required.");
  }
  if (info.Length() == 4 || !info[4]->IsNumber()) {
      return Nan::ThrowError("Z2 is required.");
  }
  if (info.Length() == 5 || !info[5]->IsNumber()) {
      return Nan::ThrowError("Z3 is required.");
  }
  if (info.Length() == 7 || !info[7]->IsNumber()) {
      return Nan::ThrowError("Tol is required.");
  }
  // convert js argument to c++ type
  double RCpp = Nan::To<double>(info[0]).FromJust();

  // convert js argument to c++ type
  double SCpp = Nan::To<double>(info[1]).FromJust();

  // convert js argument to c++ type
  double AlphaCpp = Nan::To<double>(info[2]).FromJust();

  // convert js argument to c++ type
  double Z1Cpp = Nan::To<double>(info[3]).FromJust();

  // convert js argument to c++ type
  double Z2Cpp = Nan::To<double>(info[4]).FromJust();

  // convert js argument to c++ type
  double Z3Cpp = Nan::To<double>(info[5]).FromJust();

  // convert js argument to c++ type
  ObjectHandler::property_t MaxIterCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[6]).FromJust()));

  // convert js argument to c++ type
  double TolCpp = Nan::To<double>(info[7]).FromJust();

 
  // launch worker
  SphereCylinderOptimizerClosestWorker* worker = new SphereCylinderOptimizerClosestWorker(
    RCpp
,     SCpp
,     AlphaCpp
,     Z1Cpp
,     Z2Cpp
,     Z3Cpp
,     MaxIterCpp
,     TolCpp
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

void SecondsToStringWorker::Execute(){

  try{
       // invoke the utility function
  mReturnValue = QuantLibAddin::qlSecondsToString(
      mSeconds
     );
   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::SecondsToString) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsNumber()) {
      return Nan::ThrowError("Seconds is required.");
  }
  // convert js argument to c++ type
  double SecondsCpp = Nan::To<double>(info[0]).FromJust();

 
  // launch worker
  SecondsToStringWorker* worker = new SecondsToStringWorker(
    SecondsCpp
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
 