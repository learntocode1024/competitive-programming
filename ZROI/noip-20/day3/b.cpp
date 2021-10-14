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
const int N = 1e5+5;
vector<int> f[N];
const int B = 100, BT = N / B + 5;
int n, m, maxa;
int blk[N], L[N], R[N];
int a[N];
int c[BT];
int miu[N], low[N], pri[N], lt[N], tot;

inline void build() {
  miu[1] = 1;
  lt[1] = 1;
  for (int i = 2; i <= 100000; ++i) {
    if (low[i] == 0) {
      low[i] = pri[tot++] = i;
      miu[i] = -1;
      lt[i] = 1;
    }
    for (int j = 0; j < tot && pri[j] * i <= 100000; ++j) {
      int to = pri[j] * i;
      low[to] = pri[j];
      if (pri[j] == low[i]) {
        miu[to] = 0;
        lt[to] = lt[i];
        break;
      } else {
        miu[to] = -miu[i];
        lt[to] = i;
      }
    }
  }
  for (int i = 1; i <= 100000; ++i) {
    for (int j = i; j <= 100000; j += i) {
      f[j].pb(i);
    }
  }
}

int ans[N];
int cnt[N];
vector<pii> q[N];

inline void work() {
  FOR(i, 1, n + 1) {
    for (auto v : f[a[i]]) {
      ++cnt[v];
    }
    for (auto t : q[i]) {
      int sg = 1;
      int x;
      if (t.fi < 0) x = -t.fi, sg = -1;
      else x = t.fi;
      for (auto v : f[x]) {
        ans[t.se] += sg * miu[v] * cnt[v];
      }
    }
  }
}

void solve() {
  n = rd(), m = rd();
  FOR(i, 1, n + 1) a[i] = rd(), chkmax(maxa, a[i]);
  build();
  FOR(i, 0, m) {
    int l = rd(), r = rd(), x = rd();
    q[r].emplace_back(x, i);
    q[l - 1].emplace_back(-x, i);
  }
  work();
  FOR(i, 0, m) cout << ans[i] << '\n';
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
