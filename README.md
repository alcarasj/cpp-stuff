# cpp-stuff
This is a custom gRPC C++ server and client.

## Setup
### Building the gRPC libraries
This must be done before building the server and client. Make sure `cmake` and the [prerequisites for gRPC](https://github.com/grpc/grpc/blob/master/BUILDING.md#pre-requisites) are installed on your machine.
1. Initialize the `grpc` submodule with `git submodule update --init`
2. `cd grpc`
3. Initialize the third-party library submodules that `grpc` requires with `git submodule update --init`
4. Set the CMake install directory with `export MY_INSTALL_DIR=$HOME/.local`
5. Create the build output directory with `mkdir cmake/build && cd cmake/build`
6. Generate the Makefiles with `cmake -DgRPC_INSTALL=ON -DgRPC_BUILD_TESTS=OFF -DCMAKE_INSTALL_PREFIX=$MY_INSTALL_DIR ../..`
7. Make the gRPC libraries with `make -j 4`
8. Install gRPC with `make install`
### Building the gRPC server and client
1. `cd` to repo root.
2. Set the CMake install directory with `export MY_INSTALL_DIR=$HOME/.local`
3. Generate the Makefile with `cmake -DCMAKE_PREFIX_PATH=$MY_INSTALL_DIR .`
4. Make the server and client with `make -j 4`
5. Run the server with `./bin/server`
6. Run the client with `./bin/client`
### Building the server Docker image
1. Build the server and client as normal.
2. `docker build . -t alcarasj/cpp-stuff`
3. `docker run -p 8080:50051 alcarasj/cpp-stuff:latest`
4. Run the client with `./bin/client`