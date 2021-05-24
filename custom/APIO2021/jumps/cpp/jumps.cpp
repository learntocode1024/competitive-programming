#include "jumps.h"

#include <vector>
#include <climits>
#include <queue>
#include <set>
using namespace std;
#define MX 100005

int h[MX];
int pos[MX];
int n;
queue<int> q;
set<pair<int, int>> st;

int head[MX], to[MX * 2], nxt[MX * 2], tot;
#define add_edge(X, Y) \
to[++tot] = Y;\
nxt[tot] = head[X];\
head[X] = tot;

int d[MX];

void init(int N, std::vector<int> H) {
  n = N;
  for (int i = 0; i < N; ++i) {
    h[i] = H[i];
  }
  for (int i = 0; i < N; ++i) {
    pos[H[i]] = i;
  }
  for (int i = N; i > 0; --i) {
    auto iter = st.insert(make_pair(pos[i], i)).first;
    auto iter0 = iter;
    if (iter != st.begin()) {
      --iter;
      add_edge(i, iter->second);
    }
    ++iter0;
    if (iter0 != st.end()) {
      add_edge(i, iter0->second)
    }
  }
}

int minimum_jumps(int A, int B, int C, int D) {
  int ans = INT_MAX;
  for (int i = 0; i <= n; ++i) d[i] = -1;
  for (int i = A; i <= B; ++i) {
    q.push(h[i]);
    d[h[i]] = 0;
  }
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    for (int i = head[u]; i; i = nxt[i]) {
      int v = to[i];
      if (d[v] != -1)
        continue;
      d[v] = d[u] + 1;
      if (pos[v] <= D && pos[v] >= C)
        ans = min(ans, d[v]);
      q.push(v);
    }
  }
  if (ans == INT_MAX)
    ans = -1;
  return ans;
}
