#include <unistd.h>

#include <iostream>

#include "../include/connecter.hpp"
#include "../include/tcpConnection.hpp"

using namespace std;
using namespace ty;

void test() {
    Connecter connecter("192.168.160.128", 7777);
    connecter.connect();
    TcpConnection connection(connecter.fd());
    cout << connection.info();
    string msg;
    while(1) {
        cout << "input: \"do quit\" to quit" << endl;
        getline(cin, msg);
        if(msg == "do quit") break;
        msg += '\n';
        connection.send(msg);
        cout << "recived from server: ";
        cout << connection.recv() << endl;
    }
}

int main() {
    test();
    return 0;
}
