/**********************************************************************
 * This file is the c++ solution to a particular CP problem written by
 * misaka18931 and was hosted on GitHub Repository below:
 * URL: https://github.com/misaka18931/competitive-programming
 *
 * Original Author: misaka18931
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
} // namespace IO
template<typename T>
void rdint(T &a) {
  a = IO::rd();
}
template<typename A, typename... B>
void rdint(A &a, B& ...b) {
  a = IO::rd();
  rdint(b...);
}
template<typename A>
void print(const A& a) {
  cout << a;
}
template<typename A, typename... B>
void print(const A& a, const B& ...b) {
  cout << a;
  print(b...);
}
template<typename A>
void println(const A& a) {
  cout << a << '\n';
}
template<typename A, typename... B>
void println(const A& a, const B& ...b) {
  cout << a << ' ';
  println(b...);
}

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
const int N = 205;
int n;
int r[N], c[N], a[N], b[N], p[N];

bool vis[1<<5][N][N];
vector<int> dx, dy;

pii q[N * N * 40], hd, tl;

int f1[4] = {1, -1, 1, -1};
int f2[4] = {1, 1, -1, -1};

inline void bfs(int **vis) {
  hd = tl = 0;
  q[0] = mkp(r[0], c[0]);
  while (hd <= tl) {
    pii u = q[hd++];
    vis[u.fi][u.se] = 1;
    for (int i = 0; i < dx.size(); ++i) {
      for (int j = 0; j < 4; ++j) {
        int tx = u.fi + f1[j] * dx[i];
        int ty = u.se + f2[j] * dy[i];
        if (tx >= 0 && ty >= 0)
      }
    }
  }
}

void solve() {
  n = rd();
  FOR(i, 0, n) {
    rdint(r[i], c[i], a[i], b[i], p[i]);
  }
  if (r[i] == 0 && c[i] == 0) println("0");
  else {
    dx.pb(a[0]);
    dy.pb(b[0]);
    bfs(vis[1]);
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
