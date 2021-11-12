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
int x[N], a[N];
unordered_set<i64> S;
int n;

inline void mark_factor(i64 x) {
  for (i64 i = 1; i * i <= x; ++i) {
    if (x % i) continue;
    S.insert(i);
    S.insert(x / i);
  }
}
int col[N];

inline void solve() {
  cin >> n;
  FOR(i, 0, n) rd(x[i], a[i]);
  FOR(i, 0, n) FOR(j, i + 1, n) {
    if (a[i] != a[j]) {
      mark_factor(abs(x[i] - x[j]));
    }
  }
  FOR(i, 2, n + 1) {
    bool ok = 1;
    int cnt = i;
    FOR(j, 0, n) {
      int r = x[j] % i;
      if (r < 0) r += i;
      if (!col[r]) {
        col[r] = a[j];
        --cnt;
      } else if (col[r] != a[j]) {
        ok = 0;
        break;
      }
    }
    if (!ok || cnt) {
      FOR(j, 0, i) col[j] = 0;
      continue;
    }
    for (int k = 1; k < i; ++k) {
      if (i % k) continue;
      bool ok2 = 1;
      for (int j = 0; j < k; ++j) {
        int cc = col[j];
        for (int l = j + k; l < i; l += k) {
          if (col[l] != cc) ok2 = 0;
        }
      }
      if (ok2) {
        S.insert(i);
        break;
      }
    }
    FOR(j, 0, i) col[j] = 0;
  }
  i64 s = 0;
  for (auto v : S) {
    s += v;
  }
  println(S.size(), s);
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

