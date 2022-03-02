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
const int N = 5e5+5;

int A[N], p[N];
int n, k;
struct DS {
  int a[N<<2];
  inline void up(int p) {
    a[p] = (A[a[p<<1]] > A[a[p<<1|1]]) ? a[p<<1] : a[p<<1|1];
  }
  int Max(int p, int l, int r, int s, int t) {
    if (l == s && r == t) {
      return a[p];
    }
    int mid = (l + r) >> 1;
    int ret = 0;
    if (s < mid) {int x = Max(p<<1, l, mid, s, min(mid, t)); ret = (A[x] > A[ret]) ? x : ret;}
    if (t > mid) {int x = Max(p<<1|1, mid, r, max(s, mid), t); ret = (A[x] > A[ret]) ? x : ret;}
    return ret;
  }
  void mod(int p, int l, int r, int t) {
    if (r - l == 1) {
      a[p] = 0;
      return;
    }
    int mid = (l + r) >> 1;
    if (t < mid) mod(p<<1, l, mid, t);
    else mod(p<<1|1, mid, r, t);
    up(p);
  }
  void build(int p, int l, int r) {
    if (r - l == 1) {
      a[p] = l;
      return;
    }
    int mid = (l + r) >> 1;
    build(p<<1, l, mid);
    build(p<<1|1, mid, r);
    up(p);
  }
} T;

inline bool ismax(int x) {
  return (!p[x] && T.Max(1, 1, n + 1, max(1, x - k + 1), min(n + 1, x + k)) == x);
}
void solve() {
  n = rd(), k = rd();
  FOR(i, 1, n + 1) A[i] = rd();
  T.build(1, 1, n + 1);
  priority_queue<int> pq;
  for (int i = 1; i <= n; ++i) {
    if (ismax(i)) pq.push(i);
  }
  int t = n;
  while (!pq.empty()) {
    int u = pq.top();
    pq.pop();
    p[u] = t--;
    T.mod(1, 1, n + 1, u);
    int l = max(1, u - k + 1), r = u;
    if (l < r) {
      int v = T.Max(1, 1, n + 1, l, r);
      if (ismax(v)) pq.push(v);
    }
    l = u + 1, r = min(n + 1, u + k);
    if (l < r) {
      int v = T.Max(1, 1, n + 1, l, r);
      if (ismax(v)) pq.push(v);
    }
  }
  FOR(i, 1, n + 1) cout << p[i] << '\n';
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
