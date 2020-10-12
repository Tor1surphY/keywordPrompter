#include <unistd.h>
#include <iostream>

#include "../../include/server/echoServer.hpp"

using namespace std;
using namespace ty;

void testServer() {
    EchoServer server(4, 10, "192.168.160.128", 7777, "/home/tor1/keywordPrompterForEncyclopediaSearch/config/textQuery");
    server.start();
}

int main() {
    testServer();
    return 0;
}
