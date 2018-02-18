#ifndef ConfigParam_H

#define ConfigParam_H

#include <iostream>
#include <cstring>
#include <string>
#include <fstream>
#include <cstdlib>

using namespace std;

class ConfigParam {
public:
    char *uart_name;
    int baudrate;
    char *vocabulary;
    char *setting;
    char *mode;
    char *gui;
    char *folder_name;
    int  fps;
    char *mission_route;
    string drone;

    int timespace;

    ConfigParam();
    ConfigParam(int argc, char **argv);
    ~ConfigParam();
    void initialization();
    void setfps(int fps_);
    void parse_commandline(int argc, char **argv);

private:
    void fps2Timespace(int fps);
};


#endif
