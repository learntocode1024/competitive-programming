/**********************************************************************
 * This file is the c++ solution to a particular CP problem written by
 * misaka18931 and was hosted on GitHub Repository below:
 * URL: https://github.com/misaka18931/competitive-programming
 *
 * Original Author: misaka18931
 * Date: Aug  6, 2021
 * Algorithm: 
 * Difficulty:
 *
 *********************************************************************/

#include <algorithm>
#include <bitset>
#include <cctype>
#include <climits>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
#include <string>
#include <vector>
using namespace std;

/********************************** buffer IO *********************************/
namespace IO {
char in[1 << 24]; // sizeof in varied in problem
char const *o;

void init_in() {
  o = in;
  in[fread(in, 1, sizeof(in) - 4, stdin)] = 0; // set 0 at the end of buffer.
}

int rd() {
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

char *rdstr(char *s) {
  while (*o && *o <= 32)
    ++o;
  while (*o > 32)
    *s++ = *o++;
  return s;
}
} // namespace IO

/********************************* macros *************************************/
typedef long long i64;
typedef unsigned long long u64;
typedef unsigned int u32;
typedef pair<int, int> pii;
#define mkp(x, y) make_pair(x, y)
#define pb(x) push_back(x)
#define fi first
#define se second
#define REP(x, y, z) for (int x = y; x < z; ++x) // always [y, z)
#define PER(x, y, z) for (int x = z - 1; x >= y; --x)
template <typename T> void chkmax(T &a, const T &b) { a = max(a, b); }
template <typename T> void chkmin(T &a, const T &b) { a = min(a, b); }

/*********************************** solution *********************************/
using IO::rd;
#define MX 505
bool a[MX][MX], b[MX][MX];
int n, m, q, xs, ys;
pii s;

namespace pt70 {
pii pre[MX][MX];
int dist[MX][MX], ddist[MX][MX];
pii operator+(pii a, pii b) {
  return mkp(a.fi + b.fi, a.se + b.se);
}
#define dis(x) dist[x.fi][x.se]
#define dd(x) ddist[x.fi][x.se]
#define pre(x) pre[x.fi][x.se]
pii dif[4] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

bool valid(pii u, pii v) {
  if (v.fi > n || !v.fi) return 0;
  if (v.se > m || !v.se) return 0;
  if (u > v) swap(u, v);
  if (u.fi == v.fi) {
    return !a[u.fi][u.se];
  } else {
    return !b[u.fi][u.se];
  }
}

inline void block(pii u, pii v) {
  if (u > v) swap(u, v);
  if (u.fi == v.fi) {
    a[u.fi][u.se] ^= 1;
  } else {
    b[u.fi][u.se] ^= 1;
  }
}

inline void ban(pii u) {
  while (u != s) {
    block(u, pre(u));
    u = pre(u);
  }
}

void bfs_init(pii u) {
  queue<pii> Q;
  Q.push(u);
  dis(u) = 0;
  while (!Q.empty()) {
    pii u = Q.front(); Q.pop();
    for (int i = 0; i < 4; ++i) {
      pii v = u + dif[i];
      if (valid(u, v) && dis(v) > dis(u) + 1) {
        dis(v) = dis(u) + 1;
        pre(v) = u;
        Q.push(v);
      }
    }
  }
}

bool bfs(pii u) {
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      ddist[i][j] = 100000000;
    }
  }
  queue<pii> Q;
  Q.push(u);
  dd(u) = 0;
  while (!Q.empty()) {
    pii u = Q.front(); Q.pop();
    for (int i = 0; i < 4; ++i) {
      pii v = u + dif[i];
      if (valid(u, v) && dd(v) > dd(u) + 1) {
        dd(v) = dd(u) + 1;
        Q.push(v);
      }
    }
  }
  return dis(u) < dd(s);
}

void solve() {
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      dist[i][j] = 100000000;
    }
  }
  bfs_init(s);
  for (int i = 0, x, y; i < q; ++i) {
    x = rd(), y = rd();
    pii u = mkp(x, y);
    if (dis(u) == 100000000) {
      puts("0");
      continue;
    }
    ban(u);
    cout << bfs(u) << '\n';
    ban(u);
  }
}
}

void solve() {
  n = rd(), m = rd();
  int k1 = rd(), k2 = rd();
  for (int i = 0, x, y; i < k1; ++i) {
    x = rd(), y = rd();
    a[x][y] = 1;
  }
  for (int i = 0, x, y; i < k2; ++i) {
    x = rd(), y = rd();
    b[x][y] = 1;
  }
  xs = rd(), ys = rd();
  s = mkp(xs, ys);
  q = rd();
  if (!k1 && !k2) {
    if (n > 1 && m > 1) {
      while (q--)
        puts("0");
    } else {
    while (q--)
      puts("1");
    }
  } else  {
    pt70::solve();
  }
}

int main() {
  IO::init_in();
#ifdef MULTI
  int T = IO::rd();
  while (T--)
    solve(), T && (clear(), 1);
#else
  solve();
#endif
  return 0;
}
 