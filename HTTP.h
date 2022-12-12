//
// Created by slymercymain on 09.11.2022.
//

#ifndef C___HTTP_H
#define C___HTTP_H

#include <string>
#include <map>
#include <sstream>
#include <iostream>

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
};

#endif //C___HTTP_H
