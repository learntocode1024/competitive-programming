/**********************************************************************
 * This file is the c++ solution to a particular CP problem written by
 * misaka18931 and was hosted on GitHub Repository below:
 * URL: https://github.com/misaka18931/competitive-programming
 *
 * Original Author: misaka18931
 * Date: Jul 31, 2021
 * Algorithm: HLD, 
 * Difficulty:
 *
 *********************************************************************/

#include <algorithm>
#include <cctype>
#include <climits>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

/********************************** buffer IO *********************************/
#ifdef MASSIVE_INPUT
namespace IO {
template <int size> struct io {
  char ibuf[size], obuf[size];
  char *o, *o1, *p, *p1;
  io() : o(ibuf), o1(ibuf), p(obuf), p1(obuf + size){};
  ~io() { fwrite(obuf, 1, p - obuf, stdout); }
  inline char gc() {
    return o == o1 && (o1 = (o = ibuf) + fread(ibuf, 1, size, stdin)), *o++;
  };
  inline void pc(char ch) {
    p == p1 &&fwrite(obuf, 1, p - obuf, stdout) && (p = obuf), *p++ = ch;
  }
};
io<1 << 20> f;
inline int read() {
  int x = 0, u = 1;
  char ch = f.gc();
  while (ch < '0' || ch > '9') {
    if (ch == '-')
      u = -1;
    ch = f.gc();
  }
  while (ch >= '0' && ch <= '9') {
    x = (x << 1) + (x << 3) + ch - '0';
    ch = f.gc();
  }
  return x * u;
}
} // namespace IO
#else
namespace IO {
char in[1 << 23]; // sizeof in varied in problem
char const *o;

void init_in() {
  o = in;
  in[fread(in, 1, sizeof(in) - 4, stdin)] = 0; // set 0 at the end of buffer.
}

int read() {
  unsigned u = 0, s = 0;

  while (*o && *o <= 32)
    ++o; // skip whitespaces...

  if (*o == '-')
    s = ~s, ++o;
  else if (*o == '+')
    ++o; // skip sign

  while (*o >= '0' && *o <= '9')
    u = (u << 3) + (u << 1) + (*o++ - '0'); // u * 10 = u * 8 + u * 2 :)

  return static_cast<int>((u ^ s) + !!s);
}
} // namespace IO
#endif

/********************************* macros *************************************/
typedef long long i64;
typedef unsigned long long u64;
typedef unsigned int u32;
#define pb(x) push_back(x)
#define fi first
#define se second
#define REP(x, y, z) for (int x = y; x < z; ++x) // always [y, z)
#define PER(x, y, z) for (int x = z - 1; x >= y; --x)
template <typename T> void chkmax(T &a, const T &b) { a = max(a, b); }
template <typename T> void chkmin(T &a, const T &b) { b = min(a, b); }

/*********************************** solution *********************************/
using IO::read();
const int N = 300005, MX = 500005;
int n, q;
vector<pair<int, int> > G[N];

int a[MX], b[MX], c[MX];
bool ans[MX];

namespace seg {
struct node {
  int cnt;
  bool tg;
} a[N << 2];
inline void down(int p) {
  if (a[p].tg) {
    a[p << 1].tg = a[(p << 1) + 1].tg = 1;
  }
}
inline void up(int p) {
  a[p].cnt = a[p << 1].cnt + a[(p << 1) + 1].cnt;
}
bool valid(int p, int l, int r, int s, int t) {
  if (l == s && r == t)
    return a[p].tg ^ 1;
  int mid = l + (r - l) / 2;
  down(p);
  if (s < mid && !valid(p << 1, l, mid, s, min(mid, t))) return 0;
  if (t > mid && !valid((p << 1) + 1, mid, r, max(s, mid), t)) return 0;
  return 1;
}
int cnt(int p, int l, int r, int s, int t) {
  if (l == s && r == t)
    return a[p].cnt;
  int mid = l + (r - l) / 2;
  down(p);
  int ret = 0;
  if (s < mid) ret += cnt(p << 1, l, mid, s, min(mid, t));
  if (t > mid) ret += cnt((p << 1) + 1, mid, r, max(s, mid), t);
  return ret;
}
bool A[N];
void build(int p, int l, int r) {
  if (r - l == 1) {
    cnt[l] = A[l];
    return;
  }
  int mid = l + (r - l) / 2;
  build(p << 1, l, mid);
  build((p << 1) + 1, mid, r);
  up(p);
}
void mask(int p, int l, int r, int s, int t) {
  if (l == s && r == t) {
    a[p].tg = 1;
    return;
  }
  int mid = l + (r - l) / 2;
  down(p);
  if (s < mid) mask(p << 1, l, mid, s, min(mid, t));
  if (t > mid) mask((p << 1) + 1, mid, r, max(s, mid), t);
}
}

