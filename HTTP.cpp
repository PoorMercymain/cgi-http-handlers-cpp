//
// Created by slymercymain on 13.11.2022.
//

#include "HTTP.h"
#include <iostream>

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

HTTP::~HTTP()
{
    return;
}

HTTP::HTTP()
{
    std::stringstream getStringStream(getenv("QUERY_STRING"));
    std::string key = std::string{};
    std::string val = std::string{};

    // parse GET params
    while (std::getline(getStringStream, key, '=')) {
        std::getline(getStringStream, val, '&');
        this->getParameters[key] = val;
    }
    // parse cookie
    if (getenv("HTTP_COOKIE") != nullptr) {
        std::stringstream cookieStringStream(getenv("HTTP_COOKIE"));
        while (std::getline(cookieStringStream, key, '=')) {
            std::getline(cookieStringStream, val, ';');
            key = ltrim(&key);
            key = escaping(key);
            val = escaping(val);
            this->clientCookie[key] = val;
        }
    }
   
    if (val == "application/x-www-form-urlencoded") {
        // parse POST params
        std::string postData;
        std::getline(std::cin, postData, static_cast<char>(0));
        std::stringstream postStringStream(postData);
        while (std::getline(postStringStream, key, '=')) {
            std::getline(postStringStream, val, '&');
            this->postParameters[key] = val;
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
