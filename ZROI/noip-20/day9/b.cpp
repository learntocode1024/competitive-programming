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
typedef long double f80;
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

const int N = 2e5+5;
const int p = 1e9+7;

inline i64 q_pow(i64 a, int x) {
  i64 ret = 1;
  while (x) {
    if (x & 1) ret = ret * a % p;
    a = a * a % p;
    x >>= 1;
  }
  return ret;
}

inline i64 inv(i64 a) { return q_pow(a % p, p - 2); }

int n, k, m;
int a[N];
int d1[N];
struct frac {
  i64 p;
  __int128 q, r;
  int id;
  frac() = default;
  frac(int _q, int _p, int _id) {
    p = _p;
    q = _q;
    id = _id;
  }
  bool operator< (const frac &rhs) const {
    return q > rhs.q;
  }
} d2[N];
vector<frac> d2t[N];
int d3[N];
int tt2, tt3;

i64 ca[N];
i64 a1[N];
f80 l1[N];
i64 a2[N];
f80 l2[N];

inline void solve() {
  cin >> k >> n >> m;
  FOR(i, 1, k + 1) cin >> a[i];
  FOR(_, 0, n) {
    int t, i, b;
    cin >> t >> i >> b;
    if (!b) continue;
    if (t == 1) {
      chkmax(d1[i], b - a[i]);
    } else if (t == 2) {
     d2t[i].pb(frac(b, a[i], i));
    } else {
      d3[tt3++] = b;
    }
  }
  FOR(i, 1, k + 1) {
    if (d1[i] > 0) {
     d2t[i].pb(frac(d1[i], a[i], i));
    }
  }
  FOR(i, 1, k + 1) {
    sort(begin(d2t[i]), end(d2t[i]));
    reverse(begin(d2t[i]), end(d2t[i]));
    i64 caa = a[i];
    for (auto v : d2t[i]) {
      auto f = v;
      f.p = caa + v.q;
      f.r = caa;
      caa += v.q;
      d2[tt2++] = f;
    }
  }
  sort(d2, d2 + tt2, [] (auto a, auto b) { return a.p * b.r > b.p * a.r; });
  sort(d3, d3 + tt3);
  reverse(d3, d3 + tt3);
  a1[0] = 1;
  FOR(i, 1, k + 1) {
    ca[i] = a[i];
    a1[0] = a1[0] * a[i] % p;
    l1[0] += log2((f80)a[i]);
  }
  int tot_1e9a7 = 0;
  i64 bak_1e9a7 = 0;
  FOR(i, 0, tt2) {
    l1[i + 1] = l1[i] - log2((f80)ca[d2[i].id]);
    i64 iv = inv(ca[d2[i].id]);
    if (iv) a1[i + 1] = a1[i] * iv % p;
    else {
      --tot_1e9a7;
      if (!tot_1e9a7) a1[i + 1] = bak_1e9a7;
    }
    if (tot_1e9a7 && iv) {
      bak_1e9a7 = bak_1e9a7 * iv % p;
    }
    ca[d2[i].id] += d2[i].q;
    l1[i + 1] += log2((f80)ca[d2[i].id]);
    if (ca[d2[i].id] % p && !tot_1e9a7) a1[i + 1] = a1[i + 1] * ca[d2[i].id] % p;
    else if (ca[d2[i].id] % p == 0 && !tot_1e9a7) {
      bak_1e9a7 = a1[i + 1];
      a1[i + 1] = 0;
      tot_1e9a7 = 1;
    } else {
      if (ca[d2[i].id] % p) bak_1e9a7 = bak_1e9a7 * ca[d2[i].id] % p;
      else ++tot_1e9a7;
    }
  }
  a2[0] = 1;
  FOR(i, 0, tt3) {
    a2[i + 1] = a2[i] * d3[i] % p;
    l2[i + 1] = l2[i] + log2((f80)d3[i]);
  }
  f80 mxl = 0;
  i64 ans = 1;
  for (int i = 0; i <= min(m, tt2); ++i) {
    int r = min(m - i, tt3);
    i64 cur = a1[i] * a2[r] % p;
    f80 cul = l1[i] + l2[r];
    if (cul - mxl > LDBL_EPSILON) {
      mxl = cul;
      ans = cur;
    }
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

