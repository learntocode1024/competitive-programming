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

const int N = 15;
int vis[N * N];
int a[N];

inline void solve() {
  int n;
  rd(n);
  int brd = (n - 1) * (n - 2) / 2;
  int lim = (n) * (n - 1) / 2;
  iota(a + 1, a + n + 1, 1);
  do {
    int s = 0;
    FOR(i, 1, n + 1) {
      s += i % a[i];
    }
    if (!vis[s]) {
      println(s);
      cout << "{";
      FOR(i, 1, n + 1) {
        cout << a[i] << ",}"[i == n];
      }
      cout << "\n===============\n";
    }
    ++vis[s];
  } while (next_permutation(a + 1, a + n + 1));
  FOR(i, 0, N * N) {
    if (vis[i]) cout << i << ' ';
  }
  cout << '\n';
  FOR(i, 0, N * N) {
    if (vis[i]) cout << vis[i] << ' ';
  }
  cout << '\n';
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

