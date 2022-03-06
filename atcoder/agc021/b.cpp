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
const int N = 105;
typedef long double dbl;

dbl x[N], y[N];
dbl a[N];

inline void solve() {
  int n;
  rd(n);
  if (n == 2) {
    println(0.5);
    println(0.5);
    return;
  }
  FOR(i,0,n) rd(x[i],y[i]);
  FOR(i, 0, n) {
    dbl ang = 0;
    int t = 0;
    FOR(j, 0, n) if (j != i) {
      a[t++] = atan2(y[j]-y[i],x[j]-x[i]);
    }
    sort(a, a + t);
    bool ok = a[t-1]-a[0] < M_PI;
    dbl w = a[t-1]-a[0];
    FOR(i, 0, t-1) {
      if (a[i+1]-a[i] > M_PI) {
        w = 2*M_PI-a[i+1]+a[i];
        ok = 1;
      }
    }
    if (!ok) println(0);
    else {
      cout << fixed << setprecision(15) << 0.5l-w/M_PI/2 << '\n';
    }
  }
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

