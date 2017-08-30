/* 
  Copyright (C) 2016 -2017 Jerry Jin
*/

#include <nan.h>
#include <string.h>

#include "rangeaccrual.hpp"

#include <qlo/qladdindefines.hpp>
#include <qlo/rangeaccrual.hpp>
#include <qlo/indexes/iborindex.hpp>
#include <qlo/schedule.hpp>
#include <qlo/smilesection.hpp>
#include <qlo/termstructures.hpp>
#include <ql/termstructures/yieldtermstructure.hpp>
#include <ql/cashflows/rangeaccrual.hpp>
#include <ql/indexes/iborindex.hpp>
 #include <oh/objecthandler.hpp>
#include <oh/conversions/getobjectvector.hpp>
#include <qlo/valueobjects/vo_all.hpp>
#include <qlo/conversions/all.hpp>
#include "../loop.hpp"


void RangeAccrualFloatersCouponWorker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes
  QuantLib::Date PaymentDateLib = ObjectHandler::convert2<QuantLib::Date>(
      mPaymentDate, "PaymentDate");


  // convert object IDs into library objects
  OH_GET_REFERENCE(IborIndexLibObjPtr, mIborIndex,
      QuantLibAddin::IborIndex, QuantLib::IborIndex)


  // convert input datatypes to QuantLib datatypes
  QuantLib::Date StartDateLib = ObjectHandler::convert2<QuantLib::Date>(
      mStartDate, "StartDate");


  // convert input datatypes to QuantLib datatypes
  QuantLib::Date EndDateLib = ObjectHandler::convert2<QuantLib::Date>(
      mEndDate, "EndDate");


  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::DayCounter DayCountIDEnum =
      ObjectHandler::Create<QuantLib::DayCounter>()(mDayCountID);


  // convert input datatypes to QuantLib datatypes
  QuantLib::Date RefPeriodStartLib = ObjectHandler::convert2<QuantLib::Date>(
      mRefPeriodStart, "RefPeriodStart");


  // convert input datatypes to QuantLib datatypes
  QuantLib::Date RefPeriodEndLib = ObjectHandler::convert2<QuantLib::Date>(
      mRefPeriodEnd, "RefPeriodEnd");


  // convert object IDs into library objects
  OH_GET_REFERENCE(ObserSchedIDLibObjPtr, mObserSchedID,
      QuantLibAddin::Schedule, QuantLib::Schedule)

 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlRangeAccrualFloatersCoupon(
          mObjectID,
          mNominal,
          mPaymentDate,
          mIborIndex,
          mStartDate,
          mEndDate,
          mFixingDays,
          mDayCountID,
          mGearings,
          mSpreads,
          mRefPeriodStart,
          mRefPeriodEnd,
          mObserSchedID,
          mLowerTrigger,
          mUpperTrigger,
          false
      ));

    // Construct the Object
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::RangeAccrualFloatersCoupon(
          valueObject,
          mNominal,
          PaymentDateLib,
          IborIndexLibObjPtr,
          StartDateLib,
          EndDateLib,
          mFixingDays,
          DayCountIDEnum,
          mGearings,
          mSpreads,
          RefPeriodStartLib,
          RefPeriodEndLib,
          ObserSchedIDLibObjPtr,
          mLowerTrigger,
          mUpperTrigger,
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

NAN_METHOD(QuantLibXL::RangeAccrualFloatersCoupon) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsNumber()) {
      return Nan::ThrowError("Nominal is required.");
  }
  if (info.Length() == 3 || !info[3]->IsString()) {
      return Nan::ThrowError("IborIndex is required.");
  }
  if (info.Length() == 6 || !info[6]->IsNumber()) {
      return Nan::ThrowError("FixingDays is required.");
  }
  if (info.Length() == 7 || !info[7]->IsString()) {
      return Nan::ThrowError("DayCountID is required.");
  }
  if (info.Length() == 8 || !info[8]->IsNumber()) {
      return Nan::ThrowError("Gearings is required.");
  }
  if (info.Length() == 9 || !info[9]->IsNumber()) {
      return Nan::ThrowError("Spreads is required.");
  }
  if (info.Length() == 12 || !info[12]->IsString()) {
      return Nan::ThrowError("ObserSchedID is required.");
  }
  if (info.Length() == 13 || !info[13]->IsNumber()) {
      return Nan::ThrowError("LowerTrigger is required.");
  }
  if (info.Length() == 14 || !info[14]->IsNumber()) {
      return Nan::ThrowError("UpperTrigger is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  double NominalCpp = Nan::To<double>(info[1]).FromJust();

  // convert js argument to c++ type
  ObjectHandler::property_t PaymentDateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[2]).FromJust()));

  // convert js argument to c++ type
  String::Utf8Value strIborIndex(info[3]->ToString());
  string IborIndexCpp(strdup(*strIborIndex));

  // convert js argument to c++ type
  ObjectHandler::property_t StartDateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[4]).FromJust()));

  // convert js argument to c++ type
  ObjectHandler::property_t EndDateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[5]).FromJust()));

  // convert js argument to c++ type
  long FixingDaysCpp = Nan::To<int32_t>(info[6]).FromJust();

  // convert js argument to c++ type
  String::Utf8Value strDayCountID(info[7]->ToString());
  string DayCountIDCpp(strdup(*strDayCountID));

  // convert js argument to c++ type
  double GearingsCpp = Nan::To<double>(info[8]).FromJust();

  // convert js argument to c++ type
  double SpreadsCpp = Nan::To<double>(info[9]).FromJust();

  // convert js argument to c++ type
  ObjectHandler::property_t RefPeriodStartCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[10]).FromJust()));

  // convert js argument to c++ type
  ObjectHandler::property_t RefPeriodEndCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[11]).FromJust()));

  // convert js argument to c++ type
  String::Utf8Value strObserSchedID(info[12]->ToString());
  string ObserSchedIDCpp(strdup(*strObserSchedID));

  // convert js argument to c++ type
  double LowerTriggerCpp = Nan::To<double>(info[13]).FromJust();

  // convert js argument to c++ type
  double UpperTriggerCpp = Nan::To<double>(info[14]).FromJust();

 
  // launch worker
  RangeAccrualFloatersCouponWorker* worker = new RangeAccrualFloatersCouponWorker(
    ObjectIDCpp
,     NominalCpp
,     PaymentDateCpp
,     IborIndexCpp
,     StartDateCpp
,     EndDateCpp
,     FixingDaysCpp
,     DayCountIDCpp
,     GearingsCpp
,     SpreadsCpp
,     RefPeriodStartCpp
,     RefPeriodEndCpp
,     ObserSchedIDCpp
,     LowerTriggerCpp
,     UpperTriggerCpp
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

void RangeAccrualFloatersCouponFromLegWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_UNDERLYING(RangeAccrualLegLibObj, mRangeAccrualLeg,
      QuantLibAddin::Leg, QuantLib::Leg)


  // convert input datatypes to QuantLib datatypes
  QuantLib::Size PositionLib;
  QuantLibAddin::cppToLibrary(mPosition, PositionLib);

 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlRangeAccrualFloatersCouponFromLeg(
          mObjectID,
          mRangeAccrualLeg,
          mPosition,
          false
      ));

    // Construct the Object
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::RangeAccrualFloatersCoupon(
          valueObject,
          RangeAccrualLegLibObj,
          PositionLib,
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

NAN_METHOD(QuantLibXL::RangeAccrualFloatersCouponFromLeg) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsString()) {
      return Nan::ThrowError("RangeAccrualLeg is required.");
  }
  if (info.Length() == 2 || !info[2]->IsNumber()) {
      return Nan::ThrowError("Position is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  String::Utf8Value strRangeAccrualLeg(info[1]->ToString());
  string RangeAccrualLegCpp(strdup(*strRangeAccrualLeg));

  // convert js argument to c++ type
  long PositionCpp = Nan::To<int32_t>(info[2]).FromJust();

 
  // launch worker
  RangeAccrualFloatersCouponFromLegWorker* worker = new RangeAccrualFloatersCouponFromLegWorker(
    ObjectIDCpp
,     RangeAccrualLegCpp
,     PositionCpp
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

void RangeAccrualPricerByBgmWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_REFERENCE(SmileOnStartDateIDLibObjPtr, mSmileOnStartDateID,
      QuantLibAddin::SmileSection, QuantLib::SmileSection)


  // convert object IDs into library objects
  OH_GET_REFERENCE(SmileOnEndDateIDLibObjPtr, mSmileOnEndDateID,
      QuantLibAddin::SmileSection, QuantLib::SmileSection)

 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlRangeAccrualPricerByBgm(
          mObjectID,
          mCorrelation,
          mSmileOnStartDateID,
          mSmileOnEndDateID,
          mWithSmile,
          mByCallSpread,
          false
      ));

    // Construct the Object
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::RangeAccrualPricerByBgm(
          valueObject,
          mCorrelation,
          SmileOnStartDateIDLibObjPtr,
          SmileOnEndDateIDLibObjPtr,
          mWithSmile,
          mByCallSpread,
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

NAN_METHOD(QuantLibXL::RangeAccrualPricerByBgm) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsNumber()) {
      return Nan::ThrowError("Correlation is required.");
  }
  if (info.Length() == 2 || !info[2]->IsString()) {
      return Nan::ThrowError("SmileOnStartDateID is required.");
  }
  if (info.Length() == 3 || !info[3]->IsString()) {
      return Nan::ThrowError("SmileOnEndDateID is required.");
  }
  if (info.Length() == 4 || !info[4]->IsBoolean()) {
      return Nan::ThrowError("WithSmile is required.");
  }
  if (info.Length() == 5 || !info[5]->IsBoolean()) {
      return Nan::ThrowError("ByCallSpread is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  double CorrelationCpp = Nan::To<double>(info[1]).FromJust();

  // convert js argument to c++ type
  String::Utf8Value strSmileOnStartDateID(info[2]->ToString());
  string SmileOnStartDateIDCpp(strdup(*strSmileOnStartDateID));

  // convert js argument to c++ type
  String::Utf8Value strSmileOnEndDateID(info[3]->ToString());
  string SmileOnEndDateIDCpp(strdup(*strSmileOnEndDateID));

  // convert js argument to c++ type
  bool WithSmileCpp = Nan::To<bool>(info[4]).FromJust();

  // convert js argument to c++ type
  bool ByCallSpreadCpp = Nan::To<bool>(info[5]).FromJust();

 
  // launch worker
  RangeAccrualPricerByBgmWorker* worker = new RangeAccrualPricerByBgmWorker(
    ObjectIDCpp
,     CorrelationCpp
,     SmileOnStartDateIDCpp
,     SmileOnEndDateIDCpp
,     WithSmileCpp
,     ByCallSpreadCpp
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

void RangeAccrualFloatersCouponSetPricerWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::RangeAccrualFloatersCoupon, QuantLib::RangeAccrualFloatersCoupon)


  // convert object IDs into library objects
  OH_GET_REFERENCE(RangeAccrualPricerLibObjPtr, mRangeAccrualPricer,
      QuantLibAddin::RangeAccrualPricer, QuantLib::RangeAccrualPricer)

     
  // invoke the member function
  ObjectIDLibObjPtr->setPricer(
        RangeAccrualPricerLibObjPtr
       );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::RangeAccrualFloatersCouponSetPricer) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsString()) {
      return Nan::ThrowError("RangeAccrualPricer is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  String::Utf8Value strRangeAccrualPricer(info[1]->ToString());
  string RangeAccrualPricerCpp(strdup(*strRangeAccrualPricer));

 
  // launch worker
  RangeAccrualFloatersCouponSetPricerWorker* worker = new RangeAccrualFloatersCouponSetPricerWorker(
    ObjectIDCpp
,     RangeAccrualPricerCpp
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

void RangeAccrualFloatersCouponObservationDatesWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::RangeAccrualFloatersCoupon, QuantLib::RangeAccrualFloatersCoupon)

     
  // loop on the input parameter and populate the return vector
  std::vector<QuantLib::Date> returnValue = ObjectIDLibObjPtr->observationDates(
      );


  mReturnValue = QuantLibAddin::libraryToVector(returnValue);

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::RangeAccrualFloatersCouponObservationDates) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  RangeAccrualFloatersCouponObservationDatesWorker* worker = new RangeAccrualFloatersCouponObservationDatesWorker(
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

void RangeAccrualFloatersCouponStarDateWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::RangeAccrualFloatersCoupon, QuantLib::RangeAccrualFloatersCoupon)

     
  // invoke the member function
  QuantLib::Date returnValue = ObjectIDLibObjPtr->accrualStartDate(
      );


  mReturnValue = QuantLibAddin::libraryToScalar(returnValue);

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::RangeAccrualFloatersCouponStarDate) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  RangeAccrualFloatersCouponStarDateWorker* worker = new RangeAccrualFloatersCouponStarDateWorker(
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

void RangeAccrualFloatersCouponEndDateWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::RangeAccrualFloatersCoupon, QuantLib::RangeAccrualFloatersCoupon)

     
  // invoke the member function
  QuantLib::Date returnValue = ObjectIDLibObjPtr->accrualEndDate(
      );


  mReturnValue = QuantLibAddin::libraryToScalar(returnValue);

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::RangeAccrualFloatersCouponEndDate) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  RangeAccrualFloatersCouponEndDateWorker* worker = new RangeAccrualFloatersCouponEndDateWorker(
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

void RangeAccrualFloatersCouponObservationsNoWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::RangeAccrualFloatersCoupon, QuantLib::RangeAccrualFloatersCoupon)

     
  // invoke the member function
  QuantLib::Size returnValue = ObjectIDLibObjPtr->observationsNo(
      );


  mReturnValue = QuantLibAddin::libraryToScalar(returnValue);

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::RangeAccrualFloatersCouponObservationsNo) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  RangeAccrualFloatersCouponObservationsNoWorker* worker = new RangeAccrualFloatersCouponObservationsNoWorker(
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

void RangeAccrualFloatersPriceWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::RangeAccrualFloatersCoupon, QuantLib::RangeAccrualFloatersCoupon)


  // convert object IDs into library objects
  OH_GET_OBJECT(YieldCurveCoerce, mYieldCurve, ObjectHandler::Object)
  QuantLib::Handle<QuantLib::YieldTermStructure> YieldCurveLibObj =
      QuantLibAddin::CoerceHandle<
          QuantLibAddin::YieldTermStructure,
          QuantLib::YieldTermStructure>()(
              YieldCurveCoerce);

     
  // invoke the member function
  mReturnValue = ObjectIDLibObjPtr->price(
        YieldCurveLibObj
       );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::RangeAccrualFloatersPrice) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  ObjectHandler::property_t YieldCurveCpp =
      ObjectHandler::property_t(static_cast<double>(Nan::To<double>(info[1]).FromJust()));

 
  // launch worker
  RangeAccrualFloatersPriceWorker* worker = new RangeAccrualFloatersPriceWorker(
    ObjectIDCpp
,     YieldCurveCpp
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

void SimpleFloaterPriceWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::RangeAccrualFloatersCoupon, QuantLib::RangeAccrualFloatersCoupon)


  // convert object IDs into library objects
  OH_GET_OBJECT(YieldCurveCoerce, mYieldCurve, ObjectHandler::Object)
  QuantLib::Handle<QuantLib::YieldTermStructure> YieldCurveLibObj =
      QuantLibAddin::CoerceHandle<
          QuantLibAddin::YieldTermStructure,
          QuantLib::YieldTermStructure>()(
              YieldCurveCoerce);

     
  // invoke the member function
  mReturnValue = ObjectIDLibObjPtr->priceWithoutOptionality(
        YieldCurveLibObj
       );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::SimpleFloaterPrice) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  ObjectHandler::property_t YieldCurveCpp =
      ObjectHandler::property_t(static_cast<double>(Nan::To<double>(info[1]).FromJust()));

 
  // launch worker
  SimpleFloaterPriceWorker* worker = new SimpleFloaterPriceWorker(
    ObjectIDCpp
,     YieldCurveCpp
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
 