namespace hld {
int fa[N], son[N], sz[N], top[N], dfn[N], rnk[N], dep[N], tot;
int s[N];
void dfs1(int u) {
  sz[u] = 1;
  for (auto v : G[u]) {
    if (!sz[v.fi]) {
      dep[v.fi] = dep[u] + 1;
      s[v.fi] = v.se;
      dfs1(v.fi);
      sz[u] += sz[v];
      if (sz[son[u]] < sz[v.fi]) son[u] = v.fi;
    } else fa[u] = v.fi;
  }
}
void dfs2(int u, int t) {
  dfn[u] = ++tot;
  rnk[tot] = u;
  top[u] = t;
  if (son[u])
    dfs2(son[u], u);
  for (auto v : G[u]) {
    if (v.fi == fa[u] || v.fi == son[u]) continue;
    dfs2(v.fi, v.fi);
  }
}
void init() {
  for (int i = 1; i <= n; ++i) {
    if (!sz[i]) dfs1(i);
  }
  for (int i = 1; i <= n; ++i) {
    if (!dfn[i]) dfs2(i, i);
  }
}
void set(int a, int b) {
  while (top[a] != top[b]) {
    if (dep[top[a]] < dep[top[b]]) swap(a, b);
    seg::mask(dfn[top[a]] - 1, dfn[a], col);
    a = fa[top[a]];
  }
  if (dep[a] < dep[b]) swap(a, b);
  seg::mask(dfn[b] - 1, dfn[a], col);
}
int path(int a, int b) {
  int ret = 0;
  while (top[a] != top[b]) {
    if (dep[top[a]] < dep[top[b]]) swap(a, b);
    ret += seg::get(dfn[top[a]], dfn[a]);
    a = fa[top[a]];
  }
  if (dep[a] < dep[b]) swap(a, b);
  ret += seg::get(dfn[b], dfn[a], col);
}
void set(int a, int b, int col) {
  while (top[a] != top[b]) {
    if (dep[top[a]] < dep[top[b]]) swap(a, b);
    SEG::renew(dfn[top[a]] - 1, dfn[a], col);
    a = fa[top[a]];
  }
  if (dep[a] < dep[b]) swap(a, b);
  SEG::renew(dfn[b] - 1, dfn[a], col);
}
}

namespace dsu {
int fa[N];
void init() {
  for (int i = 1; i <= n; ++i) {
    fa[i] = i;
  }
}
int get(int x) {
  if (fa[x] == x) return x;
  fa[x] = get(fa[x]);
  return fa[x];
}
bool tadd(int i) {
  if (get(a[i]) == get(b[i]))
    return 0;
  fa[get(a[i])] = get(b[i]);
  G[a[i]].emplace_back(b[i], c[i]);
  G[b[i]].emplace_back(a[i], c[i]);
  return 1;
}
}

void solve() {
  n = read();
  q = read();
  dsu::init();
  for (int i = 0; i < q; ++i) {
    a[i] = read();
    b[i] = read();
    c[i] = read();
    ans[i] = dsu::tadd(i);
  }
  hld::init();
  for (int i = 0; i < q; ++i) {
    if (!ans[i]) {
      ans[i] = hld::tadd(i);
    }
  }
  for (int i = 0; i < q; ++i) {
    if (ans[i]) cout << "Yes\n";
    else cout << "No\n";
  }
}

int main() {
#ifndef MASSIVE_INPUT
  IO::init_in();
#endif
#ifdef MULTI
  int T = IO::read();
  while (T--)
    solve(), T &&clear();
#else
  solve();
#endif
  return 0;
}
