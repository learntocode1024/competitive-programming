#include <algorithm>
#include <cmath>
#include <cstring>
#include <iostream>

#include "io"
#include "utils"

const int N = 100005;
int n, m, a[N], blk[N];
const int B = 330;
i64 ans[N];  
struct qry {
  int l, r, id;
  inline void init(int x) { l = rd(), r = rd(), id = x; };
  bool operator<(const qry &rhs) const {
    return blk[l] < blk[rhs.l] || (blk[l] == blk[rhs.l] && r < rhs.r);
  }
} q[N];
char s[N];

inline void mkblk() {
  for (int i = 1; i <= n; ++i) blk[i] = (i - 1) % B + 1;
}

int sa[N], rk[N], ht[N];

namespace SA {
int oldrk[N << 1], id[N], px[N], cnt[N];
bool cmp(int x, int y, int w) {
  return oldrk[x] == oldrk[y] && oldrk[x + w] == oldrk[y + w];
}
inline void sa_init() {
  int i, m = 300, p, w, k;
  for (i = 1; i <= n; ++i) ++cnt[rk[i] = s[i]];
  for (i = 1; i <= m; ++i) cnt[i] += cnt[i - 1];
  for (i = n; i >= 1; --i) sa[cnt[rk[i]]--] = i;

  for (w = 1;; w <<= 1, m = p) {  // m=p 就是优化计数排序值域
    for (p = 0, i = n; i > n - w; --i) id[++p] = i;
    for (i = 1; i <= n; ++i)
      if (sa[i] > w) id[++p] = sa[i] - w;
    memset(cnt, 0, sizeof(cnt));
    for (i = 1; i <= n; ++i) ++cnt[px[i] = rk[id[i]]];
    for (i = 1; i <= m; ++i) cnt[i] += cnt[i - 1];
    for (i = n; i >= 1; --i) sa[cnt[px[i]]--] = id[i];
    memcpy(oldrk, rk, sizeof(rk));
    for (p = 0, i = 1; i <= n; ++i)
      rk[sa[i]] = cmp(sa[i], sa[i - 1], w) ? p : ++p;
    if (p == n) {
      for (int i = 1; i <= n; ++i) sa[rk[i]] = i;
      break;
    }
  }

  for (i = 1, k = 0; i <= n; ++i) {
    if (k) --k;
    while (s[i + k] == s[sa[rk[i] - 1] + k]) ++k;
    ht[rk[i]] = k;  // height太长了缩写为ht
  }
}
}  // namespace SA

struct qqry {
  int x, l, r, t, id;
} c[N];

inline void prework() {
  
}

inline void mo() {
  sort(q, q + n);
}

inline void calc1() {
  
}

inline void calc2() {
  
}

int main() {
  IO::init_in();
  n = rd(), m = rd();
  rdstr(s + 1);
  FOR(i, 0, n) a[i] = rd();
  FOR(i, 0, m) q[i].init(i);
  SA::sa_init();
  mkblk();
  mo();
  calc1();
  calc2();
  FOR(i, 1, m) ans[q[i].id] += ans[q[i - 1].id];
  FOR(i, 0, m) cout << ans[i] << '\n';
}