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
const int N = 3e5+5;
vector<int> g[N];

int vis[N];
int a[N], b[N];
int f[N], d[N];
int s[N], t[N], tot, to;
bool v[N];

void dfs(int u) {
  v[u] = 1;
  for (auto to : g[u]) {
    if (!v[to]) {
      f[to] = u;
      d[to] = d[u] + 1;
      dfs(to);
    }
  }
}

void path(int u, int v) {
  tot = to = 0;
  while (u != v) {
    if (d[v] > d[u]) {
      t[to++] = v;
      v = f[v];
    } else {
      s[tot++] = u;
      u = f[u];
    }
  }
  s[tot++] = u;
  FOR(i, 0, to) s[tot + i] = t[to - i - 1];
  tot += to;
}

void solve() {
  int n = rd(), m = rd();
  FOR(_, 0, m) {
    int u = rd(), v = rd();
    g[v].pb(u);
    g[u].pb(v);
  }
  int q = rd();
  FOR(i, 0, q) {
    a[i] = rd();
    b[i] = rd();
    ++vis[a[i]];
    ++vis[b[i]];
  }
  int cnt = 0;
  FOR(i, 1, n + 1) {
    if (vis[i] & 1) ++cnt;
  }
  if (cnt) {
    cout << "NO\n" << cnt / 2 << '\n';
  } else {
    dfs(1);
    cout << "YES\n";
    FOR(i, 0, q) {
      path(a[i], b[i]);
      cout << tot << '\n';
      FOR(i, 0, tot) cout << s[i] << ' ';
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
