#include <iostream>
#include <memory>
#include <string>

#include "absl/flags/flag.h"
#include "absl/flags/parse.h"
#include <grpcpp/grpcpp.h>
#include "./protos/cppstuff.grpc.pb.h"
#include "parking.h"

ABSL_FLAG(std::string, target, "localhost:50051", "Server address");

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using cppstuff::CppStuff;
using cppstuff::HelloReply;
using cppstuff::HelloRequest;
using cppstuff::CarParkStatusRequest;
using cppstuff::CarParkStatusResponse;

class CppStuffClient {
 public:
  CppStuffClient(std::shared_ptr<Channel> channel)
      : stub_(CppStuff::NewStub(channel)) {}

  // Assembles the client's payload, sends it and presents the response back
  // from the server.
  std::string SayHello(const std::string& user) {
    // Data we are sending to the server.
    HelloRequest request;
    request.set_name(user);

    // Container for the data we expect from the server.
    HelloReply reply;

    // Context for the client. It could be used to convey extra information to
    // the server and/or tweak certain RPC behaviors.
    ClientContext context;

    // The actual RPC.
    Status status = stub_->SayHello(&context, request, &reply);

    // Act upon its status.
    if (status.ok()) {
      return reply.message();
    } else {
      std::cout << status.error_code() << ": " << status.error_message()
                << std::endl;
      return "RPC failed";
    }
  }

  CarParkStatusResponse GetCarParkStatus(const std::string& name) {
    CarParkStatusRequest request;
    request.set_name(name);
    CarParkStatusResponse response;
    ClientContext context;

    Status status = stub_->GetCarParkStatus(&context, request, &response);

    if (status.ok()) {
      return response;
    } else {
      std::cout << status.error_code() << ": " << status.error_message()
                << std::endl;
      throw std::runtime_error("RPC failed");
    }
  }

 private:
  std::unique_ptr<CppStuff::Stub> stub_;
};

int main(int argc, char** argv) {
  absl::ParseCommandLine(argc, argv);
  // Instantiate the client. It requires a channel, out of which the actual RPCs
  // are created. This channel models a connection to an endpoint specified by
  // the argument "--target=" which is the only expected argument.
  std::string target_str = absl::GetFlag(FLAGS_target);
  // We indicate that the channel isn't authenticated (use of
  // InsecureChannelCredentials()).
  CppStuffClient cppStuffClient = grpc::CreateChannel(target_str, grpc::InsecureChannelCredentials());
  
  std::string user("YOLOSWAG");
  std::string reply = cppStuffClient.SayHello(user);
  std::cout << "SayHello received: " << reply << std::endl;

  std::string name("omp");
  CarParkStatusResponse response = cppStuffClient.GetCarParkStatus(name);
  std::cout << "GetCarParkStatus received for \"" << name << "\" car park: " << response.vacancies() << " out of " << response.capacity() << " free." << std::endl;

  return 0;
}
