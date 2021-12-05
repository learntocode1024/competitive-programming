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

const int N = 1<<18;
const int p = 998244353;
int n, tot;
vector<int> g[N];

int a[N];
i64 pw[N], fac[N] = {0, 1}, A[N], B[N], iv[N];
void dfs(int u, int fa) {
  a[tot++] = g[u].size() - 1;
  for (auto v : g[u]) if (v != fa) dfs(v, u);
}

i64 q_pow(i64 a, int x) {
  i64 ret = 1;
  while (x) {
    if (x & 1) ret = ret * a % p;
    a = a * a % p;
    x >>= 1;
  }
  return ret;
}

void fft(i64 *a, int len) {
  FOR(i, 0, len) if (i < iv[i]) swap(a[i], a[iv[i]]);
  for (int i = 1; i < len; i <<= 1) {
    i64 wn = pw[N/i/2];
    for (int j = 0; j < len; j += i << 1) {
      i64 w = 1;
      for (int k = j; k < j + i; ++k) {
        i64 x = a[k], y = a[k + i] * w % p;
        a[k] = (x + y) % p;
        a[k + i] = (x + p - y) % p;
        w = w * wn % p;
      }
    }
  }
}

inline void idft(i64 *a, int len) {
  fft(a, len);
  reverse(a + 1, a + len);
  i64 rt = q_pow(len, p - 2);
  FOR(i, 0, len) a[i] = a[i] * rt % p;
}

vector<int> work(int l, int r) {
  if (r - l == 1) return {1, a[l]};
  int mid = (l + r) >> 1;
  auto a1 = work(l, mid), a2 = work(mid, r);
  int l1 = a1.size(), l2 = a2.size();
  FOR(i, 0, l1) A[i] = a1[i];
  FOR(i, 0, l2) B[i] = a2[i];
  int L = 1;
  while (L < l1 + l2 - 1) L <<= 1;
  FOR(i, 1, L) {
    iv[i] = iv[i>>1]>>1;
    if (i & 1) iv[i] |= L >> 1;
  }
  fft(A, L);
  fft(B, L);
  FOR(i, 0, L) A[i] = A[i] * B[i] % p;
  idft(A, L);
  vector<int> ret(l1 + l2 - 1);
  FOR(i, 0, ret.size()) ret[i] = A[i];
  FOR(i, 0, L) A[i] = B[i] = 0;
  return ret;
}

inline void solve() {
  pw[0] = 1;
  pw[1] = q_pow(3, (p - 1) / N);
  FOR(i, 2, N) pw[i] = pw[i - 1] * pw[1] % p;
  cin >> n;
  FOR(i, 1, n) {
    int u, v;
    rd(u, v);
    g[u].pb(v);
    g[v].pb(u);
  }
  dfs(1, 0);
  ++a[0];
  sort(a, a + tot, greater<int>());
  while (a[tot - 1] == 0) --tot;
  auto c = work(0, tot);
  int ans = 0;
  FOR(i, 2, n + 1) fac[i] = fac[i - 1] * i % p;
  FOR(i, 0, c.size()) {
    int cur = 1ll * fac[n - i] * c[i] % p;
    if (i & 1) cur = p - cur;
    ans = (ans + cur) % p;
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

