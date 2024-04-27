#include <string>
#include <netinet/in.h>

using namespace std;

#ifndef PROXYMANCER_IOMANAGER_H
#define PROXYMANCER_IOMANAGER_H

class IOManager {
public:
    static string ReadAllFile(const string& file_path);

public:
    static int CreateTcpSocket();

public:
    static bool BeginListeningForConnections(int socket_file_descriptor);

public:
    static void BindSocketToLoopbackAddress(int socket_file_descriptor);

public:
    static int EstablishClientConnection(int socket_file_descriptor);

public:
    static string GetHttpRequestContent(int client_socket_file_descriptor);

public:
    static void WriteHttpResponse(int client_socket_file_descriptor, string& response);
};

#endif