#include "../src/include/app.h"
#include "../src/include/local_database.h"
#include "../src/include/server.h"
#include "app_server.grpc.pb.h"
#include <catch2/catch_test_macros.hpp>
#include <grpcpp/create_channel.h>
#include <grpcpp/server.h>
#include <grpcpp/server_builder.h>
#include <memory>

using app::AppServer;
using grpc::Channel;
using grpc::ClientContext;
using grpc::CreateChannel;
using grpc::InsecureChannelCredentials;
using grpc::InsecureServerCredentials;

class TestingClient {
public:
  explicit TestingClient(AppServer::StubInterface *a_stub) : stub(a_stub) {}

  void test_push_task() {
    ClientContext context;
    TaskSchema request;
    TaskSchema response;
    request.set_field(42);
    Status s = stub->PushTask(&context, request, &response);
    REQUIRE(request.field() == response.field());
    REQUIRE(s.ok());
  }

private:
  AppServer::StubInterface *stub;
};

ServerImpl make_test_server() {
  auto app = std::make_unique<App>(std::make_unique<InMemoryDBCreator>(),
                                   std::make_unique<Worker>());
  return ServerImpl(std::move(app));
}

TEST_CASE("Submit tasks", "[submit]") {
  std::ostringstream server_address_;
  std::unique_ptr<Server> server_;
  std::unique_ptr<AppServer::Stub> stub_;

  auto service_ = make_test_server();

  int port = 9090;
  server_address_ << "localhost:" << port;

  // Setup server for local insecure channel
  ServerBuilder builder;
  builder.AddListeningPort(server_address_.str(), InsecureServerCredentials());
  builder.RegisterService(&service_);
  server_ = builder.BuildAndStart();
  std::shared_ptr<grpc::Channel> channel =
      CreateChannel(server_address_.str(), InsecureChannelCredentials());
  stub_ = AppServer::NewStub(channel);
  service_.run();

  SECTION("push one task") {

    TestingClient client(stub_.get());
    client.test_push_task();
  }
  service_.stop();
}
