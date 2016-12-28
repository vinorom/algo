/**
 * Problem:
 *      Cracking the Coding Interview: Tries: Contacts
 *
 * Links:
 *      https://www.hackerrank.com/challenges/ctci-contacts
 */

#include <bits/stdc++.h>

using namespace std;

class CTrie
{
public:
    bool add(const string& str)
    {
        stack<CTrieRecord*> s;

        s.push(&root_);

        for (auto c : str)
        {
            assert(c >= 'a' && c <= 'z');
            s.push(&s.top()->records[c]);
        }

        if (s.top()->value) return false;

        s.top()->value = true;

        while (!s.empty()) s.top()->count++, s.pop();

        return true;
    }

    int find(const string& prefix) const
    {
        const auto* rec = &root_;
        for (auto c : prefix)
        {
            assert(c >= 'a' && c <= 'z');

            auto it = rec->records.find(c);
            if (it == rec->records.end()) return 0;
            rec = &it->second;
        }

        return  rec->count;
    }

private:
    struct CTrieRecord
    {
        bool value = false;
        int count = 0;
        map<char, CTrieRecord> records;
    };

    CTrieRecord root_;
};

int main()
{
    CTrie contacts;

    int n;
    cin >> n;
    while (n--)
    {
        string cmd, param;
        cin >> cmd >> param;

        if (cmd == "add") contacts.add(param);
        else if (cmd == "find") cout << contacts.find(param) << '\n';
    }

    return 0;
}

