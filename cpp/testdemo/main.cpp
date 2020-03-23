#include <iostream>

#include "../config/config.h"

#define CHECKRET(ret)\
if(ret != 0)\
{\
    std::cin.get();\
    return ret;\
}

int main()
{
    gconf::config conf;
    auto ret = conf.open("./config.ini");
    CHECKRET(ret);
    int file = 0;
    ret = conf.read<int>("log", "file", file);
    CHECKRET(ret);
    std::vector<std::pair<std::string, std::string>>kvs;
    ret = conf.readall("log", kvs);
    CHECKRET(ret);
    return 0;
}