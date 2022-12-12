#include "HTTP.h"
#include "database.hpp"
#include "database.cpp"

int main()
{
    HTTP http;
    http.init();

    database<std::string, std::string> db;

    std::cout << "<!DOCTYPE HTML>" << std::endl;
    std::cout << "<html>" << std::endl;
    std::cout << "<head>" << std::endl;
    std::cout << "<meta charset=\"utf-8\">" << std::endl;
    std::cout << "<title>Данные формы</title> </head>" << std::endl;
    std::cout << "<body>" << std::endl;
    std::cout << "<p>Succesfully got ";

    std::map<std::string, std::string>* res = db.read_all();
    std::cout << "{";
    int i = 0;
    for (auto [key, val] : *res) {
        if (i > 0) {
            std::cout << ", ";
        }
        std::cout << "\"" << http.escaping(key) << "\": \"" << http.escaping(val) << "\"";
        i++;
    }
    std::cout << "}";

    std::cout << "</p>" << std::endl;
    std::cout << "</body>" << std::endl;
    std::cout << "</html>" << std::endl;

    http.send();

    return 0;
}