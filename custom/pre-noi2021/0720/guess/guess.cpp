#include "guess.h"
#include <bits/stdc++.h>
using namespace std;

vector<int> a;
int n;
namespace SUB1 {
void solve() {
  a[0] = 1;
  vector<int> c(1), b(1);
  for (int i = 1; i < n; ++i) {
    c[0] = i;
    a[i] = ask1(c, b);
  }
  if (!ask2(a)) {
    for (int i = 0; i < n; ++i) a[i] = -a[i];
  }
}
}
namespace SUB23 {
int e = -1;
int get_e() {
  vector<int> A(n - 1), B(1);
  for (int i = 0; i < n - 1; ++i) A[i] = i + 1;
  for (int i = 0; i < n; ++i) {
    B[0] = i;
    if (ask1(A, B) != 0) {
      return i;
    }
    A[i] = i;
  }
  return -1;
}

void solve() {
  e = get_e();
  a[e] = 1;
  vector<int> c(1), b(1);
  b[0] = e;
  for (int i = 0; i < n; ++i) {
    if (i == e) continue;
    c[0] = i;
    a[i] = ask1(c, b);
  }
  if (!ask2(a)) {
    for (int i = 0; i < n; ++i) a[i] = -a[i];
  }
}
}

namespace SOL {
int e;

int work(int l, int r) {
  int mid = l + (r - l) / 2;
  vector<int> R;
  for (int i = mid; i < r; ++i) R.push_back(i);
  int s = l, t = mid;
  while (t - s > 1) {
    int m = s + (t - s) / 2;
    vector<int> L;
    for (int i = s; i < m; ++i) L.push_back(i);
    if (ask1(L, R) != 0) t = m;
    else s = m;
  }
  return s;
}

int get_e(int l, int r) {
  /* cout << "Eval: [" << l << ", " << r << ")\n"; */
  if (r - l < 2) return -1;
  int mid = l + (r - l) / 2;
  vector<int> L, R;
  for (int i = l; i < mid; ++i) L.push_back(i);
  for (int i = mid; i < r; ++i) R.push_back(i);
  if (ask1(L, R) != 0) {
    if (mid - l == 1) return l;
    if (r - mid == 1) return r;
    return work(l, r);
  }
  int ret = get_e(l, mid);
  if (ret >= 0) return ret;
  return get_e(mid, r);
}

void solve() {
  e = get_e(0, n);
  a[e] = 1;
  vector<int> c(1), b(1);
  b[0] = e;
  for (int i = 0; i < n; ++i) {
    if (i == e) continue;
    c[0] = i;
    a[i] = ask1(c, b);
  }
  if (!ask2(a)) {
    for (int i = 0; i < n; ++i) a[i] = -a[i];
  }
}

}

vector<int> solve(int n, int P, int Q) {
  ::n = n;
  a = vector<int>(n);
  if (Q == 10000001) {
    SUB1::solve();
  } else if (Q <= 10000003) SUB23::solve();
  else SOL::solve();
  return a;
}
