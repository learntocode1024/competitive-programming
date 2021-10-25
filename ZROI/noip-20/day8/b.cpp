#include <bits/stdc++.h>
using namespace std;
typedef long long i64;
typedef unsigned long long u64;
typedef unsigned u32;
typedef pair<int, int> pii;
typedef pair<i64, i64> pll;
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

const int N = 2505;
int n;
struct vec {
  i64 x, y, z;
  inline void init() {
    cin >> x >> y >> z;
    if (x < 0) {
      x = -x, y = -y, z = -z;
    }
  }
  bool operator< (const vec &rhs) const {
    return x > rhs.x;
  }
} a[N];

inline u64 reduce(vec s, vec t) {
  i64 x, y;
  if (t.x) {
    i64 g = __gcd(t.x, s.x);
    i64 cs = t.x / g;
    i64 ct = - (s.x / g);
    x = cs * s.y + ct * t.y;
    y = cs * s.z + ct * t.z;
  } else {
    x = t.y;
    y = t.z;
  }
  if (x == 0 && y == 0) ;
  else if (x == 0) y = 1;
  else if (y == 0) x = 1;
  else {
    if (x < 0) x = -x, y = -y;
    i64 gg = __gcd(x, abs(y));
    x /= gg;
    y /= gg;
  }
  return (x ^ 114514) * (y ^ 1919810);
}

inline void solve() {
  cin >> n;
  FOR(i, 0, n) a[i].init();
  sort(a, a + n);
  i64 ans = 0;
  for (int i = 0; i < n; ++i) {
    unordered_map<u64, int> S;
    if (!a[i].x) break;
    for (int j = i + 1; j < n; ++j) {
      S[reduce(a[i], a[j])] += 1;
    }
    if (S.size() > 1) {
      i64 cur = 1ll * (n - i - 1) * (n - i - 2) / 2;
      if (S.find(114514ull * 1919810ull) != S.end()) {
        i64 x = n - i - 1;
        x -= S[114514ull * 1919810ull];
        cur = x * (x - 1) / 2;
        S.erase(114514ull * 1919810ull);
      }
      for (auto v : S) {
        cur -= 1ll * (v.se - 1) * v.se / 2;
      }
      ans += cur;
    }
    //for (auto v : S) {
      //cerr << v.fi.fi << ' ' << v.fi.se << '\n';
    //}
    //cerr << "==============\n";
  }
  cout << ans << '\n';
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

