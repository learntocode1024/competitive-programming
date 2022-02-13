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
const int N = 16, B = 1 << N;
bool f[N+1][N+1][B];

inline void prework() {
  for (int l = 1; l <= N; ++l) {
    f[l][0][0] = 1;
    int cB = (1 << l);
    for (int i = 1; i <= l; ++i) {
      FOR(s, 0, cB) f[l][i][s] = f[l][i-1][s];
      FOR(s, 0, cB) if (f[l][i-1][s]) {
        int cur = cB - (1<<(l-i));
        FOR(t, 0, l) {
          f[l][i][s^cur] = 1;
          cur >>= 1;
        }
      }
    }
  }
}

char s[20];

inline void solve() {
  cin >> s;
  int n = strlen(s);
  int to = 0;
  FOR(i, 0, n) {
    if (s[i] == '1') {
      to |= 1 << (n-1-i);
    }
    s[i] = 0;
  }
  FOR(i, 0, n + 1) {
    if (f[n][i][to]) {
      println(i);
      return;
    }
  }
}

int main() {
  prework();
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

