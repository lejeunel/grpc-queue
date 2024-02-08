#ifndef MODELS_H_
#define MODELS_H_

#include "uuid.h"
#include <string>

struct Task {
  std::string id;
  int field;

  Task(const int &a_field) {
    id = uuid::v4::UUID::New().String();
    field = a_field;
  }
};

#endif // MODELS_H_
