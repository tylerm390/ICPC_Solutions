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

const int max_n = 40;
const int max_n2 = 400;
const int max_k = 2500;

int n, k;
string s;

bitset<max_k> seen[max_n][max_n][max_n2];

bool calc(int idx, int ns, int nas, int nacs) {
    if(idx == n) return nacs == k;
    if(seen[idx][ns][nas][nacs]) return false;
    seen[idx][ns][nas][nacs] = 1;

    if(nacs > k) return false;

    if(s[idx] == 'N') return calc(idx+1, ns+1, nas, nacs);
    if(s[idx] == 'A') return calc(idx+1, ns, nas+ns, nacs);
    if(s[idx] == 'C') return calc(idx+1, ns, nas, nacs+nas);
    if(s[idx] != '?') return calc(idx+1, ns, nas, nacs);

    for(char c: "NACX") {
        s[idx] = c;

        bool good;
        if(c == 'N') good = calc(idx+1, ns+1, nas, nacs);
        else if(c == 'A') good = calc(idx+1, ns, nas+ns, nacs);
        else if(c == 'C') good = calc(idx+1, ns, nas, nacs+nas);
        else good = calc(idx+1, ns, nas, nacs);

        if(good) return true;

        s[idx] = '?';
    }

    return false;
}

int main() {
    cin.tie(0) -> sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    
    cin >> n >> k >> s;

    if(calc(0, 0, 0, 0)) cout << s << '\n';
    else cout << -1 << '\n';

    return 0;
}