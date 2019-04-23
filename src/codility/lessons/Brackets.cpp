/**
 * Link: https://codility.com/programmers/lessons/7-stacks_and_queues/brackets/
 */

#include <stack>
#include <string>

using namespace std;

int solution(string& str)
{
    stack<char> s;
    for (auto c : str)
    {
        switch (c)
        {
            case '(':
            case '[':
            case '{': s.push(c); break;
            case ')': if (s.empty() || s.top() != '(') return 0; s.pop(); break;
            case ']': if (s.empty() || s.top() != '[') return 0; s.pop(); break;
            case '}': if (s.empty() || s.top() != '{') return 0; s.pop(); break;
        }
    }

    return s.empty();
}

int main()
{
    return 0;
}
