# cpp-stuff
This is a custom gRPC C++ server and client used for learning C++.

## Setup
This was tested in Ubuntu 20.04 LTS on WSL.
### Installing the gRPC library
gRPC C++ libraries must be installed on your machine to be able to build the project. Make sure CMake >3.27 and the [prerequisites for gRPC](https://github.com/grpc/grpc/blob/master/BUILDING.md#pre-requisites) are installed on your machine. You only need to do this once.
1. Clone the gRPC repo at a directory of your choosing with `git clone --depth 1 --branch v1.59.0 https://github.com/grpc/grpc.git`  
2. `cd` to the repo and initialize the submodules with `git submodule update --init`
3. Set the CMake install directory with `export MY_INSTALL_DIR=$HOME/.local` (this is where the gRPC libraries will be installed)
4. Create the build output directory with `mkdir cmake/build && cd cmake/build`
5. Generate the Makefiles with `cmake -DgRPC_INSTALL=ON -DgRPC_BUILD_TESTS=OFF -DCMAKE_INSTALL_PREFIX=$MY_INSTALL_DIR ../..`
6. Make the gRPC libraries with `make -j 4`
7. Install gRPC with `make install`
### Building the project
1. `cd` to repo root.
2. Set the CMake install directory with `export MY_INSTALL_DIR=$HOME/.local`
3. Generate the Makefile with `cmake -DCMAKE_PREFIX_PATH=$MY_INSTALL_DIR .`
4. Make the binaries with `make -j 4`
5. Run the server with `./bin/server`
6. Run the client with `./bin/client`
### Building the server Docker image
1. Build the project as normal.
2. `docker build . -t alcarasj/cpp-stuff`
3. `docker run -p 8080:50051 alcarasj/cpp-stuff:latest`
4. Run the client with `./bin/client`
### Running unit tests
1. Build the project as normal.
2. Run the tests with `ctest`
3. Debug tests with `gdb ./bin/parking_test`
4. Set breakpoint in `gdb` with `b parking_test.cc:123`