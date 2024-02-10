#ifndef SERVER_H_
#define SERVER_H_
#include "app.h"
#include "database.h"
#include "my_service.grpc.pb.h"
#include <grpc/grpc.h>
#include <grpcpp/server.h>
#include <grpcpp/server_context.h>
#include <iostream>

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::ServerReader;
using grpc::ServerWriter;
using grpc::Status;
using myservice::MyService;
using myservice::TaskSchema;

class ServerImpl final : public MyService::Service {
public:
  ServerImpl(std::unique_ptr<App> a_app) : m_app(std::move(a_app)){};
  Status PushTask(ServerContext *context, const TaskSchema *request,
                  TaskSchema *response) {
    auto new_task = Task(request->field());
    m_app->push_task(new_task);
    response->set_field(new_task.field);
    response->set_id(new_task.id);
    return Status::OK;
  };
  IDBSession *db_session() { return m_app->get_db(); };
  void run() { m_app->run(); };
  void stop() { m_app->stop(); };

private:
  std::unique_ptr<App> m_app;
};
#endif // SERVER_H_
