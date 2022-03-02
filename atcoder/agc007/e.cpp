#include <bits/stdc++.h>
using namespace std;
template<typename T>
void rd(T &a) {
  cin >> a;
}
template<typename A, typename... B>
void rd(A &a, B& ...b) {
  cin >> a;
  rd(b...);
}
template<typename A>
void print(const A& a) {
  cout << a;
}
template<typename A, typename... B>
void print(const A& a, const B& ...b) {
  cout << a;
  print(b...);
}
template<typename A>
void println(const A& a) {
  cout << a << '\n';
}
template<typename A, typename... B>
void println(const A& a, const B& ...b) {
  cout << a << ' ';
  println(b...);
}
typedef long long i64;
typedef unsigned long long u64;
typedef unsigned u32;
typedef pair<i64, i64> pii;
#define mkp make_pair
#define fi first
#define se second
#define pb push_back
#define eb emplace_back
#define FOR(i, j, k) for (int i = (j); i < (k); ++i)
#define ROF(i, j, k) for (int i = ((k) - 1); i >= j; --i)
template<typename T>
inline void chkmin(T &a, const T b) {
  a = min(a, b);
}
template<typename T>
inline void chkmax(T &a, const T b) {
  a = max(a, b);
}

//#define MULTI
const int N = 1.5e5;
int n;
vector<pii> g[N];
int ch[N][2];
int s[N];
i64 mid;
vector<pii> f[N];

void pre(int u, int fa) {
  int t = 0;
  for (auto [v, w] : g[u]) if (v != fa) {
    s[v] = w;
    ch[u][t++] = v;
    pre(v, u);
  }
  if (!t) 
     f[u].eb(s[u], s[u]);
}


void dfs(int u) {
  if (!ch[u][0]) {
    return;
  }
  f[u].clear();
  dfs(ch[u][0]);dfs(ch[u][1]);
  vector<pii> &ret = f[u];
  const vector<pii> &a = f[ch[u][0]], &b = f[ch[u][1]];
  int t = 0, t1 = 0;
  int l = a.size(), r = b.size();
  vector<pii> tmp;
  for (int i = 0, c = -1; i < l; ++i) {
    while (c + 1 < r && b[c+1].fi + a[i].se <= mid) ++c;
    if (c != -1) tmp.eb(a[i].fi + s[u], b[c].se + s[u]);
  }
  int s1 = tmp.size();
  for (int i = 0, c = -1; i < r; ++i) {
    while (c + 1 < l && a[c+1].fi + b[i].se <= mid) ++c;
    if (c != -1) tmp.eb(b[i].fi + s[u], a[c].se + s[u]);
  }
  inplace_merge(begin(tmp), begin(tmp) + s1, end(tmp));
  for(int i=0;i<tmp.size();++i){
    if(!f[u].empty() && f[u].back().se<=tmp[i].se) continue;
    f[u].pb(tmp[i]);
  }
  return;
}

inline void solve() {
  cin >> n;
  bool ans_eq_zero = 1;
  FOR(i, 2, n + 1) {
    int a, v;
    cin >> a >> v;
    if (v) ans_eq_zero = 0;
    g[i].eb(a, v);
    g[a].eb(i, v);
  }
  if (ans_eq_zero) {
    println(0);
    return;
  }
  pre(1, 0);
  i64 l = 0, r = 1e11;
  while (r > l + 1) {
    mid = (l + r) >> 1;
    dfs(1);
    if (f[1].empty()) l = mid;
    else r = mid;
  }
  println(r);
}

int main() {
#ifndef MISAKA
  //freopen("044.txt", "r", stdin);
  //freopen(".out", "w", stdout);
  ios::sync_with_stdio(0);
  cin.tie(0);
#endif
#ifdef MULTI
  int T;
  cin >> T;
  while (T--)
#endif
  solve();
  return 0;
}
/* Checklist:
 * - data type
 * - overflow
 * - typo/logic
 * - special cases
 * - cleanup (multi-test)
 * - bounds
 * - memory usage
 * - file IO
 */

