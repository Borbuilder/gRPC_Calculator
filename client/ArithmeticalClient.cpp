#include "ArithmeticalClient.h"

std::pair<double, std::string> ArithmeticalClient::Calculate(
    double a, 
    double b, 
    OperationRequest::Operation op
) 
{
    if (!server_available){
        return {NAN, "Server unavailable"};
    } 

    OperationRequest request;
    request.set_a(a);
    request.set_b(b);
    request.set_op(op);

    OperationResponse response;
    ClientContext context;
    context.set_deadline(std::chrono::system_clock::now() + std::chrono::seconds(3));

    try {
        Status status = stub_->Calculate(&context, request, &response);

        if (!status.ok()) {
            if (status.error_code() == StatusCode::UNAVAILABLE) {
                server_available = false;
            }
            return {NAN, status.error_message() + " | Details: " + response.error()};
        }
        return {response.result(), ""};
    }
    catch (...) {
        server_available = false;
        return {NAN, "Connection failed"};
    }
}

bool ArithmeticalClient::CheckConnection() {
    auto state = channel_->GetState(true);
    server_available = (state == GRPC_CHANNEL_READY);
    return server_available;
}

bool ArithmeticalClient::TryReconnect() {
    channel_ = grpc::CreateChannel("localhost:50051", 
                  grpc::InsecureChannelCredentials());
    stub_ = Arithmetics::NewStub(channel_);
    server_available = true;
    return CheckConnection();
}