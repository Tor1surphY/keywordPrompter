#include <unistd.h>
#include <json/json.h>

#include <iostream>
#include <bitset>

#include "../include/connecter.hpp"
#include "../include/tcpConnection.hpp"
#include "../include/jsonUnpack.hpp"

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
        // protocol pack
        {
            Json::Value val;
            val["word"] = msg;
            bitset<32> size = msg.size();
            connection.send(size.to_string() + msg);
        }

        cout << "[promoted words:  ]" << endl;

        // unpack
        {
            string msg = connection.recv();
            // cout << msg;
            JsonUnpack unpacker(msg);
            unpacker.unpack();
        }

        cout << endl;
    }
}

int main() {
    test();
    return 0;
}
