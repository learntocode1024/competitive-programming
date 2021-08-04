/**********************************************************************
 * This file is the c++ solution to a particular CP problem written by
 * misaka18931 and was hosted on GitHub Repository below:
 * URL: https://github.com/misaka18931/competitive-programming
 *
 * Original Author: misaka18931
 * Date: Aug  3, 2021
 * Algorithm: SAM, HLD, offline-2D-quries
 * Difficulty: mid
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
vector<int> G[MX << 1];
int n, q, N;

namespace sam {
int len[MX << 1], nxt[26][MX << 1], f[MX << 1];
int lst, tot;
void expand(char ch) {
  int cur = ++tot;
  len[cur] = len[lst] + 1;
  int p = lst;
  for (; p != -1 && !nxt[ch][p]; p = f[p]) {
    nxt[ch][p] = cur;
  }
  if (p == -1) {
    f[cur] = 0;
  } else {
    int q = nxt[ch][p];
    if (len[q] == len[p] + 1) {
      f[cur] = q;
    } else {
      int mir = ++tot;
      for (int i = 0; i < 26; ++i)
        nxt[i][mir] = nxt[i][q];
      len[mir] = len[p] + 1;
      f[mir] = f[q];
      f[q] = f[cur] = mir;
      for (; p != -1 && nxt[ch][p] == q; p = f[p]) {
        nxt[ch][p] = mir;
      }
    }
  }
  lst = cur;
}
void init(char *s) {
  f[0] = -1;
  while (*s)
    expand(*s++ - 'a');
  N = tot + 1;
}
} // namespace sam

namespace hld {
int sz[MX], son[MX], dep[MX], rnk[MX], dfn[MX], top[MX], tot;
int (&fa)[] = sam::f;
void dfs1(int u, int fa) {
  sz[u] = 1;
  hld::fa[u] = fa;
  if (fa != -1) dep[u] = dep[fa] + 1;
  son[u] = 0;
  for (auto v : G[u]) {
    dfs1(v, u);
    sz[u] += sz[v];
    if (sz[v] > sz[son[u]]) son[u] = v;
  }
}

void dfs2(int u, int top) {
  hld::top[u] = top;
  dfn[u] = ++tot;
  rnk[tot] = u;
  if (son[u]) dfs2(son[u], top);
  for (auto v : G[u]) {
    if (dfn[v]) continue;
    dfs2(v, v);
  }
}
void init() {
  dfs1(0, -1);
  dfs2(0, 0);
}
} // namespace hld

char s[MX];
void solve() {
  n = IO::rdstr(s) - s;
  sam::init(s);
  hld::init();
  q = rd();

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

