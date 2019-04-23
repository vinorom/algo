/**
 * Problem:
 *      Cracking the Coding Interview: Is This a Binary Search Tree?
 *
 * Links:
 *      https://www.hackerrank.com/challenges/ctci-is-binary-search-tree
 */

#include <limits>

struct Node
{
    int data;
    Node* left;
    Node* right;
};

bool checkBSTImpl(Node* root, int min, int max)
{
    if (!root) return true;
    if (root->data <= min || root->data >= max) return false;
    return checkBSTImpl(root->left, min, root->data) && checkBSTImpl(root->right, root->data, max);
}

bool checkBST(Node* root)
{
    return checkBSTImpl(root, std::numeric_limits<int>::min(), std::numeric_limits<int>::max());
}

int main()
{
    return 0;
}

