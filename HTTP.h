//
// Created by slymercymain on 09.11.2022.
//

#ifndef C___HTTP_H
#define C___HTTP_H

#include <string>
#include <map>
#include <sstream>
#include <iostream>

typedef struct {
    std::string filename; 	// реальное имя файла
    std::string type;	// MIME-тип файла
    std::string tmp_name; // временное имя файла
    int error; 	// код ошибки (0, если ошибки нет)
    int size; 	// размер загружаемого файла
} UploadedFile;

class HTTP {
public:
    //публичные поля
    //параметры, полученные http методом GET
    std::map<std::string, std::string> getParameters;

    //параметры, полученные http методом POST
    std::map<std::string, std::string> postParameters;

    //данные cookie, сохраненные с помощью cgi программы у клиента 
    std::map<std::string, std::string> clientCookie;

    //данные cookie, сохраненные на сервере
    std::map<std::string, std::string> serverCookie;

    

    std::map<std::string, int> INTCONFIG = { {"MAX_FILESIZE",2048} };

    std::map <std::string, UploadedFile> filesData;

    //публичные методы
    //конструктор
    HTTP();

    //перенаправление cout в строковой поток cgiOut
    void init();

    //отправка заголовков, а также данных cookie клиенту
    void send();

    //экранирование символов
    std::string escaping(std::string str);

    //метод, возвращающий данные, находящиеся в postParameters под ключом name
    std::string httpPost(std::string name);

    //метод, возвращающий данные, находящиеся в getParameters под ключом name
    std::string httpGet(std::string name);

    //метод, возвращающий данные cookie, находящиеся в clientCookie под ключом name
    std::string getCookie(std::string name);

    //метод, устанавливающий значение (value) элемента serverCookie под ключом name
    std::string setCookie(std::string name, std::string value);

    //метод для декодирования строки из 16-ричного представления в plain-text
    std::string rawURLDecode(std::string str);

    //возвращает свойства файла по его названию
    std::string getHeader(std::string name); //TODO: implement

    UploadedFile getFile(std::string name); //TODO: implement

    // загружает файл в указанную директорию
    int move_uploaded_file(UploadedFile tmpFile, std::string path);

    //отправляет данные из файла в cout
    int httpSendFile(std::string name);

    //деструктор
    ~HTTP();

private:
    //приватные поля
    //символы для экранирования
    std::map<std::string, std::string> escape = {
        {"\"","\\&quot;"}, {"<","&lt;"}, {">","&gt;"}
    };

    //строковой поток для вывода клиенту
    std::stringstream cgiOut;

    //приватные методы
    //Метод для конвертации одного char (соответствующего одному шестнадцатеричному числу) в unsigned int
    unsigned int CtoI(char ch);
    //Метод для конвертации двух char (соответствующих шестнадцатеричным числам) в unsigned int
    unsigned int CCtoI(char ch1, char ch2);
};

#endif //C___HTTP_H
