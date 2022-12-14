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

HTTP::HTTP()
{
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

    std::stringstream strstm(getenv("CONTENT_TYPE"));
    std::getline(strstm, contentType, ';');

    if (contentType == "application/x-www-form-urlencoded") {
        // parse POST params
        std::string postData;
        std::getline(std::cin, postData, static_cast<char>(0));
        std::stringstream postStringStream(postData);
        while (std::getline(postStringStream, key, '=')) {
            std::getline(postStringStream, val, '&');
            this->postParameters[rawURLDecode(key)] = rawURLDecode(val);
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
