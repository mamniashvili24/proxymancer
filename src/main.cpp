#include "TcpSocketService.h"
#include "ServerConfig.h"

int main() {
    ServerConfig config;
    TcpSocketService::Run();
    return 0;
}