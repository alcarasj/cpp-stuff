# cpp-stuff
This is a custom gRPC C++ service.

## Setup
### Building the gRPC libraries
Make sure `cmake` and the [prerequisites for gRPC](https://github.com/grpc/grpc/blob/master/BUILDING.md#pre-requisites) are installed on your machine.
1. Clone the `grpc` submodule with `git submodule update --init`
2. `cd grpc`
3. Clone the third-party library submodules that `grpc` requires with `git submodule update --init`
4. Create the build output directory with `mkdir cmake/build && cd cmake/build`
5. Generate the Makefiles with `cmake ../..`
6. Make the gRPC C++ libraries with `make`
### Building the gRPC server and client
TO-DO