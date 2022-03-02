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
pii a[200005];
int n;

bool valid(int k) {
  int t = 0;
  int mn = 1e9, mx = 0;
  int x;
  do {
    x = a[t].fi;
    chkmin(mn, a[t].se);
    chkmax(mx, a[t].se);
    ++t;
  } while (a[t].fi == a[t - 1].fi);
  for (int p = t; p < n; ++p) {
    if (a[p].fi - x < k) continue;
    while (a[p].fi - a[t].fi >= k) {
      do {
        x = a[t].fi;
        chkmin(mn, a[t].se);
        chkmax(mx, a[t].se);
        ++t;
      } while (a[t].fi == a[t - 1].fi);
    }
    if (mx >= a[p].se + k) return 1;
    if (mn <= a[p].se - k) return 1;
  }
  return 0;
}

void solve() {
  n = rd();
  FOR(i, 0, n) a[i].fi = rd(), a[i].se = rd();
  sort(a, a + n);
  int l = 0, r = 1e9;
  while (r > l) {
    int mid = l + (r - l) / 2;
    if (valid(mid))
      l = mid + 1;
    else
      r = mid;
  }
  cout << max(l - 1, 0) << '\n';
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
