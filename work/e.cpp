#include <bits/stdc++.h>
using namespace std;

int T(int u) {
    cout << "T " << u << endl;
#ifndef A
    cerr << "T " << u << endl;
#endif
    int x, y;
    cin >> x >> y;
    return y;
}

pair<int, int> W() {
    cout << 'W' << endl;
#ifndef A
    cerr << 'W' << endl;
#endif
    int x, y;
    cin >> x >> y;
    return {x,y};
}

void E(long long x) {
    cout << "E " << x << endl;
}

int a[114514];
const double p = 0.6;
const int K = 100;
const double B = 0.5, w = 12.5;
const double c = 0.4;
bool vis[114514];
mt19937 rng;
int n, k, u, d;
double ans1, ans2;
int c1, c2;
bool choose() {
  if (vis[u]) return true;
  double r = pow(p,1 + 1.0l*(d-1)/n*K);
  double cur = uniform_real_distribution<double>(0.0,1.0)(rng);
#ifndef A
  cerr << u <<  ' ' << d << ' ' << r << ' ' << cur << '\n';
#endif
  if (cur > r) return true;
  else return false;
};

void upd(int x) {
  if (x >= B* n) ans2 += x, ++c2;
  else ans1 += x, ++c1;
}

void solve() {
    cin >> n >> k >> u >> d;
    c1 = c2 = ans1 = ans2 = 0;
    for (int i = 1; i <= n; ++i) vis[i] = 0;
    iota(a,a+n,1);
    random_device rd;
    rng.seed(rd());
    shuffle(a,a+n,rng);
    upd(d);
    int cnt = 0;
    for (int i = 0; i < k; ++i) {
        int to = u;
        if (choose()) d = T(u = a[cnt++]);
        else {
          auto v = W();
          d = v.second;
          u = v.first;
        }
        vis[to] = 1;
        if (!vis[u]) upd(d);
#ifndef A
        cerr << "CUR " << ans1 << ' ' << ans2 << ' ' << u << '\n';
#endif
    }
    double mv;
    if (c1 > c2) mv = (ans1 * w + ans2) / (c1*w+c2);
    else mv = (ans2 * w + ans1) / (c2*w+c1);
    E(n * mv / 2);
}

int main() {
    int T;
    cin >> T;
    for (int i = 1; i <= T; ++i) {
        // cout << "Case #" << i << ": ";
        solve();
    }
}
