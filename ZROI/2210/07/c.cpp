#include <bits/stdc++.h>
using namespace std;
#ifndef MISAKA
#define OO(x)
#else
#define OO(x) cout << __PRETTY_FUNCTION__ << ": " << #x << " : " << (x) << '\n';
#endif
template <typename T>
void rd(T &a) {
  cin >> a;
}
template <typename A, typename... B>
void rd(A &a, B &...b) {
  cin >> a;
  rd(b...);
}
template <typename A>
void O(const A &a) {
  cout << a << '\n';
}
template <typename A, typename... B>
void O(const A &a, const B &...b) {
  cout << a << ' ';
  O(b...);
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
#define ROF(i, j, k) for (int i = (k - 1); i >= (j); --i)
template <typename T>
inline void chkmin(T &a, const T b) {
  a = min(a, b);
}
template <typename T>
inline void chkmax(T &a, const T b) {
  a = max(a, b);
}

//#define MULTI
const int N = 1 << 17;
const int p = 998244353;
int f[N], g[N];
int lim, m;

inline i64 q_pow(i64 x, int a) {
  i64 ret = 1;
  while (a) {
    if (a & 1) ret = ret * x % p;
    x = x * x % p;
    a >>= 1;
  }
  return ret;
}

inline i64 inv(int x) { return q_pow(x, p - 2); }

inline void fwt(int *a) {
  for (int i = 1; i < lim; i <<= 1) {
    for (int j = 0; j < lim; j += i << 1) {
      for (int k = j; k < j + i; ++k) {
        int x = a[k], y = a[k + i];
        a[k] = (x + y) % p;
        a[k + i] = (x + p - y) % p;
      }
    }
  }
}
i64 gp[N], iv[N];

inline int wrap(int x) {
  return (x == (x & -x)) ? x : 1u << (32 - __builtin_clz(x));
};
inline void red(i64 &x) {
  if (x >= p) x -= p;
}

u32 bit_inv[N];

i64 _c[N], A[N], B[N];
i64 _h[N], _f[N];
i64 *a;

void dft(i64 *a, int len) {
  for (int i = 1; i < len; ++i) {
    bit_inv[i] = bit_inv[i >> 1] >> 1;
    if (i & 1) bit_inv[i] |= len >> 1;
    if (bit_inv[i] > i) swap(a[i], a[bit_inv[i]]);
  }
  for (int i = 1; i < len; i <<= 1) {
    i64 wn = gp[N / i / 2];
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

void mul(i64 *a, i64 *b, int len) {  // A, B
  FOR(i, 0, len) A[i] = a[i], B[i] = b[i];
  int lim = wrap(len);
  dft(A, lim);
  dft(B, lim);
  FOR(i, 0, lim) A[i] = A[i] * A[i] % p;
  idft(A, lim);
  FOR(i, 0, len) a[i] = A[i];
  FOR(i, 0, lim) A[i] = B[i] = 0;
}

void cdq(int l, int r) {  // _c A B
  if (r == l + 1) {
    if (l) _c[l] = _c[l] * iv[l] % p;
    return;
  }
  int mid = (l + r) >> 1;
  cdq(l, mid);
  FOR(i, l, mid) A[i - l] = _c[i];
  FOR(i, 0, r - l) B[i] = a[i];
  int lim = wrap(mid + r - 2 * l);
  dft(A, lim);
  dft(B, lim);
  FOR(i, 0, lim) A[i] = A[i] * B[i] % p;
  idft(A, lim);
  FOR(i, mid, r) red(_c[i] += A[i - l]);
  FOR(i, 0, lim) A[i] = B[i] = 0;
  cdq(mid, r);
}

void exp(i64 *a, int len) {  // |_c A B| _c, A, B
  _c[0] = 1;
  for (int i = 0; i < len; ++i) {
    a[i] = i * a[i] % p;
  }
  ::a = a;
  cdq(0, len);
  for (int i = 0; i < len; ++i) {
    a[i] = _c[i];
    _c[i] = 0;
  }
}

void init() {
  i64 w = q_pow(3, (p - 1) / N);
  gp[0] = 1;
  FOR(i, 1, N) gp[i] = gp[i - 1] * w % p;
  iv[1] = 1;
  FOR(i, 2, N) iv[i] = (p - p / i) * iv[p % i] % p;
}

i64 F[N];

inline int pset(int a, int b) {
  FOR(i, 0, m + 5) F[i] = 0;
  b = (p - b) % p;
  FOR(i, 1, m + 1) {
    if (i & 1)
      F[i] = 1ll * a * iv[i] % p;
    else
      F[i] = 1ll * b * iv[i] % p;
  }
  exp(F, m + 1);
  return F[m];
}

inline void ifwt(int *a) {
  fwt(a);
  i64 iv = inv(lim);
  FOR(i, 0, lim) a[i] = a[i] * iv % p;
}

inline int get(int a) { return 0; }

namespace f1 {
typedef i64 LL;
LL temp[N];

void mul(LL *f, int len,
         LL t) {  // len为多项式的次数+1，函数让多项式f变成f*(x+t)

  for (int i = len; i > 0; --i) {
    temp[i] = f[i];

    f[i] = f[i - 1];
  }

  temp[0] = f[0], f[0] = 0;

  for (int i = 0; i <= len; ++i) {
    f[i] = (f[i] + t * temp[i]) % p;
  }
}

void dev(LL *f, LL *r, LL t,
         int len) {  // f是被除多项式的系数，r保存f除以x+t的结果 len是最高次项

  for (int i = 0; i <= len; ++i) {
    temp[i] = f[i];
  }

  for (int i = len; i > 0; --i) {
    r[i - 1] = temp[i];

    temp[i - 1] = (temp[i - 1] - t * temp[i]) % p;
  }

  return;
}

LL a[N], b[N], c[N];
LL x[N], y[N];  // x,y输入从 1开始到n
int n;
void lglr() {
  memset(a, 0, sizeof(a));
  b[1] = 1, b[0] = -x[1];
  for (int i = 2; i <= n; ++i) {
    mul(b, i, -x[i]);
  }  //预处理(x-x1)*(x-x2)...*(x-xn)
  for (int i = 1; i <= n; ++i) {
    LL fz = 1;
    for (int j = 1; j <= n; ++j) {
      if (j == i) continue;
      fz = fz * (x[i] - x[j]) % p;
    }
    fz = q_pow(fz, p - 2);
    fz = fz * y[i] % p;  //得到多项式系数
    dev(b, c, -x[i], n);   //得到多项式，保存在b数组
    for (int j = 0; j < n; ++j) a[j] = (a[j] + fz * c[j]) % p;
  }
}

LL cal(LL k) {  //计算第x=k值
  LL ans = 0;
  LL res = 1;
  for (int i = 0; i < n; ++i) {
    ans = (ans + res * a[i]) % p;
    res = res * k % p;
  }
  ans = (ans + p) % p;
  return ans;
}
}  // namespace f1

int h[N];

inline void solve() {
  int n;
  rd(n, m, lim);
  // prep: PSET
  init();
  // calc
  FOR(i, 0, n) {
    int x;
    rd(x);
    ++f[x];
  }
  fwt(f);
  FOR(i, 1, m + 2) { f1::y[i] = pset(i, n), f1::x[i] = i; }
  f1::n = m+1;
  f1::lglr();
  FOR(i, 0, lim) { g[i] = f1::cal(f[i]); }
  ifwt(g);
  FOR(i, 0, lim) cout << g[i] << " \n"[i == lim - 1];
}

int main() {
#ifndef MISAKA
  // freopen(".in", "r", stdin);
  // freopen(".out", "w", stdout);
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
