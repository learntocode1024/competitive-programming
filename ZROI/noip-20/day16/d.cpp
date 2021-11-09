#include <bits/stdc++.h>
using namespace std;
template <typename T>
void rd(T& a) {
  cin >> a;
}
template <typename A, typename... B>
void rd(A& a, B&... b) {
  cin >> a;
  rd(b...);
}
template <typename A>
void print(const A& a) {
  cout << a;
}
template <typename A, typename... B>
void print(const A& a, const B&... b) {
  cout << a;
  print(b...);
}
template <typename A>
void println(const A& a) {
  cout << a << '\n';
}
template <typename A, typename... B>
void println(const A& a, const B&... b) {
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
#define ROF(i, j, k) for (int i = ((k)-1); i >= j; --i)
template <typename T>
inline void chkmin(T& a, const T b) {
  a = min(a, b);
}
template <typename T>
inline void chkmax(T& a, const T b) {
  a = max(a, b);
}

const int N = 1e5 + 5;
int n, k;

struct segT {
  struct node {
    int l, r;
    int s;
  } a[N << 5];
  int tot;
  constexpr void reset() { tot = 0; }
  void ch(int& p, int l, int r, int t, int v) {
    if (!p) {
      p = ++tot;
      memset(&a[p], 0, sizeof(a[p]));
    }
    if (r - l == 1) {
      a[p].s += v;
      return;
    }
    int mid = (l + r) >> 1;
    if (t < mid)
      ch(a[p].l, l, mid, t, v);
    else
      ch(a[p].r, mid, r, t, v);
    a[p].s += v;
  }
  inline void mod(int& rt, int pos, int v) { return ch(rt, 0, n, pos, v); }
  int get(int p, int l, int r, int s) {
    if (!p) return 0;
    if (r == s + 1) return a[p].s;
    int mid = (l + r) >> 1;
    if (s < mid) return get(a[p].l, l, mid, s);
    else return a[a[p].l].s + get(a[p].r, mid, r, s);
  }
  int get2(int p, int l, int r, int s) {
    // if (!p) return -2;
    if (r - l == 1) return (a[p].s == s) ? l : -2;
    int mid = (l + r) >> 1;
    if (s > a[a[p].l].s) return get2(a[p].r, mid, r, s - a[a[p].l].s);
    else return get2(a[p].l, l, mid, s);
  }
  inline int work(int rt, int sum, int l, int r) {
    --l, --r;
    if (get(rt, 0, n, l) > sum || get(rt, 0, n, r) < sum) return -1;
    return max(l, get2(rt, 0, n, sum)) + 1;
  }
} T;

pii ans[N];
int tans;

namespace sam {
int len[N << 1], nxt[26][N << 1], f[N << 1];
int rts[N << 1];
set<int> pos[N << 1];
vector<int> G[N << 1];
int lst, tot;
void init() { f[0] = -1; }
inline void reset() {
  for (int i = 0; i <= tot; ++i) {
    rts[i] = 0;
    G[i].clear();
    pos[i].clear();
    f[i] = 0;
    FOR(j, 0, 26) nxt[j][i] = 0;
  }
  lst = tot = 0;
}
void expand(char ch) {
  int cur = ++tot;
  len[cur] = len[lst] + 1;
  pos[cur].insert(n - len[cur] + 1);
  int p = lst;
  for (; p != -1 && !nxt[ch][p]; p = f[p]) {
    nxt[ch][p] = cur;
  }
  if (p == -1) {
    f[cur] = 0;
  } else {
    int q = nxt[ch][p];
    if (len[q] == len[p] + 1) {
      f[cur] = q;
    } else {
      int mir = ++tot;
      for (int i = 0; i < 26; ++i) nxt[i][mir] = nxt[i][q];
      len[mir] = len[p] + 1;
      f[mir] = f[q];
      f[q] = f[cur] = mir;
      for (; p != -1 && nxt[ch][p] == q; p = f[p]) {
        nxt[ch][p] = mir;
      }
    }
  }
  lst = cur;
}

void dfs(int u) {
  for (auto v : G[u]) {
    dfs(v);
    if (pos[v].size() > pos[u].size()) {
      swap(pos[u], pos[v]);
      swap(rts[u], rts[v]);
    }
    for (auto i : pos[v]) {
      auto it = pos[u].insert(i).fi;
      if (it == pos[u].begin()) {
        auto nxt = it;
        nxt++;
        T.mod(rts[u], *nxt - *it - 1, 1);
      } else if (it == (--pos[u].end())) {
        auto pre = it;
        pre--;
        T.mod(rts[u], *it - *pre - 1, 1);
      } else {
        auto nxt = it;
        nxt++;
        T.mod(rts[u], *nxt - *it - 1, 1);
        auto pre = it;
        pre--;
        T.mod(rts[u], *it - *pre - 1, 1);
        T.mod(rts[u], *nxt - *pre - 1, -1);
      }
    }
    pos[v].clear();
  }
  if (u && pos[u].size() >= k) {
    int ret = T.work(rts[u], pos[u].size() - k, len[f[u]] + 1, len[u]);
    if (ret != -1) {
      // cerr << "found";
      ans[++tans] = mkp(*pos[u].begin(), ret);
    }
  }
}

void work() {
  for (int i = 1; i <= tot; ++i) {
    G[f[i]].pb(i);
  }
  dfs(0);
}
}  // namespace sam
char s[N];

i64 pw[N] = {1, 11451};
const i64 p = 1e9+9;
i64 h[N];

inline void Hash() {
  FOR(i, 2, n + 1) pw[i] = pw[i - 1] * pw[1] % p;
  h[0] = s[0];
  FOR(i, 1, n) h[i] = (h[i - 1] * pw[1] + s[i]) % p;
}

i64 H(int l, int r) {
  if (!l) return h[r - 1];
  return (h[r - 1] + p - h[l - 1] * pw[r - l] % p) % p;
}

inline bool comp(int a1, int l1, int a2, int l2) {
  int l = 0, r = min(l1, l2) + 1;
  while (r - l > 1) {
    int mid = (l + r) >> 1;
    if (H(a1, a1 + mid) == H(a2, a2 + mid)) l = mid;
    else r = mid;
  }
  if (l == l2) return 0;
  if (l == l1) return 1;
  return s[a1 + l] < s[a2 + l];
}

inline void solve() {
  tans = 0;
  cin >> s;
  T.reset();
  sam::init();
  n = strlen(s);
  Hash();
  for (int i = 0; i < n; ++i) {
    sam::expand(s[n - i - 1] - 'a');
  }
  cin >> k;
  sam::work();
  if (!tans) {
    println(-1);
  } else {
    sort(ans + 1, ans + tans + 1, [] (auto a, auto b) {return comp(a.fi - 1, a.se, b.fi - 1, b.se); } );
    for (int j = 0; j < ans[1].se; ++j) {
      cout << s[j + ans[1].fi - 1];
    }
    cout << '\n';
  }
  sam::reset();
}

int main() {
#ifndef MISAKA
  // freopen(".in", "r", stdin);
  // freopen(".out", "w", stdout);
  // ios::sync_with_stdio(0);
  // cin.tie(0);
#endif
  int T;
  cin >> T;
  while (T--)
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
