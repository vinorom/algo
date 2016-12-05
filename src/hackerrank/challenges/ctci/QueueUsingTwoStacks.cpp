/**
 * Problem:
 *      Cracking the Coding Interview: Queues: A Tale of Two Stacks
 *
 * Links:
 *      https://www.hackerrank.com/challenges/ctci-queue-using-two-stacks
 */

#include <bits/stdc++.h>

using namespace std;

class MyQueue
{
    stack<int> stack_newest_on_top;
    stack<int> stack_oldest_on_top;

public:
    void push(int x)
    {
        stack_newest_on_top.push(x);
    }

    void pop()
    {
        if (stack_oldest_on_top.empty()) move();
        assert(!stack_oldest_on_top.empty());
        stack_oldest_on_top.pop();
    }

    int front()
    {
        if (stack_oldest_on_top.empty()) move();
        assert(!stack_oldest_on_top.empty());
        return stack_oldest_on_top.top();
    }

private:
    void move()
    {
        while (!stack_newest_on_top.empty())
        {
            stack_oldest_on_top.push(stack_newest_on_top.top());
            stack_newest_on_top.pop();
        }
    }
};

int main()
{
    MyQueue q1;
    int q, type, x;
    cin >> q;

    for(int i = 0; i < q; i++)
    {
        cin >> type;
        if(type == 1)
        {
            cin >> x;
            q1.push(x);
        }
        else if(type == 2)
        {
            q1.pop();
        }
        else
        {
            cout << q1.front() << endl;
        }
    }

    return 0;
}
