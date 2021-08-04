/**********************************************************************
 * This file is the c++ solution to a particular CP problem written by
 * misaka18931 and was hosted on GitHub Repository below:
 * URL: https://github.com/misaka18931/competitive-programming
 *
 * Original Author: misaka18931
 * Date: Aug  4, 2021
 * Algorithm: bruteforce, heuristic-algorithm，amortized-analysis
 * Difficulty: easy
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
#define MX 3005
int h, w;
char s[MX][MX];
int lst[MX];
int d[MX][MX];
vector<int> G[MX];

inline int sqr(int x) {
  return x * x;
}

void solve() {
  h = rd(), w = rd();
  for (int i = 0; i < h; ++i) {
    IO::rdstr(s[i]);
  }
  REP(i, 0, h)
    G[i].pb(-1);
  REP(i, 0, h)
    REP(j, 0, w)
      if (s[i][j] == '1')
        d[i][j] = INT_MAX, G[i].pb(j);
  REP(i, 0, h)
    G[i].pb(w);
  REP(i, 0, w)
    lst[i] = -1;
  REP(i, 0, h) {
    auto &g = G[i];
    REP(k, 1, g.size() - 1) {
      if (g[k - 1] != -1) chkmin(d[i][g[k]], sqr(g[k] - g[k - 1]));
      if (g[k + 1] != w) chkmin(d[i][g[k]], sqr(g[k + 1] - g[k]));
      REP(j, g[k - 1] + 1, g[k + 1]) {
        if (lst[j] != -1) chkmin(d[i][g[k]], sqr(g[k] - j) + sqr(lst[j] - i));
      }
    }
    REP(k, 1, g.size() - 1) {
      if (s[i][g[k]] == '1')
        lst[g[k]] = i;
    }
  }
  REP(i, 0, w)
    lst[i] = -1;
  PER(i, 0, h) {
    auto &g = G[i];
    REP(k, 1, g.size() - 1) {
      if (g[k - 1] != -1) chkmin(d[i][g[k]], sqr(g[k] - g[k - 1]));
      if (g[k + 1] != w) chkmin(d[i][g[k]], sqr(g[k + 1] - g[k]));
      REP(j, g[k - 1] + 1, g[k + 1]) {
        if (lst[j] != -1) chkmin(d[i][g[k]], sqr(g[k] - j) + sqr(lst[j] - i));
      }
    }
    REP(k, 1, g.size() - 1) {
      if (s[i][g[k]] == '1')
        lst[g[k]] = i;
    }
  }
  i64 ans = 0;
  REP(i, 0, h)
    REP(j, 0, w)
      ans += d[i][j];
  cout << ans << '\n';
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

