/* 
  Copyright (C) 2016 -2017 Jerry Jin
*/

#ifndef abcd_h
#define abcd_h
#include <nan.h>
#include <string>
#include <queue>
#include <utility>

#include "../quantlibxl.hpp"

#include <oh/objecthandler.hpp>

using namespace node;
using namespace v8;
using namespace std;


class AbcdFunctionWorker {
  public:
    string mObjectID;
    double mA;
    double mB;
    double mC;
    double mD;

    string mReturnValue;

    string mError;

    AbcdFunctionWorker(
      string ObjectID
,       double A
,       double B
,       double C
,       double D
     )
      {
        mObjectID = ObjectID;
        mA = A;
        mB = B;
        mC = C;
        mD = D;
      };

    void Execute();
};

class AbcdCalibrationWorker {
  public:
    string mObjectID;
    std::vector<double> mTimes;
    std::vector<double> mBlackVols;
    double mA;
    double mB;
    double mC;
    double mD;
    bool mAIsFixed;
    bool mBIsFixed;
    bool mCIsFixed;
    bool mDIsFixed;
    bool mVegaWeighted;
    string mEndCriteria;
    string mMethod;

    string mReturnValue;

    string mError;

    AbcdCalibrationWorker(
      string ObjectID
,       std::vector<double> Times
,       std::vector<double> BlackVols
,       double A
,       double B
,       double C
,       double D
,       bool AIsFixed
,       bool BIsFixed
,       bool CIsFixed
,       bool DIsFixed
,       bool VegaWeighted
,       string EndCriteria
,       string Method
     )
      {
        mObjectID = ObjectID;
        mTimes = Times;
        mBlackVols = BlackVols;
        mA = A;
        mB = B;
        mC = C;
        mD = D;
        mAIsFixed = AIsFixed;
        mBIsFixed = BIsFixed;
        mCIsFixed = CIsFixed;
        mDIsFixed = DIsFixed;
        mVegaWeighted = VegaWeighted;
        mEndCriteria = EndCriteria;
        mMethod = Method;
      };

    void Execute();
};

class AbcdFunctionInstantaneousValueWorker {
  public:
    string mObjectID;
    std::vector<double> mU;

    std::vector<double> mReturnValue;

    string mError;

    AbcdFunctionInstantaneousValueWorker(
      string ObjectID
,       std::vector<double> U
     )
      {
        mObjectID = ObjectID;
        mU = U;
      };

    void Execute();
};

class AbcdFunctionInstantaneousCovarianceWorker {
  public:
    string mObjectID;
    std::vector<double> mU;
    double mT;
    double mS;

    std::vector<double> mReturnValue;

    string mError;

    AbcdFunctionInstantaneousCovarianceWorker(
      string ObjectID
,       std::vector<double> U
,       double T
,       double S
     )
      {
        mObjectID = ObjectID;
        mU = U;
        mT = T;
        mS = S;
      };

    void Execute();
};

class AbcdFunctionInstantaneousVarianceWorker {
  public:
    string mObjectID;
    std::vector<double> mU;
    double mT;

    std::vector<double> mReturnValue;

    string mError;

    AbcdFunctionInstantaneousVarianceWorker(
      string ObjectID
,       std::vector<double> U
,       double T
     )
      {
        mObjectID = ObjectID;
        mU = U;
        mT = T;
      };

    void Execute();
};

class AbcdFunctionInstantaneousVolatilityWorker {
  public:
    string mObjectID;
    std::vector<double> mU;
    double mT;

    std::vector<double> mReturnValue;

    string mError;

    AbcdFunctionInstantaneousVolatilityWorker(
      string ObjectID
,       std::vector<double> U
,       double T
     )
      {
        mObjectID = ObjectID;
        mU = U;
        mT = T;
      };

    void Execute();
};

class AbcdFunctionCovarianceWorker {
  public:
    string mObjectID;
    double mTMin;
    std::vector<double> mTMax;
    double mT;
    double mS;

    std::vector<double> mReturnValue;

    string mError;

    AbcdFunctionCovarianceWorker(
      string ObjectID
,       double TMin
,       std::vector<double> TMax
,       double T
,       double S
     )
      {
        mObjectID = ObjectID;
        mTMin = TMin;
        mTMax = TMax;
        mT = T;
        mS = S;
      };

    void Execute();
};

class AbcdFunctionVarianceWorker {
  public:
    string mObjectID;
    double mTMin;
    std::vector<double> mTMax;
    double mT;

    std::vector<double> mReturnValue;

    string mError;

    AbcdFunctionVarianceWorker(
      string ObjectID
,       double TMin
,       std::vector<double> TMax
,       double T
     )
      {
        mObjectID = ObjectID;
        mTMin = TMin;
        mTMax = TMax;
        mT = T;
      };

    void Execute();
};

class AbcdFunctionVolatilityWorker {
  public:
    string mObjectID;
    double mTMin;
    std::vector<double> mTMax;
    double mT;

    std::vector<double> mReturnValue;

    string mError;

    AbcdFunctionVolatilityWorker(
      string ObjectID
,       double TMin
,       std::vector<double> TMax
,       double T
     )
      {
        mObjectID = ObjectID;
        mTMin = TMin;
        mTMax = TMax;
        mT = T;
      };

    void Execute();
};

class AbcdFunctionShortTermVolatilityWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    AbcdFunctionShortTermVolatilityWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class AbcdFunctionLongTermVolatilityWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    AbcdFunctionLongTermVolatilityWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class AbcdFunctionMaximumLocationWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    AbcdFunctionMaximumLocationWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class AbcdFunctionMaximumVolatilityWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    AbcdFunctionMaximumVolatilityWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class AbcdFunctionAWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    AbcdFunctionAWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class AbcdFunctionBWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    AbcdFunctionBWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class AbcdFunctionCWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    AbcdFunctionCWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class AbcdFunctionDWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    AbcdFunctionDWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class AbcdDFunctionWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    AbcdDFunctionWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class AbcdCalibrationComputeWorker {
  public:
    string mObjectID;

    string mError;

    AbcdCalibrationComputeWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class AbcdCalibrationKWorker {
  public:
    string mObjectID;
    std::vector<double> mTimes;
    std::vector<double> mBlackVols;

    std::vector<double> mReturnValue;

    string mError;

    AbcdCalibrationKWorker(
      string ObjectID
,       std::vector<double> Times
,       std::vector<double> BlackVols
     )
      {
        mObjectID = ObjectID;
        mTimes = Times;
        mBlackVols = BlackVols;
      };

    void Execute();
};

class AbcdCalibrationErrorWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    AbcdCalibrationErrorWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class AbcdCalibrationMaxErrorWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    AbcdCalibrationMaxErrorWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class AbcdCalibrationEndCriteriaWorker {
  public:
    string mObjectID;

    string mReturnValue;

    string mError;

    AbcdCalibrationEndCriteriaWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class AbcdCalibrationAWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    AbcdCalibrationAWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class AbcdCalibrationBWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    AbcdCalibrationBWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class AbcdCalibrationCWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    AbcdCalibrationCWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class AbcdCalibrationDWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    AbcdCalibrationDWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};
 
#endif
