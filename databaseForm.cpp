#include "HTTP.h"

int main()
{
    HTTP http;
    http.init();

    std::string previousKey = std::string{};
    std::string previousValue = std::string{};

    previousKey = http.getCookie("lastKey");
    previousValue = http.getCookie(previousKey);

    std::cout << "<!DOCTYPE HTML>" << std::endl;
    std::cout << "<html>" << std::endl;
    std::cout << "<head>" << std::endl;
    std::cout << "<meta charset=\"utf-8\">" << std::endl;
    std::cout << " <title>Данные формы</title> </head>" << std::endl;
    std::cout << "<body>" << std::endl;
    std::cout << "<div align=\"center\"><form action=\"getRowHandle.cgi\" method=\"get\" align=\"center\">" << std::endl;
    std::cout << "<p>" << std::endl;
    std::cout << "  <input name=\"getRow\" placeholder=\"Get row\">" << std::endl;
    std::cout << "</p>" << std::endl;
    std::cout << "<p><input type=\"submit\"></p>" << std::endl;
    std::cout << "</form></div>" << std::endl;

    std::cout << "<div align=\"center\"><form action=\"listAllRowsHandle.cgi\" method=\"get\" align=\"center\">" << std::endl;
    std::cout << "<p>" << std::endl;
    std::cout << "</p>" << std::endl;
    std::cout << "<p><input type=\"submit\" value=\"Show all\"></p>" << std::endl;
    std::cout << "</form></div>" << std::endl;

    std::cout << "<div align=\"center\"><form action=\"dropRowHandle.cgi\" method=\"get\" align=\"center\">" << std::endl;
    std::cout << "<p>" << std::endl;
    std::cout << "  <input name=\"drop\" placeholder=\"Drop row\">" << std::endl;
    std::cout << "</p>" << std::endl;
    std::cout << "<p><input type=\"submit\"></p>" << std::endl;
    std::cout << "</form></div>" << std::endl;

    std::cout << "<div align=\"center\"><form action=\"addRowHandle.cgi\" method=\"get\" align=\"center\">" << std::endl;
    std::cout << "<p>" << std::endl;
    std::cout << "  <input name=\"key\" placeholder=\"Key of element\" value=\"" << previousKey << "\"><input name=\"value\" placeholder=\"Value of element\" value=\"" << previousValue << "\">" << std::endl;
    std::cout << "</p>" << std::endl;
    std::cout << "<p><input type=\"submit\"></p>" << std::endl;
    std::cout << "</form></div>" << std::endl;

    std::cout << "</body>" << std::endl;
    std::cout << "</html>" << std::endl;

    http.send();

    return 0;
}