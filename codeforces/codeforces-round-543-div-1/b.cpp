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
const int N = 1e5+5;
char a[N], b[N];
int c[N], d[N];

struct qry {
  int i, dt;
  qry() = default;
  qry(int _i, int _dt) : i(_i), dt(_dt) {};
} ans[N<<2], s[N<<2];
int tot, t1;

void solve() {
  int n = rd();
  IO::rdstr(a);
  IO::rdstr(b);
  FOR(i, 0, n) a[i] -= '0', b[i] -= '0', d[i] = a[i];
  int _ans = 0;
  FOR(i, 0, n - 1) c[i] = b[i] - a[i], a[i + 1] += c[i], _ans += abs(c[i]);
  if (a[n - 1] != b[n - 1]) {
    puts("-1");
    return;
  }
  for (int i = 0; i < n - 1; ++i) {
    if (c[i] != 0 && ((d[i] == 9 && d[i + 1] == 0) || (d[i] == 0 && d[i + 1] == 9))) {
      puts("-1");
      return;
    }
  }
  cout << _ans << '\n';
  for (int i = 0; i < n - 1; ++i) {
    if (d[i + 1] + c[i] < 10 && d[i + 1] + c[i] >= 0) {
      ans[t1++] = qry(i + 1, c[i]);
    } else if (d[i + 1] + c[i] >= 10) {
      ans[t1++] = qry(i + 1, 9 - d[i + 1]);
      s[tot++] = qry(i + 1, d[i + 1] + c[i] - 9);
    } else {
      ans[t1++] = qry(i + 1, d[i + 1]);
      s[tot++] = qry(i + 1, c[i] - d[i + 1]);
    }
  }
  int o = 1e5;
  for (int i = 0; i < t1 && o; ++i) {
    int f = 1;
    if (ans[i].dt < 0) f = -1;
    while (ans[i].dt != 0 && o) {
      cout << ans[i].i << ' ' << f << '\n';
      ans[i].dt -= f;
      --o;
    }
  }
  reverse(s, s + tot);
  for (int i = 0; i < tot && o; ++i) {
    int f = 1;
    if (s[i].dt < 0) f = -1;
    while (s[i].dt != 0 && o) {
      cout << s[i].i << ' ' << f << '\n';
      s[i].dt -= f;
      --o;
    }
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
