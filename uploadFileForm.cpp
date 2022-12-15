#include "HTTP.h"

int main()
{
    HTTP http;
    http.init();

    std::cout << "<!DOCTYPE HTML>" << std::endl;
    std::cout << "<html>" << std::endl;
    std::cout << "<head>" << std::endl;
    std::cout << "<meta charset=\"utf-8\">" << std::endl;
    std::cout << " <title>Данные формы</title> </head>" << std::endl;
    std::cout << "<body>" << std::endl;

    std::cout << "<div align=\"center\">" << std::endl;
    std::cout << "<form action = \"uploadFileHandler.cgi\" method = \"POST\" enctype = \"multipart/form-data\">" << std::endl;
    std::cout << "<input type = \"file\" name = \"myFile1\"><br><br>" << std::endl;
    std::cout << "<input type = \"file\" name = \"myFile2\"><br><br>" << std::endl;
    std::cout << "<input type = \"submit\" value = \"Upload\">" << std::endl;
    std::cout << "</form></div>" << std::endl;

    std::cout << "</body>" << std::endl;
    std::cout << "</html>" << std::endl;

    http.send();

    return 0;
}