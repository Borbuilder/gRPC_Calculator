#pragma once

#include "ServerDeclare.h"
#include <atomic>

class ArithmeticalService final: public Arithmetics::Service
{
private:
    std::atomic<bool> shutting_down{false};

public:
    Status Calculate(
        ServerContext* context, 
        const OperationRequest* request, 
        OperationResponse* response
        ) override;

    void PrepareForShutdown();
};
