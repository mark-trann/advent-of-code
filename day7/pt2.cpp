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
const int N = 16;
const int M = 15;

char grid[N][M];
int memo[N][M];

int dfs(int i, int j) {
    if (j < 0 || j >= M) return 0;
    if (memo[i][j]) return memo[i][j];
    if (i == N - 1) return 1;
    memo[i][j] += grid[i][j] == '.' ? dfs(i + 1, j) : dfs(i, j - 1) + dfs(i, j + 1);
    return memo[i][j];
}

void solution() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cin >> grid[i][j];
        }
    }
    int sPosition = 0;
    for (int i = 0; i < M; i++) {
        if (grid[0][i] == 'S') {
            sPosition = i;
            break;
        }
    }
    cout << dfs(1, sPosition) << endl;
}

int32_t main() {
    FAST_IO;
    solution();
}