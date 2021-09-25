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
#include <queue>
#include <set>
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
const int N = 50005, M = 15000000;
int n, m;
pii e[M];
vector<int> G[N];
vector<pii> g[N];
int a[N], rnk[N];
set<pii> edge;
int in[N];
int jmp[200];

void topo() {
  queue<int> q;
  FOR(i, 1, n + 1) if (!in[i]) q.push(i);
  for (int i = 1; i <= n; ++i) {
    a[i] = q.front();
    int u = a[i];
    rnk[u] = i;
    q.pop();
    for (auto v : G[u]) {
      --in[v];
      if (in[v] == 0) q.push(v);
    }
  }
}

int dp[N][3];
char s[100];
void trace(int v, int c) {
  for (auto x : g[v]) {
    if (x.se != c) continue;
    if (dp[x.fi][c] == dp[v][c] - 1) {
      trace(x.fi, c);
      break;
    }
  }
  cout << '(' << v << ',' << dp[v][c] << ") ";
}

void solve() {
  jmp['R'] = 0;
  jmp['G'] = 1;
  jmp['B'] = 2;
  n = rd(), m = rd();
  FOR(i, 0, m) {
    int u = rd(), v = rd();
    IO::rdstr(s);
    e[i] = mkp(u, v);
    if (edge.find(e[i]) == edge.end()) {
      G[u].pb(v);
      g[v].pb(mkp(u, jmp[*s]));
      ++in[v];
      edge.insert(e[i]);
    }
  }
  topo();
  for (int i = 1; i <= n; ++i) {
    int v = a[i];
    for (auto x : g[i]) {
      int u = x.fi;
      chkmax(dp[v][x.se], dp[u][x.se]);
    }
    ++dp[v][0];
    ++dp[v][1];
    ++dp[v][2];
    if (dp[v][0] > 43 || dp[v][1] > 43 || dp[v][2] > 43) {
      cout << "ERROR: at " << v << '\n';
      int tr = 0;
      if (dp[v][1] > 43) tr = 1;
      if (dp[v][2] > 43) tr = 2;
      trace(v, tr);
      cout << endl;
      exit(1);
    }
  }
}

int main() {
  freopen("ex.out", "r", stdin);
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
