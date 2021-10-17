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
const int N = 805;
const int p = 1e9+7;
int n, m;
int a[N][N];
int b[N][N];
vector<int> g[N];
vector<pii> h[N * N];
bool vis[N * N];
int req[N * N];
int stk[N * N], tot;

void dfs(int *d, int u, int fa) {
  for (auto v : g[u]) {
    if (v != fa) {
      d[v] = max(d[u], a[u][v]);
      dfs(d, v, u);
    }
  }
}

void solve() {
  n = rd();
  m = (n - 1) * n / 2;
  FOR(i, 1, n) {
    int u = rd(), v = rd(), w = rd();
    a[u][v] = a[v][u] = w;
    g[u].pb(v);
    g[v].pb(u);
  }
  FOR(i, 1, n + 1) {
    dfs(b[i], i, 0);
  }
  FOR(i, 1, n) FOR(j, i + 1, n + 1) {
    if (a[i][j] == 0) {
      ++req[b[i][j]];
      h[b[i][j]].emplace_back(i, j);
    } else {
      vis[a[i][j]] = 1;
    }
  }
  i64 ans = 1;
  for (int used = 0, i = m; i > 0; --i) {
    if (vis[i]) ++used;
    else stk[++tot] = i;
    if (req[i] > 0) {
      for (int j = 0; j < req[i]; ++j) {
        if (m - i + 1 <= used) ans = 0;
        ans = ans * (m - i + 1 - used) % p;
        ++used;
        if (tot) {
          pii u = h[i][j];
          a[u.fi][u.se] = a[u.se][u.fi] = stk[tot];
          --tot;
        }
      }
    }
  }
  cout << ans << '\n';
  if (ans > 0) {
    FOR(i, 1, n + 1) {
      FOR(j, 1, n + 1) cout << a[i][j] << ' ';
      cout << '\n';
    }
  }
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
