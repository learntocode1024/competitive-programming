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
const int N = 1e6+5;
int n;
i64 ans = 0;
int r[N], r1[N], c[N << 1];

inline void calc1() {
  int i = 0;
  int cnt = 0;
  if (!c[n]) cnt = 1;
  for (; i < n; i += 2) {
    if (i) {
      if (!c[n - i]) ++cnt;
      if (!c[n + i]) ++cnt;
    }
    if (!r[n - i]) ans += cnt;
  }
  if (i == n + 1) {
    if (!c[2 * n - 1]) --cnt;
    if (!c[1]) --cnt;
    i = n - 3;
  } else {
    i -= 2;
  }
  for (; i >= 0; i -= 2) {
    if (!r1[n - i]) ans += cnt;
    if (!c[n - i]) --cnt;
    if (!c[n + i]) --cnt;
  }
}

inline void calc2() {
  int i = 1;
  int cnt = 0;
  for (; i < n; i += 2) {
    if (!c[n - i]) ++cnt;
    if (!c[n + i]) ++cnt;
    if (!r[n - i]) ans += cnt;
  }
  if (i == n + 1) {
    if (!c[2 * n - 1]) --cnt;
    if (!c[1]) --cnt;
    i = n - 3;
  } else {
    i -= 2;
  }
  for (; i >= 0; i -= 2) {
    if (!r1[n - i]) ans += cnt;
    if (!c[n - i]) --cnt;
    if (!c[n + i]) --cnt;
  }
}

void solve() {
  n = rd();
  int m = rd();
  FOR(i, 0, m) {
    int x = rd(), y = rd();
    int id = n - x + y;
    c[id] = 1;
    if (x + y <= n + 1) {
      r[n + 2 - x - y] = 1;
    } else {
      r1[x + y - n] = 1;
    }
  }
  calc1();
  calc2();
  cout << ans << '\n';
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
