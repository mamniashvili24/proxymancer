#include <string>
#include <fstream>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "IOManager.h"
#include "ServerConfig.h"

using namespace std;

void IOManager::BindSocketToLoopbackAddress(int socket_file_descriptor) {
    sockaddr_in server_address{
            .sin_family = AF_INET,
            .sin_port = htons(ServerConfig::port),
            .sin_addr.s_addr = htonl(INADDR_LOOPBACK),
    };

    if (::bind(socket_file_descriptor, (struct sockaddr *) &server_address, sizeof(server_address)) == -1) {
        close(socket_file_descriptor);
        exit(EXIT_FAILURE);
    }
}

string IOManager::ReadAllFile(const string &file_path) {
    string content;
    ifstream file(file_path);
    if (file) {
        content = string(istreambuf_iterator<char>(file), istreambuf_iterator<char>());
    }

    return content;
}

int IOManager::CreateTcpSocket() {
    int socket_file_descriptor = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_file_descriptor == -1) {
        exit(EXIT_FAILURE);
    }

    return socket_file_descriptor;
}

bool IOManager::BeginListeningForConnections(int socket_file_descriptor) {
    if (listen(socket_file_descriptor, 5) == -1) {
        return BeginListeningForConnections(socket_file_descriptor);
    }

    return true;
}

int IOManager::EstablishClientConnection(int socket_file_descriptor) {
    sockaddr_in client_address{};
    socklen_t client_length = sizeof(client_address);
    int client_socket_file_descriptor = accept(socket_file_descriptor, (struct sockaddr *) &client_address,
                                               &client_length);

    if (client_socket_file_descriptor == -1) {
        return EstablishClientConnection(socket_file_descriptor);
    }

    return client_socket_file_descriptor;
}

string IOManager::GetHttpRequestContent(int client_socket_file_descriptor) {
    string content;
    const int BUFFER_SIZE = 1024;
    char buffer[BUFFER_SIZE];
    ssize_t bytes_read = read(client_socket_file_descriptor, buffer, BUFFER_SIZE);

    if (bytes_read > 0) {
        content = string(buffer, bytes_read);
    }

    return content;
}

void IOManager::WriteHttpResponse(int client_socket_file_descriptor, string &response) {
    send(client_socket_file_descriptor, response.c_str(), response.size(), 0);
    close(client_socket_file_descriptor);
}