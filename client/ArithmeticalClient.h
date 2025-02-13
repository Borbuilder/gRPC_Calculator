#pragma once

#include "ClientDeclare.h"

class ArithmeticalClient {
    std::shared_ptr<Channel> channel_;
    std::unique_ptr<Arithmetics::Stub> stub_;
    std::atomic<bool> server_available{true};
    
public:
    ArithmeticalClient(std::shared_ptr<Channel> channel)
        : channel_(channel), stub_(Arithmetics::NewStub(channel)) {}

    std::pair<double, std::string> Calculate(
        double a, 
        double b, 
        OperationRequest::Operation op
    ); 
    bool CheckConnection();
    bool TryReconnect();
};