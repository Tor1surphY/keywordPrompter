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
    connection.send("PSG.LGD's turn to pick!\n");
    cout << connection.recv() << endl;
    while(1);
}

int main() {
    test();
    return 0;
}
