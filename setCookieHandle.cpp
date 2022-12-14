#include "HTTP.h"
#include "database.hpp"
#include "database.cpp"

int main() {
    HTTP http;
    http.init();
    database<std::string, std::string> db;

    std::cout << "<!DOCTYPE HTML>" << std::endl;
    std::cout << "<html>" << std::endl;
    std::cout << "<head>" << std::endl;
    std::cout << "<meta charset=\"utf-8\">" << std::endl;
    std::cout << "<title>Данные формы</title> </head>" << std::endl;
    std::cout << "<body>" << std::endl;
    std::cout << "<p>Succesfully sent ";

    std::cout << http.httpGet("setcookie") << ": "
        << http.setCookie(http.httpGet("setcookie"), http.httpGet("value")) << "<br></p>";

    std::cout << "</body>" << std::endl;
    std::cout << "</html>" << std::endl;

    http.setCookie("lastKey", http.httpGet("setcookie"));

    int res = db.write(http.httpGet("setcookie"), http.httpGet("value"));

    if (res != 0) {
        std::cout << "{\"status\": [500, \"Server Error\"]}";
    }

    http.send();

    return 0;
}