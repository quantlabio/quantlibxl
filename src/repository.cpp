/* 
  Copyright (C) 2016 -2017 Jerry Jin
*/

#include <nan.h>
#include <string.h>

#include "repository.hpp"

#include <qlo/qladdindefines.hpp>
 #include <oh/objecthandler.hpp>
#include <oh/conversions/getobjectvector.hpp>
#include <qlo/valueobjects/vo_all.hpp>
#include <qlo/conversions/all.hpp>
#include "../loop.hpp"


void ObjectPropertyNamesWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_OBJECT(ObjectIDObjPtr, mObjectID, ObjectHandler::Object)


  // loop on the input parameter and populate the return vector
  mReturnValue = ObjectIDObjPtr->propertyNamesVector(
      );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::ObjectPropertyNames) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  ObjectPropertyNamesWorker* worker = new ObjectPropertyNamesWorker(
    ObjectIDCpp
   );

  worker->Execute();

    Local<Array> tmpArray = Nan::New<Array>(worker->mReturnValue.size());
    for (unsigned int i = 0; i < worker->mReturnValue.size(); i++) {
      Nan::Set(tmpArray,i,Nan::New<String>(worker->mReturnValue[i]).ToLocalChecked());
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

void DeleteObjectWorker::Execute(){

  try{
       // invoke the utility function
  ObjectHandler::Repository::instance().deleteObject(
      mObjectID
     );
   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::DeleteObject) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  DeleteObjectWorker* worker = new DeleteObjectWorker(
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

void DeleteObjectsWorker::Execute(){

  try{
       // invoke the utility function
  ObjectHandler::Repository::instance().deleteObject(
      mObjectID
     );
   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::DeleteObjects) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsArray()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  std::vector<string>ObjectIDCpp;

  Local<Array> ObjectIDArray = info[0].As<Array>();
  for (unsigned int i = 0; i < ObjectIDArray->Length(); i++){
    String::Utf8Value strObjectID(Nan::Get(ObjectIDArray, i).ToLocalChecked()->ToString());
    ObjectIDCpp.push_back(strdup(*strObjectID));
  }

 
  // launch worker
  DeleteObjectsWorker* worker = new DeleteObjectsWorker(
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

void DeleteAllObjectsWorker::Execute(){

  try{
       // invoke the utility function
  ObjectHandler::Repository::instance().deleteAllObjects(
      mDeletePermanent
     );
   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::DeleteAllObjects) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsBoolean()) {
      return Nan::ThrowError("DeletePermanent is required.");
  }
  // convert js argument to c++ type
  bool DeletePermanentCpp = Nan::To<bool>(info[0]).FromJust();

 
  // launch worker
  DeleteAllObjectsWorker* worker = new DeleteAllObjectsWorker(
    DeletePermanentCpp
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

void ListObjectIDsWorker::Execute(){

  try{
       // invoke the utility function
  mReturnValue = ObjectHandler::Repository::instance().listObjectIDs(
      mRegex
   );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::ListObjectIDs) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("Regex is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strRegex(info[0]->ToString());
  string RegexCpp(strdup(*strRegex));

 
  // launch worker
  ListObjectIDsWorker* worker = new ListObjectIDsWorker(
    RegexCpp
   );

  worker->Execute();

    Local<Array> tmpArray = Nan::New<Array>(worker->mReturnValue.size());
    for (unsigned int i = 0; i < worker->mReturnValue.size(); i++) {
      Nan::Set(tmpArray,i,Nan::New<String>(worker->mReturnValue[i]).ToLocalChecked());
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
 