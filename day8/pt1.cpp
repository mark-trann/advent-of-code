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
const int N = 1000;
typedef tuple<int,int,int> point;
vector<point> coords;
vector<tuple<int, point, point>> pairPoints;
unordered_map<int, unordered_map<int, unordered_map<int, point>>> parent;
unordered_map<int, unordered_map<int, unordered_map<int, int>>> subtree_size;
set<point> relevantCoords;

void init() {
    for (auto [x,y,z] : coords) {
        parent[x][y][z] = {x,y,z};
        subtree_size[x][y][z] = 1;
    }
}

point root(point p) {
    auto [x,y,z] = p;
    return parent[x][y][z] == p ? p : parent[x][y][z] = root(parent[x][y][z]);
}

void join(point p1, point p2) {
    p1 = root(p1);
    p2 = root(p2);
    if (p1 == p2) return;
    auto [x1, y1, z1] = p1;
    auto [x2, y2, z2] = p2;
    if (subtree_size[x1][y1][z1] < subtree_size[x2][y2][z2]) {
        parent[x1][y1][z1] = p2;
        subtree_size[x2][y2][z2] += subtree_size[x1][y1][z1];
        relevantCoords.insert(p2);
        relevantCoords.erase(p1);
    } else {
        parent[x2][y2][z2] = p1;
        subtree_size[x1][y1][z1] += subtree_size[x2][y2][z2];
        relevantCoords.insert(p1);
        relevantCoords.erase(p2);
    }
}

void solution() {
    char dummy;
    int xR, yR, zR;
    while (cin >> xR >> dummy >> yR >> dummy >> zR) {
        coords.emplace_back(xR,yR,zR);
    }
    for (int i = 0; i < static_cast<int>(coords.size()); i++) {
        auto [x1, y1, z1] = coords[i];
        for (int j = i + 1; j < static_cast<int>(coords.size()); j++) {
            auto [x2, y2, z2] = coords[j];
            pairPoints.emplace_back(
                (x1 - x2) * (x1 - x2) +
                (y1 - y2) * (y1 - y2) +
                (z1 - z2) * (z1 - z2),
                coords[i],
                coords[j]
            );
        }
    }
    sort(pairPoints.begin(), pairPoints.end());
    init();
    for (int i = 0; i < N; i++) {
        auto [d, p1, p2] = pairPoints[i];
        join(p1, p2);
    }
    vector<point> parentPts(relevantCoords.begin(), relevantCoords.end());
    sort(parentPts.begin(), parentPts.end(), [](const point& a, const point& b){
        auto [x1,y1,z1] = a;
        auto [x2,y2,z2] = b;
        return subtree_size[x1][y1][z1] > subtree_size[x2][y2][z2];
    });
    int res = 1;
    for (int i = 0; i < 3; i++) {
        auto [x,y,z] = parentPts[i];
        res *= subtree_size[x][y][z];
    }
    cout << res << endl;
}

int32_t main() {
    FAST_IO;
    solution();
}