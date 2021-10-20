/**********************************************************************
 * This file is the c++ solution to a particular CP problem written by
 * misaka18931 and was hosted on GitHub Repository below:
 * URL: https://github.com/misaka18931/competitive-programming
 *
 * Original Author: misaka18931
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
namespace IO {
char in[1 << 24];  // sizeof in varied in problem
char const *o;
void init_in() {
  o = in;
  in[fread(in, 1, sizeof(in) - 4, stdin)] = 0;  // set 0 at the end of buffer.
}
int rd() {
  unsigned u = 0, s = 0;
  while (*o && *o <= 32) ++o;  // skip whitespaces...
  if (*o == '-')
    s = ~s, ++o;
  else if (*o == '+')
    ++o;  // skip sign
  while (*o >= '0' && *o <= '9')
    u = (u << 3) + (u << 1) + (*o++ - '0');  // u * 10 = u * 8 + u * 2 :)
  return static_cast<int>((u ^ s) + !!s);
}
char *rdstr(char *s) {
  while (*o && *o <= 32) ++o;
  while (*o > 32) *s++ = *o++;
  *s = '\0';
  return s;
}
}  // namespace IO

/********************************* utility ************************************/
typedef long long i64;
typedef unsigned long long u64;
typedef unsigned int u32;
typedef pair<int, int> pii;
#define pb(x) push_back(x)
#define mkp(x, y) make_pair(x, y)
#define fi first
#define se second
#define FOR(x, y, z) for (int x = y; x < z; ++x)  // always [y, z)
#define ROF(x, y, z) for (int x = z - 1; x >= y; --x)
template <typename T>
void chkmax(T &a, const T &b) {
  a = max(a, b);
}
template <typename T>
void chkmin(T &a, const T &b) {
  a = min(a, b);
}
pii operator+(const pii &a, const pii &b) {
  return mkp(a.fi + b.fi, a.se + b.se);
}

/*********************************** solution *********************************/
using IO::rd;
// #define MULTI
const int N = 2e6+5;
int n, m;
int a[N], b[N];

namespace sub1 {
int c[N];
inline void work() {
  FOR(i, 0, 1 << m) {
    FOR(i, 1, n + 1) c[i] = 0;
    FOR(k, 0, m) {
      if ((i >> k) & 1) {
        ++c[a[k]];
        ++c[b[k]];
      } else {
        --c[a[k]];
        --c[b[k]];
      }
    }
    bool ok = 1;
    FOR(i, 1, n + 1) if (abs(c[i]) > 1) ok = 0;
    if (ok) {
      FOR(k, 0, m) {
        cout << ((i >> k) & 1) << ' ';
      }
      return;
    }
  }
  puts("-1");
}
}

namespace sub2 {
vector<pii> g[N];
bool ans[N];
bool rev[N];
int exc[N];

void dfs(int u, int fa) {
  int s1 = (g[u].size() - 1) / 2;
  int c1 = 0;
  for (auto v : g[u]) {
    if (v.fi != fa) {
      dfs(v.fi, u);
      if (exc[v.fi] == -1) {
        if (s1) {
          --s1;
          ++exc[u];
          ans[v.se] = 1;
        } else {
          rev[v.fi] = 1;
          ans[v.se] = 0;
          --exc[u];
        }
      }
    }
  }
  for (auto v : g[u]) {
    if (v.fi != fa) {
      if (exc[v.fi] == 0) {
        if (s1) {
          --s1;
          ++exc[u];
          ans[v.se] = 1;
        } else {
          ans[v.se] = 0;
          --exc[u];
        }
      }
    }
  }
  for (auto v : g[u]) {
    if (v.fi != fa) {
      if (exc[v.fi] == 1) {
        if (s1) {
          --s1;
          ++exc[u];
          rev[v.fi] = 1;
          ans[v.se] = 1;
        } else {
          ans[v.se] = 0;
          --exc[u];
        }
      }
    }
  }
}

void dfs2(int u, int fa) {
  if (rev[u]) {
    for (auto v : g[u]) {
      ans[v.se] ^= 1;
      rev[v.fi] ^= 1;
    }
  }
  for (auto v : g[u]) {
    if (v.fi != fa) {
      dfs2(v.fi, u);
    }
  }
}

inline void work() {
  FOR(i, 0, m) {
    g[a[i]].emplace_back(b[i], i);
    g[b[i]].emplace_back(a[i], i);
  }
  dfs(1, 0);
  dfs2(1, 0);
  FOR(i, 0, m) {
    cout << ans[i] << ' ';
  }
}
}

namespace sub3 {
int deg[N], ecnt[N], ev[N], etot;
vector<pii> g[N];
bool ans[N], vis[N], ve[N];

void dfs(int u) {
  ev[u] = etot;
  for (auto v : g[u]) {
    if (ev[v.fi] == 0 && !ve[v.se]) {
      dfs(v.fi);
    }
  }
}

void dfs2(int u, int col) {
  vis[u] = 1;
  for (auto v : g[u]) {
    if (!ve[v.se]) {
      ans[v.se] = col;
      ve[v.se] = 1;
      dfs2(v.fi, col ^ 1);
    }
  }
}

int x;
bool dfs3(int u, int col) {
  vis[u] = 1;
  for (auto v : g[u]) {
    if (!ve[v.se]) {
      ans[v.se] = col;
      ve[v.se] = 1;
      dfs2(v.fi, col ^ 1);
    }
  }
  return 0;
}

inline void work() {
  FOR(i, 0, m) ++deg[a[i]], ++deg[b[i]], g[a[i]].emplace_back(b[i], i), g[b[i]].emplace_back(a[i], i);
  bool ok = 1;
  FOR(i, 1, n + 1) {
    if (deg[i] & 1) {
      x = i;
      if (!dfs3(i, 0)) {
        puts("-1");
        return;
      }
    }
  }
  FOR(i, 1, n + 1) {
    if (!ev[i]) {
      ++etot;
      dfs(i);
    }
  }
  FOR(i, 0, m) {
    ++ecnt[ev[a[i]]];
  }
  FOR(i, 1, etot + 1) {
    if (ecnt[i] & 1) {
      puts("-1");
      return;
    }
  }
  FOR(i, 1, n + 1) {
    if (!vis[i]) dfs2(i, 0);
  }
  FOR(i, 0, m) {
    cout << ans[i] << ' ';
  }
}
}

void solve() {
  n = rd(), m = rd();
  FOR(i, 0, m) {
    a[i] = rd(), b[i] = rd();
  }
  if (m <= 20) sub1::work();
  else if (m == n - 1) sub2::work();
  else sub3::work();
}

int main() {
  IO::init_in();
#ifdef MULTI
  int T = IO::rd();
  while (T--) solve();
#else
  solve();
#endif
  return 0;
}
/*
 * checklist:
 * - IO buffer size
 * - potential out-of-bound Errors
 * - inappropriate variable type
 * - potential Arithmetic Error
 * - potential Arithmetic Overflow
 * - typo / logical flaws
 * - clean-up on multiple test cases
 * - sufficient stress tests / random data tests
*/
