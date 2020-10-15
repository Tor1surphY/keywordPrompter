#include "../../include/cache/cache.hpp"

using std::pair;

namespace ty
{

Cache::Cache(int capacity) 
: _capacity(capacity)
, _size(0) {
    Node* tmp = new Node;
    _head = _tail = tmp;
}

string Cache::get(string key) {
    unordered_map<string, Node*>::iterator it = _storage.find(key);
    if(it == _storage.end()) {
        return "not found";
    }
    moveToHead(it->second);
    return it->second->value;
}

void Cache::put(string key, string value) {
    unordered_map<string, Node*>::iterator it = _storage.find(key);
    if (it != _storage.end()) {
        it->second->key = key;
        it->second->value = value;
        moveToHead(it->second);
    }
    else {
        Node *tmp = new Node(key, value);
        if (_size < _capacity) {
            addToHead(tmp);
        }
        else {
            removeTail();
            addToHead(tmp);
        }
        _storage.insert(pair<string, Node*>(key, tmp));
        ++_size;
    }
}

void Cache::addToHead(Node* tmp) {
    tmp->back = _head;
    _head->front = tmp;
    _head = tmp;
}

void Cache::removeNode(Node* tmp) {
    if(tmp == _head) {
        _head = _head->back;
        _head->front = nullptr;
        tmp->back  = nullptr;
        tmp->front = nullptr;
    }
    else {
        tmp->front->back = tmp->back;
        tmp->back->front = tmp->front;
    }
    _storage.erase(tmp->key);
    --_size;
}

void Cache::moveToHead(Node* tmp) {
    removeNode(tmp);
    addToHead(tmp);
    ++_size;
}

void Cache::removeTail() { removeNode(_tail->front); }
} // end of namespace ty