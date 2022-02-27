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
const int N = 2e5+5;
const int p = 1e9+7;
int a[N];
int n, k;
set<int> S;
int f[N], s[N];

inline void solve() {
  rd(n, k);
  FOR(i, 0, n) rd(a[i]);
  sort(a, a + n);
  f[0] = f[1] = 1;
  FOR(i, 2, k + 1)f[i] = (f[i-1] + f[i-2]) % p;
  s[0] = 1;
  FOR(i, 1, k + 1) s[i] = (f[i] + s[i-1]) % p;
  FOR(i, 0, n) {
    int x = a[i];
    bool fe = 1;
    while (x) {
      if (S.find(x) != S.end()) {
        fe = 0;
      }
      if (x & 1) x >>= 1;
      else if ((x & 3) == 0) x >>= 2;
      else break;
    }
    if (fe) S.insert(a[i]);
  }
  int ans = 0;
  for (auto x : S) {
    ans = (ans + s[k - (32 - __builtin_clz(x))]) % p;
  }
  println(ans);
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

