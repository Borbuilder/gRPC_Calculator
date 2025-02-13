#pragma once

#include "ServerDeclare.h"

#include <atomic>
#include <string>

void RunServer(
    std::atomic<bool>& running, 
    const std::string& server_address
);
