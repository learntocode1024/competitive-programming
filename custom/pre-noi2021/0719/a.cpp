/**********************************************************************
 * This file is the c++ solution to a particular CP problem written by
 * misaka18931 and was hosted on GitHub Repository below:
 * URL: https://github.com/misaka18931/competitive-programming
 *
 * Original Author: misaka18931
 * Date: Jul 19, 2021
 * Algorithm:
 * Difficulty:
 *
 *********************************************************************/

#include <algorithm>
#include <bitset>
#include <cctype>
#include <climits>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;

#define pb(x) push_back(x)
#define pf(x) push_front(x)
#define MX 100005

template<typename T>
void chkmax(T &a, const T &b) {
  a = max(a, b);
}
template <typename T>
void chkmin(T &a, const T &b) {
  b = min(a, b);
}

int n, q;

namespace BF {
bitset<600006> t;
char s[600006];
int a, b;
inline void getans() {
  for (int i = 0; i < n; ++i) {
    while (i < n && t[i] == t[i + 1]) ++i;
    a += t[i];
    b += !t[i];
  }
  /* a -= t[0] && t[n - 1]; */
  /* b -= !t[0] && !t[n - 1]; */
  /* printf("%d\n", min(a, b) + 1); */
  /* cout << t.to_string().substr(600006 - n, n) << endl; */
}
void solve() {
  n *= 6;
  scanf("%s", s);
  for (int i = 0; i < n; ++i) {
    t[i] = s[i] != '0';
  }
  getans();
  printf("%d\n", min(a - t[0] && t[n - 1], b - !t[0] && !t[n - 1]) + 1);
  while (q--) {
    int l, r;
    scanf("%d%d", &l, &r);
    if (l == r) {
      --l;
      if (l && l + 1 != n && t[l - 1] == t[l + 1]) {
        if (t[l] == t[l - 1]) ++a, ++b;
        else --a, --b;
      }
      if(!l) {
        
      }
      if (l + 1 == n) {

      }
      t.flip(l);
    }
    else {
      int len = (r - l + n) % n + 1;
      int r = l * 2 + len - 3;
      for (int i = l - 1; i * 2 < r; ++i)
        if (t[i % n] != t[(r - i) % n]) t.flip(i % n), t.flip((r - i) % n);
    }
    printf("%d\n", min(a - t[0] && t[n - 1], b - !t[0] && !t[n - 1]) + 1);
  }
}
}

namespace SEG {
struct node {
  int l, r, lc, rc;
  bool flp, v;
  inline void rev() {
    swap(lc, rc), flp ^= 1, swap(r, l);
  }
} tr[MX << 2];
#define val(p) tr[p].v
int get(int p, int pos) {
  if (tr[p].r - tr[p].l == 1) return val(p);
  int mid = (tr[p].l + tr[p].r) / 2;
  if (tr)
}

} // namespace SEG

int main() {
  scanf("%d%d", &n, &q);
  BF::solve();
  return 0;
}

