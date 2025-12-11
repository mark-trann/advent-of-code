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
// gets bit string value with format without brackets
uint32_t getBitString(string buttonStr) {
    auto commaPos = buttonStr.find(',');
    uint32_t tmp = 0;
    while (commaPos != string::npos) {
        tmp |= (1 << (stoi(buttonStr.substr(0, commaPos))));
        buttonStr = buttonStr.substr(commaPos + 1);
        commaPos = buttonStr.find(',');
    }
    tmp |= (1 << stoi(buttonStr));
    return tmp;
}

vector<uint32_t> getButtons(string buttonStr) {
    vector<uint32_t> buttons;
    auto spacePos = buttonStr.find(' ');
    while (spacePos != string::npos) {
        buttons.push_back(getBitString(buttonStr.substr(1, spacePos - 2)));
        buttonStr = buttonStr.substr(spacePos + 1);
        spacePos = buttonStr.find(' ');
    }
    buttons.push_back(getBitString(buttonStr.substr(1, buttonStr.length() - 2)));
    return buttons;
}

int minPresses(vector<uint32_t>& buttons, uint32_t target) {
    vector<pair<uint32_t, int>> combs = {{0, 0}};
    for (int i = 0; i < buttons.size(); i++) {
        vector<pair<uint32_t, int>> tmp;
        for (auto [comb, cnt] : combs) {
            auto num = comb ^ buttons[i];
            tmp.emplace_back(num, cnt + 1);
        }
        for (auto pr : tmp) combs.push_back(pr);
    }
    int res = INFINITY;
    for (auto [comb, cnt] : combs) {
        if (comb == target) res = min(res, cnt);
    }
    return res;
}

///////////////////////////////////////////ALTERNATE SOLUTION//////////////////////////////////////////////////////////////////////////
int minPressesAlternate(vector<uint32_t>& buttons, uint32_t target) {
    queue<pair<uint32_t, int>> q;
    unordered_map<uint32_t, bool> visited;
    q.emplace(0, 0);
    while (!q.empty()) {
        auto [switchStatus, count] = q.front();
        q.pop();
        if (switchStatus == target) return count;
        if (visited[switchStatus]) continue;
        visited[switchStatus] = true;
        for (auto button : buttons) {
            if (!visited[switchStatus ^ button])
                q.emplace(switchStatus ^ button, count + 1);
        }
    }
    return INFINITY;
}
void alternateSolution() {
    string line;
    int res = 0;
    while (getline(cin, line)) {
        auto closeSq = line.find(']');
        auto lastRnd = line.find('{') - 2;
        auto buttonStr = line.substr(closeSq + 2, lastRnd - closeSq - 1);
        auto buttons = getButtons(buttonStr);

        auto lights = line.substr(1, closeSq - 1);
        uint32_t target = 0;
        for (int i = 0; i < static_cast<int>(lights.length()); i++) {
            if (lights[i] == '#') target |= (1 << i);
        }
        res += minPresses(buttons, target);
    }
    cout << res << endl;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void solution() {
    string line;
    int res = 0;
    while (getline(cin, line)) {
        auto closeSq = line.find(']');
        auto lastRnd = line.find('{') - 2;
        auto buttonStr = line.substr(closeSq + 2, lastRnd - closeSq - 1);
        auto buttons = getButtons(buttonStr);

        auto lights = line.substr(1, closeSq - 1);
        uint32_t target = 0;
        for (int i = 0; i < static_cast<int>(lights.length()); i++) {
            if (lights[i] == '#') target |= (1 << i);
        }
        res += minPresses(buttons, target);
    }
    cout << res << endl;
}

int32_t main() {
    FAST_IO;
    solution();
}