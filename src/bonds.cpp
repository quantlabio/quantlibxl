/* 
  Copyright (C) 2016 -2017 Jerry Jin
*/

#include <nan.h>
#include <string.h>

#include "bonds.hpp"

#include <qlo/qladdindefines.hpp>
#include <qlo/indexes/iborindex.hpp>
#include <qlo/indexes/swapindex.hpp>
#include <qlo/schedule.hpp>
#include <qlo/bonds.hpp>
#include <qlo/termstructures.hpp>
#include <qlo/couponvectors.hpp>
#include <ql/instruments/bond.hpp>
#include <ql/termstructures/yieldtermstructure.hpp>
#include <ql/pricingengines/bond/bondfunctions.hpp>
#include <ql/currency.hpp>
#include <ql/indexes/iborindex.hpp>
#include <ql/indexes/swapindex.hpp>
 #include <oh/objecthandler.hpp>
#include <oh/conversions/getobjectvector.hpp>
#include <qlo/valueobjects/vo_all.hpp>
#include <qlo/conversions/all.hpp>
#include "../loop.hpp"


void FixedRateBondWorker::Execute(){

  try{

  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::Currency CurrencyEnum =
      ObjectHandler::Create<QuantLib::Currency>()(mCurrency);


  // convert input datatypes to QuantLib datatypes
  QuantLib::Size SettlementDaysLib;
  QuantLibAddin::cppToLibrary(mSettlementDays, SettlementDaysLib);


  // convert input datatypes to QuantLib datatypes

  // convert object IDs into library objects
  OH_GET_REFERENCE(ScheduleIDLibObjPtr, mScheduleID,
      QuantLibAddin::Schedule, QuantLib::Schedule)


  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::DayCounter DayCounterEnum =
      ObjectHandler::Create<QuantLib::DayCounter>()(mDayCounter);


  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::BusinessDayConvention PaymentBDCEnum =
      ObjectHandler::Create<QuantLib::BusinessDayConvention>()(mPaymentBDC);


  // convert input datatypes to QuantLib datatypes

  // convert input datatypes to QuantLib datatypes
  QuantLib::Date IssueDateLib = ObjectHandler::convert2<QuantLib::Date>(
      mIssueDate, "IssueDate");


  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::Calendar PaymentCalendarEnum =
      ObjectHandler::Create<QuantLib::Calendar>()(mPaymentCalendar);

 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlFixedRateBond(
          mObjectID,
          mDescription,
          mCurrency,
          mSettlementDays,
          mFaceAmount,
          mScheduleID,
          mCoupons,
          mDayCounter,
          mPaymentBDC,
          mRedemption,
          mIssueDate,
          mPaymentCalendar,
          false
      ));

    // Construct the Object
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::FixedRateBond(
          valueObject,
          mDescription,
          CurrencyEnum,
          SettlementDaysLib,
          mFaceAmount,
          ScheduleIDLibObjPtr,
          mCoupons,
          DayCounterEnum,
          PaymentBDCEnum,
          mRedemption,
          IssueDateLib,
          PaymentCalendarEnum,
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

NAN_METHOD(QuantLibXL::FixedRateBond) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsString()) {
      return Nan::ThrowError("Description is required.");
  }
  if (info.Length() == 2 || !info[2]->IsString()) {
      return Nan::ThrowError("Currency is required.");
  }
  if (info.Length() == 3 || !info[3]->IsNumber()) {
      return Nan::ThrowError("SettlementDays is required.");
  }
  if (info.Length() == 4 || !info[4]->IsNumber()) {
      return Nan::ThrowError("FaceAmount is required.");
  }
  if (info.Length() == 5 || !info[5]->IsString()) {
      return Nan::ThrowError("ScheduleID is required.");
  }
  if (info.Length() == 6 || !info[6]->IsArray()) {
      return Nan::ThrowError("Coupons is required.");
  }
  if (info.Length() == 7 || !info[7]->IsString()) {
      return Nan::ThrowError("DayCounter is required.");
  }
  if (info.Length() == 8 || !info[8]->IsString()) {
      return Nan::ThrowError("PaymentBDC is required.");
  }
  if (info.Length() == 9 || !info[9]->IsNumber()) {
      return Nan::ThrowError("Redemption is required.");
  }
  if (info.Length() == 11 || !info[11]->IsString()) {
      return Nan::ThrowError("PaymentCalendar is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  String::Utf8Value strDescription(info[1]->ToString());
  string DescriptionCpp(strdup(*strDescription));

  // convert js argument to c++ type
  String::Utf8Value strCurrency(info[2]->ToString());
  string CurrencyCpp(strdup(*strCurrency));

  // convert js argument to c++ type
  long SettlementDaysCpp = Nan::To<int32_t>(info[3]).FromJust();

  // convert js argument to c++ type
  double FaceAmountCpp = Nan::To<double>(info[4]).FromJust();

  // convert js argument to c++ type
  String::Utf8Value strScheduleID(info[5]->ToString());
  string ScheduleIDCpp(strdup(*strScheduleID));

  // convert js argument to c++ type
  std::vector<double>CouponsCpp;

  Local<Array> CouponsArray = info[6].As<Array>();
  for (unsigned int i = 0; i < CouponsArray->Length(); i++){
    CouponsCpp.push_back(Nan::To<double>(Nan::Get(CouponsArray, i).ToLocalChecked()).FromJust());
  }

  // convert js argument to c++ type
  String::Utf8Value strDayCounter(info[7]->ToString());
  string DayCounterCpp(strdup(*strDayCounter));

  // convert js argument to c++ type
  String::Utf8Value strPaymentBDC(info[8]->ToString());
  string PaymentBDCCpp(strdup(*strPaymentBDC));

  // convert js argument to c++ type
  double RedemptionCpp = Nan::To<double>(info[9]).FromJust();

  // convert js argument to c++ type
  ObjectHandler::property_t IssueDateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[10]).FromJust()));

  // convert js argument to c++ type
  String::Utf8Value strPaymentCalendar(info[11]->ToString());
  string PaymentCalendarCpp(strdup(*strPaymentCalendar));

 
  // launch worker
  FixedRateBondWorker* worker = new FixedRateBondWorker(
    ObjectIDCpp
,     DescriptionCpp
,     CurrencyCpp
,     SettlementDaysCpp
,     FaceAmountCpp
,     ScheduleIDCpp
,     CouponsCpp
,     DayCounterCpp
,     PaymentBDCCpp
,     RedemptionCpp
,     IssueDateCpp
,     PaymentCalendarCpp
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

void FixedRateBond2Worker::Execute(){

  try{

  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::Currency CurrencyEnum =
      ObjectHandler::Create<QuantLib::Currency>()(mCurrency);


  // convert input datatypes to QuantLib datatypes
  QuantLib::Size SettlementDaysLib;
  QuantLibAddin::cppToLibrary(mSettlementDays, SettlementDaysLib);


  // convert input datatypes to QuantLib datatypes

  // convert object IDs into library objects
  OH_GET_REFERENCE(ScheduleIDLibObjPtr, mScheduleID,
      QuantLibAddin::Schedule, QuantLib::Schedule)


  // convert object IDs into library objects
  std::vector< boost::shared_ptr<QuantLib::InterestRate> > CouponsLibObjPtr =
      ObjectHandler::getLibraryObjectVector<QuantLibAddin::InterestRate, QuantLib::InterestRate>(mCoupons);


  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::BusinessDayConvention PaymentBDCEnum =
      ObjectHandler::Create<QuantLib::BusinessDayConvention>()(mPaymentBDC);


  // convert input datatypes to QuantLib datatypes

  // convert input datatypes to QuantLib datatypes
  QuantLib::Date IssueDateLib = ObjectHandler::convert2<QuantLib::Date>(
      mIssueDate, "IssueDate");


  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::Calendar PaymentCalendarEnum =
      ObjectHandler::Create<QuantLib::Calendar>()(mPaymentCalendar);

 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlFixedRateBond2(
          mObjectID,
          mDescription,
          mCurrency,
          mSettlementDays,
          mFaceAmount,
          mScheduleID,
          mCoupons,
          mPaymentBDC,
          mRedemption,
          mIssueDate,
          mPaymentCalendar,
          false
      ));

    // Construct the Object
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::FixedRateBond(
          valueObject,
          mDescription,
          CurrencyEnum,
          SettlementDaysLib,
          mFaceAmount,
          ScheduleIDLibObjPtr,
          CouponsLibObjPtr,
          PaymentBDCEnum,
          mRedemption,
          IssueDateLib,
          PaymentCalendarEnum,
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

NAN_METHOD(QuantLibXL::FixedRateBond2) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsString()) {
      return Nan::ThrowError("Description is required.");
  }
  if (info.Length() == 2 || !info[2]->IsString()) {
      return Nan::ThrowError("Currency is required.");
  }
  if (info.Length() == 3 || !info[3]->IsNumber()) {
      return Nan::ThrowError("SettlementDays is required.");
  }
  if (info.Length() == 4 || !info[4]->IsNumber()) {
      return Nan::ThrowError("FaceAmount is required.");
  }
  if (info.Length() == 5 || !info[5]->IsString()) {
      return Nan::ThrowError("ScheduleID is required.");
  }
  if (info.Length() == 6 || !info[6]->IsArray()) {
      return Nan::ThrowError("Coupons is required.");
  }
  if (info.Length() == 7 || !info[7]->IsString()) {
      return Nan::ThrowError("PaymentBDC is required.");
  }
  if (info.Length() == 8 || !info[8]->IsNumber()) {
      return Nan::ThrowError("Redemption is required.");
  }
  if (info.Length() == 10 || !info[10]->IsString()) {
      return Nan::ThrowError("PaymentCalendar is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  String::Utf8Value strDescription(info[1]->ToString());
  string DescriptionCpp(strdup(*strDescription));

  // convert js argument to c++ type
  String::Utf8Value strCurrency(info[2]->ToString());
  string CurrencyCpp(strdup(*strCurrency));

  // convert js argument to c++ type
  long SettlementDaysCpp = Nan::To<int32_t>(info[3]).FromJust();

  // convert js argument to c++ type
  double FaceAmountCpp = Nan::To<double>(info[4]).FromJust();

  // convert js argument to c++ type
  String::Utf8Value strScheduleID(info[5]->ToString());
  string ScheduleIDCpp(strdup(*strScheduleID));

  // convert js argument to c++ type
  std::vector<string>CouponsCpp;

  Local<Array> CouponsArray = info[6].As<Array>();
  for (unsigned int i = 0; i < CouponsArray->Length(); i++){
    String::Utf8Value strCoupons(Nan::Get(CouponsArray, i).ToLocalChecked()->ToString());
    CouponsCpp.push_back(strdup(*strCoupons));
  }

  // convert js argument to c++ type
  String::Utf8Value strPaymentBDC(info[7]->ToString());
  string PaymentBDCCpp(strdup(*strPaymentBDC));

  // convert js argument to c++ type
  double RedemptionCpp = Nan::To<double>(info[8]).FromJust();

  // convert js argument to c++ type
  ObjectHandler::property_t IssueDateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[9]).FromJust()));

  // convert js argument to c++ type
  String::Utf8Value strPaymentCalendar(info[10]->ToString());
  string PaymentCalendarCpp(strdup(*strPaymentCalendar));

 
  // launch worker
  FixedRateBond2Worker* worker = new FixedRateBond2Worker(
    ObjectIDCpp
,     DescriptionCpp
,     CurrencyCpp
,     SettlementDaysCpp
,     FaceAmountCpp
,     ScheduleIDCpp
,     CouponsCpp
,     PaymentBDCCpp
,     RedemptionCpp
,     IssueDateCpp
,     PaymentCalendarCpp
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

void FloatingRateBondWorker::Execute(){

  try{

  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::Currency CurrencyEnum =
      ObjectHandler::Create<QuantLib::Currency>()(mCurrency);


  // convert input datatypes to QuantLib datatypes
  QuantLib::Size SettlementDaysLib;
  QuantLibAddin::cppToLibrary(mSettlementDays, SettlementDaysLib);


  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::BusinessDayConvention PaymentBDCEnum =
      ObjectHandler::Create<QuantLib::BusinessDayConvention>()(mPaymentBDC);


  // convert input datatypes to QuantLib datatypes

  // convert object IDs into library objects
  OH_GET_REFERENCE(ScheduleIDLibObjPtr, mScheduleID,
      QuantLibAddin::Schedule, QuantLib::Schedule)


  // convert input datatypes to QuantLib datatypes
  QuantLib::Natural FixingDaysLib = ObjectHandler::convert2<long>(
      mFixingDays, "FixingDays", QuantLib::Null<QuantLib::Natural>());


  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::DayCounter DayCounterEnum =
      ObjectHandler::Create<QuantLib::DayCounter>()(mDayCounter);


  // convert object IDs into library objects
  OH_GET_REFERENCE(IborIndexLibObjPtr, mIborIndex,
      QuantLibAddin::IborIndex, QuantLib::IborIndex)


  // convert input datatypes to QuantLib datatypes

  // convert input datatypes to QuantLib datatypes
  QuantLib::Date IssueDateLib = ObjectHandler::convert2<QuantLib::Date>(
      mIssueDate, "IssueDate");

 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlFloatingRateBond(
          mObjectID,
          mDescription,
          mCurrency,
          mSettlementDays,
          mPaymentBDC,
          mFaceAmount,
          mScheduleID,
          mFixingDays,
          mIsInArrears,
          mDayCounter,
          mFloors,
          mGearings,
          mIborIndex,
          mSpreads,
          mCaps,
          mRedemption,
          mIssueDate,
          false
      ));

    // Construct the Object
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::FloatingRateBond(
          valueObject,
          mDescription,
          CurrencyEnum,
          SettlementDaysLib,
          PaymentBDCEnum,
          mFaceAmount,
          ScheduleIDLibObjPtr,
          FixingDaysLib,
          mIsInArrears,
          DayCounterEnum,
          mFloors,
          mGearings,
          IborIndexLibObjPtr,
          mSpreads,
          mCaps,
          mRedemption,
          IssueDateLib,
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

NAN_METHOD(QuantLibXL::FloatingRateBond) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsString()) {
      return Nan::ThrowError("Description is required.");
  }
  if (info.Length() == 2 || !info[2]->IsString()) {
      return Nan::ThrowError("Currency is required.");
  }
  if (info.Length() == 3 || !info[3]->IsNumber()) {
      return Nan::ThrowError("SettlementDays is required.");
  }
  if (info.Length() == 4 || !info[4]->IsString()) {
      return Nan::ThrowError("PaymentBDC is required.");
  }
  if (info.Length() == 5 || !info[5]->IsNumber()) {
      return Nan::ThrowError("FaceAmount is required.");
  }
  if (info.Length() == 6 || !info[6]->IsString()) {
      return Nan::ThrowError("ScheduleID is required.");
  }
  if (info.Length() == 8 || !info[8]->IsBoolean()) {
      return Nan::ThrowError("IsInArrears is required.");
  }
  if (info.Length() == 9 || !info[9]->IsString()) {
      return Nan::ThrowError("DayCounter is required.");
  }
  if (info.Length() == 10 || !info[10]->IsArray()) {
      return Nan::ThrowError("Floors is required.");
  }
  if (info.Length() == 11 || !info[11]->IsArray()) {
      return Nan::ThrowError("Gearings is required.");
  }
  if (info.Length() == 12 || !info[12]->IsString()) {
      return Nan::ThrowError("IborIndex is required.");
  }
  if (info.Length() == 13 || !info[13]->IsArray()) {
      return Nan::ThrowError("Spreads is required.");
  }
  if (info.Length() == 14 || !info[14]->IsArray()) {
      return Nan::ThrowError("Caps is required.");
  }
  if (info.Length() == 15 || !info[15]->IsNumber()) {
      return Nan::ThrowError("Redemption is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  String::Utf8Value strDescription(info[1]->ToString());
  string DescriptionCpp(strdup(*strDescription));

  // convert js argument to c++ type
  String::Utf8Value strCurrency(info[2]->ToString());
  string CurrencyCpp(strdup(*strCurrency));

  // convert js argument to c++ type
  long SettlementDaysCpp = Nan::To<int32_t>(info[3]).FromJust();

  // convert js argument to c++ type
  String::Utf8Value strPaymentBDC(info[4]->ToString());
  string PaymentBDCCpp(strdup(*strPaymentBDC));

  // convert js argument to c++ type
  double FaceAmountCpp = Nan::To<double>(info[5]).FromJust();

  // convert js argument to c++ type
  String::Utf8Value strScheduleID(info[6]->ToString());
  string ScheduleIDCpp(strdup(*strScheduleID));

  // convert js argument to c++ type
  ObjectHandler::property_t FixingDaysCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[7]).FromJust()));

  // convert js argument to c++ type
  bool IsInArrearsCpp = Nan::To<bool>(info[8]).FromJust();

  // convert js argument to c++ type
  String::Utf8Value strDayCounter(info[9]->ToString());
  string DayCounterCpp(strdup(*strDayCounter));

  // convert js argument to c++ type
  std::vector<double>FloorsCpp;

  Local<Array> FloorsArray = info[10].As<Array>();
  for (unsigned int i = 0; i < FloorsArray->Length(); i++){
    FloorsCpp.push_back(Nan::To<double>(Nan::Get(FloorsArray, i).ToLocalChecked()).FromJust());
  }

  // convert js argument to c++ type
  std::vector<double>GearingsCpp;

  Local<Array> GearingsArray = info[11].As<Array>();
  for (unsigned int i = 0; i < GearingsArray->Length(); i++){
    GearingsCpp.push_back(Nan::To<double>(Nan::Get(GearingsArray, i).ToLocalChecked()).FromJust());
  }

  // convert js argument to c++ type
  String::Utf8Value strIborIndex(info[12]->ToString());
  string IborIndexCpp(strdup(*strIborIndex));

  // convert js argument to c++ type
  std::vector<double>SpreadsCpp;

  Local<Array> SpreadsArray = info[13].As<Array>();
  for (unsigned int i = 0; i < SpreadsArray->Length(); i++){
    SpreadsCpp.push_back(Nan::To<double>(Nan::Get(SpreadsArray, i).ToLocalChecked()).FromJust());
  }

  // convert js argument to c++ type
  std::vector<double>CapsCpp;

  Local<Array> CapsArray = info[14].As<Array>();
  for (unsigned int i = 0; i < CapsArray->Length(); i++){
    CapsCpp.push_back(Nan::To<double>(Nan::Get(CapsArray, i).ToLocalChecked()).FromJust());
  }

  // convert js argument to c++ type
  double RedemptionCpp = Nan::To<double>(info[15]).FromJust();

  // convert js argument to c++ type
  ObjectHandler::property_t IssueDateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[16]).FromJust()));

 
  // launch worker
  FloatingRateBondWorker* worker = new FloatingRateBondWorker(
    ObjectIDCpp
,     DescriptionCpp
,     CurrencyCpp
,     SettlementDaysCpp
,     PaymentBDCCpp
,     FaceAmountCpp
,     ScheduleIDCpp
,     FixingDaysCpp
,     IsInArrearsCpp
,     DayCounterCpp
,     FloorsCpp
,     GearingsCpp
,     IborIndexCpp
,     SpreadsCpp
,     CapsCpp
,     RedemptionCpp
,     IssueDateCpp
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

void CmsRateBondWorker::Execute(){

  try{

  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::Currency CurrencyEnum =
      ObjectHandler::Create<QuantLib::Currency>()(mCurrency);


  // convert input datatypes to QuantLib datatypes
  QuantLib::Size SettlementDaysLib;
  QuantLibAddin::cppToLibrary(mSettlementDays, SettlementDaysLib);


  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::BusinessDayConvention PaymentBDCEnum =
      ObjectHandler::Create<QuantLib::BusinessDayConvention>()(mPaymentBDC);


  // convert input datatypes to QuantLib datatypes

  // convert object IDs into library objects
  OH_GET_REFERENCE(ScheduleIDLibObjPtr, mScheduleID,
      QuantLibAddin::Schedule, QuantLib::Schedule)


  // convert input datatypes to QuantLib datatypes
  QuantLib::Natural FixingDaysLib = ObjectHandler::convert2<long>(
      mFixingDays, "FixingDays", QuantLib::Null<QuantLib::Natural>());


  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::DayCounter DayCounterEnum =
      ObjectHandler::Create<QuantLib::DayCounter>()(mDayCounter);


  // convert object IDs into library objects
  OH_GET_REFERENCE(SwapIndexLibObjPtr, mSwapIndex,
      QuantLibAddin::SwapIndex, QuantLib::SwapIndex)


  // convert input datatypes to QuantLib datatypes

  // convert input datatypes to QuantLib datatypes
  QuantLib::Date IssueDateLib = ObjectHandler::convert2<QuantLib::Date>(
      mIssueDate, "IssueDate");

 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlCmsRateBond(
          mObjectID,
          mDescription,
          mCurrency,
          mSettlementDays,
          mPaymentBDC,
          mFaceAmount,
          mScheduleID,
          mFixingDays,
          mIsInArrears,
          mDayCounter,
          mFloors,
          mGearings,
          mSwapIndex,
          mSpreads,
          mCaps,
          mRedemption,
          mIssueDate,
          false
      ));

    // Construct the Object
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::CmsRateBond(
          valueObject,
          mDescription,
          CurrencyEnum,
          SettlementDaysLib,
          PaymentBDCEnum,
          mFaceAmount,
          ScheduleIDLibObjPtr,
          FixingDaysLib,
          mIsInArrears,
          DayCounterEnum,
          mFloors,
          mGearings,
          SwapIndexLibObjPtr,
          mSpreads,
          mCaps,
          mRedemption,
          IssueDateLib,
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

NAN_METHOD(QuantLibXL::CmsRateBond) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsString()) {
      return Nan::ThrowError("Description is required.");
  }
  if (info.Length() == 2 || !info[2]->IsString()) {
      return Nan::ThrowError("Currency is required.");
  }
  if (info.Length() == 3 || !info[3]->IsNumber()) {
      return Nan::ThrowError("SettlementDays is required.");
  }
  if (info.Length() == 4 || !info[4]->IsString()) {
      return Nan::ThrowError("PaymentBDC is required.");
  }
  if (info.Length() == 5 || !info[5]->IsNumber()) {
      return Nan::ThrowError("FaceAmount is required.");
  }
  if (info.Length() == 6 || !info[6]->IsString()) {
      return Nan::ThrowError("ScheduleID is required.");
  }
  if (info.Length() == 8 || !info[8]->IsBoolean()) {
      return Nan::ThrowError("IsInArrears is required.");
  }
  if (info.Length() == 9 || !info[9]->IsString()) {
      return Nan::ThrowError("DayCounter is required.");
  }
  if (info.Length() == 10 || !info[10]->IsArray()) {
      return Nan::ThrowError("Floors is required.");
  }
  if (info.Length() == 11 || !info[11]->IsArray()) {
      return Nan::ThrowError("Gearings is required.");
  }
  if (info.Length() == 12 || !info[12]->IsString()) {
      return Nan::ThrowError("SwapIndex is required.");
  }
  if (info.Length() == 13 || !info[13]->IsArray()) {
      return Nan::ThrowError("Spreads is required.");
  }
  if (info.Length() == 14 || !info[14]->IsArray()) {
      return Nan::ThrowError("Caps is required.");
  }
  if (info.Length() == 15 || !info[15]->IsNumber()) {
      return Nan::ThrowError("Redemption is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  String::Utf8Value strDescription(info[1]->ToString());
  string DescriptionCpp(strdup(*strDescription));

  // convert js argument to c++ type
  String::Utf8Value strCurrency(info[2]->ToString());
  string CurrencyCpp(strdup(*strCurrency));

  // convert js argument to c++ type
  long SettlementDaysCpp = Nan::To<int32_t>(info[3]).FromJust();

  // convert js argument to c++ type
  String::Utf8Value strPaymentBDC(info[4]->ToString());
  string PaymentBDCCpp(strdup(*strPaymentBDC));

  // convert js argument to c++ type
  double FaceAmountCpp = Nan::To<double>(info[5]).FromJust();

  // convert js argument to c++ type
  String::Utf8Value strScheduleID(info[6]->ToString());
  string ScheduleIDCpp(strdup(*strScheduleID));

  // convert js argument to c++ type
  ObjectHandler::property_t FixingDaysCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[7]).FromJust()));

  // convert js argument to c++ type
  bool IsInArrearsCpp = Nan::To<bool>(info[8]).FromJust();

  // convert js argument to c++ type
  String::Utf8Value strDayCounter(info[9]->ToString());
  string DayCounterCpp(strdup(*strDayCounter));

  // convert js argument to c++ type
  std::vector<double>FloorsCpp;

  Local<Array> FloorsArray = info[10].As<Array>();
  for (unsigned int i = 0; i < FloorsArray->Length(); i++){
    FloorsCpp.push_back(Nan::To<double>(Nan::Get(FloorsArray, i).ToLocalChecked()).FromJust());
  }

  // convert js argument to c++ type
  std::vector<double>GearingsCpp;

  Local<Array> GearingsArray = info[11].As<Array>();
  for (unsigned int i = 0; i < GearingsArray->Length(); i++){
    GearingsCpp.push_back(Nan::To<double>(Nan::Get(GearingsArray, i).ToLocalChecked()).FromJust());
  }

  // convert js argument to c++ type
  String::Utf8Value strSwapIndex(info[12]->ToString());
  string SwapIndexCpp(strdup(*strSwapIndex));

  // convert js argument to c++ type
  std::vector<double>SpreadsCpp;

  Local<Array> SpreadsArray = info[13].As<Array>();
  for (unsigned int i = 0; i < SpreadsArray->Length(); i++){
    SpreadsCpp.push_back(Nan::To<double>(Nan::Get(SpreadsArray, i).ToLocalChecked()).FromJust());
  }

  // convert js argument to c++ type
  std::vector<double>CapsCpp;

  Local<Array> CapsArray = info[14].As<Array>();
  for (unsigned int i = 0; i < CapsArray->Length(); i++){
    CapsCpp.push_back(Nan::To<double>(Nan::Get(CapsArray, i).ToLocalChecked()).FromJust());
  }

  // convert js argument to c++ type
  double RedemptionCpp = Nan::To<double>(info[15]).FromJust();

  // convert js argument to c++ type
  ObjectHandler::property_t IssueDateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[16]).FromJust()));

 
  // launch worker
  CmsRateBondWorker* worker = new CmsRateBondWorker(
    ObjectIDCpp
,     DescriptionCpp
,     CurrencyCpp
,     SettlementDaysCpp
,     PaymentBDCCpp
,     FaceAmountCpp
,     ScheduleIDCpp
,     FixingDaysCpp
,     IsInArrearsCpp
,     DayCounterCpp
,     FloorsCpp
,     GearingsCpp
,     SwapIndexCpp
,     SpreadsCpp
,     CapsCpp
,     RedemptionCpp
,     IssueDateCpp
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

void ZeroCouponBondWorker::Execute(){

  try{

  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::Currency CurrencyEnum =
      ObjectHandler::Create<QuantLib::Currency>()(mCurrency);


  // convert input datatypes to QuantLib datatypes
  QuantLib::Size SettlementDaysLib;
  QuantLibAddin::cppToLibrary(mSettlementDays, SettlementDaysLib);


  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::Calendar CalendarEnum =
      ObjectHandler::Create<QuantLib::Calendar>()(mCalendar);


  // convert input datatypes to QuantLib datatypes

  // convert input datatypes to QuantLib datatypes
  QuantLib::Date MaturityLib = ObjectHandler::convert2<QuantLib::Date>(
      mMaturity, "Maturity");


  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::BusinessDayConvention PaymentBDCEnum =
      ObjectHandler::Create<QuantLib::BusinessDayConvention>()(mPaymentBDC);


  // convert input datatypes to QuantLib datatypes

  // convert input datatypes to QuantLib datatypes
  QuantLib::Date IssueDateLib = ObjectHandler::convert2<QuantLib::Date>(
      mIssueDate, "IssueDate");

 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlZeroCouponBond(
          mObjectID,
          mDescription,
          mCurrency,
          mSettlementDays,
          mCalendar,
          mFaceAmount,
          mMaturity,
          mPaymentBDC,
          mRedemption,
          mIssueDate,
          false
      ));

    // Construct the Object
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::ZeroCouponBond(
          valueObject,
          mDescription,
          CurrencyEnum,
          SettlementDaysLib,
          CalendarEnum,
          mFaceAmount,
          MaturityLib,
          PaymentBDCEnum,
          mRedemption,
          IssueDateLib,
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

NAN_METHOD(QuantLibXL::ZeroCouponBond) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsString()) {
      return Nan::ThrowError("Description is required.");
  }
  if (info.Length() == 2 || !info[2]->IsString()) {
      return Nan::ThrowError("Currency is required.");
  }
  if (info.Length() == 3 || !info[3]->IsNumber()) {
      return Nan::ThrowError("SettlementDays is required.");
  }
  if (info.Length() == 4 || !info[4]->IsString()) {
      return Nan::ThrowError("Calendar is required.");
  }
  if (info.Length() == 5 || !info[5]->IsNumber()) {
      return Nan::ThrowError("FaceAmount is required.");
  }
  if (info.Length() == 7 || !info[7]->IsString()) {
      return Nan::ThrowError("PaymentBDC is required.");
  }
  if (info.Length() == 8 || !info[8]->IsNumber()) {
      return Nan::ThrowError("Redemption is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  String::Utf8Value strDescription(info[1]->ToString());
  string DescriptionCpp(strdup(*strDescription));

  // convert js argument to c++ type
  String::Utf8Value strCurrency(info[2]->ToString());
  string CurrencyCpp(strdup(*strCurrency));

  // convert js argument to c++ type
  long SettlementDaysCpp = Nan::To<int32_t>(info[3]).FromJust();

  // convert js argument to c++ type
  String::Utf8Value strCalendar(info[4]->ToString());
  string CalendarCpp(strdup(*strCalendar));

  // convert js argument to c++ type
  double FaceAmountCpp = Nan::To<double>(info[5]).FromJust();

  // convert js argument to c++ type
  ObjectHandler::property_t MaturityCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[6]).FromJust()));

  // convert js argument to c++ type
  String::Utf8Value strPaymentBDC(info[7]->ToString());
  string PaymentBDCCpp(strdup(*strPaymentBDC));

  // convert js argument to c++ type
  double RedemptionCpp = Nan::To<double>(info[8]).FromJust();

  // convert js argument to c++ type
  ObjectHandler::property_t IssueDateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[9]).FromJust()));

 
  // launch worker
  ZeroCouponBondWorker* worker = new ZeroCouponBondWorker(
    ObjectIDCpp
,     DescriptionCpp
,     CurrencyCpp
,     SettlementDaysCpp
,     CalendarCpp
,     FaceAmountCpp
,     MaturityCpp
,     PaymentBDCCpp
,     RedemptionCpp
,     IssueDateCpp
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

void BondWorker::Execute(){

  try{

  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::Currency CurrencyEnum =
      ObjectHandler::Create<QuantLib::Currency>()(mCurrency);


  // convert input datatypes to QuantLib datatypes
  QuantLib::Size SettlementDaysLib;
  QuantLibAddin::cppToLibrary(mSettlementDays, SettlementDaysLib);


  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::Calendar CalendarEnum =
      ObjectHandler::Create<QuantLib::Calendar>()(mCalendar);


  // convert input datatypes to QuantLib datatypes

  // convert input datatypes to QuantLib datatypes
  QuantLib::Date MaturityDateLib = ObjectHandler::convert2<QuantLib::Date>(
      mMaturityDate, "MaturityDate");


  // convert input datatypes to QuantLib datatypes
  QuantLib::Date IssueDateLib = ObjectHandler::convert2<QuantLib::Date>(
      mIssueDate, "IssueDate");


  // convert object IDs into library objects
  OH_GET_UNDERLYING(LegIDLibObj, mLegID,
      QuantLibAddin::Leg, QuantLib::Leg)

 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlBond(
          mObjectID,
          mDescription,
          mCurrency,
          mSettlementDays,
          mCalendar,
          mFaceAmount,
          mMaturityDate,
          mIssueDate,
          mLegID,
          false
      ));

    // Construct the Object
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::Bond(
          valueObject,
          mDescription,
          CurrencyEnum,
          SettlementDaysLib,
          CalendarEnum,
          mFaceAmount,
          MaturityDateLib,
          IssueDateLib,
          LegIDLibObj,
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

NAN_METHOD(QuantLibXL::Bond) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsString()) {
      return Nan::ThrowError("Description is required.");
  }
  if (info.Length() == 2 || !info[2]->IsString()) {
      return Nan::ThrowError("Currency is required.");
  }
  if (info.Length() == 3 || !info[3]->IsNumber()) {
      return Nan::ThrowError("SettlementDays is required.");
  }
  if (info.Length() == 4 || !info[4]->IsString()) {
      return Nan::ThrowError("Calendar is required.");
  }
  if (info.Length() == 5 || !info[5]->IsNumber()) {
      return Nan::ThrowError("FaceAmount is required.");
  }
  if (info.Length() == 8 || !info[8]->IsString()) {
      return Nan::ThrowError("LegID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  String::Utf8Value strDescription(info[1]->ToString());
  string DescriptionCpp(strdup(*strDescription));

  // convert js argument to c++ type
  String::Utf8Value strCurrency(info[2]->ToString());
  string CurrencyCpp(strdup(*strCurrency));

  // convert js argument to c++ type
  long SettlementDaysCpp = Nan::To<int32_t>(info[3]).FromJust();

  // convert js argument to c++ type
  String::Utf8Value strCalendar(info[4]->ToString());
  string CalendarCpp(strdup(*strCalendar));

  // convert js argument to c++ type
  double FaceAmountCpp = Nan::To<double>(info[5]).FromJust();

  // convert js argument to c++ type
  ObjectHandler::property_t MaturityDateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[6]).FromJust()));

  // convert js argument to c++ type
  ObjectHandler::property_t IssueDateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[7]).FromJust()));

  // convert js argument to c++ type
  String::Utf8Value strLegID(info[8]->ToString());
  string LegIDCpp(strdup(*strLegID));

 
  // launch worker
  BondWorker* worker = new BondWorker(
    ObjectIDCpp
,     DescriptionCpp
,     CurrencyCpp
,     SettlementDaysCpp
,     CalendarCpp
,     FaceAmountCpp
,     MaturityDateCpp
,     IssueDateCpp
,     LegIDCpp
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

void BondSettlementDaysWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::Bond, QuantLib::Bond)


  // invoke the member function
  QuantLib::Natural returnValue = ObjectIDLibObjPtr->settlementDays(
      );


  mReturnValue = QuantLibAddin::libraryToScalar(returnValue);

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::BondSettlementDays) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  BondSettlementDaysWorker* worker = new BondSettlementDaysWorker(
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

void BondCalendarWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::Bond, QuantLib::Bond)


  // invoke the member function
  QuantLib::Calendar returnValue = ObjectIDLibObjPtr->calendar(
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

NAN_METHOD(QuantLibXL::BondCalendar) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  BondCalendarWorker* worker = new BondCalendarWorker(
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

void BondNotionalsWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::Bond, QuantLib::Bond)


  // loop on the input parameter and populate the return vector
  std::vector<QuantLib::Real> returnValue = ObjectIDLibObjPtr->notionals(
      );


  mReturnValue = QuantLibAddin::libraryToVector(returnValue);

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::BondNotionals) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  BondNotionalsWorker* worker = new BondNotionalsWorker(
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

void BondNotionalWorker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes
  QuantLib::Date SettlementDateLib = ObjectHandler::convert2<QuantLib::Date>(
      mSettlementDate, "SettlementDate");

       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::Bond, QuantLib::Bond)


  // invoke the member function
  QuantLib::Real returnValue = ObjectIDLibObjPtr->notional(
        SettlementDateLib
       );


  mReturnValue = returnValue;

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::BondNotional) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  ObjectHandler::property_t SettlementDateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[1]).FromJust()));

 
  // launch worker
  BondNotionalWorker* worker = new BondNotionalWorker(
    ObjectIDCpp
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

void BondMaturityDateWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::Bond, QuantLib::Bond)


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

