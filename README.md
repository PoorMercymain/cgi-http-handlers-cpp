# cgi-http-handlers-cpp
Компилируем так: g++ form.cpp -o form.cgi
g++ GEThandle.cpp HTTP.cpp -o GEThandle.cgi
g++ POSThandle.cpp HTTP.cpp -o POSThandle.cgi
После этого получаем от form.cgi html-страницу, использующую cgi-обработчики GEThandle.cgi и POSThandle.cgi
