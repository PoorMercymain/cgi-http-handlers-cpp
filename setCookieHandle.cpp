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

    std::cout << http.rawURLDecode(http.httpGet("setcookie")) << ": "
        << http.setCookie(http.rawURLDecode(http.httpGet("setcookie")), http.rawURLDecode(http.httpGet("value"))) << "<br></p>";

    std::cout << "</body>" << std::endl;
    std::cout << "</html>" << std::endl;

    http.setCookie("lastKey", http.rawURLDecode(http.httpGet("setcookie")));

    int res = db.write(http.rawURLDecode(http.httpGet("setcookie")), http.rawURLDecode(http.httpGet("value")));

    if (res != 0) {
        std::cout << "{\"status\": [500, \"Server Error\"]}";
    }

    http.send();

    return 0;
}