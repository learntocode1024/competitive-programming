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

const int N = 8, M = 50;
pii a[M], b[M];
int u[M], v[M];
int p[N];
int n, m;


inline void solve() {
  rd(n, m);
  FOR(i, 0, m) {
    int x, y;
    rd(x, y);
    --x, --y;
    a[i].fi = min(x, y);
    a[i].se = max(x, y);
  }
  sort(a, a + m);
  FOR(i, 0, m) rd(u[i], v[i]), --u[i], --v[i];
  iota(p, p + n, 0);
  do {
  FOR(i, 0, m) {
    int x, y;
    x = p[u[i]], y = p[v[i]];
    b[i].fi = min(x, y);
    b[i].se = max(x, y);
  }
    sort(b, b + m);bool t = 1;
    FOR(i, 0, m) {
      if (a[i] != b[i]) {
        t = 0;
        break;
      }
    }
    if (t) {
      println("Yes");
      return;
    }
  } while (next_permutation(p, p + n));
  println("No");
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

