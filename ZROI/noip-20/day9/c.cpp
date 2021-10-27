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

const int N = 1e6+5;
int tab[4][4][4] = {
  {},
{{0,1}},
{{0,1,2},{0,2,1}},
{{0,1,2,3},{0,2,1,3},{0,3,1,2},{0,1,3,2}}
};

inline i64 lim(i64 n) { return n * (n - 1) / 2; }

int ans[N];

inline void solve() {
  int n;
  i64 s;
  cin >> n >> s;
  if (s < 0 || s > lim(n)) {
    println("SPFA is dead!");
  } else {
    int r = n;
    while (r > 3 and s <= lim(r - 1)) --r;
    if (r <= 3) {
      for (int i = 1; i <= r; ++i) ans[i] = tab[r][s][i];
    } else {
      int d = lim(r) - s;
      FOR(i, 1, r) ans[i] = i + 1;
      ans[r] = 1;
      if (d) {
        if (d == 1) {
          if (r & 1) {
            int k = r >> 1;
            swap(ans[r], ans[k]);
            swap(ans[k], ans[k + 1]);
          } else {
            swap(ans[r], ans[r >> 1]);
          }
        } else {
          swap(ans[d], ans[d - 1]);
        }
      }
    }
    FOR(i, r + 1, n + 1) ans[i] = i;
    FOR(i, 1, n + 1) cout << ans[i] << '\n';
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

