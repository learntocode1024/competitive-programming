#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
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

//#define MULTI
const int N = 8e5+5;
vector<int> g[N], ly[N];
int h, t, qu[N];
int v[N], c[N], c0[N];
int in[N], nxt[N<<1], f[N], tot;
int rk[N<<1];
int cnt;
bool visited[N];
int n;

void dfs1(int u, int fa) { // euler tour
  in[u] = ++tot;
  rk[tot] = u;
  f[u] = fa;
  int lst = tot;
  bool ok = 0;
  for (auto v : g[u]) {
    if (ok) {
      dfs1(v, u);
      ++tot;
      rk[tot] = u;
      nxt[lst] = tot;
      lst = tot;
    }
    if (fa == v) ok = 1;
  }
  for (auto v : g[u]) {
    if (fa == v) break;
    dfs1(v, u);
    ++tot;
    rk[tot] = u;
    nxt[lst] = tot;
    lst = tot;
  }
}

void dfs2(int u, int fa) {
  v[u] = cnt;
  ly[cnt].pb(u<<1); // partial
  for (auto v : g[u]) {
    if (fa == v) break;
    dfs2(v, u);
  }
  bool ok = 0;
  for (auto v : g[u]) {
    if (ok) {
      qu[++t] = v;
      ++c0[u]; // skip length
    }
    if (fa == v) ok = 1;
  }
}

tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> S;
pair<i64, int> qy[N];
int ans[N];

inline void solve() {
  int q;
  cin >> n >> q;
  FOR(i, 1, n + 1) {
    cin >> c[i];
    int r0;
    cin >> r0;
    FOR(j, 1, c[i]) {
      int r;
      cin >> r;
      g[i].pb(r);
    }
    g[i].pb(r0);
  }
  dfs1(1, 1);
  h = t = qu[1] = 1;
  while (h <= t) {
    if (v[f[qu[h]]] == cnt) {
      ++cnt;
    }
    if (!visited[f[qu[h]]]) ly[cnt].pb(f[qu[h]]<<1|1), visited[f[qu[h]]] = 1; // full
    dfs2(qu[h], f[qu[h]]);
    ++h;
  }
  FOR(i, 0, q) {
    i64 x;
    cin >> x;
    qy[i] = mkp(x, i);
  }
  sort(qy, qy + q);
  int cq = 0;
  i64 slen = 0;
  while (cq < q && qy[cq].fi == 0) ans[qy[cq++].se] = 1;
  FOR(i, 1, cnt + 1) {
    for (auto u : ly[i]) {
      if (u & 1) {
        for (int t = 0, id = nxt[in[u>>1]]; t < c0[u>>1]; ++t, id = nxt[id])
          S.insert(id);
      } else {
        for (int t = 0, id = in[u>>1]; id; id = nxt[id], ++t) {
          if (!t || t > c0[u>>1]) S.insert(id);
        }
      }
    }
    S.erase(1);
    i64 oldlen = slen;
    slen += S.size();
    while (cq < q && qy[cq].fi <= slen) {
      ans[qy[cq].se] = rk[*S.find_by_order(qy[cq].fi - oldlen - 1)];
      ++cq;
    }
  }
  for (int i = cq; i < q; ++i) {
    ans[qy[i].se] = rk[*S.find_by_order((qy[i].fi-slen-1)%(2*n-2))];
  }
  FOR(i, 0, q) println(ans[i]);
}

int main() {
#ifndef MISAKA
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
