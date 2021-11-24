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

const int N = 2e5+5;
const int p = 1e9+7;
int a[N];
int n;
i64 fac[N] = {1, 1}, ifac[N] = {1, 1}, inv[N] = {0, 1}, p2[N] = {1, 2};
int cnt[40], s[40];
inline i64 C(int n, int k) {
  if (k < 0 || k > n) return 0;
  return fac[n] * ifac[k] % p * ifac[n - k] % p;
}

inline void solve() {
  cin >> n;
  FOR(i, 0, n) cin >> a[i];
  FOR(i, 2, n + 1) {
    inv[i] = inv[p % i] * (p - p / i) % p;
    fac[i] = fac[i - 1] * i % p;
    ifac[i] = ifac[i - 1] * inv[i] % p;
    p2[i] = p2[i - 1] * 2 % p;
  }
  FOR(i, 0, n) {
    int c = __builtin_ctz(a[i]);
    if (c > 0) ++cnt[c - 1];
  }
  ROF(i, 0, 39) s[i] = s[i + 1] + cnt[i];
  i64 del = 0;
  ROF(i, 0, 39) {
    for (int j = 1; j <= cnt[i]; j += 2) {
      del = (del + p2[s[i + 1]] * C(cnt[i], j)) % p;
    }
  }
  // println(del);
  println((p2[n] + p - 1 + p - del)%p);
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

