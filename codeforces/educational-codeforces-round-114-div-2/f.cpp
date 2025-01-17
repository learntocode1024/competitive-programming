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
char in[1 << 26];  // sizeof in varied in problem
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
  *s = '\0';
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
// #define MULTI
const int N = 300005;
int vis[N], vvis[N], dfn[N], t[N], in[N], cnt[N], low, tot;
vector<int> G[N];
int n, m, k;

bool dfs(int u) {
  dfn[u] = ++tot;
  if (G[u].empty() && in[u] < 2) return true;
  int v = G[u][0];
  if (dfn[v]) return false;
  return dfs(v);
}

void solve() {
  n = rd(), m = rd(), k = rd();
  int sp = k;
  FOR(i, 0, n) {
    int c = rd();
    bool valid = 1;
    FOR(j, 0, c) {
      t[j] = rd();
      if (vis[t[j]] == i + 1) {
        valid = 0;
      }
      vis[t[j]] = i + 1;
    }
    if (valid) {
      FOR(j, 0, c) {
        if (!vvis[t[j]]) --sp;
        vvis[t[j]] = 1;
        if (j) {
          G[t[j - 1]].pb(t[j]);
        }
      }
    } else {
      FOR(j, 0, c) dfn[t[j]] = 1;
    }
  }
  FOR(i, 1, k + 1) {
    sort(begin(G[i]), end(G[i]));
    G[i].erase(unique(G[i].begin(), G[i].end()), G[i].end());
    for (auto v : G[i]) {
      ++in[v];
    }
  }
  FOR(i, 1, k + 1)
    if (G[i].size() > 1 || in[i] > 1) dfn[i] = 1;
  tot = 1;
  vector<int> con;
  FOR(i, 1, k + 1) {
    if (!dfn[i] && in[i] == 0) {
      low = tot;
      if (dfs(i)) {
        ++cnt[tot - low];
        con.pb(tot - low);
      }
    }
  }
  sort(begin(con), end(con));
  con.erase(unique(con.begin(), con.end()), con.end());
  static int dp[N];
  const int mod = 998244353;
  dp[0] = 1;
  FOR(i, 1, m + 1) {
    for (auto l : con) {
      if (l > i) break;
      dp[i] = (dp[i] + 1ll * dp[i - l] * cnt[l]) % mod;
    }
  }
  cout << dp[m] << '\n';
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
