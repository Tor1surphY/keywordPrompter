#include <unistd.h>
#include <json/json.h>

#include <iostream>

#include "../include/connecter.hpp"
#include "../include/tcpConnection.hpp"
#include "../include/jsonPackup.hpp"

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
        JsonPackup data_bag(msg);
        string to_send = data_bag.packup();
        int lenth = to_send.size();
        connection.send(to_string(lenth) + to_send);
        connection.recv();
    }
}



int main() {
    test();
    return 0;
}
