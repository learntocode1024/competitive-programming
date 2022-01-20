#include <bits/stdc++.h>
using namespace std;
template<typename T>
void rd(T &a) {
  cin >> a;
}
template<typename A, typename... B>
void rd(A &a, B& ...b) {
  cin >> a;
  rd(b...);
}
template<typename A>
void print(const A& a) {
  cout << a;
}
template<typename A, typename... B>
void print(const A& a, const B& ...b) {
  cout << a;
  print(b...);
}
template<typename A>
void println(const A& a) {
  cout << a << '\n';
}
template<typename A, typename... B>
void println(const A& a, const B& ...b) {
  cout << a << ' ';
  println(b...);
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
#define FOR(i, j, k) for (int i = (j); i < (k); ++i)
#define ROF(i, j, k) for (int i = ((k) - 1); i >= j; --i)
template<typename T>
inline void chkmin(T &a, const T b) {
  a = min(a, b);
}
template<typename T>
inline void chkmax(T &a, const T b) {
  a = max(a, b);
}

//#define MULTI
const int N = 1e5+1;
int n;
map<i64, int> S;
map<i64, int> G;
int p[N], lo[N], t, t1;
i64 p3[N];

inline i64 grp(i64 X) {
  FOR(i, 0, t1) {
    while (X % p3[i] == 0) X /= p3[i];
    if (X < p3[i]) break;
  }
  return X;
}

inline i64 igrp(i64 X) {
  __int128 r2 = 1;
  FOR(i, 0, t1) {
    int c = 0;

    while (X % p[i] == 0) ++c, X /= p[i];
    if (c == 1) r2 = r2 * p[i] * p[i];
    else if (c == 2) r2 = r2 * p[i];
    if (X == 1) break;
    if (r2 > INT64_MAX) return 0;
  }
  auto it = G.find(X);
  if (it != G.end()) r2 *= it->se;
  else r2 = r2 * X * X;
    if (r2 > INT64_MAX) return 0;
  return r2;
}

inline void solve() {
  cin >> n;
  FOR(i, 2, N) {
    if (!lo[i]) {
      p[t++] = i;
      lo[i] = i;
    }
    for (int j = 0; j < t && p[j] <= lo[i] && p[j] * i < N; ++j) {
      lo[p[j] * i] = p[j];
    }
  }
  while (t1 < t && 1ll * p[t1] *p[t1] * p[t1] <= 10000000000ll) ++t1;
  FOR(i, 0, t1) p3[i] = 1ll * p[i] * p[i] * p[i];
  FOR(i, t1, t) G[1ll * p[i] * p[i]] = p[i];
  FOR(i, 0, n) {
    i64 s;
    cin >> s;
    ++S[grp(s)];
  }
  int s = 0;
  if (S.find(1)!=S.end()) S[1] = 1;
  for (auto it = S.begin(); it != S.end(); ++it)  {
    if (!it->se) continue;
    i64 rt = igrp(it->fi);
    s += max(it->se, S[rt]);
    S[rt] = 0;
  }
  println(s);
}

int main() {
#ifndef MISAKA
  //freopen(".in", "r", stdin);
  //freopen(".out", "w", stdout);
  ios::sync_with_stdio(0);
  cin.tie(0);
#endif
#ifdef MULTI
  int T;
  cin >> T;
  while (T--)
#endif
  solve();
  return 0;
}
/* Checklist:
 * - data type
 * - overflow
 * - typo/logic
 * - special cases
 * - cleanup (multi-test)
 * - bounds
 * - memory usage
 * - file IO
 */

