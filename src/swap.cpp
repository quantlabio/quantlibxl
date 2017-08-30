/* 
  Copyright (C) 2016 -2017 Jerry Jin
*/

#include <nan.h>
#include <string.h>

#include "swap.hpp"

#include <qlo/qladdindefines.hpp>
#include <qlo/swap.hpp>
#include <qlo/termstructures.hpp>
#include <qlo/conundrumpricer.hpp>
#include <qlo/indexes/iborindex.hpp>
#include <qlo/indexes/swapindex.hpp>
#include <ql/instruments/swap.hpp>
#include <ql/indexes/iborindex.hpp>
#include <ql/indexes/swapindex.hpp>
#include <ql/termstructures/yieldtermstructure.hpp>
 #include <oh/objecthandler.hpp>
#include <oh/conversions/getobjectvector.hpp>
#include <qlo/valueobjects/vo_all.hpp>
#include <qlo/conversions/all.hpp>
#include "../loop.hpp"


void SwapWorker::Execute(){

  try{

  // convert object IDs into library objects
  std::vector< boost::shared_ptr<QuantLibAddin::Leg> > LegIDsObjPtr =
      ObjectHandler::getObjectVector<QuantLibAddin::Leg>(mLegIDs);

 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlSwap(
          mObjectID,
          mLegIDs,
          mPayer,
          false
      ));

    // Construct the Object
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::Swap(
          valueObject,
          LegIDsObjPtr,
          mPayer,
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

NAN_METHOD(QuantLibXL::Swap) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsArray()) {
      return Nan::ThrowError("LegIDs is required.");
  }
  if (info.Length() == 2 || !info[2]->IsArray()) {
      return Nan::ThrowError("Payer is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  std::vector<string>LegIDsCpp;

  Local<Array> LegIDsArray = info[1].As<Array>();
  for (unsigned int i = 0; i < LegIDsArray->Length(); i++){
    String::Utf8Value strLegIDs(Nan::Get(LegIDsArray, i).ToLocalChecked()->ToString());
    LegIDsCpp.push_back(strdup(*strLegIDs));
  }

  // convert js argument to c++ type
  std::vector<bool>PayerCpp;

  Local<Array> PayerArray = info[2].As<Array>();
  for (unsigned int i = 0; i < PayerArray->Length(); i++){
    PayerCpp.push_back(Nan::To<bool>(Nan::Get(PayerArray, i).ToLocalChecked()).FromJust());
  }

 
  // launch worker
  SwapWorker* worker = new SwapWorker(
    ObjectIDCpp
,     LegIDsCpp
,     PayerCpp
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

void MakeCmsWorker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes
  QuantLib::Period SwapTenorLib;
  QuantLibAddin::cppToLibrary(mSwapTenor, SwapTenorLib);


  // convert object IDs into library objects
  OH_GET_REFERENCE(SwapIndexLibObjPtr, mSwapIndex,
      QuantLibAddin::SwapIndex, QuantLib::SwapIndex)


  // convert object IDs into library objects
  OH_GET_REFERENCE(IborIndexLibObjPtr, mIborIndex,
      QuantLibAddin::IborIndex, QuantLib::IborIndex)


  // convert input datatypes to QuantLib datatypes
  QuantLib::Period ForwardStartLib;
  QuantLibAddin::cppToLibrary(mForwardStart, ForwardStartLib);


  // convert object IDs into library objects
  OH_GET_REFERENCE(CmsCouponPricerLibObjPtr, mCmsCouponPricer,
      QuantLibAddin::CmsCouponPricer, QuantLib::CmsCouponPricer)

 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlMakeCms(
          mObjectID,
          mSwapTenor,
          mSwapIndex,
          mIborIndex,
          mIborSpread,
          mForwardStart,
          mCmsCouponPricer,
          false
      ));

    // Construct the Object
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::Swap(
          valueObject,
          SwapTenorLib,
          SwapIndexLibObjPtr,
          IborIndexLibObjPtr,
          mIborSpread,
          ForwardStartLib,
          CmsCouponPricerLibObjPtr,
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

NAN_METHOD(QuantLibXL::MakeCms) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsString()) {
      return Nan::ThrowError("SwapTenor is required.");
  }
  if (info.Length() == 2 || !info[2]->IsString()) {
      return Nan::ThrowError("SwapIndex is required.");
  }
  if (info.Length() == 3 || !info[3]->IsString()) {
      return Nan::ThrowError("IborIndex is required.");
  }
  if (info.Length() == 4 || !info[4]->IsNumber()) {
      return Nan::ThrowError("IborSpread is required.");
  }
  if (info.Length() == 5 || !info[5]->IsString()) {
      return Nan::ThrowError("ForwardStart is required.");
  }
  if (info.Length() == 6 || !info[6]->IsString()) {
      return Nan::ThrowError("CmsCouponPricer is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  String::Utf8Value strSwapTenor(info[1]->ToString());
  string SwapTenorCpp(strdup(*strSwapTenor));

  // convert js argument to c++ type
  String::Utf8Value strSwapIndex(info[2]->ToString());
  string SwapIndexCpp(strdup(*strSwapIndex));

  // convert js argument to c++ type
  String::Utf8Value strIborIndex(info[3]->ToString());
  string IborIndexCpp(strdup(*strIborIndex));

  // convert js argument to c++ type
  double IborSpreadCpp = Nan::To<double>(info[4]).FromJust();

  // convert js argument to c++ type
  String::Utf8Value strForwardStart(info[5]->ToString());
  string ForwardStartCpp(strdup(*strForwardStart));

  // convert js argument to c++ type
  String::Utf8Value strCmsCouponPricer(info[6]->ToString());
  string CmsCouponPricerCpp(strdup(*strCmsCouponPricer));

 
  // launch worker
  MakeCmsWorker* worker = new MakeCmsWorker(
    ObjectIDCpp
,     SwapTenorCpp
,     SwapIndexCpp
,     IborIndexCpp
,     IborSpreadCpp
,     ForwardStartCpp
,     CmsCouponPricerCpp
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

void SwapLegBPSWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::Swap, QuantLib::Swap)


  // invoke the member function
  mReturnValue = ObjectIDLibObjPtr->legBPS(
        mLegNumber
       );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::SwapLegBPS) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsNumber()) {
      return Nan::ThrowError("LegNumber is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  long LegNumberCpp = Nan::To<int32_t>(info[1]).FromJust();

 
  // launch worker
  SwapLegBPSWorker* worker = new SwapLegBPSWorker(
    ObjectIDCpp
,     LegNumberCpp
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

void SwapLegNPVWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::Swap, QuantLib::Swap)


  // invoke the member function
  mReturnValue = ObjectIDLibObjPtr->legNPV(
        mLegNumber
       );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::SwapLegNPV) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsNumber()) {
      return Nan::ThrowError("LegNumber is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  long LegNumberCpp = Nan::To<int32_t>(info[1]).FromJust();

 
  // launch worker
  SwapLegNPVWorker* worker = new SwapLegNPVWorker(
    ObjectIDCpp
,     LegNumberCpp
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

void SwapStartDateWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::Swap, QuantLib::Swap)


  // invoke the member function
  QuantLib::Date returnValue = ObjectIDLibObjPtr->startDate(
      );


  mReturnValue = QuantLibAddin::libraryToScalar(returnValue);

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::SwapStartDate) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  SwapStartDateWorker* worker = new SwapStartDateWorker(
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

void SwapMaturityDateWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::Swap, QuantLib::Swap)


  // invoke the member function
  QuantLib::Date returnValue = ObjectIDLibObjPtr->maturityDate(
      );


  mReturnValue = QuantLibAddin::libraryToScalar(returnValue);

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::SwapMaturityDate) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  SwapMaturityDateWorker* worker = new SwapMaturityDateWorker(
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

void SwapLegAnalysisWorker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes
  QuantLib::Date AfterDateLib = ObjectHandler::convert2<QuantLib::Date>(
      mAfterDate, "AfterDate");

       // convert object IDs into library objects
  OH_GET_OBJECT(ObjectIDObjPtr, mObjectID, QuantLibAddin::Swap)

  std::vector< std::vector<ObjectHandler::property_t> > returnValue;


  // invoke the member function
  returnValue = ObjectIDObjPtr->legAnalysis(
        mLegNumber
        ,
         AfterDateLib
       );


  mReturnValue = ObjectHandler::matrix::convert2<string>(returnValue,"returnValue");

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::SwapLegAnalysis) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsNumber()) {
      return Nan::ThrowError("LegNumber is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  long LegNumberCpp = Nan::To<int32_t>(info[1]).FromJust();

  // convert js argument to c++ type
  ObjectHandler::property_t AfterDateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[2]).FromJust()));

 
  // launch worker
  SwapLegAnalysisWorker* worker = new SwapLegAnalysisWorker(
    ObjectIDCpp
,     LegNumberCpp
,     AfterDateCpp
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
 