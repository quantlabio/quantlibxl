/* 
  Copyright (C) 2016 -2017 Jerry Jin
*/

#include <nan.h>
#include <string.h>

#include "statistics.hpp"

#include <qlo/qladdindefines.hpp>
#include <qlo/statistics.hpp>
#include <ql/math/statistics/statistics.hpp>
#include <ql/math/statistics/incrementalstatistics.hpp>
 #include <oh/objecthandler.hpp>
#include <oh/conversions/getobjectvector.hpp>
#include <qlo/valueobjects/vo_all.hpp>
#include <qlo/conversions/all.hpp>
#include "../loop.hpp"


void StatisticsWorker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes
  std::vector<QuantLib::Real> ValuesLib =
      QuantLibAddin::convertVector<double, QuantLib::Real>(mValues);


  // convert input datatypes to QuantLib datatypes
  std::vector<QuantLib::Real> WeightsLib =
      QuantLibAddin::convertVector<double, QuantLib::Real>(mWeights);

 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlStatistics(
          mObjectID,
          mValues,
          mWeights,
          false
      ));

    // Construct the Object
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::Statistics(
          valueObject,
          mValues,
          mWeights,
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

NAN_METHOD(QuantLibXL::Statistics) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsArray()) {
      return Nan::ThrowError("Values is required.");
  }
  if (info.Length() == 2 || !info[2]->IsArray()) {
      return Nan::ThrowError("Weights is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  std::vector<double>ValuesCpp;

  Local<Array> ValuesArray = info[1].As<Array>();
  for (unsigned int i = 0; i < ValuesArray->Length(); i++){
    ValuesCpp.push_back(Nan::To<double>(Nan::Get(ValuesArray, i).ToLocalChecked()).FromJust());
  }

  // convert js argument to c++ type
  std::vector<double>WeightsCpp;

  Local<Array> WeightsArray = info[2].As<Array>();
  for (unsigned int i = 0; i < WeightsArray->Length(); i++){
    WeightsCpp.push_back(Nan::To<double>(Nan::Get(WeightsArray, i).ToLocalChecked()).FromJust());
  }

 
  // launch worker
  StatisticsWorker* worker = new StatisticsWorker(
    ObjectIDCpp
,     ValuesCpp
,     WeightsCpp
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

void IncrementalStatisticsWorker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes
  std::vector<QuantLib::Real> ValuesLib =
      QuantLibAddin::convertVector<double, QuantLib::Real>(mValues);


  // convert input datatypes to QuantLib datatypes
  std::vector<QuantLib::Real> WeightsLib =
      QuantLibAddin::convertVector<double, QuantLib::Real>(mWeights);

 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlIncrementalStatistics(
          mObjectID,
          mValues,
          mWeights,
          false
      ));

    // Construct the Object
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::IncrementalStatistics(
          valueObject,
          mValues,
          mWeights,
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

NAN_METHOD(QuantLibXL::IncrementalStatistics) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsArray()) {
      return Nan::ThrowError("Values is required.");
  }
  if (info.Length() == 2 || !info[2]->IsArray()) {
      return Nan::ThrowError("Weights is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  std::vector<double>ValuesCpp;

  Local<Array> ValuesArray = info[1].As<Array>();
  for (unsigned int i = 0; i < ValuesArray->Length(); i++){
    ValuesCpp.push_back(Nan::To<double>(Nan::Get(ValuesArray, i).ToLocalChecked()).FromJust());
  }

  // convert js argument to c++ type
  std::vector<double>WeightsCpp;

  Local<Array> WeightsArray = info[2].As<Array>();
  for (unsigned int i = 0; i < WeightsArray->Length(); i++){
    WeightsCpp.push_back(Nan::To<double>(Nan::Get(WeightsArray, i).ToLocalChecked()).FromJust());
  }

 
  // launch worker
  IncrementalStatisticsWorker* worker = new IncrementalStatisticsWorker(
    ObjectIDCpp
,     ValuesCpp
,     WeightsCpp
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

void StatisticsSamplesWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::Statistics, QuantLib::Statistics)


  // invoke the member function
  QuantLib::Size returnValue = ObjectIDLibObjPtr->samples(
      );


  mReturnValue = QuantLibAddin::libraryToScalar(returnValue);

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::StatisticsSamples) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  StatisticsSamplesWorker* worker = new StatisticsSamplesWorker(
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

void StatisticsWeightSumWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::Statistics, QuantLib::Statistics)


  // invoke the member function
  QuantLib::Real returnValue = ObjectIDLibObjPtr->weightSum(
      );


  mReturnValue = returnValue;

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::StatisticsWeightSum) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  StatisticsWeightSumWorker* worker = new StatisticsWeightSumWorker(
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

void StatisticsMeanWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::Statistics, QuantLib::Statistics)


  // invoke the member function
  QuantLib::Real returnValue = ObjectIDLibObjPtr->mean(
      );


  mReturnValue = returnValue;

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::StatisticsMean) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  StatisticsMeanWorker* worker = new StatisticsMeanWorker(
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

void StatisticsVarianceWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::Statistics, QuantLib::Statistics)


  // invoke the member function
  QuantLib::Real returnValue = ObjectIDLibObjPtr->variance(
      );


  mReturnValue = returnValue;

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::StatisticsVariance) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  StatisticsVarianceWorker* worker = new StatisticsVarianceWorker(
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

void StatisticsStandardDeviationWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::Statistics, QuantLib::Statistics)


  // invoke the member function
  QuantLib::Real returnValue = ObjectIDLibObjPtr->standardDeviation(
      );


  mReturnValue = returnValue;

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::StatisticsStandardDeviation) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  StatisticsStandardDeviationWorker* worker = new StatisticsStandardDeviationWorker(
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

void StatisticsErrorEstimateWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::Statistics, QuantLib::Statistics)


  // invoke the member function
  QuantLib::Real returnValue = ObjectIDLibObjPtr->errorEstimate(
      );


  mReturnValue = returnValue;

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::StatisticsErrorEstimate) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  StatisticsErrorEstimateWorker* worker = new StatisticsErrorEstimateWorker(
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

void StatisticsSkewnessWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::Statistics, QuantLib::Statistics)


  // invoke the member function
  QuantLib::Real returnValue = ObjectIDLibObjPtr->skewness(
      );


  mReturnValue = returnValue;

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::StatisticsSkewness) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  StatisticsSkewnessWorker* worker = new StatisticsSkewnessWorker(
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

void StatisticsKurtosisWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::Statistics, QuantLib::Statistics)


  // invoke the member function
  QuantLib::Real returnValue = ObjectIDLibObjPtr->kurtosis(
      );


  mReturnValue = returnValue;

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::StatisticsKurtosis) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  StatisticsKurtosisWorker* worker = new StatisticsKurtosisWorker(
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

void StatisticsMinWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::Statistics, QuantLib::Statistics)


  // invoke the member function
  QuantLib::Real returnValue = ObjectIDLibObjPtr->min(
      );


  mReturnValue = returnValue;

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::StatisticsMin) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  StatisticsMinWorker* worker = new StatisticsMinWorker(
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

void StatisticsMaxWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::Statistics, QuantLib::Statistics)


  // invoke the member function
  QuantLib::Real returnValue = ObjectIDLibObjPtr->max(
      );


  mReturnValue = returnValue;

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::StatisticsMax) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  StatisticsMaxWorker* worker = new StatisticsMaxWorker(
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

void StatisticsPercentileWorker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::Statistics, QuantLib::Statistics)


  // invoke the member function
  QuantLib::Real returnValue = ObjectIDLibObjPtr->percentile(
        mX
       );


  mReturnValue = returnValue;

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::StatisticsPercentile) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsNumber()) {
      return Nan::ThrowError("X is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  double XCpp = Nan::To<double>(info[1]).FromJust();

 
  // launch worker
  StatisticsPercentileWorker* worker = new StatisticsPercentileWorker(
    ObjectIDCpp
,     XCpp
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

void StatisticsTopPercentileWorker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::Statistics, QuantLib::Statistics)


  // invoke the member function
  QuantLib::Real returnValue = ObjectIDLibObjPtr->topPercentile(
        mX
       );


  mReturnValue = returnValue;

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::StatisticsTopPercentile) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsNumber()) {
      return Nan::ThrowError("X is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  double XCpp = Nan::To<double>(info[1]).FromJust();

 
  // launch worker
  StatisticsTopPercentileWorker* worker = new StatisticsTopPercentileWorker(
    ObjectIDCpp
,     XCpp
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

void StatisticsGaussianDownsideVarianceWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::Statistics, QuantLib::Statistics)


  // invoke the member function
  QuantLib::Real returnValue = ObjectIDLibObjPtr->gaussianDownsideVariance(
      );


  mReturnValue = returnValue;

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::StatisticsGaussianDownsideVariance) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  StatisticsGaussianDownsideVarianceWorker* worker = new StatisticsGaussianDownsideVarianceWorker(
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

void StatisticsGaussianDownsideDeviationWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::Statistics, QuantLib::Statistics)


  // invoke the member function
  QuantLib::Real returnValue = ObjectIDLibObjPtr->gaussianDownsideDeviation(
      );


  mReturnValue = returnValue;

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::StatisticsGaussianDownsideDeviation) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  StatisticsGaussianDownsideDeviationWorker* worker = new StatisticsGaussianDownsideDeviationWorker(
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

void StatisticsGaussianRegretWorker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::Statistics, QuantLib::Statistics)


  // invoke the member function
  QuantLib::Real returnValue = ObjectIDLibObjPtr->gaussianRegret(
        mTarget
       );


  mReturnValue = returnValue;

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::StatisticsGaussianRegret) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsNumber()) {
      return Nan::ThrowError("Target is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  double TargetCpp = Nan::To<double>(info[1]).FromJust();

 
  // launch worker
  StatisticsGaussianRegretWorker* worker = new StatisticsGaussianRegretWorker(
    ObjectIDCpp
,     TargetCpp
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

void StatisticsGaussianPercentileWorker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::Statistics, QuantLib::Statistics)


  // invoke the member function
  QuantLib::Real returnValue = ObjectIDLibObjPtr->gaussianPercentile(
        mX
       );


  mReturnValue = returnValue;

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::StatisticsGaussianPercentile) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsNumber()) {
      return Nan::ThrowError("X is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  double XCpp = Nan::To<double>(info[1]).FromJust();

 
  // launch worker
  StatisticsGaussianPercentileWorker* worker = new StatisticsGaussianPercentileWorker(
    ObjectIDCpp
,     XCpp
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

void StatisticsGaussianTopPercentileWorker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::Statistics, QuantLib::Statistics)


  // invoke the member function
  QuantLib::Real returnValue = ObjectIDLibObjPtr->gaussianTopPercentile(
        mX
       );


  mReturnValue = returnValue;

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::StatisticsGaussianTopPercentile) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsNumber()) {
      return Nan::ThrowError("X is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  double XCpp = Nan::To<double>(info[1]).FromJust();

 
  // launch worker
  StatisticsGaussianTopPercentileWorker* worker = new StatisticsGaussianTopPercentileWorker(
    ObjectIDCpp
,     XCpp
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

void StatisticsGaussianPotentialUpsideWorker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::Statistics, QuantLib::Statistics)


  // invoke the member function
  QuantLib::Real returnValue = ObjectIDLibObjPtr->gaussianPotentialUpside(
        mTarget
       );


  mReturnValue = returnValue;

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::StatisticsGaussianPotentialUpside) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsNumber()) {
      return Nan::ThrowError("Target is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  double TargetCpp = Nan::To<double>(info[1]).FromJust();

 
  // launch worker
  StatisticsGaussianPotentialUpsideWorker* worker = new StatisticsGaussianPotentialUpsideWorker(
    ObjectIDCpp
,     TargetCpp
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

void StatisticsGaussianValueAtRiskWorker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::Statistics, QuantLib::Statistics)


  // invoke the member function
  QuantLib::Real returnValue = ObjectIDLibObjPtr->gaussianValueAtRisk(
        mTarget
       );


  mReturnValue = returnValue;

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::StatisticsGaussianValueAtRisk) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsNumber()) {
      return Nan::ThrowError("Target is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  double TargetCpp = Nan::To<double>(info[1]).FromJust();

 
  // launch worker
  StatisticsGaussianValueAtRiskWorker* worker = new StatisticsGaussianValueAtRiskWorker(
    ObjectIDCpp
,     TargetCpp
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

void StatisticsGaussianExpectedShortfallWorker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::Statistics, QuantLib::Statistics)


  // invoke the member function
  QuantLib::Real returnValue = ObjectIDLibObjPtr->gaussianExpectedShortfall(
        mTarget
       );


  mReturnValue = returnValue;

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::StatisticsGaussianExpectedShortfall) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsNumber()) {
      return Nan::ThrowError("Target is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  double TargetCpp = Nan::To<double>(info[1]).FromJust();

 
  // launch worker
  StatisticsGaussianExpectedShortfallWorker* worker = new StatisticsGaussianExpectedShortfallWorker(
    ObjectIDCpp
,     TargetCpp
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

void StatisticsGaussianShortfallWorker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::Statistics, QuantLib::Statistics)


  // invoke the member function
  QuantLib::Real returnValue = ObjectIDLibObjPtr->gaussianShortfall(
        mTarget
       );


  mReturnValue = returnValue;

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::StatisticsGaussianShortfall) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsNumber()) {
      return Nan::ThrowError("Target is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  double TargetCpp = Nan::To<double>(info[1]).FromJust();

 
  // launch worker
  StatisticsGaussianShortfallWorker* worker = new StatisticsGaussianShortfallWorker(
    ObjectIDCpp
,     TargetCpp
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

void StatisticsGaussianAverageShortfallWorker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::Statistics, QuantLib::Statistics)


  // invoke the member function
  QuantLib::Real returnValue = ObjectIDLibObjPtr->gaussianAverageShortfall(
        mTarget
       );


  mReturnValue = returnValue;

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::StatisticsGaussianAverageShortfall) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsNumber()) {
      return Nan::ThrowError("Target is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  double TargetCpp = Nan::To<double>(info[1]).FromJust();

 
  // launch worker
  StatisticsGaussianAverageShortfallWorker* worker = new StatisticsGaussianAverageShortfallWorker(
    ObjectIDCpp
,     TargetCpp
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

void StatisticsSemiVarianceWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::Statistics, QuantLib::Statistics)


  // invoke the member function
  QuantLib::Real returnValue = ObjectIDLibObjPtr->semiVariance(
      );


  mReturnValue = returnValue;

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::StatisticsSemiVariance) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  StatisticsSemiVarianceWorker* worker = new StatisticsSemiVarianceWorker(
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

void StatisticsSemiDeviationWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::Statistics, QuantLib::Statistics)


  // invoke the member function
  QuantLib::Real returnValue = ObjectIDLibObjPtr->semiDeviation(
      );


  mReturnValue = returnValue;

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::StatisticsSemiDeviation) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  StatisticsSemiDeviationWorker* worker = new StatisticsSemiDeviationWorker(
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

void StatisticsDownsideVarianceWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::Statistics, QuantLib::Statistics)


  // invoke the member function
  QuantLib::Real returnValue = ObjectIDLibObjPtr->downsideVariance(
      );


  mReturnValue = returnValue;

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::StatisticsDownsideVariance) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  StatisticsDownsideVarianceWorker* worker = new StatisticsDownsideVarianceWorker(
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

void StatisticsDownsideDeviationWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::Statistics, QuantLib::Statistics)


  // invoke the member function
  QuantLib::Real returnValue = ObjectIDLibObjPtr->downsideDeviation(
      );


  mReturnValue = returnValue;

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::StatisticsDownsideDeviation) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  StatisticsDownsideDeviationWorker* worker = new StatisticsDownsideDeviationWorker(
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

void StatisticsRegretWorker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::Statistics, QuantLib::Statistics)


  // invoke the member function
  QuantLib::Real returnValue = ObjectIDLibObjPtr->regret(
        mTarget
       );


  mReturnValue = returnValue;

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::StatisticsRegret) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsNumber()) {
      return Nan::ThrowError("Target is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  double TargetCpp = Nan::To<double>(info[1]).FromJust();

 
  // launch worker
  StatisticsRegretWorker* worker = new StatisticsRegretWorker(
    ObjectIDCpp
,     TargetCpp
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

void StatisticsPotentialUpsideWorker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::Statistics, QuantLib::Statistics)


  // invoke the member function
  QuantLib::Real returnValue = ObjectIDLibObjPtr->potentialUpside(
        mCentile
       );


  mReturnValue = returnValue;

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::StatisticsPotentialUpside) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsNumber()) {
      return Nan::ThrowError("Centile is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  double CentileCpp = Nan::To<double>(info[1]).FromJust();

 
  // launch worker
  StatisticsPotentialUpsideWorker* worker = new StatisticsPotentialUpsideWorker(
    ObjectIDCpp
,     CentileCpp
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

void StatisticsValueAtRiskWorker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::Statistics, QuantLib::Statistics)


  // invoke the member function
  QuantLib::Real returnValue = ObjectIDLibObjPtr->valueAtRisk(
        mTarget
       );


  mReturnValue = returnValue;

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::StatisticsValueAtRisk) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsNumber()) {
      return Nan::ThrowError("Target is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  double TargetCpp = Nan::To<double>(info[1]).FromJust();

 
  // launch worker
  StatisticsValueAtRiskWorker* worker = new StatisticsValueAtRiskWorker(
    ObjectIDCpp
,     TargetCpp
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

void StatisticsExpectedShortfallWorker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::Statistics, QuantLib::Statistics)


  // invoke the member function
  QuantLib::Real returnValue = ObjectIDLibObjPtr->expectedShortfall(
        mCentile
       );


  mReturnValue = returnValue;

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::StatisticsExpectedShortfall) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsNumber()) {
      return Nan::ThrowError("Centile is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  double CentileCpp = Nan::To<double>(info[1]).FromJust();

 
  // launch worker
  StatisticsExpectedShortfallWorker* worker = new StatisticsExpectedShortfallWorker(
    ObjectIDCpp
,     CentileCpp
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

void StatisticsShortfallWorker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::Statistics, QuantLib::Statistics)


  // invoke the member function
  QuantLib::Real returnValue = ObjectIDLibObjPtr->shortfall(
        mTarget
       );


  mReturnValue = returnValue;

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::StatisticsShortfall) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsNumber()) {
      return Nan::ThrowError("Target is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  double TargetCpp = Nan::To<double>(info[1]).FromJust();

 
  // launch worker
  StatisticsShortfallWorker* worker = new StatisticsShortfallWorker(
    ObjectIDCpp
,     TargetCpp
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

void StatisticsAverageShortfallWorker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::Statistics, QuantLib::Statistics)


  // invoke the member function
  QuantLib::Real returnValue = ObjectIDLibObjPtr->averageShortfall(
        mTarget
       );


  mReturnValue = returnValue;

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::StatisticsAverageShortfall) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsNumber()) {
      return Nan::ThrowError("Target is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  double TargetCpp = Nan::To<double>(info[1]).FromJust();

 
  // launch worker
  StatisticsAverageShortfallWorker* worker = new StatisticsAverageShortfallWorker(
    ObjectIDCpp
,     TargetCpp
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

void GaussianDownsideVarianceWorker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes

  // convert input datatypes to QuantLib datatypes
       // invoke the utility function
  QuantLib::Real returnValue = QuantLibAddin::gaussianDownsideVariance(
      mMean
      ,
       mStdDev
     );

  mReturnValue = returnValue;

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::GaussianDownsideVariance) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsNumber()) {
      return Nan::ThrowError("Mean is required.");
  }
  if (info.Length() == 1 || !info[1]->IsNumber()) {
      return Nan::ThrowError("StdDev is required.");
  }
  // convert js argument to c++ type
  double MeanCpp = Nan::To<double>(info[0]).FromJust();

  // convert js argument to c++ type
  double StdDevCpp = Nan::To<double>(info[1]).FromJust();

 
  // launch worker
  GaussianDownsideVarianceWorker* worker = new GaussianDownsideVarianceWorker(
    MeanCpp
,     StdDevCpp
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

void GaussianDownsideDeviationWorker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes

  // convert input datatypes to QuantLib datatypes
       // invoke the utility function
  QuantLib::Real returnValue = QuantLibAddin::gaussianDownsideDeviation(
      mMean
      ,
       mStdDev
     );

  mReturnValue = returnValue;

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::GaussianDownsideDeviation) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsNumber()) {
      return Nan::ThrowError("Mean is required.");
  }
  if (info.Length() == 1 || !info[1]->IsNumber()) {
      return Nan::ThrowError("StdDev is required.");
  }
  // convert js argument to c++ type
  double MeanCpp = Nan::To<double>(info[0]).FromJust();

  // convert js argument to c++ type
  double StdDevCpp = Nan::To<double>(info[1]).FromJust();

 
  // launch worker
  GaussianDownsideDeviationWorker* worker = new GaussianDownsideDeviationWorker(
    MeanCpp
,     StdDevCpp
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

void GaussianRegretWorker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes

  // convert input datatypes to QuantLib datatypes

  // convert input datatypes to QuantLib datatypes
       // invoke the utility function
  QuantLib::Real returnValue = QuantLibAddin::gaussianRegret(
      mTarget
      ,
       mMean
      ,
       mStdDev
     );

  mReturnValue = returnValue;

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::GaussianRegret) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsNumber()) {
      return Nan::ThrowError("Target is required.");
  }
  if (info.Length() == 1 || !info[1]->IsNumber()) {
      return Nan::ThrowError("Mean is required.");
  }
  if (info.Length() == 2 || !info[2]->IsNumber()) {
      return Nan::ThrowError("StdDev is required.");
  }
  // convert js argument to c++ type
  double TargetCpp = Nan::To<double>(info[0]).FromJust();

  // convert js argument to c++ type
  double MeanCpp = Nan::To<double>(info[1]).FromJust();

  // convert js argument to c++ type
  double StdDevCpp = Nan::To<double>(info[2]).FromJust();

 
  // launch worker
  GaussianRegretWorker* worker = new GaussianRegretWorker(
    TargetCpp
,     MeanCpp
,     StdDevCpp
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

void GaussianPercentileWorker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes

  // convert input datatypes to QuantLib datatypes

  // convert input datatypes to QuantLib datatypes
       // invoke the utility function
  QuantLib::Real returnValue = QuantLibAddin::gaussianPercentile(
      mX
      ,
       mMean
      ,
       mStdDev
     );

  mReturnValue = returnValue;

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::GaussianPercentile) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsNumber()) {
      return Nan::ThrowError("X is required.");
  }
  if (info.Length() == 1 || !info[1]->IsNumber()) {
      return Nan::ThrowError("Mean is required.");
  }
  if (info.Length() == 2 || !info[2]->IsNumber()) {
      return Nan::ThrowError("StdDev is required.");
  }
  // convert js argument to c++ type
  double XCpp = Nan::To<double>(info[0]).FromJust();

  // convert js argument to c++ type
  double MeanCpp = Nan::To<double>(info[1]).FromJust();

  // convert js argument to c++ type
  double StdDevCpp = Nan::To<double>(info[2]).FromJust();

 
  // launch worker
  GaussianPercentileWorker* worker = new GaussianPercentileWorker(
    XCpp
,     MeanCpp
,     StdDevCpp
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

void GaussianTopPercentileWorker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes

  // convert input datatypes to QuantLib datatypes

  // convert input datatypes to QuantLib datatypes
       // invoke the utility function
  QuantLib::Real returnValue = QuantLibAddin::gaussianTopPercentile(
      mX
      ,
       mMean
      ,
       mStdDev
     );

  mReturnValue = returnValue;

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::GaussianTopPercentile) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsNumber()) {
      return Nan::ThrowError("X is required.");
  }
  if (info.Length() == 1 || !info[1]->IsNumber()) {
      return Nan::ThrowError("Mean is required.");
  }
  if (info.Length() == 2 || !info[2]->IsNumber()) {
      return Nan::ThrowError("StdDev is required.");
  }
  // convert js argument to c++ type
  double XCpp = Nan::To<double>(info[0]).FromJust();

  // convert js argument to c++ type
  double MeanCpp = Nan::To<double>(info[1]).FromJust();

  // convert js argument to c++ type
  double StdDevCpp = Nan::To<double>(info[2]).FromJust();

 
  // launch worker
  GaussianTopPercentileWorker* worker = new GaussianTopPercentileWorker(
    XCpp
,     MeanCpp
,     StdDevCpp
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

void GaussianPotentialUpsideWorker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes

  // convert input datatypes to QuantLib datatypes

  // convert input datatypes to QuantLib datatypes
       // invoke the utility function
  QuantLib::Real returnValue = QuantLibAddin::gaussianPotentialUpside(
      mTarget
      ,
       mMean
      ,
       mStdDev
     );

  mReturnValue = returnValue;

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::GaussianPotentialUpside) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsNumber()) {
      return Nan::ThrowError("Target is required.");
  }
  if (info.Length() == 1 || !info[1]->IsNumber()) {
      return Nan::ThrowError("Mean is required.");
  }
  if (info.Length() == 2 || !info[2]->IsNumber()) {
      return Nan::ThrowError("StdDev is required.");
  }
  // convert js argument to c++ type
  double TargetCpp = Nan::To<double>(info[0]).FromJust();

  // convert js argument to c++ type
  double MeanCpp = Nan::To<double>(info[1]).FromJust();

  // convert js argument to c++ type
  double StdDevCpp = Nan::To<double>(info[2]).FromJust();

 
  // launch worker
  GaussianPotentialUpsideWorker* worker = new GaussianPotentialUpsideWorker(
    TargetCpp
,     MeanCpp
,     StdDevCpp
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

void GaussianValueAtRiskWorker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes

  // convert input datatypes to QuantLib datatypes

  // convert input datatypes to QuantLib datatypes
       // invoke the utility function
  QuantLib::Real returnValue = QuantLibAddin::gaussianValueAtRisk(
      mTarget
      ,
       mMean
      ,
       mStdDev
     );

  mReturnValue = returnValue;

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::GaussianValueAtRisk) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsNumber()) {
      return Nan::ThrowError("Target is required.");
  }
  if (info.Length() == 1 || !info[1]->IsNumber()) {
      return Nan::ThrowError("Mean is required.");
  }
  if (info.Length() == 2 || !info[2]->IsNumber()) {
      return Nan::ThrowError("StdDev is required.");
  }
  // convert js argument to c++ type
  double TargetCpp = Nan::To<double>(info[0]).FromJust();

  // convert js argument to c++ type
  double MeanCpp = Nan::To<double>(info[1]).FromJust();

  // convert js argument to c++ type
  double StdDevCpp = Nan::To<double>(info[2]).FromJust();

 
  // launch worker
  GaussianValueAtRiskWorker* worker = new GaussianValueAtRiskWorker(
    TargetCpp
,     MeanCpp
,     StdDevCpp
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

void GaussianExpectedShortfallWorker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes

  // convert input datatypes to QuantLib datatypes

  // convert input datatypes to QuantLib datatypes
       // invoke the utility function
  QuantLib::Real returnValue = QuantLibAddin::gaussianExpectedShortfall(
      mTarget
      ,
       mMean
      ,
       mStdDev
     );

  mReturnValue = returnValue;

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::GaussianExpectedShortfall) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsNumber()) {
      return Nan::ThrowError("Target is required.");
  }
  if (info.Length() == 1 || !info[1]->IsNumber()) {
      return Nan::ThrowError("Mean is required.");
  }
  if (info.Length() == 2 || !info[2]->IsNumber()) {
      return Nan::ThrowError("StdDev is required.");
  }
  // convert js argument to c++ type
  double TargetCpp = Nan::To<double>(info[0]).FromJust();

  // convert js argument to c++ type
  double MeanCpp = Nan::To<double>(info[1]).FromJust();

  // convert js argument to c++ type
  double StdDevCpp = Nan::To<double>(info[2]).FromJust();

 
  // launch worker
  GaussianExpectedShortfallWorker* worker = new GaussianExpectedShortfallWorker(
    TargetCpp
,     MeanCpp
,     StdDevCpp
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

void GaussianShortfallWorker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes

  // convert input datatypes to QuantLib datatypes

  // convert input datatypes to QuantLib datatypes
       // invoke the utility function
  QuantLib::Real returnValue = QuantLibAddin::gaussianShortfall(
      mTarget
      ,
       mMean
      ,
       mStdDev
     );

  mReturnValue = returnValue;

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::GaussianShortfall) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsNumber()) {
      return Nan::ThrowError("Target is required.");
  }
  if (info.Length() == 1 || !info[1]->IsNumber()) {
      return Nan::ThrowError("Mean is required.");
  }
  if (info.Length() == 2 || !info[2]->IsNumber()) {
      return Nan::ThrowError("StdDev is required.");
  }
  // convert js argument to c++ type
  double TargetCpp = Nan::To<double>(info[0]).FromJust();

  // convert js argument to c++ type
  double MeanCpp = Nan::To<double>(info[1]).FromJust();

  // convert js argument to c++ type
  double StdDevCpp = Nan::To<double>(info[2]).FromJust();

 
  // launch worker
  GaussianShortfallWorker* worker = new GaussianShortfallWorker(
    TargetCpp
,     MeanCpp
,     StdDevCpp
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

void GaussianAverageShortfallWorker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes

  // convert input datatypes to QuantLib datatypes

  // convert input datatypes to QuantLib datatypes
       // invoke the utility function
  QuantLib::Real returnValue = QuantLibAddin::gaussianAverageShortfall(
      mTarget
      ,
       mMean
      ,
       mStdDev
     );

  mReturnValue = returnValue;

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::GaussianAverageShortfall) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsNumber()) {
      return Nan::ThrowError("Target is required.");
  }
  if (info.Length() == 1 || !info[1]->IsNumber()) {
      return Nan::ThrowError("Mean is required.");
  }
  if (info.Length() == 2 || !info[2]->IsNumber()) {
      return Nan::ThrowError("StdDev is required.");
  }
  // convert js argument to c++ type
  double TargetCpp = Nan::To<double>(info[0]).FromJust();

  // convert js argument to c++ type
  double MeanCpp = Nan::To<double>(info[1]).FromJust();

  // convert js argument to c++ type
  double StdDevCpp = Nan::To<double>(info[2]).FromJust();

 
  // launch worker
  GaussianAverageShortfallWorker* worker = new GaussianAverageShortfallWorker(
    TargetCpp
,     MeanCpp
,     StdDevCpp
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
 