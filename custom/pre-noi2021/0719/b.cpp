#include <algorithm>
#include <climits>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
#define MX_N 500005
#define MX_M 1000005
using namespace std;
typedef long long LL;
const int INF = 0x3f3f3f3f;

int s, t, n, m;
int to[MX_M * 2], nxt[MX_M * 2], tot = 1;
int head[MX_N];
int h[MX_N], gap[MX_N * 5];
LL c[MX_M * 4], e[MX_N], cbak[MX_M * 4];
struct cmp { bool operator() (int a, int b) const { return h[a] < h[b]; } };
priority_queue<int, vector<int>, cmp> pq;
bool in_stack[MX_N];

void add_flow(int u, int v, int w) {
  to[++tot] = v;
  cbak[tot] = c[tot] = w;
  nxt[tot] = head[u];
  head[u] = tot;
  to[++tot] = u;
  cbak[tot] = c[tot] = 0;
  nxt[tot] = head[v];
  head[v] = tot;
}

void relabel(int u) {
  h[u] = INF;
  for (int i = head[u]; i; i = nxt[i]) {
    int &v = to[i];
    h[u] += (c[i] && h[u] > h[v]) * (h[v] - h[u]);
  }
  h[u] = h[u] + 1;
}

int push(int u) {
  int i = head[u];
  while (i && e[u]) {
    int &v = to[i];
    if (c[i] && h[v] + 1 == h[u]) {
      LL minv = min(c[i], e[u]);
      c[i] -= minv;
      c[i ^ 1] += minv;
      e[u] -= minv;
      e[v] += minv;  // forgoten
      if (!in_stack[v] && v != s && v != t) in_stack[v] = 1, pq.push(v);
    }
    i = nxt[i];
  }
  return e[u] != 0;
}

int bfs(int t) {
  h[t] = 0;
  queue<int> q;
  q.push(t);
  while (q.size()) {
    int u = q.front();
    q.pop();
    for (int i = head[u]; i; i = nxt[i]) {
      int &v = to[i];
      if (c[i ^ 1] && h[v] > h[u] + 1) h[v] = h[u] + 1, q.push(v);
    }
  }
  return h[s] != INF;
}

int hlpp_init() {
  memset(h, 0x3f, sizeof(h));
  if (!bfs(t)) return 0;
  h[s] = n;
  for (int i = head[s]; i; i = nxt[i]) {
    if (c[i]) {
      c[i ^ 1] += c[i];
      e[to[i]] += c[i];
      e[s] -= c[i];
      c[i] = 0;
      if (to[i] != s && to[i] != t && !in_stack[to[i]])
        pq.push(to[i]), in_stack[to[i]] = true;
    }
  }
  for (int i = 1; i <= n; ++i) {
    if (h[i] != INF) ++gap[h[i]];
  }
  return 1;
}

LL hlpp() {
  if (!hlpp_init()) return 0;
  while (pq.size()) {
    int u = pq.top();
    pq.pop();
    in_stack[u] = 0;
    while (push(u)) {
      --gap[h[u]];
      if (!gap[h[u]]) {
        for (int i = 1; i <= n; ++i) {
          if (i != s && i != t && h[i] > h[u] && h[i] < n + 1) h[i] = n + 1;
        }
      }
      relabel(u);
      ++gap[h[u]];
    }
  }
  return e[t];
}

int q;

int main() {
  scanf("%d%d%d", &n, &m, &q);
  for (int i = 0; i < m; ++i) {
    int u, v, w;
    cin >> u >> v >> w;
    add_flow(u, v, w);
    add_flow(v, u, w);
  }
  while (q--) {
    for (int i = 0; i < n + 5; ++i) {
      h[i] = e[i] = 0;
    }
    for (int i = 0; i < 5 * n + 5; ++i) gap[i] = 0;
    for (int i = 0; i < 4 * m + 5; ++i) c[i] = cbak[i];
    scanf("%d%d", &s, &t);
    printf("%lld\n", hlpp());
  }
  return 0;
}
