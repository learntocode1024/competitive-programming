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
const int N = 55, M = 305, Q = 1e7+5;
int f[N];
int n, m;
int a[M], b[M], w[M], o[M];
int vl[M*M], cgt[M*M], tot;
i64 ans[M*M];
int get(int x) {
  return (x == f[x]) ? x : (f[x] = get(f[x]));
}

bool merge(int u, int v) {
  u = get(u); v = get(v);
  if (u == v) return 0;
  f[u] = v;
  return 1;
}

inline void solve() {
  cin >> n >> m;
  vl[1] = 1e8+7;
  tot = 2;
  FOR(i, 0, m) rd(a[i], b[i], w[i]);
  FOR(i, 0, m) vl[tot++] = w[i]+1;
  FOR(i, 0, m) FOR(j, i+1, m) vl[tot++] = (w[i]+w[j])/2+1;
  sort(vl, vl+tot);
  tot = unique(vl, vl+tot) - vl;
  FOR(_, 0, tot) {
    int cv = vl[_];
    i64 &ret = ans[_];
    int &cc = cgt[_];
    iota(f + 1, f + n + 1, 1);
    iota(o, o + m, 0);
    sort(o, o + m, [cv] (int a, int b) { return abs(w[a]-cv) < abs(w[b]-cv); });
    for (int i = 0, cnt = 0; i < m && cnt < n - 1; ++i) {
      int id = o[i];
      if (merge(a[id], b[id])) {
        ++cnt;
        ret += abs(w[id] - cv);
        if (w[id] >= cv) ++cc;
      }
    }
    cc = 2 * cc - n + 1;
  }
  int A, B, C, p, k;
  rd(p, k, A, B, C);
  int q;
  i64 res = 0;
  FOR(_, 0, p) {
    cin >> q;
    int i = upper_bound(vl, vl + tot, q) - vl - 1;
    res ^= (ans[i] + 1ll * (vl[i] - q) * cgt[i]);
  }
  FOR(_, p, k) {
    q = (1ll * q * A + B) % C;
    int i = upper_bound(vl, vl + tot, q) - vl - 1;
    res ^= (ans[i] + 1ll * (vl[i] - q) * cgt[i]);
  }
  println(res);
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

