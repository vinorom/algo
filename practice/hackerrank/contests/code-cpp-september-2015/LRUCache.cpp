/**
 * https://www.hackerrank.com/contests/code-cpp-september-2015/challenges/abstract-classes-polymorphism
 */

#include <iostream>
#include <map>

using namespace std;

template <typename Key, typename Value>
struct Node
{
    Key   key;
    Value value;
    Node* prev;
    Node* next;

    Node(Key k, Value v, Node* p = 0, Node* n = 0): key(k), value(v), prev(p), next(n) {}
};

template <typename Key, typename Value>
class Cache
{
public:
    virtual ~Cache() {}
    virtual Value get(Key key) const = 0;
    virtual void set(Key key, Value value) = 0;
};

template <typename Key, typename Value>
class LRUCache
{
public:
    LRUCache(int cap): capacity(cap), head(0), tail(0) {}

    virtual ~LRUCache() {}

    virtual Value get(Key key) const
    {
        typename cache_map::iterator it = cache.find(key);
        if (it == cache.end()) return Value();
        return it->second->value;
    }

    virtual void set(Key key, Value value)
    {
        typename cache_map::iterator it = cache.find(key);
        if (it == cache.end())
        {
            add_entry(key, value);
            while (cache.size() > capacity) remove_entry(tail);
        }
        else
        {
            remove_entry(it->second);
            add_entry(key, value);
        }
    }

private:
    typedef Node<Key, Value> node;

    void remove_entry(node* n)
    {
        node* prev = n->prev;
        node* next = n->next;
        if (prev) prev->next = next;
        if (next) next->prev = prev;
        if (head == n) head = head->next;
        if (tail == n) tail = tail->prev;
        cache.erase(n->key);
        delete n;
    }

    void add_entry(Key key, Value value)
    {
        node* n = new node(key, value, 0, head);
        if (head) head->prev = n;
        head = n;
        if (!tail) tail = head;
        cache[key] = head;
    }

private:
    typedef map<Key, node*> cache_map;

    const int capacity;
    mutable cache_map cache;
    mutable node* head;
    mutable node* tail;
};

int main()
{
    int n, capacity;
    cin >> n >> capacity;

    LRUCache<int, int> cache(capacity);
    while (n--)
    {
        string cmd;
        cin >> cmd;
        if (cmd == "get")
        {
            int key;
            cin >> key;
            cout << cache.get(key) << endl;
        }
        else if (cmd == "set")
        {
            int key, value;
            cin >> key >> value;
            cache.set(key, value);
        }
    }

    return 0;
}
