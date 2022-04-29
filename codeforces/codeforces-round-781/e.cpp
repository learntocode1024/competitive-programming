#include <bits/stdc++.h>
using namespace std;
#ifndef MISAKA
#define OO(x)
#else
#define OO(x) cout << __PRETTY_FUNCTION__ << ": " << #x << " : " << (x) << '\n';
#endif
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
void O(const A& a) {
  cout << a << '\n';
}
template<typename A, typename... B>
void O(const A& a, const B& ...b) {
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
#define FOR(i, j, k) for (int i = (j); i <= (k); ++i)
#define ROF(i, j, k) for (int i = (k); i >= (j); --i)
template<typename T>
inline void chkmin(T &a, const T b) {
  a = min(a, b);
}
template<typename T>
inline void chkmax(T &a, const T b) {
  a = max(a, b);
}

#define MULTI
const int N = 3e5+5, M = 30;

const int MX = N*M;
struct TRIE {
  int tot;
  int ch[MX][2], c[MX];
  inline int gen(int o = 0) {
    ++tot;
    ch[tot][0] = ch[o][0];
    ch[tot][1] = ch[o][1];
    c[tot] = c[o];
    return tot;
  }
  inline int ins(int rt, int x) {
    int p = gen(rt);
    int crt = p;
    ++c[p];
    ROF(i,0,M-1) {
      int cu = (x>>i)&1;
      ch[p][cu] = gen(ch[rt][cu]);
      p = ch[p][cu];
      rt = ch[rt][cu];
      ++c[p];
    }
    return crt;
  }
  inline int get(int r1, int r2) {
    static int rt[M+5], lt[M+5];
    int m = 1;
    rt[0] = r1;
    lt[0] = r2;
    int ret = 0;
    ROF(i,0,M-1) {
      int cnt = 0;
      FOR(j,0,m-1) cnt += c[ch[rt[j]][0]];
      FOR(j,0,m-1) cnt -= c[ch[lt[j]][0]];
      if (cnt >= 2) {
        FOR(j,0,m-1) rt[j] = ch[rt[j]][0];
        FOR(j,0,m-1) lt[j] = ch[lt[j]][0];
      } else {
        ret |= 1 << i;
        if (!cnt) {
          FOR(j,0,m-1) rt[j] = ch[rt[j]][1];
          FOR(j,0,m-1) lt[j] = ch[lt[j]][1];
        } else {
          int m0 = m-1;
          FOR(j,0,m0) {
            if (c[ch[rt[j]][0]] > c[ch[lt[j]][0]]) {
              rt[m] = ch[rt[j]][0];
              lt[m] = ch[lt[j]][0];
              ++m;
            }
            rt[j] = ch[rt[j]][1];
            lt[j] = ch[lt[j]][1];
          }
        }
      }
    }
    return ret;
  }
} T;

int rt[N], a[N], ans[N];
vector<pii> g[N];

inline void solve() {
  T.tot = 0;
  int n;
  rd(n);
  FOR(i,1,n) rd(a[i]), g[i].clear();
  int q;
  rd(q);
  FOR(i,1,q) {
    int l, r;
    rd(l,r);
    g[r].eb(l-1,i);
  }
  FOR(i,1,n) {
    rt[i] = T.ins(rt[i-1], a[i]);
    for (auto &[l, id] : g[i]) {
      ans[id] = T.get(rt[i], rt[l]);
    }
  }
  FOR(i,1,q) O(ans[i]);
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

