#include <bits/stdc++.h>
using namespace std;

#define int long long
#define ull unsigned long long

#define FAST_IO (ios_base:: sync_with_stdio(false),cin.tie(NULL));
#define MOD 1000000007


int factorial(int n)               { if(n==0) return 1; int res = 1; for (int i = 2; i <= n; i++) res = res * i; return res; }
int nPr(int n, int r)              { return factorial(n) / factorial(n - r); }
int nCr(int n, int r)              { return factorial(n) / (factorial(r) * factorial(n - r));}
int gcd(int a, int b)              { if (b == 0) return a; return gcd(b, a % b); }
int lcm(int a, int b)              { return (a * b) / gcd(a, b);}
ull mypow(ull a, ull b)         { ull ans = 1; a%=MOD; while(b){ if (b&1) ans = (ans*a) % MOD; a = (a*a) % MOD; b >>= 1; } return ans; }

bool isPrime(int n)              { if(n <= 1) return false; for(int i = 2; i*i <= n; i++) if(n % i == 0) return false; return true; }
void _print(int t) {cerr << t;}
void _print(string t) {cerr << t;}void _print(char t) {cerr << t;}
void _print(long double t) {cerr << t;}void _print(double t) {cerr << t;}void _print(unsigned int t) {cerr << t;}
template <class T> void _print(vector <T> v);template <class T> void _print(set <T> v);
template <class T, class V> void _print(map <T, V> v);template <class T> void _print(multiset <T> v);
template <class T, class V> void _print(pair <T, V> p) {cerr << "{"; _print(p.first); cerr << ","; _print(p.second); cerr << "}" << '\n';}
template <class T> void _print(vector <T> v) {cerr << "[ "; for (T i : v) {_print(i); cerr << " ";} cerr << "]" << '\n';}
template <class T> void _print(set <T> v) {cerr << "[ "; for (T i : v) {_print(i); cerr << " ";} cerr << "]" << '\n';}
template <class T> void _print(multiset <T> v) {cerr << "[ "; for (T i : v) {_print(i); cerr << " ";} cerr << "]" << '\n';}
template <class T> void _print(unordered_set <T> v) {cerr<<"[ "; for(T i : v) {_print(i); cerr<<" ";} cerr<<"]" << '\n';}
template <class T, class V> void _print(map <T, V> v) {cerr << "[ "; for (auto i : v) {_print(i); cerr << " ";} cerr << "]" << '\n';}
template <class T, class V> void _print(multimap <T, V> v) {cerr << "[ "; for (auto i : v) {_print(i); cerr << " ";} cerr << "]" << '\n';} 
template <class T, class V> void _print(unordered_map <T, V> v) {cerr << "[ "; for (auto i : v) {_print(i); cerr << " ";} cerr << "]" << '\n';}
void precisePrint(double n, int32_t precision) {cout << fixed << setprecision(precision) << n << '\n';}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const int N = 100000;
typedef pair<int, int> point;
typedef pair<int, int> range;
vector<point> pts;
vector<range> ranges(N, {0, INFINITY});

void addRange(point curr, point target) {
    auto p = curr.second < target.second ? curr : target;
    auto t = curr.second < target.second ? target : curr;
    while (p.second <= t.second) {
        auto [storedLeft, storedRight] = ranges[p.second];
        ranges[p.second] = {max(storedLeft, p.first), min(storedRight, p.first)};
        p.second++;
    }
}

void solution() {
    char dummy;
    int xR, yR;
    bool isFirst = true;
    point prev;
    while (cin >> xR >> dummy >> yR) {
        if (!isFirst) {
            addRange({xR, yR}, prev);
        }
        isFirst = false;
        pts.emplace_back(xR, yR);
        prev = {xR, yR};
    }
    addRange(pts[0], prev);
    // ensuring range correct format
    for (auto& r : ranges) {
        auto [left, right] = r;
        if (left > right) r = {right, left};
    }
    // _print(ranges);
    int maxA = 0;
    for (int i = 0; i < static_cast<int>(pts.size()); i++) {
        auto [x1, y1] = pts[i];
        for (int j = i + 1; j < static_cast<int>(pts.size()); j++) {
            auto [x2, y2] = pts[j];
            if (x1 == x2 || y1 == y2) continue;
            bool canDo = true;
            int left = min(x1, x2), right = max(x1, x2);
            for (auto p = min(y1, y2); p <= max(y1, y2); p++) {
                if (left < ranges[p].first || right > ranges[p].second) {
                    canDo = false;
                    break;
                }
            }
            if (canDo)
                maxA = max(maxA, (abs(x1 - x2) + 1) * (abs(y1 - y2) + 1));
        }
    }
    cout << maxA << endl;
}

int32_t main() {
    FAST_IO;
    solution();
}