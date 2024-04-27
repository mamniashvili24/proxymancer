#include <map>
#include <string>
#include "IOManager.h"
#include "ServerConfig.h"

using namespace std;

#define CONFIG_FILE "config.txt"

map<string, string> config;
int ServerConfig::port;
string ServerConfig::root;
string ServerConfig::index;

static void ParseConfigContent(const string &content) {
    size_t startPos = 0;
    size_t endPos = content.find('\n');

    while (endPos != string::npos) {
        string line = content.substr(startPos, endPos - startPos);

        // Split each line into key-value pair
        size_t delimiterPos = line.find('=');
        if (delimiterPos != string::npos) {
            string key = line.substr(0, delimiterPos);
            string value = line.substr(delimiterPos + 1);
            config[key] = value;
        }

        startPos = endPos + 1;
        endPos = content.find('\n', startPos);
    }
}

static void SetPort() {
    auto it(config.find("port"));
    ServerConfig::port = stoi(it->second);
}

static void SetRoot() {
    auto it(config.find("root"));
    ServerConfig::root = it->second;
}

static void SetIndex() {
    auto it(config.find("index"));
    ServerConfig::index = it->second;
}

ServerConfig::ServerConfig() {
    string content = IOManager::ReadAllFile(CONFIG_FILE);
    ParseConfigContent(content);
    SetPort();
    SetRoot();
    SetIndex();
}