NAN_METHOD(QuantLibXL::BondMaturityDate) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  BondMaturityDateWorker* worker = new BondMaturityDateWorker(
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

void BondIssueDateWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::Bond, QuantLib::Bond)


  // invoke the member function
  QuantLib::Date returnValue = ObjectIDLibObjPtr->issueDate(
      );


  mReturnValue = QuantLibAddin::libraryToScalar(returnValue);

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::BondIssueDate) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  BondIssueDateWorker* worker = new BondIssueDateWorker(
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

void BondIsTradableWorker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes
  QuantLib::Date SettlementDateLib = ObjectHandler::convert2<QuantLib::Date>(
      mSettlementDate, "SettlementDate");

       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::Bond, QuantLib::Bond)


  // invoke the member function
  mReturnValue = ObjectIDLibObjPtr->isTradable(
        SettlementDateLib
       );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::BondIsTradable) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  ObjectHandler::property_t SettlementDateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[1]).FromJust()));

 
  // launch worker
  BondIsTradableWorker* worker = new BondIsTradableWorker(
    ObjectIDCpp
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

void BondSettlementDateWorker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes
  QuantLib::Date EvaluationDateLib = ObjectHandler::convert2<QuantLib::Date>(
      mEvaluationDate, "EvaluationDate");

       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::Bond, QuantLib::Bond)


  // invoke the member function
  QuantLib::Date returnValue = ObjectIDLibObjPtr->settlementDate(
        EvaluationDateLib
       );


  mReturnValue = QuantLibAddin::libraryToScalar(returnValue);

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::BondSettlementDate) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  ObjectHandler::property_t EvaluationDateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[1]).FromJust()));

 
  // launch worker
  BondSettlementDateWorker* worker = new BondSettlementDateWorker(
    ObjectIDCpp
,     EvaluationDateCpp
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

void BondCleanPriceWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::Bond, QuantLib::Bond)


  // invoke the member function
  mReturnValue = ObjectIDLibObjPtr->cleanPrice(
      );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::BondCleanPrice) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  BondCleanPriceWorker* worker = new BondCleanPriceWorker(
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

void BondDescriptionWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_OBJECT(ObjectIDObjPtr, mObjectID, QuantLibAddin::Bond)


  // invoke the member function
  mReturnValue = ObjectIDObjPtr->description(
      );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::BondDescription) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  BondDescriptionWorker* worker = new BondDescriptionWorker(
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

void BondCurrencyWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_OBJECT(ObjectIDObjPtr, mObjectID, QuantLibAddin::Bond)


  // invoke the member function
  mReturnValue = ObjectIDObjPtr->currency(
      );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::BondCurrency) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  BondCurrencyWorker* worker = new BondCurrencyWorker(
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

void BondRedemptionAmountWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_OBJECT(ObjectIDObjPtr, mObjectID, QuantLibAddin::Bond)


  // invoke the member function
  QuantLib::Real returnValue = ObjectIDObjPtr->redemptionAmount(
      );


  mReturnValue = returnValue;

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::BondRedemptionAmount) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  BondRedemptionAmountWorker* worker = new BondRedemptionAmountWorker(
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

void BondRedemptionDateWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_OBJECT(ObjectIDObjPtr, mObjectID, QuantLibAddin::Bond)


  // invoke the member function
  QuantLib::Date returnValue = ObjectIDObjPtr->redemptionDate(
      );


  mReturnValue = QuantLibAddin::libraryToScalar(returnValue);

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::BondRedemptionDate) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  BondRedemptionDateWorker* worker = new BondRedemptionDateWorker(
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

void BondFlowAnalysisWorker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes
  QuantLib::Date AfterDateLib = ObjectHandler::convert2<QuantLib::Date>(
      mAfterDate, "AfterDate");

       // convert object IDs into library objects
  OH_GET_OBJECT(ObjectIDObjPtr, mObjectID, QuantLibAddin::Bond)

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

NAN_METHOD(QuantLibXL::BondFlowAnalysis) {

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
  BondFlowAnalysisWorker* worker = new BondFlowAnalysisWorker(
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

void BondSetCouponPricerWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_REFERENCE(FloatingRateCouponPricerLibObjPtr, mFloatingRateCouponPricer,
      QuantLibAddin::FloatingRateCouponPricer, QuantLib::FloatingRateCouponPricer)

       // convert object IDs into library objects
  OH_GET_OBJECT(ObjectIDObjPtr, mObjectID, QuantLibAddin::Bond)


  // invoke the member function
  ObjectIDObjPtr->setCouponPricer(
        FloatingRateCouponPricerLibObjPtr
       );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::BondSetCouponPricer) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsString()) {
      return Nan::ThrowError("FloatingRateCouponPricer is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  String::Utf8Value strFloatingRateCouponPricer(info[1]->ToString());
  string FloatingRateCouponPricerCpp(strdup(*strFloatingRateCouponPricer));

 
  // launch worker
  BondSetCouponPricerWorker* worker = new BondSetCouponPricerWorker(
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

void BondSetCouponPricersWorker::Execute(){

  try{

  // convert object IDs into library objects
  std::vector< boost::shared_ptr<QuantLib::FloatingRateCouponPricer> > FloatingRateCouponPricerLibObjPtr =
      ObjectHandler::getLibraryObjectVector<QuantLibAddin::FloatingRateCouponPricer, QuantLib::FloatingRateCouponPricer>(mFloatingRateCouponPricer);

       // convert object IDs into library objects
  OH_GET_OBJECT(ObjectIDObjPtr, mObjectID, QuantLibAddin::Bond)


  // invoke the member function
  ObjectIDObjPtr->setCouponPricers(
        FloatingRateCouponPricerLibObjPtr
       );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::BondSetCouponPricers) {

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
  BondSetCouponPricersWorker* worker = new BondSetCouponPricersWorker(
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

void BondStartDateWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_UNDERLYING(ObjectIdLibObj, mObjectId,
      QuantLibAddin::Bond, QuantLib::Bond)

       // invoke the utility function
  QuantLib::Date returnValue = QuantLib::BondFunctions::startDate(
      ObjectIdLibObj
     );

  mReturnValue = QuantLibAddin::libraryToScalar(returnValue);

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::BondStartDate) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectId is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectId(info[0]->ToString());
  string ObjectIdCpp(strdup(*strObjectId));

 
  // launch worker
  BondStartDateWorker* worker = new BondStartDateWorker(
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

void BondPreviousCashFlowDateWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_UNDERLYING(ObjectIdLibObj, mObjectId,
      QuantLibAddin::Bond, QuantLib::Bond)


  // convert input datatypes to QuantLib datatypes
  QuantLib::Date SettlementDateLib = ObjectHandler::convert2<QuantLib::Date>(
      mSettlementDate, "SettlementDate");

       // invoke the utility function
  QuantLib::Date returnValue = QuantLib::BondFunctions::previousCashFlowDate(
      ObjectIdLibObj
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

NAN_METHOD(QuantLibXL::BondPreviousCashFlowDate) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectId is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectId(info[0]->ToString());
  string ObjectIdCpp(strdup(*strObjectId));

  // convert js argument to c++ type
  ObjectHandler::property_t SettlementDateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[1]).FromJust()));

 
  // launch worker
  BondPreviousCashFlowDateWorker* worker = new BondPreviousCashFlowDateWorker(
    ObjectIdCpp
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

void BondNextCashFlowDateWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_UNDERLYING(ObjectIdLibObj, mObjectId,
      QuantLibAddin::Bond, QuantLib::Bond)


  // convert input datatypes to QuantLib datatypes
  QuantLib::Date SettlementDateLib = ObjectHandler::convert2<QuantLib::Date>(
      mSettlementDate, "SettlementDate");

       // invoke the utility function
  QuantLib::Date returnValue = QuantLib::BondFunctions::nextCashFlowDate(
      ObjectIdLibObj
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

NAN_METHOD(QuantLibXL::BondNextCashFlowDate) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectId is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectId(info[0]->ToString());
  string ObjectIdCpp(strdup(*strObjectId));

  // convert js argument to c++ type
  ObjectHandler::property_t SettlementDateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[1]).FromJust()));

 
  // launch worker
  BondNextCashFlowDateWorker* worker = new BondNextCashFlowDateWorker(
    ObjectIdCpp
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

void BondPreviousCashFlowAmountWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_UNDERLYING(ObjectIdLibObj, mObjectId,
      QuantLibAddin::Bond, QuantLib::Bond)


  // convert input datatypes to QuantLib datatypes
  QuantLib::Date SettlementDateLib = ObjectHandler::convert2<QuantLib::Date>(
      mSettlementDate, "SettlementDate");

       // invoke the utility function
  QuantLib::Real returnValue = QuantLib::BondFunctions::previousCashFlowAmount(
      ObjectIdLibObj
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

NAN_METHOD(QuantLibXL::BondPreviousCashFlowAmount) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectId is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectId(info[0]->ToString());
  string ObjectIdCpp(strdup(*strObjectId));

  // convert js argument to c++ type
  ObjectHandler::property_t SettlementDateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[1]).FromJust()));

 
  // launch worker
  BondPreviousCashFlowAmountWorker* worker = new BondPreviousCashFlowAmountWorker(
    ObjectIdCpp
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

void BondNextCashFlowAmountWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_UNDERLYING(ObjectIdLibObj, mObjectId,
      QuantLibAddin::Bond, QuantLib::Bond)


  // convert input datatypes to QuantLib datatypes
  QuantLib::Date SettlementDateLib = ObjectHandler::convert2<QuantLib::Date>(
      mSettlementDate, "SettlementDate");

       // invoke the utility function
  QuantLib::Real returnValue = QuantLib::BondFunctions::nextCashFlowAmount(
      ObjectIdLibObj
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

NAN_METHOD(QuantLibXL::BondNextCashFlowAmount) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectId is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectId(info[0]->ToString());
  string ObjectIdCpp(strdup(*strObjectId));

  // convert js argument to c++ type
  ObjectHandler::property_t SettlementDateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[1]).FromJust()));

 
  // launch worker
  BondNextCashFlowAmountWorker* worker = new BondNextCashFlowAmountWorker(
    ObjectIdCpp
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

void BondPreviousCouponRateWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_UNDERLYING(ObjectIdLibObj, mObjectId,
      QuantLibAddin::Bond, QuantLib::Bond)


  // convert input datatypes to QuantLib datatypes
  QuantLib::Date SettlementDateLib = ObjectHandler::convert2<QuantLib::Date>(
      mSettlementDate, "SettlementDate");

       // invoke the utility function
  mReturnValue = QuantLib::BondFunctions::previousCouponRate(
      ObjectIdLibObj
      ,
       SettlementDateLib
     );
   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::BondPreviousCouponRate) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectId is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectId(info[0]->ToString());
  string ObjectIdCpp(strdup(*strObjectId));

  // convert js argument to c++ type
  ObjectHandler::property_t SettlementDateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[1]).FromJust()));

 
  // launch worker
  BondPreviousCouponRateWorker* worker = new BondPreviousCouponRateWorker(
    ObjectIdCpp
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

void BondNextCouponRateWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_UNDERLYING(ObjectIdLibObj, mObjectId,
      QuantLibAddin::Bond, QuantLib::Bond)


  // convert input datatypes to QuantLib datatypes
  QuantLib::Date SettlementDateLib = ObjectHandler::convert2<QuantLib::Date>(
      mSettlementDate, "SettlementDate");

       // invoke the utility function
  mReturnValue = QuantLib::BondFunctions::nextCouponRate(
      ObjectIdLibObj
      ,
       SettlementDateLib
     );
   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::BondNextCouponRate) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectId is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectId(info[0]->ToString());
  string ObjectIdCpp(strdup(*strObjectId));

  // convert js argument to c++ type
  ObjectHandler::property_t SettlementDateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[1]).FromJust()));

 
  // launch worker
  BondNextCouponRateWorker* worker = new BondNextCouponRateWorker(
    ObjectIdCpp
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

void BondAccrualStartDateWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_UNDERLYING(ObjectIdLibObj, mObjectId,
      QuantLibAddin::Bond, QuantLib::Bond)


  // convert input datatypes to QuantLib datatypes
  QuantLib::Date SettlementDateLib = ObjectHandler::convert2<QuantLib::Date>(
      mSettlementDate, "SettlementDate");

       // invoke the utility function
  QuantLib::Date returnValue = QuantLib::BondFunctions::accrualStartDate(
      ObjectIdLibObj
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

NAN_METHOD(QuantLibXL::BondAccrualStartDate) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectId is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectId(info[0]->ToString());
  string ObjectIdCpp(strdup(*strObjectId));

  // convert js argument to c++ type
  ObjectHandler::property_t SettlementDateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[1]).FromJust()));

 
  // launch worker
  BondAccrualStartDateWorker* worker = new BondAccrualStartDateWorker(
    ObjectIdCpp
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

void BondAccrualEndDateWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_UNDERLYING(ObjectIdLibObj, mObjectId,
      QuantLibAddin::Bond, QuantLib::Bond)


  // convert input datatypes to QuantLib datatypes
  QuantLib::Date SettlementDateLib = ObjectHandler::convert2<QuantLib::Date>(
      mSettlementDate, "SettlementDate");

       // invoke the utility function
  QuantLib::Date returnValue = QuantLib::BondFunctions::accrualEndDate(
      ObjectIdLibObj
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

NAN_METHOD(QuantLibXL::BondAccrualEndDate) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectId is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectId(info[0]->ToString());
  string ObjectIdCpp(strdup(*strObjectId));

  // convert js argument to c++ type
  ObjectHandler::property_t SettlementDateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[1]).FromJust()));

 
  // launch worker
  BondAccrualEndDateWorker* worker = new BondAccrualEndDateWorker(
    ObjectIdCpp
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

void BondReferencePeriodStartWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_UNDERLYING(ObjectIdLibObj, mObjectId,
      QuantLibAddin::Bond, QuantLib::Bond)


  // convert input datatypes to QuantLib datatypes
  QuantLib::Date SettlementDateLib = ObjectHandler::convert2<QuantLib::Date>(
      mSettlementDate, "SettlementDate");

       // invoke the utility function
  QuantLib::Date returnValue = QuantLib::BondFunctions::referencePeriodStart(
      ObjectIdLibObj
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

NAN_METHOD(QuantLibXL::BondReferencePeriodStart) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectId is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectId(info[0]->ToString());
  string ObjectIdCpp(strdup(*strObjectId));

  // convert js argument to c++ type
  ObjectHandler::property_t SettlementDateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[1]).FromJust()));

 
  // launch worker
  BondReferencePeriodStartWorker* worker = new BondReferencePeriodStartWorker(
    ObjectIdCpp
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

void BondReferencePeriodEndWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_UNDERLYING(ObjectIdLibObj, mObjectId,
      QuantLibAddin::Bond, QuantLib::Bond)


  // convert input datatypes to QuantLib datatypes
  QuantLib::Date SettlementDateLib = ObjectHandler::convert2<QuantLib::Date>(
      mSettlementDate, "SettlementDate");

       // invoke the utility function
  QuantLib::Date returnValue = QuantLib::BondFunctions::referencePeriodEnd(
      ObjectIdLibObj
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

NAN_METHOD(QuantLibXL::BondReferencePeriodEnd) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectId is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectId(info[0]->ToString());
  string ObjectIdCpp(strdup(*strObjectId));

  // convert js argument to c++ type
  ObjectHandler::property_t SettlementDateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[1]).FromJust()));

 
  // launch worker
  BondReferencePeriodEndWorker* worker = new BondReferencePeriodEndWorker(
    ObjectIdCpp
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

void BondAccrualPeriodWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_UNDERLYING(ObjectIdLibObj, mObjectId,
      QuantLibAddin::Bond, QuantLib::Bond)


  // convert input datatypes to QuantLib datatypes
  QuantLib::Date SettlementDateLib = ObjectHandler::convert2<QuantLib::Date>(
      mSettlementDate, "SettlementDate");

       // invoke the utility function
  mReturnValue = QuantLib::BondFunctions::accrualPeriod(
      ObjectIdLibObj
      ,
       SettlementDateLib
     );
   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::BondAccrualPeriod) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectId is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectId(info[0]->ToString());
  string ObjectIdCpp(strdup(*strObjectId));

  // convert js argument to c++ type
  ObjectHandler::property_t SettlementDateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[1]).FromJust()));

 
  // launch worker
  BondAccrualPeriodWorker* worker = new BondAccrualPeriodWorker(
    ObjectIdCpp
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

void BondAccrualDaysWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_UNDERLYING(ObjectIdLibObj, mObjectId,
      QuantLibAddin::Bond, QuantLib::Bond)


  // convert input datatypes to QuantLib datatypes
  QuantLib::Date SettlementDateLib = ObjectHandler::convert2<QuantLib::Date>(
      mSettlementDate, "SettlementDate");

       // invoke the utility function
  mReturnValue = QuantLib::BondFunctions::accrualDays(
      ObjectIdLibObj
      ,
       SettlementDateLib
     );
   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::BondAccrualDays) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectId is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectId(info[0]->ToString());
  string ObjectIdCpp(strdup(*strObjectId));

  // convert js argument to c++ type
  ObjectHandler::property_t SettlementDateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[1]).FromJust()));

 
  // launch worker
  BondAccrualDaysWorker* worker = new BondAccrualDaysWorker(
    ObjectIdCpp
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

void BondAccruedPeriodWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_UNDERLYING(ObjectIdLibObj, mObjectId,
      QuantLibAddin::Bond, QuantLib::Bond)


  // convert input datatypes to QuantLib datatypes
  QuantLib::Date SettlementDateLib = ObjectHandler::convert2<QuantLib::Date>(
      mSettlementDate, "SettlementDate");

       // invoke the utility function
  mReturnValue = QuantLib::BondFunctions::accruedPeriod(
      ObjectIdLibObj
      ,
       SettlementDateLib
     );
   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::BondAccruedPeriod) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectId is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectId(info[0]->ToString());
  string ObjectIdCpp(strdup(*strObjectId));

  // convert js argument to c++ type
  ObjectHandler::property_t SettlementDateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[1]).FromJust()));

 
  // launch worker
  BondAccruedPeriodWorker* worker = new BondAccruedPeriodWorker(
    ObjectIdCpp
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

void BondAccruedDaysWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_UNDERLYING(ObjectIdLibObj, mObjectId,
      QuantLibAddin::Bond, QuantLib::Bond)


  // convert input datatypes to QuantLib datatypes
  QuantLib::Date SettlementDateLib = ObjectHandler::convert2<QuantLib::Date>(
      mSettlementDate, "SettlementDate");

       // invoke the utility function
  mReturnValue = QuantLib::BondFunctions::accruedDays(
      ObjectIdLibObj
      ,
       SettlementDateLib
     );
   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::BondAccruedDays) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectId is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectId(info[0]->ToString());
  string ObjectIdCpp(strdup(*strObjectId));

  // convert js argument to c++ type
  ObjectHandler::property_t SettlementDateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[1]).FromJust()));

 
  // launch worker
  BondAccruedDaysWorker* worker = new BondAccruedDaysWorker(
    ObjectIdCpp
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

void BondAccruedAmountWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_UNDERLYING(ObjectIdLibObj, mObjectId,
      QuantLibAddin::Bond, QuantLib::Bond)


  // convert input datatypes to QuantLib datatypes
  QuantLib::Date SettlementDateLib = ObjectHandler::convert2<QuantLib::Date>(
      mSettlementDate, "SettlementDate");

       // invoke the utility function
  mReturnValue = QuantLib::BondFunctions::accruedAmount(
      ObjectIdLibObj
      ,
       SettlementDateLib
     );
   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::BondAccruedAmount) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectId is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectId(info[0]->ToString());
  string ObjectIdCpp(strdup(*strObjectId));

  // convert js argument to c++ type
  ObjectHandler::property_t SettlementDateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[1]).FromJust()));

 
  // launch worker
  BondAccruedAmountWorker* worker = new BondAccruedAmountWorker(
    ObjectIdCpp
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

void BondCleanPriceFromYieldTermStructureWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_UNDERLYING(ObjectIdLibObj, mObjectId,
      QuantLibAddin::Bond, QuantLib::Bond)


  // convert object IDs into library objects
  OH_GET_UNDERLYING(YieldCurveLibObj, mYieldCurve,
      QuantLibAddin::YieldTermStructure, QuantLib::YieldTermStructure)


  // convert input datatypes to QuantLib datatypes
  QuantLib::Date SettlementDateLib = ObjectHandler::convert2<QuantLib::Date>(
      mSettlementDate, "SettlementDate");

       // invoke the utility function
  QuantLib::Real returnValue = QuantLib::BondFunctions::cleanPrice(
      ObjectIdLibObj
      ,
       YieldCurveLibObj
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

NAN_METHOD(QuantLibXL::BondCleanPriceFromYieldTermStructure) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectId is required.");
  }
  if (info.Length() == 1 || !info[1]->IsString()) {
      return Nan::ThrowError("YieldCurve is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectId(info[0]->ToString());
  string ObjectIdCpp(strdup(*strObjectId));

  // convert js argument to c++ type
  String::Utf8Value strYieldCurve(info[1]->ToString());
  string YieldCurveCpp(strdup(*strYieldCurve));

  // convert js argument to c++ type
  ObjectHandler::property_t SettlementDateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[2]).FromJust()));

 
  // launch worker
  BondCleanPriceFromYieldTermStructureWorker* worker = new BondCleanPriceFromYieldTermStructureWorker(
    ObjectIdCpp
,     YieldCurveCpp
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

void BondBpsFromYieldTermStructureWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_UNDERLYING(ObjectIdLibObj, mObjectId,
      QuantLibAddin::Bond, QuantLib::Bond)


  // convert object IDs into library objects
  OH_GET_UNDERLYING(YieldCurveLibObj, mYieldCurve,
      QuantLibAddin::YieldTermStructure, QuantLib::YieldTermStructure)


  // convert input datatypes to QuantLib datatypes
  QuantLib::Date SettlementDateLib = ObjectHandler::convert2<QuantLib::Date>(
      mSettlementDate, "SettlementDate");

       // invoke the utility function
  QuantLib::Real returnValue = QuantLib::BondFunctions::bps(
      ObjectIdLibObj
      ,
       YieldCurveLibObj
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

NAN_METHOD(QuantLibXL::BondBpsFromYieldTermStructure) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectId is required.");
  }
  if (info.Length() == 1 || !info[1]->IsString()) {
      return Nan::ThrowError("YieldCurve is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectId(info[0]->ToString());
  string ObjectIdCpp(strdup(*strObjectId));

  // convert js argument to c++ type
  String::Utf8Value strYieldCurve(info[1]->ToString());
  string YieldCurveCpp(strdup(*strYieldCurve));

  // convert js argument to c++ type
  ObjectHandler::property_t SettlementDateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[2]).FromJust()));

 
  // launch worker
  BondBpsFromYieldTermStructureWorker* worker = new BondBpsFromYieldTermStructureWorker(
    ObjectIdCpp
,     YieldCurveCpp
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

void BondAtmRateFromYieldTermStructureWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_UNDERLYING(ObjectIdLibObj, mObjectId,
      QuantLibAddin::Bond, QuantLib::Bond)


  // convert object IDs into library objects
  OH_GET_UNDERLYING(YieldCurveLibObj, mYieldCurve,
      QuantLibAddin::YieldTermStructure, QuantLib::YieldTermStructure)


  // convert input datatypes to QuantLib datatypes
  QuantLib::Date SettlementDateLib = ObjectHandler::convert2<QuantLib::Date>(
      mSettlementDate, "SettlementDate");


  // convert input datatypes to QuantLib datatypes
       // invoke the utility function
  QuantLib::Real returnValue = QuantLib::BondFunctions::atmRate(
      ObjectIdLibObj
      ,
       YieldCurveLibObj
      ,
       SettlementDateLib
      ,
       mCleanPrice
     );

  mReturnValue = returnValue;

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::BondAtmRateFromYieldTermStructure) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectId is required.");
  }
  if (info.Length() == 1 || !info[1]->IsString()) {
      return Nan::ThrowError("YieldCurve is required.");
  }
  if (info.Length() == 3 || !info[3]->IsNumber()) {
      return Nan::ThrowError("CleanPrice is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectId(info[0]->ToString());
  string ObjectIdCpp(strdup(*strObjectId));

  // convert js argument to c++ type
  String::Utf8Value strYieldCurve(info[1]->ToString());
  string YieldCurveCpp(strdup(*strYieldCurve));

  // convert js argument to c++ type
  ObjectHandler::property_t SettlementDateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[2]).FromJust()));

  // convert js argument to c++ type
  double CleanPriceCpp = Nan::To<double>(info[3]).FromJust();

 
  // launch worker
  BondAtmRateFromYieldTermStructureWorker* worker = new BondAtmRateFromYieldTermStructureWorker(
    ObjectIdCpp
,     YieldCurveCpp
,     SettlementDateCpp
,     CleanPriceCpp
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

void BondCleanPriceFromYieldWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_UNDERLYING(ObjectIdLibObj, mObjectId,
      QuantLibAddin::Bond, QuantLib::Bond)


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

       // invoke the utility function
  QuantLib::Real returnValue = QuantLib::BondFunctions::cleanPrice(
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
       SettlementDateLib
     );

  mReturnValue = returnValue;

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::BondCleanPriceFromYield) {

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
  ObjectHandler::property_t SettlementDateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[5]).FromJust()));

 
  // launch worker
  BondCleanPriceFromYieldWorker* worker = new BondCleanPriceFromYieldWorker(
    ObjectIdCpp
,     YieldCpp
,     DayCounterCpp
,     CompoundingCpp
,     FrequencyCpp
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

void BondDirtyPriceFromYieldWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_UNDERLYING(ObjectIdLibObj, mObjectId,
      QuantLibAddin::Bond, QuantLib::Bond)


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

       // invoke the utility function
  QuantLib::Real returnValue = QuantLib::BondFunctions::dirtyPrice(
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
       SettlementDateLib
     );

  mReturnValue = returnValue;

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::BondDirtyPriceFromYield) {

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
  ObjectHandler::property_t SettlementDateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[5]).FromJust()));

 
  // launch worker
  BondDirtyPriceFromYieldWorker* worker = new BondDirtyPriceFromYieldWorker(
    ObjectIdCpp
,     YieldCpp
,     DayCounterCpp
,     CompoundingCpp
,     FrequencyCpp
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

void BondBpsFromYieldWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_UNDERLYING(ObjectIdLibObj, mObjectId,
      QuantLibAddin::Bond, QuantLib::Bond)


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

       // invoke the utility function
  QuantLib::Real returnValue = QuantLib::BondFunctions::bps(
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
       SettlementDateLib
     );

  mReturnValue = returnValue;

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::BondBpsFromYield) {

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
  ObjectHandler::property_t SettlementDateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[5]).FromJust()));

 
  // launch worker
  BondBpsFromYieldWorker* worker = new BondBpsFromYieldWorker(
    ObjectIdCpp
,     YieldCpp
,     DayCounterCpp
,     CompoundingCpp
,     FrequencyCpp
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

void BondYieldFromCleanPriceWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_UNDERLYING(ObjectIdLibObj, mObjectId,
      QuantLibAddin::Bond, QuantLib::Bond)


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

  // convert input datatypes to QuantLib datatypes
  QuantLib::Size MaxIterationsLib;
  QuantLibAddin::cppToLibrary(mMaxIterations, MaxIterationsLib);

       // invoke the utility function
  mReturnValue = QuantLib::BondFunctions::yield(
      ObjectIdLibObj
      ,
       mCleanPrice
      ,
       DayCounterEnum
      ,
       CompoundingEnum
      ,
       FrequencyEnum
      ,
       SettlementDateLib
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

NAN_METHOD(QuantLibXL::BondYieldFromCleanPrice) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectId is required.");
  }
  if (info.Length() == 1 || !info[1]->IsNumber()) {
      return Nan::ThrowError("CleanPrice is required.");
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
  if (info.Length() == 6 || !info[6]->IsNumber()) {
      return Nan::ThrowError("Accuracy is required.");
  }
  if (info.Length() == 7 || !info[7]->IsNumber()) {
      return Nan::ThrowError("MaxIterations is required.");
  }
  if (info.Length() == 8 || !info[8]->IsNumber()) {
      return Nan::ThrowError("Guess is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectId(info[0]->ToString());
  string ObjectIdCpp(strdup(*strObjectId));

  // convert js argument to c++ type
  double CleanPriceCpp = Nan::To<double>(info[1]).FromJust();

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
  ObjectHandler::property_t SettlementDateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[5]).FromJust()));

  // convert js argument to c++ type
  double AccuracyCpp = Nan::To<double>(info[6]).FromJust();

  // convert js argument to c++ type
  long MaxIterationsCpp = Nan::To<int32_t>(info[7]).FromJust();

  // convert js argument to c++ type
  double GuessCpp = Nan::To<double>(info[8]).FromJust();

 
  // launch worker
  BondYieldFromCleanPriceWorker* worker = new BondYieldFromCleanPriceWorker(
    ObjectIdCpp
,     CleanPriceCpp
,     DayCounterCpp
,     CompoundingCpp
,     FrequencyCpp
,     SettlementDateCpp
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

void BondDurationFromYieldWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_UNDERLYING(ObjectIdLibObj, mObjectId,
      QuantLibAddin::Bond, QuantLib::Bond)


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

       // invoke the utility function
  QuantLib::Real returnValue = QuantLib::BondFunctions::duration(
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
       SettlementDateLib
     );

  mReturnValue = returnValue;

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::BondDurationFromYield) {

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
  ObjectHandler::property_t SettlementDateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[6]).FromJust()));

 
  // launch worker
  BondDurationFromYieldWorker* worker = new BondDurationFromYieldWorker(
    ObjectIdCpp
,     YieldCpp
,     DayCounterCpp
,     CompoundingCpp
,     FrequencyCpp
,     DurationTypeCpp
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

void BondConvexityFromYieldWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_UNDERLYING(ObjectIdLibObj, mObjectId,
      QuantLibAddin::Bond, QuantLib::Bond)


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

       // invoke the utility function
  QuantLib::Real returnValue = QuantLib::BondFunctions::convexity(
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
       SettlementDateLib
     );

  mReturnValue = returnValue;

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::BondConvexityFromYield) {

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
  ObjectHandler::property_t SettlementDateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[5]).FromJust()));

 
  // launch worker
  BondConvexityFromYieldWorker* worker = new BondConvexityFromYieldWorker(
    ObjectIdCpp
,     YieldCpp
,     DayCounterCpp
,     CompoundingCpp
,     FrequencyCpp
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

void BondCleanPriceFromZSpreadWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_UNDERLYING(ObjectIdLibObj, mObjectId,
      QuantLibAddin::Bond, QuantLib::Bond)


  // convert object IDs into library objects
  OH_GET_REFERENCE(YieldCurveLibObjPtr, mYieldCurve,
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

       // invoke the utility function
  QuantLib::Real returnValue = QuantLib::BondFunctions::cleanPrice(
      ObjectIdLibObj
      ,
       YieldCurveLibObjPtr
      ,
       mZSpread
      ,
       DayCounterEnum
      ,
       CompoundingEnum
      ,
       FrequencyEnum
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

NAN_METHOD(QuantLibXL::BondCleanPriceFromZSpread) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectId is required.");
  }
  if (info.Length() == 1 || !info[1]->IsString()) {
      return Nan::ThrowError("YieldCurve is required.");
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
  // convert js argument to c++ type
  String::Utf8Value strObjectId(info[0]->ToString());
  string ObjectIdCpp(strdup(*strObjectId));

  // convert js argument to c++ type
  String::Utf8Value strYieldCurve(info[1]->ToString());
  string YieldCurveCpp(strdup(*strYieldCurve));

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
  ObjectHandler::property_t SettlementDateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[6]).FromJust()));

 
  // launch worker
  BondCleanPriceFromZSpreadWorker* worker = new BondCleanPriceFromZSpreadWorker(
    ObjectIdCpp
,     YieldCurveCpp
,     ZSpreadCpp
,     DayCounterCpp
,     CompoundingCpp
,     FrequencyCpp
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

void BondZSpreadFromCleanPriceWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_UNDERLYING(ObjectIdLibObj, mObjectId,
      QuantLibAddin::Bond, QuantLib::Bond)


  // convert input datatypes to QuantLib datatypes

  // convert object IDs into library objects
  OH_GET_REFERENCE(YieldCurveLibObjPtr, mYieldCurve,
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

  // convert input datatypes to QuantLib datatypes
  QuantLib::Size MaxIterationsLib;
  QuantLibAddin::cppToLibrary(mMaxIterations, MaxIterationsLib);

       // invoke the utility function
  mReturnValue = QuantLib::BondFunctions::zSpread(
      ObjectIdLibObj
      ,
       mCleanPrice
      ,
       YieldCurveLibObjPtr
      ,
       DayCounterEnum
      ,
       CompoundingEnum
      ,
       FrequencyEnum
      ,
       SettlementDateLib
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

NAN_METHOD(QuantLibXL::BondZSpreadFromCleanPrice) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectId is required.");
  }
  if (info.Length() == 1 || !info[1]->IsNumber()) {
      return Nan::ThrowError("CleanPrice is required.");
  }
  if (info.Length() == 2 || !info[2]->IsString()) {
      return Nan::ThrowError("YieldCurve is required.");
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
  if (info.Length() == 7 || !info[7]->IsNumber()) {
      return Nan::ThrowError("Accuracy is required.");
  }
  if (info.Length() == 8 || !info[8]->IsNumber()) {
      return Nan::ThrowError("MaxIterations is required.");
  }
  if (info.Length() == 9 || !info[9]->IsNumber()) {
      return Nan::ThrowError("Guess is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectId(info[0]->ToString());
  string ObjectIdCpp(strdup(*strObjectId));

  // convert js argument to c++ type
  double CleanPriceCpp = Nan::To<double>(info[1]).FromJust();

  // convert js argument to c++ type
  String::Utf8Value strYieldCurve(info[2]->ToString());
  string YieldCurveCpp(strdup(*strYieldCurve));

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
  ObjectHandler::property_t SettlementDateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[6]).FromJust()));

  // convert js argument to c++ type
  double AccuracyCpp = Nan::To<double>(info[7]).FromJust();

  // convert js argument to c++ type
  long MaxIterationsCpp = Nan::To<int32_t>(info[8]).FromJust();

  // convert js argument to c++ type
  double GuessCpp = Nan::To<double>(info[9]).FromJust();

 
  // launch worker
  BondZSpreadFromCleanPriceWorker* worker = new BondZSpreadFromCleanPriceWorker(
    ObjectIdCpp
,     CleanPriceCpp
,     YieldCurveCpp
,     DayCounterCpp
,     CompoundingCpp
,     FrequencyCpp
,     SettlementDateCpp
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

void BondAliveWorker::Execute(){

  try{

  // convert object IDs into library objects
  std::vector< boost::shared_ptr<QuantLibAddin::Bond> > BondsObjPtr =
      ObjectHandler::getObjectVector<QuantLibAddin::Bond>(mBonds);


  // convert input datatypes to QuantLib datatypes
  QuantLib::Date RefDateLib = ObjectHandler::convert2<QuantLib::Date>(
      mRefDate, "RefDate");

       // invoke the utility function
  mReturnValue = QuantLibAddin::qlBondAlive(
      BondsObjPtr
      ,
       RefDateLib
   );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::BondAlive) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsArray()) {
      return Nan::ThrowError("Bonds is required.");
  }
  // convert js argument to c++ type
  std::vector<string>BondsCpp;

  Local<Array> BondsArray = info[0].As<Array>();
  for (unsigned int i = 0; i < BondsArray->Length(); i++){
    String::Utf8Value strBonds(Nan::Get(BondsArray, i).ToLocalChecked()->ToString());
    BondsCpp.push_back(strdup(*strBonds));
  }

  // convert js argument to c++ type
  ObjectHandler::property_t RefDateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[1]).FromJust()));

 
  // launch worker
  BondAliveWorker* worker = new BondAliveWorker(
    BondsCpp
,     RefDateCpp
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

void BondMaturityLookupWorker::Execute(){

  try{

  // convert object IDs into library objects
  std::vector< boost::shared_ptr<QuantLibAddin::Bond> > BondsObjPtr =
      ObjectHandler::getObjectVector<QuantLibAddin::Bond>(mBonds);


  // convert input datatypes to QuantLib datatypes
  QuantLib::Date MaturityLib = ObjectHandler::convert2<QuantLib::Date>(
      mMaturity, "Maturity");

       // invoke the utility function
  mReturnValue = QuantLibAddin::qlBondMaturityLookup(
      BondsObjPtr
      ,
       MaturityLib
     );
   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::BondMaturityLookup) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsArray()) {
      return Nan::ThrowError("Bonds is required.");
  }
  // convert js argument to c++ type
  std::vector<string>BondsCpp;

  Local<Array> BondsArray = info[0].As<Array>();
  for (unsigned int i = 0; i < BondsArray->Length(); i++){
    String::Utf8Value strBonds(Nan::Get(BondsArray, i).ToLocalChecked()->ToString());
    BondsCpp.push_back(strdup(*strBonds));
  }

  // convert js argument to c++ type
  ObjectHandler::property_t MaturityCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[1]).FromJust()));

 
  // launch worker
  BondMaturityLookupWorker* worker = new BondMaturityLookupWorker(
    BondsCpp
,     MaturityCpp
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

void BondMaturitySortWorker::Execute(){

  try{

  // convert object IDs into library objects
  std::vector< boost::shared_ptr<QuantLibAddin::Bond> > BondsObjPtr =
      ObjectHandler::getObjectVector<QuantLibAddin::Bond>(mBonds);

       // invoke the utility function
  mReturnValue = QuantLibAddin::qlBondMaturitySort(
      BondsObjPtr
   );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::BondMaturitySort) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsArray()) {
      return Nan::ThrowError("Bonds is required.");
  }
  // convert js argument to c++ type
  std::vector<string>BondsCpp;

  Local<Array> BondsArray = info[0].As<Array>();
  for (unsigned int i = 0; i < BondsArray->Length(); i++){
    String::Utf8Value strBonds(Nan::Get(BondsArray, i).ToLocalChecked()->ToString());
    BondsCpp.push_back(strdup(*strBonds));
  }

 
  // launch worker
  BondMaturitySortWorker* worker = new BondMaturitySortWorker(
    BondsCpp
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
 