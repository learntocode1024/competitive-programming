/**********************************************************************
 * This file is the c++ solution to a particular CP problem written by
 * misaka18931 and was hosted on GitHub Repository below:
 * URL: https://github.com/misaka18931/competitive-programming
 *
 * Original Author: misaka18931
 * Date: Aug 11, 2021
 * Algorithm: Dinic
 * Difficulty: mid
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
#define MX 200000
#define MXM 2000000
char s[305][305];
int n, m, k;

inline int encode(int i, int j) {
  return i * m + j + 1;
}
inline pair<int, int> decode(int u) {
  --u;
  return mkp(u / m + 1, u % m + 1);
}

inline bool isT(int u) {
  --u;
  return s[u / m][u % m] == 'T';
}

namespace net {
int head[MX], to[MXM], nxt[MXM], hi[MX], d[MX], tot = 1;
i64 f[MXM];
int N;
int s, t;
void add_flow(int u, int v, i64 w) {
  to[++tot] = v, f[tot] = w, nxt[tot] = head[u], head[u] = tot;
  to[++tot] = u, f[tot] = 0, nxt[tot] = head[v], head[v] = tot;
}
bool bfs() {
  for (int i = 1; i <= N; ++i) {
    d[i] = 0;
  }
  d[s] = 1;
  queue<int> q;
  q.push(s);
  while (!q.empty()) {
    int u = q.front();q.pop();
    for (int i = head[u]; i; i = nxt[i]) {
      int v = to[i];
      i64 w = f[i];
      if (d[v] || !w) continue;
      d[v] = d[u] + 1;
      if (v == t) return 1;
      q.push(v);
    }
  }
  return 0;
}
i64 dfs(int u, i64 exc) {
  if (u == t) return exc;
  i64 res = exc;
  for (int &i = hi[u]; i; i = nxt[i]) {
    int v = to[i];
    i64 w = f[i];
    if (d[v] != d[u] + 1 || !w) continue;
    int k = dfs(v, min(res, w));
    if (!k) d[v] = 0;
    else res -= k, f[i] -= k, f[i ^ 1] += k;
    if (!res) break;
  }
  return exc - res;
}

int flow(int _s, int _t) {
  i64 ret = 0;
  s = _s, t = _t;
  while (bfs()) {
    for (int i = 1; i <= N; ++i) {
      hi[i] = head[i];
    }
    i64 f = 0;
    while ((f = dfs(s, 1e7))) ret += f;
  }
  return ret;
}
void print() {
  queue<pair<int, int> > q;
  for (int i = head[s]; i; i = nxt[i]) {
    int u = to[i];
    while (!isT(u >> 1)) {
      q.push(decode(u >> 1));
      ++u;
      for (int j = head[u]; j; j = nxt[j]) {
        if (j & 1) continue;
        int v = to[j], w = f[j];
        if (w == 0) {
          u = v;
          break;
        }
      }
    }
    q.push(decode(u >> 1));
    cout << q.size() << '\n';
    while (!q.empty()) {
      cout << q.front().fi << ' ' << q.front().se << '\n';
      q.pop();
    }
  }
}
}

int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

void solve() {
  n = rd(), m = rd(), k = rd();
  for (int i = 0; i < n; ++i)
    IO::rdstr(s[i]);
  int S = m * n * 2 + 2, T = S + 1;
  net::N = T;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      net::add_flow(encode(i, j) * 2, encode(i, j) * 2 + 1, 1);
      if (s[i][j] == 'X') continue;
      for (int k = 0; k < 4; ++k) {
        int ii = i + dx[k], jj = j + dy[k];
        if (ii < 0 || jj < 0 || ii >= n || jj >= m || s[ii][jj] == 'X') continue;
        net::add_flow(encode(i, j) * 2 + 1, encode(ii, jj) * 2, 1);
      }
      if (s[i][j] == 'S') net::add_flow(S, encode(i, j) * 2, 1);
      if (s[i][j] == 'T') net::add_flow(encode(i, j) * 2 + 1, T, 1);
    }
  }
  if (net::flow(S, T) < k) return;
  net::print();
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
