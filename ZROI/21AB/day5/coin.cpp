/**********************************************************************
 * This file is the c++ solution to a particular CP problem written by
 * misaka18931 and was hosted on GitHub Repository below:
 * URL: https://github.com/misaka18931/competitive-programming
 *
 * Original Author: misaka18931
 * Date: Aug  9, 2021
 * Algorithm: FFT, dp
 * Difficulty: high
 *
 *********************************************************************/

#include <algorithm>
#include <cctype>
#include <climits>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

/********************************** buffer IO *********************************/
namespace IO {
char in[1 << 23]; // sizeof in varied in problem
char const *o;

void init_in() {
  o = in;
  in[fread(in, 1, sizeof(in) - 4, stdin)] = 0; // set 0 at the end of buffer.
}

int rd() {
  unsigned u = 0, s = 0;

  while (*o && *o <= 32)
    ++o; // skip whitespaces...

  if (*o == '-')
    s = ~s, ++o;
  else if (*o == '+')
    ++o; // skip sign

  while (*o >= '0' && *o <= '9')
    u = (u << 3) + (u << 1) + (*o++ - '0'); // u * 10 = u * 8 + u * 2 :)

  return static_cast<int>((u ^ s) + !!s);
}

char *rdstr(char *s) {
  while (*o && *o <= 32)
    ++o;
  while (*o > 32)
    *s++ = *o++;
  return s;
}
} // namespace IO

/********************************* macros *************************************/
typedef long long i64;
typedef unsigned long long u64;
typedef unsigned int u32;
#define pb(x) push_back(x)
#define fi first
#define se second
#define REP(x, y, z) for (int x = y; x < z; ++x) // always [y, z)
#define PER(x, y, z) for (int x = z - 1; x >= y; --x)
template <typename T> void chkmax(T &a, const T &b) { a = max(a, b); }
template <typename T> void chkmin(T &a, const T &b) { a = min(a, b); }

/*********************************** solution *********************************/
using IO::rd;
#define MX 100005
int n, m;
int a[MX], b[MX];
pair<int, int> c[MX];

const int N = 1 << 20;
const i64 mod = 998244353;
i64 pp[N];
u32 inv[N];
i64 Q_pow(i64 a, int b) {
  i64 ret = 1;
  while (b) {
    if (b & 1)
      ret = ret * a % mod;
    a = a * a % mod;
    b >>= 1;
  }
  return ret;
}
void dft(i64 a[], int len) {
  for (int i = 1; i < len; ++i) {
    inv[i] = inv[i >> 1] >> 1;
    if (i & 1)
      inv[i] |= (len >> 1);
    if (i < inv[i])
      swap(a[i], a[inv[i]]);
  }
  for (int i = 1; i < len; i <<= 1) {
    i64 wn = pp[N / i / 2];
    for (int j = 0; j < len; j += i << 1) {
      i64 w = 1;
      for (int k = j; k < j + i; ++k) {
        i64 x = a[k], y = a[k + i] * w % mod;
        a[k] = (x + y) % mod;
        a[k + i] = (x - y + mod) % mod;
        w = w * wn % mod;
      }
    }
  }
}

void idft(i64 a[], int len) {
  dft(a, len);
  i64 f = Q_pow(len, mod - 2);
  for (int i = 0; i < len; ++i) {
    a[i] = a[i] * f % mod;
  }
  reverse(a + 1, a + len);
}

int wrap(int x) {
  return 1 << (32 - __builtin_clz(x));
}
i64 A[N], B[N];

typedef vector<i64> poly;
poly operator*(const poly &a, const poly &b) {
  int n = a.size(), m = b.size();
  poly ret(n + m - 1);
  int lim = wrap(n + m - 1);
  for (int i = 0; i < n; ++i) A[i] = a[i];
  for (int i = 0; i < m; ++i) B[i] = b[i];
  dft(A, lim);
  dft(B, lim);
  for (int i = 0; i < lim; ++i) A[i] = A[i] * B[i] % mod;
  idft(A, lim);
  for (int i = 0; i < n + m - 1; ++i) ret[i] = A[i];
  for (int i = 0; i < lim; ++i) A[i] = B[i] = 0;
  return ret;
}

int lim[MX];

poly prod(int l, int r) {
  if (r - l == 1) {
    poly ret(c[l].se + 1);
    ret[0] = ret[c[l].se] = 1;
    return ret;
  }
  int mid = l + (r - l) / 2;
  auto a = prod(l, mid);
  auto b = prod(mid, r);
  return a * b;
}

void shrink(poly &a, int len) {
  while (a.size() > len) a.pop_back();
  poly(a).swap(a);
}

void solve() {
  pp[0] = 1;
  i64 g = Q_pow(3, (mod - 1) >> 20);
  for (int i = 1; i < N; ++i) {
    pp[i] = pp[i - 1] * g % mod;
  }
  n = rd(), m = rd();
  for (int i = 0; i < n - 1; ++i) a[i] = rd();
  a[n - 1] = 1;
  for (int i = 0; i < n; ++i) b[i] = rd();
  for (int i = 0; i < m; ++i) c[i].se = rd(), c[i].fi = rd(), --c[i].fi;
  sort(c, c + m);
  for (int i = 0; i < m; ++i) {
    lim[c[i].fi] += c[i].se;
  }
  for (int i = 0; i < n - 1; ++i) {
    lim[i + 1] += lim[i] / a[i] + (lim[i] % a[i] != 0);
  }
  static poly f(1);
  f[0] = 1;
  i64 lt, rt;
  lt = rt = m;
  int B = 0;
  i64 ans = 0;
  for (int i = n - 1; i >= 0; --i) {
    rt = lt;
    while (lt && c[lt - 1].fi == i) --lt;
    poly g(lim[i] + 1);
    int d = f.size();
    B = B * a[i] + b[i];
    for (int j = 0; i < d && j * a[i] <= (B - lim[i]); ++j) {
      ans = (ans + f[j] * Q_pow(2, rt)) % mod;
    } // toss
    int shift = max(0, B - lim[i]);
    for (int j = shift > 0 ? (B - lim[i]) / a[i] + 1 : 0; j < d; ++j) {
      g[j * a[i] - shift] = f[j];
    }
    f.swap(g);
    B -= shift;
    if (rt > lt) f = f * prod(lt, rt);
    shrink(f, B + 1);
  }
  for (int i = 0; i <= B; ++i) {
    ans = (ans + f[i]) % mod;
  }
  cout << ans << '\n';
}

int main() {
  IO::init_in();
#ifdef MULTI
  int T = IO::rd();
  while (T--)
    solve(), T && (clear(), 1);
#else
  solve();
#endif
  return 0;
}
