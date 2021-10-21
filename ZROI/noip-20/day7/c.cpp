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
const int N = 5e5+5;
vector<int> g[N];
bool ring[N], vis[N], instk[N];
vector<int> r, rc;
int dep[N];
int aans = 0, ans[N];
vector<pii> gg[N];

int stk[N], ts;

bool dfs1(int u, int fa) {
  int ret = u;
  vis[u] = 1;
  stk[++ts] = u;
  instk[u] = 1;
  for (auto v : g[u]) {
    if (v != fa && !vis[v]) {
      if (dfs1(v, u)) return 1;
    } else if (v != fa && vis[v] && instk[v]) {
      while (stk[ts] != v) {
        r.pb(stk[ts]);
        ring[stk[ts]] = 1;
        --ts;
      }
        r.pb(v);
        ring[v] = 1;
      return 1;
    }
  }
  --ts;
  instk[u] = 0;
  return 0;
}

int dfs2(int u, int fa) {
  dep[u] = dep[fa] + 1;
  int ret = u;
  int mxd = dep[u];
  for (auto v : g[u]) {
    if (v != fa && !ring[v]) {
      int t = dfs2(v, u);
      if (dep[t] > mxd) {
        mxd = dep[t];
        ret = t;
      }
    }
  }
  return ret;
}

int x[N << 1], f[N << 1], rr[N << 1];
deque<int> q1, q2;

inline void run_dp() {
  int n = rc.size();
  for (int i = 0; i < n; ++i) {
    x[i + 1] = rc[i];
    rr[i + 1] = r[i];
  }
  for (int i = n + 1; i <= n * 2; ++i) {
    x[i] = x[i - n];
    rr[i] = rr[i - n];
  }
  for (int i = 1; i <= n; ++i) {
    while (!q1.empty() && (x[q1.back()] - q1.back()) <= x[i] - i) q1.pop_back();
    q1.push_back(i);
  }
  for (int i = 1; i <= n; ++i) {
    while (!q2.empty() && (x[q2.back()] + q2.back()) <= x[i] + i) q2.pop_back();
    q2.push_back(i);
  }
  for (int i = n; i < 2 * n; ++i) {
    int cur = x[q1.front()] - q1.front() + x[q2.front()] + q2.front();
    for (auto id : gg[rr[i]]) {
      if (id.fi == rr[i + 1]) {
        chkmax(ans[id.se], max(aans, cur));
        break;
      }
    }
    int t = i + 1;
    while (q1.size() && q1.front() < i - n + 2) q1.pop_front();
    while (!q1.empty() && (x[q1.back()] - q1.back()) <= x[t] - t) q1.pop_back();
    q1.push_back(t);
    while (q2.size() && q2.front() < i - n + 2) q2.pop_front();
    while (!q2.empty() && (x[q2.back()] + q2.back()) <= x[t] + t) q2.pop_back();
    q2.push_back(t);
  }
}

// priority_queue<pii> pq1, pq2;
// inline void work() {
//   int n = rc.size();
//   for (int i = 0; i < n; ++i) {
//     x[i + 1] = rc[i];
//     rr[i + 1] = r[i];
//   }
//   for (int i = n + 1; i <= n * 2; ++i) {
//     x[i] = x[i - n];
//     rr[i] = rr[i - n];
//   }
//   for (int i = 1; i <= n; ++i) {
//     pq1.push({x[i] - i, i});
//   }
//   for (int i = 1; i <= n; ++i) {
//     pq2.push({x[i] + i, i});
//   }
//   for (int i = n; i < 2 * n; ++i) {
//     int cur;
//     while (!pq1.empty() && pq1.top().se < i - n + 1) pq1.pop();
//     while (!pq2.empty() && pq2.top().se < i - n + 1) pq2.pop();
//     if (pq1.top().se != pq2.top().se) {
//       cur = pq1.top().fi + pq2.top().fi;
//     } else {
//       cur = 0;
//       pii p1 = pq1.top();
//       pq1.pop();
//       while (!pq1.empty() && pq1.top().se < i - n + 1) pq1.pop();
//       if (!pq1.empty()) chkmax(cur, pq1.top().fi + pq2.top().fi);
//       pq1.push(p1);
//       p1 = pq2.top();
//       pq2.pop();
//       while (!pq2.empty() && pq2.top().se < i - n + 1) pq2.pop();
//       if (!pq2.empty()) chkmax(cur, pq2.top().fi + pq1.top().fi);
//       pq2.push(p1);
//     }
//     for (auto id : gg[rr[i]]) {
//       if (id.fi == rr[i + 1]) {
//         chkmax(ans[id.se], max(aans, cur));
//         break;
//       }
//     }
//     int t = i + 1;
//     pq1.push({x[t] - t, t});
//     pq2.push({x[t] + t, t});
//   }
// }

void solve() {
  int n = rd();
  FOR(i, 0, n) {
    int u = rd();
    int v = rd();
    g[u].pb(v);
    g[v].pb(u);
    gg[u].push_back({v, i});
    gg[v].push_back({u, i});
  }
  dfs1(1, 0);
  dep[0] = -1;
  for (auto rt : r) {
    ring[rt] = 0;
    int v = dfs2(rt, 0);
    rc.pb(dep[v]);
    chkmax(aans, dep[dfs2(v, 0)]);
    ring[rt] = 1;
  }
  run_dp();
  // work();
  for (int i = 0; i < n; ++i) {
    cout << (ans[i] > 0 ? ans[i] : -1) << '\n';
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
 * 8
1 2
1 3
2 4
4 7
4 6
7 5
8 6
7 6
*/
