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
using int128 = __int128_t;

int main() {
    cin.tie(0) -> sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    
    int n;
    ll p; 
    cin >> n >> p;
    vector<ll> a(n);
    rep(i, 0, n) cin >> a[i];

    if(a[0] > p) {
        cout << 0 << '\n';
        return 0;
    }

    int128 sum = a[0];
    rep(i, 1, n) {
        if(sum + (a[i]-1) * (int128)(i+1) >= p) {
            cout << i << '\n';
            return 0;
        }
        sum += a[i];
    }

    cout << n << '\n';

    return 0;
}