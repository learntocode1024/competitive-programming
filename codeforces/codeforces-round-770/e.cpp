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
const int N = 4e5+5;
vector<int> a[N];
string s[N];
int aa[N], tot;
int m, n[N];
int cnt[N], lst[N], crf[N];
int R[N], C[N], id;
int h[N], to[N<<1], tid[N<<1], nxt[N<<1], tt;
bool vis[N];

void add_edge(int u, int v, int w) {
  ++tt;
  to[tt] = v;
  tid[tt] = w;
  nxt[tt] = h[u];
  h[u] = tt;
}

void dfs(int u, int col) {
  for (int &i = h[u]; i; i = nxt[i]) {
    int v = to[i], w = tid[i];
    if (vis[w]) continue;
    vis[w] = 1;
    s[R[w]][C[w]] = col? 'L' : 'R';
    dfs(v, col^1);
    return;
  }
}

inline void solve() {
  cin >> m;
  FOR(i, 1, m + 1) {
    cin >> n[i];
    s[i] = string(n[i],'A');
    FOR(j, 0, n[i]) {
      int cc;
      cin >> cc;
      aa[tot++] = cc;
      a[i].pb(cc);
    }
  }
  sort(aa, aa + tot);
  tot = unique(aa, aa + tot) - aa;
  FOR(i, 1, m + 1) {
    FOR(j, 0, n[i]) {
      a[i][j] = lower_bound(aa, aa + tot, a[i][j]) - aa + 1;
    }
  }
  bool has_ans = 1;
  FOR(i, 1, m + 1) {
    FOR(j, 0, n[i]) {
      ++cnt[a[i][j]];
      lst[a[i][j]] = j;
      ++crf[a[i][j]];
    }
    FOR(j, 0, n[i]) {
      if (cnt[a[i][j]]&1) {
        --cnt[a[i][j]];
        ++id;
        add_edge(i+tot, a[i][j], id);
        add_edge(a[i][j], i+tot, id);
        R[id] = i;
        C[id] = lst[a[i][j]];
      }
    }
    FOR(j, 0, n[i]) {
      if (cnt[a[i][j]]) {
        --cnt[a[i][j]];
        s[i][j] = (cnt[a[i][j]]&1)?'L':'R';
      }
    }
  } // defaults
  FOR(i, 1, tot+1) {
    if (crf[i]&1) has_ans = 0;
  }
  if (!has_ans) {
    println("NO");
    return;
  }
  println("YES");
  FOR(i, 1, tot + 1) {
    while (h[i]) dfs(i, 0);
  }
  FOR(i, 1, m+1) {
    cout << s[i] << '\n';
  }
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

