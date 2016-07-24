/**
 * https://code.google.com/codejam/contest/11264486/dashboard#s=p2
 */

#include <message.h>
#include <iostream>
#include "rps.h"
//#include "data/rps1.h"
//#include "data/rps2.h"
//#include "data/rps3.h"

using namespace std;

typedef long long ll;

ll get_winner(ll left, ll right)
{
    auto lc = GetFavoriteMove(left);
    auto rc = GetFavoriteMove(right);

    switch (lc)
    {
        case 'R': return rc != 'P' ? left : right;
        case 'S': return rc != 'R' ? left : right;
        case 'P': return rc != 'S' ? left : right;
    }

    assert(false);

    return -1;
}

ll play(ll left, ll right)
{
    if (left == right) return left;

    ll mid = (left + right) / 2;
    return get_winner(play(left, mid), play(mid + 1, right));
}

int main()
{
    ll N = GetN();
    ll nodes = NumberOfNodes();
    ll my_id = MyNodeId();

    nodes = min(nodes, N);
    ll size = 1LL << N;

    ll nodes2 = 1;
    for (; nodes > 1; nodes >>= 1, nodes2 <<= 1);
    nodes = nodes2;

    if (my_id >= nodes) return 0;

    ll block = size / nodes;
    ll left = my_id * block;
    ll right = left + block - 1;

    ll winner = play(left, right);

    ll idx = my_id;
    while (block != size)
    {
        if (idx & 1)
        {
            PutLL(idx - 1, winner);
            Send(idx - 1);
            break;
        }
        else
        {
            ll src = Receive(-1);
            winner = get_winner(winner, GetLL(src));
        }

        idx >>= 1;
        block <<= 1;
    }

    if (block == size) cout << winner << '\n';

    return 0;
}
