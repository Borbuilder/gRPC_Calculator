#pragma once

#include "ClientDeclare.h"
#include "ArithmeticalClient.h"

OperationRequest::Operation ParseOperation(char op);
std::tuple< double, char, double> Parse(const std::string& input);
void RunClient(ArithmeticalClient& client);