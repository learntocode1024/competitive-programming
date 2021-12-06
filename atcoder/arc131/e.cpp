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

const int N = 55;

vector<int> s[N][3] = {
  {{1,4},{2,3},{5}},
  {{1,6},{2,5},{3,4}},
  {{},{},{}},
  {{1,2,3,6},{4,8},{5,7}},
  {{1,2,3,4,5},{6,9},{7,8}}
};

char o[N][N];

inline void solve() {
  FOR(i, 12, N) {
    if (i % 3 == 2) continue;
    FOR(j, 0, 3) {
      s[i-6][j] = s[i - 12][j];
      s[i-6][j].pb(i-1-j);
      s[i-6][j].pb(i-6+j);
    }
  }
  int n;
  cin >> n;
  if (n < 6 || n % 3 == 2) println("No");
  else {
    println("Yes");
    FOR(i, 0, 3) {
      for (auto t : s[n - 6][i]) {
        FOR(j, 0, t) o[t-1][j] = "RBW"[i];
      }
    }
    ROF(i, 0, n - 1) println(o[i]);
  }
}

int main() {
#ifndef MISAKA
  //freopen(".in", "r", stdin);
  //freopen(".out", "w", stdout);
  ios::sync_with_stdio(0);
  cin.tie(0);
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

