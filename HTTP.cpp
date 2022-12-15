//
// Created by slymercymain on 13.11.2022.
//
#ifndef C___HTTP_CPP
#define C___HTTP_CPP

#include "HTTP.h"
#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <iterator>
#include <sstream>
#include <fstream>
#include <map>
#include <unistd.h>
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cerrno>
#include <cstdlib>


std::string& ltrim(std::string* str)
{
    if (*((*str).begin()) == ' ') {
        (*str).erase((*str).begin());
    }
    if ((*((*str).end() - 1) == '\n') or (*((*str).end() - 1) == '\r')) {
        (*str).erase((*str).end() - 1);
    }
    return *str;
}

std::string HTTP::httpPost(std::string name) {
    return this->postParameters[name];
}

std::string HTTP::httpGet(std::string name) {
    return this->getParameters[name];
}

std::string HTTP::getCookie(std::string name)
{
    return this->clientCookie[name];
}

std::string HTTP::setCookie(std::string name, std::string value)
{
    this->serverCookie[name] = value;
    return value;
}

std::string HTTP::rawURLDecode(std::string str)
{
    std::string resultString = "";

    for (int i = 0; i < str.length(); i++)
    {

        if (str[i] != '%')
        {
            resultString.append(1, str[i]);
        }
        if (str[i] == '%')
        {
            i++; //skip '%'

            if (CCtoI(str[i], str[i + 1]) < 127)
            {
                resultString.append(1, char(CCtoI(str[i], str[i + 1])));
                i++; //skip one hex (other hex will be skiped by i++ in for)
                continue;
            }
            
            if ((CCtoI(str[i], str[i + 1]) & 0b11100000) == 0b11000000)
            {

                resultString.append(1, char(CCtoI(str[i], str[i + 1])));
                i = i + 3; //skip (XX%): 2 hex numbers and '%' 
                resultString.append(1, char(CCtoI(str[i], str[i + 1])));
                i++; //skip one hex (other hex will be skiped by i++ in for)
                continue;
            }
        }
    }
    return resultString;
}

std::string HTTP::getHeader(std::string name)
{
    return std::string();
}

UploadedFile HTTP::getFile(std::string name)
{
    return UploadedFile();
}

int HTTP::move_uploaded_file(UploadedFile tmpFile, std::string path)
{
    std::ifstream  src(tmpFile.tmp_name, std::ios::binary);
    std::ofstream  dst(path, std::ios::binary);
    if (!src.is_open()) {
        return -1;
    }
    if (!dst.is_open()) {
        return -2;
    }
    dst << src.rdbuf();
    unlink(tmpFile.tmp_name.c_str());
    return 0;
}

int HTTP::httpSendFile(std::string name)
{
    std::ifstream ifile;
    ifile.open(name, std::ios::in);
    if (!ifile) {
        return -1;
    }
    std::string str;
    while (std::getline(ifile, str, '\n')) {
        std::cout << str << std::endl;
    }
    return 0;
}

HTTP::~HTTP()
{
    return;
}

unsigned int HTTP::CtoI(char ch)
{
    if (ch >= 'A') {
        return int(ch - 'A' + 10);
    }

    return int(ch - '0');
}

unsigned int HTTP::CCtoI(char ch1, char ch2)
{
    return ((CtoI(ch1) << 4) + CtoI(ch2));
}

