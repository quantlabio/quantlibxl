/* 
  Copyright (C) 2016 -2017 Jerry Jin
*/

#include <nan.h>
#include <string.h>

#include "driftcalculators.hpp"

#include <qlo/qladdindefines.hpp>
#include <qlo/driftcalculators.hpp>
#include <qlo/curvestate.hpp>
#include <ql/models/marketmodels/curvestates/cmswapcurvestate.hpp>
#include <ql/models/marketmodels/curvestates/coterminalswapcurvestate.hpp>
#include <ql/models/marketmodels/curvestates/lmmcurvestate.hpp>
 #include <oh/objecthandler.hpp>
#include <oh/conversions/getobjectvector.hpp>
#include <qlo/valueobjects/vo_all.hpp>
#include <qlo/conversions/all.hpp>
#include "../loop.hpp"


void LMMDriftCalculatorWorker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes
  QuantLib::Matrix Pseudo_square_rootLib = QuantLibAddin::vvToQlMatrix(mPseudo_square_root);


  // convert input datatypes to QuantLib datatypes
  QuantLib::Size NumeraireLib;
  QuantLibAddin::cppToLibrary(mNumeraire, NumeraireLib);


  // convert input datatypes to QuantLib datatypes
  QuantLib::Size AliveLib;
  QuantLibAddin::cppToLibrary(mAlive, AliveLib);

 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlLMMDriftCalculator(
          mObjectID,
          mPseudo_square_root,
          mDisplacements,
          mTaus,
          mNumeraire,
          mAlive,
          false
      ));

    // Construct the Object
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::LMMDriftCalculator(
          valueObject,
          Pseudo_square_rootLib,
          mDisplacements,
          mTaus,
          NumeraireLib,
          AliveLib,
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

NAN_METHOD(QuantLibXL::LMMDriftCalculator) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsArray()) {
      return Nan::ThrowError("Pseudo_square_root is required.");
  }
  if (info.Length() == 2 || !info[2]->IsArray()) {
      return Nan::ThrowError("Displacements is required.");
  }
  if (info.Length() == 3 || !info[3]->IsArray()) {
      return Nan::ThrowError("Taus is required.");
  }
  if (info.Length() == 4 || !info[4]->IsNumber()) {
      return Nan::ThrowError("Numeraire is required.");
  }
  if (info.Length() == 5 || !info[5]->IsNumber()) {
      return Nan::ThrowError("Alive is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  std::vector< std::vector<double> >Pseudo_square_rootCpp;

  Local<Array> Pseudo_square_rootMatrix = info[1].As<Array>();
  for (unsigned int i = 0; i < Pseudo_square_rootMatrix->Length(); i++){
	  Local<Array> Pseudo_square_rootArray = Pseudo_square_rootMatrix->Get(i).As<Array>();
	  std::vector<double> tmp;
	  for (unsigned int j = 0; j < Pseudo_square_rootArray->Length(); j++){
		  tmp.push_back(Nan::To<double>(Nan::Get(Pseudo_square_rootArray, j).ToLocalChecked()).FromJust());
	  }
	  Pseudo_square_rootCpp.push_back(tmp);
  }

  // convert js argument to c++ type
  std::vector<double>DisplacementsCpp;

  Local<Array> DisplacementsArray = info[2].As<Array>();
  for (unsigned int i = 0; i < DisplacementsArray->Length(); i++){
    DisplacementsCpp.push_back(Nan::To<double>(Nan::Get(DisplacementsArray, i).ToLocalChecked()).FromJust());
  }

  // convert js argument to c++ type
  std::vector<double>TausCpp;

  Local<Array> TausArray = info[3].As<Array>();
  for (unsigned int i = 0; i < TausArray->Length(); i++){
    TausCpp.push_back(Nan::To<double>(Nan::Get(TausArray, i).ToLocalChecked()).FromJust());
  }

  // convert js argument to c++ type
  long NumeraireCpp = Nan::To<int32_t>(info[4]).FromJust();

  // convert js argument to c++ type
  long AliveCpp = Nan::To<int32_t>(info[5]).FromJust();

 
  // launch worker
  LMMDriftCalculatorWorker* worker = new LMMDriftCalculatorWorker(
    ObjectIDCpp
,     Pseudo_square_rootCpp
,     DisplacementsCpp
,     TausCpp
,     NumeraireCpp
,     AliveCpp
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

void LMMNormalDriftCalculatorWorker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes
  QuantLib::Matrix Pseudo_square_rootLib = QuantLibAddin::vvToQlMatrix(mPseudo_square_root);


  // convert input datatypes to QuantLib datatypes
  QuantLib::Size NumeraireLib;
  QuantLibAddin::cppToLibrary(mNumeraire, NumeraireLib);


  // convert input datatypes to QuantLib datatypes
  QuantLib::Size AliveLib;
  QuantLibAddin::cppToLibrary(mAlive, AliveLib);

 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlLMMNormalDriftCalculator(
          mObjectID,
          mPseudo_square_root,
          mTaus,
          mNumeraire,
          mAlive,
          false
      ));

    // Construct the Object
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::LMMNormalDriftCalculator(
          valueObject,
          Pseudo_square_rootLib,
          mTaus,
          NumeraireLib,
          AliveLib,
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

NAN_METHOD(QuantLibXL::LMMNormalDriftCalculator) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsArray()) {
      return Nan::ThrowError("Pseudo_square_root is required.");
  }
  if (info.Length() == 2 || !info[2]->IsArray()) {
      return Nan::ThrowError("Taus is required.");
  }
  if (info.Length() == 3 || !info[3]->IsNumber()) {
      return Nan::ThrowError("Numeraire is required.");
  }
  if (info.Length() == 4 || !info[4]->IsNumber()) {
      return Nan::ThrowError("Alive is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  std::vector< std::vector<double> >Pseudo_square_rootCpp;

  Local<Array> Pseudo_square_rootMatrix = info[1].As<Array>();
  for (unsigned int i = 0; i < Pseudo_square_rootMatrix->Length(); i++){
	  Local<Array> Pseudo_square_rootArray = Pseudo_square_rootMatrix->Get(i).As<Array>();
	  std::vector<double> tmp;
	  for (unsigned int j = 0; j < Pseudo_square_rootArray->Length(); j++){
		  tmp.push_back(Nan::To<double>(Nan::Get(Pseudo_square_rootArray, j).ToLocalChecked()).FromJust());
	  }
	  Pseudo_square_rootCpp.push_back(tmp);
  }

  // convert js argument to c++ type
  std::vector<double>TausCpp;

  Local<Array> TausArray = info[2].As<Array>();
  for (unsigned int i = 0; i < TausArray->Length(); i++){
    TausCpp.push_back(Nan::To<double>(Nan::Get(TausArray, i).ToLocalChecked()).FromJust());
  }

  // convert js argument to c++ type
  long NumeraireCpp = Nan::To<int32_t>(info[3]).FromJust();

  // convert js argument to c++ type
  long AliveCpp = Nan::To<int32_t>(info[4]).FromJust();

 
  // launch worker
  LMMNormalDriftCalculatorWorker* worker = new LMMNormalDriftCalculatorWorker(
    ObjectIDCpp
,     Pseudo_square_rootCpp
,     TausCpp
,     NumeraireCpp
,     AliveCpp
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

void CMSMMDriftCalculatorWorker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes
  QuantLib::Matrix Pseudo_square_rootLib = QuantLibAddin::vvToQlMatrix(mPseudo_square_root);


  // convert input datatypes to QuantLib datatypes
  QuantLib::Size NumeraireLib;
  QuantLibAddin::cppToLibrary(mNumeraire, NumeraireLib);


  // convert input datatypes to QuantLib datatypes
  QuantLib::Size AliveLib;
  QuantLibAddin::cppToLibrary(mAlive, AliveLib);


  // convert input datatypes to QuantLib datatypes
  QuantLib::Size SpanningFwdsLib;
  QuantLibAddin::cppToLibrary(mSpanningFwds, SpanningFwdsLib);

 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlCMSMMDriftCalculator(
          mObjectID,
          mPseudo_square_root,
          mDisplacements,
          mTaus,
          mNumeraire,
          mAlive,
          mSpanningFwds,
          false
      ));

    // Construct the Object
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::CMSMMDriftCalculator(
          valueObject,
          Pseudo_square_rootLib,
          mDisplacements,
          mTaus,
          NumeraireLib,
          AliveLib,
          SpanningFwdsLib,
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

NAN_METHOD(QuantLibXL::CMSMMDriftCalculator) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsArray()) {
      return Nan::ThrowError("Pseudo_square_root is required.");
  }
  if (info.Length() == 2 || !info[2]->IsArray()) {
      return Nan::ThrowError("Displacements is required.");
  }
  if (info.Length() == 3 || !info[3]->IsArray()) {
      return Nan::ThrowError("Taus is required.");
  }
  if (info.Length() == 4 || !info[4]->IsNumber()) {
      return Nan::ThrowError("Numeraire is required.");
  }
  if (info.Length() == 5 || !info[5]->IsNumber()) {
      return Nan::ThrowError("Alive is required.");
  }
  if (info.Length() == 6 || !info[6]->IsNumber()) {
      return Nan::ThrowError("SpanningFwds is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  std::vector< std::vector<double> >Pseudo_square_rootCpp;

  Local<Array> Pseudo_square_rootMatrix = info[1].As<Array>();
  for (unsigned int i = 0; i < Pseudo_square_rootMatrix->Length(); i++){
	  Local<Array> Pseudo_square_rootArray = Pseudo_square_rootMatrix->Get(i).As<Array>();
	  std::vector<double> tmp;
	  for (unsigned int j = 0; j < Pseudo_square_rootArray->Length(); j++){
		  tmp.push_back(Nan::To<double>(Nan::Get(Pseudo_square_rootArray, j).ToLocalChecked()).FromJust());
	  }
	  Pseudo_square_rootCpp.push_back(tmp);
  }

  // convert js argument to c++ type
  std::vector<double>DisplacementsCpp;

  Local<Array> DisplacementsArray = info[2].As<Array>();
  for (unsigned int i = 0; i < DisplacementsArray->Length(); i++){
    DisplacementsCpp.push_back(Nan::To<double>(Nan::Get(DisplacementsArray, i).ToLocalChecked()).FromJust());
  }

  // convert js argument to c++ type
  std::vector<double>TausCpp;

  Local<Array> TausArray = info[3].As<Array>();
  for (unsigned int i = 0; i < TausArray->Length(); i++){
    TausCpp.push_back(Nan::To<double>(Nan::Get(TausArray, i).ToLocalChecked()).FromJust());
  }

  // convert js argument to c++ type
  long NumeraireCpp = Nan::To<int32_t>(info[4]).FromJust();

  // convert js argument to c++ type
  long AliveCpp = Nan::To<int32_t>(info[5]).FromJust();

  // convert js argument to c++ type
  long SpanningFwdsCpp = Nan::To<int32_t>(info[6]).FromJust();

 
  // launch worker
  CMSMMDriftCalculatorWorker* worker = new CMSMMDriftCalculatorWorker(
    ObjectIDCpp
,     Pseudo_square_rootCpp
,     DisplacementsCpp
,     TausCpp
,     NumeraireCpp
,     AliveCpp
,     SpanningFwdsCpp
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

void SMMDriftCalculatorWorker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes
  QuantLib::Matrix Pseudo_square_rootLib = QuantLibAddin::vvToQlMatrix(mPseudo_square_root);


  // convert input datatypes to QuantLib datatypes
  QuantLib::Size NumeraireLib;
  QuantLibAddin::cppToLibrary(mNumeraire, NumeraireLib);


  // convert input datatypes to QuantLib datatypes
  QuantLib::Size AliveLib;
  QuantLibAddin::cppToLibrary(mAlive, AliveLib);

 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlSMMDriftCalculator(
          mObjectID,
          mPseudo_square_root,
          mDisplacements,
          mTaus,
          mNumeraire,
          mAlive,
          false
      ));

    // Construct the Object
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::SMMDriftCalculator(
          valueObject,
          Pseudo_square_rootLib,
          mDisplacements,
          mTaus,
          NumeraireLib,
          AliveLib,
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

NAN_METHOD(QuantLibXL::SMMDriftCalculator) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsArray()) {
      return Nan::ThrowError("Pseudo_square_root is required.");
  }
  if (info.Length() == 2 || !info[2]->IsArray()) {
      return Nan::ThrowError("Displacements is required.");
  }
  if (info.Length() == 3 || !info[3]->IsArray()) {
      return Nan::ThrowError("Taus is required.");
  }
  if (info.Length() == 4 || !info[4]->IsNumber()) {
      return Nan::ThrowError("Numeraire is required.");
  }
  if (info.Length() == 5 || !info[5]->IsNumber()) {
      return Nan::ThrowError("Alive is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  std::vector< std::vector<double> >Pseudo_square_rootCpp;

  Local<Array> Pseudo_square_rootMatrix = info[1].As<Array>();
  for (unsigned int i = 0; i < Pseudo_square_rootMatrix->Length(); i++){
	  Local<Array> Pseudo_square_rootArray = Pseudo_square_rootMatrix->Get(i).As<Array>();
	  std::vector<double> tmp;
	  for (unsigned int j = 0; j < Pseudo_square_rootArray->Length(); j++){
		  tmp.push_back(Nan::To<double>(Nan::Get(Pseudo_square_rootArray, j).ToLocalChecked()).FromJust());
	  }
	  Pseudo_square_rootCpp.push_back(tmp);
  }

  // convert js argument to c++ type
  std::vector<double>DisplacementsCpp;

  Local<Array> DisplacementsArray = info[2].As<Array>();
  for (unsigned int i = 0; i < DisplacementsArray->Length(); i++){
    DisplacementsCpp.push_back(Nan::To<double>(Nan::Get(DisplacementsArray, i).ToLocalChecked()).FromJust());
  }

  // convert js argument to c++ type
  std::vector<double>TausCpp;

  Local<Array> TausArray = info[3].As<Array>();
  for (unsigned int i = 0; i < TausArray->Length(); i++){
    TausCpp.push_back(Nan::To<double>(Nan::Get(TausArray, i).ToLocalChecked()).FromJust());
  }

  // convert js argument to c++ type
  long NumeraireCpp = Nan::To<int32_t>(info[4]).FromJust();

  // convert js argument to c++ type
  long AliveCpp = Nan::To<int32_t>(info[5]).FromJust();

 
  // launch worker
  SMMDriftCalculatorWorker* worker = new SMMDriftCalculatorWorker(
    ObjectIDCpp
,     Pseudo_square_rootCpp
,     DisplacementsCpp
,     TausCpp
,     NumeraireCpp
,     AliveCpp
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

void LMMDriftCalculatorComputePlainWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_UNDERLYING(CurveStateLibObj, mCurveState,
      QuantLibAddin::LMMCurveState, QuantLib::LMMCurveState)

       // convert object IDs into library objects
  OH_GET_OBJECT(ObjectIDObjPtr, mObjectID, QuantLibAddin::LMMDriftCalculator)


  // loop on the input parameter and populate the return vector
  mReturnValue = ObjectIDObjPtr->computePlain(
        CurveStateLibObj
       );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::LMMDriftCalculatorComputePlain) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsString()) {
      return Nan::ThrowError("CurveState is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  String::Utf8Value strCurveState(info[1]->ToString());
  string CurveStateCpp(strdup(*strCurveState));

 
  // launch worker
  LMMDriftCalculatorComputePlainWorker* worker = new LMMDriftCalculatorComputePlainWorker(
    ObjectIDCpp
,     CurveStateCpp
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

void LMMDriftCalculatorComputeReducedWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_UNDERLYING(CurveStateLibObj, mCurveState,
      QuantLibAddin::LMMCurveState, QuantLib::LMMCurveState)

       // convert object IDs into library objects
  OH_GET_OBJECT(ObjectIDObjPtr, mObjectID, QuantLibAddin::LMMDriftCalculator)


  // loop on the input parameter and populate the return vector
  mReturnValue = ObjectIDObjPtr->computeReduced(
        CurveStateLibObj
       );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::LMMDriftCalculatorComputeReduced) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsString()) {
      return Nan::ThrowError("CurveState is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  String::Utf8Value strCurveState(info[1]->ToString());
  string CurveStateCpp(strdup(*strCurveState));

 
  // launch worker
  LMMDriftCalculatorComputeReducedWorker* worker = new LMMDriftCalculatorComputeReducedWorker(
    ObjectIDCpp
,     CurveStateCpp
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

void LMMDriftCalculatorComputeWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_UNDERLYING(CurveStateLibObj, mCurveState,
      QuantLibAddin::LMMCurveState, QuantLib::LMMCurveState)

       // convert object IDs into library objects
  OH_GET_OBJECT(ObjectIDObjPtr, mObjectID, QuantLibAddin::LMMDriftCalculator)


  // loop on the input parameter and populate the return vector
  mReturnValue = ObjectIDObjPtr->compute(
        CurveStateLibObj
       );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::LMMDriftCalculatorCompute) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsString()) {
      return Nan::ThrowError("CurveState is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  String::Utf8Value strCurveState(info[1]->ToString());
  string CurveStateCpp(strdup(*strCurveState));

 
  // launch worker
  LMMDriftCalculatorComputeWorker* worker = new LMMDriftCalculatorComputeWorker(
    ObjectIDCpp
,     CurveStateCpp
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

void LMMNormalDriftCalculatorComputePlainWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_UNDERLYING(CurveStateLibObj, mCurveState,
      QuantLibAddin::LMMCurveState, QuantLib::LMMCurveState)

       // convert object IDs into library objects
  OH_GET_OBJECT(ObjectIDObjPtr, mObjectID, QuantLibAddin::LMMNormalDriftCalculator)


  // loop on the input parameter and populate the return vector
  mReturnValue = ObjectIDObjPtr->computePlain(
        CurveStateLibObj
       );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::LMMNormalDriftCalculatorComputePlain) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsString()) {
      return Nan::ThrowError("CurveState is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  String::Utf8Value strCurveState(info[1]->ToString());
  string CurveStateCpp(strdup(*strCurveState));

 
  // launch worker
  LMMNormalDriftCalculatorComputePlainWorker* worker = new LMMNormalDriftCalculatorComputePlainWorker(
    ObjectIDCpp
,     CurveStateCpp
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

void LMMNormalDriftCalculatorComputeReducedWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_UNDERLYING(CurveStateLibObj, mCurveState,
      QuantLibAddin::LMMCurveState, QuantLib::LMMCurveState)

       // convert object IDs into library objects
  OH_GET_OBJECT(ObjectIDObjPtr, mObjectID, QuantLibAddin::LMMNormalDriftCalculator)


  // loop on the input parameter and populate the return vector
  mReturnValue = ObjectIDObjPtr->computeReduced(
        CurveStateLibObj
       );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::LMMNormalDriftCalculatorComputeReduced) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsString()) {
      return Nan::ThrowError("CurveState is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  String::Utf8Value strCurveState(info[1]->ToString());
  string CurveStateCpp(strdup(*strCurveState));

 
  // launch worker
  LMMNormalDriftCalculatorComputeReducedWorker* worker = new LMMNormalDriftCalculatorComputeReducedWorker(
    ObjectIDCpp
,     CurveStateCpp
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

void LMMNormalDriftCalculatorComputeWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_UNDERLYING(CurveStateLibObj, mCurveState,
      QuantLibAddin::LMMCurveState, QuantLib::LMMCurveState)

       // convert object IDs into library objects
  OH_GET_OBJECT(ObjectIDObjPtr, mObjectID, QuantLibAddin::LMMNormalDriftCalculator)


  // loop on the input parameter and populate the return vector
  mReturnValue = ObjectIDObjPtr->compute(
        CurveStateLibObj
       );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::LMMNormalDriftCalculatorCompute) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsString()) {
      return Nan::ThrowError("CurveState is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  String::Utf8Value strCurveState(info[1]->ToString());
  string CurveStateCpp(strdup(*strCurveState));

 
  // launch worker
  LMMNormalDriftCalculatorComputeWorker* worker = new LMMNormalDriftCalculatorComputeWorker(
    ObjectIDCpp
,     CurveStateCpp
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

void CMSMMDriftCalculatorComputeWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_UNDERLYING(CurveStateLibObj, mCurveState,
      QuantLibAddin::CMSwapCurveState, QuantLib::CMSwapCurveState)

       // convert object IDs into library objects
  OH_GET_OBJECT(ObjectIDObjPtr, mObjectID, QuantLibAddin::CMSMMDriftCalculator)


  // loop on the input parameter and populate the return vector
  mReturnValue = ObjectIDObjPtr->compute(
        CurveStateLibObj
       );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::CMSMMDriftCalculatorCompute) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsString()) {
      return Nan::ThrowError("CurveState is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  String::Utf8Value strCurveState(info[1]->ToString());
  string CurveStateCpp(strdup(*strCurveState));

 
  // launch worker
  CMSMMDriftCalculatorComputeWorker* worker = new CMSMMDriftCalculatorComputeWorker(
    ObjectIDCpp
,     CurveStateCpp
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

void SMMDriftCalculatorComputeWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_UNDERLYING(CurveStateLibObj, mCurveState,
      QuantLibAddin::CoterminalSwapCurveState, QuantLib::CoterminalSwapCurveState)

       // convert object IDs into library objects
  OH_GET_OBJECT(ObjectIDObjPtr, mObjectID, QuantLibAddin::SMMDriftCalculator)


  // loop on the input parameter and populate the return vector
  mReturnValue = ObjectIDObjPtr->compute(
        CurveStateLibObj
       );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::SMMDriftCalculatorCompute) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsString()) {
      return Nan::ThrowError("CurveState is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  String::Utf8Value strCurveState(info[1]->ToString());
  string CurveStateCpp(strdup(*strCurveState));

 
  // launch worker
  SMMDriftCalculatorComputeWorker* worker = new SMMDriftCalculatorComputeWorker(
    ObjectIDCpp
,     CurveStateCpp
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
 