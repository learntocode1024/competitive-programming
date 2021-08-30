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
#define MULTI

int a[100005];

void solve() {
  int n = rd();
  for (int i = 1; i <= n; ++i) a[i] = rd() & 1;
  int c1 = 0, c2 = 0;
  vector<int> a1, a2;
  FOR(i, 1, n + 1) if (a[i] == 0) a1.pb(i), c1 += a[i] == 0;
  FOR(i, 1, n + 1) if (a[i] == 1) a2.pb(i), c2 += a[i] == 1;
  i64 ans = 0;
  if (n & 1) {
    if (abs(c1 - c2) != 1) {
      cout << "-1\n";
      return;
    }
    if (c1 > c2) {
      for (int i = 1; i <= n; i += 2) {
        ans += abs(i - a1[i / 2]);
      }
    } else {
      for (int i = 1; i <= n; i += 2) {
        ans += abs(i - a2[i / 2]);
      }
    }
  } else {
    if (c1 != c2) {
      cout << "-1\n";
      return;
    }
    i64 ans1 = 0;
    for (int i = 1; i <= n; i += 2) {
      ans1 += abs(i - a1[i / 2]);
    }
    for (int i = 1; i <= n; i += 2) {
      ans += abs(i - a2[i / 2]);
    }
    chkmin(ans, ans1);
  }
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
