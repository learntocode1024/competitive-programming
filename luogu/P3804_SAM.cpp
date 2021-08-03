/**********************************************************************
 * This file is the c++ solution to a particular CP problem written by
 * misaka18931 and was hosted on GitHub Repository below:
 * URL: https://github.com/misaka18931/competitive-programming
 *
 * Original Author: misaka18931
 * Date: Aug  3, 2021
 * Algorithm: SAM
 * Difficulty: template
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
#define MX 1000005
int n;
char s[MX];

namespace sam {
int len[MX << 1], nxt[26][MX << 1], f[MX << 1], dp[MX << 1];
vector<int> G[MX * 2];
int lst, tot;
void init() {
  f[0] = -1;
}
void expand(char ch) {
  int cur = ++tot;
  len[cur] = len[lst] + 1;
  dp[cur] = 1;
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
i64 ans;
void dfs(int u) {
  for (auto v : G[u]) {
    dfs(v);
    dp[u] += dp[v];
  }
  if (dp[u] > 1) chkmax(ans, 1ll * dp[u] * len[u]);
}
i64 work() {
  for (int i = 1; i <= tot; ++i) {
    G[f[i]].pb(i);
  }
  dfs(0);
  cerr << tot << endl;
  return ans;
}
} // sam

void solve() {
  n = IO::rdstr(s) - s;
  sam::init();
  for (int i = 0; i < n; ++i)
    sam::expand(s[i] - 'a');
  cout << sam::work() << '\n';
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

