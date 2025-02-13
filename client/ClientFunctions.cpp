#include "ClientFunctions.h"

#include <tuple>
#include <sstream>

OperationRequest::Operation ParseOperation(char op)
{
    switch (op)
    {
    case '+': return OperationRequest::ADD;
    case '-': return OperationRequest::SUBSTRACT;
    case '*': return OperationRequest::MULTIPLY;
    case '/': return OperationRequest::DIVIDE;
    default:
        break;
    }
}

std::tuple<double, char, double> Parse(const std::string& input) {
    std::istringstream iss(input);
    std::string a_str, op_str, b_str;

    if (!(iss >> a_str >> op_str >> b_str)) {
        throw std::invalid_argument("Invalid format. Use: number operator number");
    }

    if (op_str.size() != 1) {
        throw std::invalid_argument("Operator must be a single character (+, -, *, /)");
    }

    char op = op_str[0];

    try {
        double a = std::stod(a_str);
        double b = std::stod(b_str);
        return {a, op, b};
    } 
    catch (const std::invalid_argument&) {
        throw std::invalid_argument("Invalid number format");
    } 
    catch (const std::out_of_range&) {
        throw std::out_of_range("Number is out of range");
    }
}

void RunClient(ArithmeticalClient &client)
{
    while(true){
        try
        {
            std::cout << "\nEnter expression (a op b) or 'exit': ";
            std::string input;
            std::getline(std::cin, input);
            if (input == "exit") {
                break;
            }
            auto data = Parse(input);

            auto [result, error] = client.Calculate(
                std::get<0>(data),
                std::get<2>(data),
                ParseOperation(std::get<1>(data))
            );

            if (!error.empty()) {
                std::cerr << "Error: " << error << std::endl;
                if (error.find("UNAVAILABLE") != std::string::npos) {
                    std::cerr << "Server is shutting down" << std::endl;
                    break;
                }
            } else {
                std::cout << "Result: " << result << std::endl;
            }
        }
        catch(const std::exception& e)
        {
            std::cerr << "Input error: " << e.what() << std::endl;
            std::cin.clear();
        }
    }
}