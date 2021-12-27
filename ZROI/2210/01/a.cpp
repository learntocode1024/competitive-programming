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
const int N = 2e5+5, H = 1 << 19;
const int p = 998244353;
int fac[H]= {1, 1}, ifac[H] = {1, 1}, inv[H] = {0, 1};
char s[N];
int b[N], h[N];
int g3[H] = {1, 363395222};
int bi[H];
int n;
int f[H];
int A[H], B[H];

void dft(int *a, int lim) {
  FOR(i, 0, lim) if (i < bi[i]) swap(a[i], a[bi[i]]);
  for (int i = 1; i < lim; i <<= 1) {
    int gn = g3[H/i/2];
    for (int j = 0; j < lim; j += i << 1) {
      i64 g = 1;
      for (int k = j; k < j + i; ++k) {
        int x = a[k], y = 1ll * a[k + i] * g % p;
        a[k] = (x + y) % p;
        a[k + i] = (x + p - y) % p;
        g = g * gn % p;
      }
    }
  }
}

inline void idft(int *a, int lim) {
  reverse(a + 1, a + lim);
  dft(a, lim);
  i64 r = inv[lim];
  FOR(i, 0, lim) a[i] = a[i] * r % p;
}

inline int wrap(int x) {
  if ((x & -x) == 0) return x;
  return 1 << (32 - __builtin_clz(x));
}

void cdq(int l, int r) {
  if (r - l == 1) {
    if (l) {
      if (b[l]) f[l] = (p - f[l]) % p;
      else f[l] = 0;
    }
    return;
  }
  int mid = (l + r) >> 1;
  cdq(l, mid);
  FOR(i, 1, r - l) B[i] = ifac[i];
  FOR(i, l, mid) A[i - l] = f[i];
  int lim = wrap(r + mid - 2 * l);
  FOR(i, 1, lim) {
    bi[i] = bi[i>>1]>>1;
    if (i & 1) bi[i] |= lim >> 1;
  }
  dft(A, lim);
  dft(B, lim);
  FOR(i, 0, lim) A[i] = 1ll * A[i] * B[i] % p;
  idft(A, lim);
  FOR(i, mid, r) {
    f[i] = (f[i] + A[i - l]) % p;
  }
  FOR(i, 0, lim) A[i] = B[i] = 0;
  cdq(mid, r);
}

inline int work(int n) {
  if (n == 1) return 1;
  b[n] = 1;
  FOR(i, 1, n + 1) f[i] = 0;
  FOR(i, 1, n + 1) h[i] = h[i - 1] + b[i];
  f[0] = 1;
  cdq(0, n + 1);
  if (h[n] & 1) f[n] = (p - f[n]) % p;
  return f[n];
}

inline void solve() {
  cin >> n >> (s+1);
  int l = 0;
  int ans = 1;
  s[n + 1] = '?';
  for (int i = 1; i <= n + 1; ++i) {
    if (s[i] == '?') {
      FOR(t, l + 1, i) b[t - l] = (s[t] - '0') ^ 1;
      ans = 1ll * ans * work(i - l) % p;
      l = i;
    }
  }
  println(1ll * ans * fac[n + 1] % p);
}

int main() {
  FOR(i, 2, H) fac[i] = 1ll * fac[i-1] * i % p, inv[i] = 1ll * (p - p / i) * inv[p % i] % p, ifac[i] = 1ll * ifac[i - 1] * inv[i] % p;
  FOR(i, 2, H) {
    g3[i] = 1ll * g3[i-1] * g3[1] % p;
  }
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

