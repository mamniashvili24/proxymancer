#ifndef PROXYMANCER_PROXYMANCERSERVERCONFIG_H
#define PROXYMANCER_PROXYMANCERSERVERCONFIG_H

#include <iostream>
#include <string>
#include <map>
#include <string>

using namespace std;

class ServerConfig {
public:
    ServerConfig();

public:
    static int port;

public:
    static string root;

public:
    static string index;
};

#endif