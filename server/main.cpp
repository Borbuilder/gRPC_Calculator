#include "ServerFunctions.h"

#include <stdexcept>
#include <iostream>

int main() {
    std::atomic<bool> running(false);
    try {
        RunServer(running,"0.0.0.0:50051");
    }
    catch (...) {
        std::cerr << "Unexpected server termination" << std::endl;
    }
    std::cout << "Server stopped gracefully" << std::endl;
    return 0;
}