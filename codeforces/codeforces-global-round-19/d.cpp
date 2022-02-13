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

#define MULTI
const int N = 105;

int a[N], b[N];
int n;
const int B = 10000, BB = 20001;
bool v[N][BB];

inline void solve() {
  cin >> n;
  FOR(i, 1, n + 1) cin >> a[i];
  FOR(i, 1, n + 1) cin >> b[i];
  if (n == 1) {
    println(0);
    return;
  }
  i64 ans = 0;
  i64 s = 0;
  FOR(i, 1, n + 1) ans += a[i] * a[i], s += a[i];
  FOR(i, 1, n + 1) ans += b[i] * b[i], s += b[i];
  ans = (n-2) * ans;
  v[0][B] = 1;
  FOR(i, 1, n + 1) {
    FOR(j, 0, BB) {
      v[i][j] = 0;
    }
    int d = a[i] - b[i];
    FOR(j, 0, BB) if (v[i-1][j]) {
      v[i][j-d] = v[i][j+d] = 1;
    }
  }
  i64 t  =1e8;
  FOR(i, 0, BB) if (v[n][i]) {
    chkmin(t, 1ll*abs(B-i));
  }
  i64 s1 = (s-t)/2, s2 = (s+t)/2;
  println(ans + s1*s1+s2*s2);
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

