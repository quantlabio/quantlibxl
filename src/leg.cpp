/* 
  Copyright (C) 2016 -2017 Jerry Jin
*/

#include <nan.h>
#include <string.h>

#include "leg.hpp"

#include <qlo/qladdindefines.hpp>
#include <qlo/couponvectors.hpp>
#include <qlo/conundrumpricer.hpp>
#include <qlo/termstructures.hpp>
#include <qlo/capfloor.hpp>
#include <qlo/swap.hpp>
#include <ql/termstructures/yieldtermstructure.hpp>
#include <ql/instruments/swap.hpp>
 #include <oh/objecthandler.hpp>
#include <oh/conversions/getobjectvector.hpp>
#include <qlo/valueobjects/vo_all.hpp>
#include <qlo/conversions/all.hpp>
#include "../loop.hpp"


void LegWorker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes
  std::vector<QuantLib::Date> DatesLib = ObjectHandler::vector::convert2<QuantLib::Date>(
      mDates, "Dates");

 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlLeg(
          mObjectID,
          mAmounts,
          mDates,
          mToBeSorted,
          false
      ));

    // Construct the Object
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::Leg(
          valueObject,
          mAmounts,
          DatesLib,
          mToBeSorted,
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

NAN_METHOD(QuantLibXL::Leg) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsArray()) {
      return Nan::ThrowError("Amounts is required.");
  }
  if (info.Length() == 2 || !info[2]->IsArray()) {
      return Nan::ThrowError("Dates is required.");
  }
  if (info.Length() == 3 || !info[3]->IsBoolean()) {
      return Nan::ThrowError("ToBeSorted is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  std::vector<double>AmountsCpp;

  Local<Array> AmountsArray = info[1].As<Array>();
  for (unsigned int i = 0; i < AmountsArray->Length(); i++){
    AmountsCpp.push_back(Nan::To<double>(Nan::Get(AmountsArray, i).ToLocalChecked()).FromJust());
  }

  // convert js argument to c++ type
  std::vector<ObjectHandler::property_t>DatesCpp;

  Local<Array> DatesArray = info[2].As<Array>();
  for (unsigned int i = 0; i < DatesArray->Length(); i++){
    ObjectHandler::property_t tmp =
        ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(Nan::Get(DatesArray, i).ToLocalChecked()).FromJust()));
    DatesCpp.push_back(tmp);
  }

  // convert js argument to c++ type
  bool ToBeSortedCpp = Nan::To<bool>(info[3]).FromJust();

 
  // launch worker
  LegWorker* worker = new LegWorker(
    ObjectIDCpp
,     AmountsCpp
,     DatesCpp
,     ToBeSortedCpp
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

void LegFromCapFloorWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_REFERENCE(CapFloorLibObjPtr, mCapFloor,
      QuantLibAddin::CapFloor, QuantLib::CapFloor)

 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlLegFromCapFloor(
          mObjectID,
          mCapFloor,
          false
      ));

    // Construct the Object
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::Leg(
          valueObject,
          CapFloorLibObjPtr,
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

NAN_METHOD(QuantLibXL::LegFromCapFloor) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsString()) {
      return Nan::ThrowError("CapFloor is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  String::Utf8Value strCapFloor(info[1]->ToString());
  string CapFloorCpp(strdup(*strCapFloor));

 
  // launch worker
  LegFromCapFloorWorker* worker = new LegFromCapFloorWorker(
    ObjectIDCpp
,     CapFloorCpp
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

void LegFromSwapWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_REFERENCE(SwapLibObjPtr, mSwap,
      QuantLibAddin::Swap, QuantLib::Swap)

 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlLegFromSwap(
          mObjectID,
          mSwap,
          mLegNumber,
          false
      ));

    // Construct the Object
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::Leg(
          valueObject,
          SwapLibObjPtr,
          mLegNumber,
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

NAN_METHOD(QuantLibXL::LegFromSwap) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsString()) {
      return Nan::ThrowError("Swap is required.");
  }
  if (info.Length() == 2 || !info[2]->IsNumber()) {
      return Nan::ThrowError("LegNumber is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  String::Utf8Value strSwap(info[1]->ToString());
  string SwapCpp(strdup(*strSwap));

  // convert js argument to c++ type
  long LegNumberCpp = Nan::To<int32_t>(info[2]).FromJust();

 
  // launch worker
  LegFromSwapWorker* worker = new LegFromSwapWorker(
    ObjectIDCpp
,     SwapCpp
,     LegNumberCpp
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

void MultiPhaseLegWorker::Execute(){

  try{

  // convert object IDs into library objects
  std::vector< boost::shared_ptr<QuantLibAddin::Leg> > LegIDsObjPtr =
      ObjectHandler::getObjectVector<QuantLibAddin::Leg>(mLegIDs);

 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlMultiPhaseLeg(
          mObjectID,
          mLegIDs,
          mToBeSorted,
          false
      ));

    // Construct the Object
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::MultiPhaseLeg(
          valueObject,
          LegIDsObjPtr,
          mToBeSorted,
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

NAN_METHOD(QuantLibXL::MultiPhaseLeg) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsArray()) {
      return Nan::ThrowError("LegIDs is required.");
  }
  if (info.Length() == 2 || !info[2]->IsBoolean()) {
      return Nan::ThrowError("ToBeSorted is required.");
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
  bool ToBeSortedCpp = Nan::To<bool>(info[2]).FromJust();

 
  // launch worker
  MultiPhaseLegWorker* worker = new MultiPhaseLegWorker(
    ObjectIDCpp
,     LegIDsCpp
,     ToBeSortedCpp
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

void InterestRateWorker::Execute(){

  try{

  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::DayCounter DayCounterEnum =
      ObjectHandler::Create<QuantLib::DayCounter>()(mDayCounter);


  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::Compounding CompoundingEnum =
      ObjectHandler::Create<QuantLib::Compounding>()(mCompounding);


  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::Frequency FrequencyEnum =
      ObjectHandler::Create<QuantLib::Frequency>()(mFrequency);

 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlInterestRate(
          mObjectID,
          mRate,
          mDayCounter,
          mCompounding,
          mFrequency,
          false
      ));

    // Construct the Object
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::InterestRate(
          valueObject,
          mRate,
          DayCounterEnum,
          CompoundingEnum,
          FrequencyEnum,
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

NAN_METHOD(QuantLibXL::InterestRate) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsNumber()) {
      return Nan::ThrowError("Rate is required.");
  }
  if (info.Length() == 2 || !info[2]->IsString()) {
      return Nan::ThrowError("DayCounter is required.");
  }
  if (info.Length() == 3 || !info[3]->IsString()) {
      return Nan::ThrowError("Compounding is required.");
  }
  if (info.Length() == 4 || !info[4]->IsString()) {
      return Nan::ThrowError("Frequency is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  double RateCpp = Nan::To<double>(info[1]).FromJust();

  // convert js argument to c++ type
  String::Utf8Value strDayCounter(info[2]->ToString());
  string DayCounterCpp(strdup(*strDayCounter));

  // convert js argument to c++ type
  String::Utf8Value strCompounding(info[3]->ToString());
  string CompoundingCpp(strdup(*strCompounding));

  // convert js argument to c++ type
  String::Utf8Value strFrequency(info[4]->ToString());
  string FrequencyCpp(strdup(*strFrequency));

 
  // launch worker
  InterestRateWorker* worker = new InterestRateWorker(
    ObjectIDCpp
,     RateCpp
,     DayCounterCpp
,     CompoundingCpp
,     FrequencyCpp
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

void LegFlowAnalysisWorker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes
  QuantLib::Date AfterDateLib = ObjectHandler::convert2<QuantLib::Date>(
      mAfterDate, "AfterDate");

       // convert object IDs into library objects
  OH_GET_OBJECT(ObjectIDObjPtr, mObjectID, QuantLibAddin::Leg)

  std::vector< std::vector<ObjectHandler::property_t> > returnValue;


  // invoke the member function
  returnValue = ObjectIDObjPtr->flowAnalysis(
        AfterDateLib
       );


  mReturnValue = ObjectHandler::matrix::convert2<string>(returnValue,"returnValue");

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::LegFlowAnalysis) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  ObjectHandler::property_t AfterDateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[1]).FromJust()));

 
  // launch worker
  LegFlowAnalysisWorker* worker = new LegFlowAnalysisWorker(
    ObjectIDCpp
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

void LegSetCouponPricersWorker::Execute(){

  try{

  // convert object IDs into library objects
  std::vector< boost::shared_ptr<QuantLibAddin::FloatingRateCouponPricer> > FloatingRateCouponPricerObjPtr =
      ObjectHandler::getObjectVector<QuantLibAddin::FloatingRateCouponPricer>(mFloatingRateCouponPricer);

       // convert object IDs into library objects
  OH_GET_OBJECT(ObjectIDObjPtr, mObjectID, QuantLibAddin::Leg)


  // invoke the member function
  ObjectIDObjPtr->setCouponPricers(
        FloatingRateCouponPricerObjPtr
       );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::LegSetCouponPricers) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsArray()) {
      return Nan::ThrowError("FloatingRateCouponPricer is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  std::vector<string>FloatingRateCouponPricerCpp;

  Local<Array> FloatingRateCouponPricerArray = info[1].As<Array>();
  for (unsigned int i = 0; i < FloatingRateCouponPricerArray->Length(); i++){
    String::Utf8Value strFloatingRateCouponPricer(Nan::Get(FloatingRateCouponPricerArray, i).ToLocalChecked()->ToString());
    FloatingRateCouponPricerCpp.push_back(strdup(*strFloatingRateCouponPricer));
  }

 
  // launch worker
  LegSetCouponPricersWorker* worker = new LegSetCouponPricersWorker(
    ObjectIDCpp
,     FloatingRateCouponPricerCpp
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

void InterestRateRateWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::InterestRate, QuantLib::InterestRate)

     
  // invoke the member function
  mReturnValue = ObjectIDLibObjPtr->rate(
      );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::InterestRateRate) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  InterestRateRateWorker* worker = new InterestRateRateWorker(
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

void InterestRateDayCounterWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::InterestRate, QuantLib::InterestRate)

     
  // invoke the member function
  QuantLib::DayCounter returnValue = ObjectIDLibObjPtr->dayCounter(
      );


  std::ostringstream os;
  os << returnValue;
  mReturnValue = os.str();

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::InterestRateDayCounter) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  InterestRateDayCounterWorker* worker = new InterestRateDayCounterWorker(
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

void InterestRateCompoundingWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::InterestRate, QuantLib::InterestRate)

     
  // invoke the member function
  QuantLib::Compounding returnValue = ObjectIDLibObjPtr->compounding(
      );


  std::ostringstream os;
  os << returnValue;
  mReturnValue = os.str();

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::InterestRateCompounding) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  InterestRateCompoundingWorker* worker = new InterestRateCompoundingWorker(
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

void InterestRateFrequencyWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::InterestRate, QuantLib::InterestRate)

     
  // invoke the member function
  QuantLib::Frequency returnValue = ObjectIDLibObjPtr->frequency(
      );


  std::ostringstream os;
  os << returnValue;
  mReturnValue = os.str();

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::InterestRateFrequency) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  InterestRateFrequencyWorker* worker = new InterestRateFrequencyWorker(
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

void InterestRateDiscountFactorWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::InterestRate, QuantLib::InterestRate)


  // convert input datatypes to QuantLib datatypes
  QuantLib::Date StartDateLib = ObjectHandler::convert2<QuantLib::Date>(
      mStartDate, "StartDate");


  // convert input datatypes to QuantLib datatypes
  QuantLib::Date EndDateLib = ObjectHandler::convert2<QuantLib::Date>(
      mEndDate, "EndDate");


  // convert input datatypes to QuantLib datatypes
  QuantLib::Date RefPeriodStartLib = ObjectHandler::convert2<QuantLib::Date>(
      mRefPeriodStart, "RefPeriodStart");


  // convert input datatypes to QuantLib datatypes
  QuantLib::Date RefPeriodEndLib = ObjectHandler::convert2<QuantLib::Date>(
      mRefPeriodEnd, "RefPeriodEnd");

     
  // invoke the member function
  QuantLib::Real returnValue = ObjectIDLibObjPtr->discountFactor(
        StartDateLib
        ,
         EndDateLib
        ,
         RefPeriodStartLib
        ,
         RefPeriodEndLib
       );


  mReturnValue = returnValue;

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::InterestRateDiscountFactor) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  ObjectHandler::property_t StartDateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[1]).FromJust()));

  // convert js argument to c++ type
  ObjectHandler::property_t EndDateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[2]).FromJust()));

  // convert js argument to c++ type
  ObjectHandler::property_t RefPeriodStartCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[3]).FromJust()));

  // convert js argument to c++ type
  ObjectHandler::property_t RefPeriodEndCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[4]).FromJust()));

 
  // launch worker
  InterestRateDiscountFactorWorker* worker = new InterestRateDiscountFactorWorker(
    ObjectIDCpp
,     StartDateCpp
,     EndDateCpp
,     RefPeriodStartCpp
,     RefPeriodEndCpp
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

void InterestRateCompoundFactorWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::InterestRate, QuantLib::InterestRate)


  // convert input datatypes to QuantLib datatypes
  QuantLib::Date StartDateLib = ObjectHandler::convert2<QuantLib::Date>(
      mStartDate, "StartDate");


  // convert input datatypes to QuantLib datatypes
  QuantLib::Date EndDateLib = ObjectHandler::convert2<QuantLib::Date>(
      mEndDate, "EndDate");


  // convert input datatypes to QuantLib datatypes
  QuantLib::Date RefPeriodStartLib = ObjectHandler::convert2<QuantLib::Date>(
      mRefPeriodStart, "RefPeriodStart");


  // convert input datatypes to QuantLib datatypes
  QuantLib::Date RefPeriodEndLib = ObjectHandler::convert2<QuantLib::Date>(
      mRefPeriodEnd, "RefPeriodEnd");

     
  // invoke the member function
  QuantLib::Real returnValue = ObjectIDLibObjPtr->compoundFactor(
        StartDateLib
        ,
         EndDateLib
        ,
         RefPeriodStartLib
        ,
         RefPeriodEndLib
       );


  mReturnValue = returnValue;

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::InterestRateCompoundFactor) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  ObjectHandler::property_t StartDateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[1]).FromJust()));

  // convert js argument to c++ type
  ObjectHandler::property_t EndDateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[2]).FromJust()));

  // convert js argument to c++ type
  ObjectHandler::property_t RefPeriodStartCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[3]).FromJust()));

  // convert js argument to c++ type
  ObjectHandler::property_t RefPeriodEndCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[4]).FromJust()));

 
  // launch worker
  InterestRateCompoundFactorWorker* worker = new InterestRateCompoundFactorWorker(
    ObjectIDCpp
,     StartDateCpp
,     EndDateCpp
,     RefPeriodStartCpp
,     RefPeriodEndCpp
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

void InterestRateEquivalentRateWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::InterestRate, QuantLib::InterestRate)


  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::DayCounter DayCounterEnum =
      ObjectHandler::Create<QuantLib::DayCounter>()(mDayCounter);


  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::Compounding CompoundingEnum =
      ObjectHandler::Create<QuantLib::Compounding>()(mCompounding);


  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::Frequency FrequencyEnum =
      ObjectHandler::Create<QuantLib::Frequency>()(mFrequency);


  // convert input datatypes to QuantLib datatypes
  QuantLib::Date StartDateLib = ObjectHandler::convert2<QuantLib::Date>(
      mStartDate, "StartDate");


  // convert input datatypes to QuantLib datatypes
  QuantLib::Date EndDateLib = ObjectHandler::convert2<QuantLib::Date>(
      mEndDate, "EndDate");


  // convert input datatypes to QuantLib datatypes
  QuantLib::Date RefPeriodStartLib = ObjectHandler::convert2<QuantLib::Date>(
      mRefPeriodStart, "RefPeriodStart");


  // convert input datatypes to QuantLib datatypes
  QuantLib::Date RefPeriodEndLib = ObjectHandler::convert2<QuantLib::Date>(
      mRefPeriodEnd, "RefPeriodEnd");

     
  // invoke the member function
  QuantLib::Real returnValue = ObjectIDLibObjPtr->equivalentRate(
        DayCounterEnum
        ,
         CompoundingEnum
        ,
         FrequencyEnum
        ,
         StartDateLib
        ,
         EndDateLib
        ,
         RefPeriodStartLib
        ,
         RefPeriodEndLib
       );


  mReturnValue = returnValue;

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::InterestRateEquivalentRate) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsString()) {
      return Nan::ThrowError("DayCounter is required.");
  }
  if (info.Length() == 2 || !info[2]->IsString()) {
      return Nan::ThrowError("Compounding is required.");
  }
  if (info.Length() == 3 || !info[3]->IsString()) {
      return Nan::ThrowError("Frequency is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  String::Utf8Value strDayCounter(info[1]->ToString());
  string DayCounterCpp(strdup(*strDayCounter));

  // convert js argument to c++ type
  String::Utf8Value strCompounding(info[2]->ToString());
  string CompoundingCpp(strdup(*strCompounding));

  // convert js argument to c++ type
  String::Utf8Value strFrequency(info[3]->ToString());
  string FrequencyCpp(strdup(*strFrequency));

  // convert js argument to c++ type
  ObjectHandler::property_t StartDateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[4]).FromJust()));

  // convert js argument to c++ type
  ObjectHandler::property_t EndDateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[5]).FromJust()));

  // convert js argument to c++ type
  ObjectHandler::property_t RefPeriodStartCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[6]).FromJust()));

  // convert js argument to c++ type
  ObjectHandler::property_t RefPeriodEndCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[7]).FromJust()));

 
  // launch worker
  InterestRateEquivalentRateWorker* worker = new InterestRateEquivalentRateWorker(
    ObjectIDCpp
,     DayCounterCpp
,     CompoundingCpp
,     FrequencyCpp
,     StartDateCpp
,     EndDateCpp
,     RefPeriodStartCpp
,     RefPeriodEndCpp
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

void LegStartDateWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_UNDERLYING(ObjectIdLibObj, mObjectId,
      QuantLibAddin::Leg, QuantLib::Leg)

       // invoke the utility function
  QuantLib::Date returnValue = QuantLib::CashFlows::startDate(
      ObjectIdLibObj
     );

  mReturnValue = QuantLibAddin::libraryToScalar(returnValue);

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::LegStartDate) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectId is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectId(info[0]->ToString());
  string ObjectIdCpp(strdup(*strObjectId));

 
  // launch worker
  LegStartDateWorker* worker = new LegStartDateWorker(
    ObjectIdCpp
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

void LegMaturityDateWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_UNDERLYING(ObjectIdLibObj, mObjectId,
      QuantLibAddin::Leg, QuantLib::Leg)

       // invoke the utility function
  QuantLib::Date returnValue = QuantLib::CashFlows::maturityDate(
      ObjectIdLibObj
     );

  mReturnValue = QuantLibAddin::libraryToScalar(returnValue);

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::LegMaturityDate) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectId is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectId(info[0]->ToString());
  string ObjectIdCpp(strdup(*strObjectId));

 
  // launch worker
  LegMaturityDateWorker* worker = new LegMaturityDateWorker(
    ObjectIdCpp
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

void LegIsExpiredWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_UNDERLYING(ObjectIdLibObj, mObjectId,
      QuantLibAddin::Leg, QuantLib::Leg)


  // convert input datatypes to QuantLib datatypes
  QuantLib::Date SettlementDateLib = ObjectHandler::convert2<QuantLib::Date>(
      mSettlementDate, "SettlementDate");

       // invoke the utility function
  mReturnValue = QuantLib::CashFlows::isExpired(
      ObjectIdLibObj
      ,
       mIncludeSettlDate
      ,
       SettlementDateLib
     );
   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::LegIsExpired) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectId is required.");
  }
  if (info.Length() == 1 || !info[1]->IsBoolean()) {
      return Nan::ThrowError("IncludeSettlDate is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectId(info[0]->ToString());
  string ObjectIdCpp(strdup(*strObjectId));

  // convert js argument to c++ type
  bool IncludeSettlDateCpp = Nan::To<bool>(info[1]).FromJust();

  // convert js argument to c++ type
  ObjectHandler::property_t SettlementDateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[2]).FromJust()));

 
  // launch worker
  LegIsExpiredWorker* worker = new LegIsExpiredWorker(
    ObjectIdCpp
,     IncludeSettlDateCpp
,     SettlementDateCpp
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

void LegPreviousCashFlowDateWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_UNDERLYING(ObjectIdLibObj, mObjectId,
      QuantLibAddin::Leg, QuantLib::Leg)


  // convert input datatypes to QuantLib datatypes
  QuantLib::Date SettlementDateLib = ObjectHandler::convert2<QuantLib::Date>(
      mSettlementDate, "SettlementDate");

       // invoke the utility function
  QuantLib::Date returnValue = QuantLib::CashFlows::previousCashFlowDate(
      ObjectIdLibObj
      ,
       mIncludeSettlDate
      ,
       SettlementDateLib
     );

  mReturnValue = QuantLibAddin::libraryToScalar(returnValue);

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::LegPreviousCashFlowDate) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectId is required.");
  }
  if (info.Length() == 1 || !info[1]->IsBoolean()) {
      return Nan::ThrowError("IncludeSettlDate is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectId(info[0]->ToString());
  string ObjectIdCpp(strdup(*strObjectId));

  // convert js argument to c++ type
  bool IncludeSettlDateCpp = Nan::To<bool>(info[1]).FromJust();

  // convert js argument to c++ type
  ObjectHandler::property_t SettlementDateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[2]).FromJust()));

 
  // launch worker
  LegPreviousCashFlowDateWorker* worker = new LegPreviousCashFlowDateWorker(
    ObjectIdCpp
,     IncludeSettlDateCpp
,     SettlementDateCpp
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

void LegNextCashFlowDateWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_UNDERLYING(ObjectIdLibObj, mObjectId,
      QuantLibAddin::Leg, QuantLib::Leg)


  // convert input datatypes to QuantLib datatypes
  QuantLib::Date SettlementDateLib = ObjectHandler::convert2<QuantLib::Date>(
      mSettlementDate, "SettlementDate");

       // invoke the utility function
  QuantLib::Date returnValue = QuantLib::CashFlows::nextCashFlowDate(
      ObjectIdLibObj
      ,
       mIncludeSettlDate
      ,
       SettlementDateLib
     );

  mReturnValue = QuantLibAddin::libraryToScalar(returnValue);

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::LegNextCashFlowDate) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectId is required.");
  }
  if (info.Length() == 1 || !info[1]->IsBoolean()) {
      return Nan::ThrowError("IncludeSettlDate is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectId(info[0]->ToString());
  string ObjectIdCpp(strdup(*strObjectId));

  // convert js argument to c++ type
  bool IncludeSettlDateCpp = Nan::To<bool>(info[1]).FromJust();

  // convert js argument to c++ type
  ObjectHandler::property_t SettlementDateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[2]).FromJust()));

 
  // launch worker
  LegNextCashFlowDateWorker* worker = new LegNextCashFlowDateWorker(
    ObjectIdCpp
,     IncludeSettlDateCpp
,     SettlementDateCpp
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

void LegPreviousCashFlowAmountWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_UNDERLYING(ObjectIdLibObj, mObjectId,
      QuantLibAddin::Leg, QuantLib::Leg)


  // convert input datatypes to QuantLib datatypes
  QuantLib::Date SettlementDateLib = ObjectHandler::convert2<QuantLib::Date>(
      mSettlementDate, "SettlementDate");

       // invoke the utility function
  QuantLib::Real returnValue = QuantLib::CashFlows::previousCashFlowAmount(
      ObjectIdLibObj
      ,
       mIncludeSettlDate
      ,
       SettlementDateLib
     );

  mReturnValue = returnValue;

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::LegPreviousCashFlowAmount) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectId is required.");
  }
  if (info.Length() == 1 || !info[1]->IsBoolean()) {
      return Nan::ThrowError("IncludeSettlDate is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectId(info[0]->ToString());
  string ObjectIdCpp(strdup(*strObjectId));

  // convert js argument to c++ type
  bool IncludeSettlDateCpp = Nan::To<bool>(info[1]).FromJust();

  // convert js argument to c++ type
  ObjectHandler::property_t SettlementDateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[2]).FromJust()));

 
  // launch worker
  LegPreviousCashFlowAmountWorker* worker = new LegPreviousCashFlowAmountWorker(
    ObjectIdCpp
,     IncludeSettlDateCpp
,     SettlementDateCpp
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

void LegNextCashFlowAmountWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_UNDERLYING(ObjectIdLibObj, mObjectId,
      QuantLibAddin::Leg, QuantLib::Leg)


  // convert input datatypes to QuantLib datatypes
  QuantLib::Date SettlementDateLib = ObjectHandler::convert2<QuantLib::Date>(
      mSettlementDate, "SettlementDate");

       // invoke the utility function
  QuantLib::Real returnValue = QuantLib::CashFlows::nextCashFlowAmount(
      ObjectIdLibObj
      ,
       mIncludeSettlDate
      ,
       SettlementDateLib
     );

  mReturnValue = returnValue;

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::LegNextCashFlowAmount) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectId is required.");
  }
  if (info.Length() == 1 || !info[1]->IsBoolean()) {
      return Nan::ThrowError("IncludeSettlDate is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectId(info[0]->ToString());
  string ObjectIdCpp(strdup(*strObjectId));

  // convert js argument to c++ type
  bool IncludeSettlDateCpp = Nan::To<bool>(info[1]).FromJust();

  // convert js argument to c++ type
  ObjectHandler::property_t SettlementDateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[2]).FromJust()));

 
  // launch worker
  LegNextCashFlowAmountWorker* worker = new LegNextCashFlowAmountWorker(
    ObjectIdCpp
,     IncludeSettlDateCpp
,     SettlementDateCpp
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

void LegPreviousCouponRateWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_UNDERLYING(ObjectIdLibObj, mObjectId,
      QuantLibAddin::Leg, QuantLib::Leg)


  // convert input datatypes to QuantLib datatypes
  QuantLib::Date SettlementDateLib = ObjectHandler::convert2<QuantLib::Date>(
      mSettlementDate, "SettlementDate");

       // invoke the utility function
  mReturnValue = QuantLib::CashFlows::previousCouponRate(
      ObjectIdLibObj
      ,
       mIncludeSettlDate
      ,
       SettlementDateLib
     );
   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::LegPreviousCouponRate) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectId is required.");
  }
  if (info.Length() == 1 || !info[1]->IsBoolean()) {
      return Nan::ThrowError("IncludeSettlDate is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectId(info[0]->ToString());
  string ObjectIdCpp(strdup(*strObjectId));

  // convert js argument to c++ type
  bool IncludeSettlDateCpp = Nan::To<bool>(info[1]).FromJust();

  // convert js argument to c++ type
  ObjectHandler::property_t SettlementDateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[2]).FromJust()));

 
  // launch worker
  LegPreviousCouponRateWorker* worker = new LegPreviousCouponRateWorker(
    ObjectIdCpp
,     IncludeSettlDateCpp
,     SettlementDateCpp
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

void LegNextCouponRateWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_UNDERLYING(ObjectIdLibObj, mObjectId,
      QuantLibAddin::Leg, QuantLib::Leg)


  // convert input datatypes to QuantLib datatypes
  QuantLib::Date SettlementDateLib = ObjectHandler::convert2<QuantLib::Date>(
      mSettlementDate, "SettlementDate");

       // invoke the utility function
  mReturnValue = QuantLib::CashFlows::nextCouponRate(
      ObjectIdLibObj
      ,
       mIncludeSettlDate
      ,
       SettlementDateLib
     );
   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::LegNextCouponRate) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectId is required.");
  }
  if (info.Length() == 1 || !info[1]->IsBoolean()) {
      return Nan::ThrowError("IncludeSettlDate is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectId(info[0]->ToString());
  string ObjectIdCpp(strdup(*strObjectId));

  // convert js argument to c++ type
  bool IncludeSettlDateCpp = Nan::To<bool>(info[1]).FromJust();

  // convert js argument to c++ type
  ObjectHandler::property_t SettlementDateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[2]).FromJust()));

 
  // launch worker
  LegNextCouponRateWorker* worker = new LegNextCouponRateWorker(
    ObjectIdCpp
,     IncludeSettlDateCpp
,     SettlementDateCpp
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

void LegNominalWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_UNDERLYING(ObjectIdLibObj, mObjectId,
      QuantLibAddin::Leg, QuantLib::Leg)


  // convert input datatypes to QuantLib datatypes
  QuantLib::Date SettlementDateLib = ObjectHandler::convert2<QuantLib::Date>(
      mSettlementDate, "SettlementDate");

       // invoke the utility function
  QuantLib::Real returnValue = QuantLib::CashFlows::nominal(
      ObjectIdLibObj
      ,
       mIncludeSettlDate
      ,
       SettlementDateLib
     );

  mReturnValue = returnValue;

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::LegNominal) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectId is required.");
  }
  if (info.Length() == 1 || !info[1]->IsBoolean()) {
      return Nan::ThrowError("IncludeSettlDate is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectId(info[0]->ToString());
  string ObjectIdCpp(strdup(*strObjectId));

  // convert js argument to c++ type
  bool IncludeSettlDateCpp = Nan::To<bool>(info[1]).FromJust();

  // convert js argument to c++ type
  ObjectHandler::property_t SettlementDateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[2]).FromJust()));

 
  // launch worker
  LegNominalWorker* worker = new LegNominalWorker(
    ObjectIdCpp
,     IncludeSettlDateCpp
,     SettlementDateCpp
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

void LegAccrualStartDateWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_UNDERLYING(ObjectIdLibObj, mObjectId,
      QuantLibAddin::Leg, QuantLib::Leg)


  // convert input datatypes to QuantLib datatypes
  QuantLib::Date SettlementDateLib = ObjectHandler::convert2<QuantLib::Date>(
      mSettlementDate, "SettlementDate");

       // invoke the utility function
  QuantLib::Date returnValue = QuantLib::CashFlows::accrualStartDate(
      ObjectIdLibObj
      ,
       mIncludeSettlDate
      ,
       SettlementDateLib
     );

  mReturnValue = QuantLibAddin::libraryToScalar(returnValue);

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::LegAccrualStartDate) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectId is required.");
  }
  if (info.Length() == 1 || !info[1]->IsBoolean()) {
      return Nan::ThrowError("IncludeSettlDate is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectId(info[0]->ToString());
  string ObjectIdCpp(strdup(*strObjectId));

  // convert js argument to c++ type
  bool IncludeSettlDateCpp = Nan::To<bool>(info[1]).FromJust();

  // convert js argument to c++ type
  ObjectHandler::property_t SettlementDateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[2]).FromJust()));

 
  // launch worker
  LegAccrualStartDateWorker* worker = new LegAccrualStartDateWorker(
    ObjectIdCpp
,     IncludeSettlDateCpp
,     SettlementDateCpp
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

void LegAccrualEndDateWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_UNDERLYING(ObjectIdLibObj, mObjectId,
      QuantLibAddin::Leg, QuantLib::Leg)


  // convert input datatypes to QuantLib datatypes
  QuantLib::Date SettlementDateLib = ObjectHandler::convert2<QuantLib::Date>(
      mSettlementDate, "SettlementDate");

       // invoke the utility function
  QuantLib::Date returnValue = QuantLib::CashFlows::accrualEndDate(
      ObjectIdLibObj
      ,
       mIncludeSettlDate
      ,
       SettlementDateLib
     );

  mReturnValue = QuantLibAddin::libraryToScalar(returnValue);

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::LegAccrualEndDate) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectId is required.");
  }
  if (info.Length() == 1 || !info[1]->IsBoolean()) {
      return Nan::ThrowError("IncludeSettlDate is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectId(info[0]->ToString());
  string ObjectIdCpp(strdup(*strObjectId));

  // convert js argument to c++ type
  bool IncludeSettlDateCpp = Nan::To<bool>(info[1]).FromJust();

  // convert js argument to c++ type
  ObjectHandler::property_t SettlementDateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[2]).FromJust()));

 
  // launch worker
  LegAccrualEndDateWorker* worker = new LegAccrualEndDateWorker(
    ObjectIdCpp
,     IncludeSettlDateCpp
,     SettlementDateCpp
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

void LegReferencePeriodStartWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_UNDERLYING(ObjectIdLibObj, mObjectId,
      QuantLibAddin::Leg, QuantLib::Leg)


  // convert input datatypes to QuantLib datatypes
  QuantLib::Date SettlementDateLib = ObjectHandler::convert2<QuantLib::Date>(
      mSettlementDate, "SettlementDate");

       // invoke the utility function
  QuantLib::Date returnValue = QuantLib::CashFlows::referencePeriodStart(
      ObjectIdLibObj
      ,
       mIncludeSettlDate
      ,
       SettlementDateLib
     );

  mReturnValue = QuantLibAddin::libraryToScalar(returnValue);

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::LegReferencePeriodStart) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectId is required.");
  }
  if (info.Length() == 1 || !info[1]->IsBoolean()) {
      return Nan::ThrowError("IncludeSettlDate is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectId(info[0]->ToString());
  string ObjectIdCpp(strdup(*strObjectId));

  // convert js argument to c++ type
  bool IncludeSettlDateCpp = Nan::To<bool>(info[1]).FromJust();

  // convert js argument to c++ type
  ObjectHandler::property_t SettlementDateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[2]).FromJust()));

 
  // launch worker
  LegReferencePeriodStartWorker* worker = new LegReferencePeriodStartWorker(
    ObjectIdCpp
,     IncludeSettlDateCpp
,     SettlementDateCpp
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

void LegReferencePeriodEndWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_UNDERLYING(ObjectIdLibObj, mObjectId,
      QuantLibAddin::Leg, QuantLib::Leg)


  // convert input datatypes to QuantLib datatypes
  QuantLib::Date SettlementDateLib = ObjectHandler::convert2<QuantLib::Date>(
      mSettlementDate, "SettlementDate");

       // invoke the utility function
  QuantLib::Date returnValue = QuantLib::CashFlows::referencePeriodEnd(
      ObjectIdLibObj
      ,
       mIncludeSettlDate
      ,
       SettlementDateLib
     );

  mReturnValue = QuantLibAddin::libraryToScalar(returnValue);

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::LegReferencePeriodEnd) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectId is required.");
  }
  if (info.Length() == 1 || !info[1]->IsBoolean()) {
      return Nan::ThrowError("IncludeSettlDate is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectId(info[0]->ToString());
  string ObjectIdCpp(strdup(*strObjectId));

  // convert js argument to c++ type
  bool IncludeSettlDateCpp = Nan::To<bool>(info[1]).FromJust();

  // convert js argument to c++ type
  ObjectHandler::property_t SettlementDateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[2]).FromJust()));

 
  // launch worker
  LegReferencePeriodEndWorker* worker = new LegReferencePeriodEndWorker(
    ObjectIdCpp
,     IncludeSettlDateCpp
,     SettlementDateCpp
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

void LegAccrualPeriodWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_UNDERLYING(ObjectIdLibObj, mObjectId,
      QuantLibAddin::Leg, QuantLib::Leg)


  // convert input datatypes to QuantLib datatypes
  QuantLib::Date SettlementDateLib = ObjectHandler::convert2<QuantLib::Date>(
      mSettlementDate, "SettlementDate");

       // invoke the utility function
  mReturnValue = QuantLib::CashFlows::accrualPeriod(
      ObjectIdLibObj
      ,
       mIncludeSettlDate
      ,
       SettlementDateLib
     );
   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::LegAccrualPeriod) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectId is required.");
  }
  if (info.Length() == 1 || !info[1]->IsBoolean()) {
      return Nan::ThrowError("IncludeSettlDate is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectId(info[0]->ToString());
  string ObjectIdCpp(strdup(*strObjectId));

  // convert js argument to c++ type
  bool IncludeSettlDateCpp = Nan::To<bool>(info[1]).FromJust();

  // convert js argument to c++ type
  ObjectHandler::property_t SettlementDateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[2]).FromJust()));

 
  // launch worker
  LegAccrualPeriodWorker* worker = new LegAccrualPeriodWorker(
    ObjectIdCpp
,     IncludeSettlDateCpp
,     SettlementDateCpp
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

void LegAccrualDaysWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_UNDERLYING(ObjectIdLibObj, mObjectId,
      QuantLibAddin::Leg, QuantLib::Leg)


  // convert input datatypes to QuantLib datatypes
  QuantLib::Date SettlementDateLib = ObjectHandler::convert2<QuantLib::Date>(
      mSettlementDate, "SettlementDate");

       // invoke the utility function
  mReturnValue = QuantLib::CashFlows::accrualDays(
      ObjectIdLibObj
      ,
       mIncludeSettlDate
      ,
       SettlementDateLib
     );
   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::LegAccrualDays) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectId is required.");
  }
  if (info.Length() == 1 || !info[1]->IsBoolean()) {
      return Nan::ThrowError("IncludeSettlDate is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectId(info[0]->ToString());
  string ObjectIdCpp(strdup(*strObjectId));

  // convert js argument to c++ type
  bool IncludeSettlDateCpp = Nan::To<bool>(info[1]).FromJust();

  // convert js argument to c++ type
  ObjectHandler::property_t SettlementDateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[2]).FromJust()));

 
  // launch worker
  LegAccrualDaysWorker* worker = new LegAccrualDaysWorker(
    ObjectIdCpp
,     IncludeSettlDateCpp
,     SettlementDateCpp
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

void LegAccruedPeriodWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_UNDERLYING(ObjectIdLibObj, mObjectId,
      QuantLibAddin::Leg, QuantLib::Leg)


  // convert input datatypes to QuantLib datatypes
  QuantLib::Date SettlementDateLib = ObjectHandler::convert2<QuantLib::Date>(
      mSettlementDate, "SettlementDate");

       // invoke the utility function
  mReturnValue = QuantLib::CashFlows::accrualPeriod(
      ObjectIdLibObj
      ,
       mIncludeSettlDate
      ,
       SettlementDateLib
     );
   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::LegAccruedPeriod) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectId is required.");
  }
  if (info.Length() == 1 || !info[1]->IsBoolean()) {
      return Nan::ThrowError("IncludeSettlDate is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectId(info[0]->ToString());
  string ObjectIdCpp(strdup(*strObjectId));

  // convert js argument to c++ type
  bool IncludeSettlDateCpp = Nan::To<bool>(info[1]).FromJust();

  // convert js argument to c++ type
  ObjectHandler::property_t SettlementDateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[2]).FromJust()));

 
  // launch worker
  LegAccruedPeriodWorker* worker = new LegAccruedPeriodWorker(
    ObjectIdCpp
,     IncludeSettlDateCpp
,     SettlementDateCpp
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

void LegAccruedDaysWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_UNDERLYING(ObjectIdLibObj, mObjectId,
      QuantLibAddin::Leg, QuantLib::Leg)


  // convert input datatypes to QuantLib datatypes
  QuantLib::Date SettlementDateLib = ObjectHandler::convert2<QuantLib::Date>(
      mSettlementDate, "SettlementDate");

       // invoke the utility function
  mReturnValue = QuantLib::CashFlows::accrualDays(
      ObjectIdLibObj
      ,
       mIncludeSettlDate
      ,
       SettlementDateLib
     );
   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::LegAccruedDays) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectId is required.");
  }
  if (info.Length() == 1 || !info[1]->IsBoolean()) {
      return Nan::ThrowError("IncludeSettlDate is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectId(info[0]->ToString());
  string ObjectIdCpp(strdup(*strObjectId));

  // convert js argument to c++ type
  bool IncludeSettlDateCpp = Nan::To<bool>(info[1]).FromJust();

  // convert js argument to c++ type
  ObjectHandler::property_t SettlementDateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[2]).FromJust()));

 
  // launch worker
  LegAccruedDaysWorker* worker = new LegAccruedDaysWorker(
    ObjectIdCpp
,     IncludeSettlDateCpp
,     SettlementDateCpp
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

void LegAccruedAmountWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_UNDERLYING(ObjectIdLibObj, mObjectId,
      QuantLibAddin::Leg, QuantLib::Leg)


  // convert input datatypes to QuantLib datatypes
  QuantLib::Date SettlementDateLib = ObjectHandler::convert2<QuantLib::Date>(
      mSettlementDate, "SettlementDate");

       // invoke the utility function
  QuantLib::Real returnValue = QuantLib::CashFlows::accruedAmount(
      ObjectIdLibObj
      ,
       mIncludeSettlDate
      ,
       SettlementDateLib
     );

  mReturnValue = returnValue;

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::LegAccruedAmount) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectId is required.");
  }
  if (info.Length() == 1 || !info[1]->IsBoolean()) {
      return Nan::ThrowError("IncludeSettlDate is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectId(info[0]->ToString());
  string ObjectIdCpp(strdup(*strObjectId));

  // convert js argument to c++ type
  bool IncludeSettlDateCpp = Nan::To<bool>(info[1]).FromJust();

  // convert js argument to c++ type
  ObjectHandler::property_t SettlementDateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[2]).FromJust()));

 
  // launch worker
  LegAccruedAmountWorker* worker = new LegAccruedAmountWorker(
    ObjectIdCpp
,     IncludeSettlDateCpp
,     SettlementDateCpp
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

void LegNPVWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_UNDERLYING(ObjectIdLibObj, mObjectId,
      QuantLibAddin::Leg, QuantLib::Leg)


  // convert object IDs into library objects
  OH_GET_UNDERLYING(DiscountCurveLibObj, mDiscountCurve,
      QuantLibAddin::YieldTermStructure, QuantLib::YieldTermStructure)


  // convert input datatypes to QuantLib datatypes
  QuantLib::Date SettlementDateLib = ObjectHandler::convert2<QuantLib::Date>(
      mSettlementDate, "SettlementDate");


  // convert input datatypes to QuantLib datatypes
  QuantLib::Date NpvDateLib = ObjectHandler::convert2<QuantLib::Date>(
      mNpvDate, "NpvDate");

       // invoke the utility function
  mReturnValue = QuantLib::CashFlows::npv(
      ObjectIdLibObj
      ,
       DiscountCurveLibObj
      ,
       mIncludeSettlDate
      ,
       SettlementDateLib
      ,
       NpvDateLib
     );
   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::LegNPV) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectId is required.");
  }
  if (info.Length() == 1 || !info[1]->IsString()) {
      return Nan::ThrowError("DiscountCurve is required.");
  }
  if (info.Length() == 2 || !info[2]->IsBoolean()) {
      return Nan::ThrowError("IncludeSettlDate is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectId(info[0]->ToString());
  string ObjectIdCpp(strdup(*strObjectId));

  // convert js argument to c++ type
  String::Utf8Value strDiscountCurve(info[1]->ToString());
  string DiscountCurveCpp(strdup(*strDiscountCurve));

  // convert js argument to c++ type
  bool IncludeSettlDateCpp = Nan::To<bool>(info[2]).FromJust();

  // convert js argument to c++ type
  ObjectHandler::property_t SettlementDateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[3]).FromJust()));

  // convert js argument to c++ type
  ObjectHandler::property_t NpvDateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[4]).FromJust()));

 
  // launch worker
  LegNPVWorker* worker = new LegNPVWorker(
    ObjectIdCpp
,     DiscountCurveCpp
,     IncludeSettlDateCpp
,     SettlementDateCpp
,     NpvDateCpp
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

void LegBPSWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_UNDERLYING(ObjectIdLibObj, mObjectId,
      QuantLibAddin::Leg, QuantLib::Leg)


  // convert object IDs into library objects
  OH_GET_UNDERLYING(DiscountCurveLibObj, mDiscountCurve,
      QuantLibAddin::YieldTermStructure, QuantLib::YieldTermStructure)


  // convert input datatypes to QuantLib datatypes
  QuantLib::Date SettlementDateLib = ObjectHandler::convert2<QuantLib::Date>(
      mSettlementDate, "SettlementDate");


  // convert input datatypes to QuantLib datatypes
  QuantLib::Date NpvDateLib = ObjectHandler::convert2<QuantLib::Date>(
      mNpvDate, "NpvDate");

       // invoke the utility function
  mReturnValue = QuantLib::CashFlows::bps(
      ObjectIdLibObj
      ,
       DiscountCurveLibObj
      ,
       mIncludeSettlDate
      ,
       SettlementDateLib
      ,
       NpvDateLib
     );
   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::LegBPS) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectId is required.");
  }
  if (info.Length() == 1 || !info[1]->IsString()) {
      return Nan::ThrowError("DiscountCurve is required.");
  }
  if (info.Length() == 2 || !info[2]->IsBoolean()) {
      return Nan::ThrowError("IncludeSettlDate is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectId(info[0]->ToString());
  string ObjectIdCpp(strdup(*strObjectId));

  // convert js argument to c++ type
  String::Utf8Value strDiscountCurve(info[1]->ToString());
  string DiscountCurveCpp(strdup(*strDiscountCurve));

  // convert js argument to c++ type
  bool IncludeSettlDateCpp = Nan::To<bool>(info[2]).FromJust();

  // convert js argument to c++ type
  ObjectHandler::property_t SettlementDateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[3]).FromJust()));

  // convert js argument to c++ type
  ObjectHandler::property_t NpvDateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[4]).FromJust()));

 
  // launch worker
  LegBPSWorker* worker = new LegBPSWorker(
    ObjectIdCpp
,     DiscountCurveCpp
,     IncludeSettlDateCpp
,     SettlementDateCpp
,     NpvDateCpp
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

void LegAtmRateWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_UNDERLYING(ObjectIdLibObj, mObjectId,
      QuantLibAddin::Leg, QuantLib::Leg)


  // convert object IDs into library objects
  OH_GET_UNDERLYING(DiscountCurveLibObj, mDiscountCurve,
      QuantLibAddin::YieldTermStructure, QuantLib::YieldTermStructure)


  // convert input datatypes to QuantLib datatypes
  QuantLib::Date SettlementDateLib = ObjectHandler::convert2<QuantLib::Date>(
      mSettlementDate, "SettlementDate");


  // convert input datatypes to QuantLib datatypes
  QuantLib::Date NpvDateLib = ObjectHandler::convert2<QuantLib::Date>(
      mNpvDate, "NpvDate");


  // convert input datatypes to QuantLib datatypes
       // invoke the utility function
  mReturnValue = QuantLib::CashFlows::atmRate(
      ObjectIdLibObj
      ,
       DiscountCurveLibObj
      ,
       mIncludeSettlDate
      ,
       SettlementDateLib
      ,
       NpvDateLib
      ,
       mNPV
     );
   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::LegAtmRate) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectId is required.");
  }
  if (info.Length() == 1 || !info[1]->IsString()) {
      return Nan::ThrowError("DiscountCurve is required.");
  }
  if (info.Length() == 2 || !info[2]->IsBoolean()) {
      return Nan::ThrowError("IncludeSettlDate is required.");
  }
  if (info.Length() == 5 || !info[5]->IsNumber()) {
      return Nan::ThrowError("NPV is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectId(info[0]->ToString());
  string ObjectIdCpp(strdup(*strObjectId));

  // convert js argument to c++ type
  String::Utf8Value strDiscountCurve(info[1]->ToString());
  string DiscountCurveCpp(strdup(*strDiscountCurve));

  // convert js argument to c++ type
  bool IncludeSettlDateCpp = Nan::To<bool>(info[2]).FromJust();

  // convert js argument to c++ type
  ObjectHandler::property_t SettlementDateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[3]).FromJust()));

  // convert js argument to c++ type
  ObjectHandler::property_t NpvDateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[4]).FromJust()));

  // convert js argument to c++ type
  double NPVCpp = Nan::To<double>(info[5]).FromJust();

 
  // launch worker
  LegAtmRateWorker* worker = new LegAtmRateWorker(
    ObjectIdCpp
,     DiscountCurveCpp
,     IncludeSettlDateCpp
,     SettlementDateCpp
,     NpvDateCpp
,     NPVCpp
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

void LegNPVFromYieldWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_UNDERLYING(ObjectIdLibObj, mObjectId,
      QuantLibAddin::Leg, QuantLib::Leg)


  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::DayCounter DayCounterEnum =
      ObjectHandler::Create<QuantLib::DayCounter>()(mDayCounter);


  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::Compounding CompoundingEnum =
      ObjectHandler::Create<QuantLib::Compounding>()(mCompounding);


  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::Frequency FrequencyEnum =
      ObjectHandler::Create<QuantLib::Frequency>()(mFrequency);


  // convert input datatypes to QuantLib datatypes
  QuantLib::Date SettlementDateLib = ObjectHandler::convert2<QuantLib::Date>(
      mSettlementDate, "SettlementDate");


  // convert input datatypes to QuantLib datatypes
  QuantLib::Date NpvDateLib = ObjectHandler::convert2<QuantLib::Date>(
      mNpvDate, "NpvDate");

       // invoke the utility function
  QuantLib::Real returnValue = QuantLib::CashFlows::npv(
      ObjectIdLibObj
      ,
       mYield
      ,
       DayCounterEnum
      ,
       CompoundingEnum
      ,
       FrequencyEnum
      ,
       mIncludeSettlDate
      ,
       SettlementDateLib
      ,
       NpvDateLib
     );

  mReturnValue = returnValue;

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::LegNPVFromYield) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectId is required.");
  }
  if (info.Length() == 1 || !info[1]->IsNumber()) {
      return Nan::ThrowError("Yield is required.");
  }
  if (info.Length() == 2 || !info[2]->IsString()) {
      return Nan::ThrowError("DayCounter is required.");
  }
  if (info.Length() == 3 || !info[3]->IsString()) {
      return Nan::ThrowError("Compounding is required.");
  }
  if (info.Length() == 4 || !info[4]->IsString()) {
      return Nan::ThrowError("Frequency is required.");
  }
  if (info.Length() == 5 || !info[5]->IsBoolean()) {
      return Nan::ThrowError("IncludeSettlDate is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectId(info[0]->ToString());
  string ObjectIdCpp(strdup(*strObjectId));

  // convert js argument to c++ type
  double YieldCpp = Nan::To<double>(info[1]).FromJust();

  // convert js argument to c++ type
  String::Utf8Value strDayCounter(info[2]->ToString());
  string DayCounterCpp(strdup(*strDayCounter));

  // convert js argument to c++ type
  String::Utf8Value strCompounding(info[3]->ToString());
  string CompoundingCpp(strdup(*strCompounding));

  // convert js argument to c++ type
  String::Utf8Value strFrequency(info[4]->ToString());
  string FrequencyCpp(strdup(*strFrequency));

  // convert js argument to c++ type
  bool IncludeSettlDateCpp = Nan::To<bool>(info[5]).FromJust();

  // convert js argument to c++ type
  ObjectHandler::property_t SettlementDateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[6]).FromJust()));

  // convert js argument to c++ type
  ObjectHandler::property_t NpvDateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[7]).FromJust()));

 
  // launch worker
  LegNPVFromYieldWorker* worker = new LegNPVFromYieldWorker(
    ObjectIdCpp
,     YieldCpp
,     DayCounterCpp
,     CompoundingCpp
,     FrequencyCpp
,     IncludeSettlDateCpp
,     SettlementDateCpp
,     NpvDateCpp
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

void LegBPSFromYieldWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_UNDERLYING(ObjectIdLibObj, mObjectId,
      QuantLibAddin::Leg, QuantLib::Leg)


  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::DayCounter DayCounterEnum =
      ObjectHandler::Create<QuantLib::DayCounter>()(mDayCounter);


  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::Compounding CompoundingEnum =
      ObjectHandler::Create<QuantLib::Compounding>()(mCompounding);


  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::Frequency FrequencyEnum =
      ObjectHandler::Create<QuantLib::Frequency>()(mFrequency);


  // convert input datatypes to QuantLib datatypes
  QuantLib::Date SettlementDateLib = ObjectHandler::convert2<QuantLib::Date>(
      mSettlementDate, "SettlementDate");


  // convert input datatypes to QuantLib datatypes
  QuantLib::Date NpvDateLib = ObjectHandler::convert2<QuantLib::Date>(
      mNpvDate, "NpvDate");

       // invoke the utility function
  mReturnValue = QuantLib::CashFlows::bps(
      ObjectIdLibObj
      ,
       mYield
      ,
       DayCounterEnum
      ,
       CompoundingEnum
      ,
       FrequencyEnum
      ,
       mIncludeSettlDate
      ,
       SettlementDateLib
      ,
       NpvDateLib
     );
   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::LegBPSFromYield) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectId is required.");
  }
  if (info.Length() == 1 || !info[1]->IsNumber()) {
      return Nan::ThrowError("Yield is required.");
  }
  if (info.Length() == 2 || !info[2]->IsString()) {
      return Nan::ThrowError("DayCounter is required.");
  }
  if (info.Length() == 3 || !info[3]->IsString()) {
      return Nan::ThrowError("Compounding is required.");
  }
  if (info.Length() == 4 || !info[4]->IsString()) {
      return Nan::ThrowError("Frequency is required.");
  }
  if (info.Length() == 5 || !info[5]->IsBoolean()) {
      return Nan::ThrowError("IncludeSettlDate is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectId(info[0]->ToString());
  string ObjectIdCpp(strdup(*strObjectId));

  // convert js argument to c++ type
  double YieldCpp = Nan::To<double>(info[1]).FromJust();

  // convert js argument to c++ type
  String::Utf8Value strDayCounter(info[2]->ToString());
  string DayCounterCpp(strdup(*strDayCounter));

  // convert js argument to c++ type
  String::Utf8Value strCompounding(info[3]->ToString());
  string CompoundingCpp(strdup(*strCompounding));

  // convert js argument to c++ type
  String::Utf8Value strFrequency(info[4]->ToString());
  string FrequencyCpp(strdup(*strFrequency));

  // convert js argument to c++ type
  bool IncludeSettlDateCpp = Nan::To<bool>(info[5]).FromJust();

  // convert js argument to c++ type
  ObjectHandler::property_t SettlementDateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[6]).FromJust()));

  // convert js argument to c++ type
  ObjectHandler::property_t NpvDateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[7]).FromJust()));

 
  // launch worker
  LegBPSFromYieldWorker* worker = new LegBPSFromYieldWorker(
    ObjectIdCpp
,     YieldCpp
,     DayCounterCpp
,     CompoundingCpp
,     FrequencyCpp
,     IncludeSettlDateCpp
,     SettlementDateCpp
,     NpvDateCpp
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

void LegYieldWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_UNDERLYING(ObjectIdLibObj, mObjectId,
      QuantLibAddin::Leg, QuantLib::Leg)


  // convert input datatypes to QuantLib datatypes

  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::DayCounter DayCounterEnum =
      ObjectHandler::Create<QuantLib::DayCounter>()(mDayCounter);


  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::Compounding CompoundingEnum =
      ObjectHandler::Create<QuantLib::Compounding>()(mCompounding);


  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::Frequency FrequencyEnum =
      ObjectHandler::Create<QuantLib::Frequency>()(mFrequency);


  // convert input datatypes to QuantLib datatypes
  QuantLib::Date SettlementDateLib = ObjectHandler::convert2<QuantLib::Date>(
      mSettlementDate, "SettlementDate");


  // convert input datatypes to QuantLib datatypes
  QuantLib::Date NpvDateLib = ObjectHandler::convert2<QuantLib::Date>(
      mNpvDate, "NpvDate");


  // convert input datatypes to QuantLib datatypes

  // convert input datatypes to QuantLib datatypes
  QuantLib::Size MaxIterationsLib;
  QuantLibAddin::cppToLibrary(mMaxIterations, MaxIterationsLib);

       // invoke the utility function
  mReturnValue = QuantLib::CashFlows::yield(
      ObjectIdLibObj
      ,
       mNPV
      ,
       DayCounterEnum
      ,
       CompoundingEnum
      ,
       FrequencyEnum
      ,
       mIncludeSettlDate
      ,
       SettlementDateLib
      ,
       NpvDateLib
      ,
       mAccuracy
      ,
       MaxIterationsLib
      ,
       mGuess
     );
   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::LegYield) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectId is required.");
  }
  if (info.Length() == 1 || !info[1]->IsNumber()) {
      return Nan::ThrowError("NPV is required.");
  }
  if (info.Length() == 2 || !info[2]->IsString()) {
      return Nan::ThrowError("DayCounter is required.");
  }
  if (info.Length() == 3 || !info[3]->IsString()) {
      return Nan::ThrowError("Compounding is required.");
  }
  if (info.Length() == 4 || !info[4]->IsString()) {
      return Nan::ThrowError("Frequency is required.");
  }
  if (info.Length() == 5 || !info[5]->IsBoolean()) {
      return Nan::ThrowError("IncludeSettlDate is required.");
  }
  if (info.Length() == 8 || !info[8]->IsNumber()) {
      return Nan::ThrowError("Accuracy is required.");
  }
  if (info.Length() == 9 || !info[9]->IsNumber()) {
      return Nan::ThrowError("MaxIterations is required.");
  }
  if (info.Length() == 10 || !info[10]->IsNumber()) {
      return Nan::ThrowError("Guess is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectId(info[0]->ToString());
  string ObjectIdCpp(strdup(*strObjectId));

  // convert js argument to c++ type
  double NPVCpp = Nan::To<double>(info[1]).FromJust();

  // convert js argument to c++ type
  String::Utf8Value strDayCounter(info[2]->ToString());
  string DayCounterCpp(strdup(*strDayCounter));

  // convert js argument to c++ type
  String::Utf8Value strCompounding(info[3]->ToString());
  string CompoundingCpp(strdup(*strCompounding));

  // convert js argument to c++ type
  String::Utf8Value strFrequency(info[4]->ToString());
  string FrequencyCpp(strdup(*strFrequency));

  // convert js argument to c++ type
  bool IncludeSettlDateCpp = Nan::To<bool>(info[5]).FromJust();

  // convert js argument to c++ type
  ObjectHandler::property_t SettlementDateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[6]).FromJust()));

  // convert js argument to c++ type
  ObjectHandler::property_t NpvDateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[7]).FromJust()));

  // convert js argument to c++ type
  double AccuracyCpp = Nan::To<double>(info[8]).FromJust();

  // convert js argument to c++ type
  long MaxIterationsCpp = Nan::To<int32_t>(info[9]).FromJust();

  // convert js argument to c++ type
  double GuessCpp = Nan::To<double>(info[10]).FromJust();

 
  // launch worker
  LegYieldWorker* worker = new LegYieldWorker(
    ObjectIdCpp
,     NPVCpp
,     DayCounterCpp
,     CompoundingCpp
,     FrequencyCpp
,     IncludeSettlDateCpp
,     SettlementDateCpp
,     NpvDateCpp
,     AccuracyCpp
,     MaxIterationsCpp
,     GuessCpp
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

void LegDurationWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_UNDERLYING(ObjectIdLibObj, mObjectId,
      QuantLibAddin::Leg, QuantLib::Leg)


  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::DayCounter DayCounterEnum =
      ObjectHandler::Create<QuantLib::DayCounter>()(mDayCounter);


  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::Compounding CompoundingEnum =
      ObjectHandler::Create<QuantLib::Compounding>()(mCompounding);


  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::Frequency FrequencyEnum =
      ObjectHandler::Create<QuantLib::Frequency>()(mFrequency);


  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::Duration::Type DurationTypeEnum =
      ObjectHandler::Create<QuantLib::Duration::Type>()(mDurationType);


  // convert input datatypes to QuantLib datatypes
  QuantLib::Date SettlementDateLib = ObjectHandler::convert2<QuantLib::Date>(
      mSettlementDate, "SettlementDate");


  // convert input datatypes to QuantLib datatypes
  QuantLib::Date NpvDateLib = ObjectHandler::convert2<QuantLib::Date>(
      mNpvDate, "NpvDate");

       // invoke the utility function
  mReturnValue = QuantLib::CashFlows::duration(
      ObjectIdLibObj
      ,
       mYield
      ,
       DayCounterEnum
      ,
       CompoundingEnum
      ,
       FrequencyEnum
      ,
       DurationTypeEnum
      ,
       mIncludeSettlDate
      ,
       SettlementDateLib
      ,
       NpvDateLib
     );
   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::LegDuration) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectId is required.");
  }
  if (info.Length() == 1 || !info[1]->IsNumber()) {
      return Nan::ThrowError("Yield is required.");
  }
  if (info.Length() == 2 || !info[2]->IsString()) {
      return Nan::ThrowError("DayCounter is required.");
  }
  if (info.Length() == 3 || !info[3]->IsString()) {
      return Nan::ThrowError("Compounding is required.");
  }
  if (info.Length() == 4 || !info[4]->IsString()) {
      return Nan::ThrowError("Frequency is required.");
  }
  if (info.Length() == 5 || !info[5]->IsString()) {
      return Nan::ThrowError("DurationType is required.");
  }
  if (info.Length() == 6 || !info[6]->IsBoolean()) {
      return Nan::ThrowError("IncludeSettlDate is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectId(info[0]->ToString());
  string ObjectIdCpp(strdup(*strObjectId));

  // convert js argument to c++ type
  double YieldCpp = Nan::To<double>(info[1]).FromJust();

  // convert js argument to c++ type
  String::Utf8Value strDayCounter(info[2]->ToString());
  string DayCounterCpp(strdup(*strDayCounter));

  // convert js argument to c++ type
  String::Utf8Value strCompounding(info[3]->ToString());
  string CompoundingCpp(strdup(*strCompounding));

  // convert js argument to c++ type
  String::Utf8Value strFrequency(info[4]->ToString());
  string FrequencyCpp(strdup(*strFrequency));

  // convert js argument to c++ type
  String::Utf8Value strDurationType(info[5]->ToString());
  string DurationTypeCpp(strdup(*strDurationType));

  // convert js argument to c++ type
  bool IncludeSettlDateCpp = Nan::To<bool>(info[6]).FromJust();

  // convert js argument to c++ type
  ObjectHandler::property_t SettlementDateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[7]).FromJust()));

  // convert js argument to c++ type
  ObjectHandler::property_t NpvDateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[8]).FromJust()));

 
  // launch worker
  LegDurationWorker* worker = new LegDurationWorker(
    ObjectIdCpp
,     YieldCpp
,     DayCounterCpp
,     CompoundingCpp
,     FrequencyCpp
,     DurationTypeCpp
,     IncludeSettlDateCpp
,     SettlementDateCpp
,     NpvDateCpp
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

void LegConvexityWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_UNDERLYING(ObjectIdLibObj, mObjectId,
      QuantLibAddin::Leg, QuantLib::Leg)


  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::DayCounter DayCounterEnum =
      ObjectHandler::Create<QuantLib::DayCounter>()(mDayCounter);


  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::Compounding CompoundingEnum =
      ObjectHandler::Create<QuantLib::Compounding>()(mCompounding);


  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::Frequency FrequencyEnum =
      ObjectHandler::Create<QuantLib::Frequency>()(mFrequency);


  // convert input datatypes to QuantLib datatypes
  QuantLib::Date SettlementDateLib = ObjectHandler::convert2<QuantLib::Date>(
      mSettlementDate, "SettlementDate");


  // convert input datatypes to QuantLib datatypes
  QuantLib::Date NpvDateLib = ObjectHandler::convert2<QuantLib::Date>(
      mNpvDate, "NpvDate");

       // invoke the utility function
  QuantLib::Real returnValue = QuantLib::CashFlows::convexity(
      ObjectIdLibObj
      ,
       mYield
      ,
       DayCounterEnum
      ,
       CompoundingEnum
      ,
       FrequencyEnum
      ,
       mIncludeSettlDate
      ,
       SettlementDateLib
      ,
       NpvDateLib
     );

  mReturnValue = returnValue;

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::LegConvexity) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectId is required.");
  }
  if (info.Length() == 1 || !info[1]->IsNumber()) {
      return Nan::ThrowError("Yield is required.");
  }
  if (info.Length() == 2 || !info[2]->IsString()) {
      return Nan::ThrowError("DayCounter is required.");
  }
  if (info.Length() == 3 || !info[3]->IsString()) {
      return Nan::ThrowError("Compounding is required.");
  }
  if (info.Length() == 4 || !info[4]->IsString()) {
      return Nan::ThrowError("Frequency is required.");
  }
  if (info.Length() == 5 || !info[5]->IsBoolean()) {
      return Nan::ThrowError("IncludeSettlDate is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectId(info[0]->ToString());
  string ObjectIdCpp(strdup(*strObjectId));

  // convert js argument to c++ type
  double YieldCpp = Nan::To<double>(info[1]).FromJust();

  // convert js argument to c++ type
  String::Utf8Value strDayCounter(info[2]->ToString());
  string DayCounterCpp(strdup(*strDayCounter));

  // convert js argument to c++ type
  String::Utf8Value strCompounding(info[3]->ToString());
  string CompoundingCpp(strdup(*strCompounding));

  // convert js argument to c++ type
  String::Utf8Value strFrequency(info[4]->ToString());
  string FrequencyCpp(strdup(*strFrequency));

  // convert js argument to c++ type
  bool IncludeSettlDateCpp = Nan::To<bool>(info[5]).FromJust();

  // convert js argument to c++ type
  ObjectHandler::property_t SettlementDateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[6]).FromJust()));

  // convert js argument to c++ type
  ObjectHandler::property_t NpvDateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[7]).FromJust()));

 
  // launch worker
  LegConvexityWorker* worker = new LegConvexityWorker(
    ObjectIdCpp
,     YieldCpp
,     DayCounterCpp
,     CompoundingCpp
,     FrequencyCpp
,     IncludeSettlDateCpp
,     SettlementDateCpp
,     NpvDateCpp
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

void LegBasisPointValueWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_UNDERLYING(ObjectIdLibObj, mObjectId,
      QuantLibAddin::Leg, QuantLib::Leg)


  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::DayCounter DayCounterEnum =
      ObjectHandler::Create<QuantLib::DayCounter>()(mDayCounter);


  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::Compounding CompoundingEnum =
      ObjectHandler::Create<QuantLib::Compounding>()(mCompounding);


  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::Frequency FrequencyEnum =
      ObjectHandler::Create<QuantLib::Frequency>()(mFrequency);


  // convert input datatypes to QuantLib datatypes
  QuantLib::Date SettlementDateLib = ObjectHandler::convert2<QuantLib::Date>(
      mSettlementDate, "SettlementDate");


  // convert input datatypes to QuantLib datatypes
  QuantLib::Date NpvDateLib = ObjectHandler::convert2<QuantLib::Date>(
      mNpvDate, "NpvDate");

       // invoke the utility function
  QuantLib::Real returnValue = QuantLib::CashFlows::basisPointValue(
      ObjectIdLibObj
      ,
       mYield
      ,
       DayCounterEnum
      ,
       CompoundingEnum
      ,
       FrequencyEnum
      ,
       mIncludeSettlDate
      ,
       SettlementDateLib
      ,
       NpvDateLib
     );

  mReturnValue = returnValue;

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::LegBasisPointValue) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectId is required.");
  }
  if (info.Length() == 1 || !info[1]->IsNumber()) {
      return Nan::ThrowError("Yield is required.");
  }
  if (info.Length() == 2 || !info[2]->IsString()) {
      return Nan::ThrowError("DayCounter is required.");
  }
  if (info.Length() == 3 || !info[3]->IsString()) {
      return Nan::ThrowError("Compounding is required.");
  }
  if (info.Length() == 4 || !info[4]->IsString()) {
      return Nan::ThrowError("Frequency is required.");
  }
  if (info.Length() == 5 || !info[5]->IsBoolean()) {
      return Nan::ThrowError("IncludeSettlDate is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectId(info[0]->ToString());
  string ObjectIdCpp(strdup(*strObjectId));

  // convert js argument to c++ type
  double YieldCpp = Nan::To<double>(info[1]).FromJust();

  // convert js argument to c++ type
  String::Utf8Value strDayCounter(info[2]->ToString());
  string DayCounterCpp(strdup(*strDayCounter));

  // convert js argument to c++ type
  String::Utf8Value strCompounding(info[3]->ToString());
  string CompoundingCpp(strdup(*strCompounding));

  // convert js argument to c++ type
  String::Utf8Value strFrequency(info[4]->ToString());
  string FrequencyCpp(strdup(*strFrequency));

  // convert js argument to c++ type
  bool IncludeSettlDateCpp = Nan::To<bool>(info[5]).FromJust();

  // convert js argument to c++ type
  ObjectHandler::property_t SettlementDateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[6]).FromJust()));

  // convert js argument to c++ type
  ObjectHandler::property_t NpvDateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[7]).FromJust()));

 
  // launch worker
  LegBasisPointValueWorker* worker = new LegBasisPointValueWorker(
    ObjectIdCpp
,     YieldCpp
,     DayCounterCpp
,     CompoundingCpp
,     FrequencyCpp
,     IncludeSettlDateCpp
,     SettlementDateCpp
,     NpvDateCpp
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

void LegYieldValueBasisPointWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_UNDERLYING(ObjectIdLibObj, mObjectId,
      QuantLibAddin::Leg, QuantLib::Leg)


  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::DayCounter DayCounterEnum =
      ObjectHandler::Create<QuantLib::DayCounter>()(mDayCounter);


  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::Compounding CompoundingEnum =
      ObjectHandler::Create<QuantLib::Compounding>()(mCompounding);


  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::Frequency FrequencyEnum =
      ObjectHandler::Create<QuantLib::Frequency>()(mFrequency);


  // convert input datatypes to QuantLib datatypes
  QuantLib::Date SettlementDateLib = ObjectHandler::convert2<QuantLib::Date>(
      mSettlementDate, "SettlementDate");


  // convert input datatypes to QuantLib datatypes
  QuantLib::Date NpvDateLib = ObjectHandler::convert2<QuantLib::Date>(
      mNpvDate, "NpvDate");

       // invoke the utility function
  QuantLib::Real returnValue = QuantLib::CashFlows::yieldValueBasisPoint(
      ObjectIdLibObj
      ,
       mYield
      ,
       DayCounterEnum
      ,
       CompoundingEnum
      ,
       FrequencyEnum
      ,
       mIncludeSettlDate
      ,
       SettlementDateLib
      ,
       NpvDateLib
     );

  mReturnValue = returnValue;

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::LegYieldValueBasisPoint) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectId is required.");
  }
  if (info.Length() == 1 || !info[1]->IsNumber()) {
      return Nan::ThrowError("Yield is required.");
  }
  if (info.Length() == 2 || !info[2]->IsString()) {
      return Nan::ThrowError("DayCounter is required.");
  }
  if (info.Length() == 3 || !info[3]->IsString()) {
      return Nan::ThrowError("Compounding is required.");
  }
  if (info.Length() == 4 || !info[4]->IsString()) {
      return Nan::ThrowError("Frequency is required.");
  }
  if (info.Length() == 5 || !info[5]->IsBoolean()) {
      return Nan::ThrowError("IncludeSettlDate is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectId(info[0]->ToString());
  string ObjectIdCpp(strdup(*strObjectId));

  // convert js argument to c++ type
  double YieldCpp = Nan::To<double>(info[1]).FromJust();

  // convert js argument to c++ type
  String::Utf8Value strDayCounter(info[2]->ToString());
  string DayCounterCpp(strdup(*strDayCounter));

  // convert js argument to c++ type
  String::Utf8Value strCompounding(info[3]->ToString());
  string CompoundingCpp(strdup(*strCompounding));

  // convert js argument to c++ type
  String::Utf8Value strFrequency(info[4]->ToString());
  string FrequencyCpp(strdup(*strFrequency));

  // convert js argument to c++ type
  bool IncludeSettlDateCpp = Nan::To<bool>(info[5]).FromJust();

  // convert js argument to c++ type
  ObjectHandler::property_t SettlementDateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[6]).FromJust()));

  // convert js argument to c++ type
  ObjectHandler::property_t NpvDateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[7]).FromJust()));

 
  // launch worker
  LegYieldValueBasisPointWorker* worker = new LegYieldValueBasisPointWorker(
    ObjectIdCpp
,     YieldCpp
,     DayCounterCpp
,     CompoundingCpp
,     FrequencyCpp
,     IncludeSettlDateCpp
,     SettlementDateCpp
,     NpvDateCpp
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

void LegNPVFromZSpreadWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_UNDERLYING(ObjectIdLibObj, mObjectId,
      QuantLibAddin::Leg, QuantLib::Leg)


  // convert object IDs into library objects
  OH_GET_REFERENCE(DiscountCurveLibObjPtr, mDiscountCurve,
      QuantLibAddin::YieldTermStructure, QuantLib::YieldTermStructure)


  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::DayCounter DayCounterEnum =
      ObjectHandler::Create<QuantLib::DayCounter>()(mDayCounter);


  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::Compounding CompoundingEnum =
      ObjectHandler::Create<QuantLib::Compounding>()(mCompounding);


  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::Frequency FrequencyEnum =
      ObjectHandler::Create<QuantLib::Frequency>()(mFrequency);


  // convert input datatypes to QuantLib datatypes
  QuantLib::Date SettlementDateLib = ObjectHandler::convert2<QuantLib::Date>(
      mSettlementDate, "SettlementDate");


  // convert input datatypes to QuantLib datatypes
  QuantLib::Date NpvDateLib = ObjectHandler::convert2<QuantLib::Date>(
      mNpvDate, "NpvDate");

       // invoke the utility function
  QuantLib::Real returnValue = QuantLib::CashFlows::npv(
      ObjectIdLibObj
      ,
       DiscountCurveLibObjPtr
      ,
       mZSpread
      ,
       DayCounterEnum
      ,
       CompoundingEnum
      ,
       FrequencyEnum
      ,
       mIncludeSettlDate
      ,
       SettlementDateLib
      ,
       NpvDateLib
     );

  mReturnValue = returnValue;

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::LegNPVFromZSpread) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectId is required.");
  }
  if (info.Length() == 1 || !info[1]->IsString()) {
      return Nan::ThrowError("DiscountCurve is required.");
  }
  if (info.Length() == 2 || !info[2]->IsNumber()) {
      return Nan::ThrowError("ZSpread is required.");
  }
  if (info.Length() == 3 || !info[3]->IsString()) {
      return Nan::ThrowError("DayCounter is required.");
  }
  if (info.Length() == 4 || !info[4]->IsString()) {
      return Nan::ThrowError("Compounding is required.");
  }
  if (info.Length() == 5 || !info[5]->IsString()) {
      return Nan::ThrowError("Frequency is required.");
  }
  if (info.Length() == 6 || !info[6]->IsBoolean()) {
      return Nan::ThrowError("IncludeSettlDate is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectId(info[0]->ToString());
  string ObjectIdCpp(strdup(*strObjectId));

  // convert js argument to c++ type
  String::Utf8Value strDiscountCurve(info[1]->ToString());
  string DiscountCurveCpp(strdup(*strDiscountCurve));

  // convert js argument to c++ type
  double ZSpreadCpp = Nan::To<double>(info[2]).FromJust();

  // convert js argument to c++ type
  String::Utf8Value strDayCounter(info[3]->ToString());
  string DayCounterCpp(strdup(*strDayCounter));

  // convert js argument to c++ type
  String::Utf8Value strCompounding(info[4]->ToString());
  string CompoundingCpp(strdup(*strCompounding));

  // convert js argument to c++ type
  String::Utf8Value strFrequency(info[5]->ToString());
  string FrequencyCpp(strdup(*strFrequency));

  // convert js argument to c++ type
  bool IncludeSettlDateCpp = Nan::To<bool>(info[6]).FromJust();

  // convert js argument to c++ type
  ObjectHandler::property_t SettlementDateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[7]).FromJust()));

  // convert js argument to c++ type
  ObjectHandler::property_t NpvDateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[8]).FromJust()));

 
  // launch worker
  LegNPVFromZSpreadWorker* worker = new LegNPVFromZSpreadWorker(
    ObjectIdCpp
,     DiscountCurveCpp
,     ZSpreadCpp
,     DayCounterCpp
,     CompoundingCpp
,     FrequencyCpp
,     IncludeSettlDateCpp
,     SettlementDateCpp
,     NpvDateCpp
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

void LegZSpreadWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_UNDERLYING(ObjectIdLibObj, mObjectId,
      QuantLibAddin::Leg, QuantLib::Leg)


  // convert input datatypes to QuantLib datatypes

  // convert object IDs into library objects
  OH_GET_REFERENCE(DiscountCurveLibObjPtr, mDiscountCurve,
      QuantLibAddin::YieldTermStructure, QuantLib::YieldTermStructure)


  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::DayCounter DayCounterEnum =
      ObjectHandler::Create<QuantLib::DayCounter>()(mDayCounter);


  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::Compounding CompoundingEnum =
      ObjectHandler::Create<QuantLib::Compounding>()(mCompounding);


  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::Frequency FrequencyEnum =
      ObjectHandler::Create<QuantLib::Frequency>()(mFrequency);


  // convert input datatypes to QuantLib datatypes
  QuantLib::Date SettlementDateLib = ObjectHandler::convert2<QuantLib::Date>(
      mSettlementDate, "SettlementDate");


  // convert input datatypes to QuantLib datatypes
  QuantLib::Date NpvDateLib = ObjectHandler::convert2<QuantLib::Date>(
      mNpvDate, "NpvDate");


  // convert input datatypes to QuantLib datatypes

  // convert input datatypes to QuantLib datatypes
  QuantLib::Size MaxIterationsLib;
  QuantLibAddin::cppToLibrary(mMaxIterations, MaxIterationsLib);

       // invoke the utility function
  mReturnValue = QuantLib::CashFlows::zSpread(
      ObjectIdLibObj
      ,
       mNPV
      ,
       DiscountCurveLibObjPtr
      ,
       DayCounterEnum
      ,
       CompoundingEnum
      ,
       FrequencyEnum
      ,
       mIncludeSettlDate
      ,
       SettlementDateLib
      ,
       NpvDateLib
      ,
       mAccuracy
      ,
       MaxIterationsLib
      ,
       mGuess
     );
   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::LegZSpread) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectId is required.");
  }
  if (info.Length() == 1 || !info[1]->IsNumber()) {
      return Nan::ThrowError("NPV is required.");
  }
  if (info.Length() == 2 || !info[2]->IsString()) {
      return Nan::ThrowError("DiscountCurve is required.");
  }
  if (info.Length() == 3 || !info[3]->IsString()) {
      return Nan::ThrowError("DayCounter is required.");
  }
  if (info.Length() == 4 || !info[4]->IsString()) {
      return Nan::ThrowError("Compounding is required.");
  }
  if (info.Length() == 5 || !info[5]->IsString()) {
      return Nan::ThrowError("Frequency is required.");
  }
  if (info.Length() == 6 || !info[6]->IsBoolean()) {
      return Nan::ThrowError("IncludeSettlDate is required.");
  }
  if (info.Length() == 9 || !info[9]->IsNumber()) {
      return Nan::ThrowError("Accuracy is required.");
  }
  if (info.Length() == 10 || !info[10]->IsNumber()) {
      return Nan::ThrowError("MaxIterations is required.");
  }
  if (info.Length() == 11 || !info[11]->IsNumber()) {
      return Nan::ThrowError("Guess is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectId(info[0]->ToString());
  string ObjectIdCpp(strdup(*strObjectId));

  // convert js argument to c++ type
  double NPVCpp = Nan::To<double>(info[1]).FromJust();

  // convert js argument to c++ type
  String::Utf8Value strDiscountCurve(info[2]->ToString());
  string DiscountCurveCpp(strdup(*strDiscountCurve));

  // convert js argument to c++ type
  String::Utf8Value strDayCounter(info[3]->ToString());
  string DayCounterCpp(strdup(*strDayCounter));

  // convert js argument to c++ type
  String::Utf8Value strCompounding(info[4]->ToString());
  string CompoundingCpp(strdup(*strCompounding));

  // convert js argument to c++ type
  String::Utf8Value strFrequency(info[5]->ToString());
  string FrequencyCpp(strdup(*strFrequency));

  // convert js argument to c++ type
  bool IncludeSettlDateCpp = Nan::To<bool>(info[6]).FromJust();

  // convert js argument to c++ type
  ObjectHandler::property_t SettlementDateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[7]).FromJust()));

  // convert js argument to c++ type
  ObjectHandler::property_t NpvDateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[8]).FromJust()));

  // convert js argument to c++ type
  double AccuracyCpp = Nan::To<double>(info[9]).FromJust();

  // convert js argument to c++ type
  long MaxIterationsCpp = Nan::To<int32_t>(info[10]).FromJust();

  // convert js argument to c++ type
  double GuessCpp = Nan::To<double>(info[11]).FromJust();

 
  // launch worker
  LegZSpreadWorker* worker = new LegZSpreadWorker(
    ObjectIdCpp
,     NPVCpp
,     DiscountCurveCpp
,     DayCounterCpp
,     CompoundingCpp
,     FrequencyCpp
,     IncludeSettlDateCpp
,     SettlementDateCpp
,     NpvDateCpp
,     AccuracyCpp
,     MaxIterationsCpp
,     GuessCpp
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

void InterestRateImpliedRateWorker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes

  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::DayCounter DayCounterEnum =
      ObjectHandler::Create<QuantLib::DayCounter>()(mDayCounter);


  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::Compounding CompoundingEnum =
      ObjectHandler::Create<QuantLib::Compounding>()(mCompounding);


  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::Frequency FrequencyEnum =
      ObjectHandler::Create<QuantLib::Frequency>()(mFrequency);


  // convert input datatypes to QuantLib datatypes
  QuantLib::Date StartDateLib = ObjectHandler::convert2<QuantLib::Date>(
      mStartDate, "StartDate");


  // convert input datatypes to QuantLib datatypes
  QuantLib::Date EndDateLib = ObjectHandler::convert2<QuantLib::Date>(
      mEndDate, "EndDate");


  // convert input datatypes to QuantLib datatypes
  QuantLib::Date RefPeriodStartLib = ObjectHandler::convert2<QuantLib::Date>(
      mRefPeriodStart, "RefPeriodStart");


  // convert input datatypes to QuantLib datatypes
  QuantLib::Date RefPeriodEndLib = ObjectHandler::convert2<QuantLib::Date>(
      mRefPeriodEnd, "RefPeriodEnd");

       // invoke the utility function
  QuantLib::Real returnValue = QuantLib::InterestRate::impliedRate(
      mCompound
      ,
       DayCounterEnum
      ,
       CompoundingEnum
      ,
       FrequencyEnum
      ,
       StartDateLib
      ,
       EndDateLib
      ,
       RefPeriodStartLib
      ,
       RefPeriodEndLib
     );

  mReturnValue = returnValue;

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::InterestRateImpliedRate) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsNumber()) {
      return Nan::ThrowError("Compound is required.");
  }
  if (info.Length() == 1 || !info[1]->IsString()) {
      return Nan::ThrowError("DayCounter is required.");
  }
  if (info.Length() == 2 || !info[2]->IsString()) {
      return Nan::ThrowError("Compounding is required.");
  }
  if (info.Length() == 3 || !info[3]->IsString()) {
      return Nan::ThrowError("Frequency is required.");
  }
  // convert js argument to c++ type
  double CompoundCpp = Nan::To<double>(info[0]).FromJust();

  // convert js argument to c++ type
  String::Utf8Value strDayCounter(info[1]->ToString());
  string DayCounterCpp(strdup(*strDayCounter));

  // convert js argument to c++ type
  String::Utf8Value strCompounding(info[2]->ToString());
  string CompoundingCpp(strdup(*strCompounding));

  // convert js argument to c++ type
  String::Utf8Value strFrequency(info[3]->ToString());
  string FrequencyCpp(strdup(*strFrequency));

  // convert js argument to c++ type
  ObjectHandler::property_t StartDateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[4]).FromJust()));

  // convert js argument to c++ type
  ObjectHandler::property_t EndDateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[5]).FromJust()));

  // convert js argument to c++ type
  ObjectHandler::property_t RefPeriodStartCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[6]).FromJust()));

  // convert js argument to c++ type
  ObjectHandler::property_t RefPeriodEndCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[7]).FromJust()));

 
  // launch worker
  InterestRateImpliedRateWorker* worker = new InterestRateImpliedRateWorker(
    CompoundCpp
,     DayCounterCpp
,     CompoundingCpp
,     FrequencyCpp
,     StartDateCpp
,     EndDateCpp
,     RefPeriodStartCpp
,     RefPeriodEndCpp
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
 