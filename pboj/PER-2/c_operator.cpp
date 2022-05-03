#include <bits/stdc++.h>
#include "operator.h"
namespace {
using namespace std;
template <typename T> inline void O(const T &x) { cout << x << '\n'; }
template <typename T, typename... W> inline void O(const T &x, const W &...b) {
  cout << x << ' ';
  O(b...);
}
template <typename T> inline void rd(const T &x) { cin >> x; }
template <typename T, typename... W> inline void rd(const T &x, const W &...b) {
  cin >> x;
  rd(b...);
}
#ifndef MISAKA
#define err(...)
#else
#define err(...) fprintf(stderr, __VA_ARGS__)
#endif
typedef long long i64;
typedef unsigned long long u64;
typedef unsigned u32;
typedef long double dbl;
typedef pair<int, int> pii;
typedef uniform_int_distribution<int> r32;
typedef uniform_int_distribution<i64> r64;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
#define shuf(L, R) shuffle((L), (R), rng)
#define fi first
#define se second
#define pb push_back
#define eb emplace_back
#define FOR(i, j, k) for (int i = (j); i <= (k); ++i)
#define ROF(i, j, k) for (int i = (k); i >= (j); --i)
template <typename T> inline void ckmin(T &a, const T &b) { a = min(a, b); }
template <typename T> inline void ckmax(T &a, const T &b) { a = max(a, b); }
//#define IOFILE "filename"
//#define MULTI

const int a[16] = {0,242409326,307274348,869671415,66746939,771487115,190657859,421741849,957930937,956231038,243819937,691787647,698223205,539227763,498803434,405420617};
const int P = 1e9+7;
map<int,int> S;
inline bool calc() {
  S.clear();
  FOR(u,0,1<<(16-1)) {
    int x = a[0];
    FOR(i,0,16-2) {
      if ((u>>i)&1) x = 1ll * x * a[i+1] % P;
      else x = (x + a[i+1]) % P;
    }
    S[x] = u;
  }
  err("%ld\n", S.size());
  return S.size() == (1<<(16-1));
}
int n;
vector<int> ans;
void ask(int l, int r) {
  vector<int> f(n+1);
  for (int i = r + 1; i < n; ++i) {
    f[i+1] = ans[i];
  }
  for (int i = r; i >= max(l, 0); --i) {
    f[i+1] = a[15 + i - r];
  }
  int u = S[query(f)];
  for (int i = r; i >= max(l, 0); --i) {
    ans[i] = (u>>(14-r+i))&1;
  }
}
}

std::vector <int> solve(int _n) {
  assert(calc());
  ans.resize(_n);
  n = _n;
  for (int i = n - 1; i >= 0; i -= 15) {
    ask(i-14, i);
  }
  return ans;
}
