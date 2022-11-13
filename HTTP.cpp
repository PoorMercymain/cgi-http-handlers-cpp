//
// Created by slymercymain on 13.11.2022.
//

#include "HTTP.h"
#include <iostream>

void HTTP::httpPost() {
    std::string postStr;
    std::cin >> postStr;
    std::cout << "Content-Type: text/html; charset=utf-8" << std::endl << std::endl;
    std::cout << "<!DOCTYPE HTML>" << std::endl;
    std::cout << "<html>" << std::endl;
    std::cout << "<head>" << std::endl;
    std::cout << "<meta charset=\"utf-8\">" << std::endl;
    std::cout << "<title>Данные формы</title> </head>" << std::endl;
    std::cout << "<body>" << std::endl;
    std::cout << "<p>You have sent " + postStr + "</p>" << std::endl;
    std::cout << "</body>" << std::endl;
    std::cout << "</html>" << std::endl;
}

void HTTP::httpGet() {
    std::string getStr = getenv("QUERY_STRING");
    std::cout << "Content-Type: text/html; charset=utf-8" << std::endl << std::endl;
    std::cout << "<!DOCTYPE HTML>" << std::endl;
    std::cout << "<html>" << std::endl;
    std::cout << "<head>" << std::endl;
    std::cout << "<meta charset=\"utf-8\">" << std::endl;
    std::cout << "<title>Данные формы</title> </head>" << std::endl;
    std::cout << "<body>" << std::endl;
    std::cout << "<p>You have sent " + getStr + "</p>" << std::endl;
    std::cout << "</body>" << std::endl;
    std::cout << "</html>" << std::endl;
}
