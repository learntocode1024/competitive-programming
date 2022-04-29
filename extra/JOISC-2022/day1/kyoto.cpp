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

//#define MULTI
const int N = 1e5+5;
list<pii> a, b;
bool va[N], vb[N];
int h, w;
int h1, w1;

struct node {
  i64 p, q;
  bool c;
  list<pii>::iterator it;
  int id;
  bool operator< (const node &b) const { return p * b.q < b.p * q || (p*b.q==b.p*q&& id<b.id); };
};

set<node> pq;

inline void solve() {
  rd(h,w);
  h1 = h, w1 = w;
  FOR(i,1,h) {
    int x;
    rd(x);
    a.pb({i,x});
  }
  FOR(i,1,w) {
    int x;
    rd(x);
    b.pb({i,x});
  }
  for (auto i = a.begin(), j = ++a.begin(); j != a.end(); ++i, ++j) {
    pq.insert({j->se-i->se, 1, 0, j, j->fi<<1});
  }
  for (auto i = b.begin(), j = ++b.begin(); j != b.end(); ++i, ++j) {
    pq.insert({j->se-i->se, 1, 1, j, j->fi<<1|1});
  }
  i64 ans = 0;
  while (!pq.empty()) {
    auto u = *pq.rbegin();
    pq.erase(*pq.rbegin());
    auto it = next(u.it);
    auto &A = u.c ? b : a;
    if (it != A.end()) {
      pq.erase({(it->se-u.it->se),(it->fi-u.it->fi), u.c, it, it->fi<<1|u.c});
      auto i2 = prev(u.it);
      pq.insert({(it->se-i2->se),(it->fi-i2->fi), u.c, it, it->fi<<1|u.c});
    }
    if (u.c) vb[u.it->fi] = 1;
    else va[u.it->fi] = 1;
    if (va[h1] && vb[w1]) {
      if (u.c) {
        ans += 1ll * u.it->se * (h1 - a.rbegin()->fi);
        h1 = a.rbegin()->fi;
      } else {
        ans += 1ll * u.it->se * (w1 - b.rbegin()->fi);
        w1 = b.rbegin()->fi;
      }
    }
    A.erase(u.it);
  }
  if (h1 != 1) ans += 1ll * b.begin()->se * (h1-1);
  if (w1 != 1) ans += 1ll * a.begin()->se * (w1-1);
  O(ans);
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

