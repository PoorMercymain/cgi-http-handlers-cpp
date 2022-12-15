#include "HTTP.h"
#include "HTTP.cpp"


int main() {
    HTTP http;
    http.init();

    std::cout << "<!DOCTYPE HTML>" << std::endl;
    std::cout << "<html>" << std::endl;
    std::cout << "<head>" << std::endl;
    std::cout << "<meta charset=\"utf-8\">" << std::endl;
    std::cout << "<title>Данные формы</title> </head>" << std::endl;
    std::cout << "<body>" << std::endl << "<p>";

    for (auto i = http.filesData.begin(); i != http.filesData.end(); i++) {
        auto key = (*i).first;
        auto val = (*i).second;

        if (val.error == -1) {
            std::cout << " filename:" << val.filename << " size:" << (val.size) << " is bigger then MAX FILE SIZE: " << http.INTCONFIG["MAX_FILESIZE"] << " bytes</br>";
            unlink(val.tmp_name.c_str());
            continue;
        }
        else {
            std::cout << "Size of file with name " << val.filename << " is ok" << std::endl;
        }
        int res = http.move_uploaded_file(val, "/var/www/uploads/" + val.filename);

        if (res != 0) {
            std::cout << strerror(errno) << " ";
            std::cout << res << " filename:" << val.filename << " size:" << (val.size) << "</br>";
            unlink(val.tmp_name.c_str());
        }
        else {
            std::cout << "File " << val.filename << " moved to uploads directory successfully" << std::endl;
        }
    }

    std::cout << "</p>";
    std::cout << "</body>" << std::endl;
    std::cout << "</html>" << std::endl;

    http.send();
    
    return 0;
}