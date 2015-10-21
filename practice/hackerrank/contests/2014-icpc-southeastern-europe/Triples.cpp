/**
 * https://www.hackerrank.com/contests/2014-icpc-southeastern-europe/challenges/triples
 */

#include <iostream>
#include <unordered_map>

using namespace std;

class BigInt
{
    string value;

public:
    BigInt(int v = 0): value(std::to_string(v)) {}
    BigInt(const string& str): value(str) {}
    BigInt(const BigInt& rhv): value(rhv.value) {}

    const string& to_string() const { return value; }

    BigInt& operator=(const BigInt& rhv)
    {
        value = rhv.value;
        return *this;
    }

    BigInt& operator+=(const BigInt& rhv)
    {
        int dl = (int)value.size();
        int dr = (int)rhv.value.size();
        for (int off = 1, next_order = 0; off <= max(dl, dr) || next_order != 0; ++off)
        {
            int s = next_order;
            if (off <= dl) s += value[dl - off] - '0';
            if (off <= dr) s += rhv.value[dr - off] - '0';
            if (off > dl) { value = string(1, ' ') + value; ++dl; } // resize
            value[dl - off] = char('0' + (s % 10));
            next_order = s / 10;
        }
        return *this;
    }

    BigInt& operator-=(const BigInt& rhv)
    {
        int dl = (int)value.size();
        int dr = (int)rhv.value.size();
        for (int off = 1, next_order = 0; off <= dl; ++off)
        {
            int s = next_order;
            s += value[dl - off] - '0';
            if (off <= dr) s -= rhv.value[dr - off] - '0';
            value[dl - off] = char('0' + ((s + 10) % 10));
            next_order = s < 0 ? -1 : 0;
        }
        size_t pos = value.find_first_not_of('0');
        if (pos == string::npos)
        {
            value = "0";
        }
        else
        {
            value = value.substr(pos);
        }
        return *this;
    }

    BigInt& operator*=(int n)
    {
        if (n == 0)
        {
            value = "0";
            return *this;
        }
        if (n == 1) return *this;

        BigInt v(*this);
        (*this) *= (n / 2);
        (*this) += (*this);
        if (n % 2 == 1) (*this) += v;

        return *this;
    }

    bool operator==(const BigInt& rhv) { return value == rhv.value; }
    bool operator!=(const BigInt& rhv) { return !((*this) == rhv); }
    bool operator<(const BigInt& rhv) { return value.size() != rhv.value.size() ? value.size() < rhv.value.size() : value < rhv.value; }
    bool operator>(const BigInt& rhv) { return value.size() != rhv.value.size() ? value.size() > rhv.value.size() : value > rhv.value; }
    bool operator<=(const BigInt& rhv) { return value.size() != rhv.value.size() ? value.size() < rhv.value.size() : value <= rhv.value; }
    bool operator>=(const BigInt& rhv) { return value.size() != rhv.value.size() ? value.size() > rhv.value.size() : value >= rhv.value; }
};

struct hash_pair
{
    template <typename T1, typename T2>
    size_t operator()(const pair<T1, T2>& p) const
    {
        return std::hash<T1>()(p.first) ^ std::hash<T2>()(p.second);
    }
};

typedef pair<string, int> PSI;
typedef unordered_map<PSI, int, hash_pair> pow_map;

const int MAXM = 100;
const int MAXN = 100;

pow_map pow2comp;
BigInt comp2pow[MAXM+1][MAXN+1];

void precompute()
{
    for (int i = 0; i <= MAXM; ++i)
    {
        BigInt v(i*i);
        for (int j = 2; j <= MAXN; ++j, v *= i)
        {
            comp2pow[i][j] = v;
            pow2comp[PSI(v.to_string(), j)] = i;
        }
    }
}

int solve(int m, int n)
{
    int count = 0;
    for (int j = 2; j <= n; ++j)
    {
        for (int z = 0; z <= m; ++z)
        {
            const BigInt& zj = comp2pow[z][j];
            for (int y = 0; y <= z; ++y)
            {
                const BigInt& yj = comp2pow[y][j];
                BigInt xj = zj;
                xj -= yj;
                pow_map::const_iterator it = pow2comp.find(PSI(xj.to_string(), j));
                if (it != pow2comp.end() && xj <= yj) ++count;
            }
        }
    }
    return count;
}

int main()
{
    precompute();

    int m, n;
    cin >> m >> n;
    cout << solve(m, n) << endl;

    return 0;
}
