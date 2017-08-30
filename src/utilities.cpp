/* 
  Copyright (C) 2016 -2017 Jerry Jin
*/

#include <nan.h>
#include <string.h>

#include "utilities.hpp"

#include <qlo/qladdindefines.hpp>
#include <qlo/utilities.hpp>
#include <ql/models/marketmodels/utilities.hpp>
 #include <oh/objecthandler.hpp>
#include <oh/conversions/getobjectvector.hpp>
#include <qlo/valueobjects/vo_all.hpp>
#include <qlo/conversions/all.hpp>
#include "../loop.hpp"


void xlVersionWorker::Execute(){

  try{
       // invoke the utility function
  mReturnValue = QuantLibAddin::qlxlVersion(
      mVerbose
     );
   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::xlVersion) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsBoolean()) {
      return Nan::ThrowError("Verbose is required.");
  }
  // convert js argument to c++ type
  bool VerboseCpp = Nan::To<bool>(info[0]).FromJust();

 
  // launch worker
  xlVersionWorker* worker = new xlVersionWorker(
    VerboseCpp
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

void AddinVersionWorker::Execute(){

  try{
       // invoke the utility function
  mReturnValue = QuantLibAddin::qlAddinVersion(
    );
   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::AddinVersion) {

  // validate js arguments
 
  // launch worker
  AddinVersionWorker* worker = new AddinVersionWorker(
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

void VersionWorker::Execute(){

  try{
       // invoke the utility function
  mReturnValue = QuantLibAddin::qlVersion(
    );
   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::Version) {

  // validate js arguments
 
  // launch worker
  VersionWorker* worker = new VersionWorker(
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

void FunctionCountWorker::Execute(){

  try{
       mReturnValue =  1046;
   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::FunctionCount) {

  // validate js arguments
 
  // launch worker
  FunctionCountWorker* worker = new FunctionCountWorker(
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
 