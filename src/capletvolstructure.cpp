/* 
  Copyright (C) 2016 -2017 Jerry Jin
*/

#include <nan.h>
#include <string.h>

#include "capletvolstructure.hpp"

#include <qlo/qladdindefines.hpp>
#include <qlo/indexes/iborindex.hpp>
#include <qlo/capletvolstructure.hpp>
#include <qlo/quote.hpp>
#include <qlo/termstructures.hpp>
#include <qlo/handleimpl.hpp>
#include <ql/termstructures/volatility/optionlet/optionletvolatilitystructure.hpp>
#include <ql/termstructures/volatility/optionlet/constantoptionletvol.hpp>
#include <ql/termstructures/volatility/optionlet/optionletstripper1.hpp>
#include <ql/termstructures/volatility/optionlet/optionletstripper2.hpp>
#include <ql/termstructures/volatility/capfloor/capfloortermvolcurve.hpp>
#include <ql/termstructures/volatility/capfloor/capfloortermvolsurface.hpp>
#include <ql/indexes/iborindex.hpp>
#include <qlo/loop/loop_capletvolstructure.hpp>
 #include <oh/objecthandler.hpp>
#include <oh/conversions/getobjectvector.hpp>
#include <qlo/valueobjects/vo_all.hpp>
#include <qlo/conversions/all.hpp>
#include "../loop.hpp"


