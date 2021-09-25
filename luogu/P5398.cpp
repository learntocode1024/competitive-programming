/**********************************************************************
 * This file is the c++ solution to a particular CP problem written by
 * misaka18931 and was hosted on GitHub Repository below:
 * URL: https://github.com/misaka18931/competitive-programming
 *
 * Original Author: misaka18931
 * Date:
 * Algorithm:
 * Difficulty:
 *
 *********************************************************************/

#include <algorithm>
#include <cctype>
#include <climits>
#include <cmath>
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
#define eb emplace_back
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
const int N = 500005;
const int B = 610;
int T = 74;
int n, m, k;
int a[N], disc[N];
i64 pre[N];                                                                                                                                                                                          
int maxa;

struct qry {
  int l, r, id;
  qry() = default;
  qry(int _l, int _r, int _id) {
    l = _l, r = _r, id = _id;
  }
  inline void init(int _i) {
    l = rd(), r = rd();
    id = _i;
  }
  bool operator< (const qry &rhs) const {
    return l / B == rhs.l / B ? r < rhs.r : l < rhs.l;
  }
} q[N];
i64 ans[N];

pair<int, qry> _qry[N<<2];
int tot;
int L[N], R[N];
void qry_opt() {
  sort(_qry, _qry + tot);
  FOR(i, 0, n + 1) L[i] = tot, R[i] = 0;
  for (int i = 1; i <= tot; ++i) {
    chkmax(R[_qry[i].fi], i + 1);
    chkmin(L[_qry[i].fi], i);
  }
}

namespace solve_divisor { // (a, a) included
vector<int> fac[N];
void init() {
  for (int i = 1; i <= maxa; ++i) {
    for (int j = i; j <= maxa; j += i) {
      fac[j].pb(i);
    }
  }
}
int cnt[N];
void work() {
  for (int i = 1; i <= n; ++i) {
    pre[i] += cnt[a[i]];
    for (auto &v : fac[a[i]]) {
      ++cnt[v];
    }
    for (int kk = L[i]; kk < R[i]; ++kk) {
      auto u = _qry[kk].se;
      int to = u.id;
      if (u.l > 0) {
        for (int j = u.l; j <= u.r; ++j) {
          ans[to] += cnt[a[j]];
        }
      } else {
        for (int j = -u.l; j <= u.r; ++j) {
          ans[to] -= cnt[a[j]];
        }
      }
    }
  }
}
}

namespace solve_multiple { // (a, a) included
int cnt[N];
int f[N];
int s[N];
const int C = 4;
void init()
	{
		for(int i = 1; i <= n; i ++)
			s[a[i]] += n/a[i];
		for(int i = m; i >= 1; i --)
			s[i] = s[i+1] + s[i];
		i64 ans = 0x3f3f3f3f;
		for(int i = 1; i <= sqrt(n); i ++)
			if(i*n*C + s[i+1] < ans) {
				ans = i*n*C + s[i+1];
				T = i;
			}
	}
void work() {
  for (int i = 1; i <= n; ++i) {
    pre[i] += cnt[a[i]];
    if (a[i] > T) {
      for (int k = a[i]; k <= maxa; k += a[i]) {
        ++cnt[k];
      }
    }
    for (int kk = L[i]; kk < R[i]; ++kk) {
      auto &u = _qry[kk].se;
      int to = u.id;
      if (u.l > 0) {
        for (int j = u.l; j <= u.r; ++j) {
          ans[to] += cnt[a[j]];
        }
      } else {
        for (int j = -u.l; j <= u.r; ++j) {
          ans[to] -= cnt[a[j]];
        }
      }
    }
  }
  // part 2 (when a[i] <= T)
  for (int k = 1; k <= T; ++k) {
    for (int i = 1; i <= n; ++i) {
      f[i] = f[i-1];
      if (a[i] % k == 0) ++f[i];
    }
    int vis = 0;
    for (int i = 1; i <= n; ++i) {
      if (f[i] != f[i-1]) pre[i] += vis;
      if (a[i] == k) ++vis;
      for (int kk = L[i]; kk < R[i]; ++kk) {
        auto &u = _qry[kk].se;
        int to = u.id;
        if (u.l > 0) {
          ans[to] += 1ll * (f[u.r] - f[u.l-1]) * vis;
        } else {
          ans[to] -= 1ll * (f[u.r] - f[-u.l-1]) * vis;
        }
      }
    }
  }
}
}

i64 ret[N];

void solve() {
  n = rd(), m = rd();
  FOR(i, 1, n + 1) a[i] = rd(), chkmax(maxa, a[i]);
  FOR(i, 0, m) q[i].init(i);
  sort(q, q + m);
  int l = 1, r = 0;
  FOR(i, 0, m) {
    if (l > q[i].l) _qry[tot++] = mkp(r, qry(q[i].l, l - 1, i)), l = q[i].l;
    if (r < q[i].r) _qry[tot++] = mkp(l-1, qry(-r - 1, q[i].r, i)), r = q[i].r;
    if (l < q[i].l) _qry[tot++] = mkp(r, qry(-l, q[i].l-1, i)), l = q[i].l;
    if (r > q[i].r) _qry[tot++] = mkp(l-1, qry(q[i].r + 1, r, i)), r = q[i].r;
  }
  qry_opt();
  solve_divisor::init();
  solve_divisor::work();
//   solve_multiple::init();
  solve_multiple::work();
  l = 1, r = 0;
  FOR(i, 2, n + 1) pre[i] += pre[i-1];
  FOR(i, 0, m) {
    if (l > q[i].l) 
      ans[i] -= pre[l-1] - pre[q[i].l-1] + ((l -  q[i].l) << 1), l = q[i].l;
    if (r < q[i].r) ans[i] += pre[q[i].r] - pre[r], r = q[i].r;
    if (l < q[i].l) ans[i] += pre[q[i].l-1] - pre[l-1] + ((q[i].l - l) << 1), l = q[i].l;
    if (r > q[i].r) ans[i] -= pre[r] - pre[q[i].r], r = q[i].r;
  }
  FOR(i, 1, m) {
    ans[i] += ans[i - 1];
  }
  FOR(i, 0, m) {
    ret[q[i].id] = ans[i] + q[i].r - q[i].l + 1;
  }
  FOR(i, 0, m) 
    cout << ret[i] << '\n';
}
double clc;
int main() {
  IO::init_in();
#ifdef MULTI
  int T = IO::rd();
  while (T--) solve();
#else
clc = clock();
  solve();
cerr << (clock() - clc) / CLOCKS_PER_SEC << endl;
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

