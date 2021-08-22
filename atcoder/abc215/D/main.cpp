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
char in[1 << 24]; // sizeof in varied in problem
char const *o;
void init_in() {
  o = in;
  in[fread(in, 1, sizeof(in) - 4, stdin)] = 0; // set 0 at the end of buffer.
}
int rd() {
  unsigned u = 0, s = 0;
  while (*o && *o <= 32)
    ++o; // skip whitespaces...
  if (*o == '-')
    s = ~s, ++o;
  else if (*o == '+')
    ++o; // skip sign
  while (*o >= '0' && *o <= '9')
    u = (u << 3) + (u << 1) + (*o++ - '0'); // u * 10 = u * 8 + u * 2 :)
  return static_cast<int>((u ^ s) + !!s);
}
char *rdstr(char *s) {
  while (*o && *o <= 32)
    ++o;
  while (*o > 32)
    *s++ = *o++;
  return s;
}
} // namespace IO

/********************************* utility ************************************/
typedef long long i64;
typedef unsigned long long u64;
typedef unsigned int u32;
typedef pair<int, int> pii;
#define pb(x) push_back(x)
#define mkp(x, y) make_pair(x, y)
#define fi first
#define se second
#define FOR(x, y, z) for (int x = y; x < z; ++x) // always [y, z)
#define ROF(x, y, z) for (int x = z - 1; x >= y; --x)
template <typename T> void chkmax(T &a, const T &b) { a = max(a, b); }
template <typename T> void chkmin(T &a, const T &b) { a = min(a, b); }
pii operator+(const pii &a, const pii &b) {
  return mkp(a.fi + b.fi, a.se + b.se);
}
// clang-format off
// clang-format on

/*********************************** solution *********************************/
using IO::rd;
#define MX 100055
int p[MX], low[MX], cnt;
int f[MX], ff[MX];
void work() {
  for (int i = 2; i < MX; ++i) {
    if (!low[i]) p[cnt++] = i, low[i] = i;
    for (int j = 0; p[j] * i < MX; ++j) {
      low[i * p[j]] = p[j];
      if (p[j] == low[i]) break;
    }
  }
}

void solve() {
  work();
  int n = rd(), m = rd();
  for (int i = 0; i < n; ++i) {
    int a = rd();
    int aa = a;
    for (int j = 0; p[j] * p[j] <= aa && j < cnt; ++j) {
      while (a % p[j] == 0) a /= p[j], f[p[j]] = 1;
    }
    if (a > 1) f[a] = 1;
  }
  for (int i = 2; i <= m; ++i) {
    if (f[i] == 1) {
      for (int j = i; j <= m; j += i) ff[j] = 1;
    }
  }
  int ans = 0;
  for (int i = 1; i <= m; ++i) {
    if (!ff[i]) ++ans;
  }
  cout << ans << '\n';
  for (int i = 1; i <= m; ++i) {
    if (!ff[i]) cout << i << '\n';
  }
}

int main() {
  IO::init_in();
#ifdef MULTI
  int T = IO::rd();
  while (T--)
    solve();
#else
  solve();
#endif
  return 0;
}
