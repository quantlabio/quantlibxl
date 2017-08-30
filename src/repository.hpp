/* 
  Copyright (C) 2016 -2017 Jerry Jin
*/

#ifndef repository_h
#define repository_h
#include <nan.h>
#include <string>
#include <queue>
#include <utility>

#include "../quantlibxl.hpp"

#include <oh/objecthandler.hpp>

using namespace node;
using namespace v8;
using namespace std;


class ObjectPropertyNamesWorker {
  public:
    string mObjectID;

    std::vector<string> mReturnValue;

    string mError;

    ObjectPropertyNamesWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class DeleteObjectWorker {
  public:
    string mObjectID;

    string mError;

    DeleteObjectWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class DeleteObjectsWorker {
  public:
    std::vector<string> mObjectID;

    string mError;

    DeleteObjectsWorker(
      std::vector<string> ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class DeleteAllObjectsWorker {
  public:
    bool mDeletePermanent;

    string mError;

    DeleteAllObjectsWorker(
      bool DeletePermanent
     )
      {
        mDeletePermanent = DeletePermanent;
      };

    void Execute();
};

class ListObjectIDsWorker {
  public:
    string mRegex;

    std::vector<string> mReturnValue;

    string mError;

    ListObjectIDsWorker(
      string Regex
     )
      {
        mRegex = Regex;
      };

    void Execute();
};
 
#endif
