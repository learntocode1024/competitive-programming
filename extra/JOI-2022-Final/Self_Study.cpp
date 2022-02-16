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
const int N = 3e5+5;
int n, m;
int a[N], b[N];

bool chk(i64 x) {
  i64 sp = 0;
  FOR(i, 0, n) {
    if (a[i] > b[i]) {
      i64 c = ceil(1.0l * x / a[i]);
      if (c <= m) sp += m - c;
      else {
        sp -= ceil(1.0l * (x - 1ll * m * a[i]) / b[i]);
      }
    } else {
      sp += m;
      sp -= ceil(1.0l * x / b[i]);
    }
  }
  return sp >= 0;
}

inline void solve() {
  rd(n, m);
  FOR(i, 0, n) rd(a[i]);
  FOR(i, 0, n) rd(b[i]);
  i64 l = 0, r = 2e18;
  while (r - l > 1) {
    i64 mid = (l + r) >> 1;
    if (chk(mid)) l = mid;
    else r = mid;
  }
  println(l);
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

