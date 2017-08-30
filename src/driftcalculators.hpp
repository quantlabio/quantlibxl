/* 
  Copyright (C) 2016 -2017 Jerry Jin
*/

#ifndef driftcalculators_h
#define driftcalculators_h
#include <nan.h>
#include <string>
#include <queue>
#include <utility>

#include "../quantlibxl.hpp"

#include <oh/objecthandler.hpp>

using namespace node;
using namespace v8;
using namespace std;


class LMMDriftCalculatorWorker {
  public:
    string mObjectID;
    std::vector< std::vector<double> > mPseudo_square_root;
    std::vector<double> mDisplacements;
    std::vector<double> mTaus;
    long mNumeraire;
    long mAlive;

    string mReturnValue;

    string mError;

    LMMDriftCalculatorWorker(
      string ObjectID
,       std::vector< std::vector<double> > Pseudo_square_root
,       std::vector<double> Displacements
,       std::vector<double> Taus
,       long Numeraire
,       long Alive
     )
      {
        mObjectID = ObjectID;
        mPseudo_square_root = Pseudo_square_root;
        mDisplacements = Displacements;
        mTaus = Taus;
        mNumeraire = Numeraire;
        mAlive = Alive;
      };

    void Execute();
};

class LMMNormalDriftCalculatorWorker {
  public:
    string mObjectID;
    std::vector< std::vector<double> > mPseudo_square_root;
    std::vector<double> mTaus;
    long mNumeraire;
    long mAlive;

    string mReturnValue;

    string mError;

    LMMNormalDriftCalculatorWorker(
      string ObjectID
,       std::vector< std::vector<double> > Pseudo_square_root
,       std::vector<double> Taus
,       long Numeraire
,       long Alive
     )
      {
        mObjectID = ObjectID;
        mPseudo_square_root = Pseudo_square_root;
        mTaus = Taus;
        mNumeraire = Numeraire;
        mAlive = Alive;
      };

    void Execute();
};

class CMSMMDriftCalculatorWorker {
  public:
    string mObjectID;
    std::vector< std::vector<double> > mPseudo_square_root;
    std::vector<double> mDisplacements;
    std::vector<double> mTaus;
    long mNumeraire;
    long mAlive;
    long mSpanningFwds;

    string mReturnValue;

    string mError;

    CMSMMDriftCalculatorWorker(
      string ObjectID
,       std::vector< std::vector<double> > Pseudo_square_root
,       std::vector<double> Displacements
,       std::vector<double> Taus
,       long Numeraire
,       long Alive
,       long SpanningFwds
     )
      {
        mObjectID = ObjectID;
        mPseudo_square_root = Pseudo_square_root;
        mDisplacements = Displacements;
        mTaus = Taus;
        mNumeraire = Numeraire;
        mAlive = Alive;
        mSpanningFwds = SpanningFwds;
      };

    void Execute();
};

class SMMDriftCalculatorWorker {
  public:
    string mObjectID;
    std::vector< std::vector<double> > mPseudo_square_root;
    std::vector<double> mDisplacements;
    std::vector<double> mTaus;
    long mNumeraire;
    long mAlive;

    string mReturnValue;

    string mError;

    SMMDriftCalculatorWorker(
      string ObjectID
,       std::vector< std::vector<double> > Pseudo_square_root
,       std::vector<double> Displacements
,       std::vector<double> Taus
,       long Numeraire
,       long Alive
     )
      {
        mObjectID = ObjectID;
        mPseudo_square_root = Pseudo_square_root;
        mDisplacements = Displacements;
        mTaus = Taus;
        mNumeraire = Numeraire;
        mAlive = Alive;
      };

    void Execute();
};

class LMMDriftCalculatorComputePlainWorker {
  public:
    string mObjectID;
    string mCurveState;

    std::vector<double> mReturnValue;

    string mError;

    LMMDriftCalculatorComputePlainWorker(
      string ObjectID
,       string CurveState
     )
      {
        mObjectID = ObjectID;
        mCurveState = CurveState;
      };

    void Execute();
};

class LMMDriftCalculatorComputeReducedWorker {
  public:
    string mObjectID;
    string mCurveState;

    std::vector<double> mReturnValue;

    string mError;

    LMMDriftCalculatorComputeReducedWorker(
      string ObjectID
,       string CurveState
     )
      {
        mObjectID = ObjectID;
        mCurveState = CurveState;
      };

    void Execute();
};

class LMMDriftCalculatorComputeWorker {
  public:
    string mObjectID;
    string mCurveState;

    std::vector<double> mReturnValue;

    string mError;

    LMMDriftCalculatorComputeWorker(
      string ObjectID
,       string CurveState
     )
      {
        mObjectID = ObjectID;
        mCurveState = CurveState;
      };

    void Execute();
};

class LMMNormalDriftCalculatorComputePlainWorker {
  public:
    string mObjectID;
    string mCurveState;

    std::vector<double> mReturnValue;

    string mError;

    LMMNormalDriftCalculatorComputePlainWorker(
      string ObjectID
,       string CurveState
     )
      {
        mObjectID = ObjectID;
        mCurveState = CurveState;
      };

    void Execute();
};

class LMMNormalDriftCalculatorComputeReducedWorker {
  public:
    string mObjectID;
    string mCurveState;

    std::vector<double> mReturnValue;

    string mError;

    LMMNormalDriftCalculatorComputeReducedWorker(
      string ObjectID
,       string CurveState
     )
      {
        mObjectID = ObjectID;
        mCurveState = CurveState;
      };

    void Execute();
};

class LMMNormalDriftCalculatorComputeWorker {
  public:
    string mObjectID;
    string mCurveState;

    std::vector<double> mReturnValue;

    string mError;

    LMMNormalDriftCalculatorComputeWorker(
      string ObjectID
,       string CurveState
     )
      {
        mObjectID = ObjectID;
        mCurveState = CurveState;
      };

    void Execute();
};

class CMSMMDriftCalculatorComputeWorker {
  public:
    string mObjectID;
    string mCurveState;

    std::vector<double> mReturnValue;

    string mError;

    CMSMMDriftCalculatorComputeWorker(
      string ObjectID
,       string CurveState
     )
      {
        mObjectID = ObjectID;
        mCurveState = CurveState;
      };

    void Execute();
};

class SMMDriftCalculatorComputeWorker {
  public:
    string mObjectID;
    string mCurveState;

    std::vector<double> mReturnValue;

    string mError;

    SMMDriftCalculatorComputeWorker(
      string ObjectID
,       string CurveState
     )
      {
        mObjectID = ObjectID;
        mCurveState = CurveState;
      };

    void Execute();
};
 
#endif