HTTP::HTTP() {
    std::stringstream getStringStream(getenv("QUERY_STRING"));
    std::string key = std::string{};
    std::string val = std::string{};

    // parse GET params
    while (std::getline(getStringStream, key, '=')) {
        std::getline(getStringStream, val, '&');
        this->getParameters[rawURLDecode(key)] = rawURLDecode(val);
    }
    // parse cookie
    if (getenv("HTTP_COOKIE") != nullptr) {
        std::stringstream cookieStringStream(getenv("HTTP_COOKIE"));
        while (std::getline(cookieStringStream, key, '=')) {
            std::getline(cookieStringStream, val, ';');
            key = rawURLDecode(key);
            key = ltrim(&key);
            key = escaping(key);
            val = rawURLDecode(val);
            val = escaping(val);
            this->clientCookie[key] = val;
        }
    }

    std::string contentType = std::string{};

    if (getenv("CONTENT_TYPE") != nullptr) {
        UploadedFile upf;
        std::string boundary;

        std::stringstream strstm(getenv("CONTENT_TYPE"));
        std::getline(strstm, contentType, ';');

        if (contentType == "multipart/form-data") {
            std::getline(strstm, val, '='); //skip " boundary="
            std::getline(strstm, boundary); // get boundary
            int flag = 100;
            int tmpfd = -1;
            std::string name;
            std::string filename;
            while (flag)
            {
                std::string ContentType[2];
                std::getline(std::cin, val);
                long long int fs = 0;

                if (ltrim(&val) == ("--" + boundary)) {
                    if (tmpfd != -1) {
                        close(tmpfd);
                    }

                    std::getline(std::cin, val, '\"'); // SKIP Content-Disposition: form-data; name="
                    std::getline(std::cin, name, '\"'); // get name

                    std::getline(std::cin, val, '\"'); // SKIP "; filename="
                    std::getline(std::cin, filename, '\"'); // get filename

                    std::getline(std::cin, val, '\n'); // skip '"\n'
                    std::getline(std::cin, val, ' '); // skip "Content-Type: "
                    std::getline(std::cin, ContentType[0], '/'); // get content type before '/'

                    std::getline(std::cin, ContentType[1], '\n'); // get content type
                    filesData[name].type = ContentType[0];
                    std::getline(std::cin, val, '\n'); // skip empty line

                    filesData[name].filename = filename;
                    filesData[name].size = 0;
                    filesData[name].error = 0;
                    //Create temp file
                    char tmpfilename[] = "/tmp/HTTPtemp_XXXXXX";
                    tmpfd = mkstemp(tmpfilename);


                    filesData[name].tmp_name = tmpfilename;

                }
                else {
                    if (ltrim(&val) == ("--" + boundary + "--")) { // Exit if end 
                        break;
                    }
                    if (tmpfd != -1) {
                        write(tmpfd, (val + '\n').c_str(), val.size() + 1);
                        filesData[name].size += val.size() + 1;
                        if (filesData[name].size > INTCONFIG["MAX_FILESIZE"]) {
                            filesData[name].error = -1;
                            break;
                        }
                    }
                }
            }
        }
        else if (contentType == "application/x-www-form-urlencoded") {
            // parse POST params
            std::string postData;
            std::getline(std::cin, postData, static_cast<char>(0));
            std::stringstream postStringStream(postData);
            while (std::getline(postStringStream, key, '=')) {
                std::getline(postStringStream, val, '&');
                this->postParameters[rawURLDecode(key)] = rawURLDecode(val);
            }
        }
        }
        return;
    }

void HTTP::init()
{
    // redirecting cout stream to string stream
    std::streambuf* x = std::cout.rdbuf(this->cgiOut.rdbuf());
}

void HTTP::send()
{
    // set headers
    fprintf(stdout, "Content-Type: text/html; charset=utf-8\n");
    // set cookie
    
    for (const auto& [key, value] : this->serverCookie) {
        fprintf(stdout, "Set-Cookie: ");
        fprintf(stdout, "%s=%s; \n", key.c_str(), value.c_str());
    }
    fprintf(stdout, "\n\n");
    // output recorded cout
    fprintf(stdout, "%s", cgiOut.str().c_str());
}

std::string ReplaceAll(std::string str, const std::string& from, const std::string& to) {
    size_t start_pos = 0;
    while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length();
    }
    return str;
}

std::string HTTP::escaping(std::string str)
{
    for (auto [key, val] : this->escape) {
        str = ReplaceAll(str, key, val);
    }
    return str;
}

#endif