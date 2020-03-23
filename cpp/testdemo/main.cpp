/*
 * @Author: gongluck 
 * @Date: 2020-03-23 15:57:21 
 * @Last Modified by: gongluck
 * @Last Modified time: 2020-03-23 15:58:01
 */

#include <iostream>

#include "../config/config.h"
#include "../code conversion/convert.h"

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

    std::string ansi = "ÄãºÃ£¬ÊÀ½ç£¡";
    std::wstring uni;
    std::string utf8;
    ret = gconvert::ansi2uni(ansi, uni);
    ret = gconvert::ansi2utf8(ansi, utf8);
    ret = gconvert::uni2ansi(uni, ansi);
    ret = gconvert::uni2utf8(uni, utf8);
    ret = gconvert::utf82ansi(utf8, ansi);
    ret = gconvert::utf82uni(utf8, uni);
    return 0;
}