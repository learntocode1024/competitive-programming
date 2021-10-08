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
#include <map>
#include <string>
#include <vector>
using namespace std;

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
// #define MULTI
const int N = 2000 * 60 + 5;
int k;
const i64 p = 1e9+7;
inline void red(i64 &x) { if (x >= p) x -= p; }
map<string, int> mp = {{"white", 0}, {"yellow", 1}, {"green", 2}, {"blue", 3}, {"red", 4}, {"orange", 5}};

const bool va[6][6] = {
{0, 0, 1, 1, 1, 1},
{0, 0, 1, 1, 1, 1},
{1, 1, 0, 0, 1, 1},
{1, 1, 0, 0, 1, 1},
{1, 1, 1, 1, 0, 0},
{1, 1, 1, 1, 0, 0}
};

struct DS {
  int ch[N][2], tag[N], tot;
  i64 dp[N][6];
  DS() {
    tot = 1;
    tag[1] = -1;
  }
  inline bool insert(i64 x, int tg) {
    int p = 1;
    int t = 62 - __builtin_clzll(x);
    for (; t >= 0; --t) {
      int &nxt = ch[p][(x >> t) & 1];
      if (nxt == 0) nxt = ++tot, tag[tot] = -1;
      p = nxt;
    }
    if (tag[p] != -1 && tag[p] != tg) return false;
    tag[p] = tg;
    return true;
  }
  void dfs(int u) {
    if (!ch[u][0] && !ch[u][1]) {
      dp[u][tag[u]] = 1;
      return;
    }
    if (!ch[u][0] || !ch[u][1]) {
      int v = ch[u][0] | ch[u][1];
      dfs(v);
      for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < 6; ++j) {
          if (va[i][j]) {
            red(dp[u][i] += dp[v][j]);
          }
        }
      }
    } else {
      dfs(ch[u][0]);
      dfs(ch[u][1]);
      int v1 = ch[u][0], v2 = ch[u][1];
      for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < 6; ++j) {
          for (int k = 0; k < 6; ++k) {
            if (va[i][j] && va[i][k]) {
              red(dp[u][i] += dp[v1][j] * dp[v2][k] % p);
            }
          }
        }
      }
    }
    if (tag[u] != -1) {
      for (int i = 0; i < 6; ++i) {
        if (i != tag[u]) dp[u][i] = 0;
      }
    }
  }
  i64 calc() {
    dfs(1);
    i64 ret = 0;
    FOR(i, 0, 6) ret = (ret + dp[1][i]) % p;
    return ret;
  }
} T;

namespace ez {
const i64 pp = p - 1;
  i64 qq_pow(i64 x, int a) {
  i64 ret = 1;
  while (a) {
    if (a & 1) ret = ret * x % pp;
    x = x * x % pp;
    a >>= 1;
  }
  return ret;
}

i64 q_pow(i64 x, int a) {
  i64 ret = 1;
  while (a) {
    if (a & 1) ret = ret * x % p;
    x = x * x % p;
    a >>= 1;
  }
  return ret;
}

i64 solve() {
  i64 y = qq_pow(2, k) + pp - 1 - T.tot;
  y %= pp;
  return q_pow(4, y);
}
}

void solve() {
  cin >> k;
  int n;
  cin >> n;
  FOR(i, 0, n) {
    string s;
    i64 x;
    cin >> x >> s;
    if (!T.insert(x, mp[s])) {
      cout << "0\n";
      return;
    }
  }
  // cout << T.calc() << '\n' << ez::solve() << '\n';
  cout << T.calc() * ez::solve() % p << '\n';
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
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
