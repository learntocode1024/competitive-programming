#include <bits/stdc++.h>
#include "modint"
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

const int N = 4e6+5;
const int MOD = 998244353;
typedef MontgomeryModInt<MOD> mint;
//#define MULTI
int n, x;
vector<pair<int, mint> > g[N];

namespace sub2 {
int d[N];
int dfs(int u, int fa) {
  d[u] = d[fa] + 1;
  int ret = u;
  for (auto v : g[u]) {
    if (v.fi != fa) {
      int to = dfs(v.fi, u);
      if (d[to] > d[ret]) ret = to;
    }
  }
  return ret;
}
inline void work() {
  d[0] = -1;
  int r = dfs(1, 0);
  println((d[dfs(r, 0)] <= x) ? 1 : 0);
}
}

int d[N], son[N];
mint prson[N], iprson[N];
const int MX = N<<1;
int id[MX], hd[MX], tl[MX], nxt[MX], pre[MX], l[MX], tot;
mint v[MX], tg[MX], itg[MX], s[MX];

void l_s_d(int u, int fa) {
  for (auto v : g[u]) if (v.fi != fa) {
    l_s_d(v.fi, u);
    if (v.se != 1) chkmax(d[u], d[v.fi] + 1);
    if (v.se != 1 && d[son[u]] < d[v.fi]) son[u] = v.fi, prson[u] = -v.se + 1;
  }
}

mint s1[N], s2[N];

void dfs(int u, int fa) {
  int &cur = id[u];
  mint iv;
  if (son[u] == 0) {
    cur = u;
    ++tot;
    hd[u] = tl[u] = tot;
    s[u] = tg[u] = itg[u] = v[tot] = 1;
    nxt[tot] = pre[tot] = 0;
    l[u] = 0;
  } else {
    dfs(son[u], u);
    cur = id[son[u]];
    mint tmp = s[cur] * (-prson[u] + 1);
    tg[cur] *= prson[u];
    itg[cur] *= iprson[u];
    s[cur] *= prson[u];
    s[cur] += tmp;
    iv = itg[cur];
    // iv = tg[cur].inverse();
    ++tot;
    v[tot] = iv * tmp;
    nxt[tot] = hd[cur];
    pre[hd[cur]] = tot;
    hd[cur] = tot;
    ++l[cur];
  }
  while (l[cur] > x) {
    --l[cur];
    s[cur] -= tg[cur] * v[tl[cur]];
    nxt[pre[tl[cur]]] = 0;
    tl[cur] = pre[tl[cur]];
  }
  for (auto oson : g[u]) if (oson.fi != fa && oson.fi != son[u]) {
    int V = oson.fi;
    mint p = oson.se;
    mint q = -p + 1;
    dfs(V, u);
    int e = l[id[V]];
    int lm1 = 0, lm2 = 0;
    int is2 = hd[cur], is1 = hd[id[V]];
    int it = hd[cur], itv = 0;
    for (int i = 0, it = hd[id[V]]; i <= e + 1; ++i, it = nxt[it]) s1[i] = tg[id[V]] * v[it];
    for (int i = 0, it = hd[cur]; i <= e + 1; ++i, it = nxt[it]) s2[i] = v[it];
    FOR(i, 1, e + 2) s1[i] += s1[i-1];
    FOR(i, 1, e + 2) s2[i] += s2[i-1];
    int i0;
    for (int i = 0; i <= l[cur]; ++i) {
      if (i - 1 > e && x - i - 1 > e) break;
      i0 = i;
        s[cur] -= tg[cur] * v[it];
        if (min(i-1, x-i-1) >= 0) v[it] = q * (v[it] * s1[min(i-1, x-i-1)] + tg[id[V]] * v[itv] * s2[min(i-1, x - i)]) + p * v[it] * s[id[V]];
        else if (min(i-1, x-i) >= 0) v[it] = q * (tg[id[V]] * v[itv] * s2[min(i-1, x - i)]) + p * v[it] * s[id[V]];
        else v[it] = p * v[it] * s[id[V]];
        s[cur] += tg[cur] * v[it];
      it = nxt[it];
      itv = (i == 0) ? hd[id[V]] : nxt[itv];
    }
    it = tl[cur], itv = (e == l[cur]) ? tl[id[V]] : 0;
    for (int i = l[cur]; i > i0; --i) {
      if (i - 1 > e && x - i - 1 > e) break;
        s[cur] -= tg[cur] * v[it];
        if (min(i-1, x-i-1) >= 0) v[it] = q * (v[it] * s1[min(i-1, x-i-1)] + tg[id[V]] * v[itv] * s2[min(i-1, x - i)]) + p * v[it] * s[id[V]];
        else if (min(i-1, x-i) >= 0) v[it] = q * (tg[id[V]] * v[itv] * s2[min(i-1, x - i)]) + p * v[it] * s[id[V]];
        else v[it] = p * v[it] * s[id[V]];
        s[cur] += tg[cur] * v[it];
      it = pre[it];
      itv = (i - 1 == e) ? tl[id[V]] : pre[itv];
    }
  }
}
mint prd[N];
inline void solve() {
  int da, db;
  rd(n, da, db);
  if (da <= db * 2) println(1);
  else {
    x = db << 1;
    bool t2 = 1;
    FOR(i, 1, n) {
      int u, v, w;
      rd(u, v, w);
      w = 61689804ll * w % MOD;
      if (w) t2 = 0;
      g[u].eb(v, w);
      g[v].eb(u, w);
    }
    if (t2) sub2::work();
    else {
      d[0] = -1;
      v[0] = 0;
      l_s_d(1, 0);
      mint prod(1);
      int tot = 0;
      prd[0] = 1;
      FOR(i, 1, n + 1) if (prson[i] != 0) prd[++tot] = (prod *= prson[i]);
      mint inv = prod.inverse();
      ROF(i, 1, n + 1) if (prson[i] != 0) {
        iprson[i] = inv * prd[--tot];
        inv *= prson[i];
      }
      dfs(1, 0);
      println(s[id[1]]);
    }
  }
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

