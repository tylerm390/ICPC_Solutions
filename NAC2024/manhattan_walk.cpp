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

int main() {
    cin.tie(0) -> sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(10) << fixed;

    int n, m, p; cin >> n >> m >> p;
    vector<vector<double>> dp(n, vector<double>(m, -1.0));
    auto calc = [&](int i, int j, auto &calc) -> double {
        if(i == n-1 && j == m-1) return 0;

        auto &cur = dp[i][j];
        if(cur != -1.0) return cur;

        if(i == n-1) {
            cur = 0.25 * p + calc(i, j+1, calc);
        }
        else if(j == m-1) {
            cur = 0.25 * p + calc(i+1, j, calc);
        }
        else {
            auto down = calc(i+1, j, calc);
            auto right = calc(i, j+1, calc);
            // make down the shorter option
            if(down > right) swap(down, right);

            auto dif = right - down;
            if(dif >= p)
                cur = 0.25 * p + down;
            else {
                // If pointing right:
                //      - wait to go down if timer is < dif
                //      - Otherwise go right
                cur = 0.5 * (0.5*dif*dif + dif*down + (p - dif)*right) / p; 
                // If pointing down, go down
                cur += 0.5 * down; 
            }
        }

        return cur;
    };

    cout << calc(0, 0, calc) << '\n';

    return 0;
}