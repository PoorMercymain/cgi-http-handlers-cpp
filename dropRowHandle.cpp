#include "HTTP.h"
#include "database.hpp"
#include "database.cpp"

int main()
{
    HTTP http;
    http.init();

    database<std::string, std::string> db;

    std::string getParameter = http.httpGet("drop");

    std::cout << "<!DOCTYPE HTML>" << std::endl;
    std::cout << "<html>" << std::endl;
    std::cout << "<head>" << std::endl;
    std::cout << "<meta charset=\"utf-8\">" << std::endl;
    std::cout << "<title>Данные формы</title> </head>" << std::endl;
    std::cout << "<body>" << std::endl;
    std::cout << "<p>Succesfully dropped ";

    int res = db.erase(getParameter);

    if (res == 0) {
        std::cout << getParameter;
    }
    else {
        std::cout << "{\"status\": [500, \"Server Error\"]}";
    }

    std::cout << "</p>" << std::endl;
    std::cout << "</body>" << std::endl;
    std::cout << "</html>" << std::endl;

    http.send();

    return 0;
}