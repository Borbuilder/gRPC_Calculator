#include "ServerFunctions.h"
#include "ArithmeticalService.h"

#include <iostream>
#include <string>
#include <thread>
#include <atomic>
#include <stdexcept>

void RunServer(std::atomic<bool>& running, const std::string& server_address) 
{
    try {
        ArithmeticalService service;

        ServerBuilder builder;
        builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
        builder.RegisterService(&service);

        std::unique_ptr<Server> server(builder.BuildAndStart());
        std::cout << "Server listening on " << server_address << std::endl;
        
        running = true;
        std::thread shutdown_thread([&]() {
            std::cout << "Enter 'exit' to stop the server..." << std::endl;
            std::string command;
            while (running) {
                std::getline(std::cin, command);
                if (command == "exit") {
                    service.PrepareForShutdown();
                    server->Shutdown();
                    running = false;
                    break;
                }
            }
        });

        server->Wait();
        shutdown_thread.join();
    }
    catch (const std::exception& e) {
        std::cerr << "Server error: " << e.what() << std::endl;
        running = false;
    }
}

