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
typedef pair<int, int> pii;
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

#define MULTI
const int N = 3e5+5;
vector<int> g[N];
int a[N];
int n, m;
int pre[N<<1], nxt[N<<1];
int va[N], vc[N], cc, ca;
int ida[N], idc[N];
int ord[N], tmp[N];
int tot = 0, st[N<<1];

inline void del(int x) {
  st[tot++] = x;
  if (nxt[x]) pre[nxt[x]] = pre[x];
  if (pre[x]) nxt[pre[x]] = nxt[x];
}

inline void rev() {
  ROF(i, 0, tot) {
    int &x = st[i];
    if (nxt[x]) pre[nxt[x]] = x;
    if (pre[x]) nxt[pre[x]] = x;
  }
  tot = 0;
}

inline void solve() {
  cin >> n >> m;
  i64 ans = 0;
  FOR(i, 1, n + 1) cin >> a[i];
  FOR(i, 1, n + 1) g[i].clear();
  FOR(i, 1, n + 1) va[i] = a[i];
  FOR(i, 0, n*2+10) pre[i] = nxt[i] = 0;
  sort(va + 1, va + n + 1);
  ca = unique(va + 1, va + n + 1) - va - 1;
  FOR(i, 1, n + 1) ida[i] = lower_bound(va + 1, va + ca + 1, a[i]) - va;
  FOR(i, 1, n + 1) tmp[i] = 0;
  FOR(i, 1, n + 1) ++tmp[ida[i]];
  cc = 0;
  FOR(i, 1, ca + 1) vc[++cc] = tmp[i];
  sort(vc + 1, vc + cc + 1);
  cc = unique(vc + 1, vc + cc + 1) - vc - 1;
  FOR(i, 1, ca + 1) idc[i] = lower_bound(vc + 1, vc + cc + 1, tmp[i]) - vc;
  iota(ord, ord + ca, 1);
  sort(ord, ord + ca, [] (int i, int j) { return idc[i] != idc[j] ? idc[i] < idc[j] : i < j; });
  FOR(i, 1, ca) {
    if (idc[ord[i-1]] == idc[ord[i]]) {
      pre[ord[i]] = ord[i-1];
      nxt[ord[i-1]] = ord[i];
    }
  }
  FOR(i, 0, ca) {
    if (i != ca - 1 && idc[ord[i+1]] == idc[ord[i]]) {
      pre[ord[i+1]] = ord[i];
      nxt[ord[i]] = ord[i+1];
    } else {
      int u = idc[ord[i]] + n;
      pre[u] = ord[i];
      nxt[ord[i]] = u;
    }
  }
  FOR(i, 0, m) {
    int u, v;
    rd(u, v);
    u = lower_bound(va + 1, va + ca + 1, u) - va;
    v = lower_bound(va + 1, va + ca + 1, v) - va;
    g[u].pb(v);
    g[v].pb(u);
  }
  FOR(i, 1, ca + 1) {
    del(i);
    for (auto x : g[i]) del(x);
    FOR(j, 1, cc + 1) {
      if (pre[j+n]) {
        i64 cur = 1ll * (vc[j] + tmp[i]) * (va[i] + va[pre[j+n]]);
        chkmax(ans, cur);
      }
    }
    rev();
  }
  println(ans);
}

int main() {
#ifndef MISAKA
  //freopen(".in", "r", stdin);
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

