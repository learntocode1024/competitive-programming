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

struct seg {
  pii a, b;
  seg() = default;
  seg(pii _a, pii _b) { a = _a, b = _b; };
};

seg a[N * N];
pii p[N];

bool cross(seg aa, seg bb) {
  pii a = aa.a, b = aa.b, c = bb.a, d = bb.b;
  if(min(a.x,b.x)<=max(c.x,d.x) && min(c.y,d.y)<=max(a.y,b.y)&&min(c.x,d.x)<=max(a.x,b.x) && min(a.y,b.y)<=max(c.y,d.y)) {
    i64 u, v, w, z;
    u=1ll*(c.x-a.x)*(b.y-a.y)-1ll*(b.x-a.x)*(c.y-a.y);
    v=1ll*(d.x-a.x)*(b.y-a.y)-1ll*(b.x-a.x)*(d.y-a.y);
    w=1ll*(a.x-c.x)*(d.y-c.y)-1ll*(d.x-c.x)*(a.y-c.y);
    z=1ll*(b.x-c.x)*(d.y-c.y)-1ll*(d.x-c.x)*(b.y-c.y);
    return (u * v < 0 && w * z < 0);
  }
  return false;
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
    for (int j = 0; j < tot; ++j) {
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
