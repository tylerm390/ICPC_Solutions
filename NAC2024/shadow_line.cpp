#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); i++)
#define sz(x) (int) (x).size()
#define all(x) begin(x), end(x)

#pragma GCC optimize("O2")
// #pragma GCC target("avx2")

using ll = long long;
using ld = double;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vii = vector<pii>;

struct DSU {
    vi e; vii st; int comp;
    DSU(int n = 0): e(n, -1), comp(n) {}
    int time() { return sz(st); }
    void rollback(int t) {
        comp += (time() - t) / 2;
        for(int i = time()-1; i >= t; i--)
            e[st[i].first] = st[i].second;
        st.resize(t);
    }
    int find(int x) { return e[x] < 0 ? x : find(e[x]); }
    bool join(int x, int y) {
        x = find(x), y = find(y);
        if(x == y) return false;
        if(e[x] > e[y]) swap(x, y);
        st.emplace_back(x, e[x]);
        st.emplace_back(y, e[y]);
        e[x] += e[y]; e[y] = x;
        comp--;
        return true;
    }
};

const ld inf = 1e300;

vector<ld> vals;

DSU dsu;
ld dyn_con(int L, int R, const vector<array<int, 4>> &ranges) {
    vector<array<int, 4>> new_ranges;
    int t = dsu.time();
    for(auto [lo, hi, i, j]: ranges) {
        if(hi < L || R < lo) continue;
        if(lo <= L && R <= hi) {
            dsu.join(i, j);
            continue;
        }
        new_ranges.push_back({lo, hi, i, j});
    }

    ld ret = 0.0;
    if(L == R && dsu.comp == 1) {
        ret = vals[R+1] - vals[L];
    }
    else if(L != R) {
        int M = (L + R) >> 1;
        ret += dyn_con(L, M, new_ranges);
        ret += dyn_con(M+1, R, new_ranges);
    }
    
    dsu.rollback(t);

    return ret;
}

int main() {
    cin.tie(0) -> sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(10) << fixed;

    int n, w; cin >> n >> w;
    vector<array<int, 3>> walls(n);
    rep(i, 0, n) rep(j, 0, 3)
        cin >> walls[i][j];

    if(n == 1) {
        cout << -1 << '\n';
        return 0;
    }

    auto interp = [&](ld x1, ld y1, ld x2, ld y2) -> ld {
        return x1 - (x1 - x2) / (y1 - y2) * y1; 
    };

    using range = tuple<ld, ld, int, int>;
    vector<range> ranges;
    rep(i, 0, n) rep(j, i+1, n) {
        auto w1 = walls[i], w2 = walls[j];
        if(w1[1] > w2[1]) swap(w1, w2);

        ld lo = 0, hi = inf;

        ld inter1 = -interp(w1[0], w1[1], w2[0], w2[2]);
        ld inter2 = -interp(w1[0], w1[2], w2[0], w2[1]);

        if(w1[2] >= w2[1]) lo = max({lo, inter1, inter2});
        else hi = min(hi, max(inter1, inter2)), lo = max(lo, min(inter1, inter2));

        if(hi < lo) continue;

        ranges.emplace_back(lo, hi, i, j);
    }

    if(sz(ranges) == 0) {
        cout << 0.0 << '\n';
        return 0;
    }

    for(auto [lo, hi, i, j]: ranges) {
        vals.push_back(lo);
        vals.push_back(hi);
    }

    sort(all(vals));
    vals.erase(unique(all(vals)), end(vals));
    vals.push_back(inf);

    vector<array<int, 4>> ranges_cc;
    for(auto [lo_d, hi_d, i, j]: ranges) {
        int lo = lower_bound(all(vals), lo_d) - begin(vals);
        int hi = lower_bound(all(vals), hi_d) - begin(vals) - 1;
        ranges_cc.push_back({lo, hi, i, j});
    }

    dsu = DSU(n);
    ld res = dyn_con(0, sz(vals)-2, ranges_cc);

    if(res > inf / 2) cout << -1 << '\n';
    else cout << res << '\n';

    return 0;
}