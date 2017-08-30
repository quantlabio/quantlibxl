/* 
  Copyright (C) 2016 -2017 Jerry Jin
*/

#ifndef randomsequencegenerator_h
#define randomsequencegenerator_h
#include <nan.h>
#include <string>
#include <queue>
#include <utility>

#include "../quantlibxl.hpp"

#include <oh/objecthandler.hpp>

using namespace node;
using namespace v8;
using namespace std;


class MersenneTwisterRsgWorker {
  public:
    string mObjectID;
    long mDimension;
    long mSeed;

    string mReturnValue;

    string mError;

    MersenneTwisterRsgWorker(
      string ObjectID
,       long Dimension
,       long Seed
     )
      {
        mObjectID = ObjectID;
        mDimension = Dimension;
        mSeed = Seed;
      };

    void Execute();
};

class FaureRsgWorker {
  public:
    string mObjectID;
    long mDimension;

    string mReturnValue;

    string mError;

    FaureRsgWorker(
      string ObjectID
,       long Dimension
     )
      {
        mObjectID = ObjectID;
        mDimension = Dimension;
      };

    void Execute();
};

class HaltonRsgWorker {
  public:
    string mObjectID;
    long mDimension;
    long mSeed;

    string mReturnValue;

    string mError;

    HaltonRsgWorker(
      string ObjectID
,       long Dimension
,       long Seed
     )
      {
        mObjectID = ObjectID;
        mDimension = Dimension;
        mSeed = Seed;
      };

    void Execute();
};

class SobolRsgWorker {
  public:
    string mObjectID;
    long mDimension;
    long mSeed;

    string mReturnValue;

    string mError;

    SobolRsgWorker(
      string ObjectID
,       long Dimension
,       long Seed
     )
      {
        mObjectID = ObjectID;
        mDimension = Dimension;
        mSeed = Seed;
      };

    void Execute();
};

class VariatesWorker {
  public:
    string mObjectID;
    long mSamples;

    std::vector< std::vector<double> > mReturnValue;

    string mError;

    VariatesWorker(
      string ObjectID
,       long Samples
     )
      {
        mObjectID = ObjectID;
        mSamples = Samples;
      };

    void Execute();
};

class RandWorker {
  public:

    double mReturnValue;

    string mError;

    RandWorker(
    )
      {
      };

    void Execute();
};

class RandomizeWorker {
  public:
    long mSeed;

    string mError;

    RandomizeWorker(
      long Seed
     )
      {
        mSeed = Seed;
      };

    void Execute();
};
 
#endif
