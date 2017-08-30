/* 
  Copyright (C) 2016 -2017 Jerry Jin
*/

#ifndef prices_h
#define prices_h
#include <nan.h>
#include <string>
#include <queue>
#include <utility>

#include "../quantlibxl.hpp"

#include <oh/objecthandler.hpp>

using namespace node;
using namespace v8;
using namespace std;


class MidEquivalentWorker {
  public:
    double mBid;
    double mAsk;
    double mLast;
    double mClose;

    double mReturnValue;

    string mError;

    MidEquivalentWorker(
      double Bid
,       double Ask
,       double Last
,       double Close
     )
      {
        mBid = Bid;
        mAsk = Ask;
        mLast = Last;
        mClose = Close;
      };

    void Execute();
};

class MidSafeWorker {
  public:
    double mBid;
    double mAsk;

    double mReturnValue;

    string mError;

    MidSafeWorker(
      double Bid
,       double Ask
     )
      {
        mBid = Bid;
        mAsk = Ask;
      };

    void Execute();
};
 
#endif
