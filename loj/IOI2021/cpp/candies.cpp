/**********************************************************************
 * This file is the c++ solution to a particular CP problem written by
 * misaka18931 and was hosted on GitHub Repository below:
 * URL: https://github.com/misaka18931/competitive-programming
 *
 * Original Author: misaka18931
 * Date: Jul 12, 2021
 * Algorithm: segment-tree, time-interval-swap
 * Difficulty: hard
 *
 *********************************************************************/

#include "candies.h"
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
const LL mod = 1e9 + 7;
#define printb(x)                                                              \
  if ((bool)x)                                                                 \
    printf("YES");                                                             \
  else                                                                         \
    printf("NO");
#define pb(x) push_back(x)
#define pf(x) push_front(x)
#define MX 200005

vector<pair<int, int>> ch[MX];
int q, n;

LL mn[MX << 2], mx[MX << 2], tg[MX << 2];

void pushdown(int u) {
  int l = u << 1, r = l + 1;
  mn[l] += tg[u];
  mn[r] += tg[u];
  mx[l] += tg[u];
  mx[r] += tg[u];
  tg[l] += tg[u];
  tg[r] += tg[u];
  tg[u] = 0;
}

void pushup(int u) {
  int l = u << 1, r = l + 1;
  mn[u] = min(mn[l], mn[r]);
  mx[u] = max(mx[l], mx[r]);
}

void change(int p, int l, int r, int s, int t, int v) {
  if (l == s && r == t) {
    mn[p] += v;
    mx[p] += v;
    tg[p] += v;
    return;
  }
  pushdown(p);
  int lc = p << 1, rc = lc + 1;
  int mid = l + (r - l) / 2;
  if (s < mid)
    change(lc, l, mid, s, min(t, mid), v);
  if (t > mid)
    change(rc, mid, r, max(s, mid), t, v);
  pushup(p);
}

int get(int pos) {
  int l = 0, r = q, ret = 1;
  while (r - l > 1) {
    pushdown(ret);
    int mid = l + (r - l) / 2;
    ret <<= 1;
    if (pos < mid)
      r = mid;
    else
      l = mid, ret++;
  }
  return ret;
}

LL search(LL c, LL final) {
  int p = 1;
  int l = 0, r = q;
  LL sfmin = 1000000000000l, sfmax = -1000000000000l;
  while (r - l > 1) {
    pushdown(p);
    int mid = l + (r - l) / 2;
    int lc = p << 1, rc = lc + 1;
    if (max(sfmax, mx[rc]) - min(sfmin, mn[rc]) > c) {
      l = mid;
      p = rc;
    } else {
      r = mid;
      p = lc;
      sfmin = min(sfmin, mn[rc]);
      sfmax = max(sfmax, mx[rc]);
    }
  }
  int ret = 0;
  if (mn[p] < sfmin)
    ret = final + c - sfmax;
  else
    ret = final - sfmin;
  return ret;
}

vector<int> distribute_candies(vector<int> c, vector<int> l, vector<int> r,
                               vector<int> v) {
  q = l.size() + 1;
  n = c.size();
  for (int i = 0; i < q - 1; ++i) {
    ch[l[i]].push_back(make_pair(i + 1, v[i]));
    ch[r[i] + 1].push_back(make_pair(i + 1, -v[i]));
  }
  vector<int> ans(n);
  for (int u = 0; u < n; ++u) {
    for (auto i : ch[u])
      change(1, 0, q, i.first, q, i.second);
    LL final = mn[get(q - 1)];
    if (mx[1] - mn[1] <= c[u]) {
      ans[u] = final - mn[1];
    } else {
      ans[u] = search(c[u], final);
    }
  }
  return ans;
}
