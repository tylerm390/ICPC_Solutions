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

int main() {
    cin.tie(0) -> sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n, i0, t0;
    cin >> n >> i0 >> t0;

    vector<set<int>> has(n+1);
    vvi seen(n+1, vi(n+1));
    has[0].insert(0);
    seen[0][0] = 1;
    rep(_, 0, n) {
        int i_lo, i_hi, t_lo, t_hi;
        cin >> i_lo >> i_hi >> t_lo >> t_hi;
        
        i_lo = max(0, i_lo - i0);
        i_hi = min(n, i_hi - i0);
        t_lo = max(0, t_lo - t0);
        t_hi = min(n, t_hi - t0);

        vii add, rem;
        rep(i, i_lo, i_hi+1) {
            auto it_lo = has[i].lower_bound(t_lo);
            auto it_hi = has[i].upper_bound(t_hi);
            for(auto it = it_lo; it != it_hi; it++) {
                rem.emplace_back(i, *it);
                if(!seen[i+1][*it]) add.emplace_back(i+1, *it);
                if(!seen[i][(*it)+1]) add.emplace_back(i, (*it)+1);
            }
        }

        for(auto [i, t]: rem)
            has[i].erase(t);

        for(auto [i, t]: add) {
            seen[i][t] = 1;
            has[i].insert(t);
        }
    }

    int res = 0;
    rep(i, 0, n+1) rep(t, 0, n+1)
        if(seen[i][t]) res = max(res, i + t);

    cout << res << '\n';

    return 0;
}