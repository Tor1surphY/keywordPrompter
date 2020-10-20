# Keyword Prompter

The *Keyword Prompter* is a server program 
based on a multi-thread TCP network service model with caching mechanism
that can prompte similar words relate to the requirement from client.

*this README is more like a development note or a lenaring note*

---

### Info

- Ubuntu  version 18.04.2
- Linux   version 5.4.0-51-generic
- VS Code version 1.50
- gcc     version 7.5.0

---

### server

The server system divided into three parts:

#### 1. multi-thread TCP model

The multi-thread TCP model has three parts.

1. TCP connection model

This model needs to listen and accept a new connection requirement and 
build a new TCP connection. So that I can do the recive and send operation in this connection object. 
Of courese, accroding to the BO design principles, the recive and send operation will implement in 
another class which is SocketIO.

![avatar](/picture/tcpconnection.png)

2. eventloop model



3. threadpool model


#### 2. cache model

The cache model is set in server system. 
The final expected version of this model is a prompter in the application scenario of search engines, 
so I need to know what the current hot keyword on Internet is, 
that's why I set the cache model in server instead of set in client.

I set cache model for every working thread, to improve search efficiency, the query operation should run in cache model first, if not found, then find in RAM. 

Once the thread got a new answer, it will be send to client and update in cache model at the same time. 
For updating cache, I used LRU algorithm. 

To unify and update all the cache data, I set a timer thread in threadpool. It will unify and update 
cache data regularly. To avoid thread confict, I set a cold cache in cache manager class. 
When timer is weaked up, the manager will copy a set of data for ervery thread cache first, then run the 
unify process, and copy back for every thread caceh. 

![avatar](/picture/cache.png)

```
(not implement yet)
even I used the hot-cold cache mechanism,
it still have the thread conflict problem.
So the expected solution is when the cache manager is running,
add a locker into the thread which is being cpoied,
so that this thread will not work when it is processed.
```

#### 3. query model

This model based on the test program in C++ Primer.

First I process the corproa to get a dictionary using a `map<word, frequence>` and 
a index for dictionary using a `map<character, vector<word>>` that can improve search efficiency. 

Dictionary and index will store in a singleton class, it is divied with the query class.

On query model, the dictionary and index will store in RAM, when system got a word input, 
it will find words that started with every charater of input word in the index first, 
then the model will count every found word's shortest edit distance with input word. 
Finally, return 5 shortest edit distance words.

![avatar](/picture/query.png)

```
(not implement yet)
the corpora will be Google search dataset,
using tinyxml2 to decode xml files
so that I can get a map with main entry
and a vector which contains its all child entry								
								
```

### client

The client needs to bulid a TCP connection with server, 
pack infomation from user and send to server, 
then unpack and dispalay data that send back from server.

![avatar](/picture/client.png)

