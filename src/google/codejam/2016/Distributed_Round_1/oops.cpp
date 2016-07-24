/**
 * https://code.google.com/codejam/contest/11264486/dashboard#s=p1
 */

#include <message.h>
#include <iostream>
#include <algorithm>
#include "oops.h"
//#include "data/oops1.h"
//#include "data/oops2.h"
//#include "data/oops3.h"

using namespace std;

typedef long long ll;

static const ll MASTER_NODE = 7;

int main() 
{
    ll N = GetN();
    ll nodes = NumberOfNodes();
    ll my_id = MyNodeId();
    ll max_diff = 0;

    for (ll i = my_id; i < N; i += nodes)
    {
        ll ai = GetNumber(i);
        for (ll j = 0; j < N; ++j) max_diff = max(max_diff, GetNumber(j) - ai);
    }

    if (my_id != MASTER_NODE)
    {
        PutLL(MASTER_NODE, max_diff);
        Send(MASTER_NODE);
    }
    else
    {
        for (ll i = 0; i < nodes - 1; ++i) max_diff = max(max_diff, GetLL(Receive(-1)));
        cout << max_diff << '\n';
    }

    return 0;
}
