/* 
  Copyright (C) 2016 -2017 Jerry Jin
*/

#include <nan.h>
#include <string.h>

#include "settings.hpp"

#include <qlo/qladdindefines.hpp>
#include <qlo/settings.hpp>
 #include <oh/objecthandler.hpp>
#include <oh/conversions/getobjectvector.hpp>
#include <qlo/valueobjects/vo_all.hpp>
#include <qlo/conversions/all.hpp>
#include "../loop.hpp"


void SettingsEvaluationDateWorker::Execute(){

  try{
       // invoke the utility function
  QuantLib::Date returnValue = QuantLib::Settings::instance().evaluationDate(
    );

  mReturnValue = QuantLibAddin::libraryToScalar(returnValue);

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::SettingsEvaluationDate) {

  // validate js arguments
 
  // launch worker
  SettingsEvaluationDateWorker* worker = new SettingsEvaluationDateWorker(
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

void SettingsSetEvaluationDateWorker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes
  QuantLib::Date EvalDateLib = ObjectHandler::convert2<QuantLib::Date>(
      mEvalDate, "EvalDate");

       // invoke the utility function
  QuantLibAddin::qlSettingsSetEvaluationDate(
      EvalDateLib
     );
   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::SettingsSetEvaluationDate) {

  // validate js arguments
  // convert js argument to c++ type
  ObjectHandler::property_t EvalDateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[0]).FromJust()));

 
  // launch worker
  SettingsSetEvaluationDateWorker* worker = new SettingsSetEvaluationDateWorker(
    EvalDateCpp
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

void SettingsEnforceTodaysHistoricFixingsWorker::Execute(){

  try{
       // invoke the utility function
  mReturnValue = QuantLib::Settings::instance().enforcesTodaysHistoricFixings(
    );
   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::SettingsEnforceTodaysHistoricFixings) {

  // validate js arguments
 
  // launch worker
  SettingsEnforceTodaysHistoricFixingsWorker* worker = new SettingsEnforceTodaysHistoricFixingsWorker(
  );

  worker->Execute();


  Local<v8::Value> argv[2] = {
		  Nan::New<String>(worker->mError).ToLocalChecked(),
      Nan::New<Boolean>(worker->mReturnValue)
	};

  v8::Local<v8::Array> results = Nan::New<v8::Array>();
  Nan::Set(results, 0, argv[0]);
  Nan::Set(results, 1, argv[1]);
  info.GetReturnValue().Set(results);
}

void SettingsSetEnforceTodaysHistoricFixingsWorker::Execute(){

  try{
       // invoke the utility function
  QuantLibAddin::qlSettingsSetEnforceTodaysHistoricFixings(
      mBoolean
     );
   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::SettingsSetEnforceTodaysHistoricFixings) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsBoolean()) {
      return Nan::ThrowError("Boolean is required.");
  }
  // convert js argument to c++ type
  bool BooleanCpp = Nan::To<bool>(info[0]).FromJust();

 
  // launch worker
  SettingsSetEnforceTodaysHistoricFixingsWorker* worker = new SettingsSetEnforceTodaysHistoricFixingsWorker(
    BooleanCpp
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
 