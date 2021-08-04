/**********************************************************************
 * This file is the c++ solution to a particular CP problem written by
 * misaka18931 and was hosted on GitHub Repository below:
 * URL: https://github.com/misaka18931/competitive-programming
 *
 * Original Author: misaka18931
 * Date: Jul 13, 2021
 * Source: ZROI simulation contests for NOI2021
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
typedef long long LL;
typedef unsigned long long ULL;
const LL mod = 1e9 + 7;
#define printb(x)                                                              \
  if ((bool)x)                                                                 \
    printf("YES");                                                             \
  else                                                                         \
    printf("NO");
#define pb(x) push_back(x)
#define pf(x) push_front(x)
#define MX 500005

/*** */
namespace IO {
char in[1 << 21]; // sizeof in varied in problem
char const *o;

void init_in() {
  o = in;
  in[fread(in, 1, sizeof(in) - 4, stdin)] = 0; // set 0 at the end of buffer.
}

int readInt() {
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
} // namespace IO
/* */

int a[MX];
vector<int> G[MX];
int n;
int vis[MX];
int dp[MX];

void dfs1(int u) {
  vis[u] = a[u];
  int a(0), b(0);
  for (auto v : G[u]) {
    if (vis[v])
      continue;
    dfs1(v);
    if (vis[v] > a) {
      b = a;
      a = vis[v];
    } else
      b = max(b, vis[v]);
  }
  vis[u] = max(vis[u], b);
}

void dfs2(int u) {
  dp[u] = a[u];
  int a(0), b(0);
  for (auto v : G[u]) {
    if (dp[v]) {
      if (dp[v] > a) {
        b = a;
        a = dp[v];
      } else
        b = max(b, dp[v]);
    } else {
      if (vis[v] > a) {
        b = a;
        a = vis[v];
      } else
        b = max(b, vis[v]);
    }
  }
  dp[u] = max(dp[u], b);
  for (auto v : G[u]) {
    if (!dp[v])
      dfs2(v);
  }
}

void solve() {
  n = IO::readInt();
  for (int i = 1; i <= n; ++i)
    a[i] = IO::readInt();
  for (int i = 1; i < n; ++i) {
    int u = IO::readInt(), v = IO::readInt();
    G[u].push_back(v);
    G[v].push_back(u);
  }
  dfs1(1);
  dp[1] = vis[1];
  dfs2(1);
  for (int i = 1; i <= n; ++i) {
    int ans = a[i];
    for (auto v : G[i])
      ans = max(ans, dp[v]);
    cout << ans << ' ';
  }
}

int main() {
  IO::init_in();
  int T = 1;
  while (T--)
    solve();
  return 0;
}
