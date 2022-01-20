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

#define MULTI
const int N = 1e5+5;
const int p = 998244353;
i64 fac[N], ifac[N], inv[N], D[N];

void work() {
  fac[0] = fac[1] = ifac[0] = ifac[1] = inv[1] = 1ll;
  D[1] = 0;
  for (int i = 2; i < N; ++i) {
    inv[i] = (p - p / i) * inv[p % i] % p;
    fac[i] = fac[i - 1] * i % p;
    ifac[i] = ifac[i - 1] * inv[i] % p;
    if (i & 1) D[i] = p - 1;
    else D[i] = 1;
    D[i] = (D[i] + i * D[i-1]) % p;
  }
}

int P[N], a1[N], a2[N], b1[N], b2[N];

inline void solve() {
  int n, a;
  rd(n, a);
  P[1] = a;
  int cnt = 0;
  int tot = 1;
  FOR(i, 2, n + 1) {
    if (tot == a) ++tot;
    P[i] = tot++;
  }
  do {
    a1[1] = a2[1] = P[1];
    b1[n] = b2[n] = P[n];
    FOR(i, 2, n) a1[i] = max(a1[i-1], P[i]), a2[i] = min(a2[i-1], P[i]);
    ROF(i, 1, n) b1[i] = max(b1[i+1], P[i]), b2[i] = min(b2[i+1], P[i]);
    bool k = 1;
    FOR(i, 2, n) {
      if (!((a1[i-1] > P[i] && b1[i+1] > P[i]) || (a2[i-1] < P[i] && b2[i+1] < P[i]))) {
        k = 0;
        break;
      }
    }
    if (k) {
      ++cnt;
    }
  } while (next_permutation(P + 2, P + n + 1));
  println(cnt);
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

