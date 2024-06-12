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

const int tot_time = 5e6 + 10, inf = 1e9; 

int main() {
    cin.tie(0) -> sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    
    int n; cin >> n;
    vi a(n), b(n);
    rep(i, 0, n)
        cin >> a[i] >> b[i];

    vi dp(tot_time, inf);
    dp[0] = 0;
    rep(i, 0, n) {
        for(int j = tot_time-1; j >= 0; j--) {
            dp[j] += b[i];
            if(j >= a[i])
                dp[j] = min(dp[j], dp[j-a[i]]);
        }
    }

    int res = inf;
    rep(a_time, 0, tot_time)
        res = min(res, max(a_time, dp[a_time]));
    
    cout << res << '\n';

    return 0;
}