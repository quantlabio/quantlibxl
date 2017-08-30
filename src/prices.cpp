/* 
  Copyright (C) 2016 -2017 Jerry Jin
*/

#include <nan.h>
#include <string.h>

#include "prices.hpp"

#include <qlo/qladdindefines.hpp>
#include <ql/prices.hpp>
 #include <oh/objecthandler.hpp>
#include <oh/conversions/getobjectvector.hpp>
#include <qlo/valueobjects/vo_all.hpp>
#include <qlo/conversions/all.hpp>
#include "../loop.hpp"


void MidEquivalentWorker::Execute(){

  try{
       // invoke the utility function
  mReturnValue = QuantLib::midEquivalent(
      mBid
      ,
       mAsk
      ,
       mLast
      ,
       mClose
     );
   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::MidEquivalent) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsNumber()) {
      return Nan::ThrowError("Bid is required.");
  }
  if (info.Length() == 1 || !info[1]->IsNumber()) {
      return Nan::ThrowError("Ask is required.");
  }
  if (info.Length() == 2 || !info[2]->IsNumber()) {
      return Nan::ThrowError("Last is required.");
  }
  if (info.Length() == 3 || !info[3]->IsNumber()) {
      return Nan::ThrowError("Close is required.");
  }
  // convert js argument to c++ type
  double BidCpp = Nan::To<double>(info[0]).FromJust();

  // convert js argument to c++ type
  double AskCpp = Nan::To<double>(info[1]).FromJust();

  // convert js argument to c++ type
  double LastCpp = Nan::To<double>(info[2]).FromJust();

  // convert js argument to c++ type
  double CloseCpp = Nan::To<double>(info[3]).FromJust();

 
  // launch worker
  MidEquivalentWorker* worker = new MidEquivalentWorker(
    BidCpp
,     AskCpp
,     LastCpp
,     CloseCpp
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

void MidSafeWorker::Execute(){

  try{
       // invoke the utility function
  mReturnValue = QuantLib::midSafe(
      mBid
      ,
       mAsk
     );
   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::MidSafe) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsNumber()) {
      return Nan::ThrowError("Bid is required.");
  }
  if (info.Length() == 1 || !info[1]->IsNumber()) {
      return Nan::ThrowError("Ask is required.");
  }
  // convert js argument to c++ type
  double BidCpp = Nan::To<double>(info[0]).FromJust();

  // convert js argument to c++ type
  double AskCpp = Nan::To<double>(info[1]).FromJust();

 
  // launch worker
  MidSafeWorker* worker = new MidSafeWorker(
    BidCpp
,     AskCpp
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
 