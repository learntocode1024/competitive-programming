/**********************************************************************
 * This file is the c++ solution to a particular CP problem written by
 * misaka18931 and was hosted on GitHub Repository below:
 * URL: https://github.com/misaka18931/competitive-programming
 *
 * Original Author: misaka18931
 * Date: Aug  4, 2021
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
#include <map>
#include <vector>
using namespace std;

/********************************** buffer IO *********************************/
namespace IO {
char in[1 << 23]; // sizeof in varied in problem
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

/********************************* macros *************************************/
typedef long long i64;
typedef unsigned long long u64;
typedef unsigned int u32;
#define pb(x) push_back(x)
#define fi first
#define se second
#define REP(x, y, z) for (int x = y; x < z; ++x) // always [y, z)
#define PER(x, y, z) for (int x = z - 1; x >= y; --x)
template <typename T> void chkmax(T &a, const T &b) { a = max(a, b); }
template <typename T> void chkmin(T &a, const T &b) { a = min(a, b); }

/*********************************** solution *********************************/
using IO::rd;
#define MX 200005
typedef pair<int, int> pii;
#define mkp make_pair
pii a[MX];
map<pii, bool> g;
int n;
bool type;
typedef bool (*fn)(int);
fn v[4];
fn p[4];
bool v0(int i) {
  return !g[mkp(a[i].fi - 1, a[i].se)] || !g[mkp(a[i].fi, a[i].se - 1)] || ! g[mkp(a[i].fi - 1, a[i].se - 1)];
}
bool v1(int i) {
  return !g[mkp(a[i].fi + 1, a[i].se)] || !g[mkp(a[i].fi, a[i].se - 1)] || ! g[mkp(a[i].fi + 1, a[i].se - 1)];
}
bool v2(int i) {
  return !g[mkp(a[i].fi - 1, a[i].se)] || !g[mkp(a[i].fi, a[i].se + 1)] || ! g[mkp(a[i].fi - 1, a[i].se + 1)];
}
bool v3(int i) {
  return !g[mkp(a[i].fi + 1, a[i].se)] || !g[mkp(a[i].fi, a[i].se + 1)] || ! g[mkp(a[i].fi + 1, a[i].se + 1)];
}
bool p0(int i) {
  if (!g[mkp(a[i].fi - 1, a[i].se)] || !g[mkp(a[i].fi, a[i].se - 1)] || ! g[mkp(a[i].fi - 1, a[i].se - 1)]) cout << i + 1 << ' ';
}
bool p1(int i) {
  if (!g[mkp(a[i].fi + 1, a[i].se)] || !g[mkp(a[i].fi, a[i].se - 1)] || ! g[mkp(a[i].fi + 1, a[i].se - 1)]) cout << i + 1 << ' ';
}
bool p2(int i) {
  if (!g[mkp(a[i].fi - 1, a[i].se)] || !g[mkp(a[i].fi, a[i].se + 1)] || ! g[mkp(a[i].fi - 1, a[i].se + 1)]) cout << i + 1 << ' ';
}
bool p3(int i) {
  if (!g[mkp(a[i].fi + 1, a[i].se)] || !g[mkp(a[i].fi, a[i].se + 1)] || ! g[mkp(a[i].fi + 1, a[i].se + 1)]) cout << i + 1 << ' ';
}


void solve() {
  n = rd();
  type = rd();
  for (int i = 0; i < n; ++i)
    a[i].fi = rd(), a[i].se = rd(), g[a[i]] = 1;
  int ans = n + 1, tp = -1;
  for (int t = 0; t < 4; ++t) {
    int cur = 0;
    for (int i = 0; i < n; ++i)
      cur += v[t](i);
    if (cur < ans) ans = cur, tp = t;
  }
  cout << ans << '\n';
  if (!type) return;
  for (int i = 0; i < n; ++i)
    p[tp](i);
  cout << '\n';
}

int main() {
  v[0] = v0;
  v[1] = v1;
  v[2] = v2;
  v[3] = v3;
  p[0] = p0;
  p[1] = p1;
  p[2] = p2;
  p[3] = p3;
  IO::init_in();
#ifdef MULTI
  int T = IO::rd();
  while (T--)
    solve(), T && (clear(), 1);
#else
  solve();
#endif
  return 0;
}

