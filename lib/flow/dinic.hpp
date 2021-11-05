#pragma once

#include <queue>

#include "utils.hpp"

template <u32 MX, u32 MXM>
struct net {
  int head[MX], to[MXM], nxt[MXM], hi[MX], d[MX], tot = 1;
  i64 f[MXM];
  int N;
  int s, t;
  net(int n) : N(n) {};
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
      int u = q.front();
      q.pop();
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
      if (!k)
        d[v] = 0;
      else
        res -= k, f[i] -= k, f[i ^ 1] += k;
      if (!res) break;
    }
    return exc - res;
  }

  i64 flow(int _s, int _t) {
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
};
