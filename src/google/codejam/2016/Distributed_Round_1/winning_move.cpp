/**
 * https://code.google.com/codejam/contest/11264486/dashboard#s=p4
 */

#include <message.h>
#include <iostream>
#include <vector>
#include "winning_move.h"
//#include "data/winning_move1.h"
//#include "data/winning_move2.h"
//#include "data/winning_move3.h"

using namespace std;

typedef long long ll;

static const ll MASTER_NODE = 0;

ll my_hash(ll value)
{
    return value * 2654435761LL;
}

int main()
{
    ll players = GetNumPlayers();
    ll nodes = NumberOfNodes();
    ll local_node_id = MyNodeId();

    vector<ll> values;
    for (ll i = 0; i < players; ++i)
    {
        ll value = GetSubmission(i);
        ll id = my_hash(value) % players;
        if (id == local_node_id) values.push_back(value);
    }

    sort(values.begin(), values.end());

    ll min_unique_value = 0; // no such value
    {
        ll i = 0;
        while (i < values.size())
        {
            ll value = values[i];
            ll count = 1;
            for (++i; i < values.size() && values[i] == value; ++i, ++count);
            if (count == 1)
            {
                min_unique_value = value;
                break;
            }
        }
    }

    if (local_node_id != MASTER_NODE)
    {
        PutLL(MASTER_NODE, min_unique_value);
        Send(MASTER_NODE);
    }
    else
    {
        for (ll i = 0; i < nodes; ++i)
        {
            if (i != MASTER_NODE)
            {
                ll received_value = GetLL(Receive(-1));
                if (received_value == 0) continue;

                if (min_unique_value == 0) min_unique_value = received_value;
                else min_unique_value = min(min_unique_value, received_value);
            }
        }
        cout << min_unique_value << '\n';
    }

    return 0;
}
