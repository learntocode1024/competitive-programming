#include <bits/stdc++.h>
using namespace std;
typedef long long i64;
typedef unsigned long long u64;
typedef unsigned u32;
#define FOR(i, j, k) for (int i = j; i < k; ++i)
const int N = 2e5+5, MX = 5e5+5, MXLOG=6638449 + 100;

int h[MX];
int low[MX], pri[MX], miu[MX], tpri;
int nxt[MXLOG], val[MXLOG], tot;
int a[N];
bool vis[N];
int cnt[MX];
i64 ans = 0;

inline void ins(int pos) {
  int x = a[pos];
  for (int i = h[x]; i; i = nxt[i]) {
    int k = val[i];
    ans += miu[k] * cnt[k];
    ++cnt[k];
  }
  vis[pos] = 1;
}

inline void del(int pos) {
  int x = a[pos];
  for (int i = h[x]; i; i = nxt[i]) {
    int k = val[i];
    --cnt[k];
    ans -= miu[k] * cnt[k];
  }
  vis[pos] = 0;
}

int main() {
  freopen("gcd.in", "r", stdin);
  freopen("gcd.out", "w", stdout);
  cin.tie(0);
  ios::sync_with_stdio(0);
  for (int i = 1; i <= 500000; ++i) {
    for (int j = i; j <= 500000; j += i) {
      val[++tot] = i;
      nxt[tot] = h[j];
      h[j] = tot;
    }
  }
  low[1] = miu[1] = 1;
  for (int i = 2; i <= 500000; ++i) {
    if (!low[i]) {
      pri[tpri++] = i;
      low[i] = i;
      miu[i] = -1;
    }
    for (int j = 0; j < tpri && pri[j] * i <= 500000; ++j) {
      int to = pri[j] * i;
      low[to] = pri[j];
      if (pri[j] == low[i]) {
        miu[to] = 0;
        break;
      } else {
        miu[to] = -miu[i];
      }
    }
  }
  int n, m;
  cin >> n >> m;
  FOR(i, 1, n + 1) {
    cin >> a[i];
  }
  FOR(i, 0, m) {
    int t;
    cin >> t;
    if (vis[t]) del(t);
    else ins(t);
    cout << ans << '\n';
  }
  return 0;
}
