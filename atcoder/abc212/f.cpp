/**********************************************************************
 * This file is the c++ solution to a particular CP problem written by
 * misaka18931 and was hosted on GitHub Repository below:
 * URL: https://github.com/misaka18931/competitive-programming
 *
 * Original Author: misaka18931
 * Date: Aug  1, 2021
 * Algorithm: ST-table
 * Difficulty: mid, remind
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
char in[1 << 26]; // sizeof in varied in problem
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
template <typename T> void chkmin(T &a, const T &b) { a = min(a, b); }

/*********************************** solution *********************************/
using IO::read;
#define MX 100005
int n, m, q;

struct bus {
  int s, t, to, id;
  bus(int x, int y, int z, int w) : s(x), t(y), to(z), id(w) {}
  bool operator<(int x) const { return s < x; }
  bool operator<(const bus &x) const { return s < x.s; }
};

vector<bus> G[MX];
int u[MX], v[MX], s[MX], t[MX];
int st[MX][20];

void solve() {
  n = read(), m = read(), q = read();
  for (int i = 1; i <= m; ++i) {
    u[i] = read(), v[i] = read(), s[i] = read(), t[i] = read();
    G[u[i]].emplace_back(s[i], t[i], v[i], i);
  }
  for (int i = 1; i <= n; ++i) {
    sort(begin(G[i]), end(G[i]));
  }
  for (int i = 1; i <= m; ++i) {
    if (!G[v[i]].empty()) {
      auto ret = lower_bound(begin(G[v[i]]), end(G[v[i]]), t[i]);
      if (ret != G[v[i]].end())
        st[i][0] = ret->id;
    }
  }
  for (int i = 1; i < 20; ++i) {
    for (int j = 1; j <= m; ++j) {
      st[j][i] = st[st[j][i - 1]][i - 1];
    }
  }
  s[0] = 0x3f3f3f3f;
  while (q--) {
    i64 x = read(), y = read(), z = read();
    swap(x, y);
    int a = 0;
    if (!G[x].empty()) {
      auto ret = lower_bound(begin(G[x]), end(G[x]), y);
      if (ret != G[x].end())
        a = ret->id;
    } // Caution!!! Manual validation over NIL value required!
    if (s[a] >= z) {
      cout << x << '\n';
      continue;
    }
    for (int i = 19; i >= 0; --i) {
      if (s[st[a][i]] < z)
        a = st[a][i];
    }
    if (t[a] < z)
      cout << v[a] << '\n';
    else
      cout << u[a] << ' ' << v[a] << '\n';
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
