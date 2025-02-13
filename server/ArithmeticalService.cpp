#include "ArithmeticalService.h"
#include <stdexcept>

Status ArithmeticalService::Calculate(
    ServerContext* context, 
    const OperationRequest* request, 
    OperationResponse* response)
{
    if(shutting_down){
        return Status(StatusCode::UNAVAILABLE, "Server is shutting down");
    }

    try
    {
        double a = request->a();
        double b = request->b();

        switch (request->op())
        {
        case arithmetics::OperationRequest_Operation_ADD:
            response->set_result(a + b);
            break;
        case arithmetics::OperationRequest_Operation_SUBSTRACT:
            response->set_result(a - b);
            break;
        case arithmetics::OperationRequest_Operation_MULTIPLY:
            response->set_result(a * b);
            break;
        case arithmetics::OperationRequest_Operation_DIVIDE:
            if(b == 0){
                throw std::runtime_error("Division by zero");
            }
            response->set_result(a / b);
            break;
        default:
            break;
        }

        return Status::OK;
    }
    catch(const std::exception& e)
    {
        response->set_error(e.what());
        return Status(StatusCode::INVALID_ARGUMENT, e.what());
    }
}

void ArithmeticalService::PrepareForShutdown()
{
    shutting_down = true;
}