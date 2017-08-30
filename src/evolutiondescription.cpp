/* 
  Copyright (C) 2016 -2017 Jerry Jin
*/

#include <nan.h>
#include <string.h>

#include "evolutiondescription.hpp"

#include <qlo/qladdindefines.hpp>
#include <qlo/evolutiondescription.hpp>
#include <qlo/products.hpp>
#include <ql/models/marketmodels/multiproduct.hpp>
#include <ql/models/marketmodels/evolutiondescription.hpp>
 #include <oh/objecthandler.hpp>
#include <oh/conversions/getobjectvector.hpp>
#include <qlo/valueobjects/vo_all.hpp>
#include <qlo/conversions/all.hpp>
#include "../loop.hpp"


void EvolutionDescriptionWorker::Execute(){

  try{
 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlEvolutionDescription(
          mObjectID,
          mRateTimes,
          mEvolutionTimes,
          false
      ));

    // Construct the Object
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::EvolutionDescription(
          valueObject,
          mRateTimes,
          mEvolutionTimes,
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

NAN_METHOD(QuantLibXL::EvolutionDescription) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsArray()) {
      return Nan::ThrowError("RateTimes is required.");
  }
  if (info.Length() == 2 || !info[2]->IsArray()) {
      return Nan::ThrowError("EvolutionTimes is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  std::vector<double>RateTimesCpp;

  Local<Array> RateTimesArray = info[1].As<Array>();
  for (unsigned int i = 0; i < RateTimesArray->Length(); i++){
    RateTimesCpp.push_back(Nan::To<double>(Nan::Get(RateTimesArray, i).ToLocalChecked()).FromJust());
  }

  // convert js argument to c++ type
  std::vector<double>EvolutionTimesCpp;

  Local<Array> EvolutionTimesArray = info[2].As<Array>();
  for (unsigned int i = 0; i < EvolutionTimesArray->Length(); i++){
    EvolutionTimesCpp.push_back(Nan::To<double>(Nan::Get(EvolutionTimesArray, i).ToLocalChecked()).FromJust());
  }

 
  // launch worker
  EvolutionDescriptionWorker* worker = new EvolutionDescriptionWorker(
    ObjectIDCpp
,     RateTimesCpp
,     EvolutionTimesCpp
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

void EvolutionDescriptionFromProductWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_UNDERLYING(ProductLibObj, mProduct,
      QuantLibAddin::MarketModelMultiProduct, QuantLib::MarketModelMultiProduct)

 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlEvolutionDescriptionFromProduct(
          mObjectID,
          mProduct,
          false
      ));

    // Construct the Object
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::EvolutionDescription(
          valueObject,
          ProductLibObj,
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

NAN_METHOD(QuantLibXL::EvolutionDescriptionFromProduct) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsString()) {
      return Nan::ThrowError("Product is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  String::Utf8Value strProduct(info[1]->ToString());
  string ProductCpp(strdup(*strProduct));

 
  // launch worker
  EvolutionDescriptionFromProductWorker* worker = new EvolutionDescriptionFromProductWorker(
    ObjectIDCpp
,     ProductCpp
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

void EvolutionDescriptionRateTimesWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::EvolutionDescription, QuantLib::EvolutionDescription)

     
  // loop on the input parameter and populate the return vector
  mReturnValue = ObjectIDLibObjPtr->rateTimes(
      );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::EvolutionDescriptionRateTimes) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  EvolutionDescriptionRateTimesWorker* worker = new EvolutionDescriptionRateTimesWorker(
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

void EvolutionDescriptionRateTausWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::EvolutionDescription, QuantLib::EvolutionDescription)

     
  // loop on the input parameter and populate the return vector
  mReturnValue = ObjectIDLibObjPtr->rateTaus(
      );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::EvolutionDescriptionRateTaus) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  EvolutionDescriptionRateTausWorker* worker = new EvolutionDescriptionRateTausWorker(
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

void EvolutionDescriptionEvolutionTimesWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::EvolutionDescription, QuantLib::EvolutionDescription)

     
  // loop on the input parameter and populate the return vector
  mReturnValue = ObjectIDLibObjPtr->evolutionTimes(
      );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::EvolutionDescriptionEvolutionTimes) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  EvolutionDescriptionEvolutionTimesWorker* worker = new EvolutionDescriptionEvolutionTimesWorker(
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

void EvolutionDescriptionFirstAliveRateWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::EvolutionDescription, QuantLib::EvolutionDescription)

     
  // loop on the input parameter and populate the return vector
  std::vector<QuantLib::Size> returnValue = ObjectIDLibObjPtr->firstAliveRate(
      );


  mReturnValue = QuantLibAddin::convertVector<QuantLib::Size, long>(returnValue);

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::EvolutionDescriptionFirstAliveRate) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  EvolutionDescriptionFirstAliveRateWorker* worker = new EvolutionDescriptionFirstAliveRateWorker(
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

void EvolutionDescriptionNumberOfRatesWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::EvolutionDescription, QuantLib::EvolutionDescription)

     
  // invoke the member function
  mReturnValue = ObjectIDLibObjPtr->numberOfRates(
      );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::EvolutionDescriptionNumberOfRates) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  EvolutionDescriptionNumberOfRatesWorker* worker = new EvolutionDescriptionNumberOfRatesWorker(
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

void EvolutionDescriptionNumberOfStepsWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::EvolutionDescription, QuantLib::EvolutionDescription)

     
  // invoke the member function
  mReturnValue = ObjectIDLibObjPtr->numberOfSteps(
      );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::EvolutionDescriptionNumberOfSteps) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  EvolutionDescriptionNumberOfStepsWorker* worker = new EvolutionDescriptionNumberOfStepsWorker(
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

void TerminalMeasureWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_UNDERLYING(EvolutionDescriptionLibObj, mEvolutionDescription,
      QuantLibAddin::EvolutionDescription, QuantLib::EvolutionDescription)

       // invoke the utility function
  std::vector<QuantLib::Size> returnValue = QuantLib::terminalMeasure(
      EvolutionDescriptionLibObj
   );


  mReturnValue = QuantLibAddin::convertVector<QuantLib::Size, long>(returnValue);

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::TerminalMeasure) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("EvolutionDescription is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strEvolutionDescription(info[0]->ToString());
  string EvolutionDescriptionCpp(strdup(*strEvolutionDescription));

 
  // launch worker
  TerminalMeasureWorker* worker = new TerminalMeasureWorker(
    EvolutionDescriptionCpp
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

void MoneyMarketMeasureWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_UNDERLYING(EvolutionDescriptionLibObj, mEvolutionDescription,
      QuantLibAddin::EvolutionDescription, QuantLib::EvolutionDescription)

       // invoke the utility function
  std::vector<QuantLib::Size> returnValue = QuantLib::moneyMarketMeasure(
      EvolutionDescriptionLibObj
   );


  mReturnValue = QuantLibAddin::convertVector<QuantLib::Size, long>(returnValue);

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::MoneyMarketMeasure) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("EvolutionDescription is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strEvolutionDescription(info[0]->ToString());
  string EvolutionDescriptionCpp(strdup(*strEvolutionDescription));

 
  // launch worker
  MoneyMarketMeasureWorker* worker = new MoneyMarketMeasureWorker(
    EvolutionDescriptionCpp
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

void MoneyMarketPlusMeasureWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_UNDERLYING(EvolutionDescriptionLibObj, mEvolutionDescription,
      QuantLibAddin::EvolutionDescription, QuantLib::EvolutionDescription)


  // convert input datatypes to QuantLib datatypes
  QuantLib::Size OffsetLib;
  QuantLibAddin::cppToLibrary(mOffset, OffsetLib);

       // invoke the utility function
  std::vector<QuantLib::Size> returnValue = QuantLib::moneyMarketPlusMeasure(
      EvolutionDescriptionLibObj
      ,
       OffsetLib
   );


  mReturnValue = QuantLibAddin::convertVector<QuantLib::Size, long>(returnValue);

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::MoneyMarketPlusMeasure) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("EvolutionDescription is required.");
  }
  if (info.Length() == 1 || !info[1]->IsNumber()) {
      return Nan::ThrowError("Offset is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strEvolutionDescription(info[0]->ToString());
  string EvolutionDescriptionCpp(strdup(*strEvolutionDescription));

  // convert js argument to c++ type
  long OffsetCpp = Nan::To<int32_t>(info[1]).FromJust();

 
  // launch worker
  MoneyMarketPlusMeasureWorker* worker = new MoneyMarketPlusMeasureWorker(
    EvolutionDescriptionCpp
,     OffsetCpp
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

void IsInTerminalMeasureWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_UNDERLYING(EvolutionDescriptionLibObj, mEvolutionDescription,
      QuantLibAddin::EvolutionDescription, QuantLib::EvolutionDescription)


  // convert input datatypes to QuantLib datatypes
  std::vector<long> NumerairesCpp;
  std::vector<QuantLib::Size> NumerairesLib =
      QuantLibAddin::convertVector<long, QuantLib::Size>(NumerairesCpp);

       // invoke the utility function
  mReturnValue = QuantLib::isInTerminalMeasure(
      EvolutionDescriptionLibObj
      ,
       NumerairesLib
     );
   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::IsInTerminalMeasure) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("EvolutionDescription is required.");
  }
  if (info.Length() == 1 || !info[1]->IsArray()) {
      return Nan::ThrowError("Numeraires is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strEvolutionDescription(info[0]->ToString());
  string EvolutionDescriptionCpp(strdup(*strEvolutionDescription));

  // convert js argument to c++ type
  std::vector<long>NumerairesCpp;

  Local<Array> NumerairesArray = info[1].As<Array>();
  for (unsigned int i = 0; i < NumerairesArray->Length(); i++){
    NumerairesCpp.push_back(Nan::To<int32_t>(Nan::Get(NumerairesArray, i).ToLocalChecked()).FromJust());
  }

 
  // launch worker
  IsInTerminalMeasureWorker* worker = new IsInTerminalMeasureWorker(
    EvolutionDescriptionCpp
,     NumerairesCpp
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

void IsInMoneyMarketMeasureWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_UNDERLYING(EvolutionDescriptionLibObj, mEvolutionDescription,
      QuantLibAddin::EvolutionDescription, QuantLib::EvolutionDescription)


  // convert input datatypes to QuantLib datatypes
  std::vector<long> NumerairesCpp;
  std::vector<QuantLib::Size> NumerairesLib =
      QuantLibAddin::convertVector<long, QuantLib::Size>(NumerairesCpp);

       // invoke the utility function
  mReturnValue = QuantLib::isInMoneyMarketMeasure(
      EvolutionDescriptionLibObj
      ,
       NumerairesLib
     );
   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::IsInMoneyMarketMeasure) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("EvolutionDescription is required.");
  }
  if (info.Length() == 1 || !info[1]->IsArray()) {
      return Nan::ThrowError("Numeraires is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strEvolutionDescription(info[0]->ToString());
  string EvolutionDescriptionCpp(strdup(*strEvolutionDescription));

  // convert js argument to c++ type
  std::vector<long>NumerairesCpp;

  Local<Array> NumerairesArray = info[1].As<Array>();
  for (unsigned int i = 0; i < NumerairesArray->Length(); i++){
    NumerairesCpp.push_back(Nan::To<int32_t>(Nan::Get(NumerairesArray, i).ToLocalChecked()).FromJust());
  }

 
  // launch worker
  IsInMoneyMarketMeasureWorker* worker = new IsInMoneyMarketMeasureWorker(
    EvolutionDescriptionCpp
,     NumerairesCpp
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

void IsInMoneyMarketPlusMeasureWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_UNDERLYING(EvolutionDescriptionLibObj, mEvolutionDescription,
      QuantLibAddin::EvolutionDescription, QuantLib::EvolutionDescription)


  // convert input datatypes to QuantLib datatypes
  std::vector<long> NumerairesCpp;
  std::vector<QuantLib::Size> NumerairesLib =
      QuantLibAddin::convertVector<long, QuantLib::Size>(NumerairesCpp);

       // invoke the utility function
  mReturnValue = QuantLib::isInMoneyMarketPlusMeasure(
      EvolutionDescriptionLibObj
      ,
       NumerairesLib
      ,
       mOffset
     );
   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::IsInMoneyMarketPlusMeasure) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("EvolutionDescription is required.");
  }
  if (info.Length() == 1 || !info[1]->IsArray()) {
      return Nan::ThrowError("Numeraires is required.");
  }
  if (info.Length() == 2 || !info[2]->IsNumber()) {
      return Nan::ThrowError("Offset is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strEvolutionDescription(info[0]->ToString());
  string EvolutionDescriptionCpp(strdup(*strEvolutionDescription));

  // convert js argument to c++ type
  std::vector<long>NumerairesCpp;

  Local<Array> NumerairesArray = info[1].As<Array>();
  for (unsigned int i = 0; i < NumerairesArray->Length(); i++){
    NumerairesCpp.push_back(Nan::To<int32_t>(Nan::Get(NumerairesArray, i).ToLocalChecked()).FromJust());
  }

  // convert js argument to c++ type
  long OffsetCpp = Nan::To<int32_t>(info[2]).FromJust();

 
  // launch worker
  IsInMoneyMarketPlusMeasureWorker* worker = new IsInMoneyMarketPlusMeasureWorker(
    EvolutionDescriptionCpp
,     NumerairesCpp
,     OffsetCpp
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
 