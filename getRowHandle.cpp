#include "HTTP.h"
#include "database.hpp"
#include "database.cpp"

int main()
{
    HTTP http;
    http.init();

    database<std::string, std::string> db;
    std::string getParameter = http.httpGet("getRow");

    std::string res = db.read_one(getParameter);

    std::cout << "<!DOCTYPE HTML>" << std::endl;
    std::cout << "<html>" << std::endl;
    std::cout << "<head>" << std::endl;
    std::cout << "<meta charset=\"utf-8\">" << std::endl;
    std::cout << "<title>Данные формы</title> </head>" << std::endl;
    std::cout << "<body>" << std::endl;
    std::cout << "<p>Succesfully got ";

    if (res != "") {
        std::cout << "{ \"" << http.escaping(getParameter) << "\": \"" << http.escaping(res) << "\"}";
    }

    std::cout << "</p>" << std::endl;
    std::cout << "</body>" << std::endl;
    std::cout << "</html>" << std::endl;

    http.send();
}