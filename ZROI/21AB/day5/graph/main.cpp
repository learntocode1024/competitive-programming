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
#include "graph.h"
using namespace std;

/********************************* macros *************************************/
typedef long long i64;
typedef unsigned long long u64;
typedef unsigned int u32;
#define pb(x) push_back(x)
#define fi first
#define se second
#define REP(x, y, z) for (int x = y; x < z; ++x) // always [y, z)
#define PER(x, y, z) for (int x = z - 1; x >= y; --x)
template <typename T> void chkmax(T &a, const T &b) { a = max(a, b); }
template <typename T> void chkmin(T &a, const T &b) { a = min(a, b); }

/*********************************** solution *********************************/
#define MX 50005
int n;

map<int, bool> G[MX];
int DEG[MX];
bool vis[MX];
inline int scan(int u) {
  if (vis[u]) return DEG[u];
  for (int i = 1; i <= n; ++i) {
    if (u == i) continue;
    bool r = query_edge(u, i);
    G[u][i] = r;
    DEG[u] += r;
  }
  vis[u] = 1;
  return DEG[u];
}

inline int only(int u) {
  for (int i = 1; i <= n; ++i) {
      if (G[u][i]) {
        return i;
      }
    }
    return 0;
}

inline int exc(int u) {
  for (int i = 1; i <= n; ++i) {
      if (i != u && !G[u][i]) {
        return i;
      }
    }
    return 0;
}

inline int oth(int u, int c) {
  for (int i = 1; i <= n; ++i) {
      if (i != c && i != u && G[u][i]) {
        return i;
      }
    }
    return 0;
}

std::vector<int> check_graph(int N, int limit) {
  n = N;
  int a = 0, b = 0, c = 0;
  int d = scan(1);
  if (d == N - 1) return {};
  if (d == N - 2) {
    c = 1;
    a = exc(c);
    if (scan(a) != 1) return {};
    b = only(a);
    if (scan(b) != 2) return {};
  } else if (d == 1) {
    int to = only(1);
    if (scan(to) == n - 2) {
      c = to;
      a = exc(c);
      if (scan(a) != 1) return {};
      b = only(a);
      if (scan(b) != 2) return {};
    } else if (scan(to) == 2) {
      a = 1;
      b = to;
      c = oth(b, a);
      if (scan(c) != N - 2) return {};
    } else return {};
  } else if (d == 2) {
    int to1 = only(1);
    int to2 = oth(1, to1);
    if (scan(to1) == N - 2) {
      c = to1;
    } else if (scan(to2) == N - 2) {
      c = to2;
    } else return {};
    a = exc(c);
    if (scan(a) != 1) return {};
    b = only(a);
    if (scan(b) != 2) return {};
  } else {
    static int s[MX], t[MX];
    int t1, t2;
    t1 = t2 = 0;
    for (int i = 2; i <= N; ++i) {
      if (G[1][i]) s[++t1] = i;
      else t[++t2] = i;
    }
    while (t1 > 0 && t2 > 0) {
      if (query_edge(s[t1], t[t2])) --t2;
      else --t1;
    }
    if (!t2) return {};
    a = t[t2];
    if (scan(a) != 1) return {};
    b = only(a);
    if (scan(b) != 2) return {};
    c = oth(b, a);
    if (scan(c) != N - 2) return {};
  }
  return {a, b, c};
}
