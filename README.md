# cgi-http-handlers-cpp
<p>Компилируем так: g++ form.cpp -o form.cgi</p>
<p>g++ GEThandle.cpp HTTP.cpp -o GEThandle.cgi</p>
<p>g++ POSThandle.cpp HTTP.cpp -o POSThandle.cgi</p>
<p>После этого получаем от form.cgi html-страницу, использующую cgi-обработчики GEThandle.cgi и POSThandle.cgi</p>
