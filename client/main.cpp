#include "ClientFunctions.h"

#include <thread>
#include <stdexcept>
#include <iostream>
#include <string>
#include <chrono>

int main() {
    ArithmeticalClient client(grpc::CreateChannel(
        "localhost:50051", grpc::InsecureChannelCredentials()));
    
    size_t reconnection_count{};
    while (true) {
        if (client.CheckConnection()) {
            RunClient(client);
        } else {
            std::cerr << "Server unavailable. Trying to reconnect in 5s...\n";
            std::this_thread::sleep_for(std::chrono::seconds(5));
            if (!client.TryReconnect()) {
                std::cerr << "Reconnection failed.\n";
                ++reconnection_count;
                if(reconnection_count > 3){
                    std::cerr << "Server is currently unavailable. You'll be lucky next time:)\n";
                    break;
                }
            }
        }
    }
    
    return 0;
}