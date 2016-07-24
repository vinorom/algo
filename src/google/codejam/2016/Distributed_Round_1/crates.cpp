/**
 * https://code.google.com/codejam/contest/11264486/dashboard#s=p3
 */

#include <message.h>
#include <iostream>
#include <vector>
#include "crates.h"
//#include "data/crates1.h"
//#include "data/crates2.h"
//#include "data/crates3.h"

using namespace std;

typedef long long ll;

static const ll MASTER_NODE = 0;

int main()
{
    struct Block
    {
        ll sum, size, offset;
        Block(): sum(0), size(0), offset(0) {}
    };

    ll num_stacks = GetNumStacks();
    ll nodes = NumberOfNodes();
    ll local_node_id = MyNodeId();

    nodes = min(nodes, num_stacks);

    if (local_node_id >= nodes) return 0;

    // init local stacks and calculate local block properties (sum, size, offset)
    Block local_block;

    local_block.size = num_stacks / nodes;
    local_block.offset = local_node_id * local_block.size;
    if (local_node_id == nodes - 1) local_block.size += num_stacks % nodes;

    ll local_stacks[local_block.size];
    for (ll i = 0; i < local_block.size; ++i)
    {
        local_stacks[i] = GetStackHeight(local_block.offset + i + 1);
        local_block.sum += local_stacks[i];
    }

    // send/recv local block properties to/from others
    vector<Block> blocks(nodes);
    blocks[local_node_id] = local_block;

    for (ll i = 0; i < nodes; ++i)
    {
        if (i != local_node_id)
        {
            PutLL(i, local_block.size);
            PutLL(i, local_block.sum);
            PutLL(i, local_block.offset);
            Send(i);
        }
    }

    for (ll i = 0; i < nodes; ++i)
    {
        if (i != local_node_id)
        {
            ll src = Receive(-1);
            blocks[src].size = GetLL(src);
            blocks[src].sum = GetLL(src);
            blocks[src].offset = GetLL(src);
        }
    }

    // init global prefix sum array
    ll prefix_sum[nodes];
    for (ll i = 0; i < nodes; ++i)
    {
        prefix_sum[i] = blocks[i].sum;
        if (i > 0) prefix_sum[i] += prefix_sum[i - 1];
    }

    ll total_sum = prefix_sum[nodes-1];

    // init global prefix move count array
    ll avg_sum = total_sum / num_stacks;
    ll rem = total_sum % num_stacks;

    ll prefix_move_sum[nodes]; // how many moves required on the right boundary (- out, + in)
    for (ll i = 0; i < nodes; ++i)
    {
        ll expected_block_sum = avg_sum * blocks[i].size;
        if (blocks[i].offset < rem) expected_block_sum += min(rem - blocks[i].offset, blocks[i].size);

        prefix_move_sum[i] = expected_block_sum - blocks[i].sum;
        if (i > 0) prefix_move_sum[i] += prefix_move_sum[i-1];
    }

    // calculate local move count
    ll local_left_moves = local_node_id == 0 ? 0 : -prefix_move_sum[local_node_id-1];
    ll local_right_moves = prefix_move_sum[local_node_id];
    ll local_moves = 0;

    if (local_left_moves < 0) local_moves += -local_left_moves;
    local_stacks[0] += local_left_moves;

    if (local_right_moves < 0) local_moves += -local_right_moves;
    local_stacks[local_block.size-1] += local_right_moves;

    rem -= local_block.offset;
    for (ll i = 0; i < local_block.size - 1; ++i, --rem)
    {
        ll expected_sum = avg_sum + (rem > 0 ? 1 : 0);
        ll diff = expected_sum - local_stacks[i];
        local_stacks[i+1] -= diff;
        local_moves += llabs(diff);
    }

    assert(local_stacks[local_block.size-1] == avg_sum + (rem > 0 ? 1 : 0));

    // aggregate intermediate results on master node
    if (local_node_id != MASTER_NODE)
    {
        PutLL(MASTER_NODE, local_moves);
        Send(MASTER_NODE);
    }
    else
    {
        for (ll i = 0; i < nodes; ++i)
        {
            if (i != local_node_id) local_moves += GetLL(Receive(-1));
        }
        cout << local_moves << '\n';
    }

    return 0;
}
