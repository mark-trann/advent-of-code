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

const int MAXN = 200;
const int MAXM = 100;
vector<vector<int>> arr;

void solution() {
    for (int i = 0; i < MAXN; i++) {
        vector<int> temp;
        for (int j = 0; j < MAXM; j++) {
            char c;
            cin >> c;
            temp.push_back(c - 48);
        }
        arr.push_back(temp);
    }

    int res = 0;
    for (int i = 0; i < MAXN; i++) {
        vector<vector<int>> dp(MAXM, vector<int>(13, 0));
        for (int j = 0; j < MAXM; j++)
            dp[j][1] = arr[i][j];

        for (int j = 1; j < MAXM; j++) {
            for (int k = 1; k < 13; k++) {
                dp[j][k] = max(dp[j-1][k - 1] * 10 + arr[i][j], dp[j-1][k]);
            }
        }

        int max_elem = 0;
        for (int j = 0; j < MAXM; j++) {
            max_elem = max(max_elem, dp[j][12]);
            // cout << dp[j][11] << endl;
        }
        cout << max_elem << endl;
        res += max_elem;
    }
    cout << res << endl;
}

int32_t main() {
    FAST_IO;
    solution();
}