#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); i++)
#define sz(x) (int) (x).size()
#define all(x) begin(x), end(x)

using ll = long long;
using ld = long double;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vii = vector<pii>;

template<class T, class U> istream& operator>>(istream &is, pair<T, U>& p) { is >> p.first >> p.second; return is; }
template<class T> istream& operator>>(istream& is, vector<T>& vec) { for(auto &x : vec) cin >> x; return is; } 
template<class T, class U> ostream& operator<<(ostream &os, const pair<T, U>& p) { os << "<" << p.first << "," << p.second << ">"; return os; }
template<class T> ostream& operator<<(ostream& os, const vector<T>& vec) { for(auto x : vec) os << x << " "; return os; }

bool test(vi &a, vi &b) {
    auto it_a = find(all(a), b[0]);
    rotate(begin(a), it_a, end(a));

    bool good = true;
    rep(i, 0, min(sz(a), sz(b)))
        good &= a[i] == b[i];
    
    return good;
}

int main() {
    cin.tie(0) -> sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    
    int n, m; cin >> n >> m;
    vi a(n), b(m);
    rep(i, 0, n) cin >> a[i];
    rep(i, 0, m) cin >> b[i];

    vi rev_a = a;
    reverse(all(rev_a));

    cout << (test(a, b) | test(rev_a, b)) << '\n';

    return 0;
}