// Original Author: misaka18931
// Date: 01-04-21
// tag: sort, binary-search
//

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
#define MX 200005
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
const int mod = 1e9 + 7;

struct v {
  LL id;
  LL w, h;
  v(LL a, LL b, LL c) { w = a, h = b, id = c; }
};

vector<v> a, b;
vector<LL> ma, mb;
LL ans[MX];

LL find(vector<v> a, vector<LL> m, LL w, LL h) {
  auto r = lower_bound(a.begin(), a.end(), h, [](v t, LL p) { return t.h < p; });
  auto x = lower_bound(m.begin(), m.begin() + (r - a.begin()), -w + 1);
  if (x == m.begin() + (r - a.begin())) return -1;
  return x - m.begin();
}

void solve() {
  int n;
  cin >> n;
  for (int i = 0; i < n; ++i) {
    LL x, y;
    cin >> x >> y;
    a.push_back(v(x, y, i));
    b.push_back(v(y, x, i));
  }
  for (int i = 0; i < n; ++i) {
    ma.push_back(a[i].w);
    if (i) ma[i] = min(ma[i], ma[i - 1]);
    mb.push_back(b[i].w);
    if (i)
      mb[i] = min(mb[i], mb[i - 1]);
  }
  for (int i = 0; i < n; ++i) {
    ma[i] = -ma[i];
    mb[i] = -mb[i];
  }
  for (int i = 0; i < n; ++i) {
    LL curr = find(a, ma, a[i].w, a[i].h);
    if (curr == -1)
      curr = find(b, mb, a[i].w, a[i].h);
    ans[i] = curr;
  }
  sort(a.begin(), a.end(), [](v a, v b) { return a.h < b.h; });
  sort(b.begin(), b.end(), [](v a, v b) { return a.h < b.h; });
  for (int i = 0; i < n; ++i) {
    cout << ans[i] + 1 << ' ';
  }
  cout << endl;
  a.clear(), b.clear();
  ma.clear(), mb.clear();
}

int main() {
  cin.tie(NULL);
  std::ios::sync_with_stdio(false);
  int T = 1;
  cin >> T;
  while (T--) {
    solve();
  }
  return 0;
}
