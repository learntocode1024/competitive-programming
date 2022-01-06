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
const int p = 998244353;
int k, h, w;
int x1, x2, Y1, Y2;
i64 ph[N], pw[N], inv[N] = {0, 1}, fac[N] = {1, 1}, ifac[N] = {1, 1};
i64 ch[N], cw[N];
inline i64 C(int n, int k) {
  if (k < 0 || k > n) return 0;
  return fac[n] * ifac[k] % p * ifac[n - k] % p;
}

inline void solve() {
  rd(h, w, k);
  rd(x1, Y1, x2, Y2);
  FOR(i, 2, k + 1) {
    fac[i] = fac[i - 1] * i % p;
    inv[i] = inv[p % i] * (p - p / i) % p;
    ifac[i] = ifac[i - 1] * inv[i] % p;
  }
  if (x1 == x2) {
    ph[0] = 1;
    ch[0] = 0;
  } else {
    ph[0] = 0;
    ch[0] = 1;
  }
  if (Y1 == Y2) {
    pw[0] = 1;
    cw[0] = 0;
  } else {
    pw[0] = 0;
    cw[0] = 1;
  }
  FOR(i, 1, k + 1) {
    ph[i] = ch[i - 1];
    ch[i] = ((h - 2) * ch[i - 1] + (h - 1) * ph[i - 1]) % p;
    pw[i] = cw[i - 1];
    cw[i] = ((w - 2) * cw[i - 1] + (w - 1) * pw[i - 1]) % p;
  }
  i64 ans = 0;
  FOR(i, 0, k + 1) {
    ans = (ans + C(k, i) * pw[i] % p * ph[k - i]) % p;
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

