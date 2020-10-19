# Keyword Prompter

The *Keyword Prompter* is a server program 
based on a multi-thread TCP network service model with caching mechanism
that can prompte similar words relate to the requirement from client.

---

### Info

- Ubuntu  version 18.04.2
- Linux   version 5.4.0-51-generic
- VS Code version 1.50
- gcc     version 7.5.0

---

### server

the server system divided into three parts:

1. multi-thread TCP model
2. cache model
3. query model

### client

The client needs to bulid a TCP connection with server, 
pack infomation from user and send to server, 
then unpack and dispalay data that send back from server.

![avatar](/picture/client.png)

