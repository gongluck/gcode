/*
 * @Author: gongluck
 * @Date: 2020-03-23 15:57:21
 * @Last Modified by: gongluck
 * @Last Modified time: 2020-03-23 15:58:01
 */

#include <iostream>

#include "../config/config.h"
#include "../code conversion/convert.h"
#include "../process/process.h"
#include "../crypto/padding.h"
#include "../crypto/base64.h"

#define CHECKRET(ret)\
if(ret != 0)\
{\
    std::cin.get();\
    return ret;\
}

int main()
{
    /*gconf::config conf;
    auto ret = conf.open("./config.ini");
    CHECKRET(ret);
    int file = 0;
    ret = conf.read<int>("log", "file", file);
    CHECKRET(ret);
    std::vector<std::pair<std::string, std::string>>kvs;
    ret = conf.readall("log", kvs);
    CHECKRET(ret);*/

    /*std::string ansi = "ÄãºÃ£¬ÊÀ½ç£¡";
    std::wstring uni;
    std::string utf8;
    ret = gconvert::ansi2uni(ansi, uni);
    ret = gconvert::ansi2utf8(ansi, utf8);
    ret = gconvert::uni2ansi(uni, ansi);
    ret = gconvert::uni2utf8(uni, utf8);
    ret = gconvert::utf82ansi(utf8, ansi);
    ret = gconvert::utf82uni(utf8, uni);*/

    /*std::vector<gprocess::ProcessInfo> infos;
    ret = gprocess::gethandle("Taskmgr.exe", infos);

    gprocess::WindowInfo info;
    info.processid = infos[0].processid;
    ret = gprocess::getallwindows(&info);*/

    std::string plain = "hello,gcrypto.";
    plain = gcrypto::PKCS5Padding(plain, 8);
    auto cipher = gcrypto::Base64Encode(plain);
    plain = gcrypto::Base64Decode(cipher);
    plain = gcrypto::UNPKCS5Padding(plain, 8);

    return 0;
}