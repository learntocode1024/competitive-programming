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
#include <string>
#include <vector>
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;

#define pb(x) push_back(x)
#define pf(x) push_front(x)
#define mkp(x, y) make_pair(x,y)
#define fi first
#define se second
#define MX 300005

template<typename T>
void chkmax(T &a, const T &b) {
  a = max(a, b);
}
template <typename T>
void chkmin(T &a, const T &b) {
  b = min(a, b);
}

int n, m;
vector<pair<int, int> > G[MX];

namespace VALID {
pair<int, int> son[MX];
int dep[MX];

int tmp[MX], tot;
int tmp1[MX], tot1;

bool dfs(int u, int fa) {
  vector<pair<int, int> > t1, t2;
  for (int Ts = 0; Ts < G[u].size(); ++Ts) {
    pair<int, int> v = G[u][Ts];
    if (v.first == fa) continue;
    if (!dfs(v.first, u)) return false;
    if (son[v.first].first == 0) t1.pb(v);
    else if (~dep[son[v.fi].fi] & 1) t2.pb(v);
    else t1.pb(v);
  }
  if (t1.size() & 1 && t2.size() & 1) return false;
  if (t1.size() & 1) son[u] = *t1.rbegin();
  if (t2.size() & 1) son[u] = *t2.rbegin();
  dep[u] = dep[son[u].fi] + 1;
  return true;
}

bool valid() {
  if (!dfs(1, 0) || (son[1].fi && dep[son[1].fi] & 1)) return false;
  return true;
}
}

namespace TREE {
pair<int, int> son[MX];
int dep[MX];

int tmp[MX], tot;
int tmp1[MX], tot1;

bool dfs(int u, int fa) {
  vector<pair<int, int> > t1, t2;
  for (int Ts = 0; Ts < G[u].size(); ++Ts) {
    pair<int, int> v = G[u][Ts];
    if (v.first == fa) continue;
    if (!dfs(v.first, u)) return false;
    if (son[v.first].first == 0) t1.pb(v);
    else if (~dep[son[v.fi].fi] & 1) t2.pb(v);
    else t1.pb(v);
  }
  if (t1.size() & 1 && t2.size() % 1) return false;
  for (int i = 1; i < t1.size(); i += 2) {
    pair<int, int> a = t1[i - 1], b = t1[i];
    while (son[a.fi].fi) tmp[tot++] = a.se, a = son[a.fi];
    while (son[b.fi].fi) tmp1[tot1++] = b.se, b = son[b.fi];
    printf("%d %d %d\n%d ", a.fi, b.fi, tot + tot1 + 2, a.se);
    for (int i = tot - 1; i >= 0; --i) {
      printf("%d ", tmp[i]);
    } tot = 0;
    for (int i = 0; i < tot1; ++i) {
      printf("%d ", tmp1[i]);
    } tot1 = 0;
    printf("%d\n", b.se);
  }
  for (int i = 1; i < t2.size(); i += 2) {
    pair<int, int> a = t2[i - 1], b = t2[i];
    while (son[a.fi].fi) tmp[tot++] = a.se, a = son[a.fi];
    while (son[b.fi].fi) tmp1[tot1++] = b.se, b = son[b.fi];
    printf("%d %d %d\n%d ", a.fi, b.fi, tot + tot1 + 2, a.se);
    for (int i = tot - 1; i >= 0; --i) {
      printf("%d ", tmp[i]);
    } tot = 0;
    for (int i = 0; i < tot1; ++i) {
      printf("%d ", tmp1[i]);
    } tot1 = 0;
    printf("%d\n", b.se);
  }
  if (t1.size() & 1) son[u] = *t1.rbegin();
  if (t2.size() & 1) son[u] = *t2.rbegin();
  dep[u] = dep[son[u].fi] + 1;
  return true;
}

void solve() {
  if (!VALID::valid()) {puts("-1"); return;}
  dfs(1, 0);
  if (son[1].fi && ~dep[son[1].fi] & 1) {
    pair<int, int> a = son[1];
    while (son[a.fi].fi) tmp[tot++] = a.se, a = son[a.fi];
    printf("1 %d %d\n", a.fi, tot + 1);
    for (int i = 0; i < tot; ++i)
      printf("%d ", tmp[i]);
    printf("%d\n", a.se);
  }
}
}

void solve() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= m; ++i) {
    int u, v;
    scanf("%d%d", &u, &v);
    G[u].pb(mkp(v, i));
    G[v].pb(mkp(u, i));
  }
  if (m == n - 1) {
    TREE::solve();
  }
}

int main() {
  int T = 1;
  while (T--)
    solve();
  return 0;
}

