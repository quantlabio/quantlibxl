/* 
  Copyright (C) 2016 -2017 Jerry Jin
*/

#ifndef settings_h
#define settings_h
#include <nan.h>
#include <string>
#include <queue>
#include <utility>

#include "../quantlibxl.hpp"

#include <oh/objecthandler.hpp>

using namespace node;
using namespace v8;
using namespace std;


class SettingsEvaluationDateWorker {
  public:

    long mReturnValue;

    string mError;

    SettingsEvaluationDateWorker(
    )
      {
      };

    void Execute();
};

class SettingsSetEvaluationDateWorker {
  public:
    ObjectHandler::property_t mEvalDate;

    string mError;

    SettingsSetEvaluationDateWorker(
      ObjectHandler::property_t EvalDate
     )
      {
        mEvalDate = EvalDate;
      };

    void Execute();
};

class SettingsEnforceTodaysHistoricFixingsWorker {
  public:

    bool mReturnValue;

    string mError;

    SettingsEnforceTodaysHistoricFixingsWorker(
    )
      {
      };

    void Execute();
};

class SettingsSetEnforceTodaysHistoricFixingsWorker {
  public:
    bool mBoolean;

    string mError;

    SettingsSetEnforceTodaysHistoricFixingsWorker(
      bool Boolean
     )
      {
        mBoolean = Boolean;
      };

    void Execute();
};
 
#endif
