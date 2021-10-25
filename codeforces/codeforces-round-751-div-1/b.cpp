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
#include <queue>
#include <set>
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
int a[N], b[N];
set<pii> S;
int d[N], lst[N];
vector<int> g[N];
priority_queue<pii> pq;
bool vis[N];

void solve() {
  int n = rd();
  FOR(i, 1, n + 1) a[i] = rd(), S.insert({i - a[i], i});
  FOR(i, 1, n + 1) b[i] = rd(), g[i + b[i]].pb(i);
  pq.push({0, 0});
  FOR(i, 1, n + 1) d[i] = -1;
  while (!pq.empty() && !S.empty() && d[n] == -1) {
    auto u = pq.top();
    pq.pop();
    if (vis[u.se]) continue;
    vis[u.se] = 1;
    auto ed = S.lower_bound({u.se + 1, 0});
    for (auto it = S.begin(); it != ed; it = S.erase(it)) {
      for (auto v : g[it->se]) {
        if (d[v] == -1 || d[v] > d[u.se] + 1) {
          d[v] = d[u.se] + 1;
          lst[v] = u.se;
          pq.push({-d[v], v});
        }
      }
    }
  }
  cout << d[n] << '\n';
  if (d[n] != -1) {
    int u = n;
    do {
      u = lst[u];
      cout << u << ' ';
    } while (u);
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
