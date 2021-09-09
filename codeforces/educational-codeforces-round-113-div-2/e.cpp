/**********************************************************************
 * This file is the c++ solution to a particular CP problem written by
 * misaka18931 and was hosted on GitHub Repository below:
 * URL: https://github.com/misaka18931/competitive-programming
 *
 * Original Author: misaka18931
 * Date:
 * Algorithm:
 * Difficulty:
 *
 *********************************************************************/

#include <algorithm>
#include <cctype>
#include <climits>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
using namespace std;

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
int k;
i64 A, h, pA[32];
const i64 mod = 998244353;

namespace BF {
int p[64];
int rk[32];
void work() {
  int n = (1 << k), m = n - 1;
  for (int i = 0; i < (1 << m); ++i) {
    int c = n;
    for (int i = 0; i < n; ++i) p[i] = i + 1, rk[i + 1] = 0;
    for (int j = 0; j < m * 2; j += 2) {
      p[c] = p[j + ((i >> (j / 2)) & 1)];
      ++c;
    }
    int cnt = 0, cp = 1;
    for (int j = c - 1; j >= 0; --j) {
      if (!rk[p[j]]) {
        ++cnt;
        rk[p[j]] = cp;
        if (__builtin_popcount(cnt) == 1) cp = cnt + 1;
      }
    }
    i64 ch = 0;
    for (int i = 1; i <= n; ++i) {
      ch = (ch + i * pA[rk[i]]) % mod;
    }
    if (ch == h) {
      for (int i = 1; i <= n; ++i) {
        cout << rk[i] << ' ';
      }
      cout << '\n';
      return;
    }
  }
  cout << "-1\n";
}
}

namespace semiBF {
int p[64];
int rk[1 << 16][32];
i64 fh[1 << 16], gh[1 << 16], f1h[1 << 16], g1h[1 << 16];
int nxt[32];
void init() {
  int n = 16, m = n - 1;
  for (int i = 0; i < (1 << m); ++i) {
    int c = n;
    for (int i = 0; i < n; ++i) p[i] = i + 1;
    for (int j = 0; j < m * 2; j += 2) {
      p[c] = p[j + ((i >> (j / 2)) & 1)];
      ++c;
    }
    int cnt = 0, cp = 1;
    for (int j = c - 1; j >= 0; --j) {
      if (!rk[i][p[j]]) {
        ++cnt;
        rk[i][p[j]] = cp;
        if (__builtin_popcount(cnt) == 1) cp = cnt + 1;
      }
    }
    for (int j = 1; j <= n; ++j) {
      // cerr << nxt[rk[i][j]] << ' ';
      if (rk[i][j] == 1) {
        fh[i] = (fh[i] + j * pA[1]) % mod;
        gh[i] = (gh[i] + (j + 16) * pA[2]) % mod;
        f1h[i] = (f1h[i] + j * pA[2]) % mod;
        g1h[i] = (g1h[i] + (j + 16) * pA[1]) % mod;
      } else {
        fh[i] = (fh[i] + j * pA[nxt[rk[i][j]]]) % mod;
        gh[i] = (gh[i] + (j + 16) * pA[nxt[rk[i][j]]]) % mod;
        f1h[i] = (f1h[i] + j * pA[nxt[rk[i][j]]]) % mod;
        g1h[i] = (g1h[i] + (j + 16) * pA[nxt[rk[i][j]]]) % mod;
      }
    }
    // cerr << '\n';
  }
}

unordered_map<i64, int> m1, m2;

void work() {
  nxt[2] = 3;
  nxt[3] = 5;
  nxt[5] = 9;
  nxt[9] = 17;
  init();
  for (int i = 0; i < 1 << 15; ++i) {
    m1[fh[i]] = i;
    m2[f1h[i]] = i;
  }
  for (int i = 0; i < 1 << 15; ++i) {
    i64 x = h - gh[i] + mod;
    if (x >= mod) x -= mod;
    if (m1.find(x) != m1.end()) {
      nxt[1] = 1;
      int xx = m1[x];
      for (int j = 1; j <= 16; ++j) cout << nxt[rk[xx][j]] << ' ';
      nxt[1] = 2;
      for (int j = 1; j <= 16; ++j) cout << nxt[rk[i][j]] << ' ';
      return;
    }
    i64 y = h - g1h[i] + mod;
    if (y >= mod) y -= mod;
    if (m2.find(y) != m2.end()) {
      nxt[1] = 2;
      int yy = m2[y];
      for (int j = 1; j <= 16; ++j) cout << nxt[rk[yy][j]] << ' ';
      nxt[1] = 1;
      for (int j = 1; j <= 16; ++j) cout << nxt[rk[i][j]] << ' ';
      return;
    }
  }
  puts("-1");
}
}

void solve() {
  scanf("%d%lld%lld", &k, &A, &h);
  pA[0] = 1;
  for (int i = 1; i < 32; ++i) pA[i] = pA[i - 1] * A % mod;
  if (k <= 4) {
    BF::work();
  } else {
    semiBF::work();
  }
}

int main() {
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
