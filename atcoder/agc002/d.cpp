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
#include <queue>
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
int n, m;

int u[N], v[N];
int x[N], y[N], z[N];
int ans[N];

struct ds {
  int l, r;
  vector<int> q;
};

struct DS {
  int f[N], sz[N];
  int _t = 1e8;
  int _get(int x) {
    if (f[x] == x) return x;
    return f[x] = _get(f[x]);
  }
  inline void _init() {
    FOR(i, 1, n + 1) f[i] = i, sz[i] = 1;
    _t = 0;
  }
  void move(int t) {
    if (t == _t) return;
    if (t < _t) _init();
    while (_t < t) {
      ++_t;
      int f1 = _get(u[_t]), f2 = _get(v[_t]);
      if (f1 != f2) {
        if (sz[f1] < sz[f2]) swap(f1, f2);
        f[f2] = f1;
        sz[f1] += sz[f2];
      }
    }
  }
  bool query(int i) {
    int f1 = _get(x[i]), f2 = _get(y[i]);
    if (f1 == f2 && sz[f1] < z[i]) return 0;
    if (f1 != f2 && sz[f1] + sz[f2] < z[i]) return 0;
    return 1;
  }
} T;
queue<ds> Q;
void solve() {
  n = rd(), m = rd();
  FOR(i, 1, m + 1) {
    u[i] = rd(), v[i] = rd();
  }
  ds t0;
  t0.l = 1, t0.r = m + 1;
  int q = rd();
  FOR(i, 0, q) {
    x[i] = rd(), y[i] = rd(), z[i] = rd();
    t0.q.pb(i);
  }
  Q.push(t0);
  while (!Q.empty()) {
    ds cur = Q.front();
    Q.pop();
    if (cur.r == cur.l + 1) {
      for (auto to : cur.q) {
        ans[to] = cur.l;
      }
      continue;
    }
    int mid = (cur.l + cur.r) >> 1;
    T.move(mid - 1);
    ds t1, t2;
    t1.l = cur.l;
    t1.r = t2.l = mid;
    t2.r = cur.r;
    for (auto id : cur.q) {
      if (T.query(id)) t1.q.pb(id);
      else t2.q.pb(id);
    }
    if (!t1.q.empty()) Q.push(t1);
    if (!t2.q.empty()) Q.push(t2);
  }
  FOR(i, 0, q) {
    cout << ans[i] << '\n';
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
