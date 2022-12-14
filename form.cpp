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
    std::cout << "<div align=\"center\"><form action=\"POSThandle.cgi\" method=\"post\" align=\"center\">" << std::endl;
    std::cout << "<p>" << std::endl;
    std::cout << "  <input name=\"postData\" placeholder=\"POST data\">" << std::endl;
    std::cout << "</p>" << std::endl;
    std::cout << "<p><input type=\"submit\"></p>" << std::endl;
    std::cout << "</form></div>" << std::endl;
    std::cout << "<div align=\"center\"><form action=\"GEThandle.cgi\" method=\"get\">" << std::endl;
    std::cout << "<p>" << std::endl;
    std::cout << "  <input name=\"getData\" placeholder=\"GET data\">" << std::endl;
    std::cout << " </p>" << std::endl;
    std::cout << " <p><input type=\"submit\"></p>" << std::endl;
    std::cout << " </form></div>" << std::endl;

    std::cout << "<div align=\"center\"><form action=\"setCookieHandle.cgi\" method=\"get\">" << std::endl;
    std::cout << "<p>" << std::endl;
    std::cout << "  <input name=\"setcookie\" placeholder=\"Cookie name\" value=\"" << previousKey <<"\"><input name=\"value\" placeholder=\"Cookie data\" value=\"" << previousValue <<"\">" << std::endl;
    std::cout << " </p>" << std::endl;
    std::cout << " <p><input type=\"submit\"></p>" << std::endl;
    std::cout << " </form></div>" << std::endl;

    std::cout << "<div align=\"center\"><form action=\"getCookieHandle.cgi\" method=\"get\">" << std::endl;
    std::cout << "<p>" << std::endl;
    std::cout << "  <input name=\"getcookie\" placeholder=\"Cookie to get\">" << std::endl;
    std::cout << " </p>" << std::endl;
    std::cout << " <p><input type=\"submit\"></p>" << std::endl;
    std::cout << " </form></div>" << std::endl;

    std::cout << "</body>" << std::endl;
    std::cout << "</html>" << std::endl;

    http.send();

    return 0;
}