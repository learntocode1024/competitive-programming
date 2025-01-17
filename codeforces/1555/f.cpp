/**********************************************************************
 * This file is the c++ solution to a particular CP problem written by
 * misaka18931 and was hosted on GitHub Repository below:
 * URL: https://github.com/misaka18931/competitive-programming
 *
 * Original Author: misaka18931
 * Date: Jul 31, 2021
 * Algorithm: Euler_tour_trick, BIT, st_table
 * Difficulty: mid
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
using IO::read;
const int N = 300005, MX = 500005;
int n, q;
vector<pair<int, int> > G[N];

int a[MX], b[MX], c[MX], dep[MX], it[MX], ot[MX], f[20][MX], tot;
bool ans[MX];
bool w[20][MX];

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

void dfs(int u, int fa) {
  it[u] = ++tot;
  f[0][u] = fa;
  dep[u] = dep[fa] + 1;
  for (auto v : G[u]) {
    if (v.fi != fa) w[0][v.fi] = v.se, dfs(v.fi, u);
  }
  ot[u] = ++tot;
}

bool xs;
int lca(int u, int v) {
  xs = 0;
  if (dep[u] < dep[v]) swap(u, v);
  int x = dep[u] - dep[v];
  if (x) {
    for (int i = 19; i >= 0; --i) {
      if (x & (1 << i)) {
        xs ^= w[i][u];
        u = f[i][u];
      }
    }
  }
  if (u == v) return u;
  for (int i = 19; i >= 0; --i) {
    if (f[i][u] != f[i][v]) {
      xs ^= w[i][u] ^ w[i][v];
      u = f[i][u];
      v = f[i][v];
    }
  }
  xs ^= w[0][u] ^ w[0][v];
  return f[0][u];
}

int bit[MX];
void mod(int x, int v) {
  while (x <= n * 3) {
    bit[x] += v;
    x += x & -x;
  }
}

int get(int x) {
  int ret = 0;
  while (x) {
    ret += bit[x];
    x -= x & -x;
  }
  return ret;
}

bool tadd(int i) {
  int u = a[i], v = b[i];
  int x = lca(u, v);
  if (!xs ^ c[i]) return 0;
  if (get(it[u]) + get(it[v]) - 2 * get(it[x])) return 0;
  for (int i = u; i != x; i = f[0][i]) {
    mod(it[i], 1);
    mod(ot[i], -1);
  }
  for (int i = v; i != x; i = f[0][i]) {
    mod(it[i], 1);
    mod(ot[i], -1);
  }
  return 1;
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
  for (int i = 1; i <= n; ++i) {
    if (!f[0][i]) dfs(i, 0);
  }
  for (int i = 1; i < 20; ++i) {
    for (int j = i; j <= n; ++j) {
      f[i][j] = f[i - 1][f[i - 1][j]];
      w[i][j] = w[i - 1][j] ^ w[i - 1][f[i - 1][j]];
    }
  }
  for (int i = 0; i < q; ++i) {
    if (!ans[i]) {
      ans[i] = tadd(i);
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
