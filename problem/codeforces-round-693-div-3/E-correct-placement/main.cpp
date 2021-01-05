// Original Author: misaka18931
// Date: 01-04-21
// tag: sort, binary-search
// 

#include <cstdio>
#include <algorithm>
#include <cstring>
#include <iostream>
#define MX 200005
using std::cin;
using std::cout;
using std::endl;
using std::memset;
typedef long long LL;
typedef unsigned long long ULL;
const int mod = 1e9 + 7;
int T;

struct cube {
  int id;
  int w, h;
} a[MX];

int to[MX], min_v[MX], ans[MX];

bool cmp(const cube &a, const cube &b) {
  return (a.h < b.h);
}

void solve() {
  int n;
  cin >> n;
  for (int i = 0; i < n; ++i) {
    cin >> a[i].h >> a[i].w;
    a[i].id = i;
  }
  std::sort(a, a + n, cmp);
  min_v[0] = 0;
  for (int i = 1; i < n; ++i) {
    if (a[i].h == a[i - 1].h) to[i] = to[i - 1];
    else to[i] = i - 1;
    if (a[i].w >= a[i - 1].w) min_v[i] = min_v[i - 1];
    else min_v[i] = i;
  } // prework
  for (int i = 0; i < n; ++i) {
    int id = a[i].id;
    if (a[i].w > a[min_v[to[i]]].w)
      ans[id] = a[min_v[to[i]]].id;
    else ans[id] = -1;
  }
  for (int i = 0; i < n; ++i) {
    cout << ans[i] << ' ';
  }
  cout << endl;
  memset(a, 0, n * sizeof(cube));
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