void RelinkableHandleOptionletVolatilityStructureWorker::Execute(){

  try{
 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlRelinkableHandleOptionletVolatilityStructure(
          mObjectID,
          mCurrentLink,
          false
      ));

    // Construct the Object
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::RelinkableHandleImpl<QuantLibAddin::OptionletVolatilityStructure, QuantLib::OptionletVolatilityStructure>(
          valueObject,
          mCurrentLink,
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

NAN_METHOD(QuantLibXL::RelinkableHandleOptionletVolatilityStructure) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsString()) {
      return Nan::ThrowError("CurrentLink is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  String::Utf8Value strCurrentLink(info[1]->ToString());
  string CurrentLinkCpp(strdup(*strCurrentLink));

 
  // launch worker
  RelinkableHandleOptionletVolatilityStructureWorker* worker = new RelinkableHandleOptionletVolatilityStructureWorker(
    ObjectIDCpp
,     CurrentLinkCpp
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

void ConstantOptionletVolatilityWorker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes
  QuantLib::Size NDaysLib;
  QuantLibAddin::cppToLibrary(mNDays, NDaysLib);


  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::Calendar CalendarEnum =
      ObjectHandler::Create<QuantLib::Calendar>()(mCalendar);


  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::BusinessDayConvention BusinessDayConventionEnum =
      ObjectHandler::Create<QuantLib::BusinessDayConvention>()(mBusinessDayConvention);


  // convert object IDs into library objects
  QuantLib::Handle<QuantLib::Quote> VolatilityLibObj =
      ObjectHandler::convert2< QuantLib::Handle<QuantLib::Quote> >(mVolatility, "Volatility");


  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::DayCounter DayCounterEnum =
      ObjectHandler::Create<QuantLib::DayCounter>()(mDayCounter);


  // convert input datatypes to QuantLib datatypes
 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlConstantOptionletVolatility(
          mObjectID,
          mNDays,
          mCalendar,
          mBusinessDayConvention,
          mVolatility,
          mDayCounter,
          mVolatilityType,
          mDisplacement,
          false
      ));

    // Construct the Object
	std::map<std::string, QuantLib::VolatilityType> strEnum;
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::ConstantOptionletVolatility(
          valueObject,
          NDaysLib,
          CalendarEnum,
          BusinessDayConventionEnum,
          VolatilityLibObj,
          DayCounterEnum,
		  strEnum[mVolatilityType],
          mDisplacement,
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

NAN_METHOD(QuantLibXL::ConstantOptionletVolatility) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsNumber()) {
      return Nan::ThrowError("NDays is required.");
  }
  if (info.Length() == 2 || !info[2]->IsString()) {
      return Nan::ThrowError("Calendar is required.");
  }
  if (info.Length() == 3 || !info[3]->IsString()) {
      return Nan::ThrowError("BusinessDayConvention is required.");
  }
  if (info.Length() == 5 || !info[5]->IsString()) {
      return Nan::ThrowError("DayCounter is required.");
  }
  if (info.Length() == 6 || !info[6]->IsString()) {
      return Nan::ThrowError("VolatilityType is required.");
  }
  if (info.Length() == 7 || !info[7]->IsNumber()) {
      return Nan::ThrowError("Displacement is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  long NDaysCpp = Nan::To<int32_t>(info[1]).FromJust();

  // convert js argument to c++ type
  String::Utf8Value strCalendar(info[2]->ToString());
  string CalendarCpp(strdup(*strCalendar));

  // convert js argument to c++ type
  String::Utf8Value strBusinessDayConvention(info[3]->ToString());
  string BusinessDayConventionCpp(strdup(*strBusinessDayConvention));

  // convert js argument to c++ type
  ObjectHandler::property_t VolatilityCpp =
      ObjectHandler::property_t(static_cast<double>(Nan::To<double>(info[4]).FromJust()));

  // convert js argument to c++ type
  String::Utf8Value strDayCounter(info[5]->ToString());
  string DayCounterCpp(strdup(*strDayCounter));

  // convert js argument to c++ type
  String::Utf8Value strVolatilityType(info[6]->ToString());
  string VolatilityTypeCpp(strdup(*strVolatilityType));

  // convert js argument to c++ type
  double DisplacementCpp = Nan::To<double>(info[7]).FromJust();

 
  // launch worker
  ConstantOptionletVolatilityWorker* worker = new ConstantOptionletVolatilityWorker(
    ObjectIDCpp
,     NDaysCpp
,     CalendarCpp
,     BusinessDayConventionCpp
,     VolatilityCpp
,     DayCounterCpp
,     VolatilityTypeCpp
,     DisplacementCpp
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

void SpreadedOptionletVolatilityWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_OBJECT(BaseVolStructureCoerce, mBaseVolStructure, ObjectHandler::Object)
  QuantLib::Handle<QuantLib::OptionletVolatilityStructure> BaseVolStructureLibObj =
      QuantLibAddin::CoerceHandle<
          QuantLibAddin::OptionletVolatilityStructure,
          QuantLib::OptionletVolatilityStructure>()(
              BaseVolStructureCoerce);


  // convert object IDs into library objects
  QuantLib::Handle<QuantLib::Quote> SpreadLibObj =
      ObjectHandler::convert2< QuantLib::Handle<QuantLib::Quote> >(mSpread, "Spread");

 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlSpreadedOptionletVolatility(
          mObjectID,
          mBaseVolStructure,
          mSpread,
          false
      ));

    // Construct the Object
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::SpreadedOptionletVolatility(
          valueObject,
          BaseVolStructureLibObj,
          SpreadLibObj,
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

NAN_METHOD(QuantLibXL::SpreadedOptionletVolatility) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  ObjectHandler::property_t BaseVolStructureCpp =
      ObjectHandler::property_t(static_cast<double>(Nan::To<double>(info[1]).FromJust()));

  // convert js argument to c++ type
  ObjectHandler::property_t SpreadCpp =
      ObjectHandler::property_t(static_cast<double>(Nan::To<double>(info[2]).FromJust()));

 
  // launch worker
  SpreadedOptionletVolatilityWorker* worker = new SpreadedOptionletVolatilityWorker(
    ObjectIDCpp
,     BaseVolStructureCpp
,     SpreadCpp
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

void StrippedOptionletAdapterWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_REFERENCE(StrippedOptionletBaseLibObjPtr, mStrippedOptionletBase,
      QuantLibAddin::StrippedOptionletBase, QuantLib::StrippedOptionletBase)

 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlStrippedOptionletAdapter(
          mObjectID,
          mStrippedOptionletBase,
          false
      ));

    // Construct the Object
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::StrippedOptionletAdapter(
          valueObject,
          StrippedOptionletBaseLibObjPtr,
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

NAN_METHOD(QuantLibXL::StrippedOptionletAdapter) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsString()) {
      return Nan::ThrowError("StrippedOptionletBase is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  String::Utf8Value strStrippedOptionletBase(info[1]->ToString());
  string StrippedOptionletBaseCpp(strdup(*strStrippedOptionletBase));

 
  // launch worker
  StrippedOptionletAdapterWorker* worker = new StrippedOptionletAdapterWorker(
    ObjectIDCpp
,     StrippedOptionletBaseCpp
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

void StrippedOptionletWorker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes
  QuantLib::Size SettlementDaysLib;
  QuantLibAddin::cppToLibrary(mSettlementDays, SettlementDaysLib);


  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::Calendar CalendarEnum =
      ObjectHandler::Create<QuantLib::Calendar>()(mCalendar);


  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::BusinessDayConvention BusinessDayConventionEnum =
      ObjectHandler::Create<QuantLib::BusinessDayConvention>()(mBusinessDayConvention);


  // convert object IDs into library objects
  OH_GET_REFERENCE(IborIndexLibObjPtr, mIborIndex,
      QuantLibAddin::IborIndex, QuantLib::IborIndex)


  // convert input datatypes to QuantLib datatypes
  std::vector<QuantLib::Date> OptionletDatesLib = ObjectHandler::vector::convert2<QuantLib::Date>(
      mOptionletDates, "OptionletDates");


  // convert object IDs into library objects
  std::vector< std::vector< QuantLib::Handle<QuantLib::Quote> > > VolatilitiesLibObj =
      ObjectHandler::matrix::convert2< QuantLib::Handle<QuantLib::Quote> >(mVolatilities, "Volatilities");


  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::DayCounter DayCounterEnum =
      ObjectHandler::Create<QuantLib::DayCounter>()(mDayCounter);


  // convert input datatypes to QuantLib datatypes
 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlStrippedOptionlet(
          mObjectID,
          mSettlementDays,
          mCalendar,
          mBusinessDayConvention,
          mIborIndex,
          mOptionletDates,
          mStrikes,
          mVolatilities,
          mDayCounter,
          mVolatilityType,
          mDisplacement,
          false
      ));

    // Construct the Object
	std::map<std::string, QuantLib::VolatilityType> strEnum;
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::StrippedOptionlet(
          valueObject,
          SettlementDaysLib,
          CalendarEnum,
          BusinessDayConventionEnum,
          IborIndexLibObjPtr,
          OptionletDatesLib,
          mStrikes,
          VolatilitiesLibObj,
          DayCounterEnum,
		  strEnum[mVolatilityType],
          mDisplacement,
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

NAN_METHOD(QuantLibXL::StrippedOptionlet) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsNumber()) {
      return Nan::ThrowError("SettlementDays is required.");
  }
  if (info.Length() == 2 || !info[2]->IsString()) {
      return Nan::ThrowError("Calendar is required.");
  }
  if (info.Length() == 3 || !info[3]->IsString()) {
      return Nan::ThrowError("BusinessDayConvention is required.");
  }
  if (info.Length() == 4 || !info[4]->IsString()) {
      return Nan::ThrowError("IborIndex is required.");
  }
  if (info.Length() == 5 || !info[5]->IsArray()) {
      return Nan::ThrowError("OptionletDates is required.");
  }
  if (info.Length() == 6 || !info[6]->IsArray()) {
      return Nan::ThrowError("Strikes is required.");
  }
  if (info.Length() == 7 || !info[7]->IsArray()) {
      return Nan::ThrowError("Volatilities is required.");
  }
  if (info.Length() == 8 || !info[8]->IsString()) {
      return Nan::ThrowError("DayCounter is required.");
  }
  if (info.Length() == 9 || !info[9]->IsString()) {
      return Nan::ThrowError("VolatilityType is required.");
  }
  if (info.Length() == 10 || !info[10]->IsNumber()) {
      return Nan::ThrowError("Displacement is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  long SettlementDaysCpp = Nan::To<int32_t>(info[1]).FromJust();

  // convert js argument to c++ type
  String::Utf8Value strCalendar(info[2]->ToString());
  string CalendarCpp(strdup(*strCalendar));

  // convert js argument to c++ type
  String::Utf8Value strBusinessDayConvention(info[3]->ToString());
  string BusinessDayConventionCpp(strdup(*strBusinessDayConvention));

  // convert js argument to c++ type
  String::Utf8Value strIborIndex(info[4]->ToString());
  string IborIndexCpp(strdup(*strIborIndex));

  // convert js argument to c++ type
  std::vector<ObjectHandler::property_t>OptionletDatesCpp;

  Local<Array> OptionletDatesArray = info[5].As<Array>();
  for (unsigned int i = 0; i < OptionletDatesArray->Length(); i++){
    ObjectHandler::property_t tmp =
        ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(Nan::Get(OptionletDatesArray, i).ToLocalChecked()).FromJust()));
    OptionletDatesCpp.push_back(tmp);
  }

  // convert js argument to c++ type
  std::vector<double>StrikesCpp;

  Local<Array> StrikesArray = info[6].As<Array>();
  for (unsigned int i = 0; i < StrikesArray->Length(); i++){
    StrikesCpp.push_back(Nan::To<double>(Nan::Get(StrikesArray, i).ToLocalChecked()).FromJust());
  }

  // convert js argument to c++ type
  std::vector< std::vector<ObjectHandler::property_t> >VolatilitiesCpp;

  Local<Array> VolatilitiesMatrix = info[7].As<Array>();
  for (unsigned int i = 0; i < VolatilitiesMatrix->Length(); i++){
	  Local<Array> VolatilitiesArray = VolatilitiesMatrix->Get(i).As<Array>();
	  std::vector<ObjectHandler::property_t> tmp;
	  for (unsigned int j = 0; j < VolatilitiesArray->Length(); j++){
      ObjectHandler::property_t temp =
          ObjectHandler::property_t(static_cast<double>(Nan::To<double>(Nan::Get(VolatilitiesArray, j).ToLocalChecked()).FromJust()));
		  tmp.push_back(temp);
	  }
	  VolatilitiesCpp.push_back(tmp);
  }

  // convert js argument to c++ type
  String::Utf8Value strDayCounter(info[8]->ToString());
  string DayCounterCpp(strdup(*strDayCounter));

  // convert js argument to c++ type
  String::Utf8Value strVolatilityType(info[9]->ToString());
  string VolatilityTypeCpp(strdup(*strVolatilityType));

  // convert js argument to c++ type
  double DisplacementCpp = Nan::To<double>(info[10]).FromJust();

 
  // launch worker
  StrippedOptionletWorker* worker = new StrippedOptionletWorker(
    ObjectIDCpp
,     SettlementDaysCpp
,     CalendarCpp
,     BusinessDayConventionCpp
,     IborIndexCpp
,     OptionletDatesCpp
,     StrikesCpp
,     VolatilitiesCpp
,     DayCounterCpp
,     VolatilityTypeCpp
,     DisplacementCpp
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

void OptionletStripper1Worker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_REFERENCE(TermVolSurfaceLibObjPtr, mTermVolSurface,
      QuantLibAddin::CapFloorTermVolSurface, QuantLib::CapFloorTermVolSurface)


  // convert object IDs into library objects
  OH_GET_REFERENCE(IborIndexLibObjPtr, mIborIndex,
      QuantLibAddin::IborIndex, QuantLib::IborIndex)


  // convert input datatypes to QuantLib datatypes

  // convert input datatypes to QuantLib datatypes
  QuantLib::Natural MaxIterLib = ObjectHandler::convert2<long>(
      mMaxIter, "MaxIter", QuantLib::Null<QuantLib::Natural>());


  // convert input datatypes to QuantLib datatypes
 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlOptionletStripper1(
          mObjectID,
          mTermVolSurface,
          mIborIndex,
          mSwitchStrike,
          mAccuracy,
          mMaxIter,
          mVolatilityType,
          mDisplacement,
          false
      ));

    // Construct the Object
	std::map<std::string, QuantLib::VolatilityType> strEnum;
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::OptionletStripper1(
          valueObject,
          TermVolSurfaceLibObjPtr,
          IborIndexLibObjPtr,
          mSwitchStrike,
          mAccuracy,
          MaxIterLib,
		  strEnum[mVolatilityType],
          mDisplacement,
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

NAN_METHOD(QuantLibXL::OptionletStripper1) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsString()) {
      return Nan::ThrowError("TermVolSurface is required.");
  }
  if (info.Length() == 2 || !info[2]->IsString()) {
      return Nan::ThrowError("IborIndex is required.");
  }
  if (info.Length() == 3 || !info[3]->IsNumber()) {
      return Nan::ThrowError("SwitchStrike is required.");
  }
  if (info.Length() == 4 || !info[4]->IsNumber()) {
      return Nan::ThrowError("Accuracy is required.");
  }
  if (info.Length() == 6 || !info[6]->IsString()) {
      return Nan::ThrowError("VolatilityType is required.");
  }
  if (info.Length() == 7 || !info[7]->IsNumber()) {
      return Nan::ThrowError("Displacement is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  String::Utf8Value strTermVolSurface(info[1]->ToString());
  string TermVolSurfaceCpp(strdup(*strTermVolSurface));

  // convert js argument to c++ type
  String::Utf8Value strIborIndex(info[2]->ToString());
  string IborIndexCpp(strdup(*strIborIndex));

  // convert js argument to c++ type
  double SwitchStrikeCpp = Nan::To<double>(info[3]).FromJust();

  // convert js argument to c++ type
  double AccuracyCpp = Nan::To<double>(info[4]).FromJust();

  // convert js argument to c++ type
  ObjectHandler::property_t MaxIterCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[5]).FromJust()));

  // convert js argument to c++ type
  String::Utf8Value strVolatilityType(info[6]->ToString());
  string VolatilityTypeCpp(strdup(*strVolatilityType));

  // convert js argument to c++ type
  double DisplacementCpp = Nan::To<double>(info[7]).FromJust();

 
  // launch worker
  OptionletStripper1Worker* worker = new OptionletStripper1Worker(
    ObjectIDCpp
,     TermVolSurfaceCpp
,     IborIndexCpp
,     SwitchStrikeCpp
,     AccuracyCpp
,     MaxIterCpp
,     VolatilityTypeCpp
,     DisplacementCpp
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

void OptionletStripper2Worker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_REFERENCE(OptionletStripper1LibObjPtr, mOptionletStripper1,
      QuantLibAddin::OptionletStripper1, QuantLib::OptionletStripper1)


  // convert object IDs into library objects
  OH_GET_OBJECT(TermVolCurveCoerce, mTermVolCurve, ObjectHandler::Object)
  QuantLib::Handle<QuantLib::CapFloorTermVolCurve> TermVolCurveLibObj =
      QuantLibAddin::CoerceHandle<
          QuantLibAddin::CapFloorTermVolCurve,
          QuantLib::CapFloorTermVolCurve>()(
              TermVolCurveCoerce);

 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlOptionletStripper2(
          mObjectID,
          mOptionletStripper1,
          mTermVolCurve,
          false
      ));

    // Construct the Object
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::OptionletStripper2(
          valueObject,
          OptionletStripper1LibObjPtr,
          TermVolCurveLibObj,
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

NAN_METHOD(QuantLibXL::OptionletStripper2) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsString()) {
      return Nan::ThrowError("OptionletStripper1 is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  String::Utf8Value strOptionletStripper1(info[1]->ToString());
  string OptionletStripper1Cpp(strdup(*strOptionletStripper1));

  // convert js argument to c++ type
  ObjectHandler::property_t TermVolCurveCpp =
      ObjectHandler::property_t(static_cast<double>(Nan::To<double>(info[2]).FromJust()));

 
  // launch worker
  OptionletStripper2Worker* worker = new OptionletStripper2Worker(
    ObjectIDCpp
,     OptionletStripper1Cpp
,     TermVolCurveCpp
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

void CapFloorTermVolCurveWorker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes
  QuantLib::Size SettlementDaysLib;
  QuantLibAddin::cppToLibrary(mSettlementDays, SettlementDaysLib);


  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::Calendar CalendarEnum =
      ObjectHandler::Create<QuantLib::Calendar>()(mCalendar);


  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::BusinessDayConvention BusinessDayConventionEnum =
      ObjectHandler::Create<QuantLib::BusinessDayConvention>()(mBusinessDayConvention);


  // convert input datatypes to QuantLib datatypes
  std::vector<QuantLib::Period> OptionTenorsLib;


  // convert object IDs into library objects
  std::vector< QuantLib::Handle<QuantLib::Quote> > VolatilitiesLibObj =
      ObjectHandler::vector::convert2< QuantLib::Handle<QuantLib::Quote> >(mVolatilities, "Volatilities");


  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::DayCounter DayCounterEnum =
      ObjectHandler::Create<QuantLib::DayCounter>()(mDayCounter);

 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlCapFloorTermVolCurve(
          mObjectID,
          mSettlementDays,
          mCalendar,
          mBusinessDayConvention,
          mOptionTenors,
          mVolatilities,
          mDayCounter,
          false
      ));

    // Construct the Object
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::CapFloorTermVolCurve(
          valueObject,
          SettlementDaysLib,
          CalendarEnum,
          BusinessDayConventionEnum,
          OptionTenorsLib,
          VolatilitiesLibObj,
          DayCounterEnum,
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

NAN_METHOD(QuantLibXL::CapFloorTermVolCurve) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsNumber()) {
      return Nan::ThrowError("SettlementDays is required.");
  }
  if (info.Length() == 2 || !info[2]->IsString()) {
      return Nan::ThrowError("Calendar is required.");
  }
  if (info.Length() == 3 || !info[3]->IsString()) {
      return Nan::ThrowError("BusinessDayConvention is required.");
  }
  if (info.Length() == 4 || !info[4]->IsArray()) {
      return Nan::ThrowError("OptionTenors is required.");
  }
  if (info.Length() == 5 || !info[5]->IsArray()) {
      return Nan::ThrowError("Volatilities is required.");
  }
  if (info.Length() == 6 || !info[6]->IsString()) {
      return Nan::ThrowError("DayCounter is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  long SettlementDaysCpp = Nan::To<int32_t>(info[1]).FromJust();

  // convert js argument to c++ type
  String::Utf8Value strCalendar(info[2]->ToString());
  string CalendarCpp(strdup(*strCalendar));

  // convert js argument to c++ type
  String::Utf8Value strBusinessDayConvention(info[3]->ToString());
  string BusinessDayConventionCpp(strdup(*strBusinessDayConvention));

  // convert js argument to c++ type
  std::vector<ObjectHandler::property_t>OptionTenorsCpp;

  Local<Array> OptionTenorsArray = info[4].As<Array>();
  for (unsigned int i = 0; i < OptionTenorsArray->Length(); i++){
    ObjectHandler::property_t tmp =
        ObjectHandler::property_t(static_cast<double>(Nan::To<double>(Nan::Get(OptionTenorsArray, i).ToLocalChecked()).FromJust()));
    OptionTenorsCpp.push_back(tmp);
  }

  // convert js argument to c++ type
  std::vector<ObjectHandler::property_t>VolatilitiesCpp;

  Local<Array> VolatilitiesArray = info[5].As<Array>();
  for (unsigned int i = 0; i < VolatilitiesArray->Length(); i++){
    ObjectHandler::property_t tmp =
        ObjectHandler::property_t(static_cast<double>(Nan::To<double>(Nan::Get(VolatilitiesArray, i).ToLocalChecked()).FromJust()));
    VolatilitiesCpp.push_back(tmp);
  }

  // convert js argument to c++ type
  String::Utf8Value strDayCounter(info[6]->ToString());
  string DayCounterCpp(strdup(*strDayCounter));

 
  // launch worker
  CapFloorTermVolCurveWorker* worker = new CapFloorTermVolCurveWorker(
    ObjectIDCpp
,     SettlementDaysCpp
,     CalendarCpp
,     BusinessDayConventionCpp
,     OptionTenorsCpp
,     VolatilitiesCpp
,     DayCounterCpp
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

void CapFloorTermVolSurfaceWorker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes
  QuantLib::Size SettlementDaysLib;
  QuantLibAddin::cppToLibrary(mSettlementDays, SettlementDaysLib);


  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::Calendar CalendarEnum =
      ObjectHandler::Create<QuantLib::Calendar>()(mCalendar);


  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::BusinessDayConvention BusinessDayConventionEnum =
      ObjectHandler::Create<QuantLib::BusinessDayConvention>()(mBusinessDayConvention);


  // convert input datatypes to QuantLib datatypes
  std::vector<QuantLib::Period> OptionTenorsLib;


  // convert object IDs into library objects
  std::vector< std::vector< QuantLib::Handle<QuantLib::Quote> > > VolatilitiesLibObj =
      ObjectHandler::matrix::convert2< QuantLib::Handle<QuantLib::Quote> >(mVolatilities, "Volatilities");


  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::DayCounter DayCounterEnum =
      ObjectHandler::Create<QuantLib::DayCounter>()(mDayCounter);

 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlCapFloorTermVolSurface(
          mObjectID,
          mSettlementDays,
          mCalendar,
          mBusinessDayConvention,
          mOptionTenors,
          mStrikes,
          mVolatilities,
          mDayCounter,
          false
      ));

    // Construct the Object
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::CapFloorTermVolSurface(
          valueObject,
          SettlementDaysLib,
          CalendarEnum,
          BusinessDayConventionEnum,
          OptionTenorsLib,
          mStrikes,
          VolatilitiesLibObj,
          DayCounterEnum,
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

NAN_METHOD(QuantLibXL::CapFloorTermVolSurface) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsNumber()) {
      return Nan::ThrowError("SettlementDays is required.");
  }
  if (info.Length() == 2 || !info[2]->IsString()) {
      return Nan::ThrowError("Calendar is required.");
  }
  if (info.Length() == 3 || !info[3]->IsString()) {
      return Nan::ThrowError("BusinessDayConvention is required.");
  }
  if (info.Length() == 4 || !info[4]->IsArray()) {
      return Nan::ThrowError("OptionTenors is required.");
  }
  if (info.Length() == 5 || !info[5]->IsArray()) {
      return Nan::ThrowError("Strikes is required.");
  }
  if (info.Length() == 6 || !info[6]->IsArray()) {
      return Nan::ThrowError("Volatilities is required.");
  }
  if (info.Length() == 7 || !info[7]->IsString()) {
      return Nan::ThrowError("DayCounter is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  long SettlementDaysCpp = Nan::To<int32_t>(info[1]).FromJust();

  // convert js argument to c++ type
  String::Utf8Value strCalendar(info[2]->ToString());
  string CalendarCpp(strdup(*strCalendar));

  // convert js argument to c++ type
  String::Utf8Value strBusinessDayConvention(info[3]->ToString());
  string BusinessDayConventionCpp(strdup(*strBusinessDayConvention));

  // convert js argument to c++ type
  std::vector<ObjectHandler::property_t>OptionTenorsCpp;

  Local<Array> OptionTenorsArray = info[4].As<Array>();
  for (unsigned int i = 0; i < OptionTenorsArray->Length(); i++){
    ObjectHandler::property_t tmp =
        ObjectHandler::property_t(static_cast<double>(Nan::To<double>(Nan::Get(OptionTenorsArray, i).ToLocalChecked()).FromJust()));
    OptionTenorsCpp.push_back(tmp);
  }

  // convert js argument to c++ type
  std::vector<double>StrikesCpp;

  Local<Array> StrikesArray = info[5].As<Array>();
  for (unsigned int i = 0; i < StrikesArray->Length(); i++){
    StrikesCpp.push_back(Nan::To<double>(Nan::Get(StrikesArray, i).ToLocalChecked()).FromJust());
  }

  // convert js argument to c++ type
  std::vector< std::vector<ObjectHandler::property_t> >VolatilitiesCpp;

  Local<Array> VolatilitiesMatrix = info[6].As<Array>();
  for (unsigned int i = 0; i < VolatilitiesMatrix->Length(); i++){
	  Local<Array> VolatilitiesArray = VolatilitiesMatrix->Get(i).As<Array>();
	  std::vector<ObjectHandler::property_t> tmp;
	  for (unsigned int j = 0; j < VolatilitiesArray->Length(); j++){
      ObjectHandler::property_t temp =
          ObjectHandler::property_t(static_cast<double>(Nan::To<double>(Nan::Get(VolatilitiesArray, j).ToLocalChecked()).FromJust()));
		  tmp.push_back(temp);
	  }
	  VolatilitiesCpp.push_back(tmp);
  }

  // convert js argument to c++ type
  String::Utf8Value strDayCounter(info[7]->ToString());
  string DayCounterCpp(strdup(*strDayCounter));

 
  // launch worker
  CapFloorTermVolSurfaceWorker* worker = new CapFloorTermVolSurfaceWorker(
    ObjectIDCpp
,     SettlementDaysCpp
,     CalendarCpp
,     BusinessDayConventionCpp
,     OptionTenorsCpp
,     StrikesCpp
,     VolatilitiesCpp
,     DayCounterCpp
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

void OptionletVTSVolatilityWorker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes
  QuantLib::Date OptionDateLib = ObjectHandler::convert2<QuantLib::Date>(
      mOptionDate, "OptionDate");

       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::OptionletVolatilityStructure, QuantLib::OptionletVolatilityStructure)


  // loop on the input parameter and populate the return vector
  QuantLibAddin::qlOptionletVTSVolatilityBind bindObject =
      boost::bind((QuantLibAddin::qlOptionletVTSVolatilitySignature)
              &QuantLib::OptionletVolatilityStructure::volatility,
              ObjectIDLibObjPtr
          ,OptionDateLib
          ,_1
          ,mAllowExtrapolation
          );

  ObjectHandler::loop
      <QuantLibAddin::qlOptionletVTSVolatilityBind,
                      QuantLib::Rate,
                      QuantLib::Volatility>
          (bindObject,
           mStrike,
          mReturnValue
          );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::OptionletVTSVolatility) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 2 || !info[2]->IsArray()) {
      return Nan::ThrowError("Strike is required.");
  }
  if (info.Length() == 3 || !info[3]->IsBoolean()) {
      return Nan::ThrowError("AllowExtrapolation is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  ObjectHandler::property_t OptionDateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[1]).FromJust()));

  // convert js argument to c++ type
  std::vector<double>StrikeCpp;

  Local<Array> StrikeArray = info[2].As<Array>();
  for (unsigned int i = 0; i < StrikeArray->Length(); i++){
    StrikeCpp.push_back(Nan::To<double>(Nan::Get(StrikeArray, i).ToLocalChecked()).FromJust());
  }

  // convert js argument to c++ type
  bool AllowExtrapolationCpp = Nan::To<bool>(info[3]).FromJust();

 
  // launch worker
  OptionletVTSVolatilityWorker* worker = new OptionletVTSVolatilityWorker(
    ObjectIDCpp
,     OptionDateCpp
,     StrikeCpp
,     AllowExtrapolationCpp
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

void OptionletVTSVolatility2Worker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes
  QuantLib::Period OptionTenorLib;
  QuantLibAddin::cppToLibrary(mOptionTenor, OptionTenorLib);

       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::OptionletVolatilityStructure, QuantLib::OptionletVolatilityStructure)


  // loop on the input parameter and populate the return vector
  QuantLibAddin::qlOptionletVTSVolatility2Bind bindObject =
      boost::bind((QuantLibAddin::qlOptionletVTSVolatility2Signature)
              &QuantLib::OptionletVolatilityStructure::volatility,
              ObjectIDLibObjPtr
          ,OptionTenorLib
          ,_1
          ,mAllowExtrapolation
          );

  ObjectHandler::loop
      <QuantLibAddin::qlOptionletVTSVolatility2Bind,
                      QuantLib::Rate,
                      QuantLib::Volatility>
          (bindObject,
           mStrike,
          mReturnValue
          );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::OptionletVTSVolatility2) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsString()) {
      return Nan::ThrowError("OptionTenor is required.");
  }
  if (info.Length() == 2 || !info[2]->IsArray()) {
      return Nan::ThrowError("Strike is required.");
  }
  if (info.Length() == 3 || !info[3]->IsBoolean()) {
      return Nan::ThrowError("AllowExtrapolation is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  String::Utf8Value strOptionTenor(info[1]->ToString());
  string OptionTenorCpp(strdup(*strOptionTenor));

  // convert js argument to c++ type
  std::vector<double>StrikeCpp;

  Local<Array> StrikeArray = info[2].As<Array>();
  for (unsigned int i = 0; i < StrikeArray->Length(); i++){
    StrikeCpp.push_back(Nan::To<double>(Nan::Get(StrikeArray, i).ToLocalChecked()).FromJust());
  }

  // convert js argument to c++ type
  bool AllowExtrapolationCpp = Nan::To<bool>(info[3]).FromJust();

 
  // launch worker
  OptionletVTSVolatility2Worker* worker = new OptionletVTSVolatility2Worker(
    ObjectIDCpp
,     OptionTenorCpp
,     StrikeCpp
,     AllowExtrapolationCpp
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

void OptionletVTSBlackVarianceWorker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes
  std::vector<QuantLib::Date> OptionDateLib = ObjectHandler::vector::convert2<QuantLib::Date>(
      mOptionDate, "OptionDate");

       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::OptionletVolatilityStructure, QuantLib::OptionletVolatilityStructure)

  std::vector<QuantLib::Real> returnValue;


  // loop on the input parameter and populate the return vector
  QuantLibAddin::qlOptionletVTSBlackVarianceBind bindObject =
      boost::bind((QuantLibAddin::qlOptionletVTSBlackVarianceSignature)
              &QuantLib::OptionletVolatilityStructure::blackVariance,
              ObjectIDLibObjPtr
          ,_1
          ,mStrike
          ,mAllowExtrapolation
          );

  ObjectHandler::loop
      <QuantLibAddin::qlOptionletVTSBlackVarianceBind,
                      QuantLib::Date,
                      QuantLib::Real>
          (bindObject,
            OptionDateLib,
          returnValue
          );


  mReturnValue = QuantLibAddin::libraryToVector(returnValue);

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::OptionletVTSBlackVariance) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsArray()) {
      return Nan::ThrowError("OptionDate is required.");
  }
  if (info.Length() == 2 || !info[2]->IsNumber()) {
      return Nan::ThrowError("Strike is required.");
  }
  if (info.Length() == 3 || !info[3]->IsBoolean()) {
      return Nan::ThrowError("AllowExtrapolation is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  std::vector<ObjectHandler::property_t>OptionDateCpp;

  Local<Array> OptionDateArray = info[1].As<Array>();
  for (unsigned int i = 0; i < OptionDateArray->Length(); i++){
    ObjectHandler::property_t tmp =
        ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(Nan::Get(OptionDateArray, i).ToLocalChecked()).FromJust()));
    OptionDateCpp.push_back(tmp);
  }

  // convert js argument to c++ type
  double StrikeCpp = Nan::To<double>(info[2]).FromJust();

  // convert js argument to c++ type
  bool AllowExtrapolationCpp = Nan::To<bool>(info[3]).FromJust();

 
  // launch worker
  OptionletVTSBlackVarianceWorker* worker = new OptionletVTSBlackVarianceWorker(
    ObjectIDCpp
,     OptionDateCpp
,     StrikeCpp
,     AllowExtrapolationCpp
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

void OptionletVTSBlackVariance2Worker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes
  std::vector<QuantLib::Period> OptionTenorLib;

       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::OptionletVolatilityStructure, QuantLib::OptionletVolatilityStructure)

  std::vector<QuantLib::Real> returnValue;


  // loop on the input parameter and populate the return vector
  QuantLibAddin::qlOptionletVTSBlackVariance2Bind bindObject =
      boost::bind((QuantLibAddin::qlOptionletVTSBlackVariance2Signature)
              &QuantLib::OptionletVolatilityStructure::blackVariance,
              ObjectIDLibObjPtr
          ,_1
          ,mStrike
          ,mAllowExtrapolation
          );

  ObjectHandler::loop
      <QuantLibAddin::qlOptionletVTSBlackVariance2Bind,
                      QuantLib::Period,
                      QuantLib::Real>
          (bindObject,
            OptionTenorLib,
          returnValue
          );


  mReturnValue = QuantLibAddin::libraryToVector(returnValue);

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::OptionletVTSBlackVariance2) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsArray()) {
      return Nan::ThrowError("OptionTenor is required.");
  }
  if (info.Length() == 2 || !info[2]->IsNumber()) {
      return Nan::ThrowError("Strike is required.");
  }
  if (info.Length() == 3 || !info[3]->IsBoolean()) {
      return Nan::ThrowError("AllowExtrapolation is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  std::vector<ObjectHandler::property_t>OptionTenorCpp;

  Local<Array> OptionTenorArray = info[1].As<Array>();
  for (unsigned int i = 0; i < OptionTenorArray->Length(); i++){
    ObjectHandler::property_t tmp =
        ObjectHandler::property_t(static_cast<double>(Nan::To<double>(Nan::Get(OptionTenorArray, i).ToLocalChecked()).FromJust()));
    OptionTenorCpp.push_back(tmp);
  }

  // convert js argument to c++ type
  double StrikeCpp = Nan::To<double>(info[2]).FromJust();

  // convert js argument to c++ type
  bool AllowExtrapolationCpp = Nan::To<bool>(info[3]).FromJust();

 
  // launch worker
  OptionletVTSBlackVariance2Worker* worker = new OptionletVTSBlackVariance2Worker(
    ObjectIDCpp
,     OptionTenorCpp
,     StrikeCpp
,     AllowExtrapolationCpp
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

void StrippedOptionletBaseStrikesWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::StrippedOptionletBase, QuantLib::StrippedOptionletBase)


  // convert input datatypes to QuantLib datatypes
  QuantLib::Size IndexLib;
  QuantLibAddin::cppToLibrary(mIndex, IndexLib);

     
  // loop on the input parameter and populate the return vector
  mReturnValue = ObjectIDLibObjPtr->optionletStrikes(
        IndexLib
       );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::StrippedOptionletBaseStrikes) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsNumber()) {
      return Nan::ThrowError("Index is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  long IndexCpp = Nan::To<int32_t>(info[1]).FromJust();

 
  // launch worker
  StrippedOptionletBaseStrikesWorker* worker = new StrippedOptionletBaseStrikesWorker(
    ObjectIDCpp
,     IndexCpp
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

void StrippedOptionletBaseOptionletVolatilitiesWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::StrippedOptionletBase, QuantLib::StrippedOptionletBase)


  // convert input datatypes to QuantLib datatypes
  QuantLib::Size IndexLib;
  QuantLibAddin::cppToLibrary(mIndex, IndexLib);

     
  // loop on the input parameter and populate the return vector
  mReturnValue = ObjectIDLibObjPtr->optionletVolatilities(
        IndexLib
       );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::StrippedOptionletBaseOptionletVolatilities) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsNumber()) {
      return Nan::ThrowError("Index is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  long IndexCpp = Nan::To<int32_t>(info[1]).FromJust();

 
  // launch worker
  StrippedOptionletBaseOptionletVolatilitiesWorker* worker = new StrippedOptionletBaseOptionletVolatilitiesWorker(
    ObjectIDCpp
,     IndexCpp
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

void StrippedOptionletBaseOptionletFixingDatesWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::StrippedOptionletBase, QuantLib::StrippedOptionletBase)

     
  // loop on the input parameter and populate the return vector
  std::vector<QuantLib::Date> returnValue = ObjectIDLibObjPtr->optionletFixingDates(
      );


  mReturnValue = QuantLibAddin::libraryToVector(returnValue);

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::StrippedOptionletBaseOptionletFixingDates) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  StrippedOptionletBaseOptionletFixingDatesWorker* worker = new StrippedOptionletBaseOptionletFixingDatesWorker(
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

void StrippedOptionletBaseOptionletFixingTimesWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::StrippedOptionletBase, QuantLib::StrippedOptionletBase)

     
  // loop on the input parameter and populate the return vector
  mReturnValue = ObjectIDLibObjPtr->optionletFixingTimes(
      );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::StrippedOptionletBaseOptionletFixingTimes) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  StrippedOptionletBaseOptionletFixingTimesWorker* worker = new StrippedOptionletBaseOptionletFixingTimesWorker(
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

void StrippedOptionletBaseAtmOptionletRatesWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::StrippedOptionletBase, QuantLib::StrippedOptionletBase)

     
  // loop on the input parameter and populate the return vector
  mReturnValue = ObjectIDLibObjPtr->atmOptionletRates(
      );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::StrippedOptionletBaseAtmOptionletRates) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  StrippedOptionletBaseAtmOptionletRatesWorker* worker = new StrippedOptionletBaseAtmOptionletRatesWorker(
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

void StrippedOptionletBaseDayCounterWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::StrippedOptionletBase, QuantLib::StrippedOptionletBase)

     
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

NAN_METHOD(QuantLibXL::StrippedOptionletBaseDayCounter) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  StrippedOptionletBaseDayCounterWorker* worker = new StrippedOptionletBaseDayCounterWorker(
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

void StrippedOptionletBaseCalendarWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::StrippedOptionletBase, QuantLib::StrippedOptionletBase)

     
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

NAN_METHOD(QuantLibXL::StrippedOptionletBaseCalendar) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  StrippedOptionletBaseCalendarWorker* worker = new StrippedOptionletBaseCalendarWorker(
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

void StrippedOptionletBaseSettlementDaysWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::StrippedOptionletBase, QuantLib::StrippedOptionletBase)

     
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

NAN_METHOD(QuantLibXL::StrippedOptionletBaseSettlementDays) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  StrippedOptionletBaseSettlementDaysWorker* worker = new StrippedOptionletBaseSettlementDaysWorker(
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

void StrippedOptionletBaseBusinessDayConventionWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::StrippedOptionletBase, QuantLib::StrippedOptionletBase)

     
  // invoke the member function
  QuantLib::BusinessDayConvention returnValue = ObjectIDLibObjPtr->businessDayConvention(
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

NAN_METHOD(QuantLibXL::StrippedOptionletBaseBusinessDayConvention) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  StrippedOptionletBaseBusinessDayConventionWorker* worker = new StrippedOptionletBaseBusinessDayConventionWorker(
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

void OptionletStripperOptionletFixingTenorsWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::OptionletStripper, QuantLib::OptionletStripper)

     
  // loop on the input parameter and populate the return vector
  std::vector<QuantLib::Period> returnValue = ObjectIDLibObjPtr->optionletFixingTenors(
      );


  mReturnValue = QuantLibAddin::libraryToVector(returnValue);

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::OptionletStripperOptionletFixingTenors) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  OptionletStripperOptionletFixingTenorsWorker* worker = new OptionletStripperOptionletFixingTenorsWorker(
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

void OptionletStripperOptionletPaymentDatesWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::OptionletStripper, QuantLib::OptionletStripper)

     
  // loop on the input parameter and populate the return vector
  std::vector<QuantLib::Date> returnValue = ObjectIDLibObjPtr->optionletPaymentDates(
      );


  mReturnValue = QuantLibAddin::libraryToVector(returnValue);

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::OptionletStripperOptionletPaymentDates) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  OptionletStripperOptionletPaymentDatesWorker* worker = new OptionletStripperOptionletPaymentDatesWorker(
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

void OptionletStripperOptionletAccrualPeriodsWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::OptionletStripper, QuantLib::OptionletStripper)

     
  // loop on the input parameter and populate the return vector
  mReturnValue = ObjectIDLibObjPtr->optionletAccrualPeriods(
      );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::OptionletStripperOptionletAccrualPeriods) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  OptionletStripperOptionletAccrualPeriodsWorker* worker = new OptionletStripperOptionletAccrualPeriodsWorker(
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

void OptionletStripper1CapFloorPricesWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::OptionletStripper1, QuantLib::OptionletStripper1)

       QuantLib::Matrix returnValue;


  // invoke the member function
  returnValue = ObjectIDLibObjPtr->capFloorPrices(
      );


  mReturnValue = QuantLibAddin::qlMatrixToVv(returnValue);

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::OptionletStripper1CapFloorPrices) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  OptionletStripper1CapFloorPricesWorker* worker = new OptionletStripper1CapFloorPricesWorker(
    ObjectIDCpp
   );

  worker->Execute();

    Local<Array> tmpMatrix = Nan::New<Array>(worker->mReturnValue.size());
    for (unsigned int i = 0; i < worker->mReturnValue.size(); i++) {
      Local<Array> tmpArray = Nan::New<Array>(worker->mReturnValue[i].size());
      for (unsigned int j = 0; j < worker->mReturnValue[i].size(); j++) {
        Nan::Set(tmpArray,j,Nan::New<Number>(worker->mReturnValue[i][j]));
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

void OptionletStripper1CapFloorVolatilitiesWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::OptionletStripper1, QuantLib::OptionletStripper1)

       QuantLib::Matrix returnValue;


  // invoke the member function
  returnValue = ObjectIDLibObjPtr->capFloorVolatilities(
      );


  mReturnValue = QuantLibAddin::qlMatrixToVv(returnValue);

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::OptionletStripper1CapFloorVolatilities) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  OptionletStripper1CapFloorVolatilitiesWorker* worker = new OptionletStripper1CapFloorVolatilitiesWorker(
    ObjectIDCpp
   );

  worker->Execute();

    Local<Array> tmpMatrix = Nan::New<Array>(worker->mReturnValue.size());
    for (unsigned int i = 0; i < worker->mReturnValue.size(); i++) {
      Local<Array> tmpArray = Nan::New<Array>(worker->mReturnValue[i].size());
      for (unsigned int j = 0; j < worker->mReturnValue[i].size(); j++) {
        Nan::Set(tmpArray,j,Nan::New<Number>(worker->mReturnValue[i][j]));
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

void OptionletStripper1OptionletPricesWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::OptionletStripper1, QuantLib::OptionletStripper1)

       QuantLib::Matrix returnValue;


  // invoke the member function
  returnValue = ObjectIDLibObjPtr->optionletPrices(
      );


  mReturnValue = QuantLibAddin::qlMatrixToVv(returnValue);

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::OptionletStripper1OptionletPrices) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  OptionletStripper1OptionletPricesWorker* worker = new OptionletStripper1OptionletPricesWorker(
    ObjectIDCpp
   );

  worker->Execute();

    Local<Array> tmpMatrix = Nan::New<Array>(worker->mReturnValue.size());
    for (unsigned int i = 0; i < worker->mReturnValue.size(); i++) {
      Local<Array> tmpArray = Nan::New<Array>(worker->mReturnValue[i].size());
      for (unsigned int j = 0; j < worker->mReturnValue[i].size(); j++) {
        Nan::Set(tmpArray,j,Nan::New<Number>(worker->mReturnValue[i][j]));
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

void OptionletStripper1SwitchStrikeWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::OptionletStripper1, QuantLib::OptionletStripper1)

     
  // invoke the member function
  mReturnValue = ObjectIDLibObjPtr->switchStrike(
      );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::OptionletStripper1SwitchStrike) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  OptionletStripper1SwitchStrikeWorker* worker = new OptionletStripper1SwitchStrikeWorker(
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

void OptionletStripper2SpreadsVolWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::OptionletStripper2, QuantLib::OptionletStripper2)

     
  // loop on the input parameter and populate the return vector
  mReturnValue = ObjectIDLibObjPtr->spreadsVol(
      );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::OptionletStripper2SpreadsVol) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  OptionletStripper2SpreadsVolWorker* worker = new OptionletStripper2SpreadsVolWorker(
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

void OptionletStripper2AtmCapFloorPricesWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::OptionletStripper2, QuantLib::OptionletStripper2)

     
  // loop on the input parameter and populate the return vector
  std::vector<QuantLib::Real> returnValue = ObjectIDLibObjPtr->atmCapFloorPrices(
      );


  mReturnValue = QuantLibAddin::libraryToVector(returnValue);

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::OptionletStripper2AtmCapFloorPrices) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  OptionletStripper2AtmCapFloorPricesWorker* worker = new OptionletStripper2AtmCapFloorPricesWorker(
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

void OptionletStripper2AtmCapFloorStrikesWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::OptionletStripper2, QuantLib::OptionletStripper2)

     
  // loop on the input parameter and populate the return vector
  mReturnValue = ObjectIDLibObjPtr->atmCapFloorStrikes(
      );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::OptionletStripper2AtmCapFloorStrikes) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  OptionletStripper2AtmCapFloorStrikesWorker* worker = new OptionletStripper2AtmCapFloorStrikesWorker(
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

void CapFloorTermVTSVolatilityWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::CapFloorTermVolatilityStructure, QuantLib::CapFloorTermVolatilityStructure)


  // convert input datatypes to QuantLib datatypes
  QuantLib::Date OptionDateLib = ObjectHandler::convert2<QuantLib::Date>(
      mOptionDate, "OptionDate");

     
  // loop on the input parameter and populate the return vector
  QuantLibAddin::qlCapFloorTermVTSVolatilityBind bindObject =
      boost::bind((QuantLibAddin::qlCapFloorTermVTSVolatilitySignature)
              &QuantLib::CapFloorTermVolatilityStructure::volatility,
              ObjectIDLibObjPtr
          ,OptionDateLib
          ,_1
          ,mAllowExtrapolation
          );

  ObjectHandler::loop
      <QuantLibAddin::qlCapFloorTermVTSVolatilityBind,
                      QuantLib::Rate,
                      QuantLib::Volatility>
          (bindObject,
           mStrike,
          mReturnValue
          );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::CapFloorTermVTSVolatility) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 2 || !info[2]->IsArray()) {
      return Nan::ThrowError("Strike is required.");
  }
  if (info.Length() == 3 || !info[3]->IsBoolean()) {
      return Nan::ThrowError("AllowExtrapolation is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  ObjectHandler::property_t OptionDateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[1]).FromJust()));

  // convert js argument to c++ type
  std::vector<double>StrikeCpp;

  Local<Array> StrikeArray = info[2].As<Array>();
  for (unsigned int i = 0; i < StrikeArray->Length(); i++){
    StrikeCpp.push_back(Nan::To<double>(Nan::Get(StrikeArray, i).ToLocalChecked()).FromJust());
  }

  // convert js argument to c++ type
  bool AllowExtrapolationCpp = Nan::To<bool>(info[3]).FromJust();

 
  // launch worker
  CapFloorTermVTSVolatilityWorker* worker = new CapFloorTermVTSVolatilityWorker(
    ObjectIDCpp
,     OptionDateCpp
,     StrikeCpp
,     AllowExtrapolationCpp
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

void CapFloorTermVTSVolatility2Worker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::CapFloorTermVolatilityStructure, QuantLib::CapFloorTermVolatilityStructure)


  // convert input datatypes to QuantLib datatypes
  QuantLib::Period OptionTenorLib;
  QuantLibAddin::cppToLibrary(mOptionTenor, OptionTenorLib);

     
  // loop on the input parameter and populate the return vector
  QuantLibAddin::qlCapFloorTermVTSVolatility2Bind bindObject =
      boost::bind((QuantLibAddin::qlCapFloorTermVTSVolatility2Signature)
              &QuantLib::CapFloorTermVolatilityStructure::volatility,
              ObjectIDLibObjPtr
          ,OptionTenorLib
          ,_1
          ,mAllowExtrapolation
          );

  ObjectHandler::loop
      <QuantLibAddin::qlCapFloorTermVTSVolatility2Bind,
                      QuantLib::Rate,
                      QuantLib::Volatility>
          (bindObject,
           mStrike,
          mReturnValue
          );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::CapFloorTermVTSVolatility2) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsString()) {
      return Nan::ThrowError("OptionTenor is required.");
  }
  if (info.Length() == 2 || !info[2]->IsArray()) {
      return Nan::ThrowError("Strike is required.");
  }
  if (info.Length() == 3 || !info[3]->IsBoolean()) {
      return Nan::ThrowError("AllowExtrapolation is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  String::Utf8Value strOptionTenor(info[1]->ToString());
  string OptionTenorCpp(strdup(*strOptionTenor));

  // convert js argument to c++ type
  std::vector<double>StrikeCpp;

  Local<Array> StrikeArray = info[2].As<Array>();
  for (unsigned int i = 0; i < StrikeArray->Length(); i++){
    StrikeCpp.push_back(Nan::To<double>(Nan::Get(StrikeArray, i).ToLocalChecked()).FromJust());
  }

  // convert js argument to c++ type
  bool AllowExtrapolationCpp = Nan::To<bool>(info[3]).FromJust();

 
  // launch worker
  CapFloorTermVTSVolatility2Worker* worker = new CapFloorTermVTSVolatility2Worker(
    ObjectIDCpp
,     OptionTenorCpp
,     StrikeCpp
,     AllowExtrapolationCpp
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

void CapFloorTermVolCurveOptionTenorsWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::CapFloorTermVolCurve, QuantLib::CapFloorTermVolCurve)

     
  // loop on the input parameter and populate the return vector
  std::vector<QuantLib::Period> returnValue = ObjectIDLibObjPtr->optionTenors(
      );


  mReturnValue = QuantLibAddin::libraryToVector(returnValue);

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::CapFloorTermVolCurveOptionTenors) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  CapFloorTermVolCurveOptionTenorsWorker* worker = new CapFloorTermVolCurveOptionTenorsWorker(
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

void CapFloorTermVolCurveOptionDatesWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::CapFloorTermVolCurve, QuantLib::CapFloorTermVolCurve)

     
  // loop on the input parameter and populate the return vector
  std::vector<QuantLib::Date> returnValue = ObjectIDLibObjPtr->optionDates(
      );


  mReturnValue = QuantLibAddin::libraryToVector(returnValue);

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::CapFloorTermVolCurveOptionDates) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  CapFloorTermVolCurveOptionDatesWorker* worker = new CapFloorTermVolCurveOptionDatesWorker(
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

void CapFloorTermVolSurfaceOptionTenorsWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::CapFloorTermVolSurface, QuantLib::CapFloorTermVolSurface)

     
  // loop on the input parameter and populate the return vector
  std::vector<QuantLib::Period> returnValue = ObjectIDLibObjPtr->optionTenors(
      );


  mReturnValue = QuantLibAddin::libraryToVector(returnValue);

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::CapFloorTermVolSurfaceOptionTenors) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  CapFloorTermVolSurfaceOptionTenorsWorker* worker = new CapFloorTermVolSurfaceOptionTenorsWorker(
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

void CapFloorTermVolSurfaceOptionDatesWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::CapFloorTermVolSurface, QuantLib::CapFloorTermVolSurface)

     
  // loop on the input parameter and populate the return vector
  std::vector<QuantLib::Date> returnValue = ObjectIDLibObjPtr->optionDates(
      );


  mReturnValue = QuantLibAddin::libraryToVector(returnValue);

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::CapFloorTermVolSurfaceOptionDates) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  CapFloorTermVolSurfaceOptionDatesWorker* worker = new CapFloorTermVolSurfaceOptionDatesWorker(
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

void CapFloorTermVolSurfaceStrikesWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::CapFloorTermVolSurface, QuantLib::CapFloorTermVolSurface)

     
  // loop on the input parameter and populate the return vector
  mReturnValue = ObjectIDLibObjPtr->strikes(
      );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::CapFloorTermVolSurfaceStrikes) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  CapFloorTermVolSurfaceStrikesWorker* worker = new CapFloorTermVolSurfaceStrikesWorker(
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
 