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
#include <list>
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
#define x first
#define y second
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
  return mkp(a.x + b.x, a.y + b.y);
}

/*********************************** solution *********************************/
using IO::rd;
// #define MULTI
const int N = 1005;

inline i64 ccw(i64 _x, i64 _y, i64 _z, i64 _w) {
  return _x * _w - _y * _z;
}

struct seg {
  pii a, b;
  seg() = default;
  seg(pii _a, pii _b) { a = _a, b = _b; };
  bool cross(const seg &rhs) {
    i64 m = ccw(b.x - a.x, b.y - a.y, rhs.a.x - a.x, rhs.a.y - a.y);
    i64 n = ccw(b.x - a.x, b.y - a.y, rhs.b.x - b.x, rhs.b.y - b.y);
    return (m > 0 && n < 0) || (m < 0 && n > 0);
  }
};

seg a[N * N];
pii p[N];

inline bool cross(seg aa, seg bb) {
  return aa.cross(bb) && bb.cross(aa);
}

void solve() {
  int n = rd();
  FOR(i, 0, n) {
    int x = rd(), y = rd();
    p[i] = mkp(x, y);
  }
  int tot = 0;
  FOR(i, 0, n) {
    FOR(j, i + 1, n) {
      a[tot++] = seg(p[i], p[j]);
    }
  }
  int cnt = 0;
  for (int i = 0; i < tot; ++i) {
    bool yes = 1;
    for (int j = 0; j < tot && yes; ++j) {
      if (j == i) continue;
      yes = yes && !cross(a[j], a[i]);
    }
    if (yes) ++cnt;
  }
  cout << cnt << '\n';
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
