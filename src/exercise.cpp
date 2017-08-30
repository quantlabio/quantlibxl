/* 
  Copyright (C) 2016 -2017 Jerry Jin
*/

#include <nan.h>
#include <string.h>

#include "exercise.hpp"

#include <qlo/qladdindefines.hpp>
#include <ql/exercise.hpp>
#include <qlo/exercise.hpp>
 #include <oh/objecthandler.hpp>
#include <oh/conversions/getobjectvector.hpp>
#include <qlo/valueobjects/vo_all.hpp>
#include <qlo/conversions/all.hpp>
#include "../loop.hpp"


void AmericanExerciseWorker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes
  QuantLib::Date EarliestDateLib = ObjectHandler::convert2<QuantLib::Date>(
      mEarliestDate, "EarliestDate");


  // convert input datatypes to QuantLib datatypes
  QuantLib::Date LatestDateLib = ObjectHandler::convert2<QuantLib::Date>(
      mLatestDate, "LatestDate");

 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlAmericanExercise(
          mObjectID,
          mEarliestDate,
          mLatestDate,
          mPayoffAtExpiry,
          false
      ));

    // Construct the Object
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::AmericanExercise(
          valueObject,
          EarliestDateLib,
          LatestDateLib,
          mPayoffAtExpiry,
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

NAN_METHOD(QuantLibXL::AmericanExercise) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 3 || !info[3]->IsBoolean()) {
      return Nan::ThrowError("PayoffAtExpiry is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  ObjectHandler::property_t EarliestDateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[1]).FromJust()));

  // convert js argument to c++ type
  ObjectHandler::property_t LatestDateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[2]).FromJust()));

  // convert js argument to c++ type
  bool PayoffAtExpiryCpp = Nan::To<bool>(info[3]).FromJust();

 
  // launch worker
  AmericanExerciseWorker* worker = new AmericanExerciseWorker(
    ObjectIDCpp
,     EarliestDateCpp
,     LatestDateCpp
,     PayoffAtExpiryCpp
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

void EuropeanExerciseWorker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes
  QuantLib::Date ExpiryDateLib = ObjectHandler::convert2<QuantLib::Date>(
      mExpiryDate, "ExpiryDate");

 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlEuropeanExercise(
          mObjectID,
          mExpiryDate,
          false
      ));

    // Construct the Object
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::EuropeanExercise(
          valueObject,
          ExpiryDateLib,
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

NAN_METHOD(QuantLibXL::EuropeanExercise) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  ObjectHandler::property_t ExpiryDateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[1]).FromJust()));

 
  // launch worker
  EuropeanExerciseWorker* worker = new EuropeanExerciseWorker(
    ObjectIDCpp
,     ExpiryDateCpp
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

void BermudanExerciseWorker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes
  std::vector<QuantLib::Date> DatesLib = ObjectHandler::vector::convert2<QuantLib::Date>(
      mDates, "Dates");

 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlBermudanExercise(
          mObjectID,
          mDates,
          mPayoffAtExpiry,
          false
      ));

    // Construct the Object
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::BermudanExercise(
          valueObject,
          DatesLib,
          mPayoffAtExpiry,
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

NAN_METHOD(QuantLibXL::BermudanExercise) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsArray()) {
      return Nan::ThrowError("Dates is required.");
  }
  if (info.Length() == 2 || !info[2]->IsBoolean()) {
      return Nan::ThrowError("PayoffAtExpiry is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  std::vector<ObjectHandler::property_t>DatesCpp;

  Local<Array> DatesArray = info[1].As<Array>();
  for (unsigned int i = 0; i < DatesArray->Length(); i++){
    ObjectHandler::property_t tmp =
        ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(Nan::Get(DatesArray, i).ToLocalChecked()).FromJust()));
    DatesCpp.push_back(tmp);
  }

  // convert js argument to c++ type
  bool PayoffAtExpiryCpp = Nan::To<bool>(info[2]).FromJust();

 
  // launch worker
  BermudanExerciseWorker* worker = new BermudanExerciseWorker(
    ObjectIDCpp
,     DatesCpp
,     PayoffAtExpiryCpp
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

void ExerciseDatesWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::Exercise, QuantLib::Exercise)


  // loop on the input parameter and populate the return vector
  std::vector<QuantLib::Date> returnValue = ObjectIDLibObjPtr->dates(
      );


  mReturnValue = QuantLibAddin::libraryToVector(returnValue);

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::ExerciseDates) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  ExerciseDatesWorker* worker = new ExerciseDatesWorker(
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

void ExerciseLastDateWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::Exercise, QuantLib::Exercise)


  // invoke the member function
  QuantLib::Date returnValue = ObjectIDLibObjPtr->lastDate(
      );


  mReturnValue = QuantLibAddin::libraryToScalar(returnValue);

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::ExerciseLastDate) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  ExerciseLastDateWorker* worker = new ExerciseLastDateWorker(
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
 