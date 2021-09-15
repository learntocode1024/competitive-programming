/**********************************************************************
 * This file is the c++ solution to a particular CP problem written by
 * misaka18931 and was hosted on GitHub Repository below:
 * URL: https://github.com/misaka18931/competitive-programming
 *
 * Original Author: misaka18931
 * Date: Sep 15, 2021
 * Algorithm:
 * Difficulty:
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
char in[1 << 24];  // sizeof in varied in problem
char const *o;
void init_in() {
  o = in;
  in[fread(in, 1, sizeof(in) - 4, stdin)] = 0;  // set 0 at the end of buffer.
}
int rd() {
  unsigned u = 0, s = 0;
  while (*o && *o <= 32) ++o;  // skip whitespaces...
  if (*o == '-')
    s = ~s, ++o;
  else if (*o == '+')
    ++o;  // skip sign
  while (*o >= '0' && *o <= '9')
    u = (u << 3) + (u << 1) + (*o++ - '0');  // u * 10 = u * 8 + u * 2 :)
  return static_cast<int>((u ^ s) + !!s);
}
char *rdstr(char *s) {
  while (*o && *o <= 32) ++o;
  while (*o > 32) *s++ = *o++;
  *s = '\0';
  return s;
}
}  // namespace IO

/********************************* utility ************************************/
typedef long long i64;
typedef unsigned long long u64;
typedef unsigned int u32;
typedef pair<int, int> pii;
#define pb(x) push_back(x)
#define mkp(x, y) make_pair(x, y)
#define fi first
#define se second
#define FOR(x, y, z) for (int x = y; x < z; ++x)  // always [y, z)
#define ROF(x, y, z) for (int x = z - 1; x >= y; --x)
template <typename T>
void chkmax(T &a, const T &b) {
  a = max(a, b);
}
template <typename T>
void chkmin(T &a, const T &b) {
  a = min(a, b);
}
pii operator+(const pii &a, const pii &b) {
  return mkp(a.fi + b.fi, a.se + b.se);
}

/*********************************** solution *********************************/
using IO::rd;
// #define MULTI
const int N = 705;
vector<int> G[N];
int n;
int sz[N];
int pow2[N * N];
// f(u, cut-count, cluster)
const int mod = 1000000007;

i64 fac[N << 1], ifac[N << 1], _inv[N << 1];

void work() {
  fac[0] = fac[1] = ifac[0] = ifac[1] = _inv[1] = 1ll;
  for (int i = 2; i < N << 1; ++i) {
    _inv[i] = (mod - mod / i) * _inv[mod % i] % mod;
    fac[i] = fac[i - 1] * i % mod;
    ifac[i] = ifac[i - 1] * _inv[i] % mod;
  }
}

inline i64 C(int n, int k) {
  if (k > n || k < 0) return 0;
  return fac[n] * ifac[k] % mod * ifac[n - k] % mod;
}


inline void reduce(int &x) {
  if (x >= mod) x -= mod;
}

int f[N][N], tmpf[N];

void _dfs(int u, int fa, int z) {
  sz[u] = 1;
  f[u][1] = 1;
  for (auto v : G[u]) {
    if (v == fa) continue;
    _dfs(v, u, z);
    for (int j = 1; j <= sz[u]; ++j) {
      for (int l = 1; l <= sz[v]; ++l) {
        int x = 1ll * f[u][j] * f[v][l] % mod;
        reduce(tmpf[j] += 1ll * x * pow2[(l-1)*l/2-l+1] % mod * z % mod);
        reduce(tmpf[j + l] += x);
      }
    }
    sz[u] += sz[v];
    for (int j = 1; j <= sz[u]; ++j) {
      f[u][j] = tmpf[j];
      tmpf[j] = 0;
    }
  }
}
int g[N];
namespace poly {
i64 x[N],y[N],c[N],fs[N],g[N],f[N];

i64 powM(i64 a,i64 t=mod-2){
  i64 ans=1;
  while(t){
    if(t&1)ans=ans*a%mod;
    a=a*a%mod;t>>=1;
  }return ans;
}
void poly() {
  for (int i = 0; i < n; ++i) x[i] = i + 1;
  for (int i=0;i<n;i++){
    c[i]=1;
    for (int j=0;j<n;j++)
      if (i!=j)
        c[i]=c[i]*(x[i]-x[j])%mod;
    c[i]=powM(c[i])*y[i]%mod;
  }
  fs[0]=1;
  for (int i=0;i<n;i++){
    for (int j=n;j;j--)
      fs[j]=(fs[j-1]+fs[j]*(mod-x[i]))%mod;
    fs[0]=fs[0]*(mod-x[i])%mod;
  }
  for (int i=0;i<n;i++){
    i64 buf=powM(mod-x[i]);
    g[0]=fs[0]*buf%mod;
    for (int j=1;j<n;j++)
      g[j]=(fs[j]-g[j-1])*buf%mod;
    for (int j=0;j<n;j++)
      f[j]=(f[j]+c[i]*g[j])%mod;
  }
  for (int i = 0; i < n; ++i) {
    ::g[i] = (f[i] + mod) % mod;
  }
}
}
int ff[N][N];
void solve() {
  n = rd();
  pow2[0] = 1;
  FOR(i, 1, n * n) {
    reduce(pow2[i] = pow2[i - 1] << 1);
  }
  FOR(i, 1, n) {
    int u = rd(), v = rd();
    G[u].pb(v);
    G[v].pb(u);
  }
  for (int i = 1; i <= n; ++i) {
    _dfs(1, 0, i);
    for (int j = 1; j <= n; ++j) ff[i][j] = f[1][j];
    FOR(j, 1, n + 1) FOR(k, 1, n + 1) f[j][k] = 0;
  }
  for (int z = 1; z <= n; ++z) {
    for (int j = 1; j <= n; ++j) {
      poly::y[z - 1] = (poly::y[z - 1] + 1ll * ff[z][j] * pow2[(j-1)*j/2-j+1]) % mod;
    }
  }
  poly::poly();
  for (int i = 0; i < n; ++i) {
    for (int j = 1; i + j < n; ++j) {
      if (j & 1) reduce(g[i] += mod - g[i + j] * C(i + j, i) % mod);
      else reduce(g[i] += g[i + j] * C(i + j, i) % mod);
    }
  }
  for (int i = 0; i < n; ++i) {
    cout << g[i] << ' ';
  }
  cout << '\n';
}

int main() {
  work();
  IO::init_in();
#ifdef MULTI
  int T = IO::rd();
  while (T--) solve();
#else
  solve();
#endif
  return 0;
}
/*
 * checklist:
 * - IO buffer size
 * - potential out-of-bound Errors
 * - inappropriate variable type
 * - potential Arithmetic Error
 * - potential Arithmetic Overflow
 * - typo / logical flaws
 * - clean-up on multiple test cases
 * - sufficient stress tests / random data tests
*/
