#include <bits/stdc++.h>
using namespace std;

#pragma GCC target("popcnt")

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

int earliest_eval[11][11][2][2];

string prec = "(!=&|^";
map<char, int> prec_idx = {
    {'(', 0},
    {'!', 1},
    {'=', 2},
    {'&', 3},
    {'|', 4},
    {'^', 5}
};

#define bitat(mask, x) (((mask) >> (x)) & 1)
using bs = bitset<1024>;

int main() {
    cin.tie(0) -> sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n, k; cin >> n >> k;
    rep(i, 0, k) rep(j, 0, k)
        rep(x, 0, 2) rep(y, 0, 2)
            earliest_eval[i][j][x][y] = n;
    
    vi ret(n+1);
    rep(t, 0, n) {
        int i, j; cin >> i >> j; i--, j--;
        string eval; cin >> eval;
        cin >> ret[t];

        rep(x, 0, 2) rep(y, 0, 2) {
            if(earliest_eval[i][j][x][y] < n) continue;

            vector<int> s;
            for(char c: eval) {
                if(c == ')') {
                    int b = s.back(); s.pop_back();
                    int op = ~s.back(); s.pop_back();
                    while(op != 0) {
                        int a = s.back(); s.pop_back();
                        switch(op) {
                            case 2:
                                b = a == b;
                                break;
                            case 3:
                                b = a & b;
                                break;
                            case 4:
                                b = a | b;
                                break;
                            case 5:
                                b = a ^ b;
                                break;
                        }

                        assert(sz(s));
                        op = ~s.back(); s.pop_back();
                    }

                    while(sz(s) && ~s.back() == prec_idx['!']) {
                        b = !b;
                        s.pop_back();
                    }

                    s.push_back(b);
                }
                else if(prec_idx.count(c)) {
                    if(sz(s) > 1 && c != '(' && c != '!'){
                        int b = s.back(); s.pop_back();
                        int op = ~s.back();
                        while(op > 0 && op < prec_idx[c]) {
                            s.pop_back();
                            int a = s.back(); s.pop_back();
                            switch(op) {
                                case 2:
                                    b = a == b;
                                    break;
                                case 3:
                                    b = a & b;
                                    break;
                                case 4:
                                    b = a | b;
                                    break;
                                case 5:
                                    b = a ^ b;
                                    break;
                            }

                            if(!sz(s)) break;
                            op = ~s.back();
                        }
                        s.push_back(b);
                    }; 
                    s.push_back(~prec_idx[c]);
                }
                else {
                    int val;
                    if(c == '0') val = 0;
                    if(c == '1') val = 1;
                    if(c == 'x') val = x;
                    if(c == 'y') val = y;

                    while(sz(s) && ~s.back() == prec_idx['!']) {
                        val = !val;
                        s.pop_back();
                    }

                    s.push_back(val);
                }
            }

            int b = s.back(); s.pop_back();
            while(sz(s)) {
                int op = ~s.back(); s.pop_back();

                int a = s.back(); s.pop_back();
                switch(op) {
                    case 2:
                        b = a == b;
                        break;
                    case 3:
                        b = a & b;
                        break;
                    case 4:
                        b = a | b;
                        break;
                    case 5:
                        b = a ^ b;
                        break;
                }
            }

            if(b == 1)
                earliest_eval[i][j][x][y] = t;
        }
    }

    cin >> ret[n];

    int reflexive = 0;
    rep(x, 0, 1 << k) {
        int t = n;
        rep(i, 0, k) rep(j, 0, k)
            t = min(t, earliest_eval[i][j][bitat(x, i)][bitat(x, j)]);
        reflexive += ret[t];
    }

    cout << reflexive << ' ';

    int symmetric = 0;
    rep(x, 0, 1 << k) rep(y, 0, 1 << k) {
        int t1 = n, t2 = n;
        rep(i, 0, k) rep(j, 0, k) {
            t1 = min(t1, earliest_eval[i][j][bitat(x, i)][bitat(y, j)]);
            t2 = min(t2, earliest_eval[i][j][bitat(y, i)][bitat(x, j)]);
        }

        symmetric += (ret[t1] == 1 && ret[t2] == 1);
    }

    cout << symmetric << ' ';

    ll transitive = 0;

    vector<bs> is_good(1 << k);
    rep(x, 0, 1 << k) rep(y, 0, 1 << k) {
        int t = n;
        rep(i, 0, k) rep(j, 0, k)
            t = min(t, earliest_eval[i][j][bitat(x, i)][bitat(y, j)]);
        is_good[x][y] = ret[t];
    }

    rep(x, 0, 1 << k) rep(y, 0, 1 << k)
        if(is_good[x][y]) transitive += (~is_good[x] & is_good[y]).count();

    cout << transitive << '\n';

    return 0;
}