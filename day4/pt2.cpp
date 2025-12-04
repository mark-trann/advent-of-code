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

const int N = 136;
char matrix[N][N];
int papers[N][N];
bool removed[N][N];

pair<int, int> directions[8] = {
    {-1, -1}, {-1, 0}, {-1, 1},
    {0, -1}, {0, 1},
    {1, -1}, {1, 0}, {1, 1},
};

int countPapers(int i, int j) {
    int res = 0;
    for (auto direction : directions) {
        int row = i + direction.first;
        int col = j + direction.second;
        if (row >= 0 && row < N && col >= 0 && col < N && matrix[row][col] == '@')
            res++;
    }
    return res;
}

void solution() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> matrix[i][j];
        }
    }
    queue<pair<int, int>> q;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (matrix[i][j] != '@') continue;
            papers[i][j] = countPapers(i, j);
            if (papers[i][j] < 4) q.emplace(i, j);
        }
    }

    int res = 0;
    while (!q.empty()) {
        auto [ i, j ] = q.front();
        q.pop();
        if (removed[i][j]) continue;
        papers[i][j]--;
        if (papers[i][j] < 4) {
            res++;
            removed[i][j] = true;
            for (auto direction : directions) {
                int row = i + direction.first;
                int col = j + direction.second;
                if (row >= 0 && row < N && col >= 0 && col < N && matrix[row][col] == '@')
                    q.emplace(row, col);
            }
        }
    }
    cout << res << endl;
}

int32_t main() {
    FAST_IO;
    solution();
}