#include <bits/stdc++.h>
#include "atcoder/modint"
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
const int N = 1 << 20;
using mint = atcoder::modint998244353;
i64 n;
int k;

inline i64 f(i64 x) {
  return (3*x)/2 + 1;
}

namespace sub2 {
void work() {
  mint ans = n;
  FOR(i, 0, n) {
    i64 x = i;
    FOR(_, 0, k) x = f(x);
    ans += x;
  }
  println(ans.val());
}
}

namespace sub0 {
void work() {
  mint ans = n;
  mint pw = 1;
  FOR(i, 0, k) pw *= 3;
  i64 c = n >> k;
  int r = n & ((1<<k)-1);
  FOR(i, 0, 1 << k) {
    i64 cur = c + (i < r);
    i64 x = i;
    FOR(_, 0, k) x = f(x);
    ans += mint(x) * cur;
    ans += pw * mint(cur) * mint(cur - 1) / mint(2);
  }
  println(ans.val());
}
}

namespace sub1 {
const int SZ = 1<<20, B = 50;
i64 ca[SZ], cb[SZ];
mint g[SZ][B];
void work() {
  mint ans = n;
  int a = k / 2, b = k - a;
  int N = 1 << b;
  mint pw = 1;
  i64 c = 1;
  FOR(i, 0, a) c *= 3;
  FOR(i, 0, b) pw *= 3;
  FOR(i, 0, N) {
    i64 x = i;
    FOR(_, 0, b) x = f(x);
    g[i][0] = x;
  }
  FOR(k, 1, B) {
    FOR(i, 0, N) {
      i64 j = i + (c << (k-1));
      mint w = j >> b;
      j &= (N-1);
      g[i][k] = g[i][k-1] + g[j][k-1] + w * mint(1 << (k-1)) * pw;
    }
  }
  auto sum = [c, N, pw] (i64 a, i64 sz) {
    mint ret = 0;
    FOR(i, 0, B) if ((sz>>i)&1) {
      i64 q = a / N;
      i64 r = a & (N - 1);
      ret += g[r][i];
      ret += q * pw * mint(1 << i);
      a += c << i;
    }
    return ret;
  };
  i64 C = n >> a;
  i64 r = n & ((1<<a)-1);
  FOR(i, 0, 1 << a) {
    i64 cur = C + (i < r);
    i64 x = i;
    FOR(_, 0, a) x = f(x);
    ans += sum(x, cur);
  }
  println(ans.val());
}
}

inline void solve() {
  rd(n, k);
  FOR(_, 0, k) n = (n*2)/3;
  if (k > 38) sub2::work();
  else if (k < 20) sub0::work();
  else sub1::work();
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

