#include <bits/stdc++.h>
#include "dango3.h"
using namespace std;
#ifndef MISAKA
#define OO(x)
#else
#define OO(x) cerr << __PRETTY_FUNCTION__ << ": " << #x << " : " << (x) << '\n';
#endif
template<typename A>
void O(const A& a) {
  cerr << a << '\n';
}
template<typename A, typename... B>
void O(const A& a, const B& ...b) {
  cerr << a << ' ';
  O(b...);
}
typedef long long i64;
typedef unsigned long long u64;
typedef unsigned u32;
typedef pair<int, int> pii;
#define mkp make_pair
#define fi first
#define se second
#define pb push_back
#define eb emplace_back
#define FOR(i, j, k) for (int i = (j); i <= (k); ++i)
#define ROF(i, j, k) for (int i = (k); i >= (j); --i)
template<typename T>
inline void chkmin(T &a, const T b) {
  a = min(a, b);
}
template<typename T>
inline void chkmax(T &a, const T b) {
  a = max(a, b);
}
typedef vector<int> vi;
vi cat(const vi &a, const vi &b) {
  vi ret = a;
  for (auto v : b) ret.pb(v);
  return ret;
}
int w;
int a[100000];
int q(int col, int exc = 0) {
  vi r;
  FOR(i,1,w) if (a[i] == col && i != exc) r.pb(i);
  return Query(r);
}
void rep(int col) {
  vi r;
  FOR(i,1,w) if (a[i] == col) r.pb(i);
  Answer(r);
}
int tot = 1;

void work(int col, int m) {
  if (m == 1) return;
  int m1 = m / 2;
  int nc = ++tot;
  ROF(i,1,w) if (a[i] == col && q(col, i) >= m1) a[i] = nc;
  work(col, m1);
  work(nc, m - m1);
}


void Solve(int n, int m) {
  w = n * m;
  FOR(i,1,w) a[i] = 1;
  tot = 1;
  work(1,m);
  FOR(i,1,m) {
    rep(i);
  }
}

