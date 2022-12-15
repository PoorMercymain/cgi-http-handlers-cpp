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
    std::string filename; 	// �������� ��� �����
    std::string type;	// MIME-��� �����
    std::string tmp_name; // ��������� ��� �����
    int error; 	// ��� ������ (0, ���� ������ ���)
    int size; 	// ������ ������������ �����
} UploadedFile;

class HTTP {
public:
    //��������� ����
    //���������, ���������� http ������� GET
    std::map<std::string, std::string> getParameters;

    //���������, ���������� http ������� POST
    std::map<std::string, std::string> postParameters;

    //������ cookie, ����������� � ������� cgi ��������� � ������� 
    std::map<std::string, std::string> clientCookie;

    //������ cookie, ����������� �� �������
    std::map<std::string, std::string> serverCookie;

    

    std::map<std::string, int> INTCONFIG = { {"MAX_FILESIZE",2048} };

    std::map <std::string, UploadedFile> filesData;

    //��������� ������
    //�����������
    HTTP();

    //��������������� cout � ��������� ����� cgiOut
    void init();

    //�������� ����������, � ����� ������ cookie �������
    void send();

    //������������� ��������
    std::string escaping(std::string str);

    //�����, ������������ ������, ����������� � postParameters ��� ������ name
    std::string httpPost(std::string name);

    //�����, ������������ ������, ����������� � getParameters ��� ������ name
    std::string httpGet(std::string name);

    //�����, ������������ ������ cookie, ����������� � clientCookie ��� ������ name
    std::string getCookie(std::string name);

    //�����, ��������������� �������� (value) �������� serverCookie ��� ������ name
    std::string setCookie(std::string name, std::string value);

    //����� ��� ������������� ������ �� 16-������� ������������� � plain-text
    std::string rawURLDecode(std::string str);

    //���������� �������� ����� �� ��� ��������
    std::string getHeader(std::string name); //TODO: implement

    UploadedFile getFile(std::string name); //TODO: implement

    // ��������� ���� � ��������� ����������
    int move_uploaded_file(UploadedFile tmpFile, std::string path);

    //���������� ������ �� ����� � cout
    int httpSendFile(std::string name);

    //����������
    ~HTTP();

private:
    //��������� ����
    //������� ��� �������������
    std::map<std::string, std::string> escape = {
        {"\"","\\&quot;"}, {"<","&lt;"}, {">","&gt;"}
    };

    //��������� ����� ��� ������ �������
    std::stringstream cgiOut;

    //��������� ������
    //����� ��� ����������� ������ char (���������������� ������ ������������������ �����) � unsigned int
    unsigned int CtoI(char ch);
    //����� ��� ����������� ���� char (��������������� ����������������� ������) � unsigned int
    unsigned int CCtoI(char ch1, char ch2);
};

#endif //C___HTTP_H
