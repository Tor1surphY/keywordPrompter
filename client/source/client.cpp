#include <unistd.h>
#include <json/json.h>

#include <iostream>
#include <bitset>

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
        cout << "[input your word: ]" << endl;
        cin >> msg;
        // protocol
        {
            bitset<32> size = msg.size();
            connection.send(size.to_string() + msg);
        }
        connection.recv();
    }
}



int main() {
    test();
    return 0;
}
