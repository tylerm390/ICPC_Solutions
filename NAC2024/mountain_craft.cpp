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

struct node {
    int lo, md, hi;
    int min_val = 0, cnt_min, lazy = 0;
    node *left = 0, *right = 0;
    node(int L, int R): lo(L), md((L+R) >> 1), hi(R), cnt_min(R-L+1) {}
    
    void check() {
        if(left) return;
        left = new node(lo, md);
        right = new node(md+1, hi);
    }

    void lazy_update(int d) {
        min_val += d;
        lazy += d;
    }

    void prop() {
        if(!lazy) return;
        left->lazy_update(lazy);
        right->lazy_update(lazy);
        lazy = 0;
    }

    void update(int L, int R, int d) {
        if(R < lo || hi < L) return;
        if(L <= lo && hi <= R) return lazy_update(d);
        check(); prop();

        left->update(L, R, d);
        right->update(L, R, d);

        min_val = min(left->min_val, right->min_val);
        cnt_min = 0;
        if(min_val == left->min_val) cnt_min += left->cnt_min;
        if(min_val == right->min_val) cnt_min += right->cnt_min; 
    }
};

const double sqrt2 = sqrt(2);

int main() {
    cin.tie(0) -> sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(10) << fixed;

    int q, w; cin >> q >> w;
    node seg_tree(0, w);
    set<pii> ranges;
    while(q--) {
        int x, y; cin >> x >> y;
        int lo = max(0, x - y), hi = min(w, x + y) - 1;
        int d;
        if(ranges.count(pii(x-y, x+y))) {
            d = -1;
            ranges.erase(pii(x-y, x+y));
        }
        else {
            d = 1;
            ranges.insert(pii(x-y, x+y));
        }
        seg_tree.update(lo, hi, d);

        if(seg_tree.min_val == 0)
            cout << sqrt2 * (w - seg_tree.cnt_min + 1) << '\n';
        else
            cout << sqrt2 * w << '\n';
    }

    return 0;
}