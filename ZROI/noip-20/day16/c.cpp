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

const int N = 1 << 21;
const i64 p = 998244353;
i64 gp[N], iv[N];

i64 q_pow(i64 x, int y) {
  i64 ret = 1;
  while (y) {
    if (y & 1) ret = ret * x % p;
    x = x * x % p;
    y >>= 1;
  }
  return ret;
}

inline int wrap(int x) { return (x == (x & -x)) ? x : 1u << (32 - __builtin_clz(x)); };
inline void red(i64 &x) { if (x >= p) x -= p; }

u32 bit_inv[N];

i64 _c[N], A[N], B[N];
i64 _h[N], _f[N];

void dft(i64 *a, int len) {
  for (int i = 1; i < len; ++i) {
    bit_inv[i] = bit_inv[i>>1]>>1;
    if (i & 1) bit_inv[i] |= len >> 1;
    if (bit_inv[i] > i) swap(a[i], a[bit_inv[i]]);
  }
  for (int i = 1; i < len; i <<= 1) {
    i64 wn = gp[N/i/2];
    for (int j = 0; j < len; j += i << 1) {
      i64 w = 1;
      for (int k = j; k < j + i; ++k) {
        i64 x = a[k], y = a[k + i] * w % p;
        red(a[k] = x + y);
        red(a[k + i] = x + p - y);
        w = w * wn % p;
      }
    }
  }
}

void idft(i64 *a, int len) {
  dft(a, len);
  reverse(a + 1, a + len);
  i64 t = q_pow(len, p - 2);
  FOR(i, 0, len) a[i] = a[i] * t % p;
}
void mul(i64 *a, i64 *b, int len) { // A, B
  FOR(i, 0, len) A[i] = a[i], B[i] = b[i];
  int lim = wrap(len);
  dft(A, lim);
  dft(B, lim);
  FOR(i, 0, lim) A[i] = A[i] * B[i] % p;
  idft(A, lim);
  FOR(i, 0, len) a[i] = A[i];
  FOR(i, 0, lim) A[i] = B[i] = 0;
}
i64 ifac[N] = {1, 1};
void init() {
  i64 w = q_pow(3, (p-1)/N);
  gp[0] = 1;
  FOR(i, 1, N) gp[i] = gp[i-1] * w % p;
  iv[1] = 1;
  FOR(i, 2, N) iv[i] = (p - p / i) * iv[p % i] % p, ifac[i] = ifac[i - 1] * iv[i] % p;
}
int n;
i64 a[N], b[N];
inline void solve() {
  cin >> n;
  i64 ans = 1;
  FOR(i, 1, n + 1) ans = ans * ifac[i] % p;
  FOR(i, 0, n) {
    int ai;
    cin >> ai;
    ++ai;
    ans = ans * ai % p;
    a[ai] = 1;
    b[N/2-ai] = 1;
  }
  mul(a, b, N);
  FOR(i, N / 2 + 1, N) {
    if (a[i]) ans = ans * q_pow(i - N/2, a[i]) % p;
  }
  println(ans);
}

int main() {
  init();
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

