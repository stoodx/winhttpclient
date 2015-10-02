set OPENSSL_CONF=D:\Work\winhttpclient\trunk\certs\server\openssl.cfg
del *.pem
openssl genrsa -out privateKey.pem 1024
openssl req -new -key privateKey.pem -out csr.pem
openssl x509 -req -in csr.pem -signkey privateKey.pem -out server.pem
rem openssl req -newkey rsa:1024 -nodes -keyout server.key -out server.crt -x509 -days 3650 -subj "/C=11/ST=22/L=33/O=44/OU=55/CN=example.com/emailAddress="root@example.com
pause