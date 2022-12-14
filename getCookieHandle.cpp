#include "HTTP.h"

int main() {
    HTTP http;
    http.init();

    std::cout << "<!DOCTYPE HTML>" << std::endl;
    std::cout << "<html>" << std::endl;
    std::cout << "<head>" << std::endl;
    std::cout << "<meta charset=\"utf-8\">" << std::endl;
    std::cout << "<title>Данные формы</title> </head>" << std::endl;
    std::cout << "<body>" << std::endl;
    std::cout << "<p>Succesfully got ";

    std::cout << http.rawURLDecode(http.httpGet("getcookie")) << ": "
        << http.getCookie(http.rawURLDecode(http.httpGet("getcookie"))) << "<br></p>";

    std::cout << "</body>" << std::endl;
    std::cout << "</html>" << std::endl;

    http.send();
    return 0;
}