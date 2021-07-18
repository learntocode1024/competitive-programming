/**********************************************************************
 * This file is the c++ solution to a particular CP problem written by
 * misaka18931 and was hosted on GitHub Repository below:
 * URL: https://github.com/misaka18931/competitive-programming
 *
 * Original Author: misaka18931
 * Date: Jul 18, 2021
 * Algorithm:
 * Difficulty:
 *
 *********************************************************************/

#include <algorithm>
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
#define MX 2000005

template<typename T>
void chkmax(T &a, const T &b) {
  a = max(a, b);
}
template <typename T>
void chkmin(T &a, const T &b) {
  b = min(a, b);
}

int n, q;
int a[MX];

namespace SUB20 {
int cnt[5005];
void solve() {
  while (q--) {
    int l, r;
    scanf("%d%d", &l, &r);
    int all = 0;
    for (int i = l; i <= r; ++i) {
      all += cnt[a[i]] == 0;
      cnt[a[i]]++;
    }
    for (int i = 1; i <= n; ++i) cnt[i] = 0;
    int L = 1, R = r - l + 2;
    while (R > L) {
      int mid = (L + R) / 2;
      int count(0), curr(0);
      for (int i = 0; i < mid; ++i) {
        curr += cnt[a[l + i]] == 0;
        ++cnt[a[l + i]];
      }
      chkmax(count, curr);
      for (int i = l + 1; i + mid - 1 <= r; ++i) {
        cnt[a[i - 1]]--;
        curr -= cnt[a[i - 1]] == 0;
        curr += cnt[a[i + mid - 1]] == 0;
        cnt[a[i + mid - 1]]++;
        chkmax(count, curr);
      }
      /* printf("%d %d\n", mid, count); */
      for (int i = 1; i <= n; ++i) cnt[i] = 0;
      if (count == all) R = mid;
      else L = mid + 1;
    }
    printf("%d\n", L);
  }
}
}

namespace SUB50 {
int cnt[50005];
void solve() {
  while (q--) {
    int l, r;
    scanf("%d%d", &l, &r);
    int all = 0;
    for (int i = l; i <= r; ++i) {
      all += cnt[a[i]] == 0;
      cnt[a[i]]++;
    }
    for (int i = 1; i <= n; ++i) cnt[i] = 0;
    int L = 1, R = r - l + 2;
    while (R > L) {
      int mid = (L + R) / 2;
      int count(0), curr(0);
      for (int i = 0; i < mid; ++i) {
        curr += cnt[a[l + i]] == 0;
        ++cnt[a[l + i]];
      }
      chkmax(count, curr);
      for (int i = l + 1; i + mid - 1 <= r; ++i) {
        cnt[a[i - 1]]--;
        curr -= cnt[a[i - 1]] == 0;
        curr += cnt[a[i + mid - 1]] == 0;
        cnt[a[i + mid - 1]]++;
        chkmax(count, curr);
      }
      /* printf("%d %d\n", mid, count); */
      for (int i = 1; i <= n; ++i) cnt[i] = 0;
      if (count == all) R = mid;
      else L = mid + 1;
    }
    printf("%d\n", L);
  }
}}

void solve() {
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", a + i);
  }
  scanf("%d", &q);
  if (n <= 5000) SUB20::solve();
  if (n <= 50000) SUB50::solve();
}

int main() {
  int T = 1;
  while (T--)
    solve();
  return 0;
}

