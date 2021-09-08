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
int a, k;
vector<int> d;
namespace sub5 {
int nxt[1000005];
i64 ans[19][1000005];
void solve() {
  for (int i = 1; i < a; ++i) {
    nxt[i] = nxt[i - 1] + 10;
    if (nxt[i] >= a) nxt[i] %= a;
  }
  for (auto i : d) {
    ans[1][i % a] = i;
  }
  for (int i = 2; i < 19; ++i) {
    for (int j = 0; j < a; ++j) {
      if (ans[i - 1][j]) {
        for (auto k : d) {
          i64 to = ans[i - 1][j] * 10 + k;
          int tj = nxt[j] + k;
          if (tj >= a) tj %= a;
          if (!ans[i][tj]) ans[i][tj] = to;
          else chkmin(ans[i][tj], to);
        }
      }
    }
    if (ans[i][0]) {
      cout << ans[i][0] << '\n';
      return;
    }
  }
  puts("-1");
}
}

const int N = 1000005;
vector<int> G[N];
int dis[N];

queue<int> q;
void dist() {
  q.push(0);
  for (int i = 1; i < a; ++i) dis[i] = 1e8;
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    for (auto v : G[u]) {
      if (dis[v] > dis[u] + 1) {
        dis[v] = dis[u] + 1;
        q.push(v);
      }
    }
  }
}

int vis[10];
void solve() {
  a = rd(), k = rd();
  FOR(i, 0, k) vis[rd()] = 1;
  FOR(i, 0, 10) if (!vis[i]) d.pb(i);
  if (d.empty()) puts("-1");
  if (a == 1) {
    for (int i = 1; i < 10; ++i) {
      if (!vis[i]) {
        cout << i << '\n';
        return;
      }
    }
    puts("-1");
    return;
  }
  // else sub5::solve();
  for (int i = 1; i < a; ++i) {
    for (int c : d) {
      int to = (10 * i + c) % a;
      G[to].pb(i);
    }
  }
  dist();
  int mn = 1e8, c = -1;
  for (auto u : d) {
    if (u && dis[u] < mn) mn = dis[u % a], c = u;
  }
  if (mn == 1e8) {
    puts("-1");
    return;
  }
  cout << c;
  while (c != 0) {
    for (int v : d) {
      int to = (c * 10 + v) % a;
      if (dis[to] == dis[c % a] - 1) {
        cout << v;
        c = to;
        break;
      }
    }
  }
  cout << '\n';
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
