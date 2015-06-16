/**
 * https://www.hackerrank.com/contests/w15/challenges/huskar-tuskar-and-balls
 * Solution is based on Tarjan's offline LCA algoritm: http://en.wikipedia.org/wiki/Tarjan%27s_off-line_lowest_common_ancestors_algorithm
 */
#include <vector>
#include <stack>
#include <unordered_map>
#include <iostream>

using namespace std;

struct Node
{
    int key;
    Node* parent;
    vector<Node*> children;
    int depth;

    bool explored;
    Node* leader;
    int rank;
    Node* ancestor;

    Node(): key(-1), parent(), depth(0), explored(false), leader(), rank(0), ancestor() {}
};

typedef vector<Node> NodeVec;
NodeVec tree;


void make_set(Node* x)
{
    x->leader = x;
    x->rank = 0;
}

Node* do_find(Node* x) // with path compression
{
    Node* lead = x;
    for (; lead != lead->leader; lead = lead->leader);
    for (Node* xp = x; x != lead; xp = x, x = x->leader, xp->leader = lead);
    return x;
}

void do_union(Node* x, Node* y) // union by rank
{
    Node* xlead = do_find(x);
    Node* ylead = do_find(y);
    if (xlead->rank > ylead->rank)
    {
        ylead->leader = xlead;
    }
    else if (xlead->rank < ylead->rank)
    {
        xlead->leader = ylead;
    }
    else if (xlead != ylead)
    {
        ylead->leader = xlead;
        xlead->rank++;
    }
}

vector<Node*> path;

void find_depth(Node* node)
{
    path.clear();
    for (; node->depth == 0; path.push_back(node), node = node->parent);
    for (int i = (int)path.size()-1, d = node->depth + 1; i >= 0; path[i]->depth = d++, --i);
}

typedef long long ll;
typedef vector<vector<Node*>> PairMap;
typedef unordered_map<ll /*x#y*/, Node* /*LCA*/> LCAMap;
PairMap lca_pair_map;
LCAMap lca_map(200007);

Node* lookup_lca(Node* x, Node* y)
{
    if (x->key > y->key) swap(x, y);
    ll key = (ll)x->key * 1000000 + y->key;
    LCAMap::iterator it = lca_map.find(key); // should be successful if implementation is correct
    return it->second;
}

void cache_lca(Node* x, Node* y, Node* lca)
{
    if (x->key > y->key) swap(x, y);
    ll key = (ll)x->key * 1000000 + y->key;
    lca_map[key] = lca;
}

void TarjanOLCA_iterative(Node* r) // iterative Tarjan's offline LCA algorithm
{
    stack<pair<Node*, int>> s;
    s.push(make_pair(r, 0));

    while (!s.empty())
    {
        Node* u = s.top().first;
        int child_idx = s.top().second;
        s.pop();

        if (child_idx == 0) // just started processing of node u
        {
            make_set(u);
            u->ancestor = u;
        }

        if (child_idx >= u->children.size()) // node is fully traversed
        {
            u->explored = true;

            // calc LCA
            const vector<Node *> &vs = lca_pair_map[u->key];
            for (int i = 0; i < vs.size(); ++i)
            {
                Node *v = vs[i];
                if (v->explored) cache_lca(u, v, do_find(v)->ancestor);
            }

            // update union find structure
            if (u != r) // not root
            {
                do_union(u->parent, u);
                do_find(u->parent)->ancestor = u->parent;
            }
        }
        else
        {
            Node* child = u->children[child_idx];
            s.push(make_pair(u, ++child_idx));
            s.push(make_pair(child, 0));
        }
    }
}

void TarjanOLCA_recursive(Node* u) // recursive Tarjan's offline LCA algorithm
{
    make_set(u);
    u->ancestor = u;
    for (int i = 0; i < u->children.size(); ++i)
    {
        Node* v = u->children[i];
        TarjanOLCA_recursive(v);
        do_union(u, v);
        do_find(u)->ancestor = u;
    }
    u->explored = true;

    const vector<Node*>& vs = lca_pair_map[u->key];
    for (int i = 0; i < vs.size(); ++i)
    {
        Node* v = vs[i];
        if (v->explored) cache_lca(u, v, do_find(v)->ancestor);
    }
}

void solve(Node* huskar_node, Node* tuskar_node, int& huskar_score, int& tuskar_score)
{
    if (huskar_node->depth == 0) find_depth(huskar_node);
    if (tuskar_node->depth == 0) find_depth(tuskar_node);
    int dh = huskar_node->depth;
    int dt = tuskar_node->depth;

    Node* lca = lookup_lca(huskar_node, tuskar_node);
    //cout << "lca: " << lca->key << " dh=" << dh << " dt=" << dt << endl;
    if (lca == tuskar_node)
    {
        huskar_score = dh - dt;
        tuskar_score = dt;
    }
    else if (lca == huskar_node)
    {
        huskar_score = dh;
        tuskar_score = dt - dh;
    }
    else
    {
        huskar_score = dh;
        tuskar_score = dt - lca->depth;
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N, Q;
    cin >> N >> Q;

    path.reserve(N);
    tree.resize(N);
    tree[0].key = 0;
    tree[0].depth = 1;

    for (int i = 1; i < N; ++i)
    {
        int par;
        cin >> par;
        --par;

        tree[i].key = i;
        tree[i].parent = &tree[par];
        tree[i].parent->children.push_back(&tree[i]);
    }

    vector<pair<Node*, Node*>> queries(Q);
    lca_pair_map.resize(N);
    for (int i = 0; i < Q; ++i)
    {
        int huskar_node, tuskar_node;
        cin >> huskar_node >> tuskar_node;
        queries[i].first = &tree[huskar_node - 1];
        queries[i].second = &tree[tuskar_node - 1];
        lca_pair_map[queries[i].first->key].push_back(queries[i].second);
        lca_pair_map[queries[i].second->key].push_back(queries[i].first);
    }
    TarjanOLCA_iterative(&tree[0]);

    for (int i = 0; i < queries.size(); ++i)
    {
        int huskar_score = 0, tuskar_score = 0;
        solve(queries[i].first, queries[i].second, huskar_score, tuskar_score);
        cout << huskar_score << " " << tuskar_score << "\n";
    }
    cout.flush();

    return 0;
}
