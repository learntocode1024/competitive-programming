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
int n, m;
vector<int> G[MX];
struct edge {
  int u, v, w;
  inline void init() {
    u = rd(), v = rd(), w = rd();
    G[u].pb(v);
    G[v].pb(u);
  }
  bool operator< (const edge &b) const {
    return w < b.w;
  }
} E[MX];
int fa[MX];
int get(int x) {
  if (fa[x] == x) return x;
  fa[x] = get(fa[x]);
  return fa[x];
}

void solve() {
  n = rd();
  m = rd();
  int k = rd();
  for (int i = 0; i < m; ++i) E[i].init();
  sort(E, E + m);
  i64 ans = 0;
  for (int i = 1; i <= n; ++i) fa[i] = i;
  for (int i = 0; i < m; ++i) {
    if (get(E[i].u) != get(E[i].v)) {
      fa[get(E[i].u)] = get(E[i].v);
      ans += max(0, E[i].w - k);
    }
  }
  if (ans == 0) {
    edge tmp;
    tmp.w = k;
    auto it = lower_bound(E, E + m, tmp);
    if (it == E + m) ans = k - E[m - 1].w;
    else
    ans = min(k - (it - 1)->w, it->w - k);
  }
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
