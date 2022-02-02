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
const int N = 2e5+5;
int n;
int a[N], mn[N];
int x[N], y[N], t;

inline void solve() {
  cin >> n;
  FOR(i, 0, n * 2) cin >> a[i];
  mn[n-1] = a[n-1];
  ROF(i, 0, n - 1) mn[i] = min(mn[i+1], a[i]);
  int mns = 1e9+7;
  FOR(i, 0, n) if (a[i] == mn[0]) chkmin(mns, a[i+n]);
  if (mns <= mn[0]) {
    println(mn[0], mns);
    return;
  }
  int j;
  FOR(i, 0, n) if (a[i] == mn[0]) {
    j = i + 1;
    x[t] = a[i];
    y[t] = a[i+n];
    ++t;
  }
  for (j; j < n; ++j) {
    if (a[j] != mn[j]) continue;
    if (a[j] < y[0]) {
      x[t] = a[j];
      y[t] = a[j+n];
      ++t;
    } else break;
  }
  if (j < n && a[j] == y[0]) {
    bool ok = 0;
    for (int k = 1; k < t; ++k) {
      if (y[k] < y[0]) break;
      if (y[k] > y[0]) ok = 1;
    }
    if (ok) {
      int val = a[j];
      for (; j < n; ++j) if (a[j] == val) {
        x[t] = a[j];
        y[t] = a[j+n];
        ++t;
      }
    }
  }
  FOR(i, 0, t) cout << x[i] << ' ';
  FOR(i, 0, t) cout << y[i] << " \n"[t==i+1];
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

