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
int n;
int a[MX];

namespace sub2 {
int cnt[MX], cntr[MX], s, sr;
void solve() {
  i64 ans = 0;
  for (int l = 1; l < n; ++l) {
    int la, ra;
    for (int i = 0; i <= n; ++i) cnt[i] = cntr[i] = 0;
    if (a[l] == a[l + 1]) la = l, ra = l + 1, cnt[a[l]] = 2, cntr[a[l]] = 1, s = sr = 1;
    else la = l + 1, ra = l, cnt[a[l]] = cnt[a[l + 1]] = cntr[a[l]] = cntr[a[l + 1]] = 1, s = sr = 2;
    for (int r = l + 1; r <= n; ++r) {
      if (ra > la) ans += ra - la;
      if (!cnt[a[r + 1]]) {
        la = r + 1;
        ++s, ++sr;
      }
      ++cnt[a[r + 1]];
      ++cntr[a[r + 1]];
      while (cntr[a[ra]] > 1) {
        --cntr[a[ra]];
        ++ra;
      }
    }
  }
  cout << ans << '\n';
}
}

namespace sol {
void solve() {

}
}

void solve() {
  n = rd();
  for (int i = 1; i <= n; ++i)
    a[i] = rd();
  if (n <= 2000) {
    sub2::solve();
  } else sol::solve(); 
}

int main() {
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

