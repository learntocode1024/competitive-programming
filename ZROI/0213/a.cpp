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
const int N = 64, M = 205;
const int p = 998244353;
int n, m;
u64 val[M], rk[M], aval[N], mask;
i64 ans = 1;
i64 pw[M];
#define msb(x) (63 - __builtin_clzll(x))
#define lsb(x) (__builtin_ctzll(x))
#define popcnt(x) (__builtin_popcountll(x))

inline void solve() {
  rd(n, m);
  FOR(i, 0, m) {
    rd(rk[i], val[i]);
    --rk[i];
  }
  mask = (1ull << n) - 1;
  FOR(i, 0, n) {
    aval[i] = mask;
  }
  int cnt = 0;
  u64 inlb = 0;
  FOR(i, 0, m) {
    if (rk[i]) {
      if (!val[i]) {
        ans = 0;
        break;
      }
      int b = msb(rk[i]);
      chkmax(cnt, b + 1);
      inlb |= 1ull << b;
      aval[b] &= 1ull << msb(val[i]);
      if (aval[b]) FOR(j, 0, b) {
        aval[j] &= aval[b] - 1;
      }
      if (aval[b]) FOR(j, b + 1, n) {
        aval[j] &= (1ull << n) - aval[b];
      }
    } else if (val[i]) ans = 0;
  }
  FOR(i, 0, cnt) aval[i] &= ~inlb;
  FOR(_, 0, cnt) {
    FOR(i, 0, cnt) {
      if (popcnt(aval[i]) == 1 && (inlb & aval[i]) == 0) {
        inlb |= aval[i];
        FOR(j, 0, cnt) aval[j] &= inlb;
        FOR(j, 0, i) aval[j] &= aval[i] - 1;
        FOR(j, i + 1, cnt) aval[j] &= mask ^ (aval[i] - 1);
        break;
      }
    }
  } // BF
  
}

int main() {
  pw[0] = 1;
  FOR(i, 1, M) pw[i] = pw[i-1] * 2 % p;
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

