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

const int N = 1e5+5;
bool dp[N][3][3];
int b[N];
int n;
int mean(int a, int b, int c) {
  int s[3] = {a, b, c};
  sort(s, s + 3);
  return s[1];
}

void ans(int i, int c0, int c) {
  if (i == 0) print(b[c0 - 1] , ' ');
  else {
    for (int c1 = 0; c1 < 3; ++c1) {
          if (i + c1 >= 2 && mean(b[i - 2 + c1], b[i - 1 + c0], b[i + c]) == b[i] && dp[i-1][c1][c0]) {
            ans(i-1, c1, c0);
            break;
          }
    }
  }
  print(b[c + i], ' ');
}

inline void solve() {
  cin >> n;
  memset(dp, 0, n * sizeof(dp[1]));
  FOR(i, 1, n - 1) cin >> b[i];
  dp[0][2][1] = dp[0][2][2] = 1;
  FOR(i, 1, n - 1) {
    for (int c1 = 0; c1 < 3; ++c1) {
      for (int c0 = 0; c0 < 3; ++c0) {
        for (int c = 0; c < 3; ++c) {
          if (i + c1 >= 2 && mean(b[i - 2 + c1], b[i - 1 + c0], b[i + c]) == b[i]) dp[i][c0][c] |= dp[i-1][c1][c0];
        }
      }
    }
  }
  FOR(i, 0, 3) FOR(j, 0, 3) {
    if (dp[n - 2][i][j]) {
      ans(n - 2, i, j);
      print('\n');
      return;
    }
  }
  println(-1);
}

int main() {
#ifndef MISAKA
  //freopen(".in", "r", stdin);
  //freopen(".out", "w", stdout);
  ios::sync_with_stdio(0);
  cin.tie(0);
#endif
int T;
cin >> T;
while (T--)
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

