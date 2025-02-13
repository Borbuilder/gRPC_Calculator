#pragma once

#include <grpcpp/grpcpp.h>
#include "../resources/arithmetic.grpc.pb.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using grpc::StatusCode;
using arithmetics::Arithmetics;
using arithmetics::OperationRequest;
using arithmetics::OperationResponse;