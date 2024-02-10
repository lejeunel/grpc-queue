#ifndef MODELS_H_
#define MODELS_H_

#include "uuid.h"
#include <string>

enum class TaskStatus { pending, done };

struct Task {
  std::string id = uuid::v4::UUID::New().String();
  int field;
  TaskStatus status = TaskStatus::pending;

  Task(const int &a_field) { field = a_field; }
};

#endif // MODELS_H_
