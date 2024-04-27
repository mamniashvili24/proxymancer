#include <map>
#include <string>
#include <unistd.h>
#include "IOManager.h"
#include "ServerConfig.h"
#include "TcpSocketService.h"

using namespace std;

static string FileExtensionsToMimeTypesMap(const string &filePath) {
    const map<string, string> mimeTypes = {
            {".html",  "text/html"},
            {".htm",   "text/html"},
            {".css",   "text/css"},
            {".js",    "application/javascript"},
            {".jpeg",  "image/jpeg"},
            {".jpg",   "image/jpeg"},
            {".png",   "image/png"},
            {".gif",   "image/gif"},
            {".svg",   "image/svg+xml"},
            {".pdf",   "application/pdf"},
            {".json",  "application/json"},
            {".xml",   "application/xml"},
            {".doc",   "application/msword"},
            {".docx",  "application/vnd.openxmlformats-officedocument.wordprocessingml.document"},
            {".xls",   "application/vnd.ms-excel"},
            {".xlsx",  "application/vnd.openxmlformats-officedocument.spreadsheetml.sheet"},
            {".ppt",   "application/vnd.ms-powerpoint"},
            {".pptx",  "application/vnd.openxmlformats-officedocument.presentationml.presentation"},
            {".zip",   "application/zip"},
            {".tar",   "application/x-tar"},
            {".gz",    "application/x-gzip"},
            {".mp3",   "audio/mpeg"},
            {".mp4",   "video/mp4"},
            {".mpeg",  "video/mpeg"},
            {".txt",   "text/plain"},
            {".form",  "application/x-www-form-urlencoded"},
            {".csv",   "text/csv"},
            {".ogg",   "audio/ogg"},
            {".wav",   "audio/wav"},
            {".ogg",   "video/ogg"},
            {".webm",  "video/webm"},
            {".ico",   "image/x-icon"},
            {".woff",  "font/woff"},
            {".woff2", "font/woff2"}
    };

    size_t dotPos = filePath.find_last_of('.');
    if (dotPos != string::npos) {
        string extension = filePath.substr(dotPos);
        auto it = mimeTypes.find(extension);
        if (it != mimeTypes.end()) {
            return it->second;
        }
    }
    return "text/plain";
}

static string GetFilePathFromRequest(const string &request) {
    size_t start = request.find(' ') + 1;
    size_t end = request.find(' ', start);
    string file_path = request.substr(start, end - start);

    file_path = file_path == "/" ?
                ServerConfig::root + "/" + ServerConfig::index
                 : ServerConfig::root + file_path;

    return file_path;
}

static string GenerateResponse(const string &fileContent, const string &filePath) {
    string response;
    if (fileContent.empty()) {
        response = "HTTP/1.1 404 Not Found\r\n\r\n404 Not Found";
    } else {
        string mimeType = FileExtensionsToMimeTypesMap(filePath);
        response = "HTTP/1.1 200 OK\r\nContent-Type: " + mimeType + "\r\n\r\n" + fileContent;
    }

    return response;
}

void TcpSocketService::Run() {
    int socket_file_descriptor = IOManager::CreateTcpSocket();
    IOManager::BindSocketToLoopbackAddress(socket_file_descriptor);

    while (IOManager::BeginListeningForConnections(socket_file_descriptor)) {
        int client_socket_file_descriptor = IOManager::EstablishClientConnection(socket_file_descriptor);
        string content = IOManager::GetHttpRequestContent(client_socket_file_descriptor);

        string file_path = GetFilePathFromRequest(content);
        string file_content = IOManager::ReadAllFile(file_path);

        string response = GenerateResponse(file_content, file_path);
        IOManager::WriteHttpResponse(client_socket_file_descriptor, response);
    }

    close(socket_file_descriptor);
}