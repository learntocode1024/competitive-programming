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
#define eb emplace_back
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
const int N = 1000005;
const int B = 450, T = 200;
int n, m, k;
int a[N], disc[N];
int pref_all[N];
int maxa;

struct qry {
  int l, r, id;
  qry() = default;
  qry(int _l, int _r, int _id) {
    l = _l, r = _r, id = _id;
  }
  inline void init(int _i) {
    l = rd(), r = rd();
    id = _i;
  }
  bool operator< (const qry &rhs) const {
    return l / B == rhs.l / B ? r < rhs.r : l < rhs.l;
  }
} q[N];
vector<qry> g[N];
i64 ans[N];

namespace solve_divisor { // (a, a) included
int cnt[N];
void work() {
  for (int i = 1; i <= n; ++i) {
    pref_all[i] += cnt[a[i]];
    for (int k = 1; k * k <= a[i]; ++k) {
      if (a[i] % k == 0) {
        ++cnt[k];
        if (a[i] != k * k) ++cnt[a[i]/k];
      }
    }
    for (auto u : g[i]) {
      int to = u.id;
      if (u.l > 0) {
        for (int j = u.l; j <= u.r; ++j) {
          ans[to] += cnt[a[j]];
        }
      } else {
        for (int j = -u.l; j <= u.r; ++j) {
          ans[to] -= cnt[a[j]];
        }
      }
    }
  }
}

}

namespace solve_multiple { // (a, a) included
int cnt[N], vis[T+5];
int f[T+5][N];
void work() {
  for (int k = 1; k <= T; ++k) {
    for (int i = 1; i <= n; ++i) {
      f[k][i] = f[k][i-1];
      if (a[i] % k == 0) ++f[k][i];
    }
  } // part 2 (when a[i] <= T)
  for (int i = 1; i <= n; ++i) {
    pref_all[i] += cnt[a[i]];
    for (int k = 1; k <= T; ++k) {
      if (f[k][i] != f[k][i-1]) pref_all[i] += cnt[k];
    }
    if (a[i] > T) {
      for (int k = a[i]; k <= maxa; k += a[i]) {
        ++cnt[k];
      }
    } else {
      ++vis[a[i]];
    }
    for (auto u : g[i]) {
      int to = u.id;
      if (u.l > 0) {
        for (int j = u.l; j <= u.r; ++j) {
          ans[to] += cnt[a[j]];
        }
        for (int k = 1; k <= T; ++k) {
          ans[to] += 1ll * (f[k][u.r] - f[k][u.l-1]) * cnt[k];
        }
      } else {
        for (int j = -u.l; j <= u.r; ++j) {
          ans[to] -= cnt[a[j]];
        }
        for (int k = 1; k <= T; ++k) {
          ans[to] -= 1ll * (f[k][u.r] - f[k][-u.l-1]) * cnt[k];
        }
      }
    }
  }
}
}

void solve() {
  n = rd(), m = rd();
  FOR(i, 1, n + 1) a[i] = rd(), chkmax(maxa, a[i]);
  FOR(i, 0, m) q[i].init(i);
  sort(q, q + m);
  int l = 1, r = 0;
  FOR(i, 0, m) {
    if (l > q[i].l) g[r].eb(q[i].l, l - 1, i), l = q[i].l;
    if (r < q[i].r) g[l-1].eb(r + 1, q[i].r, i), r = q[i].r;
    if (l < q[i].l) g[r].eb(-l, q[i].l-1, i), l = q[i].l;
    if (r > q[i].r) g[l-1].eb(-q[i].r - 1, r, i), r = q[i].r;
  }
  solve_divisor::work();
  solve_multiple::work();
  l = 1, r = 0;
  FOR(i, 0, m) {
    while (l > q[i].l) --l, ans[i] -= pref_all[l];
    while (r < q[i].r) ++r, ans[i] += pref_all[r] + 1;
    while (l < q[i].l) ans[i] += pref_all[l], ++l;
    while (r > q[i].r) ans[i] -= pref_all[r] + 1, --r;
  }
  FOR(i, 1, m) {
    ans[i] += ans[i - 1];
  }
  FOR(i, 0, m) {
    cout << ans[q[i].id] - q[i].r + q[i].l - 1 << '\n';
  }
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

