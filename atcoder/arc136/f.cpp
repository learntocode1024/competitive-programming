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
const int N = 55, M = N*N;
const int p = 998244353;
inline void red(int &x) {
  if (x >= p) x -= p;
}
int C, h, w, lim;
char s[N][N];
int a[N];
int EXP[M][M<<1], c[M][M], tmp[M<<1];
int val[M];

int q_pow(i64 a, int x) {
  i64 ret = 1;
  while (x) {
    if (x & 1) ret = ret * a % p;
    a = a * a % p;
    x >>= 1;
  }
  return ret;
}

inline int inv(int x) {
  return q_pow(x, p-2);
}

int z = 0, z1;

inline void getEXP() {
  FOR(i, 0, C+1) c[i][0] = 1;
  FOR(i, 1, C+1) FOR(j, 1, i+1) c[i][j] = (c[i-1][j-1] + c[i-1][j]) % p;
  for (int k = 0; k < lim; k += 2) {
    EXP[C][k] = c[C][k/2];
  }
  ROF(i, 0, C) {
    FOR(j, 0, lim) tmp[j] = EXP[i+1][j];
    ROF(j, 1, lim - 1) {
      int val = tmp[j+1];
      red(tmp[j+1] += p - val);
      red(tmp[j-1] += p - val);
      red(EXP[i][j+1] += val);
      red(EXP[i][j-1] += p - val);
    }
  }
  FOR(k, 0, C+1) {
    FOR(i, 0, lim-1) {
      int a = 1ll * (i - C + p) * inv(C) % p;
      red(val[k] += 1ll * inv(a+p-1) * EXP[k][i] % p);
    }
    red(val[k] += EXP[k][lim-1]);
  }
}

int f[N][M];

inline int getf() {
  f[0][0] = 1;
  FOR(i, 1, h + 1) {
    int del = a[i];
    int c0 = 0, c1 = 0;
    FOR(j, 0, w) if (s[i][j] == '1') --del, ++c1;
    c0 = w - c1;
    for (int j = 0; j <= (i-1)*w; ++j) {
      for (int k = max(0, del); k <= min(c0, del + c1); ++k) {
        red(f[i][j+w-k-k+del] += 1ll * f[i-1][j] * c[c0][k] % p * c[c1][k-del] % p);
      }
    }
  }
  int ans = 0;
  FOR(i, 0, C + 1) {
    red(ans += 1ll * f[h][i] * val[i] % p);
  }
  FOR(i, 0, C + 1) {
    red(z1 += 1ll * f[h][i] * EXP[i][lim-1] % p);
  }
  return ans;
}

int g[N][M];

inline int getg() {
  g[0][0] = 1;
  FOR(i, 1, h + 1) {
    int del = 0;
    int c0 = w-a[i], c1 = a[i];
    for (int j = 0; j <= (i-1)*w; ++j) {
      for (int k = max(0, del); k <= min(c0, del + c1); ++k) {
        red(g[i][j+w-k-k+del] += 1ll * g[i-1][j] * c[c0][k] % p * c[c1][k-del] % p);
      }
    }
  }
  int ans = 0;
  FOR(i, 0, C + 1) {
    red(ans += 1ll * g[h][i] * val[i] % p);
  }
  FOR(i, 0, C + 1) {
    red(z += 1ll * g[h][i] * EXP[i][lim-1] % p);
  }
  return ans;
}

inline void solve() {
  rd(h, w);
  C = h * w;
  lim = C << 1 | 1;
  FOR(i, 0, h) rd(s[i+1]);
  FOR(i, 0, h) rd(a[i+1]);
  getEXP();
  int x = getf();
  int y = getg();
  assert(z==z1);
  println(1ll * (x-y+p) * inv(z) % p * inv(q_pow(2, C)) % p);
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

