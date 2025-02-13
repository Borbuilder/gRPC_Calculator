#pragma once

#include <grpcpp/grpcpp.h>
#include "../resources/arithmetic.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using grpc::StatusCode;
using arithmetics::Arithmetics;
using arithmetics::OperationRequest;
using arithmetics::OperationResponse;