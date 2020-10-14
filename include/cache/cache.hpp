#ifndef __TY_CACHE_H__
#define __TY_CACHE_H__

#include <string>
#include <unordered_map>

using std::string;
using std::unordered_map;

namespace ty
{

struct Node;

class Cache {
public:
    Cache(int);

    string get(string);
    void put(string, string);

private:
    void addToHead(Node*);
    void removeNode(Node*);
    void moveToHead(Node*);
    void removeTail();

private:
    unordered_map<string, Node*> _storage;
    Node* _head;
    Node* _tail;
    int _capacity;
    int _size;
};
} // end of namespace ty
#endif