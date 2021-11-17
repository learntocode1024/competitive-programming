#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
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

struct buffer {
  int sz;
  int tot;
  tree<int, i64, less<int>, rb_tree_tag, tree_order_statistics_node_update> T;
  inline void ins(i64 x) {
    T.insert({++tot, x});
    ++sz;
  }
  inline i64 pop(int k) {
    --sz;
    auto it = T.find_by_order(k - 1);
    i64 ret = it->se;
    T.erase(it);
    return ret;
  } 
};

buffer C;

const int N = 3e5+5;
int n, m, q;

struct row {
  int sz;
  i64 pre;
  buffer r;
  tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> S;
  inline i64 pop(int k) {
    if (k > sz) return r.pop(k - sz);
    --sz;
    int l = 0, r = m - 1;
    while (r - l > 1) {
      int mid = (l + r) >> 1;
      int cur = mid - S.order_of_key(mid + 1);
      if (cur >= k) r = mid;
      else l = mid;
    }
    S.insert(r);
    return pre + r;
  }
  inline void ins(i64 x) {
    return r.ins(x);
  }
};

row R[N];

inline void solve() {
  rd(n, m, q);
  FOR(i, 1, n + 1) {
    i64 x = 1ll * (i - 1) * m;
    R[i].pre = x;
    R[i].sz = m - 1;
    C.ins(x + m);
  }
  while (q--) {
    int x, y;
    i64 ret;
    rd(x, y);
    if (y == m) {
      ret = C.pop(x);
    } else {
      ret = R[x].pop(y);
      R[x].ins(C.pop(x));
    }
    println(ret);
    C.ins(ret);
  }
